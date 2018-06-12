/*
				Almost all functions from m0d_s0beit sa
				But some of them I wrote =)
*/

#include "main.h"
 
CPools						*pPools			= nullptr;
CPed						*pPedSelf		= nullptr;
 
struct pool					*pool_vehicle	= nullptr;
struct pool					*pool_actor		= nullptr;
struct pool					*pool_object	= nullptr;

void InitSmallGamePools()
{
	pool_vehicle =	*reinterpret_cast<struct pool **>	(VEHICLE_POOL_POINTER);
	pool_actor =	*reinterpret_cast<struct pool **>	(ACTOR_POOL_POINTER);
	pool_object =	*reinterpret_cast<struct pool **>	(OBJECT_POOL_POINTER);
}
BOOL isBadPtr_GTA_pVehicle(vehicle_info * p_VehicleInfo)
{
	if (p_VehicleInfo == NULL) return TRUE;
	if (!((DWORD)p_VehicleInfo >= (DWORD)pool_vehicle->start
		&& (DWORD)p_VehicleInfo <= ((DWORD)pool_vehicle->start + (pool_vehicle->size * sizeof(vehicle_info)))))
		return TRUE;
	return BOOL(p_VehicleInfo->base.matrix == NULL);
}

BOOL isBadPtr_GTA_pVehicle(CVehicle * p_CVehicle)
{
	if (p_CVehicle == NULL) return TRUE;
	CVehicleSAInterface *p_CVehicleSAInterface = p_CVehicle->GetVehicleInterface();
	if (p_CVehicleSAInterface == NULL) return 1;
	if (!((DWORD)p_CVehicleSAInterface >= (DWORD)pool_vehicle->start
		&& (DWORD)p_CVehicleSAInterface <= ((DWORD)pool_vehicle->start + (pool_vehicle->size * sizeof(CVehicleSAInterface)))))
		return TRUE;
	return BOOL(p_CVehicleSAInterface->Placeable.matrix == NULL);
}

BOOL isBadPtr_GTA_pVehicle(CVehicleSA * p_CVehicleSA)
{
	if (p_CVehicleSA == NULL) return TRUE;
	CVehicleSAInterface *p_CVehicleSAInterface = p_CVehicleSA->GetVehicleInterface();
	if (p_CVehicleSAInterface == NULL) return 1;
	if (!((DWORD)p_CVehicleSAInterface >= (DWORD)pool_vehicle->start
		&& (DWORD)p_CVehicleSAInterface <= ((DWORD)pool_vehicle->start + (pool_vehicle->size * sizeof(CVehicleSAInterface)))))
		return TRUE;
	return BOOL(p_CVehicleSAInterface->Placeable.matrix == NULL);
}

BOOL isBadPtr_GTA_pVehicle(CVehicleSAInterface * p_CVehicleSAInterface)
{
	if (p_CVehicleSAInterface == NULL) return 1;
	if (!((DWORD)p_CVehicleSAInterface >= (DWORD)pool_vehicle->start
		&& (DWORD)p_CVehicleSAInterface <= ((DWORD)pool_vehicle->start + (pool_vehicle->size * sizeof(CVehicleSAInterface)))))
		return TRUE;
	return BOOL(p_CVehicleSAInterface->Placeable.matrix == NULL);
}

BOOL isBadPtr_GTA_pPed(actor_info * p_ActorInfo)
{
	if (p_ActorInfo == NULL) return TRUE;
	if (!((DWORD)p_ActorInfo >= (DWORD)pool_actor->start
		&& (DWORD)p_ActorInfo <= ((DWORD)pool_actor->start + (pool_actor->size * sizeof(actor_info)))))
		return TRUE;
	return BOOL(p_ActorInfo->base.matrix == NULL);
}

BOOL isBadPtr_GTA_pPed(CPed * p_CPed)
{
	if (p_CPed == NULL) return TRUE;
	CPedSAInterface *pCPedSAInterface = p_CPed->GetPedInterface();
	if (!((DWORD)pCPedSAInterface >= (DWORD)pool_actor->start
		&& (DWORD)pCPedSAInterface <= ((DWORD)pool_actor->start + (pool_actor->size * sizeof(CPedSAInterface)))))
		return TRUE;
	return BOOL(pCPedSAInterface->Placeable.matrix == NULL);
}

BOOL isBadPtr_GTA_pPed(CPedSAInterface * p_CPedSAInterface)
{
	if (p_CPedSAInterface == NULL) return TRUE;
	if (!((DWORD)p_CPedSAInterface >= (DWORD)pool_actor->start
		&& (DWORD)p_CPedSAInterface <= ((DWORD)pool_actor->start + (pool_actor->size * sizeof(CPedSAInterface))))) 
		return TRUE;
	return BOOL(p_CPedSAInterface->Placeable.matrix == NULL);
}

BOOL isBadPtr_GTA_pObject(CObjectSAInterface * p_CObjectSAInterface)
{
	if (p_CObjectSAInterface == NULL) return TRUE;

	if (!((DWORD)p_CObjectSAInterface >= (DWORD)pool_object->start
		&& (DWORD)p_CObjectSAInterface <= ((DWORD)pool_object->start + (pool_object->size * sizeof(CObjectSAInterface)))))
		return TRUE;
	return BOOL(p_CObjectSAInterface->Placeable.matrix == NULL);
}

BOOL isBadPtr_GTA_pObject(object_info * p_ObjectInfo)
{
	if (p_ObjectInfo == NULL) return TRUE;

	if (!((DWORD)p_ObjectInfo >= (DWORD)pool_object->start 
		&& (DWORD)p_ObjectInfo <= ((DWORD)pool_object->start + (pool_object->size * sizeof(object_info)))))
		return TRUE;
	return BOOL(p_ObjectInfo->base.matrix == NULL);
}

