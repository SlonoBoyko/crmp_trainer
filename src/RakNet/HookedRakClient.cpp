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

uint8_t HookedRakClientInterface::GetPacketID(Packet *p)
{
	if (!p) return 0xFF;

	if (p->data[0] == ID_TIMESTAMP) {
		assert(p->length > 5);
		return p->data[5];
	} else return p->data[0];
}

bool HookedRakClientInterface::RPC(int* uniqueID, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	for (int i = 0; i < RAKNET_MAX_PACKET; i++) {
		if (ini.patch[i].id == *uniqueID && ini.patch[i].enabled && ini.patch[i].type == OUTCOMING_RPC)
			return false;
	}

	/*if (*uniqueID == RPC_ClientJoin) {
		char path[MAX_PATH];
		sprintf(path, "%s\\RPC_ClientJoin.txt", szWorkingDirectory);
		FILE *file = fopen(path, "wb");
		fwrite(bitStream->GetData(), bitStream->GetNumberOfBytesUsed(), 1, file);
		fclose(file);
	}*/

	return pCRMP->getRakClient()->GetInterface()->RPC(uniqueID, bitStream, priority, reliability, orderingChannel, shiftTimestamp);
}

bool HookedRakClientInterface::Send(BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	BYTE packetId;
	bitStream->Read(packetId);
	
	if (packetId == ID_AIM_SYNC)
	{
		stAimData OutgoingAimData;

		bitStream->ResetReadPointer();

		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&OutgoingAimData, sizeof(stAimData));
		
		/*if (pCRMP->getPlayers()->pLocalPlayer->byteCurrentWeapon > 22)
		{
			OutgoingAimData.vecAimPos[2] = pow(10.f + random::get_float(0, 1), random::get_float(6, 9))*(int)random::get_int(-1, 1) * 3;
			OutgoingAimData.byteCamMode = 53;
			OutgoingAimData.byteWeaponState = WS_MORE_BULLETS;
		}*/
		
		bitStream->Reset();
		bitStream->Write((BYTE)ID_AIM_SYNC);
		bitStream->Write((PCHAR)&OutgoingAimData, sizeof(stAimData));
	}

	if (packetId == ID_PLAYER_SYNC)
	{

		stOnFootData OutgoingOnFootData;

		bitStream->ResetReadPointer();

		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&OutgoingOnFootData, sizeof(stOnFootData));

		if (menu.banyhop)
		{
			if(OutgoingOnFootData.stSampKeys.keys_decel__jump && OutgoingOnFootData.sUpDownKeys == 0xFF80)
				OutgoingOnFootData.stSampKeys.keys_decel__jump = false;
		}

		if (menu.uinvisible)
		{
			if (OutgoingOnFootData.fPosition[2] >= 0.0f)
				OutgoingOnFootData.fPosition[2] = -20.0f;
			else OutgoingOnFootData.fPosition[2] -= 20.0f;
		}

		if (menu.pizdarvanka) {
			OutgoingOnFootData.fMoveSpeed[0] *= random::_float(-10.0f, 10.0f);
			OutgoingOnFootData.fMoveSpeed[1] *= random::_float(-10.0f, 10.0f);
		}

		if (menu.slapper)
		{
			int iPlayerID = pCRMP->getPlayers()->findNearestPlayer(500.0f);

			if (!pCRMP->getPlayers()->isBadPlayer(iPlayerID))
			{
				actor_info *ainfo = pCRMP->getPlayers()->getGTAPed(iPlayerID);
				if (isBadPtr_GTA_pPed(ainfo)) return true;

				static BYTE byteSlapperState = 0;
				float fHitAngle = byteSlapperState * HALF_PI;
				byteSlapperState = (byteSlapperState < 3) ? ++byteSlapperState : byteSlapperState = 0;

				if (ainfo->state == ACTOR_STATE_DRIVING) {
					OutgoingOnFootData.sCurrentAnimationID = 301;
					OutgoingOnFootData.fPosition[0] += sinf(-fHitAngle) * 15;
					OutgoingOnFootData.fPosition[1] += sinf(-fHitAngle) * 15;
				} else {
					OutgoingOnFootData.sCurrentAnimationID = random::get(0, 1000);
					OutgoingOnFootData.fQuaternion[0] = random::get(0.0f, 2.0f);
					OutgoingOnFootData.fQuaternion[1] = random::get(0.0f, 2.0f);
					OutgoingOnFootData.fQuaternion[2] = random::get(0.0f, 2.0f);
					OutgoingOnFootData.fQuaternion[3] = random::get(0.0f, 2.0f);
					OutgoingOnFootData.fPosition[0] += sinf(-fHitAngle) * 5;
					OutgoingOnFootData.fPosition[1] += sinf(-fHitAngle) * 5;
				}
				OutgoingOnFootData.fMoveSpeed[0] = sinf(fHitAngle) * 20;
				OutgoingOnFootData.fMoveSpeed[1] = cosf(fHitAngle) * 20;

				CVector vecOrig(OutgoingOnFootData.fPosition), vecTarget(ainfo->base.m_CMatrix->vPos);
				pPedSelf->GetWeapon(pPedSelf->GetCurrentWeaponSlot())->DoBulletImpact(0, 0, &vecOrig, &vecTarget, 0, 0);

			}
		}


		bitStream->Reset();
		bitStream->Write((BYTE)ID_PLAYER_SYNC);
		bitStream->Write((PCHAR)&OutgoingOnFootData, sizeof(stOnFootData));
	}
	if (packetId == ID_VEHICLE_SYNC)
	{
		stInCarData OutgoingInCarData;

		bitStream->ResetReadPointer();
		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&OutgoingInCarData, sizeof(stInCarData));

		if (menu.pizdarvanka) {
			OutgoingInCarData.fMoveSpeed[0] += random::get(-10.0f, 10.0f);
			OutgoingInCarData.fMoveSpeed[1] += random::get(-10.0f, 10.0f);
		}

		bitStream->Reset();
		bitStream->Write((BYTE)ID_VEHICLE_SYNC);
		bitStream->Write((PCHAR)&OutgoingInCarData, sizeof(stInCarData));

	}

	for (int i = 0; i < RAKNET_MAX_PACKET; i++){
		if (ini.patch[i].id == packetId && ini.patch[i].enabled && ini.patch[i].type == OUTCOMING_PACKET)
			return false;
	}

	return pCRMP->getRakClient()->GetInterface()->Send(bitStream, priority, reliability, orderingChannel);
}

