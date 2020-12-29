
// -------------------------------------------------------------------
// File			:	Point4.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for 4D-Point-Class
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
 * Point4
 *
 ****************************************************************************/

namespace TurboMath
{

	//------------------------------------------------------------
	// Constructor
	// -----------------------------------------------------------

	/// default constructor, NOTE: setup components to ZERO!
	 XM_INLINE Point4::Point4() noexcept
	{
		vec.x = vec.y = vec.z = vec.w = 0.0f;
	}

	/// construct from values, set x and y to v1
	 XM_INLINE Point4::Point4( const float v1) noexcept
	{
		vec.x = vec.y = vec.z = vec.w = v1;
	}

	/// construct from values set x to v1 and y to v2 and z to v3
	 XM_INLINE Point4::Point4( const float v1, const float v2, const float v3, const float v4) noexcept
	{
		vec.x = v1;
		vec.y = v2;
		vec.z = v3;
		vec.w = v4;
	}

	/// construct from other Point4
	 XM_INLINE Point4::Point4( const Point4& p1) noexcept
	{
		vec = p1.vec;
	}

	/// C++11 Move Constructor
	 XM_INLINE Point4::Point4( Point4&& other) noexcept
	{
		vec = other.vec;		
	}

	//------------------------------------------------------------
	// assignment
	// -----------------------------------------------------------

	/// assignment operator
	 XM_INLINE void  XM_CALLCONV Point4::operator=( const Point4& rhs) noexcept
	{
		vec.x = rhs.vec.x;
		vec.y = rhs.vec.y;
		vec.z = rhs.vec.z;
		vec.w = rhs.vec.w;
	}

	/// assign an XMFLOAT4
	 XM_INLINE void  XM_CALLCONV Point4::operator=( XMFLOAT4 rhs) noexcept
	{
		vec.x = rhs.x;
		vec.y = rhs.y;
		vec.z = rhs.z;
		vec.w = rhs.w;
	}

	/// assign a float
	 XM_INLINE Point4  XM_CALLCONV Point4::operator=( const float rhs) noexcept
	{
		vec.x = vec.y = vec.z = vec.w = rhs;
		return *this;
	}

	/// assign a Vector4
	 XM_INLINE Point4  XM_CALLCONV Point4::operator=( const Vector4& rhs) noexcept
	{
		vec.x = rhs.GetX();
		vec.y = rhs.GetY();
		vec.z = rhs.GetZ();
		vec.w = rhs.GetW();
		return *this;
	}

	//------------------------------------------------------------
	// Casting-Operatoren
	//------------------------------------------------------------


	/// cast to Vector4
	 XM_INLINE Point4::operator Vector4 () noexcept
	{
		return Vector4(*this);
	}

	/// cast to const Vector4
	 XM_INLINE Point4::operator const Vector4 () const noexcept
	{
		return Vector4(*this);
	}



	//------------------------------------------------------------
	// C++11 Move
	//------------------------------------------------------------

	/// C++11 Move
	 XM_INLINE Point4&  XM_CALLCONV Point4::operator=( Point4&& other) noexcept
	{
		vec = other.vec;
		return *this;
	}

	//------------------------------------------------------------
	// operator
	//------------------------------------------------------------

	/// inplace add
	 XM_INLINE Point4&  XM_CALLCONV Point4::operator+=( const Point4 &rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorAdd(v1,v2);
		XMStoreFloat4( &vec, X );
		return *this;
	}

	/// inplace sub
	 XM_INLINE Point4& XM_CALLCONV  Point4::operator-=( const Point4 &rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorSubtract(v1,v2);
		XMStoreFloat4( &vec, X );
		return *this;
	}

	/// inplace float multiply
	 XM_INLINE Point4&  XM_CALLCONV Point4::operator*=( float s) noexcept
	{	
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR X = XMVectorScale(v1,s);
		XMStoreFloat4( &vec, X );
		return *this;
	} 


	/// muliply by a Point component-wise
	 XM_INLINE Point4&  XM_CALLCONV Point4::operator*=( const Point4& rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorMultiply(v1,v2);
		XMStoreFloat4( &vec, X );
		return *this;
	}

	/// inplace float division
	 XM_INLINE Point4&  XM_CALLCONV Point4::operator/=( float s) noexcept
	{	
		const float tmp = 1.0f / s + TURBOMATH_EPSILON;
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR X = XMVectorScale(v1,tmp);
		XMStoreFloat4( &vec, X );
		return *this;
	}

	/// muliply by a Point component-wise
	 XM_INLINE Point4  XM_CALLCONV Point4::operator*( const Point4& rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorMultiply(v1,v2);

		Point4 R;
		XMStoreFloat4( &R.vec, X );
		
		return R;
	}


	/// add 2 Points
	 XM_INLINE Point4  XM_CALLCONV Point4::operator+( const Point4 &rhs) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorAdd(v1,v2);

