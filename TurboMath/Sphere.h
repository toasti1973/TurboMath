
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
		Vector4 Center;				// X/Y/Z Center of the sphere. W -> Raduis

	public:
		// Functions

		/// Set Center
		void			SetCenter( const Vector4& center);
		/// Get Center
		const Vector4	GetCenter() const;
		/// Set Radius
		void			SetRadius( const float radius);
		/// Get Radius
		const float		GetRadius() const;
		/// Set
		void			Set(const Vector4& center, const float radius);

		void	ComputeBoundingSphereFromPoints(const UINT Count, Vector4* pPoints, const UINT Stride );
	
		void	Transform( const Sphere* pIn, const float Scale,const Quat& Rotation, const Vector4& Translation );

		//-----------------------------------------------------------------------------
		// Comparison 
		//-----------------------------------------------------------------------------
		const bool		operator == (const Sphere& s) const;
		const bool		operator != (const Sphere& s) const;
		const bool		IsEmpty();

		//-----------------------------------------------------------------------------
		// Intersection testing routines.
		//-----------------------------------------------------------------------------
		const bool	IntersectPoint(const Vector4& Point);
		const bool	IntersectRay( const Ray& theRay, float* pDist );
		const bool	IntersectTriangle( const Vector4& V0, const Vector4& V1, const Vector4& V2);
		const bool	IntersectSphere( const Sphere* pVolumeA);
		const bool	IntersectAABB(  const AABB* pVolumeB );
		const bool	IntersectOBB(  const OBB* pVolumeB );

		//-----------------------------------------------------------------------------
		// Volume vs plane intersection testing routines.
		// Return values: 0 = volume is outside the plane (on the positive sideof the plane),
		//                1 = volume intersects the plane,
		//                2 = volume is inside the plane (on the negative side of the plane)
		//-----------------------------------------------------------------------------
		const eCullClassify	IntersectFrustum( Frustum* pVolumeB );
		const eCullClassify	Intersect6Planes( const Plane& Plane0, const Plane& Plane1, const Plane& Plane2,const Plane& Plane3, const Plane& Plane4, const Plane& Plane5 );
		const eCullClassify	IntersectPlane( const Plane& Plane );
	};

}; // end of Namespace



#endif