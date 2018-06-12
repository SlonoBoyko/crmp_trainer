/*****************************************************************************
*
*  PROJECT:		Multi Theft Auto v1.0
*  LICENSE:		See LICENSE in the top level directory
*  FILE:		sdk/CVector.h
*  PURPOSE:		3D vector math implementation
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CVector_H
#define __CVector_H

#ifdef WIN32
#include <windows.h>
#endif

#include <game\RenderWare.h>
#define FLOAT_EPSILON 0.0001f

/**
 * CVector Structure used to store a 3D vertex.
 */
class CVector
{
private:
	bool IsNearZeroFloat(const float param)
	{
		if (!isfinite(param)) return true;
		return (fabs(param) < FLOAT_EPSILON);
	}

public:
	float fX, fY, fZ;

	CVector()
	{
		this->fX = 0;
		this->fY = 0;
		this->fZ = 0;
	};

	CVector(float fX, float fY, float fZ)
	{
		this->fX = fX;
		this->fY = fY;
		this->fZ = fZ;
	}

	CVector(float fVector[3])
	{
		this->fX = fVector[0];
		this->fY = fVector[1];
		this->fZ = fVector[2];
	};

	CVector(const float fVector[3])
	{
		this->fX = fVector[0];
		this->fY = fVector[1];
		this->fZ = fVector[2];
	};

	float Normalize(void)
	{
		double len = sqrt(fX * fX + fY * fY + fZ * fZ);
		if (len > FLOAT_EPSILON)
		{
			double fX2 = fX / len;
			double fY2 = fY / len;
			double fZ2 = fZ / len;
			fX = (float)fX2;
			fY = (float)fY2;
			fZ = (float)fZ2;
		} else len = 0.f;
		return static_cast <float> (len);
	}

	float Length(void) const
	{
		return sqrt((fX*fX) + (fY*fY) + (fZ*fZ));
	}

	float DotProduct(const CVector * param) const
	{
		return fX * param->fX + fY * param->fY + fZ * param->fZ;
	}

	void CrossProduct(const CVector * param)
	{
		float _fX = fX, _fY = fY, _fZ = fZ;
		fX = _fY * param->fZ - param->fY * _fZ;
		fY = _fZ * param->fX - param->fZ * _fX;
		fZ = _fX * param->fY - param->fX * _fY;
	}

	bool IsNearZero(void)
	{
		//if(!isfinite(fX) || !isfinite(fY) || !isfinite(fZ))
		//	return 1;
		return (IsNearZeroFloat(fX) && IsNearZeroFloat(fY) && IsNearZeroFloat(fZ));
	}

	void Zero(void)
	{
		fX = 0.0f;
		fY = 0.0f;
		fZ = 0.0f;
	}

	void ZeroNearZero(void)
	{
		if (IsNearZeroFloat(fX))
			fX = 0.0f;
		if (IsNearZeroFloat(fY))
			fY = 0.0f;
		if (IsNearZeroFloat(fZ))
			fZ = 0.0f;
	}

	float GetAngleRadians(void)
	{
		return -atan2(fY, -fX);
	}

	float GetAngleDegrees(void)
	{
		static double radtodeg = 57.3248407643312101910; // 180/pi
		float ret = (atan2(fY, -fX) * radtodeg) + 270.0;
		if (ret >= 360.0f) ret -= 360.0f;
		return ret;
	}

	/*CVector GetRotation(void) const
	{
		CVector vecRotation;
		vecRotation.fZ = atan2(fY, fX);
		CVector vecTemp(sqrt(fX * fX + fY * fY), fZ, 0.f);
		vecTemp.Normalize();
		vecRotation.fY = atan2(vecTemp.fX, vecTemp.fY) - 3.14159265358979323844 / 2;
		return vecRotation;
	}*/

	CVector GetRotation(void) const
	{
		static double half_pi = 1.57079632679489661923;
		float lenght = sqrt(fX * fX + fY * fY);
		CVector vTemp(lenght, fZ, 0.f);
		vTemp.fY = atan2(vTemp.fX, vTemp.fY) - half_pi;
		vTemp.Normalize();
		
		return CVector(0.f, vTemp.fY, atan2(fY, fX));
	}

