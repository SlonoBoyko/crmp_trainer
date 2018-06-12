/*
			Almost all functions from m0d_s0beit sa
			But some of them I wrote =)
*/

#pragma once

extern CPools						*pPools;
extern CPed							*pPedSelf;

extern struct pool					*pool_vehicle;
extern struct pool					*pool_actor;
extern struct pool					*pool_object;

void								InitSmallGamePools();

BOOL								isBadPtr_GTA_pPed(CPedSAInterface *p_CPedSAInterface);
BOOL								isBadPtr_GTA_pPed(CPed *p_CPed);
BOOL								isBadPtr_GTA_pPed(actor_info *p_ActorInfo);
BOOL								isBadPtr_GTA_pVehicle(CVehicleSAInterface *p_CVehicleSAInterface);
BOOL								isBadPtr_GTA_pVehicle(CVehicleSA *p_CVehicleSA);
BOOL								isBadPtr_GTA_pVehicle(CVehicle *p_CVehicle);
BOOL								isBadPtr_GTA_pVehicle(vehicle_info *p_VehicleInfo);
BOOL								isBadPtr_GTA_pObject(CObjectSAInterface * p_CObjectSAInterface);
BOOL								isBadPtr_GTA_pObject(object_info * p_ObjectInfo);

struct vehicle_info					*vehicle_info_get(int id, int flags = 0);
struct actor_info					*actor_info_get(int id, int flags = 0);

bool								gta_menu_active(void);
bool								gta_map_marker_active(void);
void								gta_interior_id_set(int id);
int									gta_interior_id_get(void);
void								gta_set_gamekey_state(ePadType key, int16_t state);
bool								gta_world_marker_get(float fPos[3]);
bool								gta_map_marker_get(float fPos[3]);
void								gta_rotate_along_surface(vehicle_info *vehicle, float fPos[3]);
float								*gta_collision_normal_get(vehicle_info *vehicle, float fPos[3]);
void								gta_vehicle_zero_speed(vehicle_info *vehicle);
void								gta_trailer_attach(vehicle_info *vehicle, vehicle_info *trailer, bool and_tp = false, bool at_surface = false);
void								gta_teleport(float fPos[3], int interior_id = 0);
struct vehicle_entry				*gta_vehicle_get_by_id(int id);

RwColor								getVehicleColorRGB(unsigned int index);
void								GTAfunt_SetVehicleColor(vehicle_info *vinfo, int color1, int color2);
enum eClientVehicleType				GTAfunc_getVehicleType(int iModelID);
void								GTAfunc_addVehicleUpgrade(vehicle_info *vinfo, int iModelID);

void								GTAfunc_loadAllWeaponModels(void);
void								GTAfunc_loadSpecificModel(int iModelID);
bool								GTAfunc_IsUpgradeCompatible(int iModelID, vehicle_info *vinfo);
bool								GTAfunc_IsUpgradeAvailable(int m_dwModelID, eVehicleUpgradePosn posn);
void								GTAfunc_PutActorInCar(vehicle_info *vehicle);
void								GTAfunc_PutActorInCarAsPassenger(vehicle_info *vehicle, int iSeat);
void								GTAfunc_RemoveActorFromCarAndPutAt(float fPos[3]);
void								GTAfunc_EnterCarAsDriver(vehicle_info *vehicle);
void								GTAfunc_RepairVehicle(vehicle_info *vehicle);
void								GTAfunc_CameraOnActor(actor_info *actor);
void								GTAfunc_CameraOnVehicle(vehicle_info *vehicle);
void								GTAfunc_PerformAnimation(const char *szBlockName, const char *szAnimName, int iTime, bool bLoop, bool bUpdatePosition, bool bInterruptable, 
										bool bFreezeLastFrame, bool bRunInSequence, bool bOffsetPed, bool bHoldLastFrame);

void								GTAfunc_TogglePlayerControllable(bool bToggle);


bool								GTAfunc_ProcessLineOfSight(CVector *vecStart, CVector *vecEnd, CColPoint **colCollision,
											CEntitySAInterface **CollisionEntity, bool bCheckBuildings, bool bCheckVehicles,
											bool bCheckPeds, bool bCheckObjects, bool bCheckDummies, bool bSeeThroughStuff,
											bool bIgnoreSomeObjectsForCamera, bool bShootThroughStuff);
bool								GTAfunc_IsLineOfSightClear(CVector *vecStart, CVector *vecEnd, bool bCheckBuildings, bool bCheckVehicles,
											bool bCheckPeds, bool bCheckObjects, bool bCheckDummies, bool bSeeThroughStuff,
											bool bIgnoreSomeObjectsForCamera);
bool								GTAfunc_testCheat(char *szCheat);
void								GTAfunc_DisembarkInstantly();
















