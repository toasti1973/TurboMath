
// -------------------------------------------------------------------
// File			:	Point2.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for 2D-Point-CLass
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

	//------------------------------------------------------------
	// Constructor
	// -----------------------------------------------------------

	/// default constructor, NOTE: setup components to ZERO!
	XM_INLINE Point2::Point2() noexcept
	{
		vec.x = vec.y = 0.0f;
	}

	/// construct from values, set x and y to v1
	XM_INLINE Point2::Point2( const float v1) noexcept
	{
		vec.x = vec.y = v1;
	}

	/// construct from values set x to v1 and y to v2
	XM_INLINE Point2::Point2( const float v1, const float v2) noexcept
	{
		vec.x = v1;
		vec.y = v2;
	}

	/// construct from other Point2
	XM_INLINE Point2::Point2( const Point2& p1) noexcept
	{
		vec = p1.vec;
	}

	/// C++11 Move Constructor
	XM_INLINE Point2::Point2( Point2&& other) noexcept
	{
		vec = other.vec;		
	}

	//------------------------------------------------------------
	// assignment
	// -----------------------------------------------------------

	/// assignment operator
	XM_INLINE void  XM_CALLCONV Point2::operator=( const Point2& rhs) noexcept
	{
		vec.x = rhs.vec.x;
		vec.y = rhs.vec.y;
	}

	/// assign an XMFLOAT2
	XM_INLINE void  XM_CALLCONV Point2::operator=( XMFLOAT2 rhs) noexcept
	{
		vec.x = rhs.x;
		vec.y = rhs.y;
	}

	/// assign a float
	XM_INLINE Point2  XM_CALLCONV Point2::operator=( const float rhs) noexcept
	{
		vec.x = vec.y = rhs;
		return *this;
	}

	/// assign a Vector2
	XM_INLINE Point2  XM_CALLCONV Point2::operator=( const Vector2& rhs) noexcept
	{
		vec.x = rhs.GetX();
		vec.y = rhs.GetY();
		return *this;
	}

	//------------------------------------------------------------
	// Casting-Operatoren
	//------------------------------------------------------------


	/// cast to Vector2
	XM_INLINE Point2::operator Vector2 () noexcept
	{
		return Vector2(*this);
	}

	/// cast to const Vector2
	XM_INLINE Point2::operator const Vector2 () const noexcept
	{
		return Vector2(*this);
	}



	//------------------------------------------------------------
	// C++11 Move
	//------------------------------------------------------------

	/// C++11 Move
	XM_INLINE Point2&  XM_CALLCONV  Point2::operator=( Point2&& other) noexcept
	{
		vec = other.vec;
		return *this;
	}

	//------------------------------------------------------------
	// operator
	//------------------------------------------------------------

	/// inplace add
	XM_INLINE Point2&  XM_CALLCONV Point2::operator+=( const Point2 &rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR v2 = XMLoadFloat2( &rhs.vec );
		const XMVECTOR X = XMVectorAdd(v1,v2);
		XMStoreFloat2( &vec, X );
		return *this;
	}

	/// inplace sub
	XM_INLINE Point2&  XM_CALLCONV Point2::operator-=( const Point2 &rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR v2 = XMLoadFloat2( &rhs.vec );
		const XMVECTOR X = XMVectorSubtract(v1,v2);
		XMStoreFloat2( &vec, X );
		return *this;
	}

	/// inplace float multiply
	XM_INLINE Point2&  XM_CALLCONV Point2::operator*=( float s) noexcept
	{	
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR X = XMVectorScale(v1,s);
		XMStoreFloat2( &vec, X );
		return *this;
	} 


	/// muliply by a Point component-wise
	XM_INLINE Point2&  XM_CALLCONV Point2::operator*=( const Point2& rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR v2 = XMLoadFloat2( &rhs.vec );
		const XMVECTOR X = XMVectorMultiply(v1,v2);
		XMStoreFloat2( &vec, X );
		return *this;
	}

	/// inplace float division
	XM_INLINE Point2&  XM_CALLCONV Point2::operator/=( float s) noexcept
	{	
		const float tmp = 1.0f / s + TURBOMATH_EPSILON;
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR X = XMVectorScale(v1,tmp);
		XMStoreFloat2( &vec, X );
		return *this;
	}

	/// muliply by a Point component-wise
	XM_INLINE Point2  XM_CALLCONV Point2::operator*( const Point2& rhs) noexcept
	{
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR v2 = XMLoadFloat2( &rhs.vec );
		const XMVECTOR X = XMVectorMultiply(v1,v2);

		Point2 R;
		XMStoreFloat2( &R.vec, X );
		
		return R;
	}


	/// add 2 Points
	XM_INLINE Point2  XM_CALLCONV Point2::operator+( const Point2 &rhs) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR v2 = XMLoadFloat2( &rhs.vec );
		const XMVECTOR X = XMVectorAdd(v1,v2);

		Point2 R;
		XMStoreFloat2( &R.vec, X );

		return R;
	}

	/// subtract 2 Points
	XM_INLINE Point2  XM_CALLCONV Point2::operator-( const Point2 &rhs) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR v2 = XMLoadFloat2( &rhs.vec );
		const XMVECTOR X = XMVectorSubtract(v1,v2);

		Point2 R;
		XMStoreFloat2( &R.vec, X );

		return R;
	}

	/// multiply with float
	XM_INLINE Point2  XM_CALLCONV Point2::operator*( float s) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR X = XMVectorScale(v1,s);

		Point2 R;
		XMStoreFloat2( &R.vec, X );
		
		return R;
	}

	/// equality operator
	XM_INLINE bool  XM_CALLCONV Point2::operator==( const Point2 &rhs) const noexcept
	{
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR v2 = XMLoadFloat2( &rhs.vec );
		return XMVector2Equal( v1, v2 );
	}

	/// inequality operator
	XM_INLINE bool  XM_CALLCONV Point2::operator!=( const Point2 &rhs) const noexcept
	{	
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR v2 = XMLoadFloat2( &rhs.vec );
		return XMVector2NotEqual( v1, v2 );
	}

		
	/// Point-float division
	XM_INLINE Point2  XM_CALLCONV Point2::operator / ( const float f) const noexcept
	{	
		const float tmp = 1.0f / f + TURBOMATH_EPSILON;
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR X = XMVectorScale(v1,tmp);
		
		Point2 R;
		XMStoreFloat2( &R.vec, X );
		
		return R;
	}

	/// inplace division by Point
	XM_INLINE Point2  XM_CALLCONV Point2::operator/= (  const Point2& rhs ) noexcept
	{	
		const XMVECTOR v1 = XMLoadFloat2( &vec );
		const XMVECTOR v2 = XMLoadFloat2( &rhs.vec );
		const XMVECTOR X = XMVectorDivide(v1,v2);
		
		Point2 R;
		XMStoreFloat2( &R.vec, X );
		
		return R;
	}

	//------------------------------------------------------------
	// Set-Functions
	//------------------------------------------------------------

	/// set with Point2
	XM_INLINE void XM_CALLCONV  Point2::Set(const Point2& rhs) noexcept
	{
		vec = rhs.vec;
	}

	/// set content
	XM_INLINE void XM_CALLCONV  Point2::Set( float x, float y) noexcept
	{
		vec.x = x;
		vec.y = y;
	}

	/// Set Content
	XM_INLINE void XM_CALLCONV  Point2::Set( XMFLOAT2 rhs) noexcept
	{
		vec = rhs;
	}

	/// set the x component
	XM_INLINE void  XM_CALLCONV Point2::SetX( float x) noexcept
	{
		vec.x = x;
	}
		
	/// set the y component
	XM_INLINE void XM_CALLCONV  Point2::SetY( float y) noexcept
	{
		vec.y = y;
	}

	/// set to Zero
	XM_INLINE void XM_CALLCONV  Point2::SetZero() noexcept
	{
		vec.x = vec.y = 0.0f;
	}

	//------------------------------------------------------------
	// Read / Write Access
	//------------------------------------------------------------

	/// read/write access to x component
	XM_INLINE float&  XM_CALLCONV Point2::X() noexcept
	{
		return vec.x;
	}

	/// read/write access to y component
	XM_INLINE float&  XM_CALLCONV Point2::Y() noexcept
	{
		return vec.y;
	}
	
	/// read-only access to x component
	XM_INLINE const float XM_CALLCONV  Point2::GetX() const noexcept
	{
		return vec.x;
	}
		
	/// read-only access to y component
	XM_INLINE const float XM_CALLCONV  Point2::GetY() const noexcept
	{
		return vec.y;
	}


	//------------------------------------------------------------
	// Get Raw Data (XMFLOAT2)
	//------------------------------------------------------------

	/// Get RawData
	XM_INLINE XMFLOAT2 XM_CALLCONV 	Point2::GetRaw() const noexcept
	{
		return vec;
	}
	
	/// Get RawDataPtr
	XM_INLINE XMFLOAT2* XM_CALLCONV 	Point2::GetRawPtr() noexcept
	{
		return &vec;
	}


}; // end of namespace TurboMath