
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
	CACHE_ALIGN(4) class Vector3
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
		Vector3( Vector3&& other);

		//------------------------------------------------------
		// operator
		//------------------------------------------------------

		/// assignment operator
		void operator=( const Vector3 &rhs);

		/// flip sign
		Vector3 operator-() const;

		/// inplace add
		void operator+=( const Vector3 &rhs);

		/// inplace sub
		void operator-=( const Vector3 &rhs);

		/// inplace float multiply
		void operator*=( float s);

		/// muliply by a vector component-wise
		void operator*=( const Vector3& rhs);

		/// muliply by a vector component-wise
		Vector3 operator*( const Vector3& rhs);

		/// add 2 vectors
		Vector3 operator+( const Vector3 &rhs) const;

		/// subtract 2 vectors
		Vector3 operator-( const Vector3 &rhs) const;

		/// multiply with float
		Vector3 operator*( float s) const;

		/// equality operator
		bool operator==( const Vector3 &rhs) const;

		/// inequality operator
		bool operator!=( const Vector3 &rhs) const;

		/// C++11 Move
		Vector3& operator=(  Vector3&& other);

		// Casting-Operatoren
		operator XMFLOAT3& ()				{return vec;}	
		operator const XMFLOAT3& () const	{return vec;}
		operator float* ()					{return (float*)&vec;}
		operator const float* () const		{return (float*)&vec;}

		/// Get RawData
		XMFLOAT3	GetRaw() const;
	
		/// Get RawDataPtr
		XMFLOAT3*	GetRawPtr();

		/// Set content
		void Set( float x,  float y,  float z);
	
		/// Set the x component
		void SetX( float x);

		/// Set the y component
		void SetY( float y);

		/// Set the z component
		void SetZ( float z);

		/// Get the x component
		const float GetX() const;

		/// Set the y component
		const float GetY() const;

		/// Set the z component
		const float GetZ() const;

		/// read/write access to x component
		float& X();

		/// read/write access to y component
		float& Y();

		/// read/write access to z component
		float& Z();

		/// read-only access to x component
		float X() const;
		
		/// read-only access to y component
		float Y() const;
		
		/// read-only access to z component
		float Z() const;

		/// unpack the first element from a XMVECTOR
		static float Unpack_X( XMVECTOR v);
	
		/// unpack the second element from a XMVECTOR
		static float Unpack_Y( XMVECTOR v);
	
		/// unpack the third element from a XMVECTOR
		static float Unpack_Z( XMVECTOR v);

		/// return the null vector
		static Vector3 NullVec();
	
		/// return the standard up vector (0, 1, 0)
		static Vector3 UpVec();
	
		/// return the standard down vector (0, -1, 0)
		static Vector3 DownVec();
	
		/// return the standard left vector (-1, 0, 0)
		static Vector3 LeftVec();
	
		/// return the standard right vector (1, 0, 0)
		static Vector3 RightVec();
	
		/// return the standard back vector (0, 0, 1)
		static Vector3 BackVec();
	
		/// return the standard foreward vector (0, 0, 1)
		static Vector3 ForewardVec();

		/// return length of vector
		float Length() const;
	
		/// return squared length of vector
		float Lengthsq() const;
	
		/// return compononent-wise absolute
		Vector3 Abs() const;

	

		/// return 1.0 / vec
		static Vector3 Reciprocal( const Vector3 &v);
	
		/// component-wise multiplication
		static Vector3 Multiply( const Vector3 &v0,  const Vector3 &v1);

		/// return 3-dimensional cross product
		static Vector3 Cross( const Vector3 &v0,  const Vector3 &v1);

		/// return 3d dot product of vectors
		static float Dot( const Vector3 &v0,  const Vector3 &v1);
	
		/// return point in barycentric coordinates
		static Vector3 Barycentric( const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, float f, float g);

		/// perform Catmull-Rom interpolation
		static Vector3 Catmullrom( const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, float s);

		/// perform Hermite spline interpolation
		static Vector3 Hermite( const Vector3 &v1, const Vector3 &t1, const Vector3 &v2, const Vector3 &t2, float s);

		/// perform linear interpolation between 2 3d vectors
		static Vector3 Lerp( const Vector3 &v0,  const Vector3 &v1,  float s);

		/// return 3d vector made up of largest components of 2 vectors
		static Vector3 Maximize( const Vector3 &v0, const Vector3 &v1);

		/// return 3d vector made up of smallest components of 2 vectors
		static Vector3 Minimize( const Vector3 &v0, const Vector3 &v1);

		/// return normalized version of 3d vector
		static Vector3 Normalize( const Vector3 &v);

		/// reflect a vector v
		static Vector3 Reflect( const Vector3 &normal, const Vector3 &incident);

		/// clamp to min/max vector
		static Vector3 Clamp( const Vector3& Clamp, const Vector3& vMin, const Vector3& vMax);

		/// angle between two vectors
		static float Angle( const Vector3& v0,  const Vector3& v1);

		/// return the Perpendicular-vector
		static Vector3 Perpendicular( const Vector3& A );

		/// merge components of 2 vectors into 1 (see XMVectorPermute for details)
		static Vector3 Permute( const Vector3& v0,  const Vector3& v1,  const UINT i0,  const UINT i1,  const UINT i2,  const UINT i3);

		/// transform 4d vector by matrix44
		static Vector3 Transform( const Vector3& v,  const Matrix &m);

		/// return true if any XYZ component is less-then
		static bool Less3_Any( const Vector3 &v0,  const Vector3 &v1);
	
		/// return true if all XYZ components are less-then
		static bool Less3_All( const Vector3 &v0,  const Vector3 &v1);

		/// return true if any XYZ component is less-or-equal
		static bool Lessequal3_Any( const Vector3 &v0, const Vector3 &v1);

		/// return true if all XYZ components are less-or-equal
		static bool Lessequal3_All( const Vector3 &v0, const Vector3 &v1);

		/// return true if any XYZ component is greater
		static bool Greater3_Any( const Vector3 &v0, const Vector3 &v1);

		/// return true if all XYZ components are greater
		static bool Greater3_All( const Vector3 &v0, const Vector3 &v1);

		/// return true if any XYZ component is greater-or-equal
		static bool Greaterequal3_Any( const Vector3 &v0, const Vector3 &v1);

		/// return true if all XYZ components are greater-or-equal
		static bool Greaterequal3_All( const Vector3 &v0, const Vector3 &v1);

		/// return true if any XYZ component is equal
		static bool Equal3_Any( const Vector3 &v0, const Vector3 &v1);

		/// return true if all XYZ components are equal
		static bool Equal3_All( const Vector3 &v0, const Vector3 &v1);

		/// perform near equal comparison with given epsilon (3 components)
		static bool Nearequal3( const Vector3 &v0, const Vector3 &v1, const Vector3 &epsilon);

		/// splat float into each component of a vector
		static Vector3 Splat( float s);

		/// return a vector with all elements set to element n of v. 0 <= element <= 3
		static Vector3 Splat( const Vector3 &v, UINT element);

		/// return a vector with all elements set to v.x
		static Vector3 Splat_X( const Vector3 &v);

		/// return a vector with all elements set to v.y
		static Vector3 Splat_Y( const Vector3 &v);

		/// return a vector with all elements set to v.z
		static Vector3 Splat_Z( const Vector3 &v);

		/// return a vector with all elements set to v.w
		static Vector3 Splat_W( const Vector3 &v);

		/// IsUnit ?
		bool IsUnit() const ;

		/// IsUnit ?
		static bool IsUnit(const XMVECTOR v);


		static Vector3 ZERO();
		static Vector3 UNIT_X();
		static Vector3 UNIT_Y();
		static Vector3 UNIT_Z();


		protected:
		XMFLOAT3			vec;
	};

}; // end of namespace TurboMath

#endif