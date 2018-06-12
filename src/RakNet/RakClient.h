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

#pragma once

#define RAKNET_MAX_PACKET	256

typedef unsigned int RakNetTime;
typedef long long RakNetTimeNS;
typedef unsigned short PlayerIndex;

enum RPCEnumeration
{
	RPC_ServerCommand = 6,
	RPC_SetInteriorId = 7,
	RPC_MapMarker = 8,
	RPC_VehicleDestroyed = 9,
	RPC_ServerJoin = 10,
	RPC_ServerQuit = 11,
	RPC_InitGame = 12,
	RPC_ConnectionRejected = 13,
	RPC_ClientMessage = 14,
	RPC_SetWorldTime = 15,
	RPC_SetPlayerWeather = 19,
	RPC_SetPlayerSkin = 20,
	RPC_SetPlayerName = 21,
	RPC_SetPlayerPos = 22,
	RPC_SetPlayerPosFindZ = 23,
	RPC_SetPlayerHealth = 24,
	RPC_PutPlayerInVehicle = 25,
	RPC_RemovePlayerFromVehicle = 26,
	RPC_SetPlayerColor = 27,
	RPC_DisplayGameText = 28,
	RPC_ForceSpawnSelection = 29,
	RPC_AttachObjectToPlayer = 30,
	RPC_InitMenu = 31,
	RPC_ShowMenu = 32,
	RPC_HideMenu = 33,
	RPC_SetPlayerWantedLevel = 34,
	RPC_ShowTextDraw = 35,
	RPC_HideTextDraw = 36,
	RPC_EnableStuntBonus = 37,
	RPC_EditTextDraw = 38,
	RPC_AddGangZone = 39,
	RPC_PlayCrimeReportForPlayer = 43,
	RPC_SetPlayerAttachedObject = 44,
	RPC_PlayAudioStream = 45,
	RPC_StopAudioStreamForPlayer = 46,
	RPC_RemoveBuildingForPlayer = 47,
	RPC_CreateObject = 48,
	RPC_SetObjectPos = 49,
	RPC_SetObjectRotation = 50,
	RPC_DestroyObject = 51,
	RPC_CreateExplosion = 54,
	RPC_ShowNameTagForPlayer = 55,
	RPC_AttachCameraToObject = 56,
	RPC_ClickTextDraw = 58,
	RPC_GiveTakeDamage = 60,
	RPC_EditAttachedObject = 61,
	RPC_EditObject = 62,
	RPC_SelectObject = 63,
	RPC_CancelEdit = 64,
	RPC_ConnectionPong = 65,
	RPC_SetPlayerTime = 66,
	RPC_TogglePlayerClock = 67,
	RPC_WorldPlayerAdd = 69,
	RPC_SetShopName = 70,
	RPC_SetPlayerSkillLevel = 71,
	RPC_SetDrunkLevel = 72,
	RPC_SetChatBubble = 75,
	RPC_ShowDialog = 77,
	RPC_DialogResponse = 78,
	RPC_ClickPlayer = 79,
	RPC_VehicleParams = 80,
	RPC_ClientJoin = 81,
	RPC_RemoveGangZone = 82,
	RPC_FlashGangZone = 83,
	RPC_StopFlashGangZone = 84,
	RPC_ApplyAnimation = 85,
	RPC_ClearAnimations = 86,
	RPC_SetSpecialAction = 87,
	RPC_SetFightingStyle = 88,
	RPC_SetPlayerVelocity = 89,
	RPC_SetVehicleVelocity = 90,
	RPC_MoveObject = 94,
	RPC_StopObject = 95,
	RPC_TogglePlayerSpectating = 97,
	RPC_SetPlayerSpectating = 98,
	RPC_PlayerSpectatePlayer = 99,
	RPC_PlayerSpectateVehicle = 100,
	RPC_RequestClass = 101,
	RPC_RequestSpawn = 102,
	RPC_EnterVehicle = 103,
	RPC_ExitVehicle = 104,
	RPC_UpdateScoresPingsIPs = 105,
	RPC_SetPlayerInterior = 106,
	RPC_SetCameraPos = 107,
	RPC_SetCameraLookAt = 108,
	RPC_SetVehiclePos = 109,
	RPC_SetVehicleZAngle = 110,
	RPC_SetVehicleParamsForPlayer = 111,
	RPC_SetCameraBehindPlayer = 112,
	RPC_TogglePlayerControllable = 113,
	RPC_PlaySound = 114,
	RPC_SetPlayerWorldBounds = 115,
	RPC_GivePlayerMoney = 116,
	RPC_SetPlayerFacingAngle = 117,
	RPC_ResetMoney = 118,
	RPC_ResetPlayerWeapons = 119,
	RPC_GivePlayerWeapon = 120,

