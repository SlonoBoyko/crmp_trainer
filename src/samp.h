/*
			AUTHOR: SlonoBoyko
			LiteHack.Ru
			21.05.2018
*/

#pragma once

#define samp_base									pCRMP->getBase()

#define SAMP_CHAT_INFO_OFFSET						(samp_base + 0x20DFD8)
#define SAMP_CHAT_INPUT_INFO_OFFSET					(samp_base + 0x20DFDC)
#define SAMP_KILL_INFO_OFFSET						(samp_base + 0x20DFE0)
#define SAMP_INFO_OFFSET							(samp_base + 0x20DFEC)
#define SAMP_MISC_INFO_OFFSET						(samp_base + 0x20DFFC)
#define SAMP_DIALOG_INFO_OFFSET						(samp_base + 0x20DFAC)
#define SAMP_TEXTDRAW_INFO_OFFSET					(samp_base + 0x20DFC0)
#define SAMP_SCOREBOARD_INFO_OFFSET					(samp_base + 0x20DFA8)

#define SAMP_D3DDEVICE_INFO_OFFSET					(samp_base + 0x20E000)
#define SAMP_DIRECT3DDEVICE9						(samp_base + 0x0D15B0)

#define SAMP_DRAWING_DISTANCE						(samp_base + 0x0C9CA8)
#define SAMP_COLOR_OFFSET							(samp_base + 0x20AE78)
#define SAMP_DRAWTEXTLABELS							(samp_base + 0x06BF37)
#define SAMP_SETENGINESTATE							(samp_base + 0x0A7DD0)
#define SAMP_DISABLE_NAMETAGS						(samp_base + 0x06B840)
#define SAMP_DISABLE_NAMETAGS_HP					(samp_base + 0x06A7E0)
#define SAMP_ONFOOTSENDRATE							(samp_base + 0x0E2098)
#define SAMP_INCARSENDRATE							(samp_base + 0x0E209C)
#define SAMP_AIMSENDRATE							(samp_base + 0x0E20A0)
#define SAMP_DISABLE_SCREENSHOT						(samp_base + 0x05AA91)
#define SAMP_OVERFLOWPOOL_BILDING_FIX				(samp_base + 0x130F58)
#define SAMP_STATIC_INPUT_STRING					(samp_base + 0x122EF8)

#define SAMP_FUNC_ADDTOCHATWND						(samp_base + 0x607D0)
#define SAMP_FUNC_SHOWDIALOG						(samp_base + 0x668C0)
#define SAMP_FUNC_SPAWN								(samp_base + 0x034C0)
#define SAMP_FUNC_REQUEST_SPAWN						(samp_base + 0x03420)
#define SAMP_FUNC_REQUEST_CLASS						(samp_base + 0x048C0)
#define SAMP_FUNC_SETSPECIALACTION					(samp_base + 0x02B10)
#define SAMP_FUNC_SENDSAY							(samp_base + 0x04A10)
#define SAMP_FUNC_SENDCMD							(samp_base + 0x62070)
#define SAMP_FUNC_GIVEDAMAGE						(samp_base + 0x057C0)
#define SAMP_FUNC_TAKEDAMEGE						(samp_base + 0x058D0)
#define SAMP_FUNC_ADDCLIENTCMD						(samp_base + 0x61EE0)
#define SAMP_FUNC_NAMECHANGE						(samp_base + 0x09930)
#define SAMP_FUNC_RESTARTGAME						(samp_base + 0x08800)
#define SAMP_FUNC_TOGGLECURSOR						(samp_base + 0x95CD0)
#define SAMP_FUNC_CURSORLOCKTOCAM					(samp_base + 0x95B60)
#define SAMP_FUNC_CURSORUNLOCKACTORCAM				(samp_base + 0x95BB0)
#define SAMP_FUNC_UPDATESCOREBOARDDATA				(samp_base + 0x076C0)
#define SAMP_FUNC_SENDINTERIOR						(samp_base + 0x04960)
#define SAMP_FUNC_GAMETEXT							(samp_base + 0x96230)
#define SAMP_FUNC_TAKESCREENSHOT					(samp_base + 0x10F71C)
#define SAMP_FUNC_CLOSE_DIALOG						(samp_base + 0x66C50)
#define SAMP_FUNC_EDITBOX_GETTEXT					(samp_base + 0x7BB00)
#define SAMP_FUNC_EDITBOX_SETTEXT					(samp_base + 0x7BA30)
#define SAMP_FUNC_DIALOG_LIST_SELECT				(samp_base + 0x80E10)
#define SAMP_FUNC_SENDDEATH							(samp_base + 0x04800)
#define SAMP_FUNC_SENDSCMEVENT						(samp_base + 0x018A0)
#define SAMP_FUNC_GETSPECIALACTION					(samp_base + 0x02D50)
#define SAMP_FUNC_SAMPPEDISPASSENGER				(samp_base + 0x9E860)
#define SAMP_FUNC_OPENCLOSEVEHICLE					(samp_base + 0xA6C80)
#define SAMP_FUNC_SETIMMUNITIES						(samp_base + 0x9E5B0)
#define SAMP_FUNC_RESETPLAYER						(samp_base + 0x0E2D0)
#define SAMP_FUNC_CREATETEXTDRAW					(samp_base + 0x17C60)
#define SAMP_FUNC_RECOLORVEHICLE					(samp_base + 0xA6760)
#define SAMP_FUNC_RESETPLAYERPOOL					(samp_base + 0x0E350)
#define SAMP_FUNC_DISABLE_INPUT						(samp_base + 0x61CF0)
#define SAMP_FUNC_ENABLE_INPUT						(samp_base + 0x61C10)
#define SAMP_FUNC_GETCMDPROC						(samp_base + 0x61E80)
#define SAMP_FUNC_PUTINCAR							(samp_base + 0x9EB00)
#define SAMP_FUNC_SETROTATION						(samp_base + 0x9E7B0)
#define SAMP_FUNC_REMOVEFROMCAR						(samp_base + 0x9EDD0)
#define SAMP_FUNC_ISDRIVING							(samp_base + 0x9E710)
#define SAMP_FUNC_GETSEATID							(samp_base + 0x9EA70)
#define SAMP_FUNC_ISVEHICLESELF						(samp_base + 0xA6870)
#define SAMP_FUNC_GETBONEPOS						(samp_base + 0xA0AE0)
#define SAMP_FUNC_ENABLE_SCOREBOARD					(samp_base + 0x66210)
#define SAMP_FUNC_DISABLE_SCOREBOARD				(samp_base + 0x658E0)

