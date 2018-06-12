/*
		AUTHOR: SlonoBoyko
		LiteHack.Ru
		21.05.2018
*/

#include <main.h>

void HandleRPCPacketFunc(uint8_t uniqueID, RPCParameters *rpcParams, void(*callback) (RPCParameters *))
{
	if (rpcParams != nullptr && rpcParams->numberOfBitsOfData >= 8)
	{
		BitStream	bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);

		//Log("uniqueID: %d | %s", uniqueID, RpcEnumeration[uniqueID]);

		if (uniqueID == RPC_ClientMessage)
		{
			uint32_t		dwStrLen, dwColor;
			char			szMsg[260];

			bsData.ResetReadPointer();
			bsData.Read(dwColor);
			bsData.Read(dwStrLen);
			if (dwStrLen >= sizeof(szMsg)) dwStrLen = sizeof(szMsg) - 1;
			bsData.Read(szMsg, dwStrLen);
			szMsg[dwStrLen] = '\0';

			if (menu.chat_ids && !strstr(szMsg, "$cmd"))
			{
				string outstr = szMsg;
				for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
				{
					if (pCRMP->getPlayers()->sLocalPlayerID != i &&
						pCRMP->getPlayers()->isBadPlayer(i)) continue;

					const char *nick = pCRMP->getPlayers()->getPlayerName(i);
					const string check[2] = { ("[" + to_string(i) + "]"), ("(" + to_string(i) + ")") };

					size_t pos = outstr.find(nick);
					if (pos != string::npos)
					{
						pos += strlen(nick);
						if (outstr.find(check[0], pos) != string::npos ||
							outstr.find(check[1], pos) != string::npos)
							continue;
						else outstr.insert(pos, check[0]);
					}
				} return pCRMP->getChat()->addMessageToChat((dwColor >> 8) | 0xFF000000, outstr);

			}
		}

		if (uniqueID == RPC_ClearAnimations)
		{
			if (menu.noeject) return;
		}

		if (uniqueID == RPC_SetVehicleHealth)
		{
			WORD wVehicleID; float fHealth;

			bsData.ResetReadPointer();
			bsData.Read<WORD>(wVehicleID);
			bsData.Read<float>(fHealth);

			if (menu.good_mode && trainer.state == CHEAT_STATE_VEHICLE)
			{
				WORD wCurrentVehicleID = pCRMP->getPlayers()->pLocalPlayer->sCurrentVehicleID;
				if (wVehicleID == wCurrentVehicleID && fHealth < vehicle_info_get(VEHICLE_SELF)->hitpoints)
					return;
			}
		}

		if (uniqueID == RPC_SetPlayerHealth)
		{
			float fHealth;

			bsData.ResetReadPointer();
			bsData.Read<float>(fHealth);

			if (menu.good_mode && fHealth < pPedSelf->GetHealth())
				return;

		}


		if (uniqueID == RPC_ShowDialog)
		{
			WORD wDialogID; BYTE bDialogStyle;

			bsData.ResetReadPointer();
			bsData.Read<WORD>(wDialogID);
			bsData.Read<BYTE>(bDialogStyle);

			if (menu.autologin)
			{
				if (bDialogStyle == DIALOG_STYLE_INPUT || bDialogStyle == DIALOG_STYLE_PASSWORD)
				{
					if (pCRMP->getPlayers()->iLocalPlayerScore == 0)
					{
						static DWORD dwTime = NULL;
						if (dwTime < GetTickCount() - 5000)
						{
							pCRMP->getRakClient()->SendDialogResponse(wDialogID, 1, 0, ini.autologin_pass);
							dwTime = GetTickCount();
							return;
						}
					}
				}
			}
		}

		if (uniqueID == RPC_WorldPlayerRemove)
		{
			WORD wPlayerID;
			bsData.ResetReadPointer();
			bsData.Read(wPlayerID);

			if (!pCRMP->getPlayers()->isBadPlayer(wPlayerID))
			{
				actor_info *pGTA_Interface = pCRMP->getPlayers()->getGTAPed(wPlayerID);
				if (!isBadPtr_GTA_pPed(pGTA_Interface))
				{
					CPed *pPed = pPools->GetPed((PDWORD)pGTA_Interface);
					if (pPed) pPools->RemovePed(pPed, false);
				}
			}
		}
		if (uniqueID == RPC_WorldVehicleRemove)
		{
			WORD wVehicleID = 0;
			bsData.ResetReadPointer();
			bsData.Read(wVehicleID);

			if (!pCRMP->getVehicles()->isBadVehicle(wVehicleID))
			{
				vehicle_info *pGTA_Interface = pCRMP->getVehicles()->pGTA_Vehicle[wVehicleID];
				if (!isBadPtr_GTA_pVehicle(pGTA_Interface)) 
				{
					CVehicle *pVehicle = pPools->GetVehicle((PDWORD)pGTA_Interface);
					if (pVehicle) pPools->RemoveVehicle(pVehicle, false);
				}
			}
		}
	}

	for (int i = 0; i < RAKNET_MAX_PACKET; i++)
	{
		if (ini.patch[i].id == uniqueID && ini.patch[i].enabled && ini.patch[i].type == INCOMING_RPC)
			return;
	}

	return callback(rpcParams);
}

