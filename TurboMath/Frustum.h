
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

		Frustum();
		Frustum(const Frustum& cpyFrustum);
	
		// Fucntions

	public:

		 void				SetOrigin(const Vector4& orig);	
		const Vector4		GetOrigin() const;		

		void				SetOrientation(const Quat& NewQuat);	
		const Quat			GetOrientation() const;		

		void				SetRightSlope(const float rf);	
		const float			GetRightSlope() const;	

		void				SetLeftSlope(const float lf);	
		const float			GetLeftSlope() const;	

		void				SetTopSlope(const float tf);	
		const float			GetTopSlope() const;	

		void				SetBottonSlope(const float bf);	
		const float			GetBottomSlope() const;		

		void				SetNearPlane(const float fNear);	
		const float			GetNearPlane() const;	

		void				SetFarPlane(const float fFar);
		const float			GetFarPlane() const	;	

		/// Rotate Frustum around `axis` by `degrees`. Frustum's position is a 
		/// pivot point of rotation, so it doesn't change
		void Rotate(const Vector4& axis, float degrees);

		void Rotate(const Quat& q);

		void ComputeFrustumFromProjection(const Matrix& Projection );
		void ComputePlanes( Plane& Plane0, Plane& Plane1, Plane& Plane2,Plane& Plane3, Plane& Plane4, Plane& Plane5 ) const;

		void Transform(const float Scale,Quat& Rotation,const Vector4& Translation );

		const bool IntersectPoint(const Vector4& Point) const;

		//-----------------------------------------------------------------------------
		// Frustum intersection testing routines.
		// Return values: 0 = no intersection,
		//                1 = intersection,
		//                2 = A is completely inside B
		//-----------------------------------------------------------------------------
		const eCullClassify IntersectTriangle(const Vector4& V0,const Vector4& V1,const Vector4& V2) const;
		const eCullClassify IntersectSphere( const Sphere& pVolumeA) const;
		const eCullClassify IntersectAABB( const AABB& pVolumeA) const;
		const eCullClassify IntersectOBB( const OBB& pVolumeA) const;
		const eCullClassify IntersectFrustum( const Frustum& pVolumeA) const;
		const eCullClassify Intersect6Planes( const Plane& Plane0,const Plane& Plane1, const Plane& Plane2,const Plane& Plane3,const  Plane& Plane4, const Plane& Plane5 ) const;
		const eCullClassify IntersectPlane( const Plane& Plane0 ) const;

	protected:
		Vector4 Origin;				// Origin of the frustum (and projection).
		Quat Orientation;			// Unit quaternion representing rotation.

		float RightSlope;           // Positive X slope (X/Z).
		float LeftSlope;            // Negative X slope.
		float TopSlope;             // Positive Y slope (Y/Z).
		float BottomSlope;          // Negative Y slope.
		float Near, Far;            // Z of the near plane and far plane.

	};

}; // end of namespace
#endif