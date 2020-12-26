
// -------------------------------------------------------------------
// File			:	Vector3
//
// Project		:	TurboMath
//
// Description	:	Class for 2D-Vector
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

#ifndef _TURBOMATH_VECTOR3_H_
#define _TURBOMATH_VECTOR3_H_

namespace TurboMath
{
	CACHE_ALIGN(16) class Vector3
	{
	public:

		//------------------------------------------------------
		// Construktor
		//------------------------------------------------------

		/// default constructor, NOTE: does NOT setup components!
		Vector3();
		
		/// construct from values
		explicit Vector3( float x, float y, float z);
		
		/// construct from XMVECTOR
			 Vector3( XMVECTOR rhs);
		
		/// construct from Vector3
			 Vector3( const Vector3& rhs);

		/// construct from Point3
		explicit Vector3( const Point3& rhs);
		
		/// construct from Vector4
		explicit Vector3( const Vector4& rhs);
		
		/// C++11 Move Constructor
		Vector3( Vector3&& other) noexcept;

		//------------------------------------------------------
		// operator
		//------------------------------------------------------

		/// assignment operator
		void XM_CALLCONV operator=( const Vector3 &rhs);

		/// flip sign
		Vector3 XM_CALLCONV operator-() const noexcept;

		/// inplace add
		void XM_CALLCONV operator+=( const Vector3 &rhs) noexcept;

		/// inplace sub
		void XM_CALLCONV operator-=( const Vector3 &rhs) noexcept;

		/// inplace float multiply
		void XM_CALLCONV operator*=( float s) noexcept;

		/// muliply by a vector component-wise
		void XM_CALLCONV operator*=( const Vector3& rhs) noexcept;

		/// muliply by a vector component-wise
		Vector3  XM_CALLCONV operator*( const Vector3& rhs) noexcept;

		/// add 2 vectors
		Vector3 XM_CALLCONV operator+( const Vector3 &rhs) const noexcept;

		/// subtract 2 vectors
		Vector3 XM_CALLCONV operator-( const Vector3 &rhs) const noexcept;

		/// multiply with float
		Vector3 XM_CALLCONV operator*( float s) const noexcept;

		/// equality operator
		bool XM_CALLCONV operator==( const Vector3 &rhs) const noexcept;

		/// inequality operator
		bool XM_CALLCONV operator!=( const Vector3 &rhs) const noexcept;

		/// C++11 Move
		Vector3& XM_CALLCONV operator=(  Vector3&& other) noexcept;

		// Casting-Operatoren
		XM_CALLCONV operator XMFLOAT3& () noexcept				{return vec;}	
		XM_CALLCONV operator const XMFLOAT3& () const noexcept	{return vec;}
		XM_CALLCONV operator float* ()	 noexcept				{return (float*)&vec;}
		XM_CALLCONV operator const float* () const noexcept		{return (float*)&vec;}

		/// Get RawData
		XMFLOAT3 XM_CALLCONV 	GetRaw() const noexcept;
	
		/// Get RawDataPtr
		XMFLOAT3* XM_CALLCONV 	GetRawPtr() noexcept;

		/// Set content
		void  XM_CALLCONV Set( const float x, const float y, const float z) noexcept;
	
		/// Set the x component
		void  XM_CALLCONV SetX( const float x) noexcept;

		/// Set the y component
		void  XM_CALLCONV SetY( const float y) noexcept;

		/// Set the z component
		void  XM_CALLCONV SetZ( const float z) noexcept;

		/// Get the x component
		const float  XM_CALLCONV GetX() const noexcept;

		/// Set the y component
		const float  XM_CALLCONV GetY() const noexcept;

		/// Set the z component
		const float  XM_CALLCONV GetZ() const noexcept;

		/// read/write access to x component
		float&  XM_CALLCONV X() noexcept;

		/// read/write access to y component
		float&  XM_CALLCONV Y() noexcept;

		/// read/write access to z component
		float&  XM_CALLCONV Z() noexcept;

		/// read-only access to x component
		float  XM_CALLCONV X() const noexcept;
		
		/// read-only access to y component
		float  XM_CALLCONV Y() const noexcept;
		
		/// read-only access to z component
		float  XM_CALLCONV Z() const noexcept;

		/// unpack the first element from a XMVECTOR
		static float  XM_CALLCONV Unpack_X( XMVECTOR v) noexcept;
	
		/// unpack the second element from a XMVECTOR
		static float  XM_CALLCONV Unpack_Y( XMVECTOR v) noexcept;
	
		/// unpack the third element from a XMVECTOR
		static float  XM_CALLCONV Unpack_Z( XMVECTOR v) noexcept;

		/// return the null vector
		static Vector3  XM_CALLCONV NullVec() noexcept;
	
		/// return the standard up vector (0, 1, 0)
		static Vector3  XM_CALLCONV UpVec() noexcept;
	
		/// return the standard down vector (0, -1, 0)
		static Vector3  XM_CALLCONV DownVec() noexcept;
	
		/// return the standard left vector (-1, 0, 0)
		static Vector3  XM_CALLCONV LeftVec() noexcept;
	
		/// return the standard right vector (1, 0, 0)
		static Vector3  XM_CALLCONV RightVec() noexcept;
	
		/// return the standard back vector (0, 0, 1)
		static Vector3  XM_CALLCONV BackVec() noexcept;
	
		/// return the standard foreward vector (0, 0, 1)
		static Vector3  XM_CALLCONV ForewardVec() noexcept;

		/// return length of vector
		float  XM_CALLCONV Length() const noexcept;
	
		/// return squared length of vector
		float  XM_CALLCONV Lengthsq() const noexcept;
	
		/// return compononent-wise absolute
		Vector3  XM_CALLCONV Abs() const noexcept;

	

		/// return 1.0 / vec
		static Vector3  XM_CALLCONV Reciprocal( const Vector3 &v) noexcept;
	
		/// component-wise multiplication
		static Vector3  XM_CALLCONV Multiply( const Vector3 &v0,  const Vector3 &v1) noexcept;

		/// return 3-dimensional cross product
		static Vector3  XM_CALLCONV Cross( const Vector3 &v0,  const Vector3 &v1) noexcept;

		/// return 3d dot product of vectors
		static float  XM_CALLCONV Dot( const Vector3 &v0,  const Vector3 &v1) noexcept;
	
		/// return point in barycentric coordinates
		static Vector3  XM_CALLCONV Barycentric( const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, float f, float g) noexcept;

		/// perform Catmull-Rom interpolation
		static Vector3  XM_CALLCONV Catmullrom( const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, float s) noexcept;

		/// perform Hermite spline interpolation
		static Vector3  XM_CALLCONV Hermite( const Vector3 &v1, const Vector3 &t1, const Vector3 &v2, const Vector3 &t2, float s) noexcept;

		/// perform linear interpolation between 2 3d vectors
		static Vector3  XM_CALLCONV Lerp( const Vector3 &v0,  const Vector3 &v1,  float s) noexcept;

		/// return 3d vector made up of largest components of 2 vectors
		static Vector3  XM_CALLCONV Maximize( const Vector3 &v0, const Vector3 &v1) noexcept;

		/// return 3d vector made up of smallest components of 2 vectors
		static Vector3  XM_CALLCONV Minimize( const Vector3 &v0, const Vector3 &v1) noexcept;

		/// return normalized version of 3d vector
		static Vector3  XM_CALLCONV Normalize( const Vector3 &v) noexcept;

		/// reflect a vector v
		static Vector3  XM_CALLCONV Reflect( const Vector3 &normal, const Vector3 &incident) noexcept;

		/// clamp to min/max vector
		static Vector3  XM_CALLCONV Clamp( const Vector3& Clamp, const Vector3& vMin, const Vector3& vMax) noexcept;

		/// angle between two vectors
		static float  XM_CALLCONV Angle( const Vector3& v0,  const Vector3& v1) noexcept;

		/// return the Perpendicular-vector
		static Vector3  XM_CALLCONV Perpendicular( const Vector3& A ) noexcept;

		/// merge components of 2 vectors into 1 (see XMVectorPermute for details)
		static Vector3  XM_CALLCONV Permute( const Vector3& v0,  const Vector3& v1,  const UINT i0,  const UINT i1,  const UINT i2,  const UINT i3) noexcept;

		/// transform 4d vector by matrix44
		static Vector3  XM_CALLCONV Transform( const Vector3& v,  const Matrix &m) noexcept;

		/// return true if any XYZ component is less-then
		static bool  XM_CALLCONV Less3_Any( const Vector3 &v0,  const Vector3 &v1) noexcept;
	
		/// return true if all XYZ components are less-then
		static bool  XM_CALLCONV Less3_All( const Vector3 &v0,  const Vector3 &v1) noexcept;

		/// return true if any XYZ component is less-or-equal
		static bool  XM_CALLCONV Lessequal3_Any( const Vector3 &v0, const Vector3 &v1) noexcept;

		/// return true if all XYZ components are less-or-equal
		static bool  XM_CALLCONV Lessequal3_All( const Vector3 &v0, const Vector3 &v1) noexcept;

		/// return true if any XYZ component is greater
		static bool  XM_CALLCONV Greater3_Any( const Vector3 &v0, const Vector3 &v1) noexcept;

		/// return true if all XYZ components are greater
		static bool  XM_CALLCONV Greater3_All( const Vector3 &v0, const Vector3 &v1) noexcept;

		/// return true if any XYZ component is greater-or-equal
		static bool  XM_CALLCONV Greaterequal3_Any( const Vector3 &v0, const Vector3 &v1) noexcept;

		/// return true if all XYZ components are greater-or-equal
		static bool  XM_CALLCONV Greaterequal3_All( const Vector3 &v0, const Vector3 &v1) noexcept;

		/// return true if any XYZ component is equal
		static bool  XM_CALLCONV Equal3_Any( const Vector3 &v0, const Vector3 &v1) noexcept;

		/// return true if all XYZ components are equal
		static bool  XM_CALLCONV Equal3_All( const Vector3 &v0, const Vector3 &v1) noexcept;

		/// perform near equal comparison with given epsilon (3 components)
		static bool  XM_CALLCONV Nearequal3( const Vector3 &v0, const Vector3 &v1, const Vector3 &epsilon) noexcept;

		/// splat float into each component of a vector
		static Vector3  XM_CALLCONV Splat( float s) noexcept;

		/// return a vector with all elements set to element n of v. 0 <= element <= 3
		static Vector3  XM_CALLCONV Splat( const Vector3 &v, UINT element) noexcept;

		/// return a vector with all elements set to v.x
		static Vector3  XM_CALLCONV Splat_X( const Vector3 &v) noexcept;

		/// return a vector with all elements set to v.y
		static Vector3  XM_CALLCONV Splat_Y( const Vector3 &v) noexcept;

		/// return a vector with all elements set to v.z
		static Vector3  XM_CALLCONV Splat_Z( const Vector3 &v) noexcept;

		/// return a vector with all elements set to v.w
		static Vector3  XM_CALLCONV Splat_W( const Vector3 &v) noexcept;

		/// IsUnit ?
		const bool  XM_CALLCONV IsUnit() const noexcept;

		/// IsUnit ?
		static const bool  XM_CALLCONV IsUnit(const XMVECTOR v) noexcept;


		static Vector3 XM_CALLCONV ZERO() noexcept;
		static Vector3 XM_CALLCONV UNIT_X() noexcept;
		static Vector3 XM_CALLCONV UNIT_Y() noexcept;
		static Vector3 XM_CALLCONV UNIT_Z() noexcept;


		protected:
		XMFLOAT3			vec;
	};

}; // end of namespace TurboMath

#endif