struct vehicle_info *vehicle_info_get(int id, int flags)
{
	struct vehicle_info *info = nullptr;

	if (pool_vehicle == NULL) return nullptr;
	if (id < VEHICLE_SELF || id >= pool_vehicle->size) return nullptr;

	if (id == VEHICLE_SELF) {
		info = *reinterpret_cast<vehicle_info **>(VEHICLE_POINTER_SELF);
		if (isBadPtr_GTA_pVehicle(info)) return nullptr;
	} else {
		info = &(reinterpret_cast<vehicle_info *>(pool_vehicle->start))[id];
		if (isBadPtr_GTA_pVehicle(info)) return nullptr;
	}

	// filtering for VEHICLE_EMPTY
	// put it here if we ever actually use it =P
	if ((flags & VEHICLE_ALIVE) && (info->hitpoints < 250.0f && info->burn_timer == 0.0f))
		return nullptr;

	return info;
}

struct actor_info *actor_info_get(int id, int flags)
{
	struct actor_info *info = nullptr;

	if (pool_actor == nullptr) return nullptr;
	if (id < ACTOR_SELF || id >= pool_actor->size) return nullptr;

	if (id == ACTOR_SELF) {
		info = *reinterpret_cast<actor_info **>(ACTOR_POINTER_SELF);
		if (isBadPtr_GTA_pPed(info)) return nullptr;
	} else {
		info = &(reinterpret_cast<actor_info *>(pool_actor->start))[id];
		if (isBadPtr_GTA_pPed(info)) return nullptr;
	}

	/* XXX this should not be nessecary... but it is. fix it. */
	if (vect3_near_zero(&info->base.matrix[4 * 3]))
		return nullptr;

	if ((flags & ACTOR_ALIVE) && ACTOR_IS_DEAD(info))
		return nullptr;

	/* exclude actors in the same car as ACTOR_SELF */
	if (flags & ACTOR_NOT_SAME_VEHICLE)
	{
		struct actor_info *self = actor_info_get(ACTOR_SELF);

		if (self != nullptr && info->state == ACTOR_STATE_DRIVING 
			&& self->state == ACTOR_STATE_DRIVING && info->vehicle == self->vehicle) 
			return nullptr;
	}

	return info;
}

bool gta_map_marker_get(float fPos[3])
{
	if (*(int *)0xBA6774 == 0) return false;

	for (int i = 0; i < MAX_MARKERS; i++) {
		CMarker * pMarker = pGame->GetRadar()->GetMarker(i);
		if (!pMarker->IsActive() || !pMarker->IsBright()) continue;
		if (pMarker->GetBlipType() != MARKER_TYPE_COORDS) continue;
		if (pMarker->GetSprite() != MARKER_SPRITE_WAYPOINT) continue;
		if (pMarker->GetPosition()->IsNearZero()) continue;

		vect3_copy(*pMarker->GetPosition(), fPos);
		fPos[2] = pGame->GetWorld()->FindGroundZForPosition(fPos[0], fPos[1]) + 1.f;
		return true;
	}
	return false;
}

bool gta_world_marker_get(float fPos[3])
{
	for (int i = 0; i < MAX_3D_MARKERS; i++) {
		C3DMarker *pMarker = pGame->Get3DMarkers()->GetMarker(i);
		if (pMarker == NULL || !pMarker->IsActive()) continue;
		if (pMarker->GetPosition()->IsNearZero()) continue;
		vect3_copy(*pMarker->GetPosition(), fPos);
		fPos[2] += 1.0f;
		return true;
	}
	return false;
}

bool gta_map_marker_active(void)
{
	return (bool)*(uint32_t *)0xBA6774 != NULL;
}

bool gta_menu_active(void)
{
	return (bool)*(uint32_t *)0xBA67A4 != NULL;
}

int gta_interior_id_get(void)
{
	return (int)*(uint32_t *)0x00B72914;
}

void gta_interior_id_set(int id)
{
	struct actor_info *info = actor_info_get(ACTOR_SELF);
	if (info != NULL) {
		info->base.interior_id = id;
		if (info->state == ACTOR_STATE_DRIVING && info->vehicle)
			info->vehicle->base.interior_id = id;
	} mem::copy((uint32_t *)0x00B72914, &id, sizeof(int));
}

void gta_set_gamekey_state(ePadType key, int16_t state)
{
	if (key >= 0 && key < 0x20) {
		trainer.gameKeyState[key] = state;
	}
}

float *gta_collision_normal_get(vehicle_info *vehicle, float fPos[3])
{
	if (isBadPtr_GTA_pVehicle(vehicle) || vect3_near_zero(fPos))
		return nullptr;
	
	CVector vUp; 
	CColPoint *pCollision = nullptr;
	CEntitySAInterface *pCollEntity = nullptr; 
	CVehicle *pVehicle = pPools->GetVehicle((PDWORD)vehicle);

	pVehicle->GetWas(&vUp);

	if (GTAfunc_ProcessLineOfSight(&((-vUp * 5.f) + fPos), &((vUp * 5.f) + fPos), &pCollision, &pCollEntity,
								   true, false, false, true, true, false, false, false) && pCollision)
	{
		CVector vNormal = *pCollision->GetNormal();
		vNormal.Normalize(); vNormal.ZeroNearZero();
		pCollision->Destroy();

		return vNormal;
	}
	return nullptr;
}

