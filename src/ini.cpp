/*
		AUTHOR: SlonoBoyko
		LiteHack.Ru
		21.05.2018
*/

#include <main.h>

string				file::ini::fname;
vector<string>		file::ini::strbuf;

struct ini_file		ini;

void create_ini_file()
{
	file::ini::align(0);

	file::ini::add("##### Кнопки #####");
	file::ini::add("key_enable_menu\t= 113\n");

	file::ini::add("key_dialoghider\t= 222");
	file::ini::add("key_good_mode\t= 45");
	file::ini::add("key_air_break\t= 161");
	file::ini::add("key_suicide\t= 114");
	file::ini::add("key_spawn\t= 55");
	file::ini::add("key_reconnect\t= 48");
	file::ini::add("key_skin_aimbot\t= 90");
	file::ini::add("key_ping_aimbot\t= 88");
	file::ini::add("key_speedhack\t= 164");
	file::ini::add("key_repair_vehicle\t= 49");
	file::ini::add("key_unfreze\t= 220");
	file::ini::add("key_fast_exit\t= 78");
	file::ini::add("key_click_warp\t= 4");
	file::ini::add("key_turn_right\t= 221");
	file::ini::add("key_turn_left\t= 219");
	file::ini::add("key_turn_back\t= 8");
	file::ini::add("key_unflip\t= 46\n");

	file::ini::align(1);

	file::ini::add("##### Интерфейс #####");
	file::ini::add("##### Цвета в формате ARGB #####");
	file::ini::add("color_trainer_base\t= 255\t0\t60\t255\n");

	file::ini::add("color_background_first\t= 120\t255\t160\t0");
	file::ini::add("color_background_second\t= 120\t0\t0\t255");
	file::ini::add("color_background_global\t= 120\t30\t30\t30");
	file::ini::add("color_background_items\t= 100\t10\t10\t10\n");

	file::ini::add("color_menu_text\t= 255\t230\t230\t230");
	file::ini::add("color_menu_title\t= 160\t0\t60\t255");
	file::ini::add("color_menu_elements\t= 100\t0\t60\t255");
	file::ini::add("color_menu_separators\t= 220\t0\t60\t255\n");

	file::ini::add("color_menu_active\t= 220\t255\t160\t0");
	file::ini::add("color_menu_hovered\t= 220\t0\t60\t255\n");

	

	file::ini::align(4);

	file::ini::add("##### Дефолтные значения #####");
	file::ini::add("reconnect_delay\t= 5");
	file::ini::add("carshot_speed\t= 100.0");
	file::ini::add("air_break_speed\t= 50.0");
	file::ini::add("normal_fov\t= 90.0\n");

	file::ini::add("speedhack_accel\t= 5.0");
	file::ini::add("speedhack_speed\t= 130.0\n");

	file::ini::add("##### Автологин #####");
	file::ini::add("enable_autologin\t= 0");
	file::ini::add("autologin_pass\t= qwerty123\n");

	file::ini::align(1);

	file::ini::add("##### Включенные функи при старте #####");
	file::ini::add("auto_save_settings\t = 1");
	file::ini::add("bottom_bar_enable\t= 1");
	file::ini::add("restore_windows_aero\t= 0");
	file::ini::add("enable_anti_bike_fall\t= 1");
	file::ini::add("enable_banyhop\t= 1");
	file::ini::add("enable_anti_afk\t= 0");
	file::ini::add("enable_improved_overview\t= 0");
	file::ini::add("enable_clear_screen\t= 1");
	file::ini::add("enable_chat_ids\t= 1");
	file::ini::add("enable_proccess_killer\t= 1");
	file::ini::add("enable_fast_connect\t= 1");
	file::ini::add("enable_auto_reconnect\t= 0");
	file::ini::add("enable_keep_trailer\t= 1");
	file::ini::add("enable_antifreeze\t= 1\n\n");

	file::ini::align(1);

	file::ini::add("##### Нопы отключающие пакеты и рпц #####");
	file::ini::add("##### Формат: \"Название\" Ид Автовключение\n");

	file::ini::add("##### Входящие РПЦ #####");
	file::ini::add("patch_incoming_rpc = \"ConnectionRejected\"\t13    \t0");
	file::ini::add("patch_incoming_rpc = \"ClientMessage\"\t14    \t0");
	file::ini::add("patch_incoming_rpc = \"SetWorldTime\"\t15    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerWeather\"\t19    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerSkin\"\t20    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerName\"\t21    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerPos\"\t22    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerPosFindZ\"\t23    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerHealth\"\t24    \t0");
	file::ini::add("patch_incoming_rpc = \"PutPlayerInVehicle\"\t25    \t0");
	file::ini::add("patch_incoming_rpc = \"RemovePlayerFromVehicle\"\t26    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerColor\"\t27    \t0");
	file::ini::add("patch_incoming_rpc = \"DisplayGameText\"\t28    \t0");
	file::ini::add("patch_incoming_rpc = \"ForceSpawnSelection\"\t29    \t0");
	file::ini::add("patch_incoming_rpc = \"AttachObjectToPlayer\"\t30    \t0");
	file::ini::add("patch_incoming_rpc = \"InitMenu\"\t31    \t0");
	file::ini::add("patch_incoming_rpc = \"ShowMenu\"\t32    \t0");
	file::ini::add("patch_incoming_rpc = \"HideMenu\"\t33    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerWantedLevel\"\t34    \t0");
	file::ini::add("patch_incoming_rpc = \"ShowTextDraw\"\t35    \t0");
	file::ini::add("patch_incoming_rpc = \"HideTextDraw\"\t36    \t0");
	file::ini::add("patch_incoming_rpc = \"EnableStuntBonus\"\t37    \t0");
	file::ini::add("patch_incoming_rpc = \"EditTextDraw\"\t38    \t0");
	file::ini::add("patch_incoming_rpc = \"AddGangZone\"\t39    \t0");
	file::ini::add("patch_incoming_rpc = \"PlayCrimeReportForPlayer\"\t43    \t0");
	file::ini::add("patch_incoming_rpc = \"PlayAudioStream\"\t45    \t0");
	file::ini::add("patch_incoming_rpc = \"StopAudioStreamForPlayer\"\t46    \t0");
	file::ini::add("patch_incoming_rpc = \"RemoveBuildingForPlayer\"\t47    \t0");
	file::ini::add("patch_incoming_rpc = \"CreateObject\"\t48    \t0");
	file::ini::add("patch_incoming_rpc = \"SetObjectPos\"\t49    \t0");
	file::ini::add("patch_incoming_rpc = \"SetObjectRotation\"\t50    \t0");
	file::ini::add("patch_incoming_rpc = \"DestroyObject\"\t51    \t0");
	file::ini::add("patch_incoming_rpc = \"CreateExplosion\"\t54    \t0");
	file::ini::add("patch_incoming_rpc = \"ShowNameTagForPlayer\"\t55    \t0");
	file::ini::add("patch_incoming_rpc = \"AttachCameraToObject\"\t56    \t0");
	file::ini::add("patch_incoming_rpc = \"ClickTextDraw\"\t58    \t0");
	file::ini::add("patch_incoming_rpc = \"GiveTakeDamage\"\t60    \t0");
	file::ini::add("patch_incoming_rpc = \"EditAttachedObject\"\t61    \t0");
	file::ini::add("patch_incoming_rpc = \"EditObject\"\t62    \t0");
	file::ini::add("patch_incoming_rpc = \"SelectObject\"\t63    \t0");
	file::ini::add("patch_incoming_rpc = \"CancelEdit\"\t64    \t0");
	file::ini::add("patch_incoming_rpc = \"WorldPlayerAdd\"\t69    \t0");
	file::ini::add("patch_incoming_rpc = \"SetShopName\"\t70    \t0");
	file::ini::add("patch_incoming_rpc = \"SetDrunkLevel\"\t72    \t0");
	file::ini::add("patch_incoming_rpc = \"SetChatBubble\"\t75    \t0");
	file::ini::add("patch_incoming_rpc = \"ShowDialog\"\t77    \t0");
	file::ini::add("patch_incoming_rpc = \"VehicleParams\"\t80    \t0");
	file::ini::add("patch_incoming_rpc = \"RemoveGangZone\"\t82    \t0");
	file::ini::add("patch_incoming_rpc = \"ClientJoin\"\t81    \t0");
	file::ini::add("patch_incoming_rpc = \"FlashGangZone\"\t83    \t0");
	file::ini::add("patch_incoming_rpc = \"StopFlashGangZone\"\t84    \t0");
	file::ini::add("patch_incoming_rpc = \"ApplyAnimation\"\t85    \t0");
	file::ini::add("patch_incoming_rpc = \"ClearAnimations\"\t86    \t0");
	file::ini::add("patch_incoming_rpc = \"SetSpecialAction\"\t87    \t0");
	file::ini::add("patch_incoming_rpc = \"SetFightingStyle\"\t88    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerVelocity\"\t89    \t0");
	file::ini::add("patch_incoming_rpc = \"SetVehicleVelocity\"\t90    \t0");
	file::ini::add("patch_incoming_rpc = \"MoveObject\"\t94    \t0");
	file::ini::add("patch_incoming_rpc = \"StopObject\"\t95    \t0");
	file::ini::add("patch_incoming_rpc = \"TogglePlayerSpectating\"\t97    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerSpectating\"\t98    \t0");
	file::ini::add("patch_incoming_rpc = \"PlayerSpectatePlayer\"\t99    \t0");
	file::ini::add("patch_incoming_rpc = \"PlayerSpectateVehicle\"\t100    \t0");
	file::ini::add("patch_incoming_rpc = \"UpdateScoresPingsIPs\"\t105    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerInterior\"\t106    \t0");
	file::ini::add("patch_incoming_rpc = \"SetCameraPos\"\t107    \t0");
	file::ini::add("patch_incoming_rpc = \"SetCameraLookAt\"\t108    \t0");
	file::ini::add("patch_incoming_rpc = \"SetVehiclePos\"\t109    \t0");
	file::ini::add("patch_incoming_rpc = \"SetVehicleZAngle\"\t110    \t0");
	file::ini::add("patch_incoming_rpc = \"SetVehicleParamsForPlayer\"\t111    \t0");
	file::ini::add("patch_incoming_rpc = \"SetCameraBehindPlayer\"\t112    \t0");
	file::ini::add("patch_incoming_rpc = \"TogglePlayerControllable\"\t113    \t0");
	file::ini::add("patch_incoming_rpc = \"PlaySound\"\t114    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerWorldBounds\"\t115    \t0");
	file::ini::add("patch_incoming_rpc = \"GivePlayerMoney\"\t116    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerFacingAngle\"\t117    \t0");
	file::ini::add("patch_incoming_rpc = \"ResetMoney\"\t118    \t0");
	file::ini::add("patch_incoming_rpc = \"ResetPlayerWeapons\"\t119    \t0");
	file::ini::add("patch_incoming_rpc = \"GivePlayerWeapon\"\t120    \t0");
	file::ini::add("patch_incoming_rpc = \"LinkVehicleToInterior\"\t122    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerArmour\"\t123    \t0");
	file::ini::add("patch_incoming_rpc = \"SetSpawnInfo\"\t125    \t0");
	file::ini::add("patch_incoming_rpc = \"SetPlayerTeam\"\t126    \t0");
	file::ini::add("patch_incoming_rpc = \"DeathMessage\"\t153    \t0");
	file::ini::add("patch_incoming_rpc = \"SetMapIcon\"\t154    \t0");
	file::ini::add("patch_incoming_rpc = \"DisableMapIcon\"\t155    \t0");
	file::ini::add("patch_incoming_rpc = \"SetGravity\"\t157    \t0");
	file::ini::add("patch_incoming_rpc = \"SetVehicleHealth\"\t158    \t0");
	file::ini::add("patch_incoming_rpc = \"AttachTrailerToVehicle\"\t159    \t0");
	file::ini::add("patch_incoming_rpc = \"DetachTrailerFromVehicle\"\t160    \t0");
	file::ini::add("patch_incoming_rpc = \"AddVehicleComponent\"\t161    \t0\n");

	file::ini::align(2);


	file::ini::add("##### Исходящие РПЦ #####");
	file::ini::add("patch_outcoming_rpc = \"ServerCommand\"\t6    \t0");
	file::ini::add("patch_outcoming_rpc = \"SetInteriorId\"\t7    \t0");
	file::ini::add("patch_outcoming_rpc = \"MapMarker\"\t8    \t0");
	file::ini::add("patch_outcoming_rpc = \"VehicleDestroyed\"\t9    \t0");
	file::ini::add("patch_outcoming_rpc = \"ServerJoin\"\t10    \t0");
	file::ini::add("patch_outcoming_rpc = \"ServerQuit\"\t11    \t0");
	file::ini::add("patch_outcoming_rpc = \"InitGame\"\t12    \t0");
	file::ini::add("patch_outcoming_rpc = \"ClickTextDraw\"\t58    \t0");
	file::ini::add("patch_outcoming_rpc = \"GiveTakeDamage\"\t60    \t0");
	file::ini::add("patch_outcoming_rpc = \"WorldPlayerAdd\"\t69    \t0");
	file::ini::add("patch_outcoming_rpc = \"DialogResponse\"\t78    \t0");
	file::ini::add("patch_outcoming_rpc = \"ClickPlayer\"\t79    \t0");
	file::ini::add("patch_outcoming_rpc = \"PlayerSpectatePlayer\"\t99    \t0");
	file::ini::add("patch_outcoming_rpc = \"PlayerSpectateVehicle\"\t100    \t0");
	file::ini::add("patch_outcoming_rpc = \"RequestClass\"\t101    \t0");
	file::ini::add("patch_outcoming_rpc = \"RequestSpawn\"\t102    \t0");
	file::ini::add("patch_outcoming_rpc = \"EnterVehicle\"\t103    \t0");
	file::ini::add("patch_outcoming_rpc = \"ExitVehicle\"\t104    \t0");
	file::ini::add("patch_outcoming_rpc = \"UpdateScoresPingsIPs\"\t105    \t0");
	file::ini::add("patch_outcoming_rpc = \"WorldPlayerRemove\"\t127    \t0");
	file::ini::add("patch_outcoming_rpc = \"WorldVehicleAdd\"\t128    \t0");
	file::ini::add("patch_outcoming_rpc = \"WorldVehicleRemove\"\t129    \t0");
	file::ini::add("patch_outcoming_rpc = \"WorldPlayerDeath\"\t130    \t0");
	file::ini::add("patch_outcoming_rpc = \"DamageVehicle\"\t131    \t0");
	file::ini::add("patch_outcoming_rpc = \"GameModeRestart\"\t136    \t0");
	file::ini::add("patch_outcoming_rpc = \"Chat\"\t138    \t0");
	file::ini::add("patch_outcoming_rpc = \"ScmEvent\"\t140    \t0");
	file::ini::add("patch_outcoming_rpc = \"PickedUpPickup\"\t142    \t0");
	file::ini::add("patch_outcoming_rpc = \"MenuSelect\"\t143    \t0");
	file::ini::add("patch_outcoming_rpc = \"MenuQuit\"\t144    \t0");
	file::ini::add("patch_outcoming_rpc = \"Spawn\"\t150    \t0");
	file::ini::add("patch_outcoming_rpc = \"Death\"\t151    \t0");
	file::ini::add("patch_outcoming_rpc = \"NPCJoin\"\t152    \t0\n");

	file::ini::align(2);

	file::ini::add("##### Входящие пакеты #####");
	file::ini::add("patch_incoming_packet = \"Authentication\"\t12    \t0");
	file::ini::add("patch_incoming_packet = \"ConnectionAccepted\"\t34    \t0");
	file::ini::add("patch_incoming_packet = \"ConnectionAttemptFailed\"\t29    \t0");
	file::ini::add("patch_incoming_packet = \"InvalidPassword\"\t37    \t0");
	file::ini::add("patch_incoming_packet = \"ConnectionLost\"\t33    \t0");
	file::ini::add("patch_incoming_packet = \"ConnectionClosed\"\t32    \t0");
	file::ini::add("patch_incoming_packet = \"NoFreeConnections\"\t31    \t0");
	file::ini::add("patch_incoming_packet = \"ConnectionBanned\"\t35    \t0");
	file::ini::add("patch_incoming_packet = \"UnoccupiedData\"\t110    \t0");
	file::ini::add("patch_incoming_packet = \"MarkersData\"\t111    \t0");
	file::ini::add("patch_incoming_packet = \"WeaponData\"\t112    \t0");
	file::ini::add("patch_incoming_packet = \"TrailerData\"\t114    \t0");
	file::ini::add("patch_incoming_packet = \"PassengerData\"\t115    \t0");
	file::ini::add("patch_incoming_packet = \"PlayerData\"\t116    \t0");
	file::ini::add("patch_incoming_packet = \"AimData\"\t117    \t0");
	file::ini::add("patch_incoming_packet = \"VehicleData\"\t118    \t0\n");

	file::ini::align(2);

	file::ini::add("##### Исходящие пакеты #####");
	file::ini::add("patch_outcoming_packet = \"Authentication\"\t12    \t0");
	file::ini::add("patch_outcoming_packet = \"UnoccupiedData\"\t110    \t0");
	file::ini::add("patch_outcoming_packet = \"MarkersData\"\t111    \t0");
	file::ini::add("patch_outcoming_packet = \"WeaponData\"\t112    \t0");
	file::ini::add("patch_outcoming_packet = \"SpectatingData\"\t113    \t0");
	file::ini::add("patch_outcoming_packet = \"TrailerData\"\t114    \t0");
	file::ini::add("patch_outcoming_packet = \"PassengerData\"\t115    \t0");
	file::ini::add("patch_outcoming_packet = \"PlayerData\"\t116    \t0");
	file::ini::add("patch_outcoming_packet = \"AimData\"\t117    \t0");
	file::ini::add("patch_outcoming_packet = \"VehicleData\"\t118    \t0\n");

	file::ini::align(2);

	file::ini::add("##### Флудер в чат #####");
	file::ini::add("flood_delay = 1.5");
	file::ini::add("flood_string = \"Запущен флудер.\"");
	file::ini::add("flood_string = \"В ини файле можно указать свои строки,которые будут флудить в чат.\"");
	file::ini::add("flood_string = \"Еще это можно сделать через меню.\"");
	file::ini::add("flood_string = \"Флудер поддерживает до 64 строки. И по 144 символов в каждой строке.\"");
	file::ini::add("flood_string = \"Так же флудер умеет вводить в чат команды.\"\n");

	file::ini::align(1);

	file::ini::add("##### Смена сервера #####");
	file::ini::add("##### Формат:	\"Название сервера\"\t\"IP адрес\"    \tПорт");
	file::ini::add("change_server = \"Amazing RP 1\"    \t\"5.254.104.13\"    \t8904");
	file::ini::add("change_server = \"Amazing RP 2\"    \t\"5.254.104.14\"    \t8904");
	file::ini::add("change_server = \"Amazing RP 3\"    \t\"5.254.104.12\"    \t8904");
	file::ini::add("change_server = \"Amazing RP 4\"    \t\"5.254.104.4\"    \t8904");
	file::ini::add("change_server = \"Amazing RP 5\"    \t\"5.254.104.5\"    \t8904");
	file::ini::add("change_server = \"Amazing RP 6\"    \t\"5.254.104.6\"    \t8904");
	file::ini::add("change_server = \"Amazing RP 7\"    \t\"5.254.124.37\"    \t8904");
	file::ini::add("change_server = \"CR-RP | Server I  \"    \t\"5.254.105.216\"    \t8904");
	file::ini::add("change_server = \"CR-RP | Server II \"    \t\"5.254.105.218\"    \t8904");
	file::ini::add("change_server = \"CR-RP | Server III\"    \t\"5.254.105.219\"    \t8904");
	file::ini::add("change_server = \"CR-RP | Server IV \"    \t\"5.254.105.220\"    \t8904");
	file::ini::add("change_server = \"Radmir RP 1\"    \t\"193.70.127.188\"    \t7777");
	file::ini::add("change_server = \"Radmir RP 2\"    \t\"193.70.127.189\"    \t7777");
	file::ini::add("change_server = \"Radmir RP 3\"    \t\"5.254.124.35\"     \t8904");
	file::ini::add("change_server = \"Radmir RP 4\"    \t\"5.254.124.36\"    \t8904");
	file::ini::add("change_server = \"GTA RolePlay 1\"    \t\"5.254.104.8\"    \t8904");
	file::ini::add("change_server = \"GTA RolePlay 2\"    \t\"5.254.104.9\"    \t8904");
	file::ini::add("change_server = \"GTA RolePlay 3\"    \t\"5.254.104.7\"    \t8904");
	file::ini::add("change_server = \"GTA RolePlay 4\"    \t\"5.254.104.2\"    \t8904");

	file::ini::align(2);

	//if (access(szIniFileName, 2) != -1)
	//	return;

	file::ini::write();
}

