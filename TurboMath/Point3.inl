
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
	__forceinline Point3::Point3()
	{
		vec.x = vec.y = vec.z = 0.0f;
	}

	/// construct from values, set x and y to v1
	__forceinline Point3::Point3( const float v1)
	{
		vec.x = vec.y = vec.z = v1;
	}

	/// construct from values set x to v1 and y to v2 and z to v3
	__forceinline Point3::Point3( const float v1, const float v2, const float v3)
	{
		vec.x = v1;
		vec.y = v2;
		vec.z = v3;
	}

	/// construct from other Point3
	__forceinline Point3::Point3( const Point3& p1)
	{
		vec = p1.vec;
	}

	/// C++11 Move Constructor
	__forceinline Point3::Point3( Point3&& other)
	{
		vec = other.vec;		
	}

	//------------------------------------------------------------
	// assignment
	// -----------------------------------------------------------

	/// assignment operator
	__forceinline void Point3::operator=( const Point3& rhs)
	{
		vec.x = rhs.vec.x;
		vec.y = rhs.vec.y;
		vec.z = rhs.vec.z;
	}

	/// assign an XMFLOAT3
	__forceinline void Point3::operator=( XMFLOAT3 rhs)
	{
		vec.x = rhs.x;
		vec.y = rhs.y;
		vec.z = rhs.z;
	}

	/// assign a float
	__forceinline Point3 Point3::operator=( const float rhs)
	{
		vec.x = vec.y = vec.z = rhs;
		return *this;
	}

	/// assign a Vector3
	__forceinline Point3 Point3::operator=( const Vector3& rhs)
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
	__forceinline Point3::operator Vector3 ()
	{
		return Vector3(*this);
	}

	/// cast to const Vector3
	__forceinline Point3::operator const Vector3 () const
	{
		return Vector3(*this);
	}



	//------------------------------------------------------------
	// C++11 Move
	//------------------------------------------------------------

	/// C++11 Move
	__forceinline Point3& Point3::operator=( Point3&& other)
	{
		vec = other.vec;
		return *this;
	}

	//------------------------------------------------------------
	// operator
	//------------------------------------------------------------

	/// inplace add
	__forceinline Point3& Point3::operator+=( const Point3 &rhs)
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorAdd(v1,v2);
		XMStoreFloat3( &vec, X );
		return *this;
	}

	/// inplace sub
	__forceinline Point3& Point3::operator-=( const Point3 &rhs)
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorSubtract(v1,v2);
		XMStoreFloat3( &vec, X );
		return *this;
	}

	/// inplace float multiply
	__forceinline Point3& Point3::operator*=( float s)
	{	
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR X = XMVectorScale(v1,s);
		XMStoreFloat3( &vec, X );
		return *this;
	} 


	/// muliply by a Point component-wise
	__forceinline Point3& Point3::operator*=( const Point3& rhs)
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorMultiply(v1,v2);
		XMStoreFloat3( &vec, X );
		return *this;
	}

	/// inplace float division
	__forceinline Point3& Point3::operator/=( float s)
	{	
		const float tmp = 1.0f / s + TURBOMATH_EPSILON;
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR X = XMVectorScale(v1,tmp);
		XMStoreFloat3( &vec, X );
		return *this;
	}

	/// muliply by a Point component-wise
	__forceinline Point3 Point3::operator*( const Point3& rhs)
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorMultiply(v1,v2);

		Point3 R;
		XMStoreFloat3( &R.vec, X );
		
		return R;
	}


	/// add 2 Points
	__forceinline Point3 Point3::operator+( const Point3 &rhs) const
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorAdd(v1,v2);

		Point3 R;
		XMStoreFloat3( &R.vec, X );

		return R;
	}

	/// subtract 2 Points
	__forceinline Point3 Point3::operator-( const Point3 &rhs) const
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		const XMVECTOR X = XMVectorSubtract(v1,v2);

		Point3 R;
		XMStoreFloat3( &R.vec, X );

		return R;
	}

	/// multiply with float
	__forceinline Point3 Point3::operator*( float s) const
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR X = XMVectorScale(v1,s);

		Point3 R;
		XMStoreFloat3( &R.vec, X );
		
		return R;
	}

	/// equality operator
	__forceinline bool Point3::operator==( const Point3 &rhs) const
	{
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		return XMVector3Equal( v1, v2 );
	}

	/// inequality operator
	__forceinline bool Point3::operator!=( const Point3 &rhs) const
	{	
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR v2 = XMLoadFloat3( &rhs.vec );
		return XMVector3NotEqual( v1, v2 );
	}

		
	/// Point-float division
	__forceinline Point3 Point3::operator / ( const float f) const
	{	
		const float tmp = 1.0f / f + TURBOMATH_EPSILON;
		const XMVECTOR v1 = XMLoadFloat3( &vec );
		const XMVECTOR X = XMVectorScale(v1,tmp);
		
		Point3 R;
		XMStoreFloat3( &R.vec, X );
		
		return R;
	}

	/// inplace division by Point
	__forceinline Point3 Point3::operator/= (  const Point3& rhs )
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
	__forceinline void Point3::Set(const Point3& rhs)
	{
		vec = rhs.vec;
	}

	/// set content
	__forceinline void Point3::Set( float x, float y, float z)
	{
		vec.x = x;
		vec.y = y;
		vec.z = z;
	}

	/// Set Content
	__forceinline void Point3::Set( XMFLOAT3 rhs)
	{
		vec = rhs;
	}

	/// set the x component
	__forceinline void Point3::SetX( float x)
	{
		vec.x = x;
	}
		
	/// set the y component
	__forceinline void Point3::SetY( float y)
	{
		vec.y = y;
	}

	/// set the z component
	__forceinline void Point3::SetZ( float z)
	{
		vec.z = z;
	}

	/// set to Zero
	__forceinline void Point3::SetZero()
	{
		vec.x = vec.y = vec.z = 0.0f;
	}

	//------------------------------------------------------------
	// Read / Write Access
	//------------------------------------------------------------

	/// read/write access to x component
	__forceinline float& Point3::X()
	{
		return vec.x;
	}

	/// read/write access to y component
	__forceinline float& Point3::Y()
	{
		return vec.y;
	}

	/// read/write access to z component
	__forceinline float& Point3::Z()
	{
		return vec.z;
	}
	
	/// read-only access to x component
	__forceinline float Point3::GetX() const
	{
		return vec.x;
	}
		
	/// read-only access to y component
	__forceinline float Point3::GetY() const
	{
		return vec.y;
	}

	/// read-only access to z component
	__forceinline float Point3::GetZ() const
	{
		return vec.z;
	}


	//------------------------------------------------------------
	// Get Raw Data (XMFLOAT3)
	//------------------------------------------------------------

	/// Get RawData
	__forceinline XMFLOAT3	Point3::GetRaw() const
	{
		return vec;
	}
	
	/// Get RawDataPtr
	__forceinline XMFLOAT3*	Point3::GetRawPtr()
	{
		return &vec;
	}


}; // end of namespace TurboMath