void gta_rotate_along_surface(vehicle_info *vehicle, float fPos[3])
{
	if (isBadPtr_GTA_pVehicle(vehicle) || vect3_near_zero(fPos)) return;

	float fPosZ = pGame->GetWorld()->FindGroundZForPosition(fPos[0], fPos[1]);
	float *fNormal = gta_collision_normal_get(vehicle, fPos);
	if (fNormal == nullptr) return;
	
	CVector vNormal = fNormal; CMatrix matVehicleSelf;
	CVehicle *pVehicle = pPools->GetVehicle((PDWORD)vehicle);
	pVehicle->GetMatrix(&matVehicleSelf);

	CVector vAxis = matVehicleSelf.vUp;
	vAxis.Normalize(); vNormal.Normalize();

	float theta = acos(vAxis.DotProduct(&vNormal));
	if (!near_zero(theta)) {
		vAxis.CrossProduct(&vNormal);
		vAxis.Normalize(); vAxis.ZeroNearZero();
		matVehicleSelf = matVehicleSelf.Rotate(&vAxis, -theta);
	}

	if (fabsf(fPos[2] - fPosZ) < 5.f)
		matVehicleSelf.vPos.fZ = fPosZ + pVehicle->GetHeightAboveRoad();

	pVehicle->SetMatrix(&matVehicleSelf);

}

void gta_vehicle_zero_speed(vehicle_info *vehicle)
{
	if (vehicle == nullptr) return;

	vect3_zero(vehicle->speed);
	vect3_zero(vehicle->spin);
	vect3_zero(vehicle->speed_rammed);
	vect3_zero(vehicle->spin_rammed);
}

void gta_trailer_attach(vehicle_info *vehicle, vehicle_info *trailer, bool and_tp, bool at_surface)
{
	if (isBadPtr_GTA_pVehicle(vehicle) || isBadPtr_GTA_pVehicle(trailer)) return;

	CVehicle *pVehicle = pPools->GetVehicle((PDWORD)vehicle);
	CVehicle *pTrailer = pPools->GetVehicle((PDWORD)trailer);
	
	if (and_tp == false)
		return (void)pVehicle->SetTowLink(pTrailer);
	
	CVector vecTowBar, vecTowHitch;
	if (!pVehicle->GetTowBarPos(&vecTowBar)) return;
	if (!pTrailer->GetTowHitchPos(&vecTowHitch)) return;
	CVector	vecDest = (trailer->base.m_CMatrix->vPos - vecTowHitch) + vecTowBar;
	pTrailer->Teleport(vecDest.fX, vecDest.fY, vecDest.fZ);
	vect3_copy(vehicle->speed, trailer->speed);
	
	if (at_surface) gta_rotate_along_surface(trailer, vecDest);

	return (void)pVehicle->SetTowLink(pTrailer);
}

void gta_teleport(float fPos[3], int interior_id)
{
	if (vect3_near_zero(fPos)) return;	
	if (trainer.state == CHEAT_STATE_VEHICLE) {
		vehicle_info *vehicle = vehicle_info_get(VEHICLE_SELF);
		if (vehicle == nullptr) return;
		
		vehicle_info *trailer = vehicle->trailer;
		CVehicle *pVehicle = pPedSelf->GetVehicle();
		pVehicle->Teleport(fPos[0], fPos[1], fPos[2]);
		
		gta_rotate_along_surface(vehicle, fPos);
		gta_vehicle_zero_speed(vehicle);
		gta_trailer_attach(vehicle, trailer, true, true);
	} else pPedSelf->SetPosition(fPos[0], fPos[1], fPos[2]);
	
	gta_interior_id_set(interior_id);
}

struct vehicle_entry *gta_vehicle_get_by_id(int id)
{
	id -= VEHICLE_LIST_ID_START;
	if (id < 0 || id >= VEHICLE_LIST_SIZE) return NULL;
	return const_cast<vehicle_entry *>(&vehicle_list[id]);
}

RwColor getVehicleColorRGB(unsigned int index)
{
	RwColor *color_table = *reinterpret_cast <RwColor **> (0x4C8390);
	return color_table[index];
}

void GTAfunc_loadAllWeaponModels(void)
{
	const struct weapon_entry *weapon;
	for (weapon = weapon_list; weapon->id > 0; weapon++) {
		if (weapon->model_id == -1) continue;
		CModelInfo *pCModel = pGame->GetModelInfo(weapon->model_id);
		if (pCModel->IsLoaded()) continue;
		else pCModel->Request(true);
	}
}

void GTAfunc_loadSpecificModel(int iModelID)
{
	CModelInfo *pModel = pGame->GetModelInfo(iModelID);
	
	if (pModel->IsLoaded()) return;
	pModel->Request(true);
	while (!pModel->IsLoaded()) Sleep(10);
}

bool GTAfunc_IsUpgradeAvailable(int m_dwModelID, eVehicleUpgradePosn posn)
{
	bool	bRet = false;
	DWORD	ModelID = m_dwModelID;
	
	__asm	mov eax, ModelID;
	__asm 	lea ecx, ARRAY_ModelInfo[eax * 4];

	__asm	mov eax, posn;
	__asm	mov ecx, [ecx + 0x5C];
	__asm	shl eax, 5;
	__asm	push esi;
	__asm	mov esi, [ecx + eax + 0x0D0];
	__asm	xor edx, edx;
	__asm	test esi, esi;
	__asm	setnl dl;
	__asm	mov al, dl;
	__asm	pop esi;
	__asm	mov bRet, al;
	

	return bRet;
}

