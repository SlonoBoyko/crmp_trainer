/*****************************************************************************
*
*  PROJECT:		Multi Theft Auto v1.0
*  LICENSE:		See LICENSE in the top level directory
*  FILE:		game_sa/CMarkerSA.h
*  PURPOSE:		Header file for marker entity class
*  DEVELOPERS:	Ed Lyons <eai@opencoding.net>
*               Christian Myhre Lundheim <>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CGAMESA_MARKER
#define __CGAMESA_MARKER

#include <game/CMarker.h>
#include "Common.h"

/**
 * \todo Ignore this class?
 */
class CEntryExit;

class CMarkerSAInterface
{
public:
	/* GTA Variables */
	DWORD			nColour;					// +0
	// The following parameter is used when Blip Type is CAR, CHAR or OBJECT
	long			PoolIndex;					// +4
	// The following parameter is used when Blip Type is COORDS	
	CVector			position;//vec2DBlip;		// +8

	WORD			ReferenceIndex;				// +20

	FLOAT			fBlipMarkerScale;				// +24
	WORD			nBlipScale;					// +28
	CEntryExit		*pEntryExit;				// +32

	BYTE			nBlipSprite;					// +36

	BYTE			bBright : 1;	// +37
	BYTE			bTrackingBlip : 1;
	BYTE			bShortRange : 1;
	BYTE			bFriendly : 1;
	BYTE			bBlipRemain : 1;
	BYTE			bBlipFade : 1;
	BYTE			nCoordBlipAppearance : 2;

	BYTE			nBlipDisplayFlag : 2;	// +38
	BYTE			BlipType : 4;

			
};

class CMarkerSA : public CMarker
{
public:
	/* Our Functions */
	CMarkerSA(CMarkerSAInterface * markerInterface) { internalInterface = markerInterface; };

	void                Init(void);

	VOID				SetSprite(eMarkerSprite Sprite);
	VOID				SetDisplay(eMarkerDisplay wDisplay);
	VOID				SetScale(WORD wScale);
	VOID				SetColor(eMarkerColor color);
	VOID				SetColor(RGBA color);
	VOID				Remove();
	BOOL				IsActive();
	VOID				SetPosition(CVector * vecPosition);
	VOID				SetEntity(CVehicle * vehicle);
	VOID				SetEntity(CPed * ped);
	VOID				SetEntity(CObject * object);
	CEntity				*GetEntity();
	CVector				*GetPosition();
	eMarkerType			GetBlipType();
	eMarkerSprite		GetSprite();
	eMarkerDisplay		GetDisplay();
	BOOL				IsBright();
	CMarkerSAInterface	*GetInterface() { return internalInterface; };
private:
	CMarkerSAInterface * internalInterface;
};

#endif