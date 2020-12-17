
// -------------------------------------------------------------------
// File			:	Ray.h
//
// Project		:	TurboMath
//
// Description	:	Class for Ray´s
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


#ifndef _TURBOMATH_RAY_H_
#define _TURBOMATH_RAY_H_

namespace TurboMath
{

	class AABB;
	class OBB;
	class Sphere;


	CACHE_ALIGN(16) class Ray
	{
	public:

		/// default constructor
					Ray();
		
					/// component constructor
		explicit	Ray(const Vector4& startPoint, const Vector4& direction);
		
		/// copy constructor
		explicit	Ray(const Ray& rhs);

		/// assignment operator
		void operator=(const Ray& rhs);

		///CopyOf -> Copy Ray to this Ray
		void CopyOf(const Ray& cpyRay);
		
		/// set start point and Direction
		void Set(const Vector4& startPoint, const Vector4& direction);
		
		/// Set StartPoint
		void SetStartPoint(const Vector4& startPoint);
	
		/// Set Direction
		void SetDirection(const Vector4& Direction);
	
		/// Set Length
		void SetLength(const float l);
		
		/// Get Length
		const float GetLength() const;
		
		/// get start point
		const Vector4& GetStartPoint() const;
		
		/// get end point
		Vector4 GetDirection() const;
		
		/// Transform to Coordiante-System
		void DeTransform(const Matrix& _m);
		
		/// Normalize
		void Normalize();

		// Member vars
	protected:
		Vector4 orig;
		Vector4 dir;

	public:
		//-----------------------------------------------------------------------------
		// Intersection testing routines.
		//-----------------------------------------------------------------------------
		const bool	IntersectTriangle( const Vector4& V0, const Vector4& V1, const Vector4& V2 ,float* pDist)  const;
		const bool	IntersectTriangle( const Vector4& V0, const Vector4& V1, const Vector4& V2,float length ,float* pDist) const;

		const bool	IntersectSphere( Sphere* pVolumeA,float* pDist) const;
		const bool	IntersectSphere( Sphere* pVolumeA, float length ,float* pDist) const;

		const bool	IntersectAABB( AABB* pVolumeB ,float* pDist) const;
		const bool	IntersectAABB( AABB* pVolumeB ,float length ,float* pDist) const;

		const bool	IntersectOBB(  OBB* pVolumeB ,float* pDist) ;
		const bool	IntersectOBB(  OBB* pVolumeB, float length  ,float* pDist) ;

		const bool	IntersectPlane( const Plane& plane,float* pDist, Vector4* vHit) const;
		const bool	IntersectPlane( const Plane& plane,float length, float* pDist, Vector4* vHit) const;
	};

}; // end of namespace


#endif