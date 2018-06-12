/*
		AUTHOR: SlonoBoyko
		LiteHack.Ru
		21.05.2018
*/

#pragma once
 
/*--------------------SAMP OFFSETS----------------------------*/
#define SAMP_HOOKENTER_STATECHANGE						(samp_base + 0x10458)
#define SAMP_HOOKENTER_HANDLE_RPC						(samp_base + 0x3611D)
#define SAMP_HOOKENTER_HANDLE_RPC_2						(samp_base + 0x3610E)

#define SAMP_HOOKENTER_CPLAYERCONSTRUCTOR				(samp_base + 0xA2793)
#define SAMP_HOOKENTER_CVEHICLECONSTRUCTOR				(samp_base + 0xA7C34)
#define SAMP_HOOKCALL_CNETGAMEDESTRUCTOR				(samp_base + 0xA8AA3)
#define SAMP_HOOKCALL_CNETGAMEDESTRUCTOR_2				(samp_base + 0xA9B12)
#define SAMP_HOOKCALL_CLOSEDIALOG						(samp_base + 0x66E1B)

#define SAMP_HOOKEXIT_STATECHANGE						(samp_base + 0x10469)
#define SAMP_HOOKEXIT_HANDLE_RPC						(samp_base + 0x36123)

#define SAMP_HOOKEXIT_CPLAYERCONSTRUCTOR				(samp_base + 0xA7C3B)
#define SAMP_HOOKEXIT_CVEHICLECONSTRUCTOR				(samp_base + 0xA279A)
#define SAMP_FUNC_CNETGAMEDESTRUCTOR					(samp_base + 0x07EB0)
#define SAMP_FUNC_CLOSEDIALOG							(samp_base + 0x665E0)

/*--------------------GAME OFFSETS----------------------------*/
#define HOOKPOS_FixMouseStuck							0x745423
#define HOOKPOS_PlayerCollision							0x54BCEE
#define HOOKPOS_CrashFix_Misc							0x4D1750
#define HOOKPOS_CrashFix_Anim							0x5E5815
#define HOOKCALL_UpdateGameKey							0x541E17

#define RETURN_FixMouseStuck_Cont						0x74542B
#define RETURN_FixMouseStuck_Exit						0x745433
#define RETURN_CollisionProcess							0x54BCF4
#define RETURN_CollisionNoProcessing					0x54CF8D



void		InstallAllHooks();