	RPC_LinkVehicleToInterior = 122,
	RPC_SetPlayerArmour = 123,
	RPC_SetSpawnInfo = 125,
	RPC_SetPlayerTeam = 126,
	RPC_WorldPlayerRemove = 127,
	RPC_WorldVehicleAdd = 128,
	RPC_WorldVehicleRemove = 129,
	RPC_WorldPlayerDeath = 130,
	RPC_DamageVehicle = 131,
	RPC_SetPlayerCheckpoint = 132,
	RPC_DisablePlayerCheckpoint = 133,
	RPC_SetPlayerRaceCheckpoint = 134,
	RPC_DisablePlayerRaceCheckpoint = 135,
	RPC_GameModeRestart = 136,
	RPC_Chat = 138,
	RPC_ScmEvent = 140,
	RPC_PickedUpPickup = 142,
	RPC_MenuSelect = 143,
	RPC_MenuQuit = 144,
	RPC_Spawn = 150,
	RPC_Death = 151,
	RPC_NPCJoin = 152,
	RPC_DeathMessage = 153,
	RPC_SetMapIcon = 154,
	RPC_DisableMapIcon = 155,
	RPC_SetGravity = 157,
	RPC_SetVehicleHealth = 158,
	RPC_AttachTrailerToVehicle = 159,
	RPC_DetachTrailerFromVehicle = 160,
	RPC_AddVehicleComponent = 161



};

enum PacketEnumeration
{
	ID_INTERNAL_PING = 4,
	ID_PING,
	ID_PING_OPEN_CONNECTIONS,
	ID_CONNECTED_PONG,
	ID_PAD1,
	ID_PAD11,
	ID_PAD12,
	ID_REQUEST_STATIC_DATA,
	ID_CONNECTION_REQUEST,
	ID_PAD2,
	ID_SECURED_CONNECTION_RESPONSE,
	ID_SECURED_CONNECTION_CONFIRMATION,
	ID_RPC_MAPPING,
	ID_PAD3,
	ID_PAD5,
	ID_PAD6,
	ID_DETECT_LOST_CONNECTIONS,
	ID_OPEN_CONNECTION_REQUEST,
	ID_OPEN_CONNECTION_REPLY,
	ID_PAD4,
	ID_RPC,
	ID_RPC_REPLY,
	ID_BROADCAST_PINGS,
	ID_SET_RANDOM_NUMBER_SEED,
	ID_CONNECTION_REQUEST_ACCEPTED,
	ID_CONNECTION_ATTEMPT_FAILED,
	ID_NEW_INCOMING_CONNECTION,
	ID_NO_FREE_INCOMING_CONNECTIONS,
	ID_DISCONNECTION_NOTIFICATION,
	ID_CONNECTION_LOST,
	ID_RSA_PUBLIC_KEY_MISMATCH,
	ID_CONNECTION_BANNED,
	ID_INVALID_PASSWORD,
	ID_MODIFIED_PACKET,
	ID_TIMESTAMP,
	ID_PONG,
	ID_RECEIVED_STATIC_DATA,
	ID_REMOTE_DISCONNECTION_NOTIFICATION,
	ID_REMOTE_CONNECTION_LOST,
	ID_REMOTE_NEW_INCOMING_CONNECTION,
	ID_REMOTE_EXISTING_CONNECTION,
	ID_REMOTE_STATIC_DATA,
	// ...
	ID_ADVERTISE_SYSTEM = 51,

	ID_UNOCCUPIED_SYNC = 110,
	ID_MARKERS_SYNC,
	ID_WEAPONS_UPDATE,
	ID_SPECTATOR_SYNC,
	ID_TRAILER_SYNC,
	ID_PASSENGER_SYNC,
	ID_PLAYER_SYNC,
	ID_AIM_SYNC,
	ID_VEHICLE_SYNC,
	ID_RCON_COMMAND,
	ID_RCON_RESPONCE,
	ID_STATS_UPDATE,
	

};

