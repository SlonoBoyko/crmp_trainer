/*
		From m0d_s0beit
*/

#pragma once

// old vehicle_info vehicle types
#define VEHICLE_TYPE_CAR	0	/* + helicopters and planes */
#define VEHICLE_TYPE_BOAT	5
#define VEHICLE_TYPE_TRAIN	6
#define VEHICLE_TYPE_BIKE	9

#define VEHICLE_CLASS_CAR			0
#define VEHICLE_CLASS_CAR_FAST		1
#define VEHICLE_CLASS_HEAVY			2
#define VEHICLE_CLASS_HELI			3
#define VEHICLE_CLASS_AIRPLANE		4
#define VEHICLE_CLASS_BIKE			5
#define VEHICLE_CLASS_BOAT			6
#define VEHICLE_CLASS_MINI			7
#define VEHICLE_CLASS_TRAILER		8
#define VEHICLE_CLASS_COUNT			9

#define VEHICLE_LIST_ID_START		400
#define VEHICLE_LIST_SIZE			212

enum eClientVehicleType
{
	CLIENTVEHICLE_NONE,
	CLIENTVEHICLE_CAR,
	CLIENTVEHICLE_BOAT,
	CLIENTVEHICLE_TRAIN,
	CLIENTVEHICLE_HELI,
	CLIENTVEHICLE_PLANE,
	CLIENTVEHICLE_BIKE,
	CLIENTVEHICLE_MONSTERTRUCK,
	CLIENTVEHICLE_QUADBIKE,
	CLIENTVEHICLE_BMX,
	CLIENTVEHICLE_TRAILER
};

// upgrade model ids
#define VEHICLEUPGRADE_NITRO_5X		1008
#define VEHICLEUPGRADE_NITRO_2X		1009
#define VEHICLEUPGRADE_NITRO_10X	1010
#define VEHICLEUPGRADE_HYDRAULICS	1087

#define VEHICLE_UPGRADES_COUNT		194

struct weapon_entry
{
	int			id;
	int			slot;
	int			model_id;
	const char	*name;
};

const struct weapon_entry weapon_list[] =
{
	{ 0, 0, -1, "Fist" },
	{ 1, 0, 331, "Brass Knuckles" },
	{ 2, 1, 333, "Golf Club" },
	{ 3, 1, 334, "Nitestick" },
	{ 4, 1, 335, "Knife" },
	{ 5, 1, 336, "Baseball Bat" },
	{ 6, 1, 337, "Shovel" },
	{ 7, 1, 338, "Pool Cue" },
	{ 8, 1, 339, "Katana" },
	{ 9, 1, 341, "Chainsaw" },
	{ 22, 2, 346, "Pistol" },
	{ 23, 2, 347, "Silenced Pistol" },
	{ 24, 2, 348, "Desert Eagle" },
	{ 25, 3, 349, "Shotgun" },
	{ 26, 3, 350, "Sawn-Off Shotgun" },
	{ 27, 3, 351, "SPAZ12" },
	{ 28, 4, 352, "Micro UZI" },
	{ 29, 4, 353, "MP5" },
	{ 32, 4, 372, "Tech9" },
	{ 30, 5, 355, "AK47" },
	{ 31, 5, 356, "M4" },
	{ 33, 6, 357, "Country Rifle" },
	{ 34, 6, 358, "Sniper Rifle" },
	{ 35, 7, 359, "Rocket Launcher" },
	{ 36, 7, 360, "Heat Seeking RPG" },
	{ 37, 7, 361, "Flame Thrower" },
	{ 38, 7, 362, "Minigun" },
	{ 16, 8, 342, "Grenade" },
	{ 17, 8, 343, "Teargas" },
	{ 18, 8, 344, "Molotov Cocktail" },
	{ 39, 8, 363, "Remote Explosives" },
	{ 41, 9, 365, "Spray Can" },
	{ 42, 9, 366, "Fire Extinguisher" },
	{ 43, 9, 367, "Camera" },
	{ 10, 10, 321, "Dildo 1" },
	{ 11, 10, 322, "Dildo 2" },
	{ 12, 10, 323, "Vibe 1" },
	{ 13, 10, 324, "Vibe 2" },
	{ 14, 10, 325, "Flowers" },
	{ 15, 10, 326, "Cane" },
	{ 44, 11, 368, "NV Goggles" },
	{ 45, 11, 369, "IR Goggles" },
	{ 46, 11, 371, "Parachute" },
	{ 40, 12, 364, "Detonator" },
	{ -1, -1, -1, NULL }
};

