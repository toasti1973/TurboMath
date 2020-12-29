
// -------------------------------------------------------------------
// File			:	Point3.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for 3D-Point-Class
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
 * Point3
 *
 ****************************************************************************/

namespace TurboMath
{

	//------------------------------------------------------------
	// Constructor
	// -----------------------------------------------------------

	/// default constructor, NOTE: setup components to ZERO!
	XM_INLINE Point3::Point3() noexcept
	{
		vec.x = vec.y = vec.z = 0.0f;
	}

	/// construct from values, set x and y to v1
	XM_INLINE Point3::Point3( const float v1) noexcept
	{
		vec.x = vec.y = vec.z = v1;
	}

	/// construct from values set x to v1 and y to v2 and z to v3
	XM_INLINE Point3::Point3( const float v1, const float v2, const float v3) noexcept
	{
		vec.x = v1;
		vec.y = v2;
		vec.z = v3;
	}

	/// construct from other Point3
	XM_INLINE Point3::Point3( const Point3& p1) noexcept
	{
		vec = p1.vec;
	}

	/// C++11 Move Constructor
	XM_INLINE Point3::Point3( Point3&& other) noexcept
	{
		vec = other.vec;		
	}

	//------------------------------------------------------------
	// assignment
	// -----------------------------------------------------------

	/// assignment operator
	XM_INLINE void XM_CALLCONV  Point3::operator=( const Point3& rhs) noexcept
	{
		vec.x = rhs.vec.x;
		vec.y = rhs.vec.y;
		vec.z = rhs.vec.z;
	}

	/// assign an XMFLOAT3
	XM_INLINE void XM_CALLCONV  Point3::operator=( XMFLOAT3 rhs) noexcept
	{
		vec.x = rhs.x;
		vec.y = rhs.y;
		vec.z = rhs.z;
	}

	/// assign a float
	XM_INLINE Point3 XM_CALLCONV  Point3::operator=( const float rhs) noexcept
	{
		vec.x = vec.y = vec.z = rhs;
		return *this;
	}

	/// assign a Vector3
	XM_INLINE Point3 XM_CALLCONV  Point3::operator=( const Vector3& rhs) noexcept
	{
		vec.x = rhs.GetX();
		vec.y = rhs.GetY();
		vec.z = rhs.GetZ();
		return *this;
	}

	//------------------------------------------------------------
	// Casting-Operatoren
	//------------------------------------------------------------


	/// cast to Vector3
	XM_INLINE Point3::operator Vector3 () noexcept
	{
		return Vector3(*this);
	}

	/// cast to const Vector3
	XM_INLINE Point3::operator const Vector3 () const noexcept
	{
		return Vector3(*this);
	}



	//------------------------------------------------------------
	// C++11 Move
	//------------------------------------------------------------

	/// C++11 Move
	XM_INLINE Point3& XM_CALLCONV  Point3::operator=( Point3&& other) noexcept
	{
		vec = other.vec;
		return *this;
	}

	//------------------------------------------------------------
	// operator
	//------------------------------------------------------------

	/// inplace add
	XM_INLINE Point3& XM_CALLCONV  Point3::operator+=( const Point3 &rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorAdd(v1,v2);
		XMStoreFloat3( &vec, X );
		return *this;
	}

	/// inplace sub
	XM_INLINE Point3& XM_CALLCONV  Point3::operator-=( const Point3 &rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorSubtract(v1,v2);
		XMStoreFloat3( &vec, X );
		return *this;
	}

	/// inplace float multiply
	XM_INLINE Point3& XM_CALLCONV  Point3::operator*=( float s) noexcept
	{	
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR X = XMVectorScale(v1,s);
		XMStoreFloat3( &vec, X );
		return *this;
	} 


	/// muliply by a Point component-wise
	XM_INLINE Point3& XM_CALLCONV  Point3::operator*=( const Point3& rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorMultiply(v1,v2);
		XMStoreFloat3( &vec, X );
		return *this;
	}

	/// inplace float division
	XM_INLINE Point3& XM_CALLCONV  Point3::operator/=( float s) noexcept
	{	
		const float tmp = 1.0f / s + TURBOMATH_EPSILON;
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR X = XMVectorScale(v1,tmp);
		XMStoreFloat3( &vec, X );
		return *this;
	}

	/// muliply by a Point component-wise
	XM_INLINE Point3 XM_CALLCONV  Point3::operator*( const Point3& rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorMultiply(v1,v2);

		Point3 R;
		XMStoreFloat3( &R.vec, X );
		
		return R;
	}