enum PacketPriority
{
	SYSTEM_PRIORITY, 
	HIGH_PRIORITY, 
	MEDIUM_PRIORITY, 
	LOW_PRIORITY,
	NUMBER_OF_PRIORITIES
};

enum PacketReliability
{
	UNRELIABLE,
	UNRELIABLE_SEQUENCED,
	RELIABLE,
	RELIABLE_ORDERED,
	RELIABLE_SEQUENCED
};

#pragma pack(push, 1)

struct PlayerID
{
	unsigned int binaryAddress;
	unsigned short port;

	PlayerID& operator = (const PlayerID& input){
		binaryAddress = input.binaryAddress;
		port = input.port;
		return *this;
	}
};

struct NetworkID
{
	static bool peerToPeerMode;
	PlayerID playerId;
	unsigned short localSystemId;
};

struct Packet
{
	PlayerIndex playerIndex;
	PlayerID playerId;
	unsigned int length;
	unsigned int bitSize;
	unsigned char* data;
	bool deleteData;
};

struct RPCParameters
{
	unsigned char *input;
	unsigned int numberOfBitsOfData;
	PlayerID sender;
	void *recipient;
	BitStream *replyToSender;
};

struct RPCNode
{
	char *uniqueIdentifier;
	union{
		void(*staticFunctionPointer) (RPCParameters *rpcParms);
		void *functionPointer;
	};
};

struct RakNetStatisticsStruct
{
	unsigned messageSendBuffer[NUMBER_OF_PRIORITIES];
	unsigned messagesSent[NUMBER_OF_PRIORITIES];
	unsigned messageDataBitsSent[NUMBER_OF_PRIORITIES];
	unsigned messageTotalBitsSent[NUMBER_OF_PRIORITIES];
	unsigned packetsContainingOnlyAcknowlegements;
	unsigned acknowlegementsSent;
	unsigned acknowlegementsPending;
	unsigned acknowlegementBitsSent;
	unsigned packetsContainingOnlyAcknowlegementsAndResends;
	unsigned messageResends;
	unsigned messageDataBitsResent;
	unsigned messagesTotalBitsResent;
	unsigned messagesOnResendQueue;
	unsigned numberOfUnsplitMessages;
	unsigned numberOfSplitMessages;
	unsigned totalSplits;
	unsigned packetsSent;
	unsigned encryptionBitsSent;
	unsigned totalBitsSent;
	unsigned sequencedMessagesOutOfOrder;
	unsigned sequencedMessagesInOrder;
	unsigned orderedMessagesOutOfOrder;
	unsigned orderedMessagesInOrder;
	unsigned packetsReceived;
	unsigned packetsWithBadCRCReceived;
	unsigned bitsReceived;
	unsigned bitsWithBadCRCReceived;
	unsigned acknowlegementsReceived;
	unsigned duplicateAcknowlegementsReceived;
	unsigned messagesReceived;
	unsigned invalidMessagesReceived;
	unsigned duplicateMessagesReceived;
	unsigned messagesWaitingForReassembly;
	unsigned internalOutputQueueSize;
	double bitsPerSecond;
	RakNetTime connectionStartTime;
};
#pragma pack(pop)