void get_ini_file_settings()
{
	file::ini(string(szIniFileName));

	if (!FileExists(szIniFileName) || !file::ini::read())
		create_ini_file();

	// keys
	file::ini::get("key_enable_menu", ini.key.menu);

	file::ini::get("key_dialoghider", ini.key.dialoghider);
	file::ini::get("key_good_mode", ini.key.good_mode);
	file::ini::get("key_air_break", ini.key.air_break);
	file::ini::get("key_suicide", ini.key.suicide);
	file::ini::get("key_spawn", ini.key.spawn);
	file::ini::get("key_reconnect", ini.key.reconnect);
	file::ini::get("key_ping_aimbot", ini.key.ping_aimbot);
	file::ini::get("key_skin_aimbot", ini.key.skin_aimbot);
	file::ini::get("key_speedhack", ini.key.speedhack);
	file::ini::get("key_repair_vehicle", ini.key.repair);
	file::ini::get("key_unfreze", ini.key.unfreze);
	file::ini::get("key_fast_exit", ini.key.fast_exit);
	file::ini::get("key_turn_right", ini.key.turn_right);
	file::ini::get("key_turn_left", ini.key.turn_left);
	file::ini::get("key_turn_back", ini.key.turn_back);
	file::ini::get("key_unflip", ini.key.unflip);
	file::ini::get("key_click_warp", ini.key.click_warp);

	// color
	file::ini::get("color_trainer_base", ini.color.base.alpha, ini.color.base.red, ini.color.base.green, ini.color.base.blue);

	file::ini::get("color_background_first", ini.color.bgnd_first.alpha, ini.color.bgnd_first.red, ini.color.bgnd_first.green, ini.color.bgnd_first.blue);
	file::ini::get("color_background_second", ini.color.bgnd_second.alpha, ini.color.bgnd_second.red, ini.color.bgnd_second.green, ini.color.bgnd_second.blue);
	file::ini::get("color_background_global", ini.color.bgnd_global.alpha, ini.color.bgnd_global.red, ini.color.bgnd_global.green, ini.color.bgnd_global.blue);
	file::ini::get("color_background_items", ini.color.bgnd_items.alpha, ini.color.bgnd_items.red, ini.color.bgnd_items.green, ini.color.bgnd_items.blue);

	file::ini::get("color_menu_text", ini.color.text.alpha, ini.color.text.red, ini.color.text.green, ini.color.text.blue);
	file::ini::get("color_menu_title", ini.color.title.alpha, ini.color.title.red, ini.color.title.green, ini.color.title.blue);
	file::ini::get("color_menu_elements", ini.color.elements.alpha, ini.color.elements.red, ini.color.elements.green, ini.color.elements.blue);
	file::ini::get("color_menu_separators", ini.color.separators.alpha, ini.color.separators.red, ini.color.separators.green, ini.color.separators.blue);

	file::ini::get("color_menu_active", ini.color.active.alpha, ini.color.active.red, ini.color.active.green, ini.color.active.blue);
	file::ini::get("color_menu_hovered", ini.color.hovered.alpha, ini.color.hovered.red, ini.color.hovered.green, ini.color.hovered.blue);


	// delays
	file::ini::get("reconnect_delay", ini.reconnect_delay);
	file::ini::get("carshot_speed", ini.carshot_speed);
	file::ini::get("air_break_speed", ini.air_break_speed);
	file::ini::get("normal_fov", ini.normal_fov);
	file::ini::get("speedhack_accel", ini.acceleration);
	file::ini::get("speedhack_speed", ini.max_speed);

	// alogin
	file::ini::get("enable_autologin", menu.autologin);
	file::ini::get("autologin_pass", ini.autologin_pass);

	// auto enable
	file::ini::get("auto_save_settings", trainer.auto_save);

	file::ini::get("bottom_bar_enable", menu.bottom_bar);
	file::ini::get("restore_windows_aero", menu.restore_aero);

	file::ini::get("enable_anti_bike_fall", menu.bike_fall);
	file::ini::get("enable_banyhop", menu.banyhop);
	file::ini::get("enable_anti_afk", menu.aafk);
	file::ini::get("enable_improved_overview", menu.improved_overview);
	file::ini::get("enable_clear_screen", menu.clear_screen);
	file::ini::get("enable_chat_ids", menu.chat_ids);
	file::ini::get("enable_proccess_killer", menu.proccess_killer);
	file::ini::get("enable_fast_connect", menu.fast_connect);
	file::ini::get("enable_auto_reconnect", menu.autoreconnect);
	file::ini::get("enable_keep_trailer", menu.keep_trailer);
	file::ini::get("enable_antifreeze", menu.antifreeze);

	ini.patch_cnt = 0;
	while (file::ini::get("patch_incoming_rpc", ini.patch[ini.patch_cnt].name,
		ini.patch[ini.patch_cnt].id, ini.patch[ini.patch_cnt].enabled))
		ini.patch[ini.patch_cnt++].type = INCOMING_RPC;

	while (file::ini::get("patch_outcoming_rpc", ini.patch[ini.patch_cnt].name,
		ini.patch[ini.patch_cnt].id, ini.patch[ini.patch_cnt].enabled))
		ini.patch[ini.patch_cnt++].type = OUTCOMING_RPC;

	while (file::ini::get("patch_incoming_packet", ini.patch[ini.patch_cnt].name,
		ini.patch[ini.patch_cnt].id, ini.patch[ini.patch_cnt].enabled))
		ini.patch[ini.patch_cnt++].type = INCOMING_PACKET;

	while (file::ini::get("patch_outcoming_packet", ini.patch[ini.patch_cnt].name,
		ini.patch[ini.patch_cnt].id, ini.patch[ini.patch_cnt].enabled))
		ini.patch[ini.patch_cnt++].type = OUTCOMING_PACKET;

	file::ini::get("flood_delay", ini.flood_delay);

	string str_buffer;
	while (file::ini::get("flood_string", str_buffer))
		ini.flood_string.push_back(str_buffer);

	struct server buffer;
	while (file::ini::get("change_server", buffer.strHostname, buffer.strIP, buffer.ulPort))
		ini.servers.push_back(buffer);
}