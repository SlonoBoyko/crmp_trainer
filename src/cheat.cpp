/*
			AUTHOR: SlonoBoyko
			LiteHack.Ru
			21.05.2018
*/

#include "main.h"

struct global				trainer;
 
void call_functions()
{
	static DWORD dwTime = GetTickCount();

	if (!pGame->IsGameLoaded()) return;
	if (!pCRMP->getPlayers() || !pCRMP->getVehicles()) return;
	if (isBadPtr_GTA_pPed(actor_info_get(ACTOR_SELF))) return;

	trainer.state = CHEAT_STATE_NONE;
	if (pCRMP->getInfo()->iGameState == GAMESTATE_CONNECTED && pCRMP->getPlayers()->pLocalPlayer->iIsSpawned)
	{
		int iPlayerState = pCRMP->getPlayers()->pLocalPlayer->getPlayerState();
		if (iPlayerState == PLAYER_STATE_DRIVER || iPlayerState == PLAYER_STATE_PASSENGER)
		{
			trainer.state = CHEAT_STATE_VEHICLE;
		} else if (iPlayerState == PLAYER_STATE_ONFOOT)
		{
			trainer.state = CHEAT_STATE_ACTOR;
		}
		if (dwTime < GetTickCount() - 5000) {
			pCRMP->getInfo()->updateScoreBoard();
			dwTime = GetTickCount();
		}
	}

	func_reconnect();
	func_carshot();
	func_aafk();
	func_aimbot();
	func_air_break();
	func_good_mode();
	func_suicide();
	func_dialoghider();
	func_anti_bike_fall();
	func_improved_overview();
	func_spawn();
	func_procces_close();
	func_repair_vehicle();
	func_nospread();
	func_cargun();
	func_noreload();
	func_fast_connect();
	func_vehicle_speedhack();
	func_unfreze();
	func_noeject();
	func_clickwarp();
	func_fast_exit();
	func_quick_turn();
	func_skillmaster();
	func_pulse();
	func_invisible();
	func_pluscbug();
	func_engine_always_on();
	func_flooder();
	func_marker_teleport();
	func_keep_trailer();
	func_antifreze();
	func_antistun();
}

void func_reconnect()
{
	static DWORD dwTime = GetTickCount();

	if (isKeyDown(VK_LSHIFT) && isKeyPressed(ini.key.reconnect))
		menu.reconnect = true;

	if (menu.reconnect) {
		if (ini.reconnect_delay > 25) ini.reconnect_delay = 25;
		static bool reconnecting = false;
		if (reconnecting && dwTime < GetTickCount() - (ini.reconnect_delay * 1000)) {
			pCRMP->getInfo()->iGameState = GAMESTATE_WAIT_CONNECT;
			reconnecting = menu.reconnect = false;
		} else if (!reconnecting) {
			mem::set((PVOID)(SAMP_OVERFLOWPOOL_BILDING_FIX), 0, sizeof(int));
			pCRMP->getInfo()->disconnect(500);
			pCRMP->getInfo()->restartGame();
			pCRMP->getPlayers()->resetPlayerPool();
			pCRMP->getInfo()->sendQuery(pCRMP->getInfo()->szIP, pCRMP->getInfo()->ulPort);
			pGame->GetPools()->DeleteAllVehicles();
			reconnecting = true;
			dwTime = GetTickCount();
		}
	}
}

void func_carshot()
{
	if (menu.carshot == true)
    {
		static float fTime = float(GetTickCount());

		if (trainer.state == CHEAT_STATE_VEHICLE)
		{
			vehicle_info *vinfo = vehicle_info_get(VEHICLE_SELF);
			if (vinfo == nullptr) return;

			float fSpeed = ini.carshot_speed / 100.0f;
			float fRotation = pGame->GetCamera()->GetCameraRotation();
			((CMatrix4 *)vinfo->base.matrix)->rotZ(fRotation);

			if (isKeyDown('W')) {
				vinfo->speed[0] = sinf(fRotation) * fSpeed;
				vinfo->speed[1] = cosf(fRotation) * fSpeed;
			}if (isKeyDown('S')) {
				vinfo->speed[0] = sinf(fRotation) * -0.5;
				vinfo->speed[1] = cosf(fRotation) * -0.5;
			}
			if (isKeyDown(VK_SPACE))	vinfo->speed[2] += fSpeed * (float(GetTickCount()) - fTime) / 1000.f;
			if (isKeyDown(VK_LCONTROL)) vinfo->speed[2] -= fSpeed * (float(GetTickCount()) - fTime) / 1000.f;
			if (isKeyDown(VK_LSHIFT))	vect3_zero(vinfo->speed);

			fTime = float(GetTickCount());
		}
    }
}

