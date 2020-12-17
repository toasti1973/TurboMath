
// -------------------------------------------------------------------
// File			:	Vector2.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for 2D-Vector-Class
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
 * Point2
 *
 ****************************************************************************/

namespace TurboMath
{
	
	//------------------------------------------------------------------------------
	__forceinline	Vector2::Vector2() :
	vec(0.0f,0.0f)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector2::Vector2(float x, float y) :
	vec(x,y)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector2::Vector2(XMVECTOR rhs) :
	vec((float*)&rhs)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector2::Vector2(const Vector2& rhs)
	{
		this->vec.x = rhs.vec.x;
		this->vec.y = rhs.vec.y;
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector2::Vector2(const Point2& rhs)
	{
		this->vec.x = rhs.GetX();
		this->vec.y = rhs.GetY();
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector2::operator=(const Vector2 &rhs)
	{
		this->vec = rhs.vec;
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::operator==(const Vector2 &rhs) const
	{
		return (0 != XMVector2Equal(XMLoadFloat2(&this->vec), XMLoadFloat2(&rhs.vec)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::operator!=(const Vector2 &rhs) const
	{
		return (0 != XMVector2NotEqual(XMLoadFloat2(&this->vec), XMLoadFloat2(&rhs.vec)));
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector2::Set(float x, float y)
	{
		this->vec.x = x;
		this->vec.y = y;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector2::SetX(float x)
	{
		this->vec.x = x;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector2::SetY(float y)
	{
		this->vec.y = y;
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::operator-() const
	{
		return Vector2(-this->vec.x,-this->vec.y);
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::operator*(float t) const
	{
		return Vector2(this->vec.x * t,this->vec.y * t);
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::operator+(const Vector2 &rhs) const
	{
		return Vector2(this->vec.x + rhs.vec.x, this->vec.y + rhs.vec.y);
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::operator-(const Vector2 &rhs) const
	{
		return Vector2(this->vec.x - rhs.vec.x, this->vec.y - rhs.vec.y);
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector2::operator+=(const Vector2 &rhs)
	{
		this->vec.x = this->vec.x + rhs.vec.x;
		this->vec.y = this->vec.y + rhs.vec.y;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector2::operator-=(const Vector2 &rhs)
	{
		this->vec.x = this->vec.x - rhs.vec.x;
		this->vec.y = this->vec.y - rhs.vec.y;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector2::operator*=(float s)
	{
		this->vec.x = this->vec.x * s;
		this->vec.y = this->vec.y * s;
	}

	//------------------------------------------------------------------------------
	__forceinline void	Vector2::operator*=(const Vector2& rhs)
	{
		this->vec.x = this->vec.x * rhs.vec.x;
		this->vec.y = this->vec.y * rhs.vec.y;
	}

	//------------------------------------------------------------------------------
	__forceinline float&	Vector2::x()
	{
#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.x;
#elif __WIN32__
		return this->vec.m128_f32[0];
#endif
		return this->vec.x;
	}

	//------------------------------------------------------------------------------
	__forceinline float	Vector2::GetX() const
	{
		return Vector2::unpack_x(XMVectorSet(this->vec.x,this->vec.y,0.0f,0.0f));
	}

	//------------------------------------------------------------------------------
	__forceinline float&	Vector2::y()
	{
#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.y;
#elif __WIN32__
		return this->vec.m128_f32[1];
#endif
		return this->vec.y;
	}

	//------------------------------------------------------------------------------
	__forceinline float		Vector2::GetY() const
	{
		return Vector2::unpack_y(XMVectorSet(this->vec.x,this->vec.y,0.0f,0.0f));
	}

	//------------------------------------------------------------------------------
	__forceinline XMFLOAT2 Vector2::GetRaw() const
	{
		return this->vec;
	}

	//------------------------------------------------------------------------------
	__forceinline XMFLOAT2* Vector2::GetRawPtr()
	{
		return &this->vec;
	}

	//------------------------------------------------------------------------------
	__forceinline float	Vector2::Length() const
	{
		return Vector2::unpack_x(XMVector2Length(XMVectorSet(this->vec.x, this->vec.y,0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline float Vector2::Lengthsq() const
	{
		return Vector4::Unpack_X(XMVector2LengthSq(XMVectorSet(this->vec.x, this->vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::abs() const
	{
		return XMVectorAbs(XMVectorSet(this->vec.x, this->vec.y, 0.0f, 0.0f));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::NullVec()
	{
		return Vector2(0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	__forceinline float		Vector2::unpack_x(XMVECTOR v)
	{
		float x;
		XMVectorGetXPtr(&x, v);
		return x;
	}

	//------------------------------------------------------------------------------
	__forceinline float		Vector2::unpack_y(XMVECTOR v)
	{
		float y;
		XMVectorGetYPtr(&y, v);
		return y;
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Reciprocal(const Vector2 &v)
	{
		return Vector2(XMVectorReciprocal(XMVectorSet(v.vec.x, v.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Multiply(const Vector2 &v0, const Vector2 &v1)
	{
		return Vector2(XMVectorMultiply(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f) , XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f) ));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Cross3(const Vector2 &v0, const Vector2 &v1)
	{
		return Vector2(XMVector2Cross(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline float	Vector2::Dot3(const Vector2 &v0, const Vector2 &v1)
	{
		return Vector2::unpack_x(XMVector2Dot(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Barycentric(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2, float f, float g)
	{
		return Vector2(XMVectorBaryCentric(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f), XMVectorSet(v2.vec.x, v2.vec.y, 0.0f, 0.0f), f, g));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Catmullrom(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, float s)
	{
		return Vector2(XMVectorCatmullRom(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f),XMVectorSet(v2.vec.x, v2.vec.y, 0.0f, 0.0f),XMVectorSet(v3.vec.x, v3.vec.y, 0.0f, 0.0f), s));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Hermite(const Vector2 &v1, const Vector2 &t1, const Vector2 &v2, const Vector2 &t2, float s)
	{
		return Vector2(XMVectorHermite(XMVectorSet(v1.vec.x,v1.vec.y,0.0f,0.0f), XMVectorSet(t1.vec.x,t1.vec.y,0.0f,0.0f), XMVectorSet(v2.vec.x,v2.vec.y,0.0f,0.0f), XMVectorSet(t2.vec.x,t2.vec.y,0.0f,0.0f), s));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Lerp(const Vector2 &v0, const Vector2 &v1, float s)
	{
		return Vector2(XMVectorLerp(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f), s));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Maximize(const Vector2 &v0, const Vector2 &v1)
	{
		return Vector2(XMVectorMax(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Minimize(const Vector2 &v0, const Vector2 &v1)
	{
		return Vector2(XMVectorMin(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Normalize(const Vector2 &v)
	{
		if (Vector2::Equal3_all(v, Vector2(0,0))) return v;

		return Vector2(XMVector2Normalize(XMVectorSet(v.vec.x,v.vec.y,0.0f,0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Reflect(const Vector2 &normal, const Vector2 &incident)
	{
		return Vector2(XMVector2Reflect(XMVectorSet(normal.vec.x, normal.vec.y, 0.0f, 0.0f),XMVectorSet(incident.vec.x, incident.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline  float Vector2::Angle(const Vector2& v0, const Vector2& v1)
	{
		return Vector2::unpack_x(XMVector2AngleBetweenVectors(XMVectorSet(v0.vec.x,v0.vec.y,0.0f,0.0f), XMVectorSet(v1.vec.x,v1.vec.y,0.0f,0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline  Vector2 Vector2::Clamp(const Vector2& vClamp, const Vector2& vMin, const Vector2& vMax)
	{
		return Vector2(XMVectorClamp(XMVectorSet(vClamp.vec.x,vClamp.vec.y,0.0f,0.0f), XMVectorSet(vMin.vec.x,vMin.vec.y,0.0f,0.0f), XMVectorSet(vMax.vec.x,vMax.vec.y,0.0f,0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::Less3_Any(const Vector2 &v0, const Vector2 &v1)
	{
		return XMComparisonAnyFalse(XMVector2GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::Less3_All(const Vector2 &v0, const Vector2 &v1)
	{
		return XMComparisonAllFalse(XMVector2GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::Lessequal3_Any(const Vector2 &v0, const Vector2 &v1)
	{
		return XMComparisonAnyFalse(XMVector2GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::Lessequal3_All(const Vector2 &v0, const Vector2 &v1)
	{
		return XMComparisonAllFalse(XMVector2GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::Greater3_Any(const Vector2 &v0, const Vector2 &v1)
	{
		return XMComparisonAnyTrue(XMVector2GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::Greater3_All(const Vector2 &v0, const Vector2 &v1)
	{
		return XMComparisonAllTrue(XMVector2GreaterR(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::Greaterequal3_Any(const Vector2 &v0, const Vector2 &v1)
	{
		return XMComparisonAnyTrue(XMVector2GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::Greaterequal3_All(const Vector2 &v0, const Vector2 &v1)
	{
		return XMComparisonAllTrue(XMVector2GreaterOrEqualR(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::Equal3_Any(const Vector2 &v0, const Vector2 &v1)
	{
		return XMComparisonAnyTrue(XMVector2EqualR(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::Equal3_all(const Vector2 &v0, const Vector2 &v1)
	{
		return XMComparisonAllTrue(XMVector2EqualR(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline bool	Vector2::Nearequal3(const Vector2 &v0, const Vector2 &v1, const Vector2 &epsilon)
	{
		return (0 != XMVector2NearEqual(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f),XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f), XMVectorSet(epsilon.vec.x, epsilon.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector2	Vector2::Splat(float s)
	{
		XMVECTOR v;
		v = XMVectorSetX(v, s);
		return Vector2(XMVectorSplatX(v));
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector2	Vector2::Splat(const Vector2 &v, UINT element)
	{
		assert(element < 3);

		switch(element)
		{
		case 0:
			return Vector2(XMVectorSplatX(XMVectorSet(v.vec.x, v.vec.y, 0.0f, 0.0f)));
		case 1:
			return Vector2(XMVectorSplatY(XMVectorSet(v.vec.x, v.vec.y, 0.0f, 0.0f)));
		}
		return Vector2(XMVectorSplatW(XMVectorSet(v.vec.x, v.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Splat_X(const Vector2 &v)
	{
		return Vector2(XMVectorSplatX(XMVectorSet(v.vec.x, v.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector2	Vector2::Splat_Y(const Vector2 &v)
	{
		return Vector2(XMVectorSplatY(XMVectorSet(v.vec.x, v.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline	Vector2	Vector2::Splat_W(const Vector2 &v)
	{
		return Vector2(XMVectorSplatW(XMVectorSet(v.vec.x, v.vec.y, 0.0f, 0.0f)));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2	Vector2::Permute(const Vector2& v0, const Vector2& v1, const UINT i0, const UINT i1, const UINT i2, const UINT i3)
	{
		return Vector2(XMVectorPermute(XMVectorSet(v0.vec.x, v0.vec.y, 0.0f, 0.0f), XMVectorSet(v1.vec.x, v1.vec.y, 0.0f, 0.0f), i0, i1, i2, i3));
	}

	//------------------------------------------------------------------------------
	__forceinline Vector2 Vector2::Transform( const Vector2& v,  const Matrix &m)
	{
		return Vector2(XMVector2Transform(XMVectorSet(v.vec.x, v.vec.y, 0.0f, 0.0f), m.mx));
	}

	//------------------------------------------------------------------------------
    /// C++11 Move Constructor
    __forceinline Vector2::Vector2(_In_ Vector2&& other)
    {
        this->vec = other.vec;
    }
    }

