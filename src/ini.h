/*
		AUTHOR: SlonoBoyko
		LiteHack.Ru
		21.05.2018
*/

#pragma once
 
struct net_patch
{
	int				id;
	string			name;
	int				type;
	bool			enabled;
};

struct server
{
	uint32_t		ulPort;
	string			strIP;
	string			strHostname;
};

struct trainer_key
{
	uint32_t menu;

	uint32_t good_mode;
	uint32_t dialoghider;
	uint32_t air_break;
	uint32_t suicide;
	uint32_t spawn;
	uint32_t reconnect;
	uint32_t skin_aimbot;
	uint32_t ping_aimbot;
	uint32_t speedhack;
	uint32_t unfreze;
	uint32_t repair;
	uint32_t fast_exit;
	uint32_t click_warp;

	uint32_t turn_right;
	uint32_t turn_left;
	uint32_t turn_back;
	uint32_t unflip;
};

struct menu_color
{
	uint8_t alpha, red, green, blue;
};

struct bar_colors 
{
	struct menu_color	bgnd_first;
	struct menu_color	bgnd_second;
	struct menu_color	bgnd_global;
	struct menu_color	bgnd_items;

	struct menu_color	text;
	struct menu_color	title;
	struct menu_color	elements;
	struct menu_color	hovered;
	struct menu_color	active;
	struct menu_color	separators;

	struct menu_color	base;
	
	
	
};

struct ini_file
{

	int							reconnect_delay;
	float						carshot_speed;
	float						air_break_speed;
	float						acceleration;
	float						max_speed;
	float						normal_fov;
	char						autologin_pass[260];
	struct trainer_key			key;
	struct net_patch			patch[RAKNET_MAX_PACKET];
	size_t						patch_cnt;
	struct bar_colors			color;
	float						flood_delay;
	vector<string>				flood_string;
	vector<server>				servers;
	
}; 
extern struct ini_file ini;

void		create_ini_file();
void		get_ini_file_settings();