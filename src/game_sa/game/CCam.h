/*****************************************************************************
*
*  PROJECT:		Multi Theft Auto v1.0
*  LICENSE:		See LICENSE in the top level directory
*  FILE:		sdk/game/CCam.h
*  PURPOSE:		Camera entity interface
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CGAME_CAM
#define __CGAME_CAM

class CCam
{
public:
	virtual CVector*        GetFront            () const = 0;
	virtual CVector*        GetUp               () const = 0;
	virtual CVector*        GetSource           () const = 0;
	virtual CVector*        GetFixedModeSource  () const = 0;
	virtual CVector*        GetFixedModeVector  () const = 0;
    virtual CVector*        GetTargetHistoryPos () const = 0;
    virtual unsigned int    GetMode             () const = 0;
    virtual float           GetFOV              () const = 0;
    virtual void            SetFOV              ( float fFOV ) = 0;
	virtual void            SetFOVSpeed			(float fFOVSpeed) = 0;
	virtual float           GetAlpha			() const = 0;
	virtual void            SetAlpha			(float Alpha) = 0;
	virtual void            SetAlphaSpeed		(float fAlphaSpeed) = 0;
	virtual float           GetBeta				() const = 0;
	virtual void            SetBeta				(float Beta) = 0;
	virtual void            SetBetaSpeed		(float fBetaSpeed) = 0;
    virtual CEntity*        GetTargetEntity     () const = 0;
};

#endif