void func_noeject()
{
	static bool install = false;
	if (menu.noeject == true) {
		if (install == false) {
			mem::copy((PVOID)(pCRMP->getBase() + 0x11D30), "\xC3\x90", 2);
			sampSyncDisable(RPCEnumeration::RPC_SetDrunkLevel, INCOMING_RPC, true);
			install = true;
		}
	} else if (install) {
		mem::copy((PVOID)(pCRMP->getBase() + 0x11D30), "\xE9\x10", 2);
		sampSyncDisable(RPCEnumeration::RPC_SetDrunkLevel, INCOMING_RPC, true);
		install = false;
	}

}

void func_aafk()
{
	static bool install = false;
	if (menu.aafk) {
		mem::copy((PVOID)0x74805A, "\x01", 1, 1, "\x00");
		mem::copy((PVOID)0x747FB6, "\x01", 1, 1, "\x00");
		mem::copy((PVOID)0x74542B, "\x90\x90\x90\x90\x90\x90\x90\x90", 8, 1, "\x50\x51\xFF\x15\x00\x83\x85\x00");
		mem::copy((PVOID)0x53EA88, "\x90\x90\x90\x90\x90\x90", 6, 1, "\x0F\x84\x7B\x01\x00\x00");
		install = true;
	} else if (install) {
		mem::copy((PVOID)0x74805A, "\x00", 1, 1, "\x01");
		mem::copy((PVOID)0x747FB6, "\x00", 1, 1, "\x01");
		mem::copy((PVOID)0x74542B, "\x50\x51\xFF\x15\x00\x83\x85\x00", 8);
		mem::copy((PVOID)0x53EA88, "\x0F\x84\x7B\x01\x00\x00", 6);
		install = false;
	}
}

void func_invisible()
{
	static bool install = false; 
	if(menu.invisible) {
		mem::copy((PVOID)0x5E4110, "\xC2\x10\x00", 3, 1, "\x56\x8B\xF1");
		pCRMP->getPlayers()->pLocalPlayer->iIsSpectating = 1;
		pCRMP->getPlayers()->pLocalPlayer->iInitiatedSpectating = 1;
		install = true;
	} else if (install) {
		mem::copy((PVOID)0x5E4110, "\x56\x8B\xF1", 3);
		pCRMP->getPlayers()->pLocalPlayer->iIsSpectating = 0;
		pCRMP->getPlayers()->pLocalPlayer->iInitiatedSpectating = 0;
		install = false;
	}
}

void func_aimbot()
{
	if (isKeyPressed(ini.key.skin_aimbot)) menu.skin_aim ^= true;
	if (isKeyPressed(ini.key.ping_aimbot)) menu.ping_aim ^= true;

	if ((menu.ping_aim || menu.skin_aim) && GetKeyState(VK_RBUTTON) < 0)
	{
		int iPlayerID = pCRMP->getPlayers()->findTargetPlayer(100.0f);
		if (!pCRMP->getPlayers()->isBadPlayer(iPlayerID))
		{
			actor_info *target = pCRMP->getPlayers()->getGTAPed(iPlayerID);
			if (target == NULL || ACTOR_IS_DEAD(target)) return;

			if (pGame->GetWorld()->IsLineOfSightClear(pPedSelf->GetPosition(), 
				&target->base.m_CMatrix->vPos, true, true, false, true, false))
			{
				CCam *pCam = pGame->GetCamera()->GetCam(pGame->GetCamera()->GetActiveCam());
				CVector vecTarget = *pCRMP->getPlayers()->getBonePos(iPlayerID, BONE_UPPERTORSO);
				CVector vecOrigin = *pCam->GetSource();
				CVector vecSpeed = target->m_SpeedVec;

				if (vecTarget.IsNearZero() || vecOrigin.IsNearZero()) return;
				if (pPedSelf->GetCurrentWeaponSlot() > 2 || pPedSelf->GetCurrentWeaponSlot() < 7) 
				{
					if (menu.ping_aim) 
					{
						int iPing = pCRMP->getPlayers()->pRemotePlayer[iPlayerID]->iPing;
						vecSpeed *= float(pCRMP->getPlayers()->iLocalPlayerPing + iPing) * 0.0472f;
					}

					CVector vecScreen(vecOrigin - (vecTarget + vecSpeed));
					float mult = tan((pCam->GetFOV() / 2) * DEGRESS);

					const float &fCrossX =		*(float *)0xB6EC14;
					const float &fCrossY =		*(float *)0xB6EC10;
					const float &fAspectRatio = *(float *)0xC3EFA4;

					float horizont = (M_PI - atan2f(vecScreen.fY, -vecScreen.fX));
					horizont += mult * (fCrossX * 2 - 1.0f);
					pCam->SetBeta(horizont);

					float vertical = atan2f(vecScreen.Length(), vecScreen.fZ);
					vertical -= (M_PI - atan2(1.0f, mult * (1.0f - fCrossY * 2) * (1.0f / fAspectRatio)));
					pCam->SetAlpha(vertical);
				}
			}
		}
	}
	if (menu.autoshot && GetKeyState(VK_RBUTTON) < 0)
	{
		int iPlayerID = pCRMP->getPlayers()->findTargetPlayer(40.0f);
		if (!pCRMP->getPlayers()->isBadPlayer(iPlayerID))
		{
			actor_info *nearest = pCRMP->getPlayers()->getGTAPed(iPlayerID);

			if (isBadPtr_GTA_pPed(nearest)) return;
			if (nearest && ACTOR_IS_DEAD(nearest)) return;
			if (pGame->GetWorld()->IsLineOfSightClear(pPedSelf->GetPosition(), 
				&nearest->base.m_CMatrix->vPos, true, true, false, true, false, false, false))
			{
				gta_set_gamekey_state(ePadType::BUTTON_CIRCLE, 0xFF);
			}
		}
	}
}