Packet *HookedRakClientInterface::Receive(void)
{
	Packet *packet = pCRMP->getRakClient()->GetInterface()->Receive();
	BYTE packetId = GetPacketID(packet);

	if (packetId == ID_CONNECTION_LOST || packetId == ID_DISCONNECTION_NOTIFICATION) {
		if (menu.autoreconnect)
			packet->data[0] = ID_CONNECTION_LOST;
	}
	if (packetId == ID_CONNECTION_BANNED) {
		if (menu.autoreconnect) {
			pCRMP->getInfo()->disconnect(0);
			pCRMP->getInfo()->iGameState = GAMESTATE_WAIT_CONNECT;
		}
	}
	
	for (int i = 0; i < RAKNET_MAX_PACKET; i++){
		if (ini.patch[i].id == packetId && ini.patch[i].enabled && ini.patch[i].type == INCOMING_PACKET){
			pCRMP->getRakClient()->GetInterface()->DeallocatePacket(packet);
			packet = pCRMP->getRakClient()->GetInterface()->Receive();
		}
	}
	return packet;
}

bool HookedRakClientInterface::Connect(const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer)
{
	return pCRMP->getRakClient()->GetInterface()->Connect(host, serverPort, clientPort, depreciated, threadSleepTimer);
}

void HookedRakClientInterface::Disconnect(unsigned int blockDuration, unsigned char orderingChannel)
{
	pCRMP->getRakClient()->GetInterface()->Disconnect(blockDuration, orderingChannel);
}

void HookedRakClientInterface::InitializeSecurity(const char *privKeyP, const char *privKeyQ)
{
	pCRMP->getRakClient()->GetInterface()->InitializeSecurity(privKeyP, privKeyQ);
}

void HookedRakClientInterface::SetPassword(const char *_password)
{
	pCRMP->getRakClient()->GetInterface()->SetPassword(_password);
}

bool HookedRakClientInterface::HasPassword(void) const
{
	return pCRMP->getRakClient()->GetInterface()->HasPassword();
}