#define SAMP_RPCFUNC_TOGGLE_CONTROLLABLE			(samp_base + 0x13E90)

enum eNetPatchType
{
	INCOMING_RPC = 1,
	OUTCOMING_RPC,
	INCOMING_PACKET,
	OUTCOMING_PACKET,
};

enum eDialogStyle
{
	DIALOG_STYLE_MSGBOX,
	DIALOG_STYLE_INPUT,
	DIALOG_STYLE_LIST,
	DIALOG_STYLE_PASSWORD,
};

enum eCursorMode
{
	CURSORMODE_DISABLE,
	CURSORMODE_NO_LOCKING,			// Show cursor witchout locking
	CURSORMODE_LOCK_KEYBOARD,		// Show cursor and locking camera rotation and keyboard
	CURSORMODE_LOCK_MOUSE,			// Show cursor and locking camera rotation and mouse buttons
	CURSORMODE_LOCK_ONLY_CAMERA		// Lock camera rotation, but cursor not showing
};

enum eLimits
{
	SAMP_MAX_PLAYERS = 502,
	SAMP_MAX_VEHICLES = 2000,
	SAMP_MAX_PICKUPS = 4096,
	SAMP_MAX_OBJECTS = 1000,
	SAMP_MAX_GANGZONES = 1024,
	SAMP_MAX_3DTEXTS = 2048,
	SAMP_MAX_TEXTDRAWS = 2048,
	SAMP_MAX_PLAYERTEXTDRAWS = 256,
	SAMP_MAX_MENUS = 128,
	SAMP_MAX_DIALOGS = 65535,
	SAMP_MAX_CLIENTCMDS = 144,
	SAMP_MAX_CMD_LENGTH = 32,
	SAMP_MAX_PLAYER_NAME_LENGHT = 24,
	SAMP_MAX_INPUT_LENGTH = 129,
	SAMP_MAX_CHAT_LENGTH = 144
};

enum eChatMessageType
{
	CHAT_TYPE_NONE = 0,
	CHAT_TYPE_CHAT = 9,
	CHAT_TYPE_INFO = 11,
	CHAT_TYPE_DEBUG = 15
};

enum eChatDisplayMode
{
	CHAT_WINDOW_MODE_OFF = 0,
	CHAT_WINDOW_MODE_LIGHT = 1,
	CHAT_WINDOW_MODE_FULL = 2
};

enum eGamestate
{
	GAMESTATE_WAIT_CONNECT = 0x1A,
	GAMESTATE_CONNECTING = 0x1C,
	GAMESTATE_AWAIT_JOIN = 0x1E,
	GAMESTATE_CONNECTED = 0x1D,
	GAMESTATE_RESTARTING = 0x21
};

enum eSampWeaponState
{
	WS_NO_BULLETS = 0,
	WS_LAST_BULLET = 1,
	WS_MORE_BULLETS = 2,
	WS_RELOADING = 3,
};

enum ePlayerState
{
	PLAYER_STATE_NONE = 0,
	PLAYER_STATE_ONFOOT = 65,
	PLAYER_STATE_PASSENGER,
	PLAYER_STATE_DRIVER,
	PLAYER_STATE_WASTED = 144,
	PLAYER_STATE_SPAWNED
};

enum eMarkersMode
{
	PLAYER_MARKERS_MODE_OFF,
	PLAYER_MARKERS_MODE_GLOBAL,
	PLAYER_MARKERS_MODE_STREAMED,
};

enum eSCMEvents
{
	EVENT_TYPE_PAINTJOB = 1,
	EVENT_TYPE_CARCOMPONENT,
	EVENT_TYPE_CARCOLOR,
	EVENT_ENTEREXIT_MODSHOP
};

