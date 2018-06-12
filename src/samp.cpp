/*
			AUTHOR: SlonoBoyko
			LiteHack.Ru
			21.05.2018
*/

#include <main.h>

CCRMP					*pCRMP = NULL;
HMODULE					hThisModule = NULL;
char					szWorkingDirectory[MAX_PATH];
char					szIniFileName[MAX_PATH];

CCRMP::CCRMP() : uiCRMPAddr(reinterpret_cast<uint32_t>(LoadLibrary(CRMP_MODULE_NAME))) 
{
	if (mem::compare((PVOID)(uiCRMPAddr + 0xBABE), hex_to_bin("E9FFFFE8C9D7FFFFC644"), 10))
		mem::copy((PVOID)(uiCRMPAddr + 0x935F0), "\xC3\x90\x90\x90", 4, true, "\x8B\x54\x24\x08");
}

uint8_t CCRMP::Init(void)
{
	if (isInited)	return true;

	if (pInfo		==	nullptr)	pInfo =		*reinterpret_cast <stSAMP **>			(SAMP_INFO_OFFSET);
	if (pInfo		==	nullptr)				return false;

	if (pMisc		==	nullptr)	pMisc =		*reinterpret_cast <stMiscInfo **>		(SAMP_MISC_INFO_OFFSET);
	if (pMisc		==	nullptr)				return false;

	if (pChat		==	nullptr)	pChat =		*reinterpret_cast <stChatInfo **>		(SAMP_CHAT_INFO_OFFSET);
	if (pChat		==	nullptr)				return false;

	if (pInput		==	nullptr)	pInput =	*reinterpret_cast <stInputInfo **>		(SAMP_CHAT_INPUT_INFO_OFFSET);
	if (pInput		==	nullptr)				return false;

	if (pKill		==	nullptr)	pKill =		*reinterpret_cast <stKillInfo **>		(SAMP_KILL_INFO_OFFSET);
	if (pKill		==	nullptr)				return false;

	if (pDialog		==	nullptr)	pDialog =	*reinterpret_cast <stDialogInfo **>		(SAMP_DIALOG_INFO_OFFSET);
	if (pDialog		==	nullptr)				return false;
	
	if (pTextDraw	==	nullptr)	pTextDraw = *reinterpret_cast <stTextdrawInfo **>	(SAMP_TEXTDRAW_INFO_OFFSET);
	if (pTextDraw	==	nullptr)				return false;

	if (pScoreList	==	nullptr)	pScoreList=	*reinterpret_cast <stScoreboardInfo **>	(SAMP_SCOREBOARD_INFO_OFFSET);
	if (pScoreList	==	nullptr)				return false;

	if (pInfo->pRakClientInterface == nullptr) return false;
	pRakClient = new RakClient(pInfo->pRakClientInterface);
	pInfo->pRakClientInterface = new HookedRakClientInterface();

	return isInited = true;
}

/*===================================================================*/
// stSAMP

void stSAMP::restartGame(void)
{
	func::thiscall(SAMP_FUNC_RESTARTGAME, this);
}

void stSAMP::updateScoreBoard(void)
{
	func::thiscall(SAMP_FUNC_UPDATESCOREBOARDDATA, this);
}

void stSAMP::takeScreenShot()
{
	mem::set((PVOID)(SAMP_FUNC_TAKESCREENSHOT), 1, sizeof(int));
}

void stSAMP::disconnect(int reason)
{
	if (pRakClientInterface == nullptr) return;
	return pRakClientInterface->Disconnect(reason);
}

void stSAMP::setPassword(const char *szPassword)
{
	if (pRakClientInterface == nullptr) return;
	return pRakClientInterface->SetPassword(szPassword);
}

void stSAMP::changeServer(const char *szIP, unsigned int iPort)
{
	disconnect(0);
	strcpy(this->szIP, szIP);
	ulPort = iPort;
}