const char RpcEnumeration[][128] = {
	" ",
	" ",
	" ",
	" ",
	" ",
	" ",
	"RPC_ServerCommand = 6",
	"RPC_SetInteriorId = 7",
	"RPC_MapMarker = 8",
	"RPC_VehicleDestroyed = 9",
	"RPC_ServerJoin = 10",
	"RPC_ServerQuit = 11",
	"RPC_InitGame = 12",
	"RPC_ConnectionRejected = 13",
	"RPC_ClientMessage = 14",
	"RPC_SetWorldTime = 15",
	"RPC_NULL = 16",
	"RPC_NULL = 17",
	"RPC_NULL = 18",
	"RPC_SetPlayerWeather = 19",
	"RPC_SetPlayerSkin = 20",
	"RPC_SetPlayerName = 21",
	"RPC_SetPlayerPos = 22",
	"RPC_SetPlayerPosFindZ = 23",
	"RPC_SetPlayerHealth = 24",
	"RPC_PutPlayerInVehicle = 25",
	"RPC_RemovePlayerFromVehicle = 26",
	"RPC_SetPlayerColor = 27",
	"RPC_DisplayGameText = 28",
	"RPC_ForceSpawnSelection = 29",
	"RPC_AttachObjectToPlayer = 30",
	"RPC_InitMenu = 31",
	"RPC_ShowMenu = 32",
	"RPC_HideMenu = 33",
	"RPC_SetPlayerWantedLevel = 34",
	"RPC_ShowTextDraw = 35",
	"RPC_HideTextDraw = 36",
	"RPC_EnableStuntBonus = 37",
	"RPC_EditTextDraw = 38",
	"RPC_AddGangZone = 39",
	" ",
	" ",
	" ",
	"RPC_PlayCrimeReportForPlayer = 43",
	"RPC_SetPlayerAttachedObject = 44",
	"RPC_PlayAudioStream = 45",
	"RPC_StopAudioStreamForPlayer = 46",
	"RPC_RemoveBuildingForPlayer = 47",
	"RPC_CreateObject = 48",
	"RPC_SetObjectPos = 49",
	"RPC_SetObjectRotation = 50",
	"RPC_DestroyObject = 51",
	" ",
	" ",
	"RPC_CreateExplosion = 54",
	"RPC_ShowNameTagForPlayer = 55",
	"RPC_AttachCameraToObject = 56",
	" ",
	"RPC_ClickTextDraw = 58",
	" ",
	"RPC_GiveTakeDamage = 60",
	"RPC_EditAttachedObject = 61",
	"RPC_EditObject = 62",
	"RPC_SelectObject = 63",
	"RPC_CancelEdit = 64",
	"RPC_ConnectionPong = 65",
	"RPC_SetPlayerTime = 66",
	"RPC_TogglePlayerClock = 67",
	" ",
	"RPC_WorldPlayerAdd = 69",
	"RPC_SetShopName = 70",
	"RPC_SetPlayerSkillLevel = 71",
	"RPC_SetDrunkLevel = 72",
	" ",
	" ",
	"RPC_SetChatBubble = 75",
	" ",
	"RPC_ShowDialog = 77",
	"RPC_DialogResponse = 78",
	"RPC_ClickPlayer = 79",
	"RPC_VehicleParams = 80",
	"RPC_ClientJoin = 81",
	"RPC_RemoveGangZone = 82",
	"RPC_FlashGangZone = 83",
	"RPC_StopFlashGangZone = 84",
	"RPC_ApplyAnimation = 85",
	"RPC_ClearAnimations = 86",
	"RPC_SetSpecialAction = 87",
	"RPC_SetFightingStyle = 88",
	"RPC_SetPlayerVelocity = 89",
	"RPC_SetVehicleVelocity = 90",
	" ",
	" ",
	" ",
	"RPC_MoveObject = 94",
	"RPC_StopObject = 95",
	" ",
	"RPC_TogglePlayerSpectating = 97",
	"RPC_SetPlayerSpectating = 98",
	"RPC_PlayerSpectatePlayer = 99",
	"RPC_PlayerSpectateVehicle = 100",
	"RPC_RequestClass = 101",
	"RPC_RequestSpawn = 102",
	"RPC_EnterVehicle = 103",
	"RPC_ExitVehicle = 104",
	"RPC_UpdateScoresPingsIPs = 105",
	"RPC_SetPlayerInterior = 106",
	"RPC_SetCameraPos = 107",
	"RPC_SetCameraLookAt = 108",
	"RPC_SetVehiclePos = 109",
	"RPC_SetVehicleZAngle = 110",
	"RPC_SetVehicleParamsForPlayer = 111",
	"RPC_SetCameraBehindPlayer = 112",
	"RPC_TogglePlayerControllable = 113",
	"RPC_PlaySound = 114",
	"RPC_SetPlayerWorldBounds = 115",
	"RPC_GivePlayerMoney = 116",
	"RPC_SetPlayerFacingAngle = 117",
	"RPC_ResetMoney = 118",
	"RPC_ResetPlayerWeapons = 119",
	"RPC_GivePlayerWeapon = 120",
	" ",
	"RPC_LinkVehicleToInterior = 122",
	"RPC_SetPlayerArmour = 123",
	" ",
	"RPC_SetSpawnInfo = 125",
	"RPC_SetPlayerTeam = 126",
	"RPC_WorldPlayerRemove = 127",
	"RPC_WorldVehicleAdd = 128",
	"RPC_WorldVehicleRemove = 129",
	"RPC_WorldPlayerDeath = 130",
	"RPC_DamageVehicle = 131",
	"RPC_SetPlayerCheckpoint = 132",
	"RPC_DisablePlayerCheckpoint = 133",
	"RPC_SetPlayerRaceCheckpoint = 134",
	"RPC_DisablePlayerRaceCheckpoint = 135",
	"RPC_GameModeRestart = 136",
	" ",
	"RPC_Chat = 138",
	" ",
	"RPC_ScmEvent = 140",
	" ",
	"RPC_PickedUpPickup = 142",
	"RPC_MenuSelect = 143",
	"RPC_MenuQuit = 144",
	" ",
	" ",
	" ",
	" ",
	" ",
	"RPC_Spawn = 150",
	"RPC_Death = 151",
	"RPC_NPCJoin = 152",
	"RPC_DeathMessage = 153",
	"RPC_SetMapIcon = 154",
	"RPC_DisableMapIcon = 155",
	" ",
	"RPC_SetGravity = 157",
	"RPC_SetVehicleHealth = 158",
	"RPC_AttachTrailerToVehicle = 159",
	"RPC_DetachTrailerFromVehicle = 160",
	"RPC_AddVehicleComponent = 161" 
};