bool HookedRakClientInterface::Send(const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	return pCRMP->getRakClient()->GetInterface()->Send(data, length, priority, reliability, orderingChannel);
}

void HookedRakClientInterface::DeallocatePacket(Packet *packet)
{
	pCRMP->getRakClient()->GetInterface()->DeallocatePacket(packet);
}

void HookedRakClientInterface::PingServer(void)
{
	pCRMP->getRakClient()->GetInterface()->PingServer();
}

void HookedRakClientInterface::PingServer(const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections)
{
	pCRMP->getRakClient()->GetInterface()->PingServer(host, serverPort, clientPort, onlyReplyOnAcceptingConnections);
}

int HookedRakClientInterface::GetAveragePing(void)
{
	return pCRMP->getRakClient()->GetInterface()->GetAveragePing();
}

int HookedRakClientInterface::GetLastPing(void) const
{
	return pCRMP->getRakClient()->GetInterface()->GetLastPing();
}

int HookedRakClientInterface::GetLowestPing(void) const
{
	return pCRMP->getRakClient()->GetInterface()->GetLowestPing();
}

int HookedRakClientInterface::GetPlayerPing(const PlayerID playerId)
{
	return pCRMP->getRakClient()->GetInterface()->GetPlayerPing(playerId);
}

void HookedRakClientInterface::StartOccasionalPing(void)
{
	pCRMP->getRakClient()->GetInterface()->StartOccasionalPing();
}

void HookedRakClientInterface::StopOccasionalPing(void)
{
	pCRMP->getRakClient()->GetInterface()->StopOccasionalPing();
}

bool HookedRakClientInterface::IsConnected(void) const
{
	return pCRMP->getRakClient()->GetInterface()->IsConnected();
}

unsigned int HookedRakClientInterface::GetSynchronizedRandomInteger(void) const
{
	return pCRMP->getRakClient()->GetInterface()->GetSynchronizedRandomInteger();
}

bool HookedRakClientInterface::GenerateCompressionLayer(unsigned int inputFrequencyTable[256], bool inputLayer)
{
	return pCRMP->getRakClient()->GetInterface()->GenerateCompressionLayer(inputFrequencyTable, inputLayer);
}

bool HookedRakClientInterface::DeleteCompressionLayer(bool inputLayer)
{
	return pCRMP->getRakClient()->GetInterface()->DeleteCompressionLayer(inputLayer);
}

void HookedRakClientInterface::RegisterAsRemoteProcedureCall(int* uniqueID, void(*functionPointer) (RPCParameters *rpcParms))
{
	pCRMP->getRakClient()->GetInterface()->RegisterAsRemoteProcedureCall(uniqueID, functionPointer);
}

void HookedRakClientInterface::RegisterClassMemberRPC(int* uniqueID, void *functionPointer)
{
	pCRMP->getRakClient()->GetInterface()->RegisterClassMemberRPC(uniqueID, functionPointer);
}

void HookedRakClientInterface::UnregisterAsRemoteProcedureCall(int* uniqueID)
{
	pCRMP->getRakClient()->GetInterface()->UnregisterAsRemoteProcedureCall(uniqueID);
}

bool HookedRakClientInterface::RPC(int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	return pCRMP->getRakClient()->GetInterface()->RPC(uniqueID, data, bitLength, priority, reliability, orderingChannel, shiftTimestamp);
}

void HookedRakClientInterface::SetTrackFrequencyTable(bool b)
{
	pCRMP->getRakClient()->GetInterface()->SetTrackFrequencyTable(b);
}

bool HookedRakClientInterface::GetSendFrequencyTable(unsigned int outputFrequencyTable[256])
{
	return pCRMP->getRakClient()->GetInterface()->GetSendFrequencyTable(outputFrequencyTable);
}

float HookedRakClientInterface::GetCompressionRatio(void) const
{
	return pCRMP->getRakClient()->GetInterface()->GetCompressionRatio();
}

float HookedRakClientInterface::GetDecompressionRatio(void) const
{
	return pCRMP->getRakClient()->GetInterface()->GetDecompressionRatio();
}

void HookedRakClientInterface::AttachPlugin(void *messageHandler)
{
	pCRMP->getRakClient()->GetInterface()->AttachPlugin(messageHandler);
}