struct vehicle_upgrade_info
{
	int			iModelID;				// iModelID
	const char	*upgradeCategoryName;	// upgrade name
	const char	*upgradeName;			// upgrade name
};

const struct vehicle_upgrade_info	cveh_upgrade_info[VEHICLE_UPGRADES_COUNT] =
{
	{ 1087, "Hydraulics", "System" },
	{ 1009, "Nitro", "2X" },
	{ 1008, "Nitro", "5X" },
	{ 1010, "Nitro", "10X" },
	{ 1086, "Stereo", "Subwoofer" },

	// used for Slamvan, but not in compatible list
	{ 1111, "Emblem", "#1" },
	{ 1112, "Emblem", "#2" },
	{ 1000, "Spoiler", "Pro" },
	{ 1001, "Spoiler", "Win" },
	{ 1002, "Spoiler", "Drag" },
	{ 1003, "Spoiler", "Alpha" },
	{ 1014, "Spoiler", "Champ" },
	{ 1015, "Spoiler", "Race" },
	{ 1016, "Spoiler", "Worx" },
	{ 1023, "Spoiler", "Fury" },
	{ 1049, "Spoiler", "Alien" },
	{ 1050, "Spoiler", "X-Flow" },
	{ 1058, "Spoiler", "Alien" },
	{ 1060, "Spoiler", "X-Flow" },
	{ 1138, "Spoiler", "Alien" },
	{ 1139, "Spoiler", "X-Flow" },
	{ 1147, "Spoiler", "Alien" },
	{ 1146, "Spoiler", "X-Flow" },
	{ 1162, "Spoiler", "Alien" },
	{ 1158, "Spoiler", "X-Flow" },
	{ 1164, "Spoiler", "Alien" },
	{ 1163, "Spoiler", "X-Flow" },
	{ 1004, "Hood", "Champ Scoop" },
	{ 1005, "Hood", "Fury Scoop" },
	{ 1011, "Hood", "Race Scoop" },
	{ 1012, "Hood", "Worx Scoop" },
	{ 1142, "Vents", "Oval Vents" },
	{ 1143, "Vents", "Oval Vents" },
	{ 1144, "Vents", "Square Vents" },
	{ 1145, "Vents", "Square Vents" },
	{ 1006, "Roof", "Roof Scoop" },
	{ 1032, "Roof", "Alien Roof Vent" },
	{ 1033, "Roof", "X-Flow Roof Vent" },
	{ 1038, "Roof", "Alien Roof Vent" },
	{ 1035, "Roof", "X-Flow Roof Vent" },
	{ 1054, "Roof", "Alien" },
	{ 1053, "Roof", "X-Flow" },
	{ 1055, "Roof", "Alien" },
	{ 1061, "Roof", "X-Flow" },
	{ 1067, "Roof", "Alien" },
	{ 1068, "Roof", "X-Flow" },
	{ 1088, "Roof", "Alien" },
	{ 1091, "Roof", "X-Flow" },
	{ 1103, "Roof", "Covertible" },
	{ 1128, "Roof", "Vinyl Hardtop" },
	{ 1130, "Roof", "Hardtop" },
	{ 1131, "Roof", "Softtop" },

	// Sultan
	{ 1169, "Front Bumper", "Alien" },
	{ 1170, "Front Bumper", "X-Flow" },
	{ 1141, "Rear Bumper", "Alien" },
	{ 1140, "Rear Bumper", "X-Flow" },

	// Elegy
	{ 1171, "Front Bumper", "Alien" },
	{ 1172, "Front Bumper", "X-Flow" },
	{ 1149, "Rear Bumper", "Alien" },
	{ 1148, "Rear Bumper", "X-Flow" },

	// Flash
	{ 1153, "Front Bumper", "Alien" },
	{ 1152, "Front Bumper", "X-Flow" },
	{ 1150, "Rear Bumper", "Alien" },
	{ 1151, "Rear Bumper", "X-Flow" },

	// Stratum
	{ 1155, "Front Bumper", "Alien" },
	{ 1157, "Front Bumper", "X-Flow" },
	{ 1154, "Rear Bumper", "Alien" },
	{ 1156, "Rear Bumper", "X-Flow" },

	// Jester
	{ 1160, "Front Bumper", "Alien" },
	{ 1173, "Front Bumper", "X-Flow" },
	{ 1159, "Rear Bumper", "Alien" },
	{ 1161, "Rear Bumper", "X-Flow" },

	// Uranus
	{ 1166, "Front Bumper", "Alien" },
	{ 1165, "Front Bumper", "X-Flow" },
	{ 1168, "Rear Bumper", "Alien" },
	{ 1167, "Rear Bumper", "X-Flow" },

	// Broadway
	{ 1174, "Front Bumper", "Chrome" },
	{ 1175, "Front Bumper", "Slamin" },
	{ 1176, "Rear Bumper", "Chrome" },
	{ 1177, "Rear Bumper", "Slamin" },

	// Remington
	{ 1179, "Front Bumper", "Chrome" },
	{ 1185, "Front Bumper", "Slamin" },
	{ 1180, "Rear Bumper", "Chrome" },
	{ 1178, "Rear Bumper", "Slamin" },

	// Blade
	{ 1182, "Front Bumper", "Chrome" },
	{ 1181, "Front Bumper", "Slamin" },
	{ 1184, "Rear Bumper", "Chrome" },
	{ 1183, "Rear Bumper", "Slamin" },

	// Savanna
	{ 1189, "Front Bumper", "Chrome" },
	{ 1188, "Front Bumper", "Slamin" },
	{ 1187, "Rear Bumper", "Chrome" },
	{ 1186, "Rear Bumper", "Slamin" },

	// Tornado
	{ 1191, "Front Bumper", "Chrome" },
	{ 1190, "Front Bumper", "Slamin" },
	{ 1192, "Rear Bumper", "Chrome" },
	{ 1193, "Rear Bumper", "Slamin" },

	// stock sideskirts
	{ 1017, "Sideskirt", "Standard" },
	{ 1007, "Sideskirt", "Standard" },

	// Sultan
	{ 1027, "Sideskirt", "Alien" },
	{ 1026, "Sideskirt", "Alien" },
	{ 1030, "Sideskirt", "X-Flow" },
	{ 1031, "Sideskirt", "X-Flow" },

	// Elgy
	{ 1040, "Sideskirt", "Alien" },
	{ 1036, "Sideskirt", "Alien" },
	{ 1039, "Sideskirt", "X-Flow" },
	{ 1041, "Sideskirt", "X-Flow" },

	// Broadway
	{ 1042, "Sideskirt", "Chrome" },
	{ 1099, "Sideskirt", "Chrome" },

	// Flash
	{ 1051, "Sideskirt", "Alien" },
	{ 1047, "Sideskirt", "Alien" },
	{ 1052, "Sideskirt", "X-Flow" },
	{ 1048, "Sideskirt", "X-Flow" },

	// Statum
	{ 1062, "Sideskirt", "Alien" },
	{ 1056, "Sideskirt", "Alien" },
	{ 1063, "Sideskirt", "X-Flow" },
	{ 1057, "Sideskirt", "X-Flow" },

	// Jester
	{ 1071, "Sideskirt", "Alien" },
	{ 1069, "Sideskirt", "Alien" },
	{ 1072, "Sideskirt", "X-Flow" },
	{ 1070, "Sideskirt", "X-Flow" },

	// Uranus
	{ 1094, "Sideskirt", "Alien" },
	{ 1090, "Sideskirt", "Alien" },
	{ 1093, "Sideskirt", "X-Flow" },
	{ 1095, "Sideskirt", "X-Flow" },

	// Remington
	{ 1101, "Sideskirt", "`Chrome Flames`" },
	{ 1122, "Sideskirt", "`Chrome Flames`" },
	{ 1124, "Sideskirt", "`Chrome Arches`" },
	{ 1106, "Sideskirt", "`Chrome Arches`" },

	// Savanna
	{ 1102, "Sideskirt", "`Chrome Strip`" },
	{ 1133, "Sideskirt", "`Chrome Strip`" },

	// Blade
	{ 1107, "Sideskirt", "`Chrome Strip`" },
	{ 1108, "Sideskirt", "`Chrome Strip`" },

	// Slamvan
	{ 1120, "Sideskirt", "`Chrome Trim`" },
	{ 1118, "Sideskirt", "`Chrome Trim`" },
	{ 1121, "Sideskirt", "`Wheelcovers`" },
	{ 1119, "Sideskirt", "`Wheelcovers`" },

	// Tornado
	{ 1137, "Sideskirt", "`Chrome Strip`" },
	{ 1134, "Sideskirt", "`Chrome Strip`" },
	{ 1018, "Exhaust", "Upswept" },
	{ 1019, "Exhaust", "Twin" },
	{ 1020, "Exhaust", "Large" },
	{ 1021, "Exhaust", "Medium" },
	{ 1022, "Exhaust", "Small" },
	{ 1028, "Exhaust", "Alien" },
	{ 1029, "Exhaust", "X-Flow" },
	{ 1034, "Exhaust", "Alien" },
	{ 1037, "Exhaust", "X-Flow" },
	{ 1043, "Exhaust", "Slamin" },
	{ 1044, "Exhaust", "Chrome" },
	{ 1045, "Exhaust", "X-Flow" },
	{ 1046, "Exhaust", "Alien" },
	{ 1059, "Exhaust", "X-Flow" },
	{ 1064, "Exhaust", "Alien" },
	{ 1065, "Exhaust", "Alien" },
	{ 1066, "Exhaust", "X-Flow" },
	{ 1089, "Exhaust", "X-Flow" },
	{ 1092, "Exhaust", "Alien" },
	{ 1104, "Exhaust", "Chrome" },
	{ 1105, "Exhaust", "Slamin" },
	{ 1113, "Exhaust", "Chrome" },
	{ 1114, "Exhaust", "Slamin" },
	{ 1126, "Exhaust", "Chrome Exhaust" },
	{ 1127, "Exhaust", "Slamin Exhaust" },
	{ 1129, "Exhaust", "Chrome" },
	{ 1132, "Exhaust", "Slamin" },
	{ 1135, "Exhaust", "Slamin" },
	{ 1136, "Exhaust", "Chrome" },
	{ 1100, "Bullbar", "Chrome Grill" },
	{ 1109, "Rear Bullbars", "Chrome" },
	{ 1110, "Rear Bullbars", "Slamin" },
	{ 1115, "Front Bullbars", "Chrome" },
	{ 1116, "Front Bullbars", "Slamin" },
	{ 1117, "Front Bumper", "Chrome" },
	{ 1123, "Bullbars", "Bullbar Chrome Bars" },
	{ 1125, "Bullbars", "Bullbar Chrome Lights" },
	{ 1013, "Lamps", "Round Fog" },
	{ 1024, "Lamps", "Square Fog" },
	{ 1025, "Wheels", "Offroad" },
	{ 1073, "Wheels", "Shadow" },
	{ 1074, "Wheels", "Mega" },
	{ 1075, "Wheels", "Rimshine" },
	{ 1076, "Wheels", "Wires" },
	{ 1077, "Wheels", "Classic" },
	{ 1078, "Wheels", "Twist" },
	{ 1079, "Wheels", "Cutter" },
	{ 1080, "Wheels", "Switch" },
	{ 1081, "Wheels", "Grove" },
	{ 1082, "Wheels", "Import" },
	{ 1083, "Wheels", "Dollar" },
	{ 1084, "Wheels", "Trance" },
	{ 1085, "Wheels", "Atomic" },
	{ 1096, "Wheels", "Ahab" },
	{ 1097, "Wheels", "Virtual" },
	{ 1098, "Wheels", "Access" }
};