void func_air_break()
{
	if (isKeyPressed(ini.key.air_break))
		menu.air_break ^= 1;

	static DWORD dwTime = NULL;
	actor_info *self = actor_info_get(ACTOR_SELF); 
	if (menu.air_break == true && self != nullptr)
	{
		pPedSelf->SetIsLocked(true);
		self->speed[2] = 0.f;
		self->fCurrentRotation = -pGame->GetCamera()->GetCameraRotation();
		float rotation = -(self->fTargetRotation = self->fCurrentRotation);
		float speed = ini.air_break_speed / 100.f;

		CVector *nVec = &self->base.m_CMatrix->vPos;
		if (trainer.state == CHEAT_STATE_VEHICLE)
		{
			vehicle_info *info = vehicle_info_get(VEHICLE_SELF);
			if (info == nullptr) return;

			nVec = &info->base.m_CMatrix->vPos;

			for (vehicle_info *temp = info; temp; temp = temp->trailer) {
				float diff = vect3_length(temp->base.m_CMatrix->vPos - *nVec);
				((CMatrix4*)temp->base.matrix)->rotZ(rotation);
				temp->base.m_CMatrix->vPos.fX = nVec->fX - sinf(rotation) * diff;
				temp->base.m_CMatrix->vPos.fY = nVec->fY - cosf(rotation) * diff;
				gta_vehicle_zero_speed(temp);
			}
		} else self->pedFlags.bIsStanding = self->pedFlags.bWasStanding = self->pedFlags.bStayInSamePlace = true;
		
		if (isKeyDown('W')) {
			nVec->fX += sinf(rotation) * speed; nVec->fY += cosf(rotation) * speed;
		} 
		if (isKeyDown('S')) {
			nVec->fX -= sinf(rotation) * speed; nVec->fY -= cosf(rotation) * speed;
		} 
		if (isKeyDown('D') || isKeyDown(VK_RIGHT)) {
			nVec->fX += cosf(rotation) * speed; nVec->fY -= sinf(rotation) * speed;
		} 
		if (isKeyDown('A') || isKeyDown(VK_LEFT)) {
			nVec->fX -= cosf(rotation) * speed; nVec->fY += sinf(rotation) * speed;
		}
		if (isKeyDown(VK_UP))	nVec->fZ += speed;
		if (isKeyDown(VK_DOWN)) nVec->fZ -= speed;
		dwTime = GetTickCount();

	}
}

void func_good_mode()
{
	if (isKeyPressed(ini.key.good_mode))
		menu.good_mode ^= true;

	static bool install = false;
	if (menu.good_mode == true)
	{
		if (trainer.state == CHEAT_STATE_VEHICLE) {
			vehicle_info *info = vehicle_info_get(VEHICLE_SELF);
			for (vehicle_info *temp = info; temp; temp = temp->trailer) {
				if (temp->m_nVehicleFlags.bCanBeDamaged)
					temp->m_nVehicleFlags.bCanBeDamaged = false;
			}
		}
		actor_info_get(ACTOR_SELF)->flags |= ACTOR_FLAGS_INVULNERABLE;
		pCRMP->getPlayers()->pLocalPlayer->pSAMP_Actor->setImmunities(true, true, true, true, true);
		install = true;
	}
	else if (install == true)
	{
		if (trainer.state == CHEAT_STATE_VEHICLE) {
			vehicle_info *info = vehicle_info_get(VEHICLE_SELF);
			for (vehicle_info *temp = info; temp; temp = temp->trailer) {
				if(!temp->m_nVehicleFlags.bCanBeDamaged)
					temp->m_nVehicleFlags.bCanBeDamaged = true;
			}
		}
		actor_info_get(ACTOR_SELF)->flags &= ~ACTOR_FLAGS_INVULNERABLE;
		install = false;
	}
}

