
// -------------------------------------------------------------------
// File			:	OBB
//
// Project		:	TurboMath
//
// Description	:	Class for OBB
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

#ifndef _TURBOMATH_OBB_H_
#define _TURBOMATH_OBB_H_

namespace TurboMath
{

	CACHE_ALIGN(16) class OBB
	{

	public:
        //-----------------------------------------------------------------------------
        // Constructor / Destructor
        //-----------------------------------------------------------------------------
        explicit OBB(const Vector4& c, const Vector4& e, const Quat&o);

        OBB();

		// Get / Set-Functions
		void	SetCenter(const Vector4& newCenter);
		void	SetExtents(const Vector4& newExtents);
		void	SetOrientation(const Quat& newOrientation);

		const	Vector4	GetCenter() const;
		const	Vector4	GetExtents() const;
		const	Quat	GetOrientation() const;

		void Reset();

		//-----------------------------------------------------------------------------
		// Find the approximate minimum oriented bounding box containing a set of
		// points.  Exact computation of minimum oriented bounding box is possible but
		// is slower and requires a more complex algorithm.
		// The algorithm works by computing the inertia tensor of the points and then
		// using the eigenvectors of the intertia tensor as the axes of the box.
		// Computing the intertia tensor of the convex hull of the points will usually
		// result in better bounding box but the computation is more complex.
		// Exact computation of the minimum oriented bounding box is possible but the
		// best know algorithm is O(N^3) and is significanly more complex to implement.
		//-----------------------------------------------------------------------------
		void ComputeBoundingOBBFromPoints( UINT Count, const XMFLOAT3* pPoints, UINT Stride );

		//-----------------------------------------------------------------------------
		// Bounding volume transforms.
		//-----------------------------------------------------------------------------
		void Transform(const float Scale, const Quat& Rotation,const Vector4& Translation );

		//-----------------------------------------------------------------------------
		// Intersection testing routines.
		//-----------------------------------------------------------------------------
		const bool IntersectPoint(const Vector4& Point);
		const bool IntersectOBB( const OBB* pVolumeB );
		const bool IntersectAABB( AABB& pVolumeB );
		const bool IntersectRay( Ray& theRay, float* pDist );
		const bool IntersectTriangle(  const Vector4& V0, const Vector4& V1, const Vector4& V2  );
		const bool IntersectSphere( const Sphere* pVolumeA  );

		//-----------------------------------------------------------------------------
		// Frustum intersection testing routines.
		// Return values: 0 = no intersection,
		//                1 = intersection,
		//                2 = A is completely inside B
		//-----------------------------------------------------------------------------
		const eCullClassify IntersectFrustum( Frustum* pVolumeB );

		//-----------------------------------------------------------------------------
		// Test vs six planes (usually forming a frustum) intersection routines.
		// The intended use for these routines is for fast culling to a view frustum.
		// When the volume being tested against a view frustum is small relative to the
		// view frustum it is usually either inside all six planes of the frustum or
		// outside one of the planes of the frustum. If neither of these cases is true
		// then it may or may not be intersecting the frustum. Outside a plane is
		// defined as being on the positive side of the plane (and inside negative).
		// Return values: 0 = volume is outside one of the planes (no intersection),
		//                1 = not completely inside or completely outside (intersecting),
		//                2 = volume is inside all the planes (completely inside)
		//-----------------------------------------------------------------------------
		const eCullClassify Intersect6Planes( const Plane& Plane0, const Plane& Plane1, const Plane& Plane2,const Plane& Plane3, const Plane& Plane4, const Plane& Plane5 );

		//-----------------------------------------------------------------------------
		// Volume vs plane intersection testing routines.
		// Return values: 0 = volume is outside the plane (on the positive sideof the plane),
		//                1 = volume intersects the plane,
		//                2 = volume is inside the plane (on the negative side of the plane)
		//-----------------------------------------------------------------------------
		const eCullClassify IntersectPlane( const Plane& Plane );

		//-------------------------------------------------------------------------------
		// Get the 8 EdgePoints from the OBB
		// We MUST give a Array from 8 TurboMath::Vector4 Members for the EdgePoints
		//-------------------------------------------------------------------------------
		void GetEdgePoints( Vector4* pPointlist);

		protected:
		Vector4 Center;				// Center of the box.
		Vector4 Extents;			// Distance from the center to each side.
		Quat Orientation;			// Unit quaternion representing rotation (box -> world).

	};

}; // end of namespace

#endif