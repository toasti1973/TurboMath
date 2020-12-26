

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
	__forceinline	Vector3::Vector3() :
	vec(0.0f,0.0f,0.0f)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector3::Vector3(float x, float y, float z) :
	vec(x,y,z)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector3::Vector3(XMVECTOR rhs) :
	vec((float*)&rhs)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector3::Vector3(const Vector3& rhs)
	{
		this->vec.x = rhs.vec.x;
		this->vec.y = rhs.vec.y;
		this->vec.z = rhs.vec.z;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector3::operator=(const Vector3 &rhs)
	{
		this->vec = rhs.vec;
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3::Vector3(const Vector4& rhs)
	{
		 XMStoreFloat3( &this->vec, rhs );
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::operator==(const Vector3 &rhs) const
	{
		return (0 != XMVector3Equal(XMLoadFloat3(&this->vec), XMLoadFloat3(&rhs.vec)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::operator!=(const Vector3 &rhs) const
	{
		return (0 != XMVector3NotEqual(XMLoadFloat3(&this->vec), XMLoadFloat3(&rhs.vec)));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline float&	Vector3::X()
	{
#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.x;
#elif __WIN32__
		return this->vec.m128_f32[0];
#endif
		return this->vec.x;
	}

	//------------------------------------------------------------------------------
	__forceinline float	Vector3::X() const
	{
		return Vector3::Unpack_X(XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f));
	}

	//------------------------------------------------------------------------------
	__forceinline float&	Vector3::Y()
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
	__forceinline float		Vector3::Y() const
	{
		return Vector4::Unpack_Y(XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f));
	}

	//------------------------------------------------------------------------------
	__forceinline float&	Vector3::Z()
	{
#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.z;
#elif __WIN32__
		return this->vec.m128_f32[2];
#endif
		return this->vec.z;
	}

	//------------------------------------------------------------------------------
	__forceinline float	Vector3::Z() const
	{
		return Vector4::Unpack_Z(XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f));
	}

	//------------------------------------------------------------------------------
	__forceinline XMFLOAT3 Vector3::GetRaw() const
	{
		return this->vec;
	}

	//------------------------------------------------------------------------------
	__forceinline XMFLOAT3* Vector3::GetRawPtr()
	{
		return &this->vec;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector3::Set(float x, float y, float z)
	{
		this->vec.x = x;
		this->vec.y = y;
		this->vec.z = z;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector3::SetX(float x)
	{
		this->vec.x = x;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector3::SetY(float y)
	{
		this->vec.y = y;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector3::SetZ(float z)
	{
		this->vec.z = z;
	}

	//------------------------------------------------------------------------------
	__forceinline const float	Vector3::GetX() const
	{
		return Vector4::Unpack_X( XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f) );
	}

	//------------------------------------------------------------------------------
	__forceinline const float	Vector3::GetY() const
	{
		return Vector4::Unpack_Y( XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f) );
	}

	//------------------------------------------------------------------------------
	__forceinline const float	Vector3::GetZ() const
	{
		return Vector4::Unpack_Z( XMVectorSet(this->vec.x,this->vec.y,this->vec.z,0.0f) );
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::operator-() const
	{
		return Vector3(-this->vec.x,-this->vec.y,-this->vec.z);
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::operator*(float t) const
	{
		return Vector3(this->vec.x * t,this->vec.y * t, this->vec.z * t);
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::operator+(const Vector3 &rhs) const
	{
		return Vector3(this->vec.x + rhs.vec.x, this->vec.y + rhs.vec.y, this->vec.z + rhs.vec.z);
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::operator-(const Vector3 &rhs) const
	{
		return Vector3(this->vec.x - rhs.vec.x, this->vec.y - rhs.vec.y, this->vec.z - rhs.vec.z);
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector3::operator+=(const Vector3 &rhs)
	{
		this->vec.x = this->vec.x + rhs.vec.x;
		this->vec.y = this->vec.y + rhs.vec.y;
		this->vec.z = this->vec.z + rhs.vec.z;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector3::operator-=(const Vector3 &rhs)
	{
		this->vec.x = this->vec.x - rhs.vec.x;
		this->vec.y = this->vec.y - rhs.vec.y;
		this->vec.z = this->vec.z - rhs.vec.z;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector3::operator*=(float s)
	{
		this->vec.x = this->vec.x * s;
		this->vec.y = this->vec.y * s;
		this->vec.z = this->vec.z * s;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector3::operator*=(const Vector3& rhs)
	{
		this->vec.x = this->vec.x * rhs.vec.x;
		this->vec.y = this->vec.y * rhs.vec.y;
		this->vec.z = this->vec.z * rhs.vec.z;
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::operator*(const Vector3& rhs)
	{
		return Vector3( this->vec.x * rhs.vec.x , this->vec.y * rhs.vec.y, this->vec.z * rhs.vec.z);
	}

	//------------------------------------------------------------------------------
	__forceinline float	Vector3::Length() const
	{
		return Vector3::Unpack_X(XMVector3Length(XMVectorSet(this->vec.x, this->vec.y, this->vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline float Vector3::Lengthsq() const
	{
		return Vector4::Unpack_X(XMVector3LengthSq(XMVectorSet(this->vec.x, this->vec.y, this->vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Abs() const
	{
		return XMVectorAbs(XMVectorSet(this->vec.x, this->vec.y, this->vec.z, 0.0f));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::NullVec()
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::UpVec()
	{
		return Vector3(0.0f, 1.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard down vector (0, -1, 0)
	__forceinline Vector3	Vector3::DownVec()
	{
		return Vector3(0.0f, -1.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard left vector (-1, 0, 0)
	__forceinline Vector3	Vector3::LeftVec()
	{
		return Vector3(-1.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	/// return the standard right vector (1, 0, 0)
	__forceinline Vector3	Vector3::RightVec()
	{
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard back vector (0, 0, 1)
	__forceinline Vector3	Vector3::BackVec()
	{
		return Vector3(0.0f, 0.0f, 1.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard foreward vector (0, 0, 1)
	__forceinline Vector3	Vector3::ForewardVec()
	{
		return Vector3(0.0f, 0.0f, -1.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard ZERO vector (0, 0, 0)
	__forceinline Vector3	Vector3::ZERO()
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard UNIT_X vector (1, 0, 0)
	__forceinline Vector3	Vector3::UNIT_X()
	{
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard UNIT_Y vector (0, 1, 0)
	__forceinline Vector3	Vector3::UNIT_Y()
	{
		return Vector3(0.0f, 1.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard UNIT_Z vector (0, 0, 1)
	__forceinline Vector3	Vector3::UNIT_Z()
	{
		return Vector3(0.0f, 0.0f, 1.0f);
	}

	//------------------------------------------------------------------------------
	__forceinline float		Vector3::Unpack_X(XMVECTOR v)
	{
		float x;
		XMVectorGetXPtr(&x, v);
		return x;
	}

	//------------------------------------------------------------------------------
	__forceinline float		Vector3::Unpack_Y(XMVECTOR v)
	{
		float y;
		XMVectorGetYPtr(&y, v);
		return y;
	}

	//------------------------------------------------------------------------------
	__forceinline float		Vector3::Unpack_Z(XMVECTOR v)
	{
		float z;
		XMVectorGetZPtr(&z, v);
		return z;
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Reciprocal(const Vector3 &v)
	{
		return Vector3(XMVectorReciprocal(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Multiply(const Vector3 &v0, const Vector3 &v1)
	{
		return Vector3(XMVectorMultiply(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f) , XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f) ));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Cross(const Vector3 &v0, const Vector3 &v1)
	{
		return Vector3(XMVector3Cross(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline float	Vector3::Dot(const Vector3 &v0, const Vector3 &v1)
	{
		return Vector3::Unpack_X(XMVector3Dot(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Barycentric(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, float f, float g)
	{
		return Vector3(XMVectorBaryCentric(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f), XMVectorSet(v2.vec.x, v2.vec.y, v2.vec.z, 0.0f), f, g));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Catmullrom(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, float s)
	{
		return Vector3(XMVectorCatmullRom(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f),XMVectorSet(v2.vec.x, v2.vec.y, v2.vec.z, 0.0f),XMVectorSet(v3.vec.x, v3.vec.y, v3.vec.z, 0.0f), s));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Hermite(const Vector3 &v1, const Vector3 &t1, const Vector3 &v2, const Vector3 &t2, float s)
	{
		return Vector3(XMVectorHermite(XMVectorSet(v1.vec.x,v1.vec.y,v1.vec.z,0.0f), XMVectorSet(t1.vec.x,t1.vec.y,t1.vec.z,0.0f), XMVectorSet(v2.vec.x,v2.vec.y,v2.vec.z,0.0f), XMVectorSet(t2.vec.x,t2.vec.y,t2.vec.z,0.0f), s));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Lerp(const Vector3 &v0, const Vector3 &v1, float s)
	{
		return Vector3(XMVectorLerp(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f), s));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Maximize(const Vector3 &v0, const Vector3 &v1)
	{
		return Vector3(XMVectorMax(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Minimize(const Vector3 &v0, const Vector3 &v1)
	{
		return Vector3(XMVectorMin(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Normalize(const Vector3 &v)
	{
		if (Vector3::Equal3_All(v, Vector3(0,0,0))) return v;

		return Vector3(XMVector3Normalize(XMVectorSet(v.vec.x,v.vec.y,v.vec.z,0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Reflect(const Vector3 &normal, const Vector3 &incident)
	{
		return Vector3(XMVector3Reflect(XMVectorSet(normal.vec.x, normal.vec.y, normal.vec.z, 0.0f),XMVectorSet(incident.vec.x, incident.vec.y, incident.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline  float Vector3::Angle(const Vector3& v0, const Vector3& v1)
	{
		return Vector3::Unpack_X(XMVector3AngleBetweenVectors(XMVectorSet(v0.vec.x,v0.vec.y,v0.vec.z,0.0f), XMVectorSet(v1.vec.x,v1.vec.y,v1.vec.z,0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline  Vector3 Vector3::Clamp(const Vector3& vClamp, const Vector3& vMin, const Vector3& vMax)
	{
		return Vector3(XMVectorClamp(XMVectorSet(vClamp.vec.x,vClamp.vec.y,vClamp.vec.z,0.0f), XMVectorSet(vMin.vec.x,vMin.vec.y,vMin.vec.z,0.0f), XMVectorSet(vMax.vec.x,vMax.vec.y,vMax.vec.z,0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline  Vector3 Vector3::Perpendicular( const Vector3& A )
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
	__forceinline bool	Vector3::Less3_Any(const Vector3 &v0, const Vector3 &v1)
	{
		return XMComparisonAnyFalse(XMVector3GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::Less3_All(const Vector3 &v0, const Vector3 &v1)
	{
		return XMComparisonAllFalse(XMVector3GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::Lessequal3_Any(const Vector3 &v0, const Vector3 &v1)
	{
		return XMComparisonAnyFalse(XMVector3GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::Lessequal3_All(const Vector3 &v0, const Vector3 &v1)
	{
		return XMComparisonAllFalse(XMVector3GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::Greater3_Any(const Vector3 &v0, const Vector3 &v1)
	{
		return XMComparisonAnyTrue(XMVector3GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::Greater3_All(const Vector3 &v0, const Vector3 &v1)
	{
		return XMComparisonAllTrue(XMVector3GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::Greaterequal3_Any(const Vector3 &v0, const Vector3 &v1)
	{
		return XMComparisonAnyTrue(XMVector3GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::Greaterequal3_All(const Vector3 &v0, const Vector3 &v1)
	{
		return XMComparisonAllTrue(XMVector3GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::Equal3_Any(const Vector3 &v0, const Vector3 &v1)
	{
		return XMComparisonAnyTrue(XMVector3EqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::Equal3_All(const Vector3 &v0, const Vector3 &v1)
	{
		return XMComparisonAllTrue(XMVector3EqualR(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector3::Nearequal3(const Vector3 &v0, const Vector3 &v1, const Vector3 &epsilon)
	{
		return (0 != XMVector3NearEqual(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f), XMVectorSet(epsilon.vec.x, epsilon.vec.y, epsilon.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector3	Vector3::Splat(float s)
	{
		XMVECTOR v;
		v = XMVectorSetX(v, s);
		return Vector3(XMVectorSplatX(v));
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector3	Vector3::Splat(const Vector3 &v, UINT element)
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
	__forceinline Vector3	Vector3::Splat_X(const Vector3 &v)
	{
		return Vector3(XMVectorSplatX(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector3	Vector3::Splat_Y(const Vector3 &v)
	{
		return Vector3(XMVectorSplatY(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector3	Vector3::Splat_Z(const Vector3 &v)
	{
		return Vector3(XMVectorSplatZ(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector3	Vector3::Splat_W(const Vector3 &v)
	{
		return Vector3(XMVectorSplatW(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3	Vector3::Permute(const Vector3& v0, const Vector3& v1, const UINT i0, const UINT i1, const UINT i2, const UINT i3)
	{
		return Vector3(XMVectorPermute(XMVectorSet(v0.vec.x, v0.vec.y, v0.vec.z, 0.0f), XMVectorSet(v1.vec.x, v1.vec.y, v1.vec.z, 0.0f),i0,i1,i2,i3 ) );
	}

	//------------------------------------------------------------------------------
	__forceinline Vector3 Vector3::Transform( const Vector3& v, const Matrix &m)
	{
		return Vector3(XMVector3Transform(XMVectorSet(v.vec.x, v.vec.y, v.vec.z, 0.0f), m.mx));
	}

	//------------------------------------------------------------------------------
	__forceinline bool Vector3::IsUnit() const 
	{
		static const XMVECTOR g_UnitVectorEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		XMVECTOR Difference = XMVector3Length( XMVectorSet(this->vec.x, this->vec.y, this->vec.z, 0.0f) ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), g_UnitVectorEpsilon );
	}

	//------------------------------------------------------------------------------
	__forceinline bool Vector3::IsUnit(const XMVECTOR v) 
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
	__forceinline	Vector3&	Vector3::operator=( _In_ Vector3&& other)
	{
		vec = other;
		return *this;
	}

	//------------------------------------------------------------------------------
	/// C++11 Move Constructor
	__forceinline	Vector3::Vector3(_In_ Vector3&& other)
	{
		this->vec = other.vec;
	}


}