eClientVehicleType GTAfunc_getVehicleType(int iModelID)
{
	CModelInfo * pCModel =				pGame->GetModelInfo(iModelID);
	
	if (pCModel->IsValid()) {
		if (pCModel->IsCar())			return CLIENTVEHICLE_CAR;
		if (pCModel->IsBike())			return CLIENTVEHICLE_BIKE;
		if (pCModel->IsPlane())			return CLIENTVEHICLE_PLANE;
		if (pCModel->IsHeli())			return CLIENTVEHICLE_HELI;
		if (pCModel->IsBoat())			return CLIENTVEHICLE_BOAT;
		if (pCModel->IsQuadBike())		return CLIENTVEHICLE_QUADBIKE;
		if (pCModel->IsBmx())			return CLIENTVEHICLE_BMX;
		if (pCModel->IsMonsterTruck())	return CLIENTVEHICLE_MONSTERTRUCK;
		if (pCModel->IsTrailer())		return CLIENTVEHICLE_TRAILER;
		if (pCModel->IsTrain())			return CLIENTVEHICLE_TRAIN;
	}

	// Invalid vehicle id or some other error
	return CLIENTVEHICLE_NONE;
}

bool GTAfunc_IsUpgradeCompatible(int iModelID, vehicle_info *vinfo)
{
	// get vehicle model
	int					usModel = vinfo->base.model_alt_id;

	// get vehicle type
	eClientVehicleType	vehicleType = GTAfunc_getVehicleType(usModel);

	// no upgrades for you!
	if (vehicleType == CLIENTVEHICLE_BOAT || vehicleType == CLIENTVEHICLE_TRAIN || vehicleType == CLIENTVEHICLE_HELI
		|| vehicleType == CLIENTVEHICLE_PLANE || vehicleType == CLIENTVEHICLE_BIKE || vehicleType == CLIENTVEHICLE_BMX) return false;

	// shorter upgrade model id variable
	unsigned short	us = iModelID;

	// these can go on any vehicle that hasn't been filtered out yet
	if (us == VEHICLEUPGRADE_NITRO_5X || us == VEHICLEUPGRADE_NITRO_2X || us == VEHICLEUPGRADE_NITRO_10X)
		return true;

	// hydraulics on the rest except for monster trucks
	if (us == VEHICLEUPGRADE_HYDRAULICS && vehicleType != CLIENTVEHICLE_MONSTERTRUCK)
		return true;

	// Wheels should be compatible with any car
	if (us == 1025 || us == 1073 || us == 1074 || us == 1075 || us == 1076 || us == 1077 || us == 1078 || us == 1079
		|| us == 1080 || us == 1081 || us == 1082 || us == 1083 || us == 1084 || us == 1085
		|| us == 1096 || us == 1097 || us == 1098)
	{
	//	Log("This are wheel");

		return true;

	}

	switch (usModel)
	{
		case 400:
			return us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1018
				|| us == 1013
				|| us == 1024
				|| us == 1008
				|| us == 1009
				|| us == 1010;

		case 401:
			return us == 1005
				|| us == 1004
				|| us == 1142
				|| us == 1143
				|| us == 1144
				|| us == 114
				|| us == 1020
				|| us == 1019
				|| us == 1013
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1001
				|| us == 1003
				|| us == 1017
				|| us == 1007;

		case 402:
			return us == 1009 || us == 1010;

		case 404:
			return us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1013
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1002
				|| us == 1016
				|| us == 1000
				|| us == 1017
				|| us == 1007;

		case 405:
			return us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1001
				|| us == 1014
				|| us == 1023
				|| us == 1000;

		case 409:
			return us == 1009;

		case 410:
			return us == 1019
				|| us == 1021
				|| us == 1020
				|| us == 1013
				|| us == 1024
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1001
				|| us == 1023
				|| us == 1003
				|| us == 1017
				|| us == 1007;

		case 411:
			return us == 1008 || us == 1009 || us == 1010;

		case 412:
			return us == 1008 || us == 1009 || us == 1010;

		case 415:
			return us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1001
				|| us == 1023
				|| us == 1003
				|| us == 1017
				|| us == 1007;

		case 418:
			return us == 1020
				|| us == 1021
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1002
				|| us == 1016;

		case 419:
			return us == 1008 || us == 1009 || us == 1010;

		case 420:
			return us == 1005
				|| us == 1004
				|| us == 1021
				|| us == 1019
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1001
				|| us == 1003;

		case 421:
			return us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1014
				|| us == 1023
				|| us == 1016
				|| us == 1000;

		case 422:
			return us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1013
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1017
				|| us == 1007;

		case 426:
			return us == 1005
				|| us == 1004
				|| us == 1021
				|| us == 1019
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1001
				|| us == 1003;

		case 429:
			return us == 1008 || us == 1009 || us == 1010;

		case 436:
			return us == 1020
				|| us == 1021
				|| us == 1022
				|| us == 1019
				|| us == 1013
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1001
				|| us == 1003
				|| us == 1017
				|| us == 1007;

		case 438:
			return us == 1008 || us == 1009 || us == 1010;

		case 439:
			return us == 1003
				|| us == 1023
				|| us == 1001
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1017
				|| us == 1007
				|| us == 1142
				|| us == 1143
				|| us == 1144
				|| us == 1145
				|| us == 1013;

		case 442:
			return us == 1008 || us == 1009 || us == 1010;

		case 445:
			return us == 1008 || us == 1009 || us == 1010;

		case 451:
			return us == 1008 || us == 1009 || us == 1010;

		case 458:
			return us == 1008 || us == 1009 || us == 1010;

		case 466:
			return us == 1008 || us == 1009 || us == 1010;

		case 467:
			return us == 1008 || us == 1009 || us == 1010;

		case 474:
			return us == 1008 || us == 1009 || us == 1010;

		case 475:
			return us == 1008 || us == 1009 || us == 1010;

		case 477:
			return us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1017
				|| us == 1007;

		case 478:
			return us == 1005
				|| us == 1004
				|| us == 1012
				|| us == 1020
				|| us == 1021
				|| us == 1022
				|| us == 1013
				|| us == 1024
				|| us == 1008
				|| us == 1009
				|| us == 1010;

		case 479:
			return us == 1008 || us == 1009 || us == 1010;

		case 480:
			return us == 1008 || us == 1009 || us == 1010;

		case 489:
			return us == 1005
				|| us == 1004
				|| us == 1020
				|| us == 1019
				|| us == 1018
				|| us == 1013
				|| us == 1024
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1002
				|| us == 1016
				|| us == 1000;

		case 490:
			return us == 1002 || us == 1016 || us == 1000 || us == 1020 || us == 1021 || us == 1019;

		case 491:
			return us == 1142
				|| us == 1143
				|| us == 1144
				|| us == 1145
				|| us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1014
				|| us == 1023
				|| us == 1003
				|| us == 1017
				|| us == 1007;

		case 492:
			return us == 1005
				|| us == 1004
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1016
				|| us == 1000;

		case 496:
			return us == 1006
				|| us == 1017
				|| us == 1007
				|| us == 1011
				|| us == 1019
				|| us == 1023
				|| us == 1001
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1003
				|| us == 1002
				|| us == 1142
				|| us == 1143
				|| us == 1020;

		case 500:
			return us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1013
				|| us == 1024
				|| us == 1008
				|| us == 1009
				|| us == 1010;

		case 505:
			return us == 1005
				|| us == 1004
				|| us == 1020
				|| us == 1019
				|| us == 1018
				|| us == 1013
				|| us == 1024
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1002
				|| us == 1016
				|| us == 1000;

		case 506:
			return us == 1009;

		case 507:
			return us == 1008 || us == 1009 || us == 1010;

		case 516:
			return us == 1004
				|| us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1002
				|| us == 1015
				|| us == 1016
				|| us == 1000
				|| us == 1017
				|| us == 1007;

		case 517:
			return us == 1142
				|| us == 1143
				|| us == 1144
				|| us == 1145
				|| us == 1020
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1002
				|| us == 1023
				|| us == 1016
				|| us == 1003
				|| us == 1017
				|| us == 1007;

		case 518:
			return us == 1005
				|| us == 1142
				|| us == 1143
				|| us == 1144
				|| us == 1145
				|| us == 1020
				|| us == 1018
				|| us == 1013
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1001
				|| us == 1023
				|| us == 1003
				|| us == 1017
				|| us == 1007;

		case 526:
			return us == 1008 || us == 1009 || us == 1010;

		case 527:
			return us == 1021
				|| us == 1020
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1001
				|| us == 1014
				|| us == 1015
				|| us == 1017
				|| us == 1007;

		case 529:
			return us == 1012
				|| us == 1011
				|| us == 1020
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1001
				|| us == 1023
				|| us == 1003
				|| us == 1017
				|| us == 1007;

		case 533:
			return us == 1008 || us == 1009 || us == 1010;

		case 534:
			return us == 1126
				|| us == 1127
				|| us == 1179
				|| us == 1185
				|| us == 1100
				|| us == 1123
				|| us == 1125
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1180
				|| us == 1178
				|| us == 1101
				|| us == 1122
				|| us == 1124
				|| us == 1106;

		case 535:
			return us == 1109
				|| us == 1110
				|| us == 1113
				|| us == 1114
				|| us == 1115
				|| us == 1116
				|| us == 1117
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1120
				|| us == 1118
				|| us == 1121
				|| us == 1119;

		case 536:
			return us == 1104
				|| us == 1105
				|| us == 1182
				|| us == 1181
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1184
				|| us == 1183
				|| us == 1128
				|| us == 1103
				|| us == 1107
				|| us == 1108;

		case 540:
			return us == 1004
				|| us == 1142
				|| us == 1143
				|| us == 1144
				|| us == 1145
				|| us == 1020
				|| us == 1019
				|| us == 1018
				|| us == 1024
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1001
				|| us == 1023
				|| us == 1017
				|| us == 1007;

		case 541:
			return us == 1008 || us == 1009 || us == 1010;

		case 542:
			return us == 1144
				|| us == 1145
				|| us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1014
				|| us == 1015;

		case 545:
			return us == 1008 || us == 1009 || us == 1010;

		case 546:
			return us == 1004
				|| us == 1142
				|| us == 1143
				|| us == 1144
				|| us == 1145
				|| us == 1019
				|| us == 1018
				|| us == 1024
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1002
				|| us == 1001
				|| us == 1023
				|| us == 1017
				|| us == 1007;

		case 547:
			return us == 1142
				|| us == 1143
				|| us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1016
				|| us == 1003
				|| us == 1000;

		case 549:
			return us == 1012
				|| us == 1011
				|| us == 1142
				|| us == 1143
				|| us == 1144
				|| us == 1145
				|| us == 1020
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1001
				|| us == 1023
				|| us == 1003
				|| us == 1017
				|| us == 1007;

		case 550:
			return us == 1005
				|| us == 1004
				|| us == 1142
				|| us == 1143
				|| us == 1144
				|| us == 1145
				|| us == 1020
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1001
				|| us == 1023
				|| us == 1003;

		case 551:
			return us == 1005
				|| us == 1020
				|| us == 1021
				|| us == 1019
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1002
				|| us == 1023
				|| us == 1016
				|| us == 1003;

		case 555:
			return us == 1008 || us == 1009 || us == 1010;

		case 558:
			return us == 1092
				|| us == 1089
				|| us == 1166
				|| us == 1165
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1168
				|| us == 1167
				|| us == 1088
				|| us == 1091
				|| us == 1164
				|| us == 1163
				|| us == 1094
				|| us == 1090
				|| us == 1095
				|| us == 1093;

		case 559:
			return us == 1065
				|| us == 1066
				|| us == 1160
				|| us == 1173
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1159
				|| us == 1161
				|| us == 1162
				|| us == 1158
				|| us == 1067
				|| us == 1068
				|| us == 1071
				|| us == 1069
				|| us == 1072
				|| us == 1070
				|| us == 1009;

		case 560:
			return us == 1028
				|| us == 1029
				|| us == 1169
				|| us == 1170
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1141
				|| us == 1140
				|| us == 1032
				|| us == 1033
				|| us == 1138
				|| us == 1139
				|| us == 1027
				|| us == 1026
				|| us == 1030
				|| us == 1031;

		case 561:
			return us == 1064
				|| us == 1059
				|| us == 1155
				|| us == 1157
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1154
				|| us == 1156
				|| us == 1055
				|| us == 1061
				|| us == 1058
				|| us == 1060
				|| us == 1062
				|| us == 1056
				|| us == 1063
				|| us == 1057;

		case 562:
			return us == 1034
				|| us == 1037
				|| us == 1171
				|| us == 1172
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1149
				|| us == 1148
				|| us == 1038
				|| us == 1035
				|| us == 1147
				|| us == 1146
				|| us == 1040
				|| us == 1036
				|| us == 1041
				|| us == 1039;

		case 565:
			return us == 1046
				|| us == 1045
				|| us == 1153
				|| us == 1152
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1150
				|| us == 1151
				|| us == 1054
				|| us == 1053
				|| us == 1049
				|| us == 1050
				|| us == 1051
				|| us == 1047
				|| us == 1052
				|| us == 1048;

		case 566:
			return us == 1008 || us == 1009 || us == 1010;

		case 567:
			return us == 1129
				|| us == 1132
				|| us == 1189
				|| us == 1188
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1187
				|| us == 1186
				|| us == 1130
				|| us == 1131
				|| us == 1102
				|| us == 1133;

		case 575:
			return us == 1044
				|| us == 1043
				|| us == 1174
				|| us == 1175
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1176
				|| us == 1177
				|| us == 1099
				|| us == 1042;

		case 576:
			return us == 1136
				|| us == 1135
				|| us == 1191
				|| us == 1190
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1192
				|| us == 1193
				|| us == 1137
				|| us == 1134;

		case 579:
			return us == 1008 || us == 1009 || us == 1010;

		case 580:
			return us == 1020
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1001
				|| us == 1023
				|| us == 1017
				|| us == 1007;

		case 585:
			return us == 1142
				|| us == 1143
				|| us == 1144
				|| us == 1145
				|| us == 1020
				|| us == 1019
				|| us == 1018
				|| us == 1013
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1001
				|| us == 1023
				|| us == 1003
				|| us == 1017
				|| us == 1007;

		case 587:
			return us == 1008 || us == 1009 || us == 1010;

		case 589:
			return us == 1005
				|| us == 1004
				|| us == 1144
				|| us == 1145
				|| us == 1020
				|| us == 1018
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1024
				|| us == 1013
				|| us == 1006
				|| us == 1016
				|| us == 1000
				|| us == 1017
				|| us == 1007;

		case 600:
			return us == 1005
				|| us == 1004
				|| us == 1020
				|| us == 1022
				|| us == 1018
				|| us == 1013
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1017
				|| us == 1007;

		case 602:
			return us == 1008 || us == 1009 || us == 1010;

		case 603:
			return us == 1144
				|| us == 1145
				|| us == 1142
				|| us == 1143
				|| us == 1020
				|| us == 1019
				|| us == 1018
				|| us == 1024
				|| us == 1008
				|| us == 1009
				|| us == 1010
				|| us == 1006
				|| us == 1001
				|| us == 1023
				|| us == 1017
				|| us == 1007;
	}

	// no mod for you
	return false;
}

