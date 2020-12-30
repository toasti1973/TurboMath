
// -------------------------------------------------------------------
// File			:	Frustum
//
// Project		:	TurboMath
//
// Description	:	Class for View-Frustum
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

#ifndef _TURBOMATH_FRUSTUM_H_
#define _TURBOMATH_FRUSTUM_H_


namespace TurboMath
{

	CACHE_ALIGN(16) class Frustum
	{
	public:

		Frustum() noexcept;
		Frustum(const Frustum& cpyFrustum) noexcept;
	
		// Fucntions

	public:

		void		XM_CALLCONV SetOrigin(const Vector4& orig) noexcept;	
		const Vector4	XM_CALLCONV GetOrigin() const noexcept;		

		void		XM_CALLCONV SetOrientation(const Quat& NewQuat) noexcept;	
		const Quat	XM_CALLCONV GetOrientation() const noexcept;		

		void		XM_CALLCONV SetRightSlope(const float rf) noexcept;	
		const float	XM_CALLCONV GetRightSlope() const noexcept;	

		void		XM_CALLCONV SetLeftSlope(const float lf) noexcept;	
		const float	XM_CALLCONV GetLeftSlope() const noexcept;	

		void		XM_CALLCONV SetTopSlope(const float tf) noexcept;	
		const float	XM_CALLCONV GetTopSlope() const noexcept;	

		void		XM_CALLCONV SetBottonSlope(const float bf) noexcept;	
		const float	XM_CALLCONV GetBottomSlope() const noexcept;		

		void		XM_CALLCONV SetNearPlane(const float fNear) noexcept;	
		const float	XM_CALLCONV GetNearPlane() const noexcept;	

		void		XM_CALLCONV SetFarPlane(const float fFar) noexcept;
		const float	XM_CALLCONV GetFarPlane() const  noexcept;	

		/// Rotate Frustum around `axis` by `degrees`. Frustum's position is a 
		/// pivot point of rotation, so it doesn't change
		void XM_CALLCONV Rotate(const Vector4& axis, float degrees) noexcept;

		void XM_CALLCONV Rotate(const Quat& q) noexcept;

		void XM_CALLCONV ComputeFrustumFromProjection(const Matrix& Projection ) noexcept;
		void XM_CALLCONV ComputePlanes( Plane& Plane0, Plane& Plane1, Plane& Plane2,Plane& Plane3, Plane& Plane4, Plane& Plane5 ) const noexcept;

		void XM_CALLCONV Transform(const float Scale,Quat& Rotation,const Vector4& Translation ) noexcept;

		const bool XM_CALLCONV IntersectPoint(const Vector4& Point) const noexcept;

		//-----------------------------------------------------------------------------
		// Frustum intersection testing routines.
		// Return values: 0 = no intersection,
		//                1 = intersection,
		//                2 = A is completely inside B
		//-----------------------------------------------------------------------------
		const eCullClassify XM_CALLCONV IntersectTriangle(const Vector4& V0,const Vector4& V1,const Vector4& V2) const noexcept;
		const eCullClassify XM_CALLCONV IntersectSphere( const Sphere& pVolumeA) const noexcept;
		const eCullClassify XM_CALLCONV IntersectAABB( const AABB& pVolumeA) const noexcept;
		const eCullClassify XM_CALLCONV IntersectOBB( const OBB& pVolumeA) const noexcept;
		const eCullClassify XM_CALLCONV IntersectFrustum( const Frustum& pVolumeA) const noexcept;
		const eCullClassify XM_CALLCONV Intersect6Planes( const Plane& Plane0,const Plane& Plane1, const Plane& Plane2,const Plane& Plane3,const  Plane& Plane4, const Plane& Plane5 ) const;
		const eCullClassify XM_CALLCONV IntersectPlane( const Plane& Plane0 ) const;

	protected:
		Vector4 Origin;		// Origin of the frustum (and projection).
		Quat Orientation;	// Unit quaternion representing rotation.

		float RightSlope;       // Positive X slope (X/Z).
		float LeftSlope;        // Negative X slope.
		float TopSlope;         // Positive Y slope (Y/Z).
		float BottomSlope;      // Negative Y slope.
		float Near, Far;        // Z of the near plane and far plane.

	};

}; // end of namespace
#endif