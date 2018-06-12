/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <main.h>

bool RakClient::RPC(int rpcId, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if (!pRakClient) return false;

	return pRakClient->RPC(&rpcId, bitStream, priority, reliability, orderingChannel, shiftTimestamp);
}

bool RakClient::Send(BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	if (!pRakClient) return false;

	return pRakClient->Send(bitStream, priority, reliability, orderingChannel);
}

// misc functions
void RakClient::SendDeath(uint16_t killerId, uint8_t reason)
{
	BitStream bsDeath;

	bsDeath.Write(reason);
	bsDeath.Write(killerId);
	this->RPC(RPC_Death, &bsDeath);
}

void RakClient::SendPickUp(int pickupId)
{
	BitStream bsPickup;
	bsPickup.Write(pickupId);
	this->RPC(RPC_PickedUpPickup, &bsPickup);
}

void RakClient::SendEnterVehicle(WORD wVehicleID, uint8_t bIsPassenger)
{
	if (pCRMP->getVehicles()->isBadVehicle(wVehicleID)) return;

	BitStream bsSend;
	bsSend.Write(wVehicleID);
	bsSend.Write(bIsPassenger);
	this->RPC(RPC_EnterVehicle, &bsSend);
}

void RakClient::SendClickTextDraw(int iTextId)
{
	BitStream bsSend;
	bsSend.Write(iTextId);
	this->RPC(RPC_ClickTextDraw, &bsSend);
}

void RakClient::SendVehicleDestroyed(int iVehicleId)
{
	BitStream bsSend;
	bsSend.Write(iVehicleId);
	this->RPC(RPC_VehicleDestroyed, &bsSend);
}

void RakClient::RequestClass(int classId)
{
	BitStream bsClass;
	bsClass.Write(classId);
	this->RPC(RPC_RequestClass, &bsClass);
}

void RakClient::SendSCMEvent(int eventId, int vehicleID, int param1, int param2)
{
	BitStream bsScmEvent;

	bsScmEvent.Write(eventId);
	bsScmEvent.Write(vehicleID);
	bsScmEvent.Write(param1);
	bsScmEvent.Write(param2);

	this->RPC(RPC_ScmEvent, &bsScmEvent);
}

void RakClient::SendSpawn(void)
{
	BitStream bsSpawn;
	this->RPC(RPC_RequestSpawn, &bsSpawn);
	this->RPC(RPC_Spawn, &bsSpawn);
}

void RakClient::SendGiveDamage(int iPlayerID, float fDamage, int iWeaponID, int iBodyPart)
{
	BitStream bsGiveDamage;

	bsGiveDamage.Write<bool>(false);
	bsGiveDamage.Write<WORD>(iPlayerID);
	bsGiveDamage.Write<float>(fDamage);
	bsGiveDamage.Write<int>(iWeaponID);
	bsGiveDamage.Write<int>(iBodyPart);

	this->RPC(RPC_GiveTakeDamage, &bsGiveDamage);
}

void RakClient::SendDialogResponse(WORD wDialogID, BYTE bButtonID, WORD wListBoxItem, const char *szInputResp)
{
	BitStream bsSend;
	size_t byteLen = strlen(szInputResp);
	bsSend.Write<WORD>(wDialogID);
	bsSend.Write<BYTE>(bButtonID);
	bsSend.Write<WORD>(wListBoxItem);
	bsSend.Write<BYTE>(byteLen);
	bsSend.Write(szInputResp, byteLen);
	this->RPC(RPC_DialogResponse, &bsSend);
}

void RakClient::SendFakeOnfootSyncData(float fPos[3], float fHealth, float fSpeed[3])
{
	stOnFootData ofSync; BitStream bsOnfootSync;
	memcpy(&ofSync, &pCRMP->getPlayers()->pLocalPlayer->onFootData, sizeof(stOnFootData));

	ofSync.byteHealth = (uint8_t)fHealth;
	vect3_copy(fPos, ofSync.fPosition);
	vect3_copy(fSpeed, ofSync.fMoveSpeed);

	bsOnfootSync.Write((BYTE)ID_PLAYER_SYNC);
	bsOnfootSync.Write((PCHAR)&ofSync, sizeof(stOnFootData));

	this->Send(&bsOnfootSync, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);
}

void RakClient::SendFakeDriverSyncData(int iVehicleID, float fVehiclePos[3], float fVehicleHealth, float fMoveSpeed[3])
{
	stInCarData carSync; BitStream bsInCarData;
	memcpy(&carSync, &pCRMP->getPlayers()->pLocalPlayer->inCarData, sizeof(stInCarData));

	carSync.sVehicleID = iVehicleID;
	carSync.fVehicleHealth = fVehicleHealth;

	vect3_copy(fVehiclePos, carSync.fPosition);
	vect3_copy(fMoveSpeed, carSync.fMoveSpeed);

	bsInCarData.Write((BYTE)ID_VEHICLE_SYNC);
	bsInCarData.Write((PCHAR)&carSync, sizeof(stInCarData));

	this->Send(&bsInCarData, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);
}

void RakClient::SendFakeAimSyncData(float vecAimPos[3], float vecAimf1[3], float fAimZ, BYTE byteCamMode, BYTE byteWeaponState)
{
	stAimData aimSync; BitStream bsAimSync;
	memcpy(&aimSync, &pCRMP->getPlayers()->pLocalPlayer->aimData, sizeof(stAimData));

	aimSync.fAimZ = fAimZ;
	aimSync.byteCamMode = byteCamMode;
	aimSync.byteWeaponState = byteWeaponState;
	vect3_copy(vecAimPos, aimSync.vecAimPos);
	vect3_copy(vecAimf1, aimSync.vecAimf1);

	bsAimSync.Write((BYTE)ID_AIM_SYNC);
	bsAimSync.Write((PCHAR)&aimSync, sizeof(stAimData));
	this->Send(&bsAimSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}

void RakClient::SendFakeTrailerSyncData(int iTrailerID, float fPos[3], float fSpeed[3])
{
	stTrailerData trailerSync; BitStream bsTrailer;
	memcpy(&trailerSync, &pCRMP->getPlayers()->pLocalPlayer->trailerData, sizeof(stTrailerData));

	trailerSync.sTrailerID = iTrailerID;
	vect3_copy(fPos, trailerSync.fPosition);
	vect3_copy(fSpeed, trailerSync.fSpeed);

	bsTrailer.Write((BYTE)ID_TRAILER_SYNC);
	bsTrailer.Write((PCHAR)&trailerSync, sizeof(bsTrailer));
	this->Send(&bsTrailer, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}