void GTAfunc_addVehicleUpgrade(vehicle_info *vinfo, int iModelID)
{
	if (isBadPtr_GTA_pVehicle(vinfo)) return;
	if (iModelID >= 1000 && iModelID <= 1193)
	{
		CModelInfo *pCModel = pGame->GetModelInfo(iModelID);
		
		// is the mod compatible with my ride? (upgrade model, vehicle_info)
		if (!GTAfunc_IsUpgradeCompatible(iModelID, vinfo)) return;
		if (!pCModel->IsLoaded()) {
			pCModel->RequestVehicleUpgrade();
			pCModel->LoadAllRequestedModels();
		} while (!pCModel->IsLoaded()) Sleep(10);

		CVehicle * pCVeh = pPools->GetVehicle((PDWORD)vinfo);
		pCVeh->AddVehicleUpgrade(iModelID);

		if (pCRMP != NULL && pCRMP->getVehicles()) {
			uint16_t id = pCRMP->getVehicles()->getSAMPVehicleID(vinfo);
			pCRMP->getVehicles()->sendSCMEvent(EVENT_TYPE_CARCOMPONENT, id, iModelID, 0);
		}
	}
}

void GTAfunc_TogglePlayerControllable(bool bToggle)
{
	float fTen = 10.0f;
	((void(__thiscall *)(void *, bool, float))FUNC_MakePlayerSafe)((void *)ACTOR_POINTER_SELF, bToggle, fTen);

//	((CPlayerInfoSA *)pGame->GetPlayerInfo())->MakePlayerSafe(bToggle);

}

