/*
			AUTHOR: SlonoBoyko
			LiteHack.Ru
			21.05.2018
*/

#include "main.h"

namespace cmd
{
	void dgun(char *params)
	{
		int iWeaponID, iAmmo;
		if (pCRMP->getPlayers()->pLocalPlayer == NULL) return;

		GTAfunc_loadAllWeaponModels();

		if (!strlen(params) || sscanf(params, "%d%d", &iWeaponID, &iAmmo) < 2)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /dgun [ИД оружия] [Количество патронов]");
		if (iWeaponID < 0 || iWeaponID > 46)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Ошибка! Ид оружия должен быть от 0 до 46");

		pPedSelf->GiveWeapon((eWeaponType)iWeaponID, iAmmo);

	}

	void boom(char *params)
	{
		if (!strlen(params)) {
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите: /boom [PlayerID]");
		}
		int playerid = atoi(params); float * pos;

		if (pCRMP->getVehicles() == NULL || pCRMP->getPlayers() == NULL) return;

		if (pCRMP->getPlayers()->iIsListed[playerid] != 1)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Такого игрока нет");

		if (pCRMP->getPlayers()->pRemotePlayer[playerid]->pPlayerData == NULL ||
			pCRMP->getPlayers()->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor == NULL)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Игрок не в стриме");

		if ((pos = *pCRMP->getPlayers()->getPlayerPos(playerid)) == NULL)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Такого игрока нет");

		int nearest = pCRMP->getVehicles()->findNearestVehicle();
		if (nearest && !pCRMP->getVehicles()->isBadVehicle(nearest))
		{
			vehicle_info *vinfo = pCRMP->getVehicles()->getGTAVehicle(nearest);
			if (vinfo != NULL && vinfo->driver == NULL)
			{
				vect3_copy(pos, &vinfo->base.matrix[4 * 3]);
				pCRMP->getRakClient()->SendEnterVehicle(nearest, 0);
				pCRMP->getRakClient()->SendFakeDriverSyncData(nearest, pos, vinfo->hitpoints = 0.0f, vinfo->speed);
			}
		}
		return;
	}

	void cchat(char *params)
	{
		if (pCRMP->getChat() == nullptr) return;

		pCRMP->getChat()->clearChat();
		return;
	}

	void warp(char *params)
	{
		if (pCRMP->getPlayers() == nullptr) return;

		if (!strlen(params))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите: /goto [PlayerID]");

		int playerid = atoi(params); float * pos;
		if (pCRMP->getPlayers()->iIsListed[playerid] != 1)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Такого игрока нет");
		if (pCRMP->getPlayers()->pRemotePlayer[playerid]->pPlayerData == NULL ||
			pCRMP->getPlayers()->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor == NULL)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Игрок не в стриме");
		if ((pos = *pCRMP->getPlayers()->getPlayerPos(playerid)) == NULL)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Такого игрока нет");

		actor_info *actor = pCRMP->getPlayers()->getGTAPed(playerid);
		pos[0] -= sinf(-actor->fCurrentRotation) * 2.0f;
		pos[1] -= cosf(-actor->fCurrentRotation) * 2.0f;
		pos[2] = pGame->GetWorld()->FindGroundZForPosition(pos[0], pos[1]) + 1.f;
		gta_teleport(pos);

		return;
	}

	void pickup(char *params)
	{
		if (!strlen(params))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите: /sendpic [ПикапID]");

		int iPickupID = atoi(params); float coords[3];
		if (pCRMP->getInfo()->pPools.pPickup == NULL) return;
		if (pCRMP->getInfo()->pPools.pPickup->iPickupID[iPickupID] == NULL) return;
		if (pCRMP->getInfo()->pPools.pPickup->ul_GTA_PickupID[iPickupID] == NULL) return;
		vect3_copy(pCRMP->getInfo()->pPools.pPickup->pickup[iPickupID].fPosition, coords);

		pCRMP->getRakClient()->SendFakeOnfootSyncData(coords, pPedSelf->GetHealth(), CVector());
		pCRMP->getRakClient()->SendPickUp(iPickupID);

		return;
	}

	void gotocheck(char *params)
	{
		float markerPos[3];
		if (!gta_world_marker_get(markerPos))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Активного маркера не обнаружено.");

		gta_teleport(markerPos);
	}

	void sendcheck(char *params)
	{
		float markerPos[3];
		if (!gta_world_marker_get(markerPos))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Активного маркера не обнаружено.");

		struct actor_info *info = actor_info_get(ACTOR_SELF);
		pCRMP->getRakClient()->SendFakeOnfootSyncData(markerPos, info->hitpoints, info->speed);

	}

	void nick(char *params)
	{
		if (!strlen(params))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /nick [Новое имя]");

		pCRMP->getPlayers()->setLocalPlayerName(params);
		menu.reconnect = true;
	}

