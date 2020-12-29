
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

	class Point2
	{
	public:
		//------------------------------------------------------------
		// Constructor
		// -----------------------------------------------------------

		/// default constructor, NOTE: setup components to ZERO!
					Point2() noexcept;

		/// construct from values, set x and y to v1
		explicit	Point2( const float v1) noexcept;

		/// construct from values set x to v1 and y to v2
		explicit	Point2( const float v1, const float v2) noexcept;

		/// construct from other Point2
					Point2( const Point2& p1) noexcept;

		/// C++11 Move Constructor
					Point2( Point2&& other) noexcept;

		//------------------------------------------------------------
		// assignment
		// -----------------------------------------------------------

		/// assignment operator
		void  XM_CALLCONV operator=( const Point2& rhs) noexcept;

		/// assign an XMFLOAT2
		void  XM_CALLCONV operator=( XMFLOAT2 rhs) noexcept;

		/// assign a float
		Point2  XM_CALLCONV operator=( const float rhs) noexcept;

		/// assign a Vector2
		Point2  XM_CALLCONV operator=( const Vector2& rhs) noexcept;

		//------------------------------------------------------------
		// Casting-Operatoren
		//------------------------------------------------------------

		/// cast to XMFLOAT2&
		 XM_CALLCONV operator XMFLOAT2& () noexcept			{return vec;}	

		/// cast to const XMFLOAT2&
		 XM_CALLCONV operator const XMFLOAT2& () const noexcept		{return vec;}

		/// cast to XMFLOAT2*
		 XM_CALLCONV operator XMFLOAT2* () noexcept			{return &vec;}

		/// cast to const XMFLOAT2*
		 XM_CALLCONV operator const XMFLOAT2* () const noexcept		{return &vec;}

		/// cast to Vector2
		 XM_CALLCONV operator Vector2 () noexcept;

		/// cast to const Vector2
		 XM_CALLCONV operator const Vector2 () const noexcept;

		/// cast to float*
		 XM_CALLCONV operator float* ()	 noexcept			{return (float*)&vec;}

		/// cast to const float*
		 XM_CALLCONV operator const float* () const	 noexcept	{return (float*)&vec;}

		//------------------------------------------------------------
		// C++11 Move
		//------------------------------------------------------------

		/// C++11 Move
		Point2& XM_CALLCONV  operator=( Point2&& other) noexcept;

		//------------------------------------------------------------
		// operator
		//------------------------------------------------------------

		/// inplace add
		Point2& XM_CALLCONV  operator+=( const Point2 &rhs) noexcept;

		/// inplace sub
		Point2& XM_CALLCONV  operator-=( const Point2 &rhs) noexcept;

		/// inplace float multiply
		Point2& XM_CALLCONV  operator*=( float s) noexcept;

		/// muliply by a Point component-wise
		Point2& XM_CALLCONV  operator*=( const Point2& rhs) noexcept;

		/// inplace float division
		Point2& XM_CALLCONV  operator/=( float s) noexcept;

		/// muliply by a Point component-wise
		Point2 XM_CALLCONV  operator*( const Point2& rhs) noexcept;

		/// add 2 Points
		Point2 XM_CALLCONV  operator+( const Point2 &rhs) const noexcept;

		/// subtract 2 Points
		Point2 XM_CALLCONV  operator-( const Point2 &rhs) const noexcept;

		/// multiply with float
		Point2 XM_CALLCONV  operator*( float s) const noexcept;

		/// equality operator
		bool XM_CALLCONV  operator==( const Point2 &rhs) const noexcept;

		/// inequality operator
		bool XM_CALLCONV  operator!=( const Point2 &rhs) const noexcept;
		
		/// Point-float division
		Point2 XM_CALLCONV  operator / ( const float f) const noexcept;

		/// inplace division by Point
		Point2 XM_CALLCONV  operator/= (  const Point2& rhs ) noexcept;

		//------------------------------------------------------------
		// Set-Functions
		//------------------------------------------------------------

		/// set with Point2
		void XM_CALLCONV   Set(const Point2& rhs) noexcept;

		/// set content
		void XM_CALLCONV  Set( float x, float y) noexcept;

		/// Set Content
		void XM_CALLCONV  Set( XMFLOAT2 rhs) noexcept;

		/// set the x component
		void XM_CALLCONV  SetX( float x) noexcept;
		
		/// set the y component
		void XM_CALLCONV  SetY( float y) noexcept;

		/// set to Zero
		void XM_CALLCONV  SetZero() noexcept;

		//------------------------------------------------------------
		// Read / Write Access
		//------------------------------------------------------------

		/// read/write access to x component
		float& XM_CALLCONV  X() noexcept;

		/// read/write access to y component
		float& XM_CALLCONV  Y() noexcept;
	
		/// read-only access to x component
		const float XM_CALLCONV  GetX() const noexcept;
		
		/// read-only access to y component
		const float XM_CALLCONV  GetY() const noexcept;


		//------------------------------------------------------------
		// Get Raw Data (XMFLOAT2)
		//------------------------------------------------------------

		/// Get RawData
		XMFLOAT2 XM_CALLCONV 	GetRaw() const noexcept;
	
		/// Get RawDataPtr
		XMFLOAT2* XM_CALLCONV 	GetRawPtr() noexcept;


	protected:
		XMFLOAT2	vec;
	};

}; // namespace TurboMath



#endif