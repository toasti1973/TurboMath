
// -------------------------------------------------------------------
// File			:	Plane
//
// Project		:	TurboMath
//
// Description	:	Class for Plane´s
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


#ifndef _TURBOMATH_PLANE_H_
#define _TURBOMATH_PLANE_H_


namespace TurboMath
{

	CACHE_ALIGN(16) class Plane
	{
	public:
		/// default constructor, NOTE: does NOT setup componenets!
					Plane();
	
		/// construct from components
		explicit	Plane(float a, float b, float c, float d);
	
		/// construct from points
		explicit	Plane(const Vector4& p0, const Vector4& p1, const Vector4& p2);
		
		/// construct from point and normal
		explicit	Plane(const Vector4& p, const Vector4& n);
		
		/// construct from XMVECTOR
		explicit	Plane(XMVECTOR rhs);

		const bool operator == (const Plane& p) const;
		const bool operator != (const Plane& p) const;

		/// Set with Point and Normal
		void Set(const Vector4& point, const Vector4& normal);
		
		/// set componenets
		void Set(float a, float b, float c, float d);
		
		/// set by Vector4
		void Set(const Vector4& Data);
		
		/// set by XMVECTOR
		void Set(const XMVECTOR& Data);
		
		/// set by points
		void Set(const Vector4& p0, const Vector4& p1, const Vector4& p2);
		
		/// set the x component
		void SetA(float a);
		
		/// set the y component
		void SetB(float b);
		
		/// set the z component
		void SetC(float c);
		
		/// set the w component
		void SetD(float d);

		static Plane XZ_PLANE();
		static Plane XY_PLANE();
		static Plane YZ_PLANE();

		/// get the x component
		const float GetA() const;
		
		/// get the y component
		const float GetB() const;
		
		/// get the z component
		const float GetC() const;
		
		/// get the w component
		const float GetD() const;
	
		/// Get
		Vector4	Get() const;

		/// GetNormal
		Vector4	GetNormal() const;

		/// read/write access to A component
		float& a();
		
		/// read/write access to B component
		float& b();
		
		/// read/write access to C component
		float& c();
		
		/// read/write access to D component
		float& d();
		
		/// read-only access to A component
		float a() const;
		
		/// read-only access to B component
		float b() const;
		
		/// read-only access to C component
		float c() const;
		
		/// read-only access to D component
		float d() const;

		/// compute dot product of plane and vector
		float Dot(const Vector4& v) const;
		
		/// find intersection with line
		bool Intersectline(const Vector4& startPoint, const Vector4& endPoint, Vector4& outIntersectPoint);

		/// normalize plane components a,b,c
		static Plane Normalize(const Plane &p);

		void Normalize();

		void Transform(const Quat& Rotation,const Vector4& Translation );
		
		void Transform(const Matrix& m);

		/// Inverse
		void Inverse();

		/// Refelct
		const Vector4 Reflect(const Vector4& vec) const;

		/// Project
		const Vector4 Project(const Vector4& p) const;

		/// Get  Distrance to Point
		const float DistanceToPoint(const Vector4& pt) const;

		/// IsUnit ?
		const bool IsUnit() const ;

		/// IsUnit ?
		static bool IsUnit(const XMVECTOR p);

		//-----------------------------------------------------------------------------
		// Volume vs plane intersection testing routines.
		// Return values: 0 = volume in Front of the plane (on the positive sideof the plane),
		//                1 = volume intersects the plane,
		//                2 = volume is behind the plane (on the negative side of the plane)
		//-----------------------------------------------------------------------------
		// Classify point to plane.
		const eCullClassify Classify(const Vector4& vcPoint);
		
		// Classify point to plane.
		const eCullClassify Classify(const Polygon& vcPoint);

		// clips a ray into two segments if it Collision the plane
		const bool Clip(const Line& inLine, float fL, Line* pFrontLine, Line* pBackLine);

		friend class Matrix;

		
	protected:
		XMVECTOR vec;
	}; // End of Class Plane

	

} // Namespace TurboMath

#endif