void stSAMP::sendQuery(const char *szIP, unsigned int iPort)
{
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
	SOCKET my_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(szIP);
	addr.sin_port = htons(iPort);

	connect(my_sock, (struct sockaddr *)&addr, sizeof(sockaddr));
	char szPacket[256]; uint8_t aIP[4]; char *szParams = "ircdp";

	if (sscanf(szIP, "%d.%d.%d.%d", &aIP[0], &aIP[1], &aIP[2], &aIP[3])) {
		for (szParams; *szParams != '\0'; szParams++) {
			sprintf(szPacket, "SAMP%c%c%c%c%c%c%c", aIP[0], aIP[1], aIP[2], aIP[3], LOBYTE(iPort), HIBYTE(iPort), *szParams);
			send(my_sock, szPacket, strlen(szPacket), 0);
		}
	}
	closesocket(my_sock);
	WSACleanup();
}

void stSAMP::showGameText(const char *szText, int iTime, signed int iStyle)
{
	if (!szText || strlen(szText) > 64) return;
	return func::stdcall(SAMP_FUNC_GAMETEXT, szText, iTime, iStyle);
}

/*===================================================================*/
// stMiscInfo

void stMiscInfo::toggleSAMPCursor(bool bToggle, eCursorMode iMode)
{
	if (pCRMP->getDialog()->iDialogShowed) return;
	if (pCRMP->getInput()->iInputEnabled) return;
	
	if (bToggle) 
	{
		func::thiscall(SAMP_FUNC_TOGGLECURSOR, this, bToggle ? iMode : 0, !bToggle, 0);
		mem::copy((PVOID)SAMP_FUNC_TOGGLECURSOR, "\xC2\x0C\x00", 3, true, "\x55\x8B\xEC"); // Patch toggle cursor
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	} 
	else 
	{
		mem::copy((PVOID)SAMP_FUNC_TOGGLECURSOR, "\x55\x8B\xEC", 3, true, "\xC2\x0C\x00");
		func::thiscall(SAMP_FUNC_TOGGLECURSOR, this, bToggle ? iMode : 0, !bToggle, 0);
		SetCursor(0);
	}
	//if (!bToggle) func::thiscall(SAMP_FUNC_CURSORUNLOCKACTORCAM, this);
}

/*===================================================================*/
// stDialogInfo

void stDialogInfo::createDialog(int iDialogID, int iType, string title, string text, string button1, string button2)
{
	if (button1.empty() || text.empty() || title.size() > 64) return;
	func::thiscall(SAMP_FUNC_SHOWDIALOG, this, iDialogID, iType, title.data(), text.data(), button1.data(), button2.data(), false);
}

void stDialogInfo::setListBoxItem(WORD wListItem)
{
	if (pListBox == nullptr) return;
	func::thiscall(SAMP_FUNC_DIALOG_LIST_SELECT, pListBox, wListItem);
}

void stDialogInfo::setEditBoxText(string input)
{
	if (!pEditBox || input.empty() || input.size() >= SAMP_MAX_INPUT_LENGTH) return;
	func::thiscall(SAMP_FUNC_EDITBOX_SETTEXT, pEditBox, input.data(), 0);
} 

string stDialogInfo::getEditBoxText()
{
	if (!pEditBox) return NULL;
	return func::thiscall<PCHAR>(SAMP_FUNC_EDITBOX_GETTEXT, pEditBox);
}

void stDialogInfo::closeDialog(BYTE bButtonID, WORD wListItem, string input)
{
	if (wListItem) setListBoxItem(wListItem);
	if (input.size()) setEditBoxText(input);
	func::thiscall(SAMP_FUNC_CLOSE_DIALOG, this, bButtonID);
}

/*===================================================================*/
// stPlayerPool

inline bool stPlayerPool::isBadPlayer(int iPlayerID)
{
	if (iPlayerID == sLocalPlayerID) return true;
	if (iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS) return true;
	if (iIsListed[iPlayerID] != 1 || pRemotePlayer[iPlayerID] == NULL) return true;
	
	return false;
}

void stPlayerPool::deletePlayer(int iPlayerID)
{
	if (isBadPlayer(iPlayerID)) return;
	func::thiscall(SAMP_FUNC_RESETPLAYER, this, static_cast<int16_t>(iPlayerID), 0);
}

void stPlayerPool::resetPlayerPool()
{
	for (int i = 0; i < SAMP_MAX_PLAYERS; i++) 
		deletePlayer(i);
	iLocalPlayerScore = iLocalPlayerPing = sLocalPlayerID = 0;
}