void HookedRakClientInterface::DetachPlugin(void *messageHandler)
{
	pCRMP->getRakClient()->GetInterface()->DetachPlugin(messageHandler);
}

BitStream * HookedRakClientInterface::GetStaticServerData(void)
{
	return pCRMP->getRakClient()->GetInterface()->GetStaticServerData();
}

void HookedRakClientInterface::SetStaticServerData(const char *data, const int length)
{
	pCRMP->getRakClient()->GetInterface()->SetStaticServerData(data, length);
}

BitStream * HookedRakClientInterface::GetStaticClientData(const PlayerID playerId)
{
	return pCRMP->getRakClient()->GetInterface()->GetStaticClientData(playerId);
}

void HookedRakClientInterface::SetStaticClientData(const PlayerID playerId, const char *data, const int length)
{
	pCRMP->getRakClient()->GetInterface()->SetStaticClientData(playerId, data, length);
}

void HookedRakClientInterface::SendStaticClientDataToServer(void)
{
	pCRMP->getRakClient()->GetInterface()->SendStaticClientDataToServer();
}

PlayerID HookedRakClientInterface::GetServerID(void) const
{
	return pCRMP->getRakClient()->GetInterface()->GetServerID();
}

PlayerID HookedRakClientInterface::GetPlayerID(void) const
{
	return pCRMP->getRakClient()->GetInterface()->GetPlayerID();
}

PlayerID HookedRakClientInterface::GetInternalID(void) const
{
	return pCRMP->getRakClient()->GetInterface()->GetInternalID();
}

const char* HookedRakClientInterface::PlayerIDToDottedIP(const PlayerID playerId) const
{
	return pCRMP->getRakClient()->GetInterface()->PlayerIDToDottedIP(playerId);
}

void HookedRakClientInterface::PushBackPacket(Packet *packet, bool pushAtHead)
{

	pCRMP->getRakClient()->GetInterface()->PushBackPacket(packet, pushAtHead);
}

void HookedRakClientInterface::SetRouterInterface(void *routerInterface)
{
	pCRMP->getRakClient()->GetInterface()->SetRouterInterface(routerInterface);
}
void HookedRakClientInterface::RemoveRouterInterface(void *routerInterface)
{
	pCRMP->getRakClient()->GetInterface()->RemoveRouterInterface(routerInterface);
}

void HookedRakClientInterface::SetTimeoutTime(RakNetTime timeMS)
{
	pCRMP->getRakClient()->GetInterface()->SetTimeoutTime(timeMS);
}

bool HookedRakClientInterface::SetMTUSize(int size)
{
	return pCRMP->getRakClient()->GetInterface()->SetMTUSize(size);
}

int HookedRakClientInterface::GetMTUSize(void) const
{
	return pCRMP->getRakClient()->GetInterface()->GetMTUSize();
}

void HookedRakClientInterface::AllowConnectionResponseIPMigration(bool allow)
{
	pCRMP->getRakClient()->GetInterface()->AllowConnectionResponseIPMigration(allow);
}

void HookedRakClientInterface::AdvertiseSystem(const char *host, unsigned short remotePort, const char *data, int dataLength)
{
	pCRMP->getRakClient()->GetInterface()->AdvertiseSystem(host, remotePort, data, dataLength);
}

RakNetStatisticsStruct* const HookedRakClientInterface::GetStatistics(void)
{
	return pCRMP->getRakClient()->GetInterface()->GetStatistics();
}

void HookedRakClientInterface::ApplyNetworkSimulator(double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance)
{
	pCRMP->getRakClient()->GetInterface()->ApplyNetworkSimulator(maxSendBPS, minExtraPing, extraPingVariance);
}

bool HookedRakClientInterface::IsNetworkSimulatorActive(void)
{
	return pCRMP->getRakClient()->GetInterface()->IsNetworkSimulatorActive();
}

PlayerIndex HookedRakClientInterface::GetPlayerIndex(void)
{
	return pCRMP->getRakClient()->GetInterface()->GetPlayerIndex();
}

bool HookedRakClientInterface::RPC_(int* uniqueID, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp, NetworkID networkID)
{

	return pCRMP->getRakClient()->GetInterface()->RPC_(uniqueID, bitStream, priority, reliability, orderingChannel, shiftTimestamp, networkID);
}