	void scar(char *params)
	{
		if (!strlen(params))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /scar [ИД кара]");

		int carid = atoi(params);
		if (pCRMP->getVehicles()->iIsListed[carid] != 1)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Такого автомобиля не существует!");
		if (carid == pCRMP->getPlayers()->pLocalPlayer->sCurrentVehicleID)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Это ваш автомобиль!");

		pCRMP->getRakClient()->SendVehicleDestroyed(carid);
	}

	void vadd(char *params)
	{
		int model = 0, color_0 = 0, color_1 = 0;
		int numberOfParams = sscanf(params, "%d%d%d", &model, &color_0, &color_1);
		if (numberOfParams == 0)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /vadd [Ид авто]");
		else if (model < 400 || model > 611)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Ид автомобиля должен быть от 400 до 611");

		float fRotation = pGame->GetCamera()->GetCameraRotation();
		GTAfunc_loadSpecificModel(model);
		CVehicle *pVehicle = pPools->AddVehicle(eVehicleTypes(model));
		pVehicle->SetPosition(pPedSelf->GetPosition());
		((CMatrix4 *)((vehicle_info *)pVehicle->GetInterface())->base.matrix)->rotZ(fRotation);
		GTAfunc_PutActorInCar((vehicle_info *)pVehicle->GetInterface());
		if (numberOfParams == 1) pVehicle->SetColor((rand() % 0xFF), (rand() % 0xFF), 0, 0);
		else if (numberOfParams == 2) pVehicle->SetColor(color_0, color_0, 0, 0);
		else if (numberOfParams == 3) pVehicle->SetColor(color_0, color_1, 0, 0);
		pGame->GetCamera()->RestoreWithJumpCut();

		return;


	}

	void sskin(char *params)
	{
		int iParam1 = 0, iParam2 = 0;
		int numberOfParams = sscanf(params, "%d%d", &iParam1, &iParam2);
		if (numberOfParams == 0)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /sskin [Ид скина]");

		if (numberOfParams == 1 && iParam1 >= 0 && iParam1 < 300) {
			GTAfunc_DisembarkInstantly();
			GTAfunc_loadSpecificModel(iParam1);
			pPedSelf->SetModelIndex(iParam1);
			return;
		}
		if (numberOfParams > 1 && iParam2 >= 0 && iParam2 < 300) {
			if (pCRMP->getPlayers()->isBadPlayer(iParam1)
				|| !pCRMP->getPlayers()->pRemotePlayer[iParam1]
				|| !pCRMP->getPlayers()->pRemotePlayer[iParam1]->pPlayerData)
				return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Игрок не найден.");

			actor_info *info = pCRMP->getPlayers()->getGTAPed(iParam1);
			CPed *pPed = pPools->GetPed((PDWORD)info);
			if (!isBadPtr_GTA_pPed(pPed)) {
				GTAfunc_loadSpecificModel(iParam2);
				pPed->SetModelIndex(iParam2);
				return;
			}
		}
	}

	void recolor(char *params)
	{
		int iParam0 = 0, iParam1 = 0, iParam2 = 0;
		int numberOfParams = sscanf(params, "%d%d%d", &iParam0, &iParam1, &iParam2);
		if (numberOfParams == 0)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /rec [Ид Авто] [Первый цвет] [Второй цвет]");

		if (trainer.state == CHEAT_STATE_VEHICLE)
		{
			struct vehicle_info * info = vehicle_info_get(VEHICLE_SELF);
			if (isBadPtr_GTA_pVehicle(info)) return;
			if (numberOfParams == 1)
				return GTAfunt_SetVehicleColor(info, iParam0, iParam0);
			else if (numberOfParams == 2)
				return GTAfunt_SetVehicleColor(info, iParam0, iParam1);
			else if (numberOfParams == 3 && !pCRMP->getVehicles()->isBadVehicle(iParam0))
				return GTAfunt_SetVehicleColor(pCRMP->getVehicles()->pGTA_Vehicle[iParam0], iParam1, iParam2);
		} else if (numberOfParams >= 2 && !pCRMP->getVehicles()->isBadVehicle(iParam0))
		{
			struct vehicle_info * info = pCRMP->getVehicles()->pGTA_Vehicle[iParam0];
			if (numberOfParams == 2)
				return GTAfunt_SetVehicleColor(info, iParam1, iParam1);
			else if (numberOfParams == 3)
				return GTAfunt_SetVehicleColor(info, iParam1, iParam2);
		} else if (numberOfParams == 1)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /rec [Ид Авто] [Первый цвет] [Второй цвет]");

	}

	void open_vehicle(char *params)
	{
		if (pCRMP->getVehicles() == nullptr) return;

		int iVehicle = 0, open = 0;
		if (!strlen(params) || !sscanf(params, "%d%d", &iVehicle, &open))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /vopen [Ид Авто] [0 или 1]");
		if (pCRMP->getVehicles()->isBadVehicle(iVehicle))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Автомобиль не найден.");

		return pCRMP->getVehicles()->pSAMP_Vehicle[iVehicle]->setDoorState(!open);
	}

	void set_weather(char *params)
	{
		return pGame->GetWeather()->ForceWeatherNow(atoi(params));
	}