void stPlayerPool::setLocalPlayerName(string name)
{
	if (name.empty() || name.size() > SAMP_MAX_PLAYER_NAME_LENGHT) return;
	func::thiscall(SAMP_FUNC_NAMECHANGE, &pVTBL_txtHandler, name.data(), name.size());
}

void stPlayerPool::setPlayerName(int iPlayerID, string name)
{
	if (iPlayerID == sLocalPlayerID)
		return setLocalPlayerName(name);

	if (isBadPlayer(iPlayerID) || name.empty()) return;
	if (name.size() > SAMP_MAX_PLAYER_NAME_LENGHT) return;
	pRemotePlayer[iPlayerID]->strPlayerName = name;
}

const char *stPlayerPool::getPlayerName(int iPlayerID)
{
	if (iPlayerID == sLocalPlayerID)
		return strLocalPlayerName.data();

	if (isBadPlayer(iPlayerID)) return nullptr;
	if (pRemotePlayer[iPlayerID]->strPlayerName.empty()) 
		return nullptr;

	return pRemotePlayer[iPlayerID]->strPlayerName.data();
}

CVector *stPlayerPool::getPlayerPos(int iPlayerID)
{
	static CVector vecZero = CVector(0.0f, 0.0f, 0.0f);
	if (iPlayerID == sLocalPlayerID && pLocalPlayer->pSAMP_Actor)
		return pLocalPlayer->pSAMP_Actor->getPosition();

	if (isBadPlayer(iPlayerID)) return &vecZero;
	if (pRemotePlayer[iPlayerID]->pPlayerData == NULL) return &vecZero;
	if (pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL) return &vecZero;

	if ((getPlayerState(iPlayerID) == PLAYER_STATE_DRIVER || getPlayerState(iPlayerID) == PLAYER_STATE_PASSENGER))
		return pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->getPosition();

	return pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->getPosition();
}

CVector * stPlayerPool::getBonePos(int iPlayerID, uint8_t bBoneID)
{
	static CVector vecZero = CVector(0.0f, 0.0f, 0.0f);

	if (iPlayerID == sLocalPlayerID && pLocalPlayer->pSAMP_Actor)
		return pLocalPlayer->pSAMP_Actor->getBonePos(bBoneID);

	if (isBadPlayer(iPlayerID)) return &vecZero;
	if (pRemotePlayer[iPlayerID]->pPlayerData == NULL)
		return &vecZero;
	if (pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL)
		return &vecZero;

	return pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->getBonePos(bBoneID);
}

D3DCOLOR stPlayerPool::getPlayerColor(int iPlayerID, DWORD trans)
{
	if (iPlayerID == sLocalPlayerID)
		return getLocalPlayerColor(trans);

	switch (iPlayerID)
	{
	case (SAMP_MAX_PLAYERS + 500): return 0xFF888888;
	case (SAMP_MAX_PLAYERS + 501): return 0xFF0000AA;
	case (SAMP_MAX_PLAYERS + 502): return 0xFF63C0E2;
	default: break;
	}
	if (isBadPlayer(iPlayerID)) return 0xFF999999;
	D3DCOLOR *color_table = reinterpret_cast <PDWORD> (SAMP_COLOR_OFFSET);
	return (color_table[iPlayerID] >> 8) | trans;
}

D3DCOLOR stPlayerPool::getLocalPlayerColor(DWORD trans)
{
	return (reinterpret_cast<PDWORD>(SAMP_COLOR_OFFSET)[sLocalPlayerID] >> 8) | trans;
}

int stPlayerPool::getPlayerCount()
{
	int count = 1;
	for (int i = 0; i < SAMP_MAX_PLAYERS; i++){
		if (iIsListed[i] != 1) continue;
		else count++;
	}
	return count;
}

int stPlayerPool::getPlayerState(int iPlayerID)
{
	if (iPlayerID == sLocalPlayerID)
		return pLocalPlayer->getPlayerState();

	if (isBadPlayer(iPlayerID)) return NULL;
	if (pRemotePlayer[iPlayerID]->pPlayerData == NULL) return NULL;
	
	return pRemotePlayer[iPlayerID]->pPlayerData->bytePlayerState;
}

