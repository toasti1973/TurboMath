
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
	__forceinline Point4::Point4()
	{
		vec.x = vec.y = vec.z = vec.w = 0.0f;
	}

	/// construct from values, set x and y to v1
	__forceinline Point4::Point4( const float v1)
	{
		vec.x = vec.y = vec.z = vec.w = v1;
	}

	/// construct from values set x to v1 and y to v2 and z to v3
	__forceinline Point4::Point4( const float v1, const float v2, const float v3, const float v4)
	{
		vec.x = v1;
		vec.y = v2;
		vec.z = v3;
		vec.w = v4;
	}

	/// construct from other Point4
	__forceinline Point4::Point4( const Point4& p1)
	{
		vec = p1.vec;
	}

	/// C++11 Move Constructor
	__forceinline Point4::Point4( Point4&& other)
	{
		vec = other.vec;		
	}

	//------------------------------------------------------------
	// assignment
	// -----------------------------------------------------------

	/// assignment operator
	__forceinline void Point4::operator=( const Point4& rhs)
	{
		vec.x = rhs.vec.x;
		vec.y = rhs.vec.y;
		vec.z = rhs.vec.z;
		vec.w = rhs.vec.w;
	}

	/// assign an XMFLOAT4
	__forceinline void Point4::operator=( XMFLOAT4 rhs)
	{
		vec.x = rhs.x;
		vec.y = rhs.y;
		vec.z = rhs.z;
		vec.w = rhs.w;
	}

	/// assign a float
	__forceinline Point4 Point4::operator=( const float rhs)
	{
		vec.x = vec.y = vec.z = vec.w = rhs;
		return *this;
	}

	/// assign a Vector4
	__forceinline Point4 Point4::operator=( const Vector4& rhs)
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
	__forceinline Point4::operator Vector4 ()
	{
		return Vector4(*this);
	}

	/// cast to const Vector4
	__forceinline Point4::operator const Vector4 () const
	{
		return Vector4(*this);
	}



	//------------------------------------------------------------
	// C++11 Move
	//------------------------------------------------------------

	/// C++11 Move
	__forceinline Point4& Point4::operator=( Point4&& other)
	{
		vec = other.vec;
		return *this;
	}

	//------------------------------------------------------------
	// operator
	//------------------------------------------------------------

	/// inplace add
	__forceinline Point4& Point4::operator+=( const Point4 &rhs)
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorAdd(v1,v2);
		XMStoreFloat4( &vec, X );
		return *this;
	}

	/// inplace sub
	__forceinline Point4& Point4::operator-=( const Point4 &rhs)
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorSubtract(v1,v2);
		XMStoreFloat4( &vec, X );
		return *this;
	}

	/// inplace float multiply
	__forceinline Point4& Point4::operator*=( float s)
	{	
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR X = XMVectorScale(v1,s);
		XMStoreFloat4( &vec, X );
		return *this;
	} 


	/// muliply by a Point component-wise
	__forceinline Point4& Point4::operator*=( const Point4& rhs)
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorMultiply(v1,v2);
		XMStoreFloat4( &vec, X );
		return *this;
	}

	/// inplace float division
	__forceinline Point4& Point4::operator/=( float s)
	{	
		const float tmp = 1.0f / s + TURBOMATH_EPSILON;
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR X = XMVectorScale(v1,tmp);
		XMStoreFloat4( &vec, X );
		return *this;
	}

	/// muliply by a Point component-wise
	__forceinline Point4 Point4::operator*( const Point4& rhs)
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorMultiply(v1,v2);

		Point4 R;
		XMStoreFloat4( &R.vec, X );
		
		return R;
	}


	/// add 2 Points
	__forceinline Point4 Point4::operator+( const Point4 &rhs) const
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorAdd(v1,v2);

		Point4 R;
		XMStoreFloat4( &R.vec, X );

		return R;
	}

	/// subtract 2 Points
	__forceinline Point4 Point4::operator-( const Point4 &rhs) const
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		const XMVECTOR X = XMVectorSubtract(v1,v2);

		Point4 R;
		XMStoreFloat4( &R.vec, X );

		return R;
	}

	/// multiply with float
	__forceinline Point4 Point4::operator*( float s) const
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR X = XMVectorScale(v1,s);

		Point4 R;
		XMStoreFloat4( &R.vec, X );
		
		return R;
	}

	/// equality operator
	__forceinline bool Point4::operator==( const Point4 &rhs) const
	{
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		return XMVector4Equal( v1, v2 );
	}

	/// inequality operator
	__forceinline bool Point4::operator!=( const Point4 &rhs) const
	{	
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR v2 = XMLoadFloat4( &rhs.vec );
		return XMVector4NotEqual( v1, v2 );
	}

		
	/// Point-float division
	__forceinline Point4 Point4::operator / ( const float f) const
	{	
		const float tmp = 1.0f / f + TURBOMATH_EPSILON;
		const XMVECTOR v1 = XMLoadFloat4( &vec );
		const XMVECTOR X = XMVectorScale(v1,tmp);
		
		Point4 R;
		XMStoreFloat4( &R.vec, X );
		
		return R;
	}

	/// inplace division by Point
	__forceinline Point4 Point4::operator/= (  const Point4& rhs )
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
	__forceinline void Point4::Set(const Point4& rhs)
	{
		vec = rhs.vec;
	}

	/// set content
	__forceinline void Point4::Set( float x, float y, float z, float w)
	{
		vec.x = x;
		vec.y = y;
		vec.z = z;
		vec.w = w;
	}

	/// Set Content
	__forceinline void Point4::Set( XMFLOAT4 rhs)
	{
		vec = rhs;
	}

	/// set the x component
	__forceinline void Point4::SetX( float x)
	{
		vec.x = x;
	}
		
	/// set the y component
	__forceinline void Point4::SetY( float y)
	{
		vec.y = y;
	}

	/// set the z component
	__forceinline void Point4::SetZ( float z)
	{
		vec.z = z;
	}

	/// set the w component
	__forceinline void Point4::SetW( float w)
	{
		vec.w = w;
	}

	/// set to Zero
	__forceinline void Point4::SetZero()
	{
		vec.x = vec.y = vec.z = vec.w = 0.0f;
	}

	//------------------------------------------------------------
	// Read / Write Access
	//------------------------------------------------------------

	/// read/write access to x component
	__forceinline float& Point4::X()
	{
		return vec.x;
	}

	/// read/write access to y component
	__forceinline float& Point4::Y()
	{
		return vec.y;
	}

	/// read/write access to z component
	__forceinline float& Point4::Z()
	{
		return vec.z;
	}
	
	/// read/write access to w component
	__forceinline float& Point4::W()
	{
		return vec.w;
	}

	/// read-only access to x component
	__forceinline float Point4::GetX() const
	{
		return vec.x;
	}
		
	/// read-only access to y component
	__forceinline float Point4::GetY() const
	{
		return vec.y;
	}

	/// read-only access to z component
	__forceinline float Point4::GetZ() const
	{
		return vec.z;
	}

	/// read-only access to w component
	__forceinline float Point4::GetW() const
	{
		return vec.w;
	}

	//------------------------------------------------------------
	// Get Raw Data (XMFLOAT4)
	//------------------------------------------------------------

	/// Get RawData
	__forceinline XMFLOAT4	Point4::GetRaw() const
	{
		return vec;
	}
	
	/// Get RawDataPtr
	__forceinline XMFLOAT4*	Point4::GetRawPtr()
	{
		return &vec;
	}


}; // end of namespace TurboMath