void func_suicide()
{
	if (isKeyPressed(ini.key.suicide)) {
		pPedSelf->SetHealth(0.0f);
		pPedSelf->DetachPedFromEntity();
		pCRMP->getPlayers()->pLocalPlayer->sendDeath();
	}
}

void func_dialoghider()
{
	static bool enable = false;
	
	static DWORD dwTime = GetTickCount();
	if (dwTime < GetTickCount() - 500)
	{
		enable = menu.dhider;
		dwTime = GetTickCount();
	}
	if (menu.dhider != enable)
	{
		pCRMP->getDialog()->iDialogShowed = !menu.dhider;
		enable = menu.dhider;
	}
	if ((menu.dhider == enable) && ((int)menu.dhider == pCRMP->getDialog()->iDialogShowed))
	{
		menu.dhider = !pCRMP->getDialog()->iDialogShowed;
		enable = menu.dhider;
	}
	if (isKeyPressed(ini.key.dialoghider))
	{
		pCRMP->getDialog()->iDialogShowed ^= 1;
		menu.dhider = !pCRMP->getDialog()->iDialogShowed;
		if (pCRMP->getDialog()->iDialogShowed)
			pCRMP->getMisc()->toggleSAMPCursor(1);
		else pCRMP->getMisc()->toggleSAMPCursor(0);
	}

}

void func_anti_bike_fall()
{
	if (menu.bike_fall == true) {
		mem::copy((PVOID)0x522F6A, "\xE9\xA7\x03\x00\x00\x90", 6, 1, "\x0F\x84\xA6\x03\x00\x00");
		mem::copy((PVOID)0x4B3296, "\x90\x90\x90", 3);
	} else if (!mem::compare((void *)0x4B3296, "\x90\x90\x90", 3)){
		mem::copy((PVOID)0x4BA3B9, "\x0F\x84\xA6\x03\x00\x00", 6);
		mem::copy((PVOID)0x4B3296, "\xD8\x65\x04", 3);
	}
}

void func_improved_overview()
{
	if (menu.improved_overview)
	{
		if (pCRMP->getPlayers()->pLocalPlayer->iIsSpawned)
		{
			CCamera		*pCamera = pGame->GetCamera();
			CCam		*pCam = pCamera->GetCam(pCamera->GetActiveCam());

			if (pCam->GetFOV() != ini.normal_fov) {
				pCam->SetFOV(ini.normal_fov);
				pCam->SetFOVSpeed(0.0f);
			} mem::copy((PVOID)0x522F6A, "\x90\x90\x90\x90\x90\x90", 6, 1, "\xD9\x9F\xB4\x00\x00\x00");
		}
	} else mem::copy((PVOID)0x522F6A, "\xD9\x9F\xB4\x00\x00\x00", 6, 1, "\x90\x90\x90\x90\x90\x90");
		
}

void func_spawn()
{
	if (isKeyDown(VK_LSHIFT) && isKeyPressed(ini.key.spawn))
		pCRMP->getPlayers()->pLocalPlayer->sendSpawn();
	
}

void func_procces_close()
{
	if (menu.proccess_killer) {
		if (isKeyDown(VK_LMENU) && isKeyPressed(VK_F4)) {
			pCRMP->getInfo()->disconnect(0);
			ExitProcess(EXIT_SUCCESS);
		}
	}
}

void func_repair_vehicle()
{
	if (trainer.state == CHEAT_STATE_VEHICLE)
	{
		if (isKeyPressed(ini.key.repair))
		{
			vehicle_info *info = vehicle_info_get(VEHICLE_SELF);
			for (vehicle_info *temp = info; temp; temp = temp->trailer) {
				GTAfunc_RepairVehicle(temp);
				temp->m_nVehicleFlags.bIsDamaged = false;
			}
		}
	}
}

void func_nospread()
{
	if (pCRMP == NULL || pGame == NULL) return;

	static float standVal[11][4]; static bool active = false;

	if (menu.nospread) {
		if (active == false) {
			for (int i = WEAPONSKILL_POOR; i <= WEAPONSKILL_SPECIAL; i++) {
				for (int x = WEAPONTYPE_PISTOL; x <= WEAPONTYPE_TEC9; x++) {
					CWeaponInfo *pWeaponInfo = pGame->GetWeaponInfo((eWeaponType)x, (eWeaponSkill)i);
					standVal[x - 22][i] = pWeaponInfo->GetAccuracy();
					pWeaponInfo->SetAccuracy(10.0f);
				}
			} active = true;
		}
	} else if (active == true) {
		for (int i = WEAPONSKILL_POOR; i <= WEAPONSKILL_SPECIAL; i++) {
			for (int x = WEAPONTYPE_PISTOL; x <= WEAPONTYPE_TEC9; x++) {
				CWeaponInfo *pWeaponInfo = pGame->GetWeaponInfo((eWeaponType)x, (eWeaponSkill)i);
				pWeaponInfo->SetAccuracy(standVal[x - 22][i]);
			}
		}
		active = false;
	}
}