int stPlayerPool::findTargetPlayer(float fRadius)
{
	int nearest = -1; float dist = fRadius;

	for (int i = 0; i < SAMP_MAX_PLAYERS; i++) 
	{
		if (isBadPlayer(i) || pRemotePlayer[i]->pPlayerData == NULL) continue;
		if (pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL) continue;
		if (pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL) continue;
		
		CVector vecScreen, *vecPosition = getPlayerPos(i);
		if (vecPosition->IsNearZero()) continue;

		CalcScreenCoors(vecPosition, &vecScreen);
		if (vecScreen.fZ < 1.0f) continue;

		uint32_t uiScreenX = pD3DHook->pPresentParam->BackBufferWidth * 0.53f;
		uint32_t uiScreenY = pD3DHook->pPresentParam->BackBufferHeight * 0.4f;

		CVector2D vecLength(uiScreenX - vecScreen.fX, uiScreenY - vecScreen.fY);

		if (vecLength.Length() > dist) continue;
		dist = vecLength.Length();
		nearest = i;
	}

	return nearest;
}

int stPlayerPool::findNearestPlayer(float fRadius)
{
	int nearest = -1; float dist = fRadius;

	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (isBadPlayer(i) || pRemotePlayer[i]->pPlayerData == NULL) continue;
		if (pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL) continue;
		if (pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL) continue;

		CVector *vecPosition = getPlayerPos(i);
		if (vecPosition->IsNearZero()) continue;
		
		CVector vecBetwen(*vecPosition - *pPedSelf->GetPosition());

		if (vecBetwen.Length() > dist) continue;

		nearest = i; 
		dist = vecBetwen.Length();
	}
	return nearest;
}

int	stPlayerPool::findAnyStreemedPlayer()
{
	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (isBadPlayer(i) || pRemotePlayer[i]->pPlayerData == NULL) continue;
		if (pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL) continue;
		if (pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL) continue;

		return i;
	}
	return NULL;
}

struct actor_info *stPlayerPool::getGTAPed(int iPlayerID)
{
	if (iPlayerID == sLocalPlayerID)
		return actor_info_get(ACTOR_SELF);

	if (isBadPlayer(iPlayerID)) return NULL;
	if (pRemotePlayer[iPlayerID]->pPlayerData == NULL) return NULL;
	if (pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL) return NULL;

	return pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;
}

int stPlayerPool::getPlayerID(struct actor_info *pGTAPed)
{
	if (pGTAPed == actor_info_get(ACTOR_SELF))
		return sLocalPlayerID;

	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (isBadPlayer(i) || pRemotePlayer[i]->pPlayerData == NULL) continue;
		if (pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL) continue;
		if (pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == pGTAPed) 
			return i;
	}
	return -1;
}

/*===================================================================*/
// stLocalPlayer

void stLocalPlayer::say(const char *szMsg, ...)
{
	if (!szMsg || strlen(szMsg) >= 128) return;
	
	char temp[128]; va_list ap_list;	
	strnset(temp, 0, 128);
	va_start(ap_list, szMsg);
	vsprintf(temp, szMsg, ap_list);
	va_end(ap_list);

	if (*temp == '/')
		return pCRMP->getInput()->sendClientCommand(temp);
	return func::thiscall(SAMP_FUNC_SENDSAY, this, temp);
}

void stLocalPlayer::sendDeath(void)
{
	func::thiscall(SAMP_FUNC_SENDDEATH, this);
}

void stLocalPlayer::sendSpawn(void)
{
	func::thiscall(SAMP_FUNC_REQUEST_SPAWN, this);
	func::thiscall(SAMP_FUNC_SPAWN, this);
}

void stLocalPlayer::sendSetInterior(uint8_t interiorID)
{
	func::thiscall(SAMP_FUNC_SENDINTERIOR, this, interiorID);
}

void stLocalPlayer::setSpecialAction(uint8_t bAction)
{
	func::thiscall(SAMP_FUNC_SETSPECIALACTION, this, bAction);
}

uint8_t stLocalPlayer::getSpecialAction(void)
{
	return func::thiscall<uint8_t>(SAMP_FUNC_GETSPECIALACTION, this);
}