enum eSpecialAction
{
	SPECIAL_ACTION_NONE,
	SPECIAL_ACTION_DUCK,
	SPECIAL_ACTION_USEJETPACK,
	SPECIAL_ACTION_ENTER_VEHICLE,
	SPECIAL_ACTION_EXIT_VEHICLE,
	SPECIAL_ACTION_DANCE1,
	SPECIAL_ACTION_DANCE2,
	SPECIAL_ACTION_DANCE3,
	SPECIAL_ACTION_DANCE4,
	SPECIAL_ACTION_HANDSUP = 10,
	SPECIAL_ACTION_USECELLPHONE,
	SPECIAL_ACTION_SITTING,
	SPECIAL_ACTION_STOPUSECELLPHONE,
	SPECIAL_ACTION_DRINK_BEER = 20,
	SPECIAL_ACTION_SMOKE_CIGGY,
	SPECIAL_ACTION_DRINK_WINE,
	SPECIAL_ACTION_DRINK_SPRUNK,
	SPECIAL_ACTION_CUFFED,
	SPECIAL_ACTION_CARRY,
	SPECIAL_ACTION_URINATE = 68,

	COUNT_SPECIAL_ACTION = 20
};

//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// SAMP STRUCTURES ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)
struct stSAMPPools
{
	struct stGangzonePool	*pGangzone;
	struct stPlayerPool		*pPlayer;
	struct stVehiclePool	*pVehicle;
	void					*pPlayerLabels;
	struct stTextdrawPool	*pTextdraw;
	struct stObjectPool		*pObject;
	struct stTextLabelPool	*pText3D;
	struct stPickupPool		*pPickup;
};

struct stSAMP
{
	uint8_t					unk0[32];
	uint32_t				ulMapIcons[100];
	int						iLanMode;
	uint32_t				ulPort;
	char					szIP[257];				// 440
	char					szHostname[257];
	int						iGameState;
	uint32_t 				ulConnectTick;			
	RakClientInterface		*pRakClientInterface;	// 962
	struct stSampSettings	*pSettings;				// 966
	struct stSAMPPools		pPools;					// 970

	void					updateScoreBoard(void);
	void					restartGame(void);
	void					disconnect(int reason);
	void					takeScreenShot();
	void					setPassword(const char *szPassword);
	void					changeServer(const char *szIP, unsigned int iPort);
	void					sendQuery(const char *szIP, unsigned int iPort);
	void					showGameText(const char *szText, int iTime, signed int iStyle);
};

struct stSampSettings
{
	uint8_t	isTimeUpdate;
	uint8_t	unk_1;
	uint8_t	bZoneNames;
	uint8_t	unk_3;
	uint8_t	bWeather;
	uint8_t	bNoNametagsBehindWalls;
	uint8_t	bPlayerMarkersMode;
	int		iSpawnsAvailable;
	uint8_t	unk_11[3];
	uint8_t	bShowNameTags;
	uint8_t	unk_15;
	uint8_t	bCJWalk;
	int		iDeadDropMoney;
	float	fWorldBoundaries[4];
	uint8_t	unk_37;
	float	fGravity;
	uint8_t	bDisableInteriorEnterExits;
	int		iSelectedClass;
	float	fNameTagsDistance;
	uint8_t	bShowZoneNames;
	uint8_t	bWorldTime_Hour;
	uint8_t	bWorldTime_Minute;

};

struct stSAMPKeys
{
	uint8_t keys_primaryFire : 1;
	uint8_t keys_horn__crouch : 1;
	uint8_t keys_secondaryFire__shoot : 1;
	uint8_t keys_accel__zoomOut : 1;
	uint8_t keys_enterExitCar : 1;
	uint8_t keys_decel__jump : 1;			// on foot: jump or zoom in
	uint8_t keys_circleRight : 1;
	uint8_t keys_aim : 1;					// hydra auto aim or on foot aim
	uint8_t keys_circleLeft : 1;
	uint8_t keys_landingGear__lookback : 1;
	uint8_t keys_unknown__walkSlow : 1;
	uint8_t keys_specialCtrlUp : 1;
	uint8_t keys_specialCtrlDown : 1;
	uint8_t keys_specialCtrlLeft : 1;
	uint8_t keys_specialCtrlRight : 1;
	uint8_t keys__unused : 1;
};

struct stAttachedObject
{
	int		iModelID;
	int		iBoneID;
	float	vecPos[3];
	float	vecRot[3];
	float	vecScale[3];
	DWORD	dwMaterialColor1;
	DWORD	dwMaterialColor2;
};

struct stOnFootData
{
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float		fPosition[3];
	float		fQuaternion[4];
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSpecialAction;
	float		fMoveSpeed[3];
	float		fSurfingOffsets[3];
	uint16_t	sSurfingVehicleID;
	uint16_t	sCurrentAnimationID;
	uint16_t	sAnimFlags;
};

struct stInCarData
{
	uint16_t	sVehicleID;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float		fQuaternion[4];
	float		fPosition[3];
	float		fMoveSpeed[3];
	float		fVehicleHealth;
	uint8_t		bytePlayerHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSiren;
	uint8_t		byteLandingGearState;
	uint16_t	sTrailerID;
	union
	{
		uint16_t	HydraThrustAngle[2];	//nearly same value
		float		fTrainSpeed;
	};
};

struct stAimData
{
	BYTE	byteCamMode;
	float	vecAimf1[3];
	float	vecAimPos[3];
	float	fAimZ;
	BYTE	byteCamExtZoom : 6;	// 0-63 normalized
	BYTE	byteWeaponState : 2;	// see eWeaponState
	BYTE	bUnk;
};

