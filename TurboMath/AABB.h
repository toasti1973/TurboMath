
// -------------------------------------------------------------------
// File			:	AABB.h
//
// Project		:	TurboMath
//
// Description	:	Class for AABB
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
#pragma once


#ifndef _TURBOMATH_AABB_H_
#define _TURBOMATH_AABB_H_

namespace TurboMath
{

	CACHE_ALIGN(16) class AABB
	{

	public:
		//-----------------------------------------------------------------------------
		// Constructor / Destructor
		//-----------------------------------------------------------------------------
		explicit	AABB(const Vector4& c,const Vector4& e);

					AABB();

		explicit	AABB( OBB& o );

		bool XM_CALLCONV operator == (const AABB& box) const noexcept;
		bool XM_CALLCONV operator != (const AABB& box) const noexcept;

		// Functions
		/// Set Center and Extents
		void		XM_CALLCONV Reset() noexcept;
		const bool	XM_CALLCONV	IsReset() const noexcept;

		void		XM_CALLCONV	Set(const Vector4& c, const Vector4& e) noexcept;
		void		XM_CALLCONV	SetCenter(const Vector4& c) noexcept;
		void		XM_CALLCONV	SetExtents(const Vector4& e) noexcept;
		void		XM_CALLCONV	SetMinMaxExtents(const Vector4& vMin,const Vector4& vMax) noexcept;

		void		XM_CALLCONV	Move(const Vector4& vec) noexcept;

		const Vector4	XM_CALLCONV	GetCenter() const noexcept;
		const Vector4	XM_CALLCONV	GetExtents() const noexcept;

		const Vector4	XM_CALLCONV	GetMinExtents() const noexcept;
		const Vector4	XM_CALLCONV	GetMaxExtents() const noexcept;

		const float		XM_CALLCONV	GetVolume() const noexcept;

		const Vector4	XM_CALLCONV	GetPoint(const int index) const noexcept;
		const Vector4	XM_CALLCONV	GetVertexNormal( const int index) const noexcept;
		const Vector4	XM_CALLCONV	GetFaceNormal( const ePlane which) const noexcept;
		
		const Plane		XM_CALLCONV	GetPlane(const ePlane which) const noexcept;
		const Line		XM_CALLCONV	GetEdge(const int index) const noexcept;

		// Get the 6 plane of the AABB
		const void XM_CALLCONV	GetPlanes(  Plane& Plane0, Plane& Plane1, Plane& Plane2, Plane& Plane3, Plane& Plane4, Plane& Plane5 ) const noexcept;

		//-----------------------------------------------------------------------------
		// Find the minimum axis aligned bounding box containing a set of points.
		//-----------------------------------------------------------------------------
		void XM_CALLCONV	ComputeBoundingAABBFromPoints(UINT Count, Vector4* pPoints, UINT Stride ) noexcept;

		//-----------------------------------------------------------------------------
		// Transform an axis aligned box by an angle preserving transform.
		//-----------------------------------------------------------------------------
		void XM_CALLCONV	Transform( const AABB* pIn,const float Scale, const Quat& Rotation, const Vector4& Translation ) noexcept;

		//-----------------------------------------------------------------------------
		// Intersection testing routines.
		//-----------------------------------------------------------------------------
		const bool XM_CALLCONV	IntersectPoint( const Vector4& Point) const noexcept;
		const bool XM_CALLCONV	IntersectRay(  const Ray& theRay,float* pDist ) const noexcept;
		const bool XM_CALLCONV	IntersectTriangle(  const Vector4& V0, const Vector4& V1, const Vector4& V2 ) const noexcept;
		const bool XM_CALLCONV	IntersectSphere( Sphere& pVolumeA ) const noexcept;
		const bool XM_CALLCONV	IntersectAABB( AABB& pVolumeB ) const noexcept;
		const bool XM_CALLCONV	IntersectOBB( OBB& pVolumeB ) const noexcept;

		// does aabb contain ray
		const bool XM_CALLCONV	Contains(const Ray& ray, float fL) const noexcept;

		//-----------------------------------------------------------------------------
		// Frustum intersection testing routines.
		// Return values: 0 = no intersection,
		//                1 = intersection,
		//                2 = A is completely inside B
		//-----------------------------------------------------------------------------
		const eCullClassify XM_CALLCONV	IntersectFrustum( Frustum* pVolumeB ) const noexcept;
		const eCullClassify XM_CALLCONV	IntersectPlane( Plane& Plane0 ) const noexcept;

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
		const eCullClassify XM_CALLCONV	Intersect6Planes(  Plane& Plane0, Plane& Plane1, Plane& Plane2, Plane& Plane3, Plane& Plane4, Plane& Plane5 ) const noexcept;

		protected:

		Vector4 Center;				// Center of the box.
		Vector4 Extents;			// Distance from the center to each side.

	};

}; // end of namespace

#endif