void func_cargun()
{
	if (menu.cargun == true && isKeyPressed(VK_LBUTTON)) {
		int VehicleID = pCRMP->getVehicles()->findNearestEmptyVehicle();
		if (VehicleID < 0) return;

		vehicle_info *info = pCRMP->getVehicles()->getGTAVehicle(VehicleID);
		CVehicle *pCVehicle = pPools->GetVehicle((PDWORD)info);
		if (isBadPtr_GTA_pVehicle(pCVehicle)) return;

		CCamera *pCamera = pGame->GetCamera();
		CVector vecSpeed = *pCamera->GetCam(pCamera->GetActiveCam())->GetFront() * 2.5f;
		CVector vecCoord = *pPedSelf->GetPosition() + vecSpeed * 5.f;
		pCVehicle->SetPosition(&vecCoord);
		pCVehicle->SetMoveSpeed(&vecSpeed);

		pCRMP->getRakClient()->SendEnterVehicle(VehicleID, 0);
		pCRMP->getRakClient()->SendFakeDriverSyncData(VehicleID, vecCoord, pCVehicle->GetHealth(), vecSpeed);

	}
}

void func_noreload()
{
	if (menu.noreload)
	{
		actor_info *info = actor_info_get(ACTOR_SELF);
		if (info && ACTOR_IS_DEAD(info)) return;

		int weapon_id = info->weapon[info->weapon_slot].id;
		if (weapon_id >= 22 && weapon_id <= 42) {
			if (info->weapon[info->weapon_slot].ammo_clip == 1) {
				pPedSelf->GiveWeapon(eWeaponType(weapon_id), 0);
			}
		}
	}
}

void func_fast_connect()
{
	if (menu.fast_connect) {
		mem::copy((void *)(pCRMP->getBase() + 0x2A09C6), "\x00\x00\x00\x00", 4, true, "\xB8\x0B\x00\x00");
	} else mem::copy((void *)(pCRMP->getBase() + 0x2A09C6), "\xB8\x0B\x00\x00", 4, true, NULL);
}

void func_unfreze()
{
	if (isKeyPressed(ini.key.unfreze))
	{
		pPedSelf->SetIsLocked(false);
		GTAfunc_TogglePlayerControllable(false); 
		pGame->GetCamera()->RestoreWithJumpCut();
		if (trainer.state == CHEAT_STATE_ACTOR) 
			GTAfunc_DisembarkInstantly();		

		pCRMP->getPlayers()->pLocalPlayer->toggleControllable(true);
		if (!menu.clickwarp)
			pCRMP->getMisc()->toggleSAMPCursor(false);
	}
}

void func_vehicle_speedhack()
{
	static DWORD timer = GetTickCount();

	if (trainer.state == CHEAT_STATE_VEHICLE)
	{
		vehicle_info *info = vehicle_info_get(VEHICLE_SELF);
		if (info == nullptr) return;

		CModelInfo *pModel = pGame->GetModelInfo(info->base.model_alt_id);
		if (pModel == nullptr || pModel->IsTrain() || pModel->IsBoat()) return;

		if (isKeyPressed(ini.key.speedhack)) 
			timer = GetTickCount();
	
		if (isKeyDown(ini.key.speedhack))
		{
			float speed = vect3_length(info->speed);
			if (near_zero(speed)) return;

			speed += ini.acceleration * FLOAT(GetTickCount() - timer) / 10000.f;

			if (speed > ini.max_speed / 100.f)
				speed = ini.max_speed / 100.f;
			for (vehicle_info *temp = info; temp; temp = temp->trailer) {
				vect3_normalize(info->speed, info->speed);
				vect3_mult(info->speed, speed, info->speed);
			}
			timer = GetTickCount();	
		}
	}
}

