
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
				Point3() noexcept;

		/// construct from values, set x and y and z to v1
		explicit	Point3( const float v1) noexcept;

		/// construct from values set x to v1 and y to v2 and z to v3
		explicit	Point3( const float v1, const float v2, const float v3) noexcept;

		/// construct from other Point3
				Point3( const Point3& p1) noexcept;

		/// C++11 Move Constructor
				Point3( Point3&& other) noexcept;

		//------------------------------------------------------------
		// assignment
		// -----------------------------------------------------------

		/// assignment operator
		void XM_CALLCONV  operator=( const Point3& rhs) noexcept;

		/// assign an XMFLOAT3
		void XM_CALLCONV  operator=( XMFLOAT3 rhs) noexcept;

		/// assign a float
		Point3 XM_CALLCONV  operator=( const float rhs) noexcept;

		/// assign a Vector3
		Point3 XM_CALLCONV  operator=( const Vector3& rhs) noexcept;

		//------------------------------------------------------------
		// Casting-Operatoren
		//------------------------------------------------------------

		/// cast to XMFLOAT3&
		 XM_CALLCONV operator XMFLOAT3& () noexcept;	

		/// cast to const XMFLOAT3&
		 XM_CALLCONV operator const XMFLOAT3& () const noexcept;

		/// cast to XMFLOAT3*
		 XM_CALLCONV operator XMFLOAT3* () noexcept;

		/// cast to const XMFLOAT3*
		 XM_CALLCONV operator const XMFLOAT3* () const noexcept;

		/// cast to Vector3
		 XM_CALLCONV operator Vector3 () noexcept;

		/// cast to const Vector3
		 XM_CALLCONV operator const Vector3 () const noexcept;

		/// cast to float*
		 XM_CALLCONV operator float* () noexcept		{return (float*)&vec;}

		/// cast to const float*
		 XM_CALLCONV operator const float* () const noexcept	{return (float*)&vec;}

		//------------------------------------------------------------
		// C++11 Move
		//------------------------------------------------------------

		/// C++11 Move
		Point3& XM_CALLCONV  operator=( Point3&& other) noexcept;

		//------------------------------------------------------------
		// operator
		//------------------------------------------------------------

		/// inplace add
		Point3& XM_CALLCONV  operator+=( const Point3 &rhs) noexcept;

		/// inplace sub
		Point3& XM_CALLCONV  operator-=( const Point3 &rhs) noexcept;

		/// inplace float multiply
		Point3& XM_CALLCONV  operator*=( float s) noexcept;

		/// muliply by a Point component-wise
		Point3& XM_CALLCONV operator*=( const Point3& rhs) noexcept;

		/// muliply by a Point component-wise
		Point3 XM_CALLCONV  operator*( const Point3& rhs) noexcept;

		/// add 2 Points
		Point3 XM_CALLCONV  operator+( const Point3 &rhs) const noexcept;

		/// subtract 2 Points
		Point3 XM_CALLCONV  operator-( const Point3 &rhs) const noexcept;

		/// multiply with float
		Point3 XM_CALLCONV  operator*( float s) const noexcept;

		/// equality operator
		bool XM_CALLCONV  operator==( const Point3 &rhs) const noexcept;

		/// inequality operator
		bool XM_CALLCONV  operator!=( const Point3 &rhs) const noexcept;
		
		/// Point-float division
		Point3 XM_CALLCONV  operator / ( const float f) const noexcept;

		/// inplace division by Scalar
		Point3&  XM_CALLCONV operator/= (  const float fScalar ) noexcept;

		/// inplace division by Point
		Point3 XM_CALLCONV  operator/= (  const Point3& rhs ) noexcept;

		//------------------------------------------------------------
		// Set-Functions
		//------------------------------------------------------------

		/// set with Point3
		void XM_CALLCONV  Set(const Point3& rhs) noexcept;

		/// set content
		void XM_CALLCONV  Set( const float x, const float y, const float z) noexcept;

		/// Set Content
		void XM_CALLCONV  Set( const XMFLOAT3 rhs) noexcept;

		/// set the x component
		void XM_CALLCONV  SetX( const float x) noexcept;
		
		/// set the y component
		void XM_CALLCONV  SetY( const float y) noexcept;

		/// set the z component
		void XM_CALLCONV  SetZ( const float z) noexcept;

		/// set to Zero
		void XM_CALLCONV  SetZero() noexcept;

		//------------------------------------------------------------
		// Read / Write Access
		//------------------------------------------------------------

		/// read/write access to x component
		float& XM_CALLCONV  X() noexcept;

		/// read/write access to y component
		float& XM_CALLCONV  Y() noexcept;

		/// read/write access to z component
		float& XM_CALLCONV  Z() noexcept;
	
		/// read-only access to x component
		const float XM_CALLCONV  GetX() const noexcept;
		
		/// read-only access to y component
		const float XM_CALLCONV  GetY() const noexcept;

		/// read-only access to z component
		const float XM_CALLCONV  GetZ() const noexcept;

		//------------------------------------------------------------
		// Get Raw Data (XMFLOAT3)
		//------------------------------------------------------------

		/// Get RawData
		XMFLOAT3 XM_CALLCONV 	GetRaw() const noexcept;
	
		/// Get RawDataPtr
		XMFLOAT3* XM_CALLCONV 	GetRawPtr() noexcept;


	protected:
		XMFLOAT3	vec;
	};

}; // namespace TurboMath



#endif