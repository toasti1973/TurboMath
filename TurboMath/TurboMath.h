//	 #######                             #     #                     
//		#    #    # #####  #####   ####  ##   ##   ##   ##### #    # 
//		#    #    # #    # #    # #    # # # # #  #  #    #   #    # 
//		#    #    # #    # #####  #    # #  #  # #    #   #   ###### 
//		#    #    # #####  #    # #    # #     # ######   #   #    # 
//		#    #    # #   #  #    # #    # #     # #    #   #   #    # 
//		#     ####  #    # #####   ####  #     # #    #   #   #    # 
// -------------------------------------------------------------------
// File			:	TurboMath.h
//
// Description	:	Collection of Math-Classes for DirectXMath
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


#ifndef _TURBOMATH_H_
#define _TURBOMATH_H_

// ************************************************************
// Disable Warnings
// ************************************************************

//#pragma warning (disable : 4996)
//#pragma warning (disable : 4800)

//#pragma warning (disable : 4201)
//#pragma warning (disable : 4129)

//#pragma warning (disable : 4324)
#pragma warning (disable : 4244)

//-------------------------------------------------------
// Math for TurboMath
//-------------------------------------------------------


#include <assert.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>
#include <DirectXColors.h>
#include <limits>

using namespace DirectX;

//------------------------------------------------------
// Some Helpers
//------------------------------------------------------


#ifndef CACHE_ALIGN
#define CACHE_ALIGN(x)			__declspec(align(x))
#endif

typedef unsigned int        UINT;

//------------------------------------------------------
// We want the fastest Calling-Convention
// for all Functions ...	: __vectorcall
//------------------------------------------------------
#define XM_CALLCONV __vectorcall


#define XM_INLINE   __forceinline


//------------------------------------------------------
// TurboMath
//------------------------------------------------------

namespace TurboMath
{
	#pragma warning (push)

	

	enum eCullClassify
	{
		FRONT,
		BACK,
		PLANAR,
		CLIPPED,
		CULLED,
		VISIBLE,
	};

	enum ePlane
	{
		LEFT_PLANE,				/**< Left plane.*/
		RIGHT_PLANE,			/**< Right plane.*/
		BOTTOM_PLANE,			/**< Bottom plane.*/
		TOP_PLANE,				/**< Top plane.*/
		NEAR_PLANE,				/**< Near plane.*/
		FAR_PLANE				/**< Far plane.*/
	};


	constexpr  float	TURBOMATH_PI				= 3.14159265358979323846f;				// pi
	constexpr  float	TURBOMATH_TWO_PI			= 2.0f * TURBOMATH_PI;					// pi * 2
	constexpr  float	TURBOMATH_HALF_PI			= 0.5f * TURBOMATH_PI;					// pi * 0.5
	constexpr  float	TURBOMATH_ONEFOURTH_PI		= 0.25f * TURBOMATH_PI;					// pi * 0.25
	constexpr  float	TURBOMATH_SQRT_TWO			= 1.41421356237309504880f;				// sqrt( 2 )
	constexpr  float	TURBOMATH_SQRT_THREE		= 1.73205080756887729352f;				// sqrt( 3 )
	constexpr  float	TURBOMATH_SQRT_1OVER2		= 0.70710678118654752440f;				// sqrt( 1 / 2 )
	constexpr  float	TURBOMATH_SQRT_1OVER3		= 0.57735026918962576450f;				// sqrt( 1 / 3 )
	constexpr  float	TURBOMATH_EPSILON			= std::numeric_limits<float>::epsilon() ;// Used to compensate for floating point inaccuracy.


	// Foreward declaration
	class Vector2;
	class Vector3;
	class Vector4;
	class Line;
	class Ray;
	class Matrix;
	class Frustum;
	class Polygon;

	

	
	//----------------------------------------------------------------------------------------
	// Check for SSE/SSE2 CPU-Support for XNA-Math
	//----------------------------------------------------------------------------------------
extern "C"
{
	const bool  VerifyCPUSupport();
}

#pragma warning(pop)
}; // namespace TurboMath

//----------------------------------------------------------------------------------------
// include all Header-Files
//----------------------------------------------------------------------------------------

	#include "Scalar.h"
	#include "Point2.h"
	#include "Point3.h"
	#include "Point4.h"
	#include "Vector2.h"
	#include "Vector3.h"
	#include "Vector4.h"
	#include "Quat.h"
	#include "Plane.h"
	#include "Matrix.h"
	#include "Line.h"
	#include "Sphere.h"
	#include "Ray.h"
	#include "AABB.h"
	#include "OBB.h"
	#include "Frustum.h"
	#include "Color.h"
	#include "Camera.h"
	#include "AAllocator.h"
	#include "WayPoints.h"
	#include "MoveController.h"
	#include "Triangle.h"


//----------------------------------------------------------------------------------------
// include all Inline-Code
//----------------------------------------------------------------------------------------
	#include "Scalar.inl"
	#include "Helper.inl"
	#include "Point2.inl"
	#include "Point3.inl"
	#include "Point4.inl"
	#include "Quat.inl"
	#include "Vector2.inl"
	#include "Vector3.inl"
	#include "Vector4.inl"
	#include "Line.inl"
	#include "Matrix.inl"
	#include "Sphere.inl"
	#include "AABB.inl"
	#include "OBB.inl"
	#include "Plane.inl"
	#include "Ray.inl"
	#include "Sphere.inl"
	#include "Frustum.inl"
	#include "Color.inl"
	#include "Camera.inl"
	#include "WayPoints.inl"
	#include "MoveController.inl"
	#include "Triangle.inl"


#endif