void func_clickwarp()
{
	if (gta_menu_active()) return;

	POINT cursor_pos;
	
	uint8_t cam = pGame->GetCamera()->GetActiveCam();
	CVector vecOrigin = *pGame->GetCamera()->GetCam(cam)->GetSource();

	if (isKeyPressed(ini.key.click_warp)) {
		menu.clickwarp ^= true;
		pCRMP->getMisc()->toggleSAMPCursor(menu.clickwarp, CURSORMODE_LOCK_MOUSE);
		CControllerConfigManager *pPadConfig = pGame->GetControllerConfigManager();
		if (pPadConfig != nullptr && pPadConfig->GetInputType()) {
			if (pPadConfig->GetControllerKeyAssociatedWithAction(VEHICLE_LOOK_BEHIND, MOUSE))
				pPadConfig->SetControllerKeyAssociatedWithAction(VEHICLE_LOOK_BEHIND, 0, MOUSE);
		}
	}

	if (menu.clickwarp)
	{
		if (pCRMP->getMisc()->iCursorMode != CURSORMODE_LOCK_MOUSE)
			pCRMP->getMisc()->toggleSAMPCursor(menu.clickwarp, CURSORMODE_LOCK_MOUSE);
		
		if (GetCursorPos(&cursor_pos) && ScreenToClient(pD3DHook->pPresentParam->hDeviceWindow, &cursor_pos))
		{
			char buf[256];
			CVector	vecGround, vecTarget, vecScreen(cursor_pos.x, cursor_pos.y, 700.0f);
			
			CalcWorldCoors(&vecScreen, &vecTarget);
	
			CVehicle			*pVehicle = nullptr;
			CColPoint			*pCollision = nullptr; 
			CEntitySAInterface	*pCollEntity = nullptr;
		
			if (GTAfunc_ProcessLineOfSight(&vecOrigin, &vecTarget, &pCollision, &pCollEntity,
				true, true, false, true, true, false, false, false) && pCollision)
			{
				vecGround = *pCollision->GetPosition();
				if (trainer.state == CHEAT_STATE_VEHICLE)
					vecGround -= (*pCollision->GetNormal() * 2.0f);
				else vecGround -= (*pCollision->GetNormal() * 0.5f);

				if (pPedSelf->GetAreaCode() == 0)
					vecGround.fZ = pGame->GetWorld()->FindGroundZForPosition(vecGround.fX, vecGround.fY);
				else vecGround.fZ = pGame->GetWorld()->FindGroundZFor3DPosition(&vecGround);

				sprintf(buf, "Дистанция: %0.2f", vect3_dist(vecOrigin, vecGround));

				if (pCollEntity && pCollEntity->nType == ENTITY_TYPE_VEHICLE) {
					if (pCollEntity != NULL && (pVehicle = pPools->GetVehicle((DWORD *)pCollEntity)) != NULL 
						&& pVehicle->GetHealth() > 250.0f) {
						if (trainer.state == CHEAT_STATE_VEHICLE && pVehicle == pPedSelf->GetVehicle()) return;
						const vehicle_entry *vehicleEntry = gta_vehicle_get_by_id(pVehicle->GetModelIndex());
						if (vehicleEntry != NULL) sprintf(buf, "Сесть в %s", vehicleEntry->name);
					}
				}

				if (pVehicle != nullptr) {
					CalcScreenCoors(pVehicle->GetPosition(), &vecScreen);
					pD3DHook->pD3DFontBig->PrintShadow(vecScreen.fX, vecScreen.fY + 10.0f, -1, buf);
				} else {
					CalcScreenCoors(&vecGround, &vecScreen);
					pD3DHook->pD3DFontBig->PrintShadow(vecScreen.fX - (pD3DHook->pD3DFontBig->DrawLength(buf) / 2.0f) + 3.5f, 
						vecScreen.fY - 40.0f, -1, buf);
				}

				if (isKeyDown(VK_LBUTTON))
				{
					vecGround.fZ += 1.f;
					if (pVehicle && pCollEntity->nType == ENTITY_TYPE_VEHICLE) {
						vehicle_info *vehicle = (vehicle_info *)(pVehicle->GetVehicleInterface());
						if (vehicle->driver == NULL && vehicle->m_nNumPassengers == 0)
							GTAfunc_PutActorInCar(vehicle);
						else GTAfunc_PutActorInCarAsPassenger(vehicle, vehicle->m_nNumPassengers);
					} gta_teleport(vecGround);

					pPedSelf->SetIsLocked(false);
					GTAfunc_TogglePlayerControllable(false);
					pCRMP->getMisc()->toggleSAMPCursor(menu.clickwarp = false);
				}
			} if (pCollision != nullptr) pCollision->Destroy();
		} 
	}
}

void func_fast_exit()
{
	if (isKeyPressed(ini.key.fast_exit))
	{
		float fPosition[3];
		actor_info * self = actor_info_get(ACTOR_SELF);
		if (trainer.state == CHEAT_STATE_VEHICLE)
		{
			vehicle_info *vinfo = vehicle_info_get(VEHICLE_SELF);
			if (vinfo == nullptr) return;

			vect3_copy(vinfo->base.m_CMatrix->vPos, fPosition);

			fPosition[0] -= sinf(-self->fCurrentRotation) * 4.0f;
			fPosition[1] -= cosf(-self->fCurrentRotation) * 4.0f;
			fPosition[2] = pGame->GetWorld()->FindGroundZForPosition(fPosition[0], fPosition[1]);

			GTAfunc_RemoveActorFromCarAndPutAt(fPosition);
		}
	}
}

