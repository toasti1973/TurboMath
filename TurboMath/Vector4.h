
// -------------------------------------------------------------------
// File			:	Vector4
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

#ifndef _TURBOMATH_VECTOR4_H_
#define _TURBOMATH_VECTOR4_H_



namespace TurboMath
{
	class Matrix;
	class Quat;
	class Vector3;

	CACHE_ALIGN(16) class Vector4
	{
		public:
		//------------------------------------------------------------
		// Constructor
		// -----------------------------------------------------------
		/// default constructor, NOTE: setup components to ZERO!
					Vector4() noexcept;
	
		/// construct from values
		explicit	Vector4( float x,  float y,  float z,   float w) ;
		
		/// construct from XMVECTOR
					Vector4( XMVECTOR rhs) ;
		
		/// construct from components
		explicit	Vector4( float x,  float y,  float z) ;
		
		/// construct from float
		explicit	Vector4( float x) ;
		
		/// construct from float4
					Vector4( const Vector4& rhs) ;
		
		/// construct from XMFLOAT3
					Vector4( const XMFLOAT3& rhs) ;
		
		// constructs from Vector3
		explicit	Vector4( const Vector3& rhs) ;
		
		// constructs from Vector3 and a float for Element W
		explicit	Vector4( const Vector3& rhs,  const float w) ;
		
		/// C++11 Move Constructor
					Vector4( Vector4&& other) noexcept;

		//------------------------------------------------------------
		// assignment
		// -----------------------------------------------------------
		/// assignment operator
		void XM_CALLCONV operator=( const Vector4 &rhs) ;
		
		/// assign an XMVECTOR
		void XM_CALLCONV operator=( XMVECTOR rhs) noexcept;
		
		/// assign an XMFLOAT3
		void XM_CALLCONV operator=( XMFLOAT3 rhs) noexcept;
		// assign a float
		Vector4 XM_CALLCONV operator=( const float rhs) noexcept;

		//------------------------------------------------------------
		// Casting-Operatoren
		//------------------------------------------------------------

		XM_CALLCONV operator  XMVECTOR& ()	 noexcept			{return vec;}
		XM_CALLCONV operator const  XMVECTOR& () const noexcept	{return vec;}
		XM_CALLCONV operator  XMVECTOR* ()	 noexcept			{return &vec;}
		XM_CALLCONV operator const  XMVECTOR* () const noexcept	{return &vec;}
		XM_CALLCONV operator float* ()		 noexcept			{return (float*)&vec;}
		XM_CALLCONV operator const float* () const	 noexcept	{return (float*)&vec;}

		//------------------------------------------------------------
		// operator
		//------------------------------------------------------------
		/// flip sign
		Vector4 XM_CALLCONV operator-() const noexcept;
		
		/// inplace add
		void XM_CALLCONV operator+=( const Vector4 &rhs) noexcept;
		
		/// inplace sub
		void XM_CALLCONV operator-=( const Vector4 &rhs) noexcept;
		
		/// inplace float multiply
		void XM_CALLCONV operator*=( float s) noexcept;
		
		/// muliply by a vector component-wise
		void XM_CALLCONV operator*=( const Vector4& rhs) noexcept;
		
		/// muliply by a vector component-wise
		Vector4 XM_CALLCONV operator*( const Vector4& rhs) noexcept;
		
		/// add 2 vectors
		Vector4 XM_CALLCONV operator+( const Vector4 &rhs) const noexcept;
		
		/// subtract 2 vectors
		Vector4 XM_CALLCONV operator-( const Vector4 &rhs) const noexcept;
		
		/// multiply with float
		Vector4 XM_CALLCONV operator*( float s) const noexcept;
		
		/// equality operator
		bool XM_CALLCONV operator==( const Vector4 &rhs) const noexcept;
		
		/// inequality operator
		bool XM_CALLCONV operator!=( const Vector4 &rhs) const noexcept;
		
		// vector-matrix product
		const Vector4 XM_CALLCONV operator * ( const Matrix& m) const noexcept;
		
		// vector-float division
		Vector4 XM_CALLCONV operator / ( const float f) const noexcept;
		
		/// inplace division by Scalar
		Vector4 XM_CALLCONV operator/= (  const float fScalar ) noexcept;
		
		/// inplace division by Vector
		Vector4 XM_CALLCONV operator/= (  const Vector4& rhs ) noexcept;

		/// C++11 Move
		Vector4& XM_CALLCONV operator=(  Vector4&& other) noexcept;

		/// set components
		void XM_CALLCONV Set( const float x, const  float y, const float z) noexcept;
		
		/// set with Vector4
		void XM_CALLCONV Set(const  Vector4& rhs) noexcept;

		/// Get RawData
		XMVECTOR	XM_CALLCONV GetRaw() const noexcept;
		/// Get RawDataPtr
		XMVECTOR* XM_CALLCONV GetRawPtr() noexcept;

		/// load content from 16-byte-aligned memory
		void XM_CALLCONV Load( const float* ptr) noexcept;
	
		/// load content from unaligned memory
		void XM_CALLCONV LoadU( const float* ptr) noexcept;
		
		/// write content to 16-byte-aligned memory through the write cache
		void XM_CALLCONV Store( float* ptr) const noexcept;
		
		/// write content to unaligned memory through the write cache
		void XM_CALLCONV StoreU( float* ptr) const noexcept;
		
		/// stream content to 16-byte-aligned memory circumventing the write-cache
		void XM_CALLCONV Stream( float* ptr) const noexcept;

		/// load 3 floats into x,y,z from unaligned memory
		void XM_CALLCONV Load_Float3( const void* ptr,  float w) noexcept;
		
		/// load from UByte4N packed vector, move range to -1..+1
		void XM_CALLCONV Load_ubyte4n_signed( const void* ptr,  float w) noexcept;

		/// set content
		void XM_CALLCONV Set( const float x, const float y, const float z, const float w) noexcept;
		
		/// Set Content
		void XM_CALLCONV Set( const XMVECTOR rhs) noexcept;
		
		/// set the x component
		void XM_CALLCONV SetX( const float x) noexcept;
		
		/// set the y component
		void XM_CALLCONV SetY( const float y) noexcept;
		
		/// set the z component
		void XM_CALLCONV SetZ( const float z) noexcept;
		
		/// set the w component
		void XM_CALLCONV SetW( const float w) noexcept;

		/// read/write access to x component
		float& XM_CALLCONV X() noexcept;
	
		/// read/write access to y component
		float& XM_CALLCONV Y() noexcept;
		
		/// read/write access to z component
		float& XM_CALLCONV Z() noexcept;
		
		/// read/write access to w component
		float& XM_CALLCONV W() noexcept;
		
		/// read-only access to x component
		const float XM_CALLCONV GetX() const noexcept;
		
		/// read-only access to y component
		const float XM_CALLCONV GetY() const noexcept;
		
		/// read-only access to z component
		const float XM_CALLCONV GetZ() const noexcept;
		
		/// read-only access to w component
		const float XM_CALLCONV  GetW() const noexcept;

		/// rotate by Quaterion
		Vector4  XM_CALLCONV Rotate( const Quat& Rotation,  const float Scale = 1.0f) noexcept;

		/// return length of vector
		const float XM_CALLCONV Length() const noexcept;
		
		/// return squared length of vector
		const float XM_CALLCONV Lengthsq() const noexcept;
		
		/// return compononent-wise absolute
		Vector4 XM_CALLCONV Abs() const noexcept;

		/// return the null vector
		static Vector4 XM_CALLCONV NullVec() noexcept;
		
		/// return the standard up vector (0, 1, 0)
		static Vector4 XM_CALLCONV UpVec() noexcept;
		
		/// return the standard down vector (0, -1, 0)
		static Vector4 XM_CALLCONV DownVec() noexcept;
		
		/// return the standard left vector (-1, 0, 0)
		static Vector4 XM_CALLCONV LeftVec() noexcept;
		
		/// return the standard right vector (1, 0, 0)
		static Vector4 XM_CALLCONV RightVec() noexcept;
		
		/// return the standard back vector (0, 0, 1)
		static Vector4 XM_CALLCONV BackVec() noexcept;
		
		/// return the standard foreward vector (0, 0, 1)
		static Vector4 XM_CALLCONV ForewardVec() noexcept;
		static Vector4 XM_CALLCONV ZERO() noexcept;
		static Vector4 XM_CALLCONV UNIT_X() noexcept;
		static Vector4 XM_CALLCONV UNIT_Y() noexcept;
		static Vector4 XM_CALLCONV UNIT_Z() noexcept;


		/// return AngleWith
		const float XM_CALLCONV AngleWith( const Vector4& v) noexcept;

		/// return 1.0 / vec
		static Vector4 XM_CALLCONV Reciprocal( const Vector4 &v) noexcept;
		
		/// component-wise multiplication
		static Vector4 XM_CALLCONV Multiply( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return 3-dimensional cross product
		static Vector4 XM_CALLCONV Cross( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return 3d dot product of vectors
		static float XM_CALLCONV Dot( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return point in barycentric coordinates
		static Vector4 XM_CALLCONV Barycentric( const Vector4 &v0,  const Vector4 &v1,  const Vector4 &v2,  float f,  float g) noexcept;
		
		/// perform Catmull-Rom interpolation
		static Vector4 XM_CALLCONV Catmullrom( const Vector4 &v0,  const Vector4 &v1,  const Vector4 &v2,  const Vector4 &v3,  float s) noexcept;
		
		/// perform Hermite spline interpolation
		static Vector4 XM_CALLCONV Hermite( const Vector4 &v1,  const Vector4 &t1,  const Vector4 &v2,  const Vector4 &t2, float s) noexcept;
		
		/// perform linear interpolation between 2 4d vectors
		static Vector4 XM_CALLCONV Lerp( const Vector4 &v0,  const Vector4 &v1,  float s) noexcept;
		
		/// return 4d vector made up of largest components of 2 vectors
		static Vector4 XM_CALLCONV Maximize( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return 4d vector made up of smallest components of 2 vectors
		static Vector4 XM_CALLCONV Minimize( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return normalized version of 4d vector
		static Vector4 XM_CALLCONV Normalize( const Vector4 &v) noexcept;
		
		/// reflect a vector v
		static Vector4 XM_CALLCONV Reflect( const Vector4 &normal,  const Vector4 &incident) noexcept;
		
		/// clamp to min/max vector
		static Vector4 XM_CALLCONV Clamp( const Vector4& Clamp,  const Vector4& vMin,  const Vector4& vMax) noexcept;
		 		
		/// angle between two vectors
		static float XM_CALLCONV Angle( const Vector4& v0,  const Vector4& v1) noexcept;

		/// return true if any XYZ component is less-then
		static bool XM_CALLCONV Less3_Any( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if all XYZ components are less-then
		static bool XM_CALLCONV Less3_All( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if any XYZ component is less-or-equal
		static bool XM_CALLCONV Lessequal3_Any( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if all XYZ components are less-or-equal
		static bool XM_CALLCONV Lessequal3_All( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if any XYZ component is greater
		static bool XM_CALLCONV  Greater3_Any( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if all XYZ components are greater
		static bool XM_CALLCONV Greater3_All( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if any XYZ component is greater-or-equal
		static bool XM_CALLCONV Greaterequal3_Any( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if all XYZ components are greater-or-equal
		static bool XM_CALLCONV Greaterequal3_All( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if any XYZ component is equal
		static bool XM_CALLCONV Equal3_Any( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if all XYZ components are equal
		static bool XM_CALLCONV Equal3_All( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// perform near equal comparison with given epsilon (3 components)
		static bool XM_CALLCONV Nearequal3( const Vector4 &v0,  const Vector4 &v1,  const Vector4 &epsilon) noexcept;

		/// Performs a per-component test for less-than between two vectors.
		static Vector4 XM_CALLCONV Less( const Vector4& v1,  const Vector4& v2) noexcept;
		
		/// return true if any XYZW component is less-then
		static bool XM_CALLCONV Less4_Any( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if all XYZW components are less-then
		static bool XM_CALLCONV Less4_All( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if any XYZW component is less-or-equal
		static bool XM_CALLCONV Lessequal4_Any( const Vector4 &v0,  const Vector4 &v1 ) noexcept;
		
		/// return true if all XYZW components are less-or-equal
		static bool XM_CALLCONV Lessequal4_All( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if any XYZW component is greater
		static bool XM_CALLCONV Greater4_Any( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if all XYZW components are greater
		static bool XM_CALLCONV Greater4_All( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if any XYZW component is greater-or-equal
		static bool XM_CALLCONV Greaterequal4_Any( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if all XYZW components are greater-or-equal
		static bool XM_CALLCONV Greaterequal4_All( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if any XYZW component is equal
		static bool XM_CALLCONV Gqual4_Any( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// return true if all XYZW components are equal
		static bool XM_CALLCONV Equal4_All( const Vector4 &v0,  const Vector4 &v1) noexcept;
		
		/// perform near equal comparison with given epsilon (4 components)
		static bool XM_CALLCONV Nearequal4( const Vector4 &v0,  const Vector4 &v1,  const Vector4 &epsilon) noexcept;
		
		/// unpack the first element from a XMVECTOR
		static float XM_CALLCONV Unpack_X( XMVECTOR v) noexcept;
		
		/// unpack the second element from a XMVECTOR
		static float XM_CALLCONV Unpack_Y( XMVECTOR v) noexcept;
		
		/// unpack the third element from a XMVECTOR
		static float XM_CALLCONV Unpack_Z( XMVECTOR v) noexcept;
		
		/// unpack the fourth element from a XMVECTOR
		static float XM_CALLCONV Unpack_W( XMVECTOR v) noexcept;
		
		/// splat float into each component of a vector
		static const Vector4 XM_CALLCONV Splat( float s) noexcept;
		
		/// return a vector with all elements set to element n of v. 0 <= element <= 3
		static const Vector4 XM_CALLCONV Splat( const Vector4 &v,  UINT element) noexcept;
		
		/// return a vector with all elements set to v.x
		static const Vector4 XM_CALLCONV Splat_X( const Vector4 &v) noexcept;
		
		/// return a vector with all elements set to v.y
		static const Vector4 XM_CALLCONV Splat_Y( const Vector4 &v) noexcept;
		
		/// return a vector with all elements set to v.z
		static const Vector4 XM_CALLCONV Splat_Z( const Vector4 &v) noexcept;
		
		/// return a vector with all elements set to v.w
		static const Vector4 XM_CALLCONV Splat_W( const Vector4 &v) noexcept;
		
		/// merge components of 2 vectors into 1 (see XMVectorPermute for details)
		static const Vector4 XM_CALLCONV Permute( const Vector4& v0,  const Vector4& v1,  const UINT i0,  const UINT i1,  const UINT i2,  const UINT i3) noexcept;
		
		/// transform 4d vector by matrix44
		static const Vector4 XM_CALLCONV Transform( const Vector4 & v,  const Matrix &m) noexcept;
		
		/// Select
		static const Vector4 XM_CALLCONV Select(  const Vector4& v1,  const Vector4& v2,  const Vector4& Control) noexcept;

		/// IsUnit ?
		const bool XM_CALLCONV IsUnit() const  noexcept;

		/// IsUnit ?
		static const bool XM_CALLCONV IsUnit(const XMVECTOR v) noexcept;

		protected:

		XMVECTOR vec;
	};

}// Namespace TurboMath

#endif