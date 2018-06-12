/*
		AUTHOR: SlonoBoyko
		LiteHack.Ru
		21.05.2018
*/

#pragma once

// -loadsamp -c -n Slono_Boyko -h 192.168.1.10 -p 8904
  
#ifdef _DEBUG
#	define DLL_NAME					"CRMP_Trainer.asi"
#	define CRMP_MODULE_NAME			"samp.dll"
#else 
#	define DLL_NAME					"CRMP_Trainer.dll"
#	define CRMP_MODULE_NAME			"san_andreas_multiplayer.dll"
#endif

#define	TRAINER_VERSION				9
#define PATH_TO_CHECKING_SCRIPT		"https://litehack.ru/crmp_trainer/version.php"
#define PATH_TO_OFFICIAL_THREAD		"https://litehack.ru/threads/3275/"

// API/SDK 
#include <windows.h>
#include <wininet.h>
#include <stdint.h>
#include <process.h>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <d3dx9.h>
#include <d3d9.h>
#include <time.h>
#include <vector>
#include <memory>
#include <io.h>
#include <map>
#include <set>

// public SA classes
// try to always include these in the private class's header
#include <game/CGame.h>

// private SA classes
#include <CEntitySA.h>
#include <Common.h>
#include <CGameSA.h>
#include <CWorldSA.h>
#include <CPoolsSA.h>
#include <CClockSA.h>
#include <CFontSA.h>
#include <CRadarSA.h>
#include <CMenuManagerSA.h>
#include <CCameraSA.h>
#include <CCheckpointsSA.h>
#include <CRenderWareSA.h>
#include <CCoronasSA.h>
#include <CPickupsSA.h>
#include <CPathFindSA.h>
#include <CWeaponInfoSA.h>
#include <CExplosionManagerSA.h>
#include <CFireManagerSA.h>
#include <CHandlingManagerSA.h>
#include <CHudSA.h>
#include <C3DMarkersSA.h>
#include <CStatsSA.h>
#include <CTheCarGeneratorsSA.h>
#include <CPadSA.h>
#include <CAERadioTrackManagerSA.h>
#include <CWeatherSA.h>
#include <CTextSA.h>
#include <CPedSA.h>
#include <CPedSoundSA.h>
#include <CAudioSA.h>
#include <CPlayerInfoSA.h>
#include <CPopulationSA.h>
#include <CSettingsSA.h>
#include <CCarEnterExitSA.h>
#include <COffsets.h>
#include <CControllerConfigManagerSA.h>
#include <CProjectileInfoSA.h>
#include <CEventListSA.h>
#include <CGaragesSA.h>
#include <CTasksSA.h>
#include <CEventDamageSA.h>
#include <CEventGunShotSA.h>
#include <CEventGroupSA.h>
#include <CAnimManagerSA.h>
#include <CStreamingSA.h>
#include <CVisibilityPluginsSA.h>
#include <CKeyGenSA.h>
#include <CRopesSA.h>
#include <CFxSA.h>
#include <HookSystem.h>
#include <CModelInfoSA.h>
#include <CPedModelInfoSA.h>
#include <CColPointSA.h>
#include <CCivilianPedSA.h>
#include <CAnimBlendAssociationSA.h>
#include <CAnimBlendAssocGroupSA.h>
#include <CAnimBlendHierarchySA.h>
#include <CAnimBlendSequenceSA.h>
#include <CAnimBlendStaticAssociationSA.h>
#include <CAnimBlockSA.h>
#include <CAutomobileSA.h>
#include <CBikeSA.h>
#include <CBoatSA.h>
#include <CBmxSA.h>
#include <CQuadBikeSA.h>
#include <CMonsterTruckSA.h>
#include <CPlaneSA.h>
#include <CTrailerSA.h>
#include <CPlayerPedSA.h>
#include <CCivilianPedSA.h>
#include <CObjectSA.h>
#include <CBuildingSA.h>
#include <CRestartSA.h>
#include <CWaterManagerSA.h>
#include <CPedDamageResponseSA.h>
#include <CPedDamageResponseCalculatorSA.h>

using namespace std;

// ImGui
#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_dx9.h"

// d3d9
#include "d3d9\d3dhook.h"
#include "d3d9\d3drender.h"

// RakNet
#include <BitStream.h>
#include <RakClient.h>
#include <HookedRakClient.h>

// scripting
#include "scripting.h"

// ini file
#include <file.h>
#include "ini.h"

// hook
#include <memory_stuff.h>
#include <memory_hook.h>
#include <window_hook.h>

// Main
#include "samp.h"
#include "samp_cmds.h"
#include "misc.h"
#include "gta_struct.h"
#include "cheat.h"
#include "gta_func.h"
#include "gta_entry.h"
#include "menu.h"