struct vehicle_entry
{
	int			id;			// model id
	int			class_id;	// class id
	const char	*name;		// vehicle name
	int			passengers; // total passenger seats, 0-10
};

/* IDs must be sequential */
const struct vehicle_entry	vehicle_list[VEHICLE_LIST_SIZE] =
{	// model_id, vehicle class, vehicle name, passenger seats
	{ 400, VEHICLE_CLASS_CAR, "Landstalker", 3 },
	{ 401, VEHICLE_CLASS_CAR, "Bravura", 1 },
	{ 402, VEHICLE_CLASS_CAR_FAST, "Buffalo", 1 },
	{ 403, VEHICLE_CLASS_HEAVY, "Linerunner", 1 },
	{ 404, VEHICLE_CLASS_CAR, "Perennial", 3 },
	{ 405, VEHICLE_CLASS_CAR, "Sentinel", 3 },
	{ 406, VEHICLE_CLASS_HEAVY, "Dumper", 0 },
	{ 407, VEHICLE_CLASS_HEAVY, "Fire Truck", 1 },
	{ 408, VEHICLE_CLASS_HEAVY, "Trashmaster", 1 },
	{ 409, VEHICLE_CLASS_HEAVY, "Stretch", 3 },
	{ 410, VEHICLE_CLASS_CAR, "Manana", 1 },
	{ 411, VEHICLE_CLASS_CAR_FAST, "Infernus", 1 },
	{ 412, VEHICLE_CLASS_CAR, "Voodoo", 1 },
	{ 413, VEHICLE_CLASS_CAR, "Pony", 3 },
	{ 414, VEHICLE_CLASS_CAR, "Mule", 1 },
	{ 415, VEHICLE_CLASS_CAR_FAST, "Cheetah", 1 },
	{ 416, VEHICLE_CLASS_HEAVY, "Ambulance", 3 },
	{ 417, VEHICLE_CLASS_HELI, "Leviathan", 1 },
	{ 418, VEHICLE_CLASS_CAR, "Moonbeam", 3 },
	{ 419, VEHICLE_CLASS_CAR, "Esperanto", 1 },
	{ 420, VEHICLE_CLASS_CAR, "Taxi", 3 },
	{ 421, VEHICLE_CLASS_CAR, "Washington", 3 },
	{ 422, VEHICLE_CLASS_CAR, "Bobcat", 1 },
	{ 423, VEHICLE_CLASS_HEAVY, "Mr. Whoopee", 1 },
	{ 424, VEHICLE_CLASS_CAR, "BF Injection", 1 },
	{ 425, VEHICLE_CLASS_HELI, "Hunter", 0 },
	{ 426, VEHICLE_CLASS_CAR, "Premier", 3 },
	{ 427, VEHICLE_CLASS_HEAVY, "Enforcer", 3 },
	{ 428, VEHICLE_CLASS_HEAVY, "Securicar", 3 },
	{ 429, VEHICLE_CLASS_CAR_FAST, "Banshee", 1 },
	{ 430, VEHICLE_CLASS_BOAT, "Predator", 0 },
	{ 431, VEHICLE_CLASS_HEAVY, "Bus", 7 },
	{ 432, VEHICLE_CLASS_HEAVY, "Rhino", 0 },

	/* tank... */
	{ 433, VEHICLE_CLASS_HEAVY, "Barracks", 1 },
	{ 434, VEHICLE_CLASS_CAR_FAST, "Hotknife", 1 },
	{ 435, VEHICLE_CLASS_TRAILER, "Artict Trailer", 0 },
	{ 436, VEHICLE_CLASS_CAR, "Previon", 1 },
	{ 437, VEHICLE_CLASS_HEAVY, "Coach", 7 },
	{ 438, VEHICLE_CLASS_CAR, "Cabbie", 3 },
	{ 439, VEHICLE_CLASS_CAR_FAST, "Stallion", 1 },
	{ 440, VEHICLE_CLASS_CAR, "Rumpo", 3 },
	{ 441, VEHICLE_CLASS_MINI, "RC Bandit", 0 },
	{ 442, VEHICLE_CLASS_CAR, "Romero", 1 },
	{ 443, VEHICLE_CLASS_HEAVY, "Packer", 1 },
	{ 444, VEHICLE_CLASS_HEAVY, "Monster", 1 },
	{ 445, VEHICLE_CLASS_CAR, "Admiral", 3 },
	{ 446, VEHICLE_CLASS_BOAT, "Squalo", 0 },
	{ 447, VEHICLE_CLASS_HELI, "Seasparrow", 1 },
	{ 448, VEHICLE_CLASS_BIKE, "Pizza Boy", 0 },

	// needs to be researched to find actual max passengers in SA:MP
	{ 449, VEHICLE_CLASS_HEAVY, "Trolly", 1 },

	/* train... */
	{ 450, VEHICLE_CLASS_TRAILER, "Artict Trailer 2", 0 },
	{ 451, VEHICLE_CLASS_CAR_FAST, "Turismo", 1 },
	{ 452, VEHICLE_CLASS_BOAT, "Speeder", 0 },
	{ 453, VEHICLE_CLASS_BOAT, "Reefer", 0 },
	{ 454, VEHICLE_CLASS_BOAT, "Tropic", 0 },
	{ 455, VEHICLE_CLASS_HEAVY, "Flatbed", 1 },
	{ 456, VEHICLE_CLASS_HEAVY, "Yankee", 1 },
	{ 457, VEHICLE_CLASS_MINI, "Caddy", 1 },
	{ 458, VEHICLE_CLASS_CAR, "Solair", 3 },
	{ 459, VEHICLE_CLASS_HEAVY, "Berkley's RC Van", 3 },
	{ 460, VEHICLE_CLASS_AIRPLANE, "Skimmer", 1 },
	{ 461, VEHICLE_CLASS_BIKE, "PCJ-600", 1 },
	{ 462, VEHICLE_CLASS_BIKE, "Faggio", 1 },
	{ 463, VEHICLE_CLASS_BIKE, "Freeway", 1 },
	{ 464, VEHICLE_CLASS_MINI, "RC Baron", 0 },
	{ 465, VEHICLE_CLASS_MINI, "RC Raider", 0 },
	{ 466, VEHICLE_CLASS_CAR, "Glendale", 3 },
	{ 467, VEHICLE_CLASS_CAR, "Oceanic", 3 },
	{ 468, VEHICLE_CLASS_BIKE, "Sanchez", 1 },
	{ 469, VEHICLE_CLASS_HELI, "Sparrow", 1 },
	{ 470, VEHICLE_CLASS_CAR, "Patriot", 3 },
	{ 471, VEHICLE_CLASS_BIKE, "Quadbike", 1 },

	/* sort of.. */
	{ 472, VEHICLE_CLASS_BOAT, "Coastguard", 0 },
	{ 473, VEHICLE_CLASS_BOAT, "Dinghy", 0 },
	{ 474, VEHICLE_CLASS_CAR, "Hermes", 1 },
	{ 475, VEHICLE_CLASS_CAR, "Sabre", 1 },
	{ 476, VEHICLE_CLASS_AIRPLANE, "Rustler", 0 },
	{ 477, VEHICLE_CLASS_CAR_FAST, "ZR-350", 1 },
	{ 478, VEHICLE_CLASS_CAR, "Walton", 1 },
	{ 479, VEHICLE_CLASS_CAR, "Regina", 3 },
	{ 480, VEHICLE_CLASS_CAR_FAST, "Comet", 1 },
	{ 481, VEHICLE_CLASS_BIKE, "BMX", 0 },
	{ 482, VEHICLE_CLASS_HEAVY, "Burrito", 3 },

	// more research on this, the side door might allow 2 passengers
	{ 483, VEHICLE_CLASS_HEAVY, "Camper", 2 },
	{ 484, VEHICLE_CLASS_BOAT, "Marquis", 0 },
	{ 485, VEHICLE_CLASS_MINI, "Baggage", 0 },
	{ 486, VEHICLE_CLASS_HEAVY, "Dozer", 0 },
	{ 487, VEHICLE_CLASS_HELI, "Maverick", 3 },
	{ 488, VEHICLE_CLASS_HELI, "News Chopper", 1 },
	{ 489, VEHICLE_CLASS_CAR, "Rancher", 1 },
	{ 490, VEHICLE_CLASS_CAR, "FBI Rancher", 3 },
	{ 491, VEHICLE_CLASS_CAR, "Virgo", 1 },
	{ 492, VEHICLE_CLASS_CAR, "Greenwood", 3 },
	{ 493, VEHICLE_CLASS_BOAT, "Jetmax", 0 },
	{ 494, VEHICLE_CLASS_CAR_FAST, "Hotring Racer", 1 },
	{ 495, VEHICLE_CLASS_CAR, "Sandking", 1 },
	{ 496, VEHICLE_CLASS_CAR, "Blista Compact", 1 },
	{ 497, VEHICLE_CLASS_HELI, "Police Maverick", 3 },
	{ 498, VEHICLE_CLASS_HEAVY, "Boxville", 3 },
	{ 499, VEHICLE_CLASS_HEAVY, "Benson", 1 },
	{ 500, VEHICLE_CLASS_CAR, "Mesa", 1 },
	{ 501, VEHICLE_CLASS_MINI, "RC Goblin", 0 },
	{ 502, VEHICLE_CLASS_CAR_FAST, "Hotring Racer 2", 1 },
	{ 503, VEHICLE_CLASS_CAR_FAST, "Hotring Racer 3", 1 },
	{ 504, VEHICLE_CLASS_CAR_FAST, "Bloodring Banger", 1 },
	{ 505, VEHICLE_CLASS_CAR, "Rancher", 1 },
	{ 506, VEHICLE_CLASS_CAR_FAST, "Super GT", 1 },
	{ 507, VEHICLE_CLASS_CAR, "Elegant", 3 },
	{ 508, VEHICLE_CLASS_HEAVY, "Journey", 1 },
	{ 509, VEHICLE_CLASS_BIKE, "Bike", 0 },
	{ 510, VEHICLE_CLASS_BIKE, "Mountain Bike", 0 },
	{ 511, VEHICLE_CLASS_AIRPLANE, "Beagle", 1 },
	{ 512, VEHICLE_CLASS_AIRPLANE, "Cropduster", 0 },
	{ 513, VEHICLE_CLASS_AIRPLANE, "Stuntplane", 0 },
	{ 514, VEHICLE_CLASS_HEAVY, "Tanker", 1 },

	/* semi truck */
	{ 515, VEHICLE_CLASS_HEAVY, "Roadtrain", 1 },

	/* semi truck */
	{ 516, VEHICLE_CLASS_CAR, "Nebula", 3 },
	{ 517, VEHICLE_CLASS_CAR, "Majestic", 1 },
	{ 518, VEHICLE_CLASS_CAR, "Buccaneer", 1 },
	{ 519, VEHICLE_CLASS_AIRPLANE, "Shamal", 0 },
	{ 520, VEHICLE_CLASS_AIRPLANE, "Hydra", 0 },
	{ 521, VEHICLE_CLASS_BIKE, "FCR-900", 1 },
	{ 522, VEHICLE_CLASS_BIKE, "NRG-500", 1 },
	{ 523, VEHICLE_CLASS_BIKE, "HPV1000", 1 },
	{ 524, VEHICLE_CLASS_HEAVY, "Cement Truck", 1 },
	{ 525, VEHICLE_CLASS_HEAVY, "Towtruck", 1 },
	{ 526, VEHICLE_CLASS_CAR, "Fortune", 1 },
	{ 527, VEHICLE_CLASS_CAR, "Cadrona", 1 },
	{ 528, VEHICLE_CLASS_HEAVY, "FBI Truck", 1 },
	{ 529, VEHICLE_CLASS_CAR, "Willard", 3 },
	{ 530, VEHICLE_CLASS_MINI, "Forklift", 0 },
	{ 531, VEHICLE_CLASS_CAR, "Tractor", 0 },
	{ 532, VEHICLE_CLASS_HEAVY, "Combine Harvester", 0 },
	{ 533, VEHICLE_CLASS_CAR, "Feltzer", 1 },
	{ 534, VEHICLE_CLASS_CAR, "Remington", 1 },
	{ 535, VEHICLE_CLASS_CAR_FAST, "Slamvan", 1 },
	{ 536, VEHICLE_CLASS_CAR_FAST, "Blade", 1 },
	{ 537, VEHICLE_CLASS_HEAVY, "Freight", 1 },

	/* train engine... */
	{ 538, VEHICLE_CLASS_HEAVY, "Brown Streak Engine", 1 },

	/* train engine... */
	{ 539, VEHICLE_CLASS_BOAT, "Vortex", 0 },
	{ 540, VEHICLE_CLASS_CAR, "Vincent", 3 },
	{ 541, VEHICLE_CLASS_CAR_FAST, "Bullet", 1 },
	{ 542, VEHICLE_CLASS_CAR, "Clover", 1 },
	{ 543, VEHICLE_CLASS_CAR, "Sadler", 1 },
	{ 544, VEHICLE_CLASS_HEAVY, "Fire Truck with ladder", 1 },
	{ 545, VEHICLE_CLASS_CAR, "Hustler", 1 },
	{ 546, VEHICLE_CLASS_CAR, "Intruder", 3 },
	{ 547, VEHICLE_CLASS_CAR, "Primo", 3 },
	{ 548, VEHICLE_CLASS_HELI, "Cargobob", 1 },
	{ 549, VEHICLE_CLASS_CAR, "Tampa", 1 },
	{ 550, VEHICLE_CLASS_CAR, "Sunrise", 3 },
	{ 551, VEHICLE_CLASS_CAR, "Merit", 3 },
	{ 552, VEHICLE_CLASS_HEAVY, "Utility Van", 1 },
	{ 553, VEHICLE_CLASS_AIRPLANE, "Nevada", 0 },
	{ 554, VEHICLE_CLASS_CAR, "Yosemite", 1 },
	{ 555, VEHICLE_CLASS_CAR, "Windsor", 1 },
	{ 556, VEHICLE_CLASS_HEAVY, "Monster 2", 1 },
	{ 557, VEHICLE_CLASS_HEAVY, "Monster 3", 1 },
	{ 558, VEHICLE_CLASS_CAR_FAST, "Uranus", 1 },
	{ 559, VEHICLE_CLASS_CAR_FAST, "Jester", 1 },
	{ 560, VEHICLE_CLASS_CAR_FAST, "Sultan", 3 },
	{ 561, VEHICLE_CLASS_CAR, "Stratum", 3 },
	{ 562, VEHICLE_CLASS_CAR_FAST, "Elegy", 1 },
	{ 563, VEHICLE_CLASS_HELI, "Raindance", 1 },
	{ 564, VEHICLE_CLASS_MINI, "RC Tiger", 0 },
	{ 565, VEHICLE_CLASS_CAR, "Flash", 1 },
	{ 566, VEHICLE_CLASS_CAR, "Tahoma", 3 },
	{ 567, VEHICLE_CLASS_CAR, "Savanna", 3 },
	{ 568, VEHICLE_CLASS_CAR_FAST, "Bandito", 0 },
	{ 569, VEHICLE_CLASS_HEAVY, "Freight Train Flatbed", 0 },

	/* train car... */
	{ 570, VEHICLE_CLASS_HEAVY, "Brown Streak", 0 },

	/* train car... XXX dupe, streakc */
	{ 571, VEHICLE_CLASS_MINI, "Kart", 0 },
	{ 572, VEHICLE_CLASS_MINI, "Mower", 0 },
	{ 573, VEHICLE_CLASS_HEAVY, "Dune", 1 },
	{ 574, VEHICLE_CLASS_MINI, "Sweeper", 0 },
	{ 575, VEHICLE_CLASS_CAR, "Broadway", 1 },
	{ 576, VEHICLE_CLASS_CAR, "Tornado", 1 },
	{ 577, VEHICLE_CLASS_AIRPLANE, "AT-400", 0 },
	{ 578, VEHICLE_CLASS_HEAVY, "DFT-30", 1 },

	/* large flat-bed truck */
	{ 579, VEHICLE_CLASS_CAR, "Huntley", 3 },
	{ 580, VEHICLE_CLASS_CAR, "Stafford", 1 },
	{ 581, VEHICLE_CLASS_BIKE, "BF-400", 1 },
	{ 582, VEHICLE_CLASS_HEAVY, "News Van", 3 },
	{ 583, VEHICLE_CLASS_MINI, "Tug", 0 },
	{ 584, VEHICLE_CLASS_TRAILER, "Petrol Trailer", 0 },
	{ 585, VEHICLE_CLASS_CAR, "Emperor", 3 },
	{ 586, VEHICLE_CLASS_BIKE, "Wayfarer", 1 },
	{ 587, VEHICLE_CLASS_CAR_FAST, "Euros", 1 },
	{ 588, VEHICLE_CLASS_HEAVY, "Hotdog", 1 },
	{ 589, VEHICLE_CLASS_CAR, "Club", 1 },
	{ 590, VEHICLE_CLASS_HEAVY, "Freight Train Boxcar", 0 },

	/* train car... */
	{ 591, VEHICLE_CLASS_TRAILER, "Artict Trailer 3", 0 },
	{ 592, VEHICLE_CLASS_AIRPLANE, "Andromada", 0 },
	{ 593, VEHICLE_CLASS_AIRPLANE, "Dodo", 1 },
	{ 594, VEHICLE_CLASS_MINI, "RC Cam", 0 },
	{ 595, VEHICLE_CLASS_BOAT, "Launch", 0 },
	{ 596, VEHICLE_CLASS_CAR, "Police Car (LS)", 3 },
	{ 597, VEHICLE_CLASS_CAR, "Police Car (SF)", 3 },
	{ 598, VEHICLE_CLASS_CAR, "Police Car (LV)", 3 },
	{ 599, VEHICLE_CLASS_CAR, "Police Ranger", 1 },
	{ 600, VEHICLE_CLASS_CAR, "Picador", 1 },
	{ 601, VEHICLE_CLASS_HEAVY, "S.W.A.T.", 1 },
	{ 602, VEHICLE_CLASS_CAR_FAST, "Alpha", 1 },
	{ 603, VEHICLE_CLASS_CAR_FAST, "Phoenix", 1 },
	{ 604, VEHICLE_CLASS_CAR, "Damaged Glendale", 3 },
	{ 605, VEHICLE_CLASS_CAR, "Damaged Sadler", 1 },
	{ 606, VEHICLE_CLASS_TRAILER, "Baggage Trailer", 0 },
	{ 607, VEHICLE_CLASS_TRAILER, "Baggage Trailer 2", 0 },
	{ 608, VEHICLE_CLASS_TRAILER, "Tug Staircase", 0 },
	{ 609, VEHICLE_CLASS_HEAVY, "Black Boxville", 3 },
	{ 610, VEHICLE_CLASS_TRAILER, "Farm Trailer", 0 },
	{ 611, VEHICLE_CLASS_TRAILER, "Street Sweeper Trailer", 0 }
};

