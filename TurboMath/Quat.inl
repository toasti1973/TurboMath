
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
	XM_INLINE Quat::Quat() noexcept
	{
		// empty
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat::Quat(const float x, const float y, const float z, const float w) noexcept
	{
		this->vec = XMVectorSet(x, y, z, w);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat::Quat(Vector4 const &rhs) noexcept :
	vec(rhs)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat::Quat(const Quat& rhs) noexcept :
	vec(rhs.vec)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	XM_INLINE 	Quat::Quat(XMVECTOR rhs) noexcept :
	vec(rhs)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Quat::operator=(const Quat& rhs) noexcept
	{
		this->vec = rhs.vec;
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Quat::operator=(XMVECTOR rhs) noexcept
	{
		this->vec = rhs;
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Quat::operator==(const Quat& rhs) const noexcept
	{
		return (0 != XMQuaternionEqual(this->vec, rhs.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Quat::operator!=(const Quat& rhs) const noexcept
	{
		return (0 != XMQuaternionNotEqual(this->vec, rhs.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Quat::Set(const float x,const float y,const float z,const float w) noexcept
	{
		this->vec = XMVectorSet(x, y, z, w);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV Quat::Set_X(const float x) noexcept
	{
		this->vec = XMVectorSetXPtr(this->vec, &x);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV Quat::Set_Y(const float y) noexcept
	{
		this->vec = XMVectorSetYPtr(this->vec, &y);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV Quat::Set_Z(const float z) noexcept
	{
		this->vec = XMVectorSetZPtr(this->vec, &z);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV Quat::Set_W(const float w) noexcept
	{
		this->vec = XMVectorSetWPtr(this->vec, &w);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Quat::Set(Vector4 const &f4) noexcept
	{
		this->vec = f4;
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Quat::Set(XMVECTOR const &f4) noexcept
	{
		this->vec = f4;
	}

	//------------------------------------------------------------------------------
	XM_INLINE float& XM_CALLCONV Quat::X() noexcept
	{
		return this->vec.m128_f32[0];
	}

	//------------------------------------------------------------------------------
	XM_INLINE float	Quat::X() const noexcept
	{
		return Vector4::Unpack_X(this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float& XM_CALLCONV Quat::Y() noexcept
	{
		return this->vec.m128_f32[1];
	}

	//------------------------------------------------------------------------------
	XM_INLINE float XM_CALLCONV Quat::Y() const noexcept
	{
		return Vector4::Unpack_Y(this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float& XM_CALLCONV Quat::Z() noexcept
	{
		return this->vec.m128_f32[2];
	}

	//------------------------------------------------------------------------------
	XM_INLINE float	XM_CALLCONV Quat::Z() const noexcept
	{
		return Vector4::Unpack_Z(this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float& XM_CALLCONV Quat::W() noexcept
	{
		return this->vec.m128_f32[3];
	}

	//------------------------------------------------------------------------------
	XM_INLINE float	XM_CALLCONV Quat::W() const noexcept
	{
		return Vector4::Unpack_W(this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE const XMVECTOR XM_CALLCONV Quat::Get() const noexcept
	{
		return (this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV Quat::operator*=(const Quat& rhs) noexcept
	{
		this->vec = XMQuaternionMultiply(this->vec, rhs.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool XM_CALLCONV Quat::IsIdentity() const noexcept
	{
		return (0 != XMQuaternionIsIdentity(this->vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::NullQuat() noexcept
	{
		return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float	XM_CALLCONV Quat::Length() const noexcept
	{
		return Vector4::Unpack_X(XMQuaternionLength(this->vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE float	XM_CALLCONV Quat::Lengthsq() const noexcept
	{
		return Vector4::Unpack_X(XMQuaternionLengthSq(this->vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::Barycentric(const Quat& q0, const Quat& q1, const Quat& q2, float f, float g) noexcept
	{
		return XMQuaternionBaryCentric(q0.vec, q1.vec, q2.vec, f, g);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::Conjugate(const Quat& q) noexcept
	{
		return XMQuaternionConjugate(q.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float	XM_CALLCONV Quat::Dot(const Quat& q0, const Quat& q1) noexcept
	{
		return Vector4::Unpack_X(XMQuaternionDot(q0.vec, q1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::Exp(const Quat& q) noexcept
	{
		return XMQuaternionExp(q.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::Identity() noexcept
	{
		return XMQuaternionIdentity();
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::Inverse(const Quat& q) noexcept
	{
		return XMQuaternionInverse(q.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::ln(const Quat& q) noexcept
	{
		return XMQuaternionLn(q.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::Multiply(const Quat& q0, const Quat& q1) noexcept
	{
		return XMQuaternionMultiply(q0.vec, q1.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::Normalize(const Quat& q) noexcept
	{
		return XMQuaternionNormalize(q.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::RotationAxis(const Vector4& axis, float angle) noexcept
	{
		return XMQuaternionRotationAxis(axis, angle);
	}
	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::RotationRollPitchYaw(const float roll,const float pitch, const float yaw) noexcept
	{
		return XMQuaternionRotationRollPitchYaw(roll,pitch,yaw);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::RotationYawPitchRoll(float yaw, float pitch, float roll) noexcept
	{
		return XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::Slerp(const Quat& q1, const Quat& q2, float t) noexcept
	{
		return XMQuaternionSlerp(q1.vec, q2.vec, t);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV Quat::SquadSetup(const Quat& q0, const Quat& q1, const Quat& q2, const Quat& q3, Quat& aOut, Quat& bOut, Quat& cOut) noexcept
	{
		XMQuaternionSquadSetup(&aOut.vec, &bOut.vec, &cOut.vec, q0.vec, q1.vec, q2.vec, q3.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::Squad(const Quat& q1, const Quat& a, const Quat& b, const Quat& c, float t) noexcept
	{
		return XMQuaternionSquad(q1.vec, a.vec, b.vec, c.vec, t);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV Quat::To_AxisAngle(const Quat& q, Vector4& outAxis, float& outAngle) noexcept
	{
		XMQuaternionToAxisAngle(outAxis.GetRawPtr(), &outAngle, q.vec);
		outAxis.SetW(0.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Quat XM_CALLCONV Quat::RotationMatrix(const Matrix& m) noexcept
	{
		return XMQuaternionRotationMatrix(m.mx);
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool XM_CALLCONV Quat::IsUnit() const  noexcept
	{
		static constexpr XMVECTOR UnitQuaternionEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		const XMVECTOR Difference = XMVector4Length( vec ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), UnitQuaternionEpsilon );
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool XM_CALLCONV Quat::IsUnit(const XMVECTOR q)  noexcept
	{
		static constexpr XMVECTOR UnitQuaternionEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		const XMVECTOR Difference = XMVector4Length( q ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), UnitQuaternionEpsilon );
	}

	//------------------------------------------------------------------------------
	XM_INLINE Matrix XM_CALLCONV Quat::GetMatrix(const Quat& q) noexcept
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
	XM_INLINE Quat  XM_CALLCONV Quat::MakeFromEuler(const float fPitch, const float fYaw, const float fRoll) noexcept
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
	XM_INLINE void XM_CALLCONV Quat::GetEulers(const Quat& q, float *fPitch, float *fYaw, float *fRoll)
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