void func_quick_turn()
{
	if (trainer.state == CHEAT_STATE_VEHICLE)
	{
		vehicle_info *info = vehicle_info_get(VEHICLE_SELF);
		if (!info || pGame->GetModelInfo(info->base.model_alt_id)->IsTrain()) return;
		
		CVector vPos = info->base.m_CMatrix->vPos;
		CVector vUnder = info->base.m_CMatrix->vUp;
		vUnder.Normalize(); vUnder.ZeroNearZero();
		vehicle_info *tow_info = info;

		if (isKeyPressed(ini.key.turn_back)) 
		{
			for (vehicle_info *temp = info; temp; temp = temp->trailer) 
			{
				CVector vDiff;
				RwMatrix *matrix = temp->base.m_pRwMatrix;
				vect3_vect3_sub(matrix->pos, vPos, vDiff);
				vect3_invert(matrix->right, matrix->right);
				vect3_invert(matrix->up, matrix->up);
				temp->base.m_CMatrix->vPos = vPos - vDiff;
				temp->base.m_CMatrix->vPos.fZ = vPos.fZ;
				vect3_invert(temp->speed, temp->speed);

				if (temp == tow_info) continue;
				gta_trailer_attach(tow_info, temp, false);
				tow_info = temp;
			}
		}
		
		if (isKeyPressed(ini.key.turn_right))
		{
			for (vehicle_info *temp = info; temp; temp = temp->trailer)
			{
				CVector vDiff = temp->base.m_CMatrix->vPos - vPos;
				matrix_vect3_rotate(temp->base.matrix, vUnder, (float)HALF_PI, temp->base.matrix);	
				temp->base.m_CMatrix->vPos.fX = vPos.fX + vDiff.fY;
				temp->base.m_CMatrix->vPos.fY = vPos.fY - vDiff.fX;
				temp->base.m_CMatrix->vPos.fZ = vPos.fZ;
				temp->m_SpeedVec.CrossProduct(&vUnder);
				
				if (temp == tow_info) continue;
				gta_trailer_attach(tow_info, temp, false);
				tow_info = temp;

			}
		}

		if (isKeyPressed(ini.key.turn_left))
		{
			for (vehicle_info *temp = info; temp; temp = temp->trailer)
			{
				CVector vDiff = temp->base.m_CMatrix->vPos - vPos;
				matrix_vect3_rotate(temp->base.matrix, vUnder, (float)-HALF_PI, temp->base.matrix);
				temp->base.m_CMatrix->vPos.fX = vPos.fX - vDiff.fY;
				temp->base.m_CMatrix->vPos.fY = vPos.fY + vDiff.fX;
				temp->base.m_CMatrix->vPos.fZ = vPos.fZ;
				temp->m_SpeedVec.CrossProduct(&-vUnder);

				if (temp == tow_info) continue;
				gta_trailer_attach(tow_info, temp, false);
				tow_info = temp;
			}
		}

		if (isKeyPressed(ini.key.unflip))
		{
			float cam_rot = pGame->GetCamera()->GetCameraRotation();
			for (vehicle_info *temp = info; temp; temp = temp->trailer)
			{
				float diff = vect3_dist(temp->base.m_CMatrix->vPos, vPos);
				((CMatrix4*)temp->base.matrix)->rotZ(cam_rot);
				temp->base.m_CMatrix->vPos.fX = vPos.fX - sinf(cam_rot) * diff;
				temp->base.m_CMatrix->vPos.fY = vPos.fY - cosf(cam_rot) * diff;
				temp->base.m_CMatrix->vPos.fZ = vPos.fZ;	
				gta_rotate_along_surface(temp, temp->base.m_CMatrix->vPos);
				gta_vehicle_zero_speed(temp);
			}
		}
	}
}

void func_skillmaster()
{
	static DWORD dwTime = GetTickCount();
	if (menu.skillmaster && GetTickCount() - 2000 > dwTime)
	{
		actor_info *info = actor_info_get(ACTOR_SELF);
		if (info->weapon_slot != 0) {
			weapon *weapon = &info->weapon[info->weapon_slot];
			if (weapon->ammo_clip == 0) {
				if (weapon->ammo > 7) weapon->ammo_clip += 7;
				else weapon->ammo_clip = weapon->ammo;
			} else if (weapon->ammo_clip > 0) {
				weapon->ammo_clip--;
				weapon->ammo--;
			}
		}
		dwTime = GetTickCount();
	}
}