void stLocalPlayer::toggleControllable(int iControl)
{
	BitStream bsData;
	RPCParameters rpcParams; 
	bsData.Write<int>(iControl);
	bsData.CopyData(&rpcParams.input);
	rpcParams.numberOfBitsOfData = bsData.GetNumberOfBitsUsed();
	func::cdclcall(SAMP_RPCFUNC_TOGGLE_CONTROLLABLE, &rpcParams);
	//((void(__cdecl *)(RPCParameters *))SAMP_RPCFUNC_TOGGLE_CONTROLLABLE)(&rpcParams);
}

int stLocalPlayer::getPlayerState()
{
	if (pSAMP_Actor == NULL)
		return PLAYER_STATE_NONE;
	
	if (iIsWasted) return PLAYER_STATE_WASTED;
	if (pSAMP_Actor->isDriving()) {
		if (pSAMP_Actor->isPassenger())
			return PLAYER_STATE_PASSENGER;
		return PLAYER_STATE_DRIVER;
	}
	if (iIsSpawned && iIsAlive && !iIsSpectating)
		return PLAYER_STATE_ONFOOT;
	
	return PLAYER_STATE_NONE;
}

void stLocalPlayer::sendGiveDamage(uint16_t sPlayer, float fDamage, int iWeapon, int iBody)
{
	func::stdcall(SAMP_FUNC_GIVEDAMAGE, sPlayer, fDamage, iWeapon, iBody);
	//return ((void(__stdcall *)(uint16_t, float, int, int))(SAMP_FUNC_GIVEDAMAGE))(sPlayer, fDamage, iWeapon, iBody);
}

void stLocalPlayer::sendTakeDamage(uint16_t sPlayer, float fDamage, int iWeapon, int iBody)
{
	func::stdcall(SAMP_FUNC_TAKEDAMEGE, sPlayer, fDamage, iWeapon, iBody);
	//return ((void(__stdcall *)(uint16_t, float, int, int))(SAMP_FUNC_TAKEDAMEGE))(sPlayer, fDamage, iWeapon, iBody);
}

/*===================================================================*/
// stSAMPPed

void stSAMPPed::setImmunities(bool bullet, bool flame, bool explosion, bool collision, bool knife)
{
	return func::thiscall(SAMP_FUNC_SETIMMUNITIES, this, bullet, flame, explosion, collision, knife);
}

bool stSAMPPed::isPassenger(void)
{
	return func::thiscall<bool>(SAMP_FUNC_SAMPPEDISPASSENGER, this);
}

uint8_t stSAMPPed::getSeatId(void)
{
	return func::thiscall<uint8_t>(SAMP_FUNC_GETSEATID, this);
}

bool stSAMPPed::isDriving(void)
{
	return func::thiscall<bool>(SAMP_FUNC_ISDRIVING, this);
}

void stSAMPPed::removeFromCarAndPutAt(float fPos[3])
{
	func::thiscall(SAMP_FUNC_REMOVEFROMCAR, this, fPos[0], fPos[1], fPos[2]);
}

void stSAMPPed::putInVehicle(int iVehicleId, uint8_t bSeatID)
{
	stVehiclePool *pVehicles = pCRMP->getVehicles();
	if (!pVehicles || pVehicles->isBadVehicle(iVehicleId)) return;
	int iGtaID = pVehicles->pSAMP_Vehicle[iVehicleId]->dwScriptID;
	
	func::thiscall(SAMP_FUNC_PUTINCAR, this, iGtaID, bSeatID);
}

void stSAMPPed::setRotation(float fAngle)
{
	func::thiscall(SAMP_FUNC_SETROTATION, this, fAngle);
}

CVector *stSAMPPed::getPosition()
{
	static CVector vecZero = CVector(0.0f, 0.0f, 0.0f);
	if (isBadPtr_GTA_pPed(pGTA_Ped)) 
		return &vecZero;

	return &pGTA_Ped->base.m_CMatrix->vPos;
} 

CVector *stSAMPPed::getBonePos(uint8_t bBoneID)
{
	CVector vecPosition(0.0f, 0.0f, 0.0f);
	if (isBadPtr_GTA_pPed(pGTA_Ped)) 
		return &vecPosition;

	func::thiscall(SAMP_FUNC_GETBONEPOS, this, bBoneID, &vecPosition);

	return &vecPosition;
}

/*===================================================================*/
// stVehiclePool