void __declspec(naked) hook_handle_rpc_packet(void)
{
	static RPCParameters	*pRPCParams = nullptr;
	static RPCNode			*pRPCNode = nullptr;
	static DWORD			dwTmp = 0;

	__asm pushad;
	__asm mov pRPCParams, eax;
	__asm mov pRPCNode, ecx;

	HandleRPCPacketFunc(*pRPCNode->uniqueIdentifier, pRPCParams, pRPCNode->staticFunctionPointer);
	dwTmp = SAMP_HOOKEXIT_HANDLE_RPC;

	__asm popad;
	__asm add esp, 4;
	__asm jmp dwTmp;
}


void __declspec(naked) hook_handle_rpc_packet_2(void)
{
	static RPCParameters *pRPCParams = nullptr;
	static RPCNode *pRPCNode = nullptr;
	static DWORD dwTmp = 0;

	__asm pushad;
	__asm mov pRPCParams, ecx;
	__asm mov pRPCNode, edx;

	HandleRPCPacketFunc(*pRPCNode->uniqueIdentifier, pRPCParams, pRPCNode->staticFunctionPointer);
	dwTmp = SAMP_HOOKEXIT_HANDLE_RPC;

	__asm popad;
	__asm add esp, 8;
	__asm jmp dwTmp;
}

void __stdcall CNetGame_destructor(void)
{
	stSAMP *pSamp = pCRMP->getInfo();
	if (pSamp != NULL && pSamp->pRakClientInterface != NULL)
		delete pSamp->pRakClientInterface;
	pSamp->pRakClientInterface = pCRMP->getRakClient()->GetInterface();
	return func::thiscall(SAMP_FUNC_CNETGAMEDESTRUCTOR, pSamp);
}

void *__stdcall Hook_CloseDialog()
{
	stDialogInfo *pDialog = pCRMP->getDialog();
	return func::thiscall<void*>(SAMP_FUNC_CLOSEDIALOG, pDialog);
}

void __declspec(naked) CPlayer_Constructor()
{
	static DWORD dwRet = NULL;
	static stSAMPPed *actor = nullptr;

	__asm mov fs : [00000000h], ecx;
	__asm pushad;

	__asm mov actor, eax;

	if (!isBadPtr_GTA_pPed(actor->pGTA_Ped))
		pPools->AddPed((PDWORD)actor->pGTA_Ped);

	dwRet = SAMP_HOOKEXIT_CVEHICLECONSTRUCTOR;
	__asm popad;
	__asm jmp dwRet;
}

void __declspec(naked) CVehicle_Constructor()
{
	static DWORD dwRet = NULL;
	static stSAMPVehicle *vehicle = nullptr;

	__asm mov fs : [00000000h], ecx;
	__asm pushad;

	__asm mov vehicle, eax;

	if (!isBadPtr_GTA_pVehicle(vehicle->pGTA_Vehicle))
		pPools->AddVehicle((PDWORD)vehicle->pGTA_Vehicle);

	dwRet = SAMP_HOOKEXIT_CPLAYERCONSTRUCTOR;
	__asm popad;
	__asm jmp dwRet;
}

/*		GAME MEMORY HOOKS		*/