struct stTrailerData
{
	uint16_t	sTrailerID;
	float		fPosition[3];
	float		fQuaternion[4];
	float		fSpeed[3];
	float		fUnk[3];
};

struct stPassengerData
{
	uint16_t	sVehicleID;
	uint8_t		byteSeatID;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float		fPosition[3];
};

struct stDamageData
{
	uint16_t	sVehicleID_lastDamageProcessed;
	int			iBumperDamage;
	int			iDoorDamage;
	uint8_t		byteLightDamage;
	uint8_t		byteWheelDamage;
};

struct stSurfData
{
	int			iIsSurfing;
	float		fSurfPosition[3];
	int			iUnknown;
	uint16_t	sSurfingVehicleID;
	uint32_t	ulSurfTick;
	void		*unkPointer;
	int			iSurfMode;			// 0 = not surfing, 1 = moving (unstable surf), 2 = fixed on vehicle
};

struct stHeadSync
{
	float	fHeadSync[3];
	int		iHeadSyncUpdateTick;
	int		iHeadSyncLookTick;
};

struct stSpawnInfo
{
	uint8_t		byteTeamID;
	int			iSpawnSkin;
	uint8_t		unknown_1D;
	float		fSpawnPos[3];
	float		fSpawnRot;
	int			iSpawnWeapon[3];
	int			iSpawnAmmo[3];
};

struct stPlayerPool
{
	struct stLocalPlayer	*pLocalPlayer;
	void					*pVTBL_txtHandler;
	string					strLocalPlayerName;
	struct stRemotePlayer	*pRemotePlayer[SAMP_MAX_PLAYERS + 500];
	int						iIsListed[SAMP_MAX_PLAYERS + 500];
	int						iLocalPlayerScore;
	int						iLocalPlayerPing;
	uint16_t				sLocalPlayerID;

	inline bool				isBadPlayer(int iPlayerID);
	void					deletePlayer(int iPlayerID);
	void					resetPlayerPool(void);
	void					setLocalPlayerName(string name);
	void					setPlayerName(int iPlayerID, string name);
	const char				*getPlayerName(int iPlayerID);
	D3DCOLOR				getPlayerColor(int iPlayerID, DWORD trans = 0xFF000000);
	D3DCOLOR				getLocalPlayerColor(DWORD trans = 0xFF000000);
	int						getPlayerCount(void);
	CVector					*getPlayerPos(int iPlayerID);
	CVector					*getBonePos(int iPlayerID, uint8_t bBoneID);
	int						getPlayerState(int iPlayerID);
	struct actor_info		*getGTAPed(int iPlayerID);
	int						getPlayerID(struct actor_info *pGTAPed);
	int						findTargetPlayer(float fRadius);
	int						findNearestPlayer(float fRadius);
	int						findAnyStreemedPlayer();
};

struct stRemotePlayer
{
	void						*pVTBL_txtHandler;		// 0
	string						strPlayerName;
	int							iSmth;					// 28
	struct stRemotePlayerData	*pPlayerData;			// 32
	int							iScore;
	int							iIsNPC;
	int							iPing;
};

struct stLocalPlayer
{
	struct stSAMPPed		*pSAMP_Actor;				// 0
	uint16_t				sCurrentVehicleID;			// 4
	uint16_t				sLastVehicleID;				// 6
	int						iIsAlive;					// 8
	int						iIsWasted;					// 12
	uint16_t				sCurrentAnimID;				// 16
	uint16_t				sAnimFlags;					// 18
	uint32_t				unk_20;						// 20
	struct stSpawnInfo		spawnInfo;					// 24
	int						iIsSpawned;					// 70
	int						iSpawnClassLoaded;			// 74
	uint32_t				ulSpawnSelectionTick;		// 78
	uint32_t				ulSpawnSelectionStart;		// 82
	int						iIsSpectating;				// 86
	uint8_t					byteTeamID2;				// 90	
	uint8_t					byteUnkTimers[22];			// 91
	uint16_t				sAimingAtPid;				// 113
	uint8_t					byteCurrentWeapon;			// 115
	uint8_t					byteWeaponInventory[13];	// 116
	int						iWeaponAmmo[13];			// 129
	struct stHeadSync		headSyncData;				// 181
	uint32_t				unkTick;					// 201
	struct stSurfData		surfData;					// 205		
	int						iPassengerDriveBy;			// 236
	uint8_t					byteCurrentInterior;		// 243
	int						iIsInRCVehicle;				// 244
	uint8_t					unk_248[256];				// 248	
	struct stPassengerData	passengerData;				// 504
	struct stAimData		aimData;					// 528
	struct stTrailerData	trailerData;				// 559
	struct stOnFootData		onFootData;					// 613
	struct stInCarData		inCarData;					// 681
	uint8_t					byteSpectateMode;		// 3 = vehicle, 4 = player, side = 14, fixed = 15
	uint8_t					byteSpectateType;		// 0 = none, 1 = player, 2 = vehicle
	int						iSpectateID;				// 746
	int						iInitiatedSpectating;		// 750
	struct stDamageData		vehicleDamageData;
	int						unk_766;
	int						iClassSelectionOnDeath;
	int						iSpawnClassID;
	int						iRequestToSpawn;
	int						iIsInSpawnScreen;
	int						unk_786;
	
