#pragma once

#define MAX_SCRIPT_VARS 16              // Size of our variable saving array
#define MAX_SCRIPT_SIZE 255             // Size of ScriptBuf - Max is really (2+(13*5))

struct GAME_SCRIPT_THREAD               // 0xE0 bytes total.
{
	void	*pNext;
	void	*pPrev;
	char	szName[8];
	char	*pBaseIP;
	char	*pCurrentIP;
	char	*apStack[8];
	short	nSP;
	BYTE	Pad1[0x02];
	DWORD   dwLocalVar[18];					// 0x3C [0x48]
	int		anTimers[2];
	BYTE    Pad3[0x39];                     // 0x84 [0x41]
	DWORD   dwIfFlag;                       // 0xC5 [0x04]
	BYTE    Pad4[0xF];                      // 0xC9 [0x0F]
	DWORD   dwIndexSomething;				// 0xD8 [0x04]  (indexes into 0xA49960)
	BYTE    bHasLocalCopy;					// 0xDC [0x01]  (has local copy of something, if 1, then uses .data:00A48960 CTheScripts_LocalCopy instead of var0)
	BYTE    Pad5[0x3];                      // 0xDD [0x03]
}; 

struct SCRIPT_COMMAND						//				Params: i = integer, f = float, v = variable, s = string
{											
	WORD    OpCode;							
	char    Params[MAX_SCRIPT_VARS];        
};											

void                                    InitScripting();
void									UnInitScripting();
int                                     ScriptCommand(const SCRIPT_COMMAND *pScriptCommand, ...);

const SCRIPT_COMMAND    toggle_player_controllable = { 0x01B4, "ii" };
const SCRIPT_COMMAND    lock_actor = { 0x04D7, "ii" };
const SCRIPT_COMMAND    actor_put_at = { 0x00A1, "ifff" };
const SCRIPT_COMMAND    put_actor_in_car = { 0x036A, "ii" };
const SCRIPT_COMMAND    put_actor_in_car_passenger = { 0x0430, "iii" };
const SCRIPT_COMMAND    restore_camera_with_jumpcut = { 0x02EB, "" };
const SCRIPT_COMMAND    set_camera_directly_behind = { 0x0373, "" };
const SCRIPT_COMMAND    remove_actor_from_car_and_put_at = { 0x0362, "ifff" };
const SCRIPT_COMMAND    apply_momentum_in_direction_XYZ = { 0x07D5, "iffffff" };
const SCRIPT_COMMAND    apply_rotory_pulse_about_an_axis_XYZ = { 0x07DA, "ifff" };
const SCRIPT_COMMAND    repair_car = { 0x0A30, "i" };
const SCRIPT_COMMAND    get_actor_car = { 0x03C0, "iv" };
const SCRIPT_COMMAND    camera_on_actor = { 0x0159, "iii" };
const SCRIPT_COMMAND    camera_on_vehicle = { 0x0158, "iii" };
const SCRIPT_COMMAND    put_trailer_on_cab = { 0x0893, "ii" };	// 0893: put_trailer 37@ on_cab 34@
const SCRIPT_COMMAND    enter_car_as_driver = { 0x05CB, "iii" };
const SCRIPT_COMMAND    set_car_lights = { 0x067F, "ii" };
const SCRIPT_COMMAND	player_perform_animation_at_x_times_normal_rate = { 0x0393, "isf" }; // 0393=3,actor %1d% perform_animation %2h% at %3d% times_normal_rate
const SCRIPT_COMMAND	play_sound = { 0x018C , "fffi" };
const SCRIPT_COMMAND	write_memory = { 0x0A8C, "iiii" };		// 0A8C=4,write_memory %1d% size %2d% value %3d% virtual_protect %4d%
const SCRIPT_COMMAND    set_camera_zoom = { 0x0922, "ffii" };	// 0922: set_camera_zoom_from 101.0 to 1.0 timelimit 3500 smooth_transition 1
const SCRIPT_COMMAND	get_camera_pos = { 0x068D, "fff" };		// 068D: get_camera_position_to 1@ 2@ 3@
const SCRIPT_COMMAND	give_weapon = { 0x01B2, "iii" };		// 01B2=3,give_actor %1d% weapon %2d% ammo %3d%  ;
const SCRIPT_COMMAND	show_text_highpriority = { 0x0ACD, "si" };			// 0ACD: show_text_highpriority 0x969110 time 100
const SCRIPT_COMMAND	show_styled_text = { 0x0ACB, "sii" };		// 0ACB=3,show_styled_text %1s% time %2d% style %3d%
const SCRIPT_COMMAND	set_car_collision = { 0x099A, "ii" };		// 099A: set_car $CAR collision_detection 0
const SCRIPT_COMMAND    set_stun = { 0x0946, "ii" };