inline bool stVehiclePool::isBadVehicle(int iVehicleID)
{
	if (iVehicleID < 0 || iVehicleID > SAMP_MAX_VEHICLES)  return true;
	if (!iInitiated || iIsListed[iVehicleID] != 1) return true;
	if (pSAMP_Vehicle[iVehicleID] == NULL || pGTA_Vehicle[iVehicleID] == NULL) 
		return true;

	return false;
}

CVector *stVehiclePool::getVehiclePos(int iVehicleID)
{
	static CVector vecZero = CVector(0.0f, 0.0f, 0.0f);
	if (isBadVehicle(iVehicleID)) 
		return &vecZero;

	return pSAMP_Vehicle[iVehicleID]->getPosition();
}

void stVehiclePool::sendSCMEvent(int iEvent, int sampVehId, int iParam1, int iParam2)
{
	func::cdclcall(SAMP_FUNC_SENDSCMEVENT, iEvent, sampVehId, iParam1, iParam2);
}

int stVehiclePool::getVehiclesCount()
{
	if (!iInitiated) return NULL;

	int count = 0;
	for (int i = 0; i < SAMP_MAX_VEHICLES; i++) {
		if (isBadVehicle(i)) continue;
		else count++;
	}
	return count;
}

int stVehiclePool::getSAMPVehicleID(struct vehicle_info *pVehicle)
{
	for (int i = 0; i < SAMP_MAX_VEHICLES; i++)
	{
		if (isBadVehicle(i)) continue;
		if (pGTA_Vehicle[i] == pVehicle) 
			return i;
	} 
	return NULL;
}

struct vehicle_info *stVehiclePool::getGTAVehicle(int iVehicleID)
{
	if (isBadVehicle(iVehicleID)) return nullptr;
	return pGTA_Vehicle[iVehicleID];
}

int stVehiclePool::findNearestVehicle(float fRadius)
{
	int nearest = -1; float dist = fRadius;

	for (int i = 0; i < SAMP_MAX_VEHICLES; i++)
	{
		if (isBadVehicle(i) || pSAMP_Vehicle[i]->pGTA_Vehicle == NULL) continue;
		if (pSAMP_Vehicle[i]->isSelfVehicle()) continue;

		struct vehicle_info *vinfo = getGTAVehicle(i);
		if (isBadPtr_GTA_pVehicle(vinfo)) continue;

		CVector vecBetwen(vinfo->base.m_CMatrix->vPos - *pPedSelf->GetPosition());

		if (vecBetwen.Length() > dist) continue;

		dist = vecBetwen.Length();
		nearest = i;
	}
	return nearest;
}

int stVehiclePool::findNearestEmptyVehicle(float fRadius)
{
	int nearest = -1; float dist = 1000.0f;

	for (int i = 0; i < SAMP_MAX_VEHICLES; i++)
	{
		if (isBadVehicle(i) || pSAMP_Vehicle[i]->pGTA_Vehicle == NULL) continue;
		if (pCRMP->getPlayers()->pLocalPlayer->sCurrentVehicleID == i) continue;

		struct vehicle_info *vinfo = getGTAVehicle(i);
		if (isBadPtr_GTA_pVehicle(vinfo) || vinfo->driver != NULL) continue;

		CVector vecBetwen(vinfo->base.m_CMatrix->vPos - *pPedSelf->GetPosition());

		if (vecBetwen.Length() > dist) continue;

		nearest = i;
		dist = vecBetwen.Length();
	}
	
	return nearest;
}

/*===================================================================*/
// stSAMPVehicle

void stSAMPVehicle::setColor(uint8_t color_0, uint8_t color_1)
{
	func::thiscall(SAMP_FUNC_RECOLORVEHICLE, this, color_0, color_1);
}

void stSAMPVehicle::setDoorState( bool state )
{
	func::thiscall(SAMP_FUNC_OPENCLOSEVEHICLE, this, state);
}

bool stSAMPVehicle::isSelfVehicle( void )
{
	return func::thiscall<bool>(SAMP_FUNC_ISVEHICLESELF, this);
}

CVector *stSAMPVehicle::getPosition( void )
{
	static CVector vecZero = CVector(0.0f, 0.0f, 0.0f);
	if (isBadPtr_GTA_pVehicle(pGTA_Vehicle)) 
		return &vecZero;

	return &pGTA_Vehicle->base.m_CMatrix->vPos;
}