bool GTAfunc_IsLineOfSightClear(CVector *vecStart, CVector *vecEnd, bool bCheckBuildings, bool bCheckVehicles,
	bool bCheckPeds, bool bCheckObjects, bool bCheckDummies, bool bSeeThroughStuff,
	bool bIgnoreSomeObjectsForCamera)
{
	return ((bool(__cdecl *)(CVector *, CVector *, bool, bool, bool, bool, bool, bool, bool))FUNC_IsLineOfSightClear)(vecStart, vecEnd,
		bCheckBuildings, bCheckVehicles, bCheckPeds, bCheckObjects, bCheckDummies, bSeeThroughStuff, bIgnoreSomeObjectsForCamera);
}

bool GTAfunc_ProcessLineOfSight(CVector *vecStart, CVector *vecEnd, CColPoint **colCollision, CEntitySAInterface **CollisionEntity, 
	bool bCheckBuildings, bool bCheckVehicles, bool bCheckPeds, bool bCheckObjects, 
	bool bCheckDummies, bool bSeeThroughStuff, bool bIgnoreSomeObjectsForCamera, bool bShootThroughStuff)
{

	CColPointSA				*pColPointSA = new CColPointSA();
	CColPointSAInterface	*pColPointSAInterface = pColPointSA->GetInterface();
	CEntitySAInterface		*targetEntity = NULL;

	bool bReturn = ((bool(__cdecl *)(CVector *, CVector *, void *, void *, bool, bool, bool, bool, bool, bool, bool, bool))FUNC_ProcessLineOfSight)
		(vecStart, vecEnd, pColPointSAInterface, &targetEntity, bCheckBuildings, bCheckVehicles, bCheckPeds, bCheckObjects, 
		bCheckDummies, bSeeThroughStuff, bIgnoreSomeObjectsForCamera, bShootThroughStuff);

	*CollisionEntity = targetEntity;
	if (colCollision) *colCollision = pColPointSA;
	else pColPointSA->Destroy();

	return bReturn;
}

