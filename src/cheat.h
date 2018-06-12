/*
			AUTHOR: SlonoBoyko
			LiteHack.Ru
			21.05.2018
*/

#pragma once

#define COLOR_MSG_ERROR				D3DCOLOR_XRGB(0xFF, 0x30, 0x0)
#define COLOR_MSG_SUCCESS			D3DCOLOR_XRGB(0x30, 0xFF, 0x30)
#define COLOR_MSG_INFO				D3DCOLOR_XRGB(ini.color.base.red, ini.color.base.green, ini.color.base.blue)

struct global
{
	eCheatStates		state;
	int16_t				gameKeyState[32];
	bool				update_available;
	bool&				imcursor = ImGui::GetIO().MouseDrawCursor;
	
	bool				auto_save;
};

extern struct global	trainer;

void call_functions();
void func_reconnect();
void func_carshot();
void func_aafk();
void func_invisible();
void func_aimbot();
void func_air_break();
void func_good_mode();
void func_suicide();
void func_dialoghider();
void func_anti_bike_fall();
void func_improved_overview();
void func_spawn();
void func_procces_close();
void func_nospread();
void func_cargun();
void func_noreload();
void func_fast_connect();
void func_vehicle_speedhack();
void func_unfreze();
void func_noeject();
void func_repair_vehicle();
void func_clickwarp();
void func_fast_exit();
void func_quick_turn();
void func_skillmaster();
void func_pulse();
void func_pluscbug();
void func_engine_always_on();
void func_flooder();
void func_marker_teleport();
void func_keep_trailer();
void func_antifreze();
void func_antistun();