class RakClientInterface
{
public:
	virtual ~RakClientInterface() {}
	virtual bool Connect(const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer) = 0;
	virtual void Disconnect(unsigned int blockDuration, unsigned char orderingChannel = 0) = 0;
	virtual void InitializeSecurity(const char *privKeyP, const char *privKeyQ) = 0;
	virtual void SetPassword(const char *_password) = 0;
	virtual bool HasPassword(void) const = 0;
	virtual bool Send(const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel) = 0;
	virtual bool Send(BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel) = 0;
	virtual Packet* Receive(void) = 0;
	virtual void DeallocatePacket(Packet *packet) = 0;
	virtual void PingServer(void) = 0;
	virtual void PingServer(const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections) = 0;
	virtual int GetAveragePing(void) = 0;
	virtual int GetLastPing(void) const = 0;
	virtual int GetLowestPing(void) const = 0;
	virtual int GetPlayerPing(const PlayerID playerId) = 0;
	virtual void StartOccasionalPing(void) = 0;
	virtual void StopOccasionalPing(void) = 0;
	virtual bool IsConnected(void) const = 0;
	virtual unsigned int GetSynchronizedRandomInteger(void) const = 0;
	virtual bool GenerateCompressionLayer(unsigned int inputFrequencyTable[256], bool inputLayer) = 0;
	virtual bool DeleteCompressionLayer(bool inputLayer) = 0;
	virtual void RegisterAsRemoteProcedureCall(int* uniqueID, void(*functionPointer) (RPCParameters *rpcParms)) = 0;
	virtual void RegisterClassMemberRPC(int* uniqueID, void *functionPointer) = 0;
	virtual void UnregisterAsRemoteProcedureCall(int* uniqueID) = 0;
	virtual bool RPC(int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp) = 0;
	virtual bool RPC(int* uniqueID, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp) = 0;
	virtual bool RPC_(int* uniqueID, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp, NetworkID networkID) = 0;
	virtual void SetTrackFrequencyTable(bool b) = 0;
	virtual bool GetSendFrequencyTable(unsigned int outputFrequencyTable[256]) = 0;
	virtual float GetCompressionRatio(void) const = 0;
	virtual float GetDecompressionRatio(void) const = 0;
	virtual void AttachPlugin(void *messageHandler) = 0;
	virtual void DetachPlugin(void *messageHandler) = 0;
	virtual BitStream * GetStaticServerData(void) = 0;
	virtual void SetStaticServerData(const char *data, const int length) = 0;
	virtual BitStream * GetStaticClientData(const PlayerID playerId) = 0;
	virtual void SetStaticClientData(const PlayerID playerId, const char *data, const int length) = 0;
	virtual void SendStaticClientDataToServer(void) = 0;
	virtual PlayerID GetServerID(void) const = 0;
	virtual PlayerID GetPlayerID(void) const = 0;
	virtual PlayerID GetInternalID(void) const = 0;
	virtual const char* PlayerIDToDottedIP(const PlayerID playerId) const = 0;
	virtual void PushBackPacket(Packet *packet, bool pushAtHead) = 0;
	virtual void SetRouterInterface(void *routerInterface) = 0;
	virtual void RemoveRouterInterface(void *routerInterface) = 0;
	virtual void SetTimeoutTime(RakNetTime timeMS) = 0;
	virtual bool SetMTUSize(int size) = 0;
	virtual int GetMTUSize(void) const = 0;
	virtual void AllowConnectionResponseIPMigration(bool allow) = 0;
	virtual void AdvertiseSystem(const char *host, unsigned short remotePort, const char *data, int dataLength) = 0;
	virtual RakNetStatisticsStruct * const GetStatistics(void) = 0;
	virtual void ApplyNetworkSimulator(double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance) = 0;
	virtual bool IsNetworkSimulatorActive(void) = 0;
	virtual PlayerIndex GetPlayerIndex(void) = 0;
};

class RakClient
{
private:
	RakClientInterface *pRakClient = nullptr;
public:
	RakClient(RakClientInterface *pRakClientInterface) : pRakClient(pRakClientInterface) {};

	bool RPC(int rpcId, BitStream *bitStream, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED, char orderingChannel = 0, bool shiftTimestamp = false);
	bool Send(BitStream *bitStream, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = UNRELIABLE_SEQUENCED, char orderingChannel = 0);

	RakClientInterface	*GetInterface(void) { return pRakClient; };

//	RPC 
	void SendDeath(uint16_t killerId, uint8_t reason);
	void RequestClass(int classId);
	void SendSCMEvent(int eventId, int vehicleID, int param1, int param2);
	void SendSpawn(void);
	void SendPickUp(int pickupId);
	void SendDialogResponse(WORD wDialogID, BYTE bButtonID, WORD wListBoxItem, const char *szInputResp);
	void SendGiveDamage(int iPlayerID, float fDamage, int iWeaponID, int iBodyPart);
	void SendEnterVehicle(WORD wVehicleID, uint8_t bIsPassenger);
	void SendClickTextDraw(int iTextId);
	void SendVehicleDestroyed(int iVehicleId);

//	PACKETS
	void SendFakeOnfootSyncData(float fPos[3], float fHealth, float fSpeed[3]);
	void SendFakeDriverSyncData(int iVehicleID, float fVehiclePos[3], float fVehicleHealth, float fMoveSpeed[3]);
	void SendFakeAimSyncData(float vecAimPos[3], float vecAimf1[3], float fAimZ, BYTE byteCamMode, BYTE byteWeaponState);
	void SendFakeTrailerSyncData(int iTrailerID, float fPos[3], float fSpeed[3]);
};