bool GTAfunc_testCheat(char *szCheat)
{
	if (!szCheat || strlen(szCheat) < 6 || strlen(szCheat) > 29) 
		return false;

	char *szCheatStr = (char *)FUNC_CheatString;
	char szCheatBuf[30]; strset(szCheatBuf, 0);
	
	strncpy(szCheatBuf, szCheatStr, strlen(szCheat));
	
	if (!stricmp(strrev(szCheatBuf), szCheat)) {
		strset(szCheatStr, 0);
		//pCRMP->getChat()->addMessageToChat(COLOR_MSG_INFO, "cheat = %s", szCheat);
		return true;
	}

	return false;
}

void GTAfunc_PutActorInCar(vehicle_info *vehicle)
{
	if (trainer.state == CHEAT_STATE_VEHICLE && pPedSelf->GetVehicle()){
		GTAfunc_RemoveActorFromCarAndPutAt(vehicle->base.m_CMatrix->vPos);
	}

	CVehicle *pVehicle = pPools->GetVehicle((DWORD *)vehicle);

	if (pVehicle && pVehicle->GetDriver() == NULL){
		CTaskSimpleCarSetPedInAsDriver* pInTask = pGame->GetTasks()->CreateTaskSimpleCarSetPedInAsDriver(pVehicle);
		if (pInTask) {
			pInTask->SetIsWarpingPedIntoCar();
			pInTask->ProcessPed(pPedSelf);
			pInTask->Destroy();
		}
		int iSAMPid = pCRMP->getVehicles()->getSAMPVehicleID(vehicle);
		if (pCRMP->getRakClient() && iSAMPid){
			pCRMP->getRakClient()->SendEnterVehicle(iSAMPid, 0);
		}
	}

	
}

void GTAfunc_PutActorInCarAsPassenger(vehicle_info *vehicle, int iSeat)
{
	if (trainer.state == CHEAT_STATE_VEHICLE && pPedSelf->GetVehicle()){
		GTAfunc_RemoveActorFromCarAndPutAt(vehicle->base.m_CMatrix->vPos);
	}

	CVehicle *pVehicle = pPools->GetVehicle((DWORD *)vehicle);

	if (pVehicle && iSeat <= pVehicle->GetMaxPassengerCount()){
		CTaskSimpleCarSetPedInAsPassenger* pInTask = pGame->GetTasks()->CreateTaskSimpleCarSetPedInAsPassenger(pVehicle, iSeat);
		if (pInTask) {
			pInTask->SetIsWarpingPedIntoCar();
			pInTask->ProcessPed(pPedSelf);
			pInTask->Destroy();
		}
		int iSAMPid = pCRMP->getVehicles()->getSAMPVehicleID(vehicle);
		if (pCRMP->getRakClient() && iSAMPid){
			pCRMP->getRakClient()->SendEnterVehicle(iSAMPid, 1);
		}
	}
}

void GTAfunc_RemoveActorFromCarAndPutAt(float fPos[3])
{
	if (pCRMP->getPlayers() == NULL) return;
	if (pCRMP->getPlayers()->pLocalPlayer == NULL) return;
	if (pCRMP->getPlayers()->pLocalPlayer->pSAMP_Actor == NULL) return;

	pCRMP->getPlayers()->pLocalPlayer->pSAMP_Actor->removeFromCarAndPutAt(fPos);
	if (pGame->GetCamera()->GetCam(pGame->GetCamera()->GetActiveCam())->GetMode() != MODE_FOLLOWPED) {
		GTAfunc_CameraOnActor(actor_info_get(ACTOR_SELF));
		pGame->GetCamera()->RestoreWithJumpCut();
	}
}

