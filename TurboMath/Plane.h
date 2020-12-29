
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
				Plane() noexcept;
	
		/// construct from components
		explicit	Plane(const float a, const float b, const float c, const float d) noexcept;
	
		/// construct from points
		explicit	Plane(const Vector4& p0, const Vector4& p1, const Vector4& p2) noexcept;
		
		/// construct from point and normal
		explicit	Plane(const Vector4& p, const Vector4& n);
		
		/// construct from XMVECTOR
		explicit	Plane(XMVECTOR rhs) noexcept;

		const bool XM_CALLCONV operator == (const Plane& p) const noexcept;
		const bool XM_CALLCONV operator != (const Plane& p) const noexcept;

		/// Set with Point and Normal
		void XM_CALLCONV Set(const Vector4& point, const Vector4& normal) noexcept;
		
		/// set componenets
		void XM_CALLCONV Set(float a, float b, float c, float d) noexcept;
		
		/// set by Vector4
		void XM_CALLCONV Set(const Vector4& Data) noexcept;
		
		/// set by XMVECTOR
		void XM_CALLCONV Set(const XMVECTOR& Data) noexcept;
		
		/// set by points
		void XM_CALLCONV Set(const Vector4& p0, const Vector4& p1, const Vector4& p2) noexcept;
		
		/// set the x component
		void XM_CALLCONV SetA(const float a) noexcept;
		
		/// set the y component
		void XM_CALLCONV SetB(const float b) noexcept;
		
		/// set the z component
		void XM_CALLCONV SetC(const float c) noexcept;
		
		/// set the w component
		void XM_CALLCONV SetD(const float d) noexcept;

		static const Plane XM_CALLCONV XZ_PLANE() noexcept;
		static const Plane XM_CALLCONV XY_PLANE() noexcept;
		static const Plane XM_CALLCONV YZ_PLANE() noexcept;

		/// get the x component
		const float XM_CALLCONV  GetA() const noexcept;
		
		/// get the y component
		const float XM_CALLCONV GetB() const noexcept;
		
		/// get the z component
		const float XM_CALLCONV GetC() const noexcept;
		
		/// get the w component
		const float XM_CALLCONV GetD() const noexcept;
	
		/// Get
		const Vector4	XM_CALLCONV Get() const noexcept;

		/// GetNormal
		const Vector4	XM_CALLCONV GetNormal() const noexcept;

		/// read/write access to A component
		float& XM_CALLCONV a() noexcept;
		
		/// read/write access to B component
		float& XM_CALLCONV b() noexcept;
		
		/// read/write access to C component
		float& XM_CALLCONV c() noexcept;
		
		/// read/write access to D component
		float& XM_CALLCONV d() noexcept;
		
		/// read-only access to A component
		const float XM_CALLCONV a() const noexcept;
		
		/// read-only access to B component
		const float XM_CALLCONV b() const noexcept;
		
		/// read-only access to C component
		const float XM_CALLCONV c() const noexcept;
		
		/// read-only access to D component
		const float XM_CALLCONV d() const noexcept;

		/// compute dot product of plane and vector
		const float XM_CALLCONV Dot(const Vector4& v) const noexcept;
		
		/// find intersection with line
		const bool XM_CALLCONV Intersectline(const Vector4& startPoint, const Vector4& endPoint, Vector4& outIntersectPoint) noexcept;

		/// normalize plane components a,b,c
		static Plane XM_CALLCONV Normalize(const Plane &p) noexcept;

		void XM_CALLCONV Normalize() noexcept;

		void XM_CALLCONV Transform(const Quat& Rotation,const Vector4& Translation ) noexcept;
		
		void XM_CALLCONV Transform(const Matrix& m) noexcept;

		/// Inverse
		void XM_CALLCONV Inverse() noexcept;

		/// Refelct
		const Vector4 XM_CALLCONV Reflect(const Vector4& vec) const noexcept;

		/// Project
		const Vector4 XM_CALLCONV Project(const Vector4& p) const noexcept;

		/// Get  Distrance to Point
		const float XM_CALLCONV DistanceToPoint(const Vector4& pt) const noexcept;

		/// IsUnit ?
		const bool XM_CALLCONV IsUnit() const noexcept ;

		/// IsUnit ?
		static const bool XM_CALLCONV IsUnit(const XMVECTOR p) noexcept;

		//-----------------------------------------------------------------------------
		// Volume vs plane intersection testing routines.
		// Return values: 0 = volume in Front of the plane (on the positive sideof the plane),
		//                1 = volume intersects the plane,
		//                2 = volume is behind the plane (on the negative side of the plane)
		//-----------------------------------------------------------------------------
		// Classify point to plane.
		const eCullClassify XM_CALLCONV Classify(const Vector4& vcPoint) noexcept;
		
		// Classify point to plane.
		const eCullClassify XM_CALLCONV Classify(const Polygon& vcPoint) noexcept;

		// clips a ray into two segments if it Collision the plane
		const bool XM_CALLCONV Clip(const Line& inLine, float fL, Line* pFrontLine, Line* pBackLine) noexcept;

		friend class Matrix;

		
	protected:
		XMVECTOR vec;
	}; // End of Class Plane

	

} // Namespace TurboMath

#endif