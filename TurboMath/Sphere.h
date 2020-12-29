
// -------------------------------------------------------------------
// File			:	Sphere
//
// Project		:	TurboMath
//
// Description	:	Class for SPhere
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

#ifndef _TURBOMATH_SPHERE_H_
#define _TURBOMATH_SPHERE_H_

namespace TurboMath
{

	class AABB;
	class OBB;
	class Frustum;

	CACHE_ALIGN(16) class Sphere
	{
	protected:
		Vector4 Center;			// X/Y/Z Center of the sphere. W -> Raduis

	public:
		// Functions

		/// Set Center
		void XM_CALLCONV 		SetCenter( const Vector4& center) noexcept;
		/// Get Center
		const Vector4 XM_CALLCONV 	GetCenter() const noexcept;
		/// Set Radius
		void XM_CALLCONV 		SetRadius( const float radius) noexcept;
		/// Get Radius
		const float XM_CALLCONV 	GetRadius() const noexcept;
		/// Set
		void XM_CALLCONV 		Set(const Vector4& center, const float radius) noexcept;

		void XM_CALLCONV 		ComputeBoundingSphereFromPoints(const UINT Count, Vector4* pPoints, const UINT Stride );
	
		void XM_CALLCONV 		Transform( const Sphere* pIn, const float Scale,const Quat& Rotation, const Vector4& Translation );

		//-----------------------------------------------------------------------------
		// Comparison 
		//-----------------------------------------------------------------------------
		const bool XM_CALLCONV 		operator == (const Sphere& s) const noexcept;
		const bool XM_CALLCONV 		operator != (const Sphere& s) const noexcept;
		const bool XM_CALLCONV 		IsEmpty() noexcept;

		//-----------------------------------------------------------------------------
		// Intersection testing routines.
		//-----------------------------------------------------------------------------
		const bool XM_CALLCONV 	IntersectPoint(const Vector4& Point) noexcept;
		const bool XM_CALLCONV 	IntersectRay( const Ray& theRay, float* pDist );
		const bool XM_CALLCONV 	IntersectTriangle( const Vector4& V0, const Vector4& V1, const Vector4& V2) noexcept;
		const bool XM_CALLCONV 	IntersectSphere( const Sphere* pVolumeA);
		const bool XM_CALLCONV 	IntersectAABB(  const AABB* pVolumeB );
		const bool XM_CALLCONV 	IntersectOBB(  const OBB* pVolumeB );

		//-----------------------------------------------------------------------------
		// Volume vs plane intersection testing routines.
		// Return values: 0 = volume is outside the plane (on the positive sideof the plane),
		//                1 = volume intersects the plane,
		//                2 = volume is inside the plane (on the negative side of the plane)
		//-----------------------------------------------------------------------------
		const eCullClassify XM_CALLCONV 	IntersectFrustum( Frustum* pVolumeB );
		const eCullClassify XM_CALLCONV 	Intersect6Planes( const Plane& Plane0, const Plane& Plane1, const Plane& Plane2,const Plane& Plane3, const Plane& Plane4, const Plane& Plane5 ) noexcept;
		const eCullClassify XM_CALLCONV 	IntersectPlane( const Plane& Plane );
	};

}; // end of Namespace



#endif