	void					say(const char *szMsg, ...);
	void					sendDeath(void);
	void					sendSpawn(void);
	void					sendSetInterior(uint8_t interiorID);
	uint8_t					getSpecialAction(void);
	void					setSpecialAction(uint8_t bAction);
	void					toggleControllable(int iControl);
	int						getPlayerState(void);
	void					sendGiveDamage(uint16_t sPlayer, float fDamage, int iWeapon, int iBody);
	void					sendTakeDamage(uint16_t sPlayer, float fDamage, int iWeapon, int iBody);
}; 

struct stRemotePlayerData
{
	int						unk_0;				// 0
	uint16_t				sPlayerID;			// 4
	uint16_t				sVehicleID;			// 6
	uint8_t					byteSeatID;			// 7 not tested
	int						iPassengerDriveBy;  // 11
	uint8_t					byteTeamID;			// 12
	uint8_t					bytePlayerState;	// 13
	struct stPassengerData	passengerData;			// 14
	struct stAimData		aimData;				// 38
	struct stTrailerData	trailerData;			// 69
	struct stInCarData		inCarData;				// 125
	struct stOnFootData		onFootData;				// 188	
	uint8_t					unk_255[12];			// 255
	uint8_t					byteSpecialAction;		// 267
	float					fOnFootPosition[3];		// 268
	float					fOnFootSpeed[3];		// 280
	float					fInVehiclePosition[3];	// 292
	float					fInVehicleMoveSpeed[3];	// 304
	float					fInVehicleRoll[4];		// 316
	uint8_t					unk_332[33];			// 332
	int						iShowNameTag;			// 365
	int						iHasJetPack;			// 369
	uint32_t				dwTick;					// 373
	uint32_t				dwLastStreamedInTick;	// 377 is 0 when currently streamed in
	float					fActorHealth;			// 381
	float					fActorArmor;			// 385
	int						unk_389;				// 389
	struct stSAMPPed		*pSAMP_Actor;			// 393
	struct stSAMPVehicle	*pSAMP_Vehicle;			// 397	
	struct stHeadSync		headSyncData;			// 401
	int						iGlobalMarkerLoaded;	// 421
	int						iGlobalMarkerLocation[3];// 425
	uint32_t				ulGlobalMarker_GTAID;	// 437
};

struct stVehiclePool
{
	BYTE					bUnknown[0xBCAC];
	struct vehicle_info		*pGTA_Vehicle[SAMP_MAX_VEHICLES];
	struct stSAMPVehicle	*pSAMP_Vehicle[SAMP_MAX_VEHICLES];
	int						iIsListed[SAMP_MAX_VEHICLES];
	float					fSpawnPos[SAMP_MAX_VEHICLES][3];
	int						iInitiated;


	inline bool				isBadVehicle(int iVehicleID);
	CVector					*getVehiclePos(int iVehicleID);
	void					sendSCMEvent(int iEvent, int iVehicleID, int iParam1, int iParam2);
	int						getVehiclesCount(void);
	int						getSAMPVehicleID(struct vehicle_info *pVehicle);
	struct vehicle_info		*getGTAVehicle(int iVehicleID);
	int						findNearestVehicle(float fRadius = 1000.f);
	int						findNearestEmptyVehicle(float fRadius = 1000.f);

};

struct stEntity
{
	void				*pVTBL_Entity;
	uint8_t				unknown_pad[60];	// +4
	struct entity_base	*pGTA_Entity;		// +64
	DWORD				dwScriptID;			// +68
};

struct stSAMPPed : public stEntity
{
	int					usingCellPhone;		// +72
	struct actor_info	*pGTA_Ped;			// +76
	int					unk_80;				// +80
	int					unk_84;				// +84
	uint8_t				bytePedId;			// +88
	int					unk_89;				// +89
	int					unk_93;				// +93
	int					atached_object_id;	// +97
	uint8_t				unk_101[612];		// +101
	int					DrinkingOrSmoking;	// +713
	int					object_in_hand;		// +717
	int					drunkLevel;			// +721
	int					isUrinating;		// +725
	uint32_t			ulGTA_UrinateParticle_ID; // +729
	int					maybe_GtaMarkerID;	// +733
	uint8_t				unk_737;			// +737
	int					isDancing;			// +738
	int					danceStyle;			// +742
	int					danceMove;			// +746
	int					isCuffed;			// +750
	int					unk_754;			// +754

	bool				isPassenger(void);
	bool				isDriving(void);
	uint8_t				getSeatId(void);
	void				setImmunities(bool bullet, bool flame, bool explosion, bool collision, bool knife);
	void				removeFromCarAndPutAt(float fPos[3]);
	void				putInVehicle(int iGTA_VehicleID, uint8_t seatId);
	void				setRotation(float fAngle); // not testing
	CVector				*getPosition(void);
	CVector				*getBonePos(uint8_t bBoneID);
};