	CVector GetPerpendicularAxis(void) const
	{
		if (fabs(fX) > fabs(fY)) return CVector(fZ, 0.f, -fX);
		return CVector(0.f, -fZ, fY);
	}

	operator float * (void)
	{
		return reinterpret_cast <float *> (this);
	}

	operator const float * (void) const
	{
		return reinterpret_cast <const float *> (this);
	}

	CVector operator + (const CVector& vecRight) const
	{
		return CVector(fX + vecRight.fX, fY + vecRight.fY, fZ + vecRight.fZ);
	}

	CVector operator - (const CVector& vecRight) const
	{
		return CVector(fX - vecRight.fX, fY - vecRight.fY, fZ - vecRight.fZ);
	}

	CVector operator * (const CVector& vecRight) const
	{
		return CVector(fX * vecRight.fX, fY * vecRight.fY, fZ * vecRight.fZ);
	}

	CVector operator * (float fRight) const
	{
		return CVector(fX * fRight, fY * fRight, fZ * fRight);
	}

	CVector operator / (const CVector& vecRight) const
	{
		return CVector(fX / vecRight.fX, fY / vecRight.fY, fZ / vecRight.fZ);
	}

	CVector operator / (float fRight) const
	{
		return CVector(fX / fRight, fY / fRight, fZ / fRight);
	}

	CVector operator - (void) const
	{
		return CVector(-fX, -fY, -fZ);
	}

	//CVector operator = (RwV3d& RwVecor)
	//{
	//	return CVector(fX = RwVecor.x, fY = RwVecor.y, fZ = RwVecor.z);
	//}

	CVector operator = (float fVector[3])
	{
		return CVector(fX = fVector[0], fY = fVector[1], fZ = fVector[2]);
	}

	CVector operator = (const float fVector[3])
	{
		return CVector(fX = fVector[0], fY = fVector[1], fZ = fVector[2]);
	}

	void operator += (float fRight)
	{
		fX += fRight;
		fY += fRight;
		fZ += fRight;
	}

	void operator += (const CVector& vecRight)
	{
		fX += vecRight.fX;
		fY += vecRight.fY;
		fZ += vecRight.fZ;
	}

	void operator -= (float fRight)
	{
		fX -= fRight;
		fY -= fRight;
		fZ -= fRight;
	}

	void operator -= (const CVector& vecRight)
	{
		fX -= vecRight.fX;
		fY -= vecRight.fY;
		fZ -= vecRight.fZ;
	}

	void operator *= (float fRight)
	{
		fX *= fRight;
		fY *= fRight;
		fZ *= fRight;
	}

	void operator *= (const CVector& vecRight)
	{
		fX *= vecRight.fX;
		fY *= vecRight.fY;
		fZ *= vecRight.fZ;
	}

	void operator /= (float fRight)
	{
		fX /= fRight;
		fY /= fRight;
		fZ /= fRight;
	}

	void operator /= (const CVector& vecRight)
	{
		fX /= vecRight.fX;
		fY /= vecRight.fY;
		fZ /= vecRight.fZ;
	}

	bool operator == (const CVector& param) const
	{
		return ((fabs(fX - param.fX) < FLOAT_EPSILON) &&
				(fabs(fY - param.fY) < FLOAT_EPSILON) &&
				(fabs(fZ - param.fZ) < FLOAT_EPSILON));
	}

	bool operator != (const CVector& param) const
	{
		return ((fabs(fX - param.fX) >= FLOAT_EPSILON) ||
				(fabs(fY - param.fY) >= FLOAT_EPSILON) ||
				(fabs(fZ - param.fZ) >= FLOAT_EPSILON));
	}
};

// global vector normals
CVector const g_vecFrontNormal(1.0f, 0.0f, 0.0f);
CVector const g_vecRightNormal(0.0f, 1.0f, 0.0f);
CVector const g_vecUpNormal(0.0f, 0.0f, 1.0f);

#endif
