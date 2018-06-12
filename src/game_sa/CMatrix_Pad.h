/*****************************************************************************
*
*  PROJECT:		Multi Theft Auto v1.0
*  LICENSE:		See LICENSE in the top level directory
*  FILE:		sdk/CMatrix_Pad.h
*  PURPOSE:		4x3 GTA padded matrix
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CMATRIX_PAD_H
#define __CMATRIX_PAD_H

#include "CVector.h"
#include "CMatrix.h"

/**
 * CVector Structure used internally by GTA.
 */
class CMatrix_Padded
{
public:
	CVector vRight;					// 0		RIGHT
private:
	DWORD	 dwPadRoll;				// 12
public:
	CVector vFront;					// 16		FOREWARDS
private:
	DWORD	 dwPadDirection;		// 28
public:
	CVector vUp;					// 32		UP
private:
	DWORD	 dwPadWas;				// 44
public:
	CVector vPos;					// 48		TRANSLATE
private:
	DWORD dwPadPos;					// 60
public:
	CMatrix_Padded()
	{
		memset(this, 0, sizeof(CMatrix_Padded));
	}

	CMatrix_Padded(const CMatrix& Matrix)
	{
		vPos = Matrix.vPos;
		vUp = Matrix.vUp;
		vFront = Matrix.vFront;
		vRight = Matrix.vRight;
		dwPadPos = dwPadRoll = dwPadWas = dwPadDirection = NULL;
	}

	CMatrix& operator = (const CMatrix& Matrix)
	{
		vPos = Matrix.vPos;
		vUp = Matrix.vUp;
		vFront = Matrix.vFront;
		vRight = Matrix.vRight;
		dwPadPos = dwPadRoll = dwPadWas = dwPadDirection = NULL;

		return CMatrix(Matrix);
	}

	operator CMatrix& ()
	{
		CMatrix Matrix;
		Matrix.vPos = vPos;
		Matrix.vUp = vUp;
		Matrix.vFront = vFront;
		Matrix.vRight = vRight;

		return Matrix;
	}
};

#endif

/* OLD */
/*
class CMatrix_Padded
{
public:
	CVector vRight;					// 0		RIGHT
private:
	DWORD	 dwPadRoll;				// 12
public:
	CVector vFront;					// 16		FOREWARDS
private:
	DWORD	 dwPadDirection;		// 28
public:
	CVector vUp;					// 32		UP
private:
	DWORD	 dwPadWas;				// 44
public:
	CVector vPos;					// 48		TRANSLATE
private:
	DWORD dwPadPos;					// 60

	CMatrix_Padded()
	{
		memset(this, 0, sizeof(CMatrix_Padded));
	}

	CMatrix_Padded(const CMatrix& Matrix)
	{
		vPos = Matrix.vPos;
		dwPadPos = 0;

		vFront = Matrix.vFront;
		dwPadDirection = 0;

		vUp = Matrix.vUp;
		dwPadWas = 0;

		vRight = Matrix.vRight;
		dwPadRoll = 0;
	}

	void ConvertToMatrix(CMatrix& Matrix) const
	{
		Matrix.vPos = vPos;
		Matrix.vFront = vFront;
		Matrix.vUp = vUp;
		Matrix.vRight = vRight;
	}

	void SetFromMatrix(const CMatrix& Matrix)
	{
		vPos = Matrix.vPos;
		dwPadPos = 0;

		vFront = Matrix.vFront;
		dwPadDirection = 0;

		vUp = Matrix.vUp;
		dwPadWas = 0;

		vRight = Matrix.vRight;
		dwPadRoll = 0;
	}
};
*/