struct stSAMPVehicle : public stEntity
{
	struct vehicle_info *pGTA_Vehicle;		// 72
	BOOL				iIsMotorOn;			// 76
	BOOL				iIsLightsOn;		// 80
	BOOL				iIsInvulnerable;
	BOOL				iIsBlocked;			// No control state
	BOOL				iIsDoorLocked;		// 92
	uint8_t				byteIsObjective;	// 96
	int					iObjectiveCreated;	// 97
	uint8_t				unk_101[8];			// 101
	stSAMPVehicle		*pTrailer;			// 109
	uint8_t				unk_113[12];		// 113
	
	uint8_t				byteColor[2];		// 125
	int					iColorSync;			// 127
	int					iColor_something;	// 131

	void				setDoorState(bool state);
	void				setColor(uint8_t color_0, uint8_t color_1);
	bool				isSelfVehicle(void);
	CVector				*getPosition(void);
};

struct stObject : public stEntity
{
	BYTE				bIsCreated;
	uint8_t				unk_77[64];		// 73
	float				fRot[3];		// 137 
	uint8_t				unk_149[112];	// 149
	float				fPos[3];		// 261
}; 

struct stObjectPool
{
	uint8_t				pad[76];
	int					iIsListed[SAMP_MAX_OBJECTS];
	struct stObject		*object[SAMP_MAX_OBJECTS];
};

struct stPickupPool
{
	struct stPickup
	{
		int		iModelID;
		int		iType;
		float	fPosition[3];
	};

	int					iTimePickup[SAMP_MAX_PICKUPS];
	uint8_t				unk[SAMP_MAX_PICKUPS * 3];
	stPickup			pickup[SAMP_MAX_PICKUPS];
	uint32_t			ul_GTA_PickupID[SAMP_MAX_PICKUPS];
	int					iPickupID[SAMP_MAX_PICKUPS];
	int					count;
};

struct stGangzonePool
{
	struct stGangzone
	{
		float	fPosition[4];
		DWORD	dwColor;
		DWORD	dwAltColor;
	};
	
	stGangzone			*pGangzone[SAMP_MAX_GANGZONES];
	int					iIsListed[SAMP_MAX_GANGZONES];
};

struct stTextDrawTransmit
{
	float		fLetterWidth;
	float		fLetterHeight;
	DWORD		dwLetterColor;
	float		fBoxWidth;
	float		fBoxHeight;
	DWORD		dwBoxColor;
	union
	{
		BYTE byteFlags;
		struct
		{
			BYTE byteBox : 1;
			BYTE byteLeft : 1;
			BYTE byteRight : 1;
			BYTE byteCenter : 1;
			BYTE byteProportional : 1;
			BYTE bytePadding : 3;
		};
	};
	BYTE		byteShadowSize;
	BYTE		byteOutline;
	DWORD		dwShadowColor;
	BYTE		byteStyle;
	BYTE		byteSelectable;
	float		fX;
	float		fY;
	uint16_t	sModel;
	float		fRot[3];
	float		fZoom;
	WORD		sColor[2];
};

struct stTextdraw
{
	char		szText[0x401];
	char		szString[0x802];
	float		fLetterWidth;
	float		fLetterHeight;
	DWORD		dwLetterColor;
	BYTE		byte_unk;
	BYTE		byteCenter;
	BYTE		byteBox;
	float		fBoxSizeX;
	float		fBoxSizeY;
	D3DCOLOR	dwBoxColor;
	BYTE		byteProportional;
	D3DCOLOR	dwShadowColor;
	BYTE		byteShadowSize;
	BYTE		byteOutline;
	BYTE		byteLeft;
	BYTE		byteRight;
	int			iStyle;
	float		fX;
	float		fY;
	BYTE		unk[16];
	DWORD		index;
	BYTE		byteSelectable;
	uint16_t	sModel;
	float		fRot[3];
	float		fZoom;
	BYTE		bColor;
	DWORD		dwColor;
};

struct stTextdrawPool
{
	int					iIsListed[SAMP_MAX_TEXTDRAWS];
	int					iPlayerTextDraw[SAMP_MAX_PLAYERTEXTDRAWS];
	struct stTextdraw	*textdraw[SAMP_MAX_TEXTDRAWS];
	struct stTextdraw	*playerTextdraw[SAMP_MAX_PLAYERTEXTDRAWS];
};

struct stTextLabel
{
	char		*pText;
	DWORD		color;
	float		fPosition[3];
	float		fMaxViewDistance;
	uint8_t		byteShowBehindWalls;
	uint16_t	sAttachedToPlayerID;
	uint16_t	sAttachedToVehicleID;
};

struct stTextLabelPool
{
	struct stTextLabel	textLabel[SAMP_MAX_3DTEXTS];
	int					iIsListed[SAMP_MAX_3DTEXTS];
};

struct stScrollBar
{
	void				*p_ScrollInterface;
	uint8_t				bIsScrollOpen;
	uint8_t				bIsMouseInScroll;
	uint8_t				bMouseClick_related;
	uint8_t				buteUnk;
	DWORD				dwScrollPos[2];
	DWORD				dwScrollSize[2];
	uint8_t				unk_18[53];		/* 24 */
	uint8_t				unk_4D;			/* 77 */
	uint8_t				unk_4E[36];		/* 78 */
	uint32_t			unk_72;			/* 114 */
	uint8_t				unk_76[4];		/* 118 */
	uint32_t			unk_7C;			/* 122 */
	uint8_t				unk_80[4];		/* 126 */
	uint32_t			unk_82;			/* 130 */
	uint8_t				unk_86[4];		/* 134 */
	uint32_t			unk_8A;			/* 138 */
	int					pagesize;		/* 142 */
	int					curentPos;		/* 146 */
	int					minimum;		/* 150 */
	int					maximum;		/* 154 */
};