		Point4 R;
		XMStoreFloat4( &R.vec, X );

		return R;
	}

	/// subtract 2 Points
	 XM_INLINE Point4 XM_CALLCONV  Point4::operator-( const Point4 &rhs) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorSubtract(v1,v2);

		Point4 R;
		XMStoreFloat4( &R.vec, X );

		return R;
	}

	/// multiply with float
	 XM_INLINE Point4 XM_CALLCONV  Point4::operator*( float s) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR X = XMVectorScale(v1,s);

		Point4 R;
		XMStoreFloat4( &R.vec, X );
		
		return R;
	}

	/// equality operator
	 XM_INLINE bool  XM_CALLCONV Point4::operator==( const Point4 &rhs) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		return XMVector4Equal( v1, v2 );
	}

	/// inequality operator
	 XM_INLINE bool  XM_CALLCONV Point4::operator!=( const Point4 &rhs) const noexcept
	{	
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		return XMVector4NotEqual( v1, v2 );
	}

		
	/// Point-float division
	 XM_INLINE Point4 XM_CALLCONV  Point4::operator / ( const float f) const noexcept
	{	
		const float tmp = 1.0f / f + TURBOMATH_EPSILON;
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR X = XMVectorScale(v1,tmp);
		
		Point4 R;
		XMStoreFloat4( &R.vec, X );
		
		return R;
	}

	/// inplace division by Point
	 XM_INLINE Point4 XM_CALLCONV  Point4::operator/= (  const Point4& rhs ) noexcept
	{	
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorDivide(v1,v2);
		
		Point4 R;
		XMStoreFloat4( &R.vec, X );
		
		return R;
	}

	//------------------------------------------------------------
	// Set-Functions
	//------------------------------------------------------------

	/// set with Point4
	 XM_INLINE void XM_CALLCONV  Point4::Set(const Point4& rhs) noexcept
	{
		vec = rhs.vec;
	}

	/// set content
	 XM_INLINE void XM_CALLCONV  Point4::Set( const float x, const float y, const float z, const float w) noexcept
	{
		vec.x = x;
		vec.y = y;
		vec.z = z;
		vec.w = w;
	}

	/// Set Content
	 XM_INLINE void XM_CALLCONV  Point4::Set( const XMFLOAT4 rhs) noexcept
	{
		vec = rhs;
	}

	/// set the x component
	 XM_INLINE void XM_CALLCONV  Point4::SetX( const float x) noexcept
	{
		vec.x = x;
	}
		
	/// set the y component
	 XM_INLINE void  XM_CALLCONV Point4::SetY( const float y) noexcept
	{
		vec.y = y;
	}

	/// set the z component
	 XM_INLINE void  XM_CALLCONV Point4::SetZ( const float z) noexcept
	{
		vec.z = z;
	}

	/// set the w component
	 XM_INLINE void XM_CALLCONV  Point4::SetW( const float w) noexcept
	{
		vec.w = w;
	}

	/// set to Zero
	 XM_INLINE  void XM_CALLCONV  Point4::SetZero() noexcept
	{
		vec.x = vec.y = vec.z = vec.w = 0.0f;
	}

	//------------------------------------------------------------
	// Read / Write Access
	//------------------------------------------------------------

	/// read/write access to x component
	 XM_INLINE float&  XM_CALLCONV Point4::X() noexcept
	{
		return vec.x;
	}

	/// read/write access to y component
	 XM_INLINE float& XM_CALLCONV  Point4::Y() noexcept
	{
		return vec.y;
	}

	/// read/write access to z component
	 XM_INLINE float& XM_CALLCONV  Point4::Z() noexcept
	{
		return vec.z;
	}
	
	/// read/write access to w component
	 XM_INLINE float&  XM_CALLCONV Point4::W() noexcept
	{
		return vec.w;
	}

	/// read-only access to x component
	 XM_INLINE const float XM_CALLCONV  Point4::GetX() const noexcept
	{
		return vec.x;
	}
		
	/// read-only access to y component
	 XM_INLINE const float XM_CALLCONV  Point4::GetY() const noexcept
	{
		return vec.y;
	}

	/// read-only access to z component
	 XM_INLINE const float XM_CALLCONV  Point4::GetZ() const noexcept
	{
		return vec.z;
	}

	/// read-only access to w component
	 XM_INLINE const float XM_CALLCONV  Point4::GetW() const noexcept
	{
		return vec.w;
	}

	//------------------------------------------------------------
	// Get Raw Data (XMFLOAT4)
	//------------------------------------------------------------

	/// Get RawData
	 XM_INLINE XMFLOAT4 XM_CALLCONV 	Point4::GetRaw() const noexcept
	{
		return vec;
	}
	
	/// Get RawDataPtr
	 XM_INLINE XMFLOAT4* XM_CALLCONV 	Point4::GetRawPtr() noexcept
	{
		return &vec;
	}


}; // end of namespace TurboMath