
// -------------------------------------------------------------------
// File			:	Point2
//
// Project		:	TurboMath
//
// Description	:	Class for 2D-Point
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


#ifndef _TURBOMATH_POINT2_H_
#define _TURBOMATH_POINT2_H_


namespace TurboMath
{

	CACHE_ALIGN(16) class Point2
	{
	public:
		//------------------------------------------------------------
		// Constructor
		// -----------------------------------------------------------

		/// default constructor, NOTE: setup components to ZERO!
					Point2();

		/// construct from values, set x and y to v1
		explicit	Point2( const float v1);

		/// construct from values set x to v1 and y to v2
		explicit	Point2( const float v1, const float v2);

		/// construct from other Point2
					Point2( const Point2& p1);

		/// C++11 Move Constructor
					Point2( Point2&& other);

		//------------------------------------------------------------
		// assignment
		// -----------------------------------------------------------

		/// assignment operator
		void operator=( const Point2& rhs);

		/// assign an XMFLOAT2
		void operator=( XMFLOAT2 rhs);

		/// assign a float
		Point2 operator=( const float rhs);

		/// assign a Vector2
		Point2 operator=( const Vector2& rhs);

		//------------------------------------------------------------
		// Casting-Operatoren
		//------------------------------------------------------------

		/// cast to XMFLOAT2&
		operator XMFLOAT2& ()		{return vec;}	

		/// cast to const XMFLOAT2&
		operator const XMFLOAT2& () const	{return vec;}

		/// cast to XMFLOAT2*
		operator XMFLOAT2* ()		{return &vec;}

		/// cast to const XMFLOAT2*
		operator const XMFLOAT2* () const	{return &vec;}

		/// cast to Vector2
		operator Vector2 ();

		/// cast to const Vector2
		operator const Vector2 () const;

		/// cast to float*
		operator float* ()					{return (float*)&vec;}

		/// cast to const float*
		operator const float* () const		{return (float*)&vec;}

		//------------------------------------------------------------
		// C++11 Move
		//------------------------------------------------------------

		/// C++11 Move
		Point2& operator=( Point2&& other);

		//------------------------------------------------------------
		// operator
		//------------------------------------------------------------

		/// inplace add
		Point2& operator+=( const Point2 &rhs);

		/// inplace sub
		Point2& operator-=( const Point2 &rhs);

		/// inplace float multiply
		Point2& operator*=( float s);

		/// muliply by a Point component-wise
		Point2& operator*=( const Point2& rhs);

		/// inplace float division
		Point2& operator/=( float s);

		/// muliply by a Point component-wise
		Point2 operator*( const Point2& rhs);

		/// add 2 Points
		Point2 operator+( const Point2 &rhs) const;

		/// subtract 2 Points
		Point2 operator-( const Point2 &rhs) const;

		/// multiply with float
		Point2 operator*( float s) const;

		/// equality operator
		bool operator==( const Point2 &rhs) const;

		/// inequality operator
		bool operator!=( const Point2 &rhs) const;
		
		/// Point-float division
		Point2 operator / ( const float f) const;

		/// inplace division by Point
		Point2 operator/= (  const Point2& rhs );

		//------------------------------------------------------------
		// Set-Functions
		//------------------------------------------------------------

		/// set with Point2
		const void Set(const Point2& rhs) noexcept;

		/// set content
		void Set( float x, float y) noexcept;

		/// Set Content
		void Set( XMFLOAT2 rhs) noexcept;

		/// set the x component
		void SetX( float x) noexcept;
		
		/// set the y component
		void SetY( float y) noexcept;

		/// set to Zero
		void SetZero() noexcept;

		//------------------------------------------------------------
		// Read / Write Access
		//------------------------------------------------------------

		/// read/write access to x component
		float& X();

		/// read/write access to y component
		float& Y();
	
		/// read-only access to x component
		float GetX() const;
		
		/// read-only access to y component
		float GetY() const;


		//------------------------------------------------------------
		// Get Raw Data (XMFLOAT2)
		//------------------------------------------------------------

		/// Get RawData
		XMFLOAT2	GetRaw() const;
	
		/// Get RawDataPtr
		XMFLOAT2*	GetRawPtr();


	protected:
		XMFLOAT2	vec;
	};

}; // namespace TurboMath



#endif