struct stFontRenderer
{
	ID3DXFont			*m_pChatFont;
	ID3DXFont			*m_pLittleFont;
	ID3DXFont			*m_pChatShadowFont;
	ID3DXFont			*m_pLittleShadowFont;
	ID3DXFont			*m_pCarNumberFont;
	ID3DXSprite			*m_pTempSprite;
	IDirect3DDevice9	*m_pD3DDevice;
	char				*m_pszTextBuffer;
};

struct stChatEntry			// size 252
{
	DWORD					dwTime;			// +0
	char					szPrefix[28];	// +4
	char					szText[144];	// +32
	uint8_t					unknown[64];	// +176
	eChatMessageType		iType;			// +240
	D3DCOLOR				clTextColor;	// +244
	D3DCOLOR				clPrefixColor;	// +248
};

struct stChatInfo
{
	D3DCOLOR				clTextColor;			// 0
	D3DCOLOR				clInfoColor;			// 4
	D3DCOLOR				clDebugColor;			// 8
	DWORD					dwChatboxOffset;		// 12
	eChatDisplayMode		iChatWindowMode;		// 16
	uint8_t					bTimestamps;			// 20
	uint32_t				iLogFileExist;			// 21
	char					szLogFilePath[MAX_PATH + 1]; // 25
	int						pagesize;				// 286
	void					*pChatbox_unknown[2];	// 290
	struct stEditBox		*pEditBackground;		// CDXUTEditBox
	struct stScrollBar		*pScrollBar;			// CDXUTScrollBar
	struct stChatEntry		chatEntry[100];			// 306
	struct stFontRenderer	*pFontRenderer;			// 25506
	ID3DXSprite				*pChatTextSprite;		// 25510
	ID3DXSprite				*pSprite;				// 25514
	IDirect3DDevice9		*pD3DDevice;			// 25518
	int						iRenderMode;			// 25522   // 0 - Direct Mode (slow), 1 - Normal mode
	ID3DXRenderToSurface	*pID3DXRenderToSurface; // 25526
	IDirect3DTexture9		*m_pTexture;			// 25530
	IDirect3DSurface9		*pSurface;				// 25534
	D3DDISPLAYMODE			D3DDisplayMode;			// 25538
	uint32_t				ulLastUpdateTick;		// 25554
	int						iUnk_25558;				// 25558
	int						iRedraw;				// 25562
	int						iScrollPosition;		// 25566
	int						iTimestampWidth;		// 25570
	int						iFontHeight;

	void					addMessageToChat(D3DCOLOR dwColor, string &msg, int type = CHAT_TYPE_DEBUG, D3DCOLOR dwPrefixColor = NULL, string prefix = "");
	void					addMessageToChat(D3DCOLOR dwColor, const char *msg, ...);
	void					deleteMessage(int iStringNum);
	void					clearChat(void);
};

struct stEditBox
{
	void					*pUnknown;				// 0
	uint8_t					bIsShowed;				// 4
	uint8_t					bIsMouseAtEdit;			// 5
	uint8_t					bInFocusForEnter;		// 6
	uint8_t					unk_7;					// 7
	int32_t					iPosInsideX;			// 8
	int32_t					iPosInsideY;			// 12
	int32_t					iWidth;					// 16
	int32_t					iHeight;				// 20
	uint8_t					unk_24[53];
	std::wstring			wstrInputText;
	uint8_t					unk_101[180];			// 101
	int						iCursorPosition;		// 281
	uint8_t					unk3;					// 285
	int						iMarkedText_startPos;	// 286
	uint32_t				unk_290;				// 290
	uint8_t					unk_294[17];			// 294
	uint8_t					bMouseLeftButton;		// 311

};

using CMDPROC = void(__cdecl *)(PCHAR);
struct stInputInfo
{
	IDirect3DDevice9		*pD3DDevice;
	class _CDXUTDialog		*pDXUTDialog;
	struct stEditBox		*pEditBox;
	CMDPROC 				pszCMDs[SAMP_MAX_CLIENTCMDS];
	char					szCMDNames[SAMP_MAX_CLIENTCMDS][33];
	int						iCMDCount;
	int						iInputEnabled;
	char					szInputBuffer[SAMP_MAX_INPUT_LENGTH];
	char					szRecallBufffer[10][SAMP_MAX_INPUT_LENGTH];
	char					szCurrentBuffer[SAMP_MAX_INPUT_LENGTH];
	int						iCurrentRecall;
	int						iTotalRecalls;
	CMDPROC 				pszDefaultCMD;

	void					addClientCommand(string cmd, CMDPROC func);
	void  					sendClientCommand(string cmd);
	CMDPROC					getCmdFunc(string cmd);
	string 					getInputText(void);
	void					disableInput(void);
	void					enableInput(void);
}; 