	/// add 2 Points
	XM_INLINE Point3 XM_CALLCONV  Point3::operator+( const Point3 &rhs) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorAdd(v1,v2);

		Point3 R;
		XMStoreFloat3( &R.vec, X );

		return R;
	}

	/// subtract 2 Points
	XM_INLINE Point3 XM_CALLCONV  Point3::operator-( const Point3 &rhs) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorSubtract(v1,v2);

		Point3 R;
		XMStoreFloat3( &R.vec, X );

		return R;
	}

	/// multiply with float
	XM_INLINE Point3 XM_CALLCONV  Point3::operator*( float s) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR X = XMVectorScale(v1,s);

		Point3 R;
		XMStoreFloat3( &R.vec, X );
		
		return R;
	}

	/// equality operator
	XM_INLINE bool XM_CALLCONV  Point3::operator==( const Point3 &rhs) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		return XMVector3Equal( v1, v2 );
	}

	/// inequality operator
	XM_INLINE bool XM_CALLCONV  Point3::operator!=( const Point3 &rhs) const noexcept
	{	
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		return XMVector3NotEqual( v1, v2 );
	}

		
	/// Point-float division
	XM_INLINE Point3 XM_CALLCONV  Point3::operator / ( const float f) const noexcept
	{	
		const float tmp = 1.0f / f + TURBOMATH_EPSILON;
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR X = XMVectorScale(v1,tmp);
		
		Point3 R;
		XMStoreFloat3( &R.vec, X );
		
		return R;
	}

	/// inplace division by Point
	XM_INLINE Point3 XM_CALLCONV  Point3::operator/= (  const Point3& rhs ) noexcept
	{	
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorDivide(v1,v2);
		
		Point3 R;
		XMStoreFloat3( &R.vec, X );
		
		return R;
	}

	//------------------------------------------------------------
	// Set-Functions
	//------------------------------------------------------------

	/// set with Point3
	XM_INLINE void XM_CALLCONV  Point3::Set(const Point3& rhs) noexcept
	{
		vec = rhs.vec;
	}

	/// set content
	XM_INLINE void XM_CALLCONV  Point3::Set( const float x, const float y, const float z) noexcept
	{
		vec.x = x;
		vec.y = y;
		vec.z = z;
	}

	/// Set Content
	XM_INLINE void XM_CALLCONV  Point3::Set( const XMFLOAT3 rhs) noexcept
	{
		vec = rhs;
	}

	/// set the x component
	XM_INLINE void XM_CALLCONV  Point3::SetX( const float x) noexcept
	{
		vec.x = x;
	}
		
	/// set the y component
	XM_INLINE void XM_CALLCONV  Point3::SetY(const float y) noexcept
	{
		vec.y = y;
	}

	/// set the z component
	XM_INLINE void XM_CALLCONV  Point3::SetZ( const float z) noexcept
	{
		vec.z = z;
	}

	/// set to Zero
	XM_INLINE void XM_CALLCONV  Point3::SetZero() noexcept
	{
		vec.x = vec.y = vec.z = 0.0f;
	}

	//------------------------------------------------------------
	// Read / Write Access
	//------------------------------------------------------------

	/// read/write access to x component
	XM_INLINE float& XM_CALLCONV  Point3::X() noexcept
	{
		return vec.x;
	}

	/// read/write access to y component
	XM_INLINE float& XM_CALLCONV  Point3::Y() noexcept
	{
		return vec.y;
	}

	/// read/write access to z component
	XM_INLINE float& XM_CALLCONV  Point3::Z() noexcept
	{
		return vec.z;
	}
	
	/// read-only access to x component
	XM_INLINE const float XM_CALLCONV  Point3::GetX() const noexcept
	{
		return vec.x;
	}
		
	/// read-only access to y component
	XM_INLINE const float XM_CALLCONV  Point3::GetY() const noexcept
	{
		return vec.y;
	}

	/// read-only access to z component
	XM_INLINE const float XM_CALLCONV  Point3::GetZ() const noexcept
	{
		return vec.z;
	}


	//------------------------------------------------------------
	// Get Raw Data (XMFLOAT3)
	//------------------------------------------------------------

	/// Get RawData
	XM_INLINE XMFLOAT3 XM_CALLCONV 	Point3::GetRaw() const noexcept
	{
		return vec;
	}
	
	/// Get RawDataPtr
	XM_INLINE XMFLOAT3* XM_CALLCONV 	Point3::GetRawPtr() noexcept
	{
		return &vec;
	}


}; // end of namespace TurboMath