// It's just pizdec. Don't read it, please.
void __declspec(naked) HOOK_PlayerCollision(void)
{
	static struct entity_base *self, *target, *aself, *vself;
	static struct actor_info *info = nullptr;
	static DWORD _return = RETURN_CollisionProcess, _ovrwr = 0x54CEFC;

	__asm jz hooking;
	__asm jmp _ovrwr;

hooking:

	__asm pushad;
	__asm mov self, esi;
	__asm mov target, edi;

	aself =	*reinterpret_cast<entity_base **>(ACTOR_POINTER_SELF);
	vself =	*reinterpret_cast<entity_base **>(VEHICLE_POINTER_SELF);

	if (!menu.veh_col && !menu.obj_col && !menu.play_col)
		_return = RETURN_CollisionProcess;
	else if (self == nullptr || target == nullptr || (info = (actor_info*)aself) == nullptr)
		_return = RETURN_CollisionNoProcessing;
	else if ((self->nType == ENTITY_TYPE_PED && self == aself) || (self->nType == ENTITY_TYPE_VEHICLE && self == vself)	// if for my
			 || (target->nType == ENTITY_TYPE_PED && target == aself) || (target->nType == ENTITY_TYPE_VEHICLE && target == vself)) // if from my
	{
		if (info->item_contact == self || info->item_contact == target || info->pedFlags.bIsLanding)
			_return = RETURN_CollisionProcess;
		else if (menu.play_col && target->nType == ENTITY_TYPE_PED && (self == aself || target == aself))
			_return = RETURN_CollisionNoProcessing;
		else if (menu.veh_col && (self->nType == ENTITY_TYPE_VEHICLE && target->nType == ENTITY_TYPE_VEHICLE) && (self == vself || target == vself))
			_return = RETURN_CollisionNoProcessing;
		else if (menu.veh_col && (target->nType == ENTITY_TYPE_VEHICLE && self->nType == ENTITY_TYPE_PED && self == aself) 
			|| (self->nType == ENTITY_TYPE_VEHICLE && target->nType == ENTITY_TYPE_PED && target == aself))
			_return = RETURN_CollisionNoProcessing;
		else if (menu.obj_col && (self->nType == ENTITY_TYPE_PED || self->nType == ENTITY_TYPE_VEHICLE) && target->nType == ENTITY_TYPE_OBJECT)
			_return = RETURN_CollisionNoProcessing;
		else _return = RETURN_CollisionProcess;
	} else _return = RETURN_CollisionProcess;

	__asm popad;
	__asm jmp _return;
}

void __declspec(naked) HOOK_FixMouseStuck(void)
{
	static DWORD _return = RETURN_FixMouseStuck_Cont;

	__asm	mov eax, [esp + 08h]; // eax = y pos
	__asm	mov ecx, [esp + 04h]; // ecx = x pos
	__asm	pushad;

	if (*(HWND *)GAME_DEVICE_WINDOW != GetForegroundWindow())
		_return = RETURN_FixMouseStuck_Exit;

	__asm	popad;
	__asm	jmp _return;
}

DWORD RETURN_CrashFix_Misc = 0x4D1755;
DWORD RETURN_CrashFix_Misc_2 = 0x4D1A44;
void __declspec(naked) HOOK_CrashFix_Misc()
{
	__asm test	ecx, ecx;
	__asm je	cont;
	__asm mov	eax, dword ptr[ecx + 10h];
	__asm test	eax, eax;
	__asm jmp	RETURN_CrashFix_Misc;
cont:
	__asm jmp	RETURN_CrashFix_Misc_2;
}

DWORD RETURN_CrashFix_Anim = 0x5E581B;
void _declspec(naked) HOOK_CrashFix_Anim()
{
	__asm cmp     eax, 0;
	__asm je      cont;

	__asm movsx   ecx, word ptr[eax + 2Ch];
	__asm xor     edi, edi;
	__asm jmp     RETURN_CrashFix_Anim;

cont:
	__asm add     esp, 96;
	__asm retn;

}

BYTE __stdcall CPad_UpdateGameKey(int idx)
{
	BYTE result = func::thiscall<BYTE>(FUNC_CPad_StopPads, (CPadSA *)CPad_StoppedPadInteface, idx);

	int16_t *key_state = (int16_t *)CLASS_CPad;
	for (int i = 0; i < 0x20; i++) {
		if (trainer.gameKeyState[i]) {
			key_state[i] = trainer.gameKeyState[i];
			trainer.gameKeyState[i] = 0;
		}
	} return result;
}

void InstallAllHooks()
{
	hook::jump(HOOKPOS_PlayerCollision, HOOK_PlayerCollision);
	hook::jump(HOOKPOS_FixMouseStuck, HOOK_FixMouseStuck);
	hook::jump(HOOKPOS_CrashFix_Misc, HOOK_CrashFix_Misc);
	hook::jump(HOOKPOS_CrashFix_Anim, HOOK_CrashFix_Anim);
	hook::call(HOOKCALL_UpdateGameKey, CPad_UpdateGameKey);

	/*  CRMP HOOKS  */
	hook::jump(SAMP_HOOKENTER_HANDLE_RPC, hook_handle_rpc_packet);
	hook::jump(SAMP_HOOKENTER_HANDLE_RPC_2, hook_handle_rpc_packet_2);
	hook::call(SAMP_HOOKCALL_CNETGAMEDESTRUCTOR, CNetGame_destructor);
	hook::call(SAMP_HOOKCALL_CNETGAMEDESTRUCTOR_2, CNetGame_destructor);
	hook::call(SAMP_HOOKCALL_CLOSEDIALOG, Hook_CloseDialog);

	hook::jump(SAMP_HOOKENTER_CPLAYERCONSTRUCTOR, CPlayer_Constructor, 6);
	hook::jump(SAMP_HOOKENTER_CVEHICLECONSTRUCTOR, CVehicle_Constructor, 6);

	HWND hWnd = *reinterpret_cast<HWND *>(GAME_DEVICE_WINDOW);
	g_origWndProc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)WndProcHook);
}