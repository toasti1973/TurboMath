
// -------------------------------------------------------------------
// File			:	Vector2
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

#ifndef _TURBOMATH_VECTOR2_H_
#define _TURBOMATH_VECTOR2_H_

namespace TurboMath
{
	CACHE_ALIGN(16) class Vector2
	{
	public:
		//------------------------------------------------------
		// Construktor
		//------------------------------------------------------

		/// default constructor, NOTE: does NOT setup components!
		Vector2();
		
		/// construct from values
		explicit Vector2(float x, float y);
		
		/// construct from XMVECTOR
				 Vector2(XMVECTOR rhs);
		
		/// construct from Vector2
				 Vector2(const Vector2& rhs);

		/// construct from Point2
				 Vector2(const Point2& rhs);

		/// C++11 Move Constructor
        Vector2(Vector2&& other);

		//------------------------------------------------------
		// operator
		//------------------------------------------------------

		/// assignment operator
		void operator=(const Vector2 &rhs);

		/// assignment operator
		void operator=(const Point2 &rhs);
	
		/// flip sign
		Vector2 operator-() const;
	
		/// inplace add
		void operator+=(const Vector2 &rhs);
	
		/// inplace sub
		void operator-=(const Vector2 &rhs);
	
		/// inplace float multiply
		void operator*=(float s);
	
		/// muliply by a vector component-wise
		void operator*=(const Vector2& rhs);
	
		/// add 2 vectors
		Vector2 operator+(const Vector2 &rhs) const;
	
		/// subtract 2 vectors
		Vector2 operator-(const Vector2 &rhs) const;
	
		/// multiply with float
		Vector2 operator*(float s) const;
	
		/// equality operator
		bool operator==(const Vector2 &rhs) const;

		/// equality operator
		bool operator==(const Point2 &rhs) const;
	
		/// inequality operator
		bool operator!=(const Vector2 &rhs) const;
	
		/// inequality operator
		bool operator!=(const Point2 &rhs) const;

		//------------------------------------------------------
		// Casting-Operatoren
		//------------------------------------------------------

		operator XMFLOAT2& ();
		operator const XMFLOAT2& () const;
		operator Point2& ();
		operator const Point2() const;
		operator float* ()					{return (float*)&vec;}
		operator const float* () const		{return (float*)&vec;}

		//------------------------------------------------------
		// Set
		//------------------------------------------------------

		/// Set content
		void Set(float x, float y);
	
		/// Set the x component
		void SetX(float x);
	
		/// Set the y component
		void SetY(float y);

		//------------------------------------------------------
		// Get RawData
		//------------------------------------------------------

		/// Get RawData
		XMFLOAT2	GetRaw() const;
		
		/// Get RawDataPtr
		XMFLOAT2*	GetRawPtr();

		//------------------------------------------------------
		// Read / Write-Access
		//------------------------------------------------------

		/// read/write access to x component
		float& x();
	
		/// read/write access to y component
		float& y();
	
		/// read-only access to x component
		float GetX() const;
	
		/// read-only access to y component
		float GetY() const;

		//------------------------------------------------------
		// Functions
		//------------------------------------------------------

		/// Get the NULL-Vector (0.0f,0.0f)
		Vector2	NullVec();

		/// unpack the first element from a XMVECTOR
		static float unpack_x(XMVECTOR v);
	
		/// unpack the second element from a XMVECTOR
		static float unpack_y(XMVECTOR v);

		/// return length of vector
		float Length() const;
	
		/// return squared length of vector
		float Lengthsq() const;

		/// return compononent-wise absolute
		Vector2 abs() const;

		/// return 1.0 / vec
		static Vector2 Reciprocal(const Vector2 &v);

		/// component-wise multiplication
		static Vector2 Multiply(const Vector2 &v0, const Vector2 &v1);

		/// return 3-dimensional cross product
		static Vector2 Cross3(const Vector2 &v0, const Vector2 &v1);

		/// return 3d dot product of vectors
		static float Dot3(const Vector2 &v0, const Vector2 &v1);

		/// return point in barycentric coordinates
		static Vector2 Barycentric(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2, float f, float g);

		/// perform Catmull-Rom interpolation
		static Vector2 Catmullrom(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, float s);

		/// perform Hermite spline interpolation
		static Vector2 Hermite(const Vector2 &v1, const Vector2 &t1, const Vector2 &v2, const Vector2 &t2, float s);

		/// perform linear interpolation between 2 2d vectors
		static Vector2 Lerp(const Vector2 &v0, const Vector2 &v1, float s);

		/// return 2d vector made up of largest components of 2 vectors
		static Vector2 Maximize(const Vector2 &v0, const Vector2 &v1);

		/// return 2d vector made up of smallest components of 2 vectors
		static Vector2 Minimize(const Vector2 &v0, const Vector2 &v1);

		/// return normalized version of 2d vector
		static Vector2 Normalize(const Vector2 &v);

		/// reflect a vector v
		static Vector2 Reflect(const Vector2 &normal, const Vector2 &incident);

		/// clamp to min/max vector
		static Vector2 Clamp(const Vector2& Clamp, const Vector2& vMin, const Vector2& vMax);

		/// angle between two vectors
		static float Angle(const Vector2& v0, const Vector2& v1);

		/// merge components of 2 vectors into 1 (see XMVectorPermute for details)
		static Vector2 Permute(const Vector2& v0, const Vector2& v1, const UINT i0, const UINT i1, const UINT i2, const UINT i3);

		/// transform 4d vector by matrix44
		static Vector2 Transform(const Vector2& v, const Matrix &m);

		//------------------------------------------------------
		// Compare
		//------------------------------------------------------

		/// return true if any XYZ component is less-then
		static bool Less3_Any(const Vector2 &v0, const Vector2 &v1);

		/// return true if all XYZ components are less-then
		static bool Less3_All(const Vector2 &v0, const Vector2 &v1);

		/// return true if any XYZ component is less-or-equal
		static bool Lessequal3_Any(const Vector2 &v0, const Vector2 &v1);

		/// return true if all XYZ components are less-or-equal
		static bool Lessequal3_All(const Vector2 &v0, const Vector2 &v1);

		/// return true if any XYZ component is greater
		static bool Greater3_Any(const Vector2 &v0, const Vector2 &v1);

		/// return true if all XYZ components are greater
		static bool Greater3_All(const Vector2 &v0, const Vector2 &v1);

		/// return true if any XYZ component is greater-or-equal
		static bool Greaterequal3_Any(const Vector2 &v0, const Vector2 &v1);

		/// return true if all XYZ components are greater-or-equal
		static bool Greaterequal3_All(const Vector2 &v0, const Vector2 &v1);

		/// return true if any XYZ component is equal
		static bool Equal3_Any(const Vector2 &v0, const Vector2 &v1);

		/// return true if all XYZ components are equal
		static bool Equal3_all(const Vector2 &v0, const Vector2 &v1);

		/// perform near equal comparison with given epsilon (3 components)
		static bool Nearequal3(const Vector2 &v0, const Vector2 &v1, const Vector2 &epsilon);

		//------------------------------------------------------
		// Splat
		//------------------------------------------------------

		/// splat float into each component of a vector
		static Vector2 Splat(float s);

		/// return a vector with all elements set to element n of v. 0 <= element <= 3
		static Vector2 Splat(const Vector2 &v, UINT element);

		/// return a vector with all elements set to v.x
		static Vector2 Splat_X(const Vector2 &v);

		/// return a vector with all elements set to v.y
		static Vector2 Splat_Y(const Vector2 &v);

		/// return a vector with all elements set to v.w
		static Vector2 Splat_W(const Vector2 &v);



		protected:
		XMFLOAT2			vec;
	};

}; // end of namespace TurboMath

#endif