
// -------------------------------------------------------------------
// File			:	Quat.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for Quat-Class
//
// Author		:	Thorsten Polte
// -------------------------------------------------------------------
// (c) 2011-2020 by Innovation3D-Studio´s
// --------------------------------------------------------------------
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//---------------------------------------------------------------------
// https://github.com/toasti1973/TurboMath
// 
// Contact : thorsten.polte@innovation3d.de
//---------------------------------------------------------------------


#ifdef _MSC_VER
#pragma once
#endif

/****************************************************************************
 *
 * Quat
 *
 ****************************************************************************/

namespace TurboMath
{
	//------------------------------------------------------------------------------
	__forceinline	Quat::Quat()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline	Quat::Quat(float x, float y, float z, float w)
	{
		this->vec = XMVectorSet(x, y, z, w);
	}

	//------------------------------------------------------------------------------
	__forceinline	Quat::Quat(Vector4 const &rhs) :
	vec(rhs)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline	Quat::Quat(const Quat& rhs) :
	vec(rhs.vec)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline 	Quat::Quat(XMVECTOR rhs) :
	vec(rhs)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline void	Quat::operator=(const Quat& rhs)
	{
		this->vec = rhs.vec;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Quat::operator=(XMVECTOR rhs)
	{
		this->vec = rhs;
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Quat::operator==(const Quat& rhs) const
	{
		return (0 != XMQuaternionEqual(this->vec, rhs.vec));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Quat::operator!=(const Quat& rhs) const
	{
		return (0 != XMQuaternionNotEqual(this->vec, rhs.vec));
	}

	//------------------------------------------------------------------------------
	__forceinline void	Quat::Set(const float x,const float y,const float z,const float w)
	{
		this->vec = XMVectorSet(x, y, z, w);
	}

	//------------------------------------------------------------------------------
	__forceinline void Quat::Set_X(const float x)
	{
		this->vec = XMVectorSetXPtr(this->vec, &x);
	}

	//------------------------------------------------------------------------------
	__forceinline void Quat::Set_Y(const float y)
	{
		this->vec = XMVectorSetYPtr(this->vec, &y);
	}

	//------------------------------------------------------------------------------
	__forceinline void Quat::Set_Z(const float z)
	{
		this->vec = XMVectorSetZPtr(this->vec, &z);
	}

	//------------------------------------------------------------------------------
	__forceinline void Quat::Set_W(const float w)
	{
		this->vec = XMVectorSetWPtr(this->vec, &w);
	}

	//------------------------------------------------------------------------------
	__forceinline void	Quat::Set(Vector4 const &f4)
	{
		this->vec = f4;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Quat::Set(XMVECTOR const &f4)
	{
		this->vec = f4;
	}

	//------------------------------------------------------------------------------
	__forceinline float&	Quat::X()
	{
#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.x;
#elif __WIN32__
		return this->vec.m128_f32[0];
#endif
	}

	//------------------------------------------------------------------------------
	__forceinline float	Quat::X() const
	{
		return Vector4::Unpack_X(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline float&	Quat::Y()
	{
#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.y;
#elif __WIN32__
		return this->vec.m128_f32[1];
#endif
	}

	//------------------------------------------------------------------------------
	__forceinline float	Quat::Y() const
	{
		return Vector4::Unpack_Y(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline float&	Quat::Z()
	{
#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.z;
#elif __WIN32__
		return this->vec.m128_f32[2];
#endif
	}

	//------------------------------------------------------------------------------
	__forceinline float	Quat::Z() const
	{
		return Vector4::Unpack_Z(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline float&	Quat::W()
	{
#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.w;
#elif __WIN32__
		return this->vec.m128_f32[3];
#endif
	}

	//------------------------------------------------------------------------------
	__forceinline float	Quat::W() const
	{
		return Vector4::Unpack_W(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline const XMVECTOR Quat::Get() const
	{
		return (this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline void	Quat::operator*=(const Quat& rhs)
	{
		this->vec = XMQuaternionMultiply(this->vec, rhs.vec);
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Quat::IsIdentity() const
	{
		return (0 != XMQuaternionIsIdentity(this->vec));
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::NullQuat()
	{
		return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	__forceinline float	Quat::Length() const
	{
		return Vector4::Unpack_X(XMQuaternionLength(this->vec));
	}

	//------------------------------------------------------------------------------
	__forceinline float	Quat::Lengthsq() const
	{
		return Vector4::Unpack_X(XMQuaternionLengthSq(this->vec));
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::Barycentric(const Quat& q0, const Quat& q1, const Quat& q2, float f, float g)
	{
		return XMQuaternionBaryCentric(q0.vec, q1.vec, q2.vec, f, g);
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::Conjugate(const Quat& q)
	{
		return XMQuaternionConjugate(q.vec);
	}

	//------------------------------------------------------------------------------
	__forceinline float	Quat::Dot(const Quat& q0, const Quat& q1)
	{
		return Vector4::Unpack_X(XMQuaternionDot(q0.vec, q1.vec));
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::Exp(const Quat& q)
	{
		return XMQuaternionExp(q.vec);
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::Identity()
	{
		return XMQuaternionIdentity();
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::Inverse(const Quat& q)
	{
		return XMQuaternionInverse(q.vec);
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::ln(const Quat& q)
	{
		return XMQuaternionLn(q.vec);
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::Multiply(const Quat& q0, const Quat& q1)
	{
		return XMQuaternionMultiply(q0.vec, q1.vec);
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::Normalize(const Quat& q)
	{
		return XMQuaternionNormalize(q.vec);
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::RotationAxis(const Vector4& axis, float angle)
	{
		return XMQuaternionRotationAxis(axis, angle);
	}
	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::RotationRollPitchYaw(const float roll,const float pitch, const float yaw)
	{
		return XMQuaternionRotationRollPitchYaw(roll,pitch,yaw);
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::RotationYawPitchRoll(float yaw, float pitch, float roll)
	{
		return XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::Slerp(const Quat& q1, const Quat& q2, float t)
	{
		return XMQuaternionSlerp(q1.vec, q2.vec, t);
	}

	//------------------------------------------------------------------------------
	__forceinline void	Quat::SquadSetup(const Quat& q0, const Quat& q1, const Quat& q2, const Quat& q3, Quat& aOut, Quat& bOut, Quat& cOut)
	{
		XMQuaternionSquadSetup(&aOut.vec, &bOut.vec, &cOut.vec, q0.vec, q1.vec, q2.vec, q3.vec);
	}

	//------------------------------------------------------------------------------
	__forceinline Quat	Quat::Squad(const Quat& q1, const Quat& a, const Quat& b, const Quat& c, float t)
	{
		return XMQuaternionSquad(q1.vec, a.vec, b.vec, c.vec, t);
	}

	//------------------------------------------------------------------------------
	__forceinline void	Quat::To_AxisAngle(const Quat& q, Vector4& outAxis, float& outAngle)
	{
		XMQuaternionToAxisAngle(outAxis.GetRawPtr(), &outAngle, q.vec);
		outAxis.SetW(0.0f);
	}

	//------------------------------------------------------------------------------
	__forceinline Quat Quat::RotationMatrix(const Matrix& m)
	{
		return XMQuaternionRotationMatrix(m.mx);
	}

	//------------------------------------------------------------------------------
	__forceinline bool Quat::IsUnit() const 
	{
		static const XMVECTOR UnitQuaternionEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		const XMVECTOR Difference = XMVector4Length( vec ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), UnitQuaternionEpsilon );
	}

	//------------------------------------------------------------------------------
	__forceinline bool Quat::IsUnit(const XMVECTOR q) 
	{
		static const XMVECTOR UnitQuaternionEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		const XMVECTOR Difference = XMVector4Length( q ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), UnitQuaternionEpsilon );
	}

	//------------------------------------------------------------------------------
	__forceinline Matrix Quat::GetMatrix(const Quat& q)
	{
		Matrix mat;

		float wx,wy,wz,xx,yy,yz,xy,xz,zz,x2,y2,z2;

		// set matrix to identity
		mat = Matrix::Identity();

		x2 = q.X() + q.X(); 
		y2 = q.Y() + q.Y(); 
		z2 = q.Z() + q.Z();

		xx = q.X() * x2;   
		xy = q.X() * y2;  
		xz = q.X() * z2;

		yy = q.Y() * y2;   
		yz = q.Y() * z2;   
		zz = q.Z() * z2;

		wx = q.W() * x2;   
		wy = q.W() * y2;   
		wz = q.W() * z2;

		mat.SetM11(1.0f - (yy + zz));
		mat.SetM12(xy - wz);
		mat.SetM13(xz + wy);

		mat.SetM21(xy + wz);
		mat.SetM22(1.0f - (xx + zz));
		mat.SetM23(yz - wx);

		mat.SetM31(xz - wy);
		mat.SetM32(yz + wx);
		mat.SetM33(1.0f - (xx + yy));

		return mat;
	}

	//------------------------------------------------------------------------------
	__forceinline Quat  Quat::MakeFromEuler(const float fPitch, const float fYaw, const float fRoll)
	{
		Quat q;
		float cX, cY, cZ, sX, sY,sZ, cYcZ, sYsZ, cYsZ, sYcZ;

		XMScalarSinCos(&sX, &cX, (fPitch/2.0f) );
		XMScalarSinCos(&sY, &cY, (fYaw/2.0f) );
		XMScalarSinCos(&cZ, &sZ, (fRoll/2.0f) );

		cYcZ = cY * cZ;
		sYsZ = sY * sZ;
		cYsZ = cY * sZ;
		sYcZ = sY * cZ;

		q.Set_W( cX * cYcZ + sX * sYsZ );
		q.Set_X( sX * cYcZ - cX * sYsZ );
		q.Set_Y( cX * sYcZ + sX * cYsZ );
		q.Set_Z( cX * cYsZ - sX * sYcZ );

		return q;
	}

	//------------------------------------------------------------------------------
	__forceinline void Quat::GetEulers(const Quat& q, float *fPitch, float *fYaw, float *fRoll)
	{
		assert(fPitch);
		assert(fYaw);
		assert(fRoll);

		double	r11,r21,r31,r32,r33,r12,r13,q00,q11,q22,q33,temp;

		q00 = q.W() * q.W();
		q11 = q.X() * q.X();
		q22 = q.Y() * q.Y();
		q33 = q.W() * q.W();

		r11 = q00 + q11 - q22 - q33;
		r21 = 2 * (q.X() * q.Y() + q.W() * q.Z() );
		r31 = 2 * (q.X() * q.Z() - q.W() * q.Y() );
		r32 = 2 * (q.Y() * q.Z() + q.W() * q.X() );
		r33 = q00 - q11 - q22 + q33;

		temp = fabs(r31);
		if(temp > 0.999999)
		{
			r12 = 2 * (q.X() * q.Y() - q.W() * q.Z() );
			r13 = 2 * (q.X() * q.Z() + q.W() * q.Y() );

			*fPitch = 0.0f;
			*fYaw	= (float) - ((TURBOMATH_TWO_PI) * r31 / temp);
			*fRoll	= (float) ATan2( static_cast<float>(-r12) , static_cast<float>(-r31 * r13));
		}

		else
		{
			*fPitch = (float) ATan2( static_cast<float>(r32), static_cast<float>(r33));
			*fYaw	= (float) ASin( static_cast<float>(+r31) );
			*fRoll	= (float) ATan2( static_cast<float>(r21),static_cast<float>(r11));
		}
	}

}// Namespace

