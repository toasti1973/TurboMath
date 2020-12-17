
// -------------------------------------------------------------------
// File			:	Point4
//
// Project		:	TurboMath
//
// Description	:	Class for 4D-Point
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


#ifndef _TURBOMATH_POINT4_H_
#define _TURBOMATH_POINT4_H_


namespace TurboMath
{

	class Point4
	{
	public:
		//------------------------------------------------------------
		// Constructor
		// -----------------------------------------------------------

		/// default constructor, NOTE: setup components to ZERO!
					Point4();

		/// construct from values, set x and y and z to v1
		explicit	Point4( const float v1);

		/// construct from values set x to v1 and y to v2 and z to v3 and w to v4
		explicit	Point4( const float v1, const float v2, const float v3, const float v4);

		/// construct from other Point4
					Point4( const Point4& p1);

		/// C++11 Move Constructor
					Point4( Point4&& other);

		//------------------------------------------------------------
		// assignment
		// -----------------------------------------------------------

		/// assignment operator
		void operator=( const Point4& rhs);

		/// assign an XMFLOAT4
		void operator=( XMFLOAT4 rhs);

		/// assign a float
		Point4 operator=( const float rhs);

		/// assign a Vector4
		Point4 operator=( const Vector4& rhs);

		//------------------------------------------------------------
		// Casting-Operatoren
		//------------------------------------------------------------

		/// cast to XMFLOAT4&
		operator XMFLOAT4& ();	

		/// cast to const XMFLOAT4&
		operator const XMFLOAT4& () const;

		/// cast to XMFLOAT4*
		operator XMFLOAT4* ();

		/// cast to const XMFLOAT4*
		operator const XMFLOAT4* () const;

		/// cast to Vector4
		operator Vector4 ();

		/// cast to const Vector4
		operator const Vector4 () const;

		/// cast to float*
		operator float* ()					{return (float*)&vec;}

		/// cast to const float*
		operator const float* () const		{return (float*)&vec;}

		//------------------------------------------------------------
		// C++11 Move
		//------------------------------------------------------------

		/// C++11 Move
		Point4& operator=( Point4&& other);

		//------------------------------------------------------------
		// operator
		//------------------------------------------------------------

		/// inplace add
		Point4& operator+=( const Point4 &rhs);

		/// inplace sub
		Point4& operator-=( const Point4 &rhs);

		/// inplace float multiply
		Point4& operator*=( float s);

		/// muliply by a Point component-wise
		Point4& operator*=( const Point4& rhs);

		/// muliply by a Point component-wise
		Point4 operator*( const Point4& rhs);

		/// add 2 Points
		Point4 operator+( const Point4 &rhs) const;

		/// subtract 2 Points
		Point4 operator-( const Point4 &rhs) const;

		/// multiply with float
		Point4 operator*( float s) const;

		/// equality operator
		bool operator==( const Point4 &rhs) const;

		/// inequality operator
		bool operator!=( const Point4 &rhs) const;
		
		/// Point-float division
		Point4 operator / ( const float f) const;

		/// inplace division by Scalar
		Point4& operator/= (  const float fScalar );

		/// inplace division by Point
		Point4 operator/= (  const Point4& rhs );

		//------------------------------------------------------------
		// Set-Functions
		//------------------------------------------------------------

		/// set with Point4
		void Set(const Point4& rhs);

		/// set content
		void Set( float x, float y, float z, float w);

		/// Set Content
		void Set( XMFLOAT4 rhs);

		/// set the x component
		void SetX( float x);
		
		/// set the y component
		void SetY( float y);

		/// set the z component
		void SetZ( float z);

		/// set the w component
		void SetW( float w);

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

		/// read/write access to w component
		float& W();
	
		/// read-only access to x component
		float GetX() const;
		
		/// read-only access to y component
		float GetY() const;

		/// read-only access to z component
		float GetZ() const;

		/// read-only access to w component
		float GetW() const;

		//------------------------------------------------------------
		// Get Raw Data (XMFLOAT4)
		//------------------------------------------------------------

		/// Get RawData
		XMFLOAT4	GetRaw() const;
	
		/// Get RawDataPtr
		XMFLOAT4*	GetRawPtr();


	protected:
		XMFLOAT4	vec;
	};

}; // namespace TurboMath



#endif