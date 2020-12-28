

// -------------------------------------------------------------------
// File			:	Vector3.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for 3D-Vector-Class
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
 * Vector3
 *
 ****************************************************************************/

namespace TurboMath
{
	//------------------------------------------------------------------------------
	XM_INLINE   	Vector3::Vector3() :
	vec(0.0f,0.0f,0.0f)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	XM_INLINE   	Vector3::Vector3(float x, float y, float z) :
	vec(x,y,z)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	XM_INLINE   	Vector3::Vector3(XMVECTOR rhs) :
	vec((float*)&rhs)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	XM_INLINE   	Vector3::Vector3(const Vector3& rhs)
	{
		this->vec.x = rhs.vec.x;
		this->vec.y = rhs.vec.y;
		this->vec.z = rhs.vec.z;
	}

	//------------------------------------------------------------------------------
	XM_INLINE    void XM_CALLCONV	Vector3::operator=(const Vector3 &rhs)
	{
		this->vec = rhs.vec;
	}

	//------------------------------------------------------------------------------
	XM_INLINE   Vector3::Vector3(const Vector4& rhs)
	{
		 XMStoreFloat3( &this->vec, rhs );
	}

	//------------------------------------------------------------------------------
	XM_INLINE  bool  XM_CALLCONV	Vector3::operator==(const Vector3 &rhs) const noexcept
	{
		return (0 != XMVector3Equal(XMLoadFloat3(&this->vec), XMLoadFloat3(&rhs.vec)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE   bool XM_CALLCONV	Vector3::operator!=(const Vector3 &rhs) const noexcept
	{
		return (0 != XMVector3NotEqual(XMLoadFloat3(&this->vec), XMLoadFloat3(&rhs.vec)));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE  float& XM_CALLCONV	Vector3::X() noexcept
	{
#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.x;
#elif __WIN32__
		return this->vec.m128_f32[0];
#endif
		return this->vec.x;
	}

	//------------------------------------------------------------------------------
	 float XM_CALLCONV	Vector3::X() const noexcept
	{
		return Vector3::Unpack_X(XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f));
	}

	//------------------------------------------------------------------------------
	XM_INLINE  float& XM_CALLCONV	Vector3::Y() noexcept
	{
#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.y;
#elif __WIN32__
		return this->vec.m128_f32[1];
#endif
		return this->vec.y;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE float  XM_CALLCONV	Vector3::Y() const noexcept
	{
		return Vector4::Unpack_Y(XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f));
	}

	//------------------------------------------------------------------------------
	XM_INLINE  float& XM_CALLCONV	Vector3::Z() noexcept
	{
#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.z;
#elif __WIN32__
		return this->vec.m128_f32[2];
#endif
		return this->vec.z;
	}

	//------------------------------------------------------------------------------
	XM_INLINE  float XM_CALLCONV	Vector3::Z() const noexcept
	{
		return Vector4::Unpack_Z(XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f));
	}

	//------------------------------------------------------------------------------
	XM_INLINE  XMFLOAT3 XM_CALLCONV Vector3::GetRaw() const noexcept
	{
		return this->vec;
	}

	//------------------------------------------------------------------------------
	XM_INLINE XMFLOAT3* XM_CALLCONV  Vector3::GetRawPtr() noexcept
	{
		return &this->vec;
	}

	//------------------------------------------------------------------------------
	XM_INLINE  void XM_CALLCONV	Vector3::Set( const float x, const float y, const float z) noexcept
	{
		this->vec.x = x;
		this->vec.y = y;
		this->vec.z = z;
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV 	Vector3::SetX( const float x) noexcept
	{
		this->vec.x = x;
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV 	Vector3::SetY(const float y)  noexcept
	{
		this->vec.y = y;
	}

	//------------------------------------------------------------------------------
	XM_INLINE  void XM_CALLCONV	Vector3::SetZ(const float z) noexcept
	{
		this->vec.z = z;
	}

	//------------------------------------------------------------------------------
	XM_INLINE const float XM_CALLCONV 	Vector3::GetX() const noexcept
	{
		return Vector4::Unpack_X( XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f) );
	}

	//------------------------------------------------------------------------------
	XM_INLINE const float XM_CALLCONV 	Vector3::GetY() const noexcept
	{
		return Vector4::Unpack_Y( XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f) );
	}

	//------------------------------------------------------------------------------
	XM_INLINE const float  XM_CALLCONV 	Vector3::GetZ() const noexcept
	{
		return Vector4::Unpack_Z( XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f) );
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::operator-() const noexcept
	{
		return Vector3(-this->vec.x,-this->vec.y,-this->vec.z);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::operator*(float t) const noexcept
	{
		return Vector3(this->vec.x * t,this->vec.y * t, this->vec.z * t);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::operator+(const Vector3 &rhs) const noexcept
	{
		return Vector3(this->vec.x + rhs.vec.x, this->vec.y + rhs.vec.y, this->vec.z + rhs.vec.z);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::operator-(const Vector3 &rhs) const noexcept
	{
		return Vector3(this->vec.x - rhs.vec.x, this->vec.y - rhs.vec.y, this->vec.z - rhs.vec.z);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV 	Vector3::operator+=(const Vector3 &rhs) noexcept
	{
		this->vec.x = this->vec.x + rhs.vec.x;
		this->vec.y = this->vec.y + rhs.vec.y;
		this->vec.z = this->vec.z + rhs.vec.z;
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	 XM_CALLCONV Vector3::operator-=(const Vector3 &rhs) noexcept
	{
		this->vec.x = this->vec.x - rhs.vec.x;
		this->vec.y = this->vec.y - rhs.vec.y;
		this->vec.z = this->vec.z - rhs.vec.z;
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV 	Vector3::operator*=(float s) noexcept
	{
		this->vec.x = this->vec.x * s;
		this->vec.y = this->vec.y * s;
		this->vec.z = this->vec.z * s;
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV 	Vector3::operator*=(const Vector3& rhs) noexcept
	{
		this->vec.x = this->vec.x * rhs.vec.x;
		this->vec.y = this->vec.y * rhs.vec.y;
		this->vec.z = this->vec.z * rhs.vec.z;
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::operator*(const Vector3& rhs) noexcept
	{
		return Vector3( this->vec.x * rhs.vec.x , this->vec.y * rhs.vec.y, this->vec.z * rhs.vec.z);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float XM_CALLCONV 	Vector3::Length() const noexcept
	{
		return Vector3::Unpack_X(XMVector3Length(XMVectorSet(this->vec.x, this->vec.y, this->vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE  float  XM_CALLCONV Vector3::Lengthsq() const noexcept
	{
		return Vector4::Unpack_X(XMVector3LengthSq(XMVectorSet(this->vec.x, this->vec.y, this->vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Abs() const noexcept
	{
		return XMVectorAbs(XMVectorSet(this->vec.x, this->vec.y, this->vec.z, 0.0f));
	}

	//------------------------------------------------------------------------------
	XM_INLINE  Vector3 XM_CALLCONV	Vector3::NullVec() noexcept
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::UpVec() noexcept
	{
		return Vector3(0.0f, 1.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard down vector (0, -1, 0)
	XM_INLINE  Vector3 XM_CALLCONV	Vector3::DownVec() noexcept
	{
		return Vector3(0.0f, -1.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard left vector (-1, 0, 0)
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::LeftVec() noexcept
	{
		return Vector3(-1.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	/// return the standard right vector (1, 0, 0)
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::RightVec() noexcept
	{
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard back vector (0, 0, 1)
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::BackVec() noexcept
	{
		return Vector3(0.0f, 0.0f, 1.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard foreward vector (0, 0, 1)
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::ForewardVec() noexcept
	{
		return Vector3(0.0f, 0.0f, -1.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard ZERO vector (0, 0, 0)
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::ZERO() noexcept
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard UNIT_X vector (1, 0, 0)
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::UNIT_X() noexcept
	{
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard UNIT_Y vector (0, 1, 0)
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::UNIT_Y() noexcept
	{
		return Vector3(0.0f, 1.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard UNIT_Z vector (0, 0, 1)
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::UNIT_Z() noexcept
	{
		return Vector3(0.0f, 0.0f, 1.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float XM_CALLCONV 		Vector3::Unpack_X(XMVECTOR v) noexcept
	{
		float x;
		XMVectorGetXPtr(&x, v);
		return x;
	}

	//------------------------------------------------------------------------------
	XM_INLINE  float XM_CALLCONV		Vector3::Unpack_Y(XMVECTOR v) noexcept
	{
		float y;
		XMVectorGetYPtr(&y, v);
		return y;
	}

	//------------------------------------------------------------------------------
	XM_INLINE float XM_CALLCONV 		Vector3::Unpack_Z(XMVECTOR v) noexcept
	{
		float z;
		XMVectorGetZPtr(&z, v);
		return z;
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Reciprocal(const Vector3 &v) noexcept
	{
		return Vector3(XMVectorReciprocal(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Multiply(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return Vector3(XMVectorMultiply(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f) , XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f) ));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Cross(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return Vector3(XMVector3Cross(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE float XM_CALLCONV 	Vector3::Dot(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return Vector3::Unpack_X(XMVector3Dot(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Barycentric(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, float f, float g) noexcept
	{
		return Vector3(XMVectorBaryCentric(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f), XMVectorSet(v2.vec.x, v2.vec.y, v2.vec.z, 0.0f), f, g));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Catmullrom(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, float s) noexcept
	{
		return Vector3(XMVectorCatmullRom(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f),XMVectorSet(v2.vec.x, v2.vec.y, v2.vec.z, 0.0f),XMVectorSet(v3.vec.x, v3.vec.y, v3.vec.z, 0.0f), s));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Hermite(const Vector3 &v1, const Vector3 &t1, const Vector3 &v2, const Vector3 &t2, float s) noexcept
	{
		return Vector3(XMVectorHermite(XMVectorSet(v1.vec.x,v1.vec.y,v1.vec.z,0.0f), XMVectorSet(t1.vec.x,t1.vec.y,t1.vec.z,0.0f), XMVectorSet(v2.vec.x,v2.vec.y,v2.vec.z,0.0f), XMVectorSet(t2.vec.x,t2.vec.y,t2.vec.z,0.0f), s));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Lerp(const Vector3 &v0, const Vector3 &v1, float s) noexcept
	{
		return Vector3(XMVectorLerp(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f), s));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3  XM_CALLCONV 	Vector3::Maximize(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return Vector3(XMVectorMax(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Minimize(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return Vector3(XMVectorMin(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Normalize(const Vector3 &v) noexcept
	{
		if (Vector3::Equal3_All(v, Vector3(0,0,0))) return v;

		return Vector3(XMVector3Normalize(XMVectorSet(v.vec.x,v.vec.y,v.vec.z,0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Reflect(const Vector3 &normal, const Vector3 &incident) noexcept
	{
		return Vector3(XMVector3Reflect(XMVectorSet(normal.vec.x, normal.vec.y, normal.vec.z, 0.0f),XMVectorSet(incident.vec.x, incident.vec.y, incident.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE float XM_CALLCONV  Vector3::Angle(const Vector3& v0, const Vector3& v1) noexcept
	{
		return Vector3::Unpack_X(XMVector3AngleBetweenVectors(XMVectorSet(v0.vec.x,v0.vec.y,v0.vec.z,0.0f), XMVectorSet(v1.vec.x,v1.vec.y,v1.vec.z,0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV  Vector3::Clamp(const Vector3& vClamp, const Vector3& vMin, const Vector3& vMax) noexcept
	{
		return Vector3(XMVectorClamp(XMVectorSet(vClamp.vec.x,vClamp.vec.y,vClamp.vec.z,0.0f), XMVectorSet(vMin.vec.x,vMin.vec.y,vMin.vec.z,0.0f), XMVectorSet(vMax.vec.x,vMax.vec.y,vMax.vec.z,0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV  Vector3::Perpendicular( const Vector3& A ) noexcept
	{
		const float xAbs = fabs( A.GetX() );
		const float yAbs = fabs( A.GetY() );
		const float zAbs = fabs( A.GetZ() );
		const float minVal = TB_min( TB_min( xAbs, yAbs ), zAbs );

		if ( xAbs == minVal )
			return Vector3::Cross( A, Vector3( 1.0f, 0.0f, 0.0f ) );
		else if ( yAbs == minVal )
			return Vector3::Cross( A, Vector3( 0.0f, 1.0f, 0.0f ) );
		else
			return Vector3::Cross( A, Vector3( 0.0f, 0.0f, 1.0f ) );
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool XM_CALLCONV 	Vector3::Less3_Any(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return XMComparisonAnyFalse(XMVector3GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	 XM_CALLCONV Vector3::Less3_All(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return XMComparisonAllFalse(XMVector3GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	 XM_CALLCONV Vector3::Lessequal3_Any(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return XMComparisonAnyFalse(XMVector3GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE  bool XM_CALLCONV 	Vector3::Lessequal3_All(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return XMComparisonAllFalse(XMVector3GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool XM_CALLCONV 	Vector3::Greater3_Any(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return XMComparisonAnyTrue(XMVector3GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	 XM_CALLCONV Vector3::Greater3_All(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return XMComparisonAllTrue(XMVector3GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE  bool XM_CALLCONV	Vector3::Greaterequal3_Any(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return XMComparisonAnyTrue(XMVector3GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool XM_CALLCONV 	Vector3::Greaterequal3_All(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return XMComparisonAllTrue(XMVector3GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool XM_CALLCONV 	Vector3::Equal3_Any(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return XMComparisonAnyTrue(XMVector3EqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	 XM_CALLCONV Vector3::Equal3_All(const Vector3 &v0, const Vector3 &v1) noexcept
	{
		return XMComparisonAllTrue(XMVector3EqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool XM_CALLCONV 	Vector3::Nearequal3(const Vector3 &v0, const Vector3 &v1, const Vector3 &epsilon) noexcept
	{
		return (0 != XMVector3NearEqual(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f), XMVectorSet(epsilon.vec.x, epsilon.vec.y, epsilon.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE  Vector3 XM_CALLCONV	Vector3::Splat(float s) noexcept
	{
		XMVECTOR v;
		v = XMVectorSetX(v, s);
		return Vector3(XMVectorSplatX(v));
	}

	//------------------------------------------------------------------------------
	XM_INLINE  Vector3 XM_CALLCONV	Vector3::Splat(const Vector3 &v, UINT element) noexcept
	{
		assert(element < 4);

		switch(element)
		{
		case 0:
			return Vector3(XMVectorSplatX(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
		case 1:
			return Vector3(XMVectorSplatY(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
		case 2:
			return Vector3(XMVectorSplatZ(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
		}
		return Vector3(XMVectorSplatW(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Splat_X(const Vector3 &v) noexcept
	{
		return Vector3(XMVectorSplatX(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3  XM_CALLCONV	Vector3::Splat_Y(const Vector3 &v) noexcept
	{
		return Vector3(XMVectorSplatY(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Splat_Z(const Vector3 &v) noexcept
	{
		return Vector3(XMVectorSplatZ(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV 	Vector3::Splat_W(const Vector3 &v) noexcept
	{
		return Vector3(XMVectorSplatW(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	XM_INLINE  Vector3 XM_CALLCONV	Vector3::Permute(const Vector3& v0, const Vector3& v1, const UINT i0, const UINT i1, const UINT i2, const UINT i3) noexcept
	{
		return Vector3(XMVectorPermute(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f), XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f),i0,i1,i2,i3 ) );
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector3 XM_CALLCONV  Vector3::Transform( const Vector3& v, const Matrix &m) noexcept
	{
		return Vector3(XMVector3Transform(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f), m.mx));
	}

	//------------------------------------------------------------------------------
	XM_INLINE const bool XM_CALLCONV  Vector3::IsUnit() const noexcept
	{
		static const XMVECTOR g_UnitVectorEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		XMVECTOR Difference = XMVector3Length( XMVectorSet(this->vec.x, this->vec.y, this->vec.z, 0.0f) ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), g_UnitVectorEpsilon );
	}

	//------------------------------------------------------------------------------
	XM_INLINE  const bool XM_CALLCONV Vector3::IsUnit(const XMVECTOR v) noexcept
	{
		static const XMVECTOR g_UnitVectorEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		XMVECTOR Difference = XMVector3Length( v ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), g_UnitVectorEpsilon );
	}

	//------------------------------------------------------------------------------
	/// C++11 Move
	XM_INLINE  	Vector3& XM_CALLCONV	Vector3::operator=( _In_ Vector3&& other) noexcept
	{
		vec = other;
		return *this;
	}

	//------------------------------------------------------------------------------
	/// C++11 Move Constructor
	XM_INLINE   	Vector3::Vector3(_In_ Vector3&& other)
	{
		this->vec = other.vec;
	}


}

