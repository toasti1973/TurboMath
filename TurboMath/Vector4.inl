
// -------------------------------------------------------------------
// File			:	Vector4.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for 4D-Vector-Class
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
 * Vector4
 *
 ****************************************************************************/

namespace TurboMath
{
	// constructs from Vector3
	XM_INLINE	Vector4::Vector4( const Vector3& rhs) 
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->vec,16));

		this->vec = XMLoadFloat3((XMFLOAT3*)&rhs.GetRaw());
		this->SetW(0.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE	Vector4::Vector4() noexcept
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->vec,16));

		this->vec = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE	Vector4::Vector4( float x,  float y,  float z,  float w) 
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->vec,16));

		this->vec = XMVectorSet(x, y, z, w);
	}

	//------------------------------------------------------------------------------
	XM_INLINE	Vector4::Vector4( float x) 
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->vec,16));

		this->vec = XMVectorSet(x, x, x, x);
	}

	//------------------------------------------------------------------------------
	XM_INLINE	Vector4::Vector4( XMVECTOR rhs)   :
	vec(rhs)
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->vec,16));
	}

	//------------------------------------------------------------------------------
	XM_INLINE	Vector4::Vector4( float x,  float y,  float z)
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->vec,16));

		this->vec = XMVectorSet(x, y, z, 0.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE	Vector4::Vector4( const Vector4& rhs)
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->vec,16));

		this->vec = rhs.vec;
	}

	//------------------------------------------------------------------------------
	XM_INLINE	Vector4::Vector4( const XMFLOAT3& rhs)
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->vec,16));

		this->vec = XMLoadFloat3(&rhs);
		this->SetW(0.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE	Vector4::Vector4( const Vector3& rhs,  const float w) 
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->vec,16));

		this->vec = XMLoadFloat3(&rhs.GetRaw());
		this->SetW( w );
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::operator=( const Vector4 &rhs) 
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->vec,16));

		this->vec = rhs.vec;
	}

	//------------------------------------------------------------------------------
	XM_INLINE void 	XM_CALLCONV Vector4::operator=( XMVECTOR rhs) noexcept
	{
		this->vec = rhs;
	}
	//------------------------------------------------------------------------------
	XM_INLINE void 	XM_CALLCONV Vector4::operator=( XMFLOAT3 rhs) noexcept
	{
		this->vec = XMLoadFloat3A((XMFLOAT3A*)&rhs);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4 	XM_CALLCONV Vector4::operator=( float rhs) noexcept
	{
		return Vector4(rhs);
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::operator==( const Vector4 &rhs) const noexcept
	{
		return (0 != XMVector4Equal(this->vec, rhs.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::operator!=( const Vector4 &rhs) const noexcept
	{
		return (0 != XMVector4NotEqual(this->vec, rhs.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::Load( const float* ptr) noexcept
	{
		this->vec = XMLoadFloat4A((XMFLOAT4A*)ptr);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::LoadU( const float* ptr) noexcept
	{
		this->vec = XMLoadFloat4((XMFLOAT4*)ptr);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::Store( float* ptr) const noexcept
	{
		XMStoreFloat4A((XMFLOAT4A*)ptr, this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::StoreU( float* ptr) const noexcept
	{
		XMStoreFloat4((XMFLOAT4*)ptr, this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::Stream( float* ptr) const noexcept
	{
		XMStoreFloat4A((XMFLOAT4A*)ptr, this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::Load_Float3( const void* ptr,  float w) noexcept
	{
		this->vec = XMLoadFloat3((XMFLOAT3*)ptr);
		this->SetW(w);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::operator-() const noexcept
	{
		return XMVectorNegate(this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::operator*( float t) const noexcept
	{
		return XMVectorScale(this->vec, t);
	}

	//------------------------------------------------------------------------------
	// vector-float division
	XM_INLINE Vector4	XM_CALLCONV Vector4::operator / ( const float f) const noexcept
	{
		// Add simple Data ti the float, so we don´t have a Division by Zero!
		const float div = f + 0.000001f;

		const float x = this->GetX() / div;
		const float y = this->GetY() / div;
		const float z = this->GetZ() / div;
		const float w = this->GetW() / div;

		return Vector4(x,y,z,w);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::operator/= (  const float fScalar ) noexcept
	{
		// Add simple Data ti the float, so we don´t have a Division by Zero!
		const float div = fScalar + 0.000001f;

		this->SetX(this->GetX() / div);
		this->SetY(this->GetY() / div);
		this->SetZ(this->GetZ() / div);
		this->SetW(this->GetW() / div);

		return( *this );
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::operator/= (  const Vector4& rhs ) noexcept
	{
		const float x = rhs.GetX() != 0.0f ? this->GetX() / rhs.GetX() : 0.0f;
		const float y = rhs.GetY() != 0.0f ? this->GetY() / rhs.GetY() : 0.0f;
		const float z = rhs.GetZ() != 0.0f ? this->GetZ() / rhs.GetZ() : 0.0f;
		const float w = rhs.GetW() != 0.0f ? this->GetW() / rhs.GetW() : 0.0f;

		this->Set(x,y,z,w);

		return( *this );
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::operator*=( const Vector4& rhs) noexcept
	{
		this->vec = XMVectorMultiply(this->vec, rhs.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::operator*( const Vector4& rhs) noexcept
	{
		return Vector4( XMVectorMultiply(this->vec, rhs.vec) );
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::operator+=( const Vector4 &rhs) noexcept
	{
		this->vec = XMVectorAdd(this->vec, rhs.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::operator-=( const Vector4 &rhs) noexcept
	{
		this->vec = XMVectorSubtract(this->vec, rhs.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::operator*=( float s) noexcept
	{
		this->vec = XMVectorScale(this->vec, s);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::operator+( const Vector4 &rhs) const noexcept
	{
		return XMVectorAdd(this->vec, rhs.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::operator-( const Vector4 &rhs) const noexcept
	{
		return XMVectorSubtract(this->vec, rhs.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::Set( float x,  float y,  float z,  float w) noexcept
	{
		this->vec = XMVectorSet(x, y, z, w);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV Vector4::Set( XMVECTOR rhs) noexcept
	{
		this->vec = rhs;
	}

	//------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV Vector4::Set( const Vector4& rhs) noexcept
	{
		this->vec = rhs.vec;
	}

	//------------------------------------------------------------------------------
	XM_INLINE float& XM_CALLCONV Vector4::X() noexcept
	{
		return this->vec.m128_f32[0];
	}

	//------------------------------------------------------------------------------
	XM_INLINE const float	XM_CALLCONV Vector4::GetX() const noexcept
	{
		return Vector4::Unpack_X(this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float& XM_CALLCONV Vector4::Y() noexcept
	{
		return this->vec.m128_f32[1];
	}

	//------------------------------------------------------------------------------
	XM_INLINE const float		XM_CALLCONV Vector4::GetY() const noexcept
	{
		return Vector4::Unpack_Y(this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float& XM_CALLCONV Vector4::Z() noexcept
	{
		return this->vec.m128_f32[2];
	}

	//------------------------------------------------------------------------------
	XM_INLINE const float	XM_CALLCONV Vector4::GetZ() const noexcept
	{
		return Vector4::Unpack_Z(this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float& XM_CALLCONV Vector4::W() noexcept
	{
		return this->vec.m128_f32[3];
	}

	//------------------------------------------------------------------------------
	XM_INLINE const float	XM_CALLCONV Vector4::GetW() const noexcept
	{
		return Vector4::Unpack_W(this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE XMVECTOR XM_CALLCONV Vector4::GetRaw() const noexcept
	{
		return this->vec;
	}

	//------------------------------------------------------------------------------
	XM_INLINE XMVECTOR* XM_CALLCONV Vector4::GetRawPtr() noexcept
	{ 
		return &this->vec;
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::Set( const float x, const float y, const float z) noexcept
	{
		Vector4::Set(x, y, z, 0.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::SetX( const float x) noexcept
	{
		this->vec = XMVectorSetXPtr(this->vec, &x);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::SetY( const float y) noexcept
	{
		this->vec = XMVectorSetYPtr(this->vec, &y);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::SetZ( const float z) noexcept
	{
		this->vec = XMVectorSetZPtr(this->vec, &z);
	}

	//------------------------------------------------------------------------------
	XM_INLINE void	XM_CALLCONV Vector4::SetW( const float w) noexcept
	{
		this->vec = XMVectorSetWPtr(this->vec, &w);
	}

	//------------------------------------------------------------------------------
	XM_INLINE const float	XM_CALLCONV Vector4::Length() const noexcept
	{
		return Vector4::Unpack_X(XMVector4Length(this->vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE const float XM_CALLCONV Vector4::Lengthsq() const noexcept
	{
		return Vector4::Unpack_X(XMVector4LengthSq(this->vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Reciprocal( const Vector4 &v) noexcept
	{
		return XMVectorReciprocal(v.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Multiply( const Vector4 &v0,  const Vector4 &v1) noexcept
	{
		return XMVectorMultiply(v0.vec, v1.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Abs() const noexcept
	{
		return XMVectorAbs(this->vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Cross( const Vector4 &v0,  const Vector4 &v1) noexcept
	{
		return XMVector3Cross(v0.vec, v1.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float	XM_CALLCONV Vector4::Dot( const Vector4 &v0,  const Vector4 &v1) noexcept
	{
		return Vector4::Unpack_X(XMVector3Dot(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Barycentric(const Vector4 &v0, const Vector4 &v1, const Vector4 &v2, float f, float g) noexcept
	{
		return XMVectorBaryCentric(v0.vec, v1.vec, v2.vec, f, g);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Catmullrom(const Vector4 &v0, const Vector4 &v1, const Vector4 &v2, const Vector4 &v3, float s) noexcept
	{
		return XMVectorCatmullRom(v0.vec, v1.vec, v2.vec, v3.vec, s);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Hermite(const Vector4 &v1, const Vector4 &t1, const Vector4 &v2, const Vector4 &t2, float s) noexcept
	{
		return XMVectorHermite(v1.vec, t1.vec, v2.vec, t2.vec, s);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Lerp(const Vector4 &v0, const Vector4 &v1, float s) noexcept
	{
		return XMVectorLerp(v0.vec, v1.vec, s);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Maximize(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMVectorMax(v0.vec, v1.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Minimize(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMVectorMin(v0.vec, v1.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Normalize(const Vector4 &v) noexcept
	{
		if (Vector4::Equal3_All(v, Vector4(0,0,0,0))) return v;
		return XMVector4Normalize(v.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::Reflect(const Vector4 &normal, const Vector4 &incident) noexcept
	{
		return XMVector3Reflect(incident.vec, normal.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::NullVec() noexcept
	{
		return Vector4(0.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4	XM_CALLCONV Vector4::UpVec() noexcept
	{
		return Vector4(0.0f, 1.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard down vector (0, -1, 0)
	XM_INLINE Vector4	XM_CALLCONV Vector4::DownVec() noexcept
	{
		return Vector4(0.0f, -1.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard left vector (-1, 0, 0)
	XM_INLINE Vector4	XM_CALLCONV Vector4::LeftVec() noexcept
	{
		return Vector4(-1.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard right vector (1, 0, 0)
	XM_INLINE Vector4	XM_CALLCONV Vector4::RightVec() noexcept
	{
		return Vector4(1.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard back vector (0, 0, 1)
	XM_INLINE Vector4	XM_CALLCONV Vector4::BackVec() noexcept
	{
		return Vector4(0.0f, 0.0f, 1.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard foreward vector (0, 0, 1)
	XM_INLINE Vector4	XM_CALLCONV Vector4::ForewardVec() noexcept
	{
		return Vector4(0.0f, 0.0f, -1.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard ZERO vector (0, 0, 0,0)
	XM_INLINE Vector4	XM_CALLCONV Vector4::ZERO() noexcept
	{
		return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard UNIT_X vector (1, 0, 0, 0)
	XM_INLINE Vector4	XM_CALLCONV Vector4::UNIT_X() noexcept
	{
		return Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard UNIT_Y vector (0, 1, 0, 0)
	XM_INLINE Vector4	XM_CALLCONV Vector4::UNIT_Y() noexcept
	{
		return Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// return the standard UNIT_Z vector (0, 0, 1, 0)
	XM_INLINE Vector4	XM_CALLCONV Vector4::UNIT_Z() noexcept
	{
		return Vector4(0.0f, 0.0f, 1.0f, 0.0f);
	}

	//------------------------------------------------------------------------------
	/// Performs a per-component test for less-than between two vectors.
	XM_INLINE Vector4 XM_CALLCONV Vector4::Less( const Vector4& v1,  const Vector4& v2) noexcept
	{
		return Vector4(XMVectorLess(v1.vec,v2.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Less4_Any(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAnyFalse(XMVector4GreaterOrEqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Less4_All(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAllFalse(XMVector4GreaterOrEqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Lessequal4_Any(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAnyFalse(XMVector4GreaterR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Lessequal4_All(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAllFalse(XMVector4GreaterR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Greater4_Any(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAnyTrue(XMVector4GreaterR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Greater4_All(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAllTrue(XMVector4GreaterR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Greaterequal4_Any(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAnyTrue(XMVector4GreaterOrEqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Greaterequal4_All(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAllTrue(XMVector4GreaterOrEqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Gqual4_Any(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAnyTrue(XMVector4EqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Equal4_All(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAllTrue(XMVector4EqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Nearequal4(const Vector4 &v0, const Vector4 &v1, const Vector4 &epsilon) noexcept
	{
		return (0 != XMVector4NearEqual(v0.vec, v1.vec, epsilon.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Less3_Any(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAnyFalse(XMVector3GreaterOrEqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Less3_All(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAllFalse(XMVector3GreaterOrEqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Lessequal3_Any(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAnyFalse(XMVector3GreaterR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Lessequal3_All(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAllFalse(XMVector3GreaterR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Greater3_Any(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAnyTrue(XMVector3GreaterR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Greater3_All(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAllTrue(XMVector3GreaterR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Greaterequal3_Any(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAnyTrue(XMVector3GreaterOrEqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Greaterequal3_All(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAllTrue(XMVector3GreaterOrEqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Equal3_Any(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAnyTrue(XMVector3EqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Equal3_All(const Vector4 &v0, const Vector4 &v1) noexcept
	{
		return XMComparisonAllTrue(XMVector3EqualR(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE bool	XM_CALLCONV Vector4::Nearequal3(const Vector4 &v0, const Vector4 &v1, const Vector4 &epsilon) noexcept
	{
		return (0 != XMVector3NearEqual(v0.vec, v1.vec, epsilon.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE float		XM_CALLCONV Vector4::Unpack_X(XMVECTOR v) noexcept
	{
		float x;
		XMVectorGetXPtr(&x, v);
		return x;
	}

	//------------------------------------------------------------------------------
	XM_INLINE float		XM_CALLCONV Vector4::Unpack_Y(XMVECTOR v) noexcept
	{
		float y;
		XMVectorGetYPtr(&y, v);
		return y;
	}

	//------------------------------------------------------------------------------
	XM_INLINE float		XM_CALLCONV Vector4::Unpack_Z(XMVECTOR v) noexcept
	{
		float z;
		XMVectorGetZPtr(&z, v);
		return z;
	}

	//------------------------------------------------------------------------------
	XM_INLINE float		XM_CALLCONV Vector4::Unpack_W(XMVECTOR v) noexcept
	{
		float w;
		XMVectorGetWPtr(&w, v);
		return w;
	}
	//------------------------------------------------------------------------------
	XM_INLINE	const Vector4	XM_CALLCONV Vector4::Splat(float s) noexcept
	{
		XMVECTOR v;
		v = XMVectorSetX(v, s);
		return Vector4(XMVectorSplatX(v));
	}

	//------------------------------------------------------------------------------
	XM_INLINE	const Vector4	XM_CALLCONV Vector4::Splat(const Vector4 &v, UINT element) noexcept
	{
		assert(element < 4);

		switch(element)
		{
		case 0:
			return Vector4(XMVectorSplatX(v.vec));
		case 1:
			return Vector4(XMVectorSplatY(v.vec));
		case 2:
			return Vector4(XMVectorSplatZ(v.vec));
		}
		return Vector4(XMVectorSplatW(v.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE const Vector4	XM_CALLCONV Vector4::Splat_X(const Vector4 &v) noexcept
	{
		return Vector4(XMVectorSplatX(v.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE	const Vector4	XM_CALLCONV Vector4::Splat_Y(const Vector4 &v) noexcept
	{
		return Vector4(XMVectorSplatY(v.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE	const Vector4	XM_CALLCONV Vector4::Splat_Z(const Vector4 &v) noexcept
	{
		return Vector4(XMVectorSplatZ(v.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE	const Vector4	XM_CALLCONV Vector4::Splat_W(const Vector4 &v) noexcept
	{
		return Vector4(XMVectorSplatW(v.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE const Vector4	XM_CALLCONV Vector4::Permute(const Vector4& v0, const Vector4& v1, const UINT i0, const UINT i1, const UINT i2, const UINT i3) noexcept
	{
		return Vector4(XMVectorPermute(v0.vec, v1.vec,  i0,  i1,  i2, i3));
	}

	//------------------------------------------------------------------------------
	XM_INLINE  float XM_CALLCONV Vector4::Angle(const Vector4& v0, const Vector4& v1) noexcept
	{
		return Vector4::Unpack_X(XMVector4AngleBetweenVectors(v0.vec, v1.vec));
	}

	//------------------------------------------------------------------------------

	XM_INLINE  Vector4 XM_CALLCONV Vector4::Clamp(const Vector4& vClamp, const Vector4& vMin, const Vector4& vMax) noexcept
	{
		return XMVectorClamp(vClamp.vec, vMin.vec, vMax.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE  void XM_CALLCONV Vector4::Load_ubyte4n_signed(const void* ptr, float w) noexcept
	{
		// need to endian-convert the source...
		DirectX::PackedVector::XMUBYTEN4 ub4nValue = *(DirectX::PackedVector::XMUBYTEN4*)ptr;
		this->vec = XMVectorSubtract(XMVectorScale(DirectX::PackedVector::XMLoadUByteN4(&ub4nValue), 2.0f), XMVectorSplatOne());
		this->SetW(w);
	}

	//------------------------------------------------------------------------------
	XM_INLINE  const float XM_CALLCONV Vector4::AngleWith(const Vector4& v) noexcept
	{
		return Vector4::Unpack_X(XMVector4AngleBetweenVectors(this->vec, v.vec));
	}

	//------------------------------------------------------------------------------
	/// Select
	XM_INLINE  const Vector4 XM_CALLCONV Vector4::Select( const Vector4& v1, const Vector4& v2, const Vector4& Control) noexcept
	{
		return Vector4(XMVectorSelect(v1.vec,v2.vec,Control.vec));
	}

	//------------------------------------------------------------------------------
	XM_INLINE const bool XM_CALLCONV Vector4::IsUnit() const  noexcept
	{
		static const XMVECTOR g_UnitVectorEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		XMVECTOR Difference = XMVector4Length( vec ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), g_UnitVectorEpsilon );
	}

	//------------------------------------------------------------------------------
	XM_INLINE const bool XM_CALLCONV Vector4::IsUnit(const XMVECTOR v)  noexcept
	{
		static const XMVECTOR g_UnitVectorEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		XMVECTOR Difference = XMVector4Length( v ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), g_UnitVectorEpsilon );
	}

	//------------------------------------------------------------------------------
	XM_INLINE const Vector4	XM_CALLCONV Vector4::Transform( const Vector4 & v, const Matrix &m) noexcept
	{
		return XMVector4Transform(v.vec, m.mx);
	}

	//------------------------------------------------------------------------------
	XM_INLINE Vector4  XM_CALLCONV Vector4::Rotate( const Quat& Rotation,  const float Scale ) noexcept
	{
		vec = XMVector3Rotate( XMVectorMultiply(XMVectorReplicate( Scale ) , vec) , Rotation.Get() );

		return this->vec;
	}

	//------------------------------------------------------------------------------
	XM_INLINE const Vector4 XM_CALLCONV Vector4::operator * ( const Matrix& m) const noexcept
	{
		XMVector3Transform(this->vec, m.mx );

		return this->vec;
	}

	//------------------------------------------------------------------------------
	/// C++11 Move
	XM_INLINE	Vector4& XM_CALLCONV Vector4::operator=(  Vector4&& other) noexcept
	{
		//return std::move(other);
		this->vec = other.vec;
		return *this;
	}

	//------------------------------------------------------------------------------
	/// C++11 Move Constructor
	XM_INLINE	Vector4::Vector4( Vector4&& other) noexcept
	{
		this->vec = other.vec;
	}

};// Namespace TurboMath

