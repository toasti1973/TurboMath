
// -------------------------------------------------------------------
// File			:	Point3
//
// Project		:	TurboMath
//
// Description	:	Class for 3D-Point
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


#ifndef _TURBOMATH_POINT3_H_
#define _TURBOMATH_POINT3_H_


namespace TurboMath
{

	class Point3
	{
	public:
		//------------------------------------------------------------
		// Constructor
		// -----------------------------------------------------------

		/// default constructor, NOTE: setup components to ZERO!
					Point3();

		/// construct from values, set x and y and z to v1
		explicit	Point3( const float v1);

		/// construct from values set x to v1 and y to v2 and z to v3
		explicit	Point3( const float v1, const float v2, const float v3);

		/// construct from other Point3
					Point3( const Point3& p1);

		/// C++11 Move Constructor
					Point3( Point3&& other);

		//------------------------------------------------------------
		// assignment
		// -----------------------------------------------------------

		/// assignment operator
		void operator=( const Point3& rhs);

		/// assign an XMFLOAT3
		void operator=( XMFLOAT3 rhs);

		/// assign a float
		Point3 operator=( const float rhs);

		/// assign a Vector3
		Point3 operator=( const Vector3& rhs);

		//------------------------------------------------------------
		// Casting-Operatoren
		//------------------------------------------------------------

		/// cast to XMFLOAT3&
		operator XMFLOAT3& ();	

		/// cast to const XMFLOAT3&
		operator const XMFLOAT3& () const;

		/// cast to XMFLOAT3*
		operator XMFLOAT3* ();

		/// cast to const XMFLOAT3*
		operator const XMFLOAT3* () const;

		/// cast to Vector3
		operator Vector3 ();

		/// cast to const Vector3
		operator const Vector3 () const;

		/// cast to float*
		operator float* ()					{return (float*)&vec;}

		/// cast to const float*
		operator const float* () const		{return (float*)&vec;}

		//------------------------------------------------------------
		// C++11 Move
		//------------------------------------------------------------

		/// C++11 Move
		Point3& operator=( Point3&& other);

		//------------------------------------------------------------
		// operator
		//------------------------------------------------------------

		/// inplace add
		Point3& operator+=( const Point3 &rhs);

		/// inplace sub
		Point3& operator-=( const Point3 &rhs);

		/// inplace float multiply
		Point3& operator*=( float s);

		/// muliply by a Point component-wise
		Point3& operator*=( const Point3& rhs);

		/// muliply by a Point component-wise
		Point3 operator*( const Point3& rhs);

		/// add 2 Points
		Point3 operator+( const Point3 &rhs) const;

		/// subtract 2 Points
		Point3 operator-( const Point3 &rhs) const;

		/// multiply with float
		Point3 operator*( float s) const;

		/// equality operator
		bool operator==( const Point3 &rhs) const;

		/// inequality operator
		bool operator!=( const Point3 &rhs) const;
		
		/// Point-float division
		Point3 operator / ( const float f) const;

		/// inplace division by Scalar
		Point3& operator/= (  const float fScalar );

		/// inplace division by Point
		Point3 operator/= (  const Point3& rhs );

		//------------------------------------------------------------
		// Set-Functions
		//------------------------------------------------------------

		/// set with Point3
		void Set(const Point3& rhs);

		/// set content
		void Set( float x, float y, float z);

		/// Set Content
		void Set( XMFLOAT3 rhs);

		/// set the x component
		void SetX( float x);
		
		/// set the y component
		void SetY( float y);

		/// set the z component
		void SetZ( float z);

		/// set to Zero
		void SetZero();

		//------------------------------------------------------------
		// Read / Write Access
		//------------------------------------------------------------

		/// read/write access to x component
		float& X();

		/// read/write access to y component
		float& Y();

		/// read/write access to z component
		float& Z();
	
		/// read-only access to x component
		float GetX() const;
		
		/// read-only access to y component
		float GetY() const;

		/// read-only access to z component
		float GetZ() const;

		//------------------------------------------------------------
		// Get Raw Data (XMFLOAT3)
		//------------------------------------------------------------

		/// Get RawData
		XMFLOAT3	GetRaw() const;
	
		/// Get RawDataPtr
		XMFLOAT3*	GetRawPtr();


	protected:
		XMFLOAT3	vec;
	};

}; // namespace TurboMath



#endif