void func_pulse()
{
	static DWORD dwTime = GetTickCount();
	if (dwTime < GetTickCount() - 200)
	{
		vehicle_info *info = vehicle_info_get(VEHICLE_SELF);
		if (menu.pulsecolor && trainer.state == CHEAT_STATE_VEHICLE) {
			for (vehicle_info *temp = info; temp; temp = temp->trailer) {
				GTAfunt_SetVehicleColor(temp, rand() % 180, rand() % 180);
			}
		}
		
		if (menu.pulsewheels && trainer.state == CHEAT_STATE_VEHICLE) {
			static uint8_t idx = 0; if (idx >= 16) idx = 0;
			DWORD pWheels[] = { 1025, 1073, 1074, 1075, 1076, 1077, 1078, 1079, 1080, 1081, 1082, 1083, 1084, 1085, 1096, 1097, 1098 };
			for (vehicle_info *temp = info; temp; temp = temp->trailer) {
				GTAfunc_addVehicleUpgrade(vehicle_info_get(VEHICLE_SELF), pWheels[++idx]);
			}
		}
		dwTime = GetTickCount();
	}
}

void func_pluscbug()
{
	static DWORD dwTime = GetTickCount();
	if (menu.pluscbug && dwTime < GetTickCount() - 200)
	{
		CWeapon *pWeapon = pPedSelf->GetWeapon(pPedSelf->GetCurrentWeaponSlot());
		
		if (pWeapon->GetType() == WEAPONTYPE_DESERT_EAGLE) {
			if (pWeapon->GetState() == WEAPONSTATE_FIRING) {
				GTAfunc_DisembarkInstantly();
				dwTime = GetTickCount();
			}
		} else if (pWeapon->GetType() == WEAPONTYPE_SHOTGUN) {
			if (pWeapon->GetState() == WEAPONSTATE_RELOADING) {
				GTAfunc_DisembarkInstantly();
				dwTime = GetTickCount();
			}
		}
	}
}

void func_engine_always_on()
{
	if (menu.always_engine_on) {
		mem::copy((PVOID)(SAMP_SETENGINESTATE), "\xC2\x04\x00", 3, 1, "\x55\x8B\xEC");

		vehicle_info *vinfo = vehicle_info_get(VEHICLE_SELF);
		if (vinfo && !vinfo->m_nVehicleFlags.bEngineOn) {
			vinfo->m_nVehicleFlags.bEngineOn = true;
		}
	} else mem::copy((PVOID)(SAMP_SETENGINESTATE), "\x55\x8B\xEC", 3, 1, "\xC2\x04\x00");
}

void func_marker_teleport()
{
	if (isKeyDown(VK_LCONTROL) && isKeyPressed(VK_RBUTTON))
	{
		if(!gta_map_marker_active())
			return pCRMP->getChat()->addMessageToChat(COLOR_MSG_ERROR, "Ошибка! Поставьте метку на карте.");
		
		float coords[3] = { 0.f, 0.f, 0.f };
		if (gta_map_marker_get(coords)) 
		{
			pCRMP->getChat()->addMessageToChat(COLOR_MSG_SUCCESS, 
				"Вы были телепортированы на координаты: %0.2f %0.2f %0.2f",
				coords[0], coords[1], coords[2]);
			gta_teleport(coords);
		
		} 
	}
}

void func_flooder()
{
	static DWORD dwTime = GetTickCount(), iter = 0;

	if (menu.flooder) 
	{
		if (dwTime < GetTickCount() - (int)(ini.flood_delay * 1000.f)) {
			if (iter >= ini.flood_string.size() || ini.flood_string[iter].empty()) iter = 0;
			pCRMP->getPlayers()->pLocalPlayer->say(ini.flood_string[iter++].c_str());
			dwTime = GetTickCount();
		}
	} else iter = 0;
}

void func_keep_trailer()
{
	static vehicle_info *trailer = nullptr;
	if (menu.keep_trailer)
	{
		if (trainer.state == CHEAT_STATE_VEHICLE) {
			vehicle_info *vinfo = vehicle_info_get(VEHICLE_SELF);
			if (vinfo == nullptr) {
				trailer = nullptr; return;
			} else if (vinfo->trailer != nullptr) {
				trailer = vinfo->trailer;
			} else if (vinfo->trailer != trailer) {
				gta_trailer_attach(vinfo, trailer, true);
			}
		} else trailer = nullptr;
	} else trailer = nullptr;
}

void func_antifreze()
{
	static bool install = false;
	if (menu.antifreeze) {
		if (!install) {
			sampSyncDisable(RPC_TogglePlayerControllable, INCOMING_RPC, true);
			install = true;
		}
	} else if (install) {
		sampSyncDisable(RPC_TogglePlayerControllable, INCOMING_RPC, false);
		install = false;
	}
}

void func_antistun()
{
	static bool install = false;
	if (menu.antistun) {
		if (install == false) {
			ScriptCommand(&set_stun, pCRMP->getPlayers()->pLocalPlayer->pSAMP_Actor->dwScriptID, TRUE);
			install = true;
		}
	} else if (install) {
		ScriptCommand(&set_stun, pCRMP->getPlayers()->pLocalPlayer->pSAMP_Actor->dwScriptID, FALSE);
		install = false;
	} else install = false;

}