/*===================================================================*/
// stChatInfo

void stChatInfo::addMessageToChat(D3DCOLOR dwColor, string &msg, int type, D3DCOLOR dwPrefixColor, string prefix)
{
	if (msg.empty() || msg.length() > SAMP_MAX_CHAT_LENGTH) return;
	func::thiscall(SAMP_FUNC_ADDTOCHATWND, this, type, msg.c_str(), prefix.c_str(), dwColor, dwPrefixColor);
}

void stChatInfo::addMessageToChat(D3DCOLOR dwColor, const char *msg, ...)
{
	if (!msg || strlen(msg) > SAMP_MAX_CHAT_LENGTH) return;

	char *ap_list, temp[0x90];
	strnset(temp, NULL, 0x90);

	va_start(ap_list, msg);
	vsprintf(temp, msg, ap_list);
	va_end(ap_list);

	return addMessageToChat(dwColor, string(temp));
}

void stChatInfo::deleteMessage(int iStringNum)
{
	if (iStringNum < 0 || iStringNum > 99) return;

	if (strlen(chatEntry[iStringNum].szText)) {
		mem::set(&chatEntry[iStringNum], 0, sizeof(stChatEntry));
		for (int i = iStringNum; i > 0; i--) {
			if (!strlen(chatEntry[i - 1].szText)) {
				mem::set(&chatEntry[i], 0, sizeof(stChatEntry));
				break;
			} mem::copy(&chatEntry[i], &chatEntry[i-1], sizeof(stChatEntry));
		}
	} iRedraw = 1;
}

void stChatInfo::clearChat(void)
{
	iRedraw = mem::set(chatEntry, 0, sizeof(stChatEntry) * 100) != nullptr;
}

/*===================================================================*/
// stInputInfo

void stInputInfo::addClientCommand(string cmd, CMDPROC func)
{
	if (iCMDCount > SAMP_MAX_CLIENTCMDS) return;
	if (!func || cmd.empty() || cmd.length() > SAMP_MAX_CMD_LENGTH) return;

	func::thiscall(SAMP_FUNC_ADDCLIENTCMD, this, cmd.c_str(), func);
}

void stInputInfo::sendClientCommand(string cmd)
{
	CMDPROC pCmdFunction = nullptr;
	if (cmd.empty() || cmd.length() > SAMP_MAX_CMD_LENGTH) return;
	if (pCmdFunction = pCRMP->getInput()->getCmdFunc(&cmd[1]))
		return pCmdFunction(&cmd[1]);

	func::stdcall(SAMP_FUNC_SENDCMD, cmd.c_str());
}

CMDPROC stInputInfo::getCmdFunc(string cmd)
{
	if (cmd.empty() || cmd.length() > SAMP_MAX_CMD_LENGTH) return NULL;
	return func::thiscall<CMDPROC>(SAMP_FUNC_GETCMDPROC, this, cmd.c_str());
}

void stInputInfo::disableInput()
{
	func::thiscall(SAMP_FUNC_DISABLE_INPUT, this);
}

void stInputInfo::enableInput()
{
	func::thiscall(SAMP_FUNC_ENABLE_INPUT, this);
}

string stInputInfo::getInputText()
{
	if (pEditBox == nullptr) return NULL;
	return func::thiscall<PCHAR>(SAMP_FUNC_EDITBOX_GETTEXT, pEditBox);
}

void stScoreboardInfo::disableScoreboard(void)
{
	func::thiscall(SAMP_FUNC_DISABLE_SCOREBOARD, this, true);
}

void stScoreboardInfo::enableScoreboard(void)
{
	func::thiscall(SAMP_FUNC_ENABLE_SCOREBOARD, this);
}

/*
				CCRMP Class End
*/

void sampSyncDisable(uint8_t id, eNetPatchType type, bool state)
{
	if (id < 0 || id > RAKNET_MAX_PACKET) return;
	for (size_t i = 0; i < RAKNET_MAX_PACKET; i++) {
		if (ini.patch[i].type == type && ini.patch[i].id == id) {
			ini.patch[i].enabled = state;
			break;
		}
	}
}