struct stDialogInfo
{
	IDirect3DDevice9		*pD3DDevice;		// 0
	int						iTextPosX;			// 4
	int						iTextPosY;			// 8
	uint32_t				uiDialogSizeX;		// 12
	uint32_t				uiDialogSizeY;		// 16
	int						iBtnOffsetX;		// 20
	int						iBtnOffsetY;		// 24
	class _CDXUTDialog		*pDXUTDialog;		// 28
	class _CDXUTListBox		*pListBox;			// 32
	struct stEditBox		*pEditBox;			// 36
	int						iDialogShowed;		// 40
	int						iType;				// 44
	uint32_t				iDialogID;			// 48
	char					*szText;			// 52
	uint32_t				uiTextWidth;		// 56
	uint32_t				uiTextHeight;		// 60
	char					szTitle[65];		// 64
	int						bServerside;		// 129

	void					createDialog(int iDialogID, int iType, string title, string text, string button1, string button2 = NULL);
	void					setListBoxItem(WORD wListItem);
	void					setEditBoxText(string input);
	string					getEditBoxText(void);
	void					closeDialog(BYTE bButtonID, WORD wListItem = 0, string input = NULL);

};

struct stScoreboardInfo
{
	int					iIsEnabled;
	int					iPlayersCount;
	float				fTextOffset[2];
	float				fScalar;
	float				fSize[2];
	float				fUnk0[5];
	IDirect3DDevice9	*pDirectDevice;
	class _CDXUTDialog	*pDialog;
	class _CDXUTListBox *pList;
	int					iOffset;		// ?
	int					iIsSorted;		// ?


	void				disableScoreboard(void);
	void				enableScoreboard(void);
};

struct stKillEntry
{
	char		szKiller[25];
	char		szVictim[25];
	D3DCOLOR	clKillerColor;
	D3DCOLOR	clVictimColor;
	uint8_t		byteType;
};

struct stKillInfo
{
	int					iEnabled;
	struct stKillEntry	killEntry[5];
};

struct stChatPlayer
{
	int			iCreated;
	char		probablyTheText[256]; // text max length = 144
	DWORD		dwTickCreated;
	DWORD		dwLiveLength;
	DWORD		dwColor;
	float		fDrawDistance;
	DWORD		dwUnknown;
};

struct stMiscInfo
{
	void			*pAudio;
	void			*pCamera;
	stSAMPPed		*pLocalPlayerPed;
	float			fCheckpointPos[3];			// 12
	float			fCheckpointSize[3];			// 24
	DWORD			iCheckpointEnabled;			// 36
	DWORD			dwCheckpointMarker;
	float			vecRaceCheckpointPos[3];	// 44
	float			vecRaceCheckpointNextPos[3];// 56
	float			m_fRaceCheckpointSize;		// 68 
	uint8_t			byteRaceType;				// 72
	int				iRaceCheckpointEnabled;		// 73
	DWORD			dwRaceCheckpointMarker;
	DWORD			dwRaceCheckpointHandle;		// 81
	eCursorMode		iCursorMode;				// 85
	int				iCursorSomething;
	int				iClockEnable;
	int				unk_97;
	int				iHeadMove;
	int				iFpsLimit;
	
	void			toggleSAMPCursor(bool bToggle, eCursorMode iMode = CURSORMODE_LOCK_KEYBOARD);
};

struct stTextdrawInfo
{
	uint16_t	isActive;
	uint8_t		unk_2[6];
	uint16_t	wSelectedTextId;

	// ...
};

#pragma pack(pop)
//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// SUPPORT VARIABLES //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class CCRMP
{
private:
	bool						isInited		= false;
	uint32_t					uiCRMPAddr		= 0;
protected:
	stSAMP						*pInfo			= nullptr;
	stMiscInfo					*pMisc			= nullptr;
	stChatInfo					*pChat			= nullptr;
	stInputInfo					*pInput			= nullptr;
	stKillInfo					*pKill			= nullptr;
	stDialogInfo				*pDialog		= nullptr;
	stTextdrawInfo				*pTextDraw		= nullptr;
	stScoreboardInfo			*pScoreList		= nullptr;
	RakClient					*pRakClient		= nullptr;
public:
								CCRMP			(void);
	
	uint8_t						Init			(void);
	uint32_t					getBase			(void)	{ return uiCRMPAddr; };
	stSAMP						*getInfo		(void)	{ return pInfo; };
	stMiscInfo					*getMisc		(void)	{ return pMisc; };
	stChatInfo					*getChat		(void)	{ return pChat; };
	stInputInfo					*getInput		(void)	{ return pInput; };
	stKillInfo					*getKill		(void)	{ return pKill; };
	stDialogInfo				*getDialog		(void)	{ return pDialog; };
	stTextdrawInfo				*getTextDraw	(void)	{ return pTextDraw; };
	stScoreboardInfo			*getScoreList	(void)	{ return pScoreList; };
	stPlayerPool				*getPlayers		(void)	{ return pInfo->pPools.pPlayer; };
	stVehiclePool				*getVehicles	(void)	{ return pInfo->pPools.pVehicle; };
	stObjectPool				*getObjects		(void)	{ return pInfo->pPools.pObject; };
	RakClient					*getRakClient	(void)	{ return pRakClient; };
};

void							sampSyncDisable(uint8_t id, eNetPatchType type, bool state);

extern CCRMP					*pCRMP;
extern HMODULE					hThisModule;
extern char						szWorkingDirectory[MAX_PATH];
extern char						szIniFileName[MAX_PATH];