void GTAfunc_EnterCarAsDriver(vehicle_info *vehicle)
{
	CVehicle *pVehicle = pPools->GetVehicle((DWORD *)vehicle);
	if (pVehicle) {
		CTaskComplexEnterCarAsDriver* pInTask = pGame->GetTasks()->CreateTaskComplexEnterCarAsDriver(pVehicle);
		if (pInTask) pInTask->SetAsPedTask(pPedSelf, TASK_PRIORITY_PRIMARY, true);
	}
}

void GTAfunc_RepairVehicle(vehicle_info *vehicle)
{
	CVehicle *pVehicle = pPools->GetVehicle((DWORD *)vehicle);
	if (pVehicle) {
		pVehicle->Fix();
		pVehicle->SetHealth(1000.0f);
	}
}

void GTAfunc_CameraOnActor(actor_info *actor)
{
	if (actor == NULL) return;

	CEntity *pEntity = pPools->GetEntity((DWORD *)actor);
	CCamera *pCamera = pGame->GetCamera();
	if (pCamera && pEntity) {
		pCamera->TakeControl(pEntity, eCamMode::MODE_FOLLOWPED, 1);
	}
}

void GTAfunc_CameraOnVehicle(vehicle_info *vehicle)
{
	if (vehicle == NULL) return;

	CEntity *pEntity = pPools->GetEntity((DWORD *)vehicle);
	CCamera *pCamera = pGame->GetCamera();
	if (pCamera && pEntity){
		pCamera->TakeControl(pEntity, eCamMode::MODE_BEHINDCAR, 1);
	}
}

void GTAfunc_PerformAnimation(const char *szBlockName, const char *szAnimName, int iTime, bool bLoop,
	bool bUpdatePosition, bool bInterruptable, bool bFreezeLastFrame, bool bRunInSequence, bool bOffsetPed, bool bHoldLastFrame)
{
	CAnimBlock *pBlock = pGame->GetAnimManager()->GetAnimationBlock(szBlockName);
	if (pBlock){
		bool bLoaded = true;
		if (!pBlock->IsLoaded()){
			int iTimeToWait = 50;
			// load animations
			pGame->GetStreaming()->RequestAnimations(pBlock->GetIndex(), 4);
			pGame->GetStreaming()->LoadAllRequestedModels();

			while (!pBlock->IsLoaded() && iTimeToWait != 0) {
				iTimeToWait--;
				Sleep(10);
			}
			if (iTimeToWait == 0) bLoaded = false;
		}
		if (bLoaded) {
			// allow tasks to be removed
			pPedSelf->GetPedIntelligence()->GetTaskManager()->Flush(TASK_PRIORITY_PRIMARY);

			// removes temporary tasks caused by events like falling
			pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_EVENT_RESPONSE_TEMP);

			// remove jumping task
			CTask *jumpTask = pPedSelf->GetPedIntelligence()->GetTaskManager()->FindActiveTaskByType(211);
			if (jumpTask)pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_PRIMARY);
			

			// more removals if needed ever
			//pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_EVENT_RESPONSE_NONTEMP);
			//pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_PHYSICAL_RESPONSE);
			//pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_MAX);
			//pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_PRIMARY);

			// set flags
			int flags = 0x10; // // Stops jaw fucking up, some speaking flag maybe   
			if (bLoop) flags |= 0x2; // flag that triggers the loop (Maccer)
			if (bUpdatePosition){
				// 0x40 enables position updating on Y-coord, 0x80 on X. (Maccer)
				flags |= 0x40; 
				flags |= 0x80;
			}
			if (!bFreezeLastFrame) flags |= 0x08; // flag determines whether to freeze player when anim ends. Really annoying (Maccer)

			// create a new task
			CTask *pTask = pGame->GetTasks()->CreateTaskSimpleRunNamedAnim(
				szAnimName, pBlock->GetName(), flags, 4.0f, iTime, !bInterruptable, bRunInSequence, bOffsetPed, bHoldLastFrame);

			if (pTask)pTask->SetAsPedTask(pPedSelf, TASK_PRIORITY_PRIMARY);
		}else{
			// TODO: unload unreferenced blocks later on
			pGame->GetStreaming()->RequestAnimations(pBlock->GetIndex(), 8);
		}
	}
}

void GTAfunt_SetVehicleColor(vehicle_info *vinfo, int color0, int color1)
{
	if (vinfo == NULL) return;

	uint16_t sVehicleID = pCRMP->getVehicles()->getSAMPVehicleID(vinfo);
	if (sVehicleID && !pCRMP->getVehicles()->isBadVehicle(sVehicleID))
	{
		pCRMP->getVehicles()->sendSCMEvent(EVENT_TYPE_CARCOLOR, sVehicleID, color0, color1);
		pCRMP->getVehicles()->pSAMP_Vehicle[sVehicleID]->setColor(color0, color1);
	}
	else {
		vinfo->color[0] = color0;
		vinfo->color[1] = color1; 
	}
}

void GTAfunc_DisembarkInstantly()
{
	CTaskManager *taskManager = pPedSelf->GetPedIntelligence()->GetTaskManager();
	for (int i = 0; i < TASK_PRIORITY_MAX; i++)
	{
		CTask *pTask = taskManager->GetTask(i);
		if (pTask != nullptr)
		{
			pTask->MakeAbortable(pPedSelf, ABORT_PRIORITY_IMMEDIATE, NULL);
			taskManager->RemoveTask(i);
		}
	}
	for (int i = 0; i < TASK_SECONDARY_MAX; i++)
	{
		CTask *pTask = taskManager->GetTaskSecondary(i);
		if (pTask != nullptr)
		{
			pTask->MakeAbortable(pPedSelf, ABORT_PRIORITY_IMMEDIATE, NULL);
			if (i != TASK_SECONDARY_FACIAL_COMPLEX)
				taskManager->RemoveTaskSecondary(i);
		}
	}
}