	void set_time(char *params)
	{
		int time = atoi(params);
		if (time >= 0 && time <= 24) {
			pCRMP->getInfo()->pSettings->bWorldTime_Hour = time;
			pCRMP->getInfo()->pSettings->isTimeUpdate = 1;
			pGame->GetClock()->Set(time, 0);
		} else pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Время должно быть от 0 до 23!");
	}

	void set_health(char *params)
	{
		float health = stof(params);
		if (!strlen(params))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /shp [Количество здоровья]!");
		else if (health && health <= 100)
			pPedSelf->SetHealth(health);
	}

	void set_vehicle_hp(char *params)
	{
		float vehicle_hp = stof(params);
		if (!strlen(params))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /svhp [Количество хп]!");
		else if (vehicle_hp && vehicle_hp <= 1000)
		{
			if (trainer.state == CHEAT_STATE_VEHICLE && pPedSelf->GetVehicle())
				pPedSelf->GetVehicle()->SetHealth(vehicle_hp);
			else pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Вы должны сидеть в транспорте!");
		}
	}

	void del_msg(char *params)
	{
		int iStrNumber;
		if (!strlen(params) || (iStrNumber = atoi(params)) == NULL)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /delmsg [Номер строки]!");
		if (iStrNumber < 0 || iStrNumber > 99)
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Не существует такой строки!");
		if (strstr(pCRMP->getChat()->chatEntry[iStrNumber].szText, "CRMP Trainer by SlonoBoyko"))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Нельзя удалять копирайты!");

		pCRMP->getChat()->deleteMessage(iStrNumber);
	}

	void spectate(char *params)
	{
		static bool bSpectating = false;
		int iPlayerID = NULL;
		if (!strlen(params)) {
			if (bSpectating) {
				pPedSelf->SetIsLocked(bSpectating = false);
				return pGame->GetCamera()->RestoreWithJumpCut();
			} else return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /spec [Ид игрока]!");
		}

		if (!(iPlayerID = atoi(params)))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Введите /spec [Ид игрока]!");
		if (pCRMP->getPlayers()->isBadPlayer(iPlayerID))
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Игрок не найден!");

		int iPlayerState = pCRMP->getPlayers()->getPlayerState(iPlayerID);
		if (iPlayerState == PLAYER_STATE_DRIVER || iPlayerState == PLAYER_STATE_PASSENGER) {
			int iVehicleID = pCRMP->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->sVehicleID;
			if (!pCRMP->getVehicles()->isBadVehicle(iVehicleID)) {
				GTAfunc_CameraOnVehicle(pCRMP->getVehicles()->pGTA_Vehicle[iVehicleID]);
			}
		} else if (iPlayerState == PLAYER_STATE_ONFOOT || iPlayerState == PLAYER_STATE_SPAWNED) {
			GTAfunc_CameraOnActor(pCRMP->getPlayers()->getGTAPed(iPlayerID));
		}
		bSpectating = true;
		pPedSelf->SetIsLocked(true);
	}

	//void go(char *param) 
	//{
	//	GTAfunc_PerformAnimation("PED", "run_civi", 20000, true, true, true, false, true, true, false);
	//}
}

void registerSampCommand()
{
	if (pCRMP->getInput() == nullptr) return;
	if (!pCRMP->getInput()->iCMDCount || 
		pCRMP->getInput()->iCMDCount > SAMP_MAX_CLIENTCMDS) return;

	pCRMP->getInput()->addClientCommand("dgun", cmd::dgun);
	pCRMP->getInput()->addClientCommand("boom", cmd::boom);
	pCRMP->getInput()->addClientCommand("cchat", cmd::cchat);
	pCRMP->getInput()->addClientCommand("goto", cmd::warp);
	pCRMP->getInput()->addClientCommand("sendpic", cmd::pickup);
	pCRMP->getInput()->addClientCommand("gcheck", cmd::gotocheck);
	pCRMP->getInput()->addClientCommand("scheck", cmd::sendcheck);
	pCRMP->getInput()->addClientCommand("nick", cmd::nick);
	pCRMP->getInput()->addClientCommand("scar", cmd::scar);
	pCRMP->getInput()->addClientCommand("sskin", cmd::sskin);
	pCRMP->getInput()->addClientCommand("vadd", cmd::vadd);
	pCRMP->getInput()->addClientCommand("rec", cmd::recolor);
	pCRMP->getInput()->addClientCommand("vopen", cmd::open_vehicle);
	pCRMP->getInput()->addClientCommand("sweather", cmd::set_weather);
	pCRMP->getInput()->addClientCommand("stime", cmd::set_time);
	pCRMP->getInput()->addClientCommand("shp", cmd::set_health);
	pCRMP->getInput()->addClientCommand("svhp", cmd::set_vehicle_hp);
	pCRMP->getInput()->addClientCommand("delmsg", cmd::del_msg);
	pCRMP->getInput()->addClientCommand("spec", cmd::spectate);
}