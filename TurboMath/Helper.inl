
// -------------------------------------------------------------------
// File			:	Helper
//
// Project		:	TurboMath
//
// Description	:	Helper-Functions for TurboMath
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


#ifndef _TURBOMATH_HELPER_H_
#define _TURBOMATH_HELPER_H_


namespace TurboMath
{
	//----------------------------------------------------------------------------------------
	// Check for Memory Align 
	//----------------------------------------------------------------------------------------

	template <typename T> XM_INLINE T AlignUpWithMask(T value, size_t mask)
	{
		return (T)(((size_t)value + mask) & ~mask);
	}

	template <typename T> XM_INLINE T AlignDownWithMask(T value, size_t mask)
	{
		return (T)((size_t)value & ~mask);
	}

	template <typename T> XM_INLINE T AlignUp(T value, size_t alignment)
	{
		return AlignUpWithMask(value, alignment - 1);
	}

	template <typename T> XM_INLINE T AlignDown(T value, size_t alignment)
	{
		return AlignDownWithMask(value, alignment - 1);
	}

	template <typename T> XM_INLINE bool IsAligned(T value, size_t alignment)
	{
		return 0 == ((size_t)value & (alignment - 1));
	}

	template <typename T> XM_INLINE T DivideByMultiple(T value, size_t alignment)
	{
		return (T)((value + alignment - 1) / alignment);
	}

	//-----------------------------------------------------------------------------
	// Test, is Memory Aligned ?
	//-----------------------------------------------------------------------------
/*	static const bool IsAligned(void* data, int alignment)
	{
		// check that the alignment is a power of two
		assert((alignment & (alignment-1)) == 0);
		return ((uintptr_t)data & (alignment-1)) == 0;
	}
*/
	//-----------------------------------------------------------------------------
	// Get Max from two floats
	//-----------------------------------------------------------------------------
	XM_INLINE float TB_max(const float a,const float b)
	{
		return (a > b) ? a : b;
	}

	//-----------------------------------------------------------------------------
	// Get Min from two floats
	//-----------------------------------------------------------------------------
	XM_INLINE float TB_min(const float a,const float b)
	{
		return (a < b) ? a : b;
	}

	
	//-----------------------------------------------------------------------------
	// Return true if any of the elements of a 3 vector are equal to 0xffffffff.
	// Slightly more efficient than using XMVector3EqualInt.
	//-----------------------------------------------------------------------------
	XM_INLINE bool XMVector3AnyTrue( const FXMVECTOR V )
	{
		// Duplicate the fourth element from the first element.
		const XMVECTOR C = XMVectorSwizzle<XM_SWIZZLE_X, XM_SWIZZLE_Y, XM_SWIZZLE_Z, XM_SWIZZLE_X>(V);

		return XMComparisonAnyTrue( XMVector4EqualIntR( C, XMVectorTrueInt() ) );
	}


	//-----------------------------------------------------------------------------
	// Return true if all of the elements of a 3 vector are equal to 0xffffffff.
	// Slightly more efficient than using XMVector3EqualInt.
	//-----------------------------------------------------------------------------
	XM_INLINE bool XMVector3AllTrue( const FXMVECTOR V )
	{
		// Duplicate the fourth element from the first element.
		const XMVECTOR C = XMVectorSwizzle<XM_SWIZZLE_X, XM_SWIZZLE_Y, XM_SWIZZLE_Z, XM_SWIZZLE_X>( V );

		return XMComparisonAllTrue( XMVector4EqualIntR( C, XMVectorTrueInt() ) );
	}

	//-----------------------------------------------------------------------------
	// Test if the point (P) on the plane of the triangle is inside the triangle
	// (V0, V1, V2).
	//-----------------------------------------------------------------------------
	XM_INLINE Vector4 PointOnPlaneInsideTriangle( const Vector4& P, const Vector4& V0, const Vector4& V1, const Vector4& V2 )
	{
		// Compute the triangle normal.
		const XMVECTOR N = XMVector3Cross(  (V2 - V0) , (V1 - V0) );

		// Compute the cross products of the vector from the base of each edge to
		// the point with each edge vector.
		const XMVECTOR C0 = XMVector3Cross( (P - V0), (V1 - V0) );
		const XMVECTOR C1 = XMVector3Cross( (P - V1), (V2 - V1) );
		const XMVECTOR C2 = XMVector3Cross( (P - V2), (V0 - V2) );

		// If the cross product points in the same direction as the normal the the
		// point is inside the edge (it is zero if is on the edge).
		const XMVECTOR Zero = XMVectorZero();
		const XMVECTOR Inside0 = XMVectorGreaterOrEqual( XMVector3Dot( C0, N ), Zero );
		const XMVECTOR Inside1 = XMVectorGreaterOrEqual( XMVector3Dot( C1, N ), Zero );
		const XMVECTOR Inside2 = XMVectorGreaterOrEqual( XMVector3Dot( C2, N ), Zero );

		// If the point inside all of the edges it is inside.
		return XMVectorAndInt( XMVectorAndInt( Inside0, Inside1 ), Inside2 );
	}

	//-----------------------------------------------------------------------------
	static XM_INLINE void FastIntersectSpherePlane( const Vector4& Center, const Vector4& Radius,  const Plane& Plane, XMVECTOR& Outside,  XMVECTOR& Inside )
	{
		const XMVECTOR Dist = XMVector4Dot( Center, Plane.Get() );

		// Outside the plane?
		Outside = XMVectorGreater( Dist, Radius);

		// Fully inside the plane?
		Inside = XMVectorLess( Dist, -Radius );
	}

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	static XM_INLINE void FastIntersectFrustumPlane(  Vector4& Point0,  Vector4& Point1,  Vector4& Point2,  const Vector4& Point3,	 const Vector4& Point4,
												 const Vector4& Point5,  const Vector4& Point6,  const Vector4& Point7,  const Plane& Plane,  XMVECTOR& Outside,  XMVECTOR& Inside )
	{
		// Find the min/max projection of the frustum onto the plane normal.
		XMVECTOR Min, Max, Dist;

		Min = Max = XMVector3Dot( Plane.Get(), Point0 );

		Dist = XMVector3Dot( Plane.Get(), Point1 );
		Min = XMVectorMin( Min, Dist );
		Max = XMVectorMax( Max, Dist );

		Dist = XMVector3Dot( Plane.Get(), Point2 );
		Min = XMVectorMin( Min, Dist );
		Max = XMVectorMax( Max, Dist );

		Dist = XMVector3Dot( Plane.Get(), Point3 );
		Min = XMVectorMin( Min, Dist );
		Max = XMVectorMax( Max, Dist );

		Dist = XMVector3Dot( Plane.Get(), Point4 );
		Min = XMVectorMin( Min, Dist );
		Max = XMVectorMax( Max, Dist );

		Dist = XMVector3Dot( Plane.Get(), Point5 );
		Min = XMVectorMin( Min, Dist );
		Max = XMVectorMax( Max, Dist );

		Dist = XMVector3Dot( Plane.Get(), Point6 );
		Min = XMVectorMin( Min, Dist );
		Max = XMVectorMax( Max, Dist );

		Dist = XMVector3Dot( Plane.Get(), Point7 );
		Min = XMVectorMin( Min, Dist );
		Max = XMVectorMax( Max, Dist );

		const XMVECTOR PlaneDist = XMVectorNegate(XMVectorSplatW( Plane.Get() ) );

		// Outside the plane?
		Outside = XMVectorGreater( Min, PlaneDist );

		// Fully inside the plane?
		Inside = XMVectorLess( Max, PlaneDist );
	}

	//------------------------------------------------------------------------------
	//	A fuzzy floating point equality check
	//------------------------------------------------------------------------------
	XM_INLINE bool TestFloatEqual(const float f0,const float f1,const float tolerance)
	{
		const float f = f0 - f1;
		return ((f > (-tolerance)) && (f < tolerance));
	}

	//------------------------------------------------------------------------------
	XM_INLINE float Abs(const float a)
	{
		return (a < 0.0f) ? -a : a;
	}

	//------------------------------------------------------------------------------
	XM_INLINE float Sgn(const float a)
	{
		return (a < 0.0f) ? -1.0f : 1.0f;
	}

	//------------------------------------------------------------------------------
	XM_INLINE float Deg2Rad(float d)
	{
		return (float)((d * TURBOMATH_PI) / 180.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float Rad2Deg(float r)
	{
		return (float)((r * 180.0f) / TURBOMATH_PI);
	}

	//------------------------------------------------------------------------------
	XM_INLINE int Clamp(int val, int minVal, int maxVal)
	{
		if (val < minVal)      return minVal;
		else if (val > maxVal) return maxVal;
		else return val;
	}

	//------------------------------------------------------------------------------
	//	A fuzzy floating point less-then check.
	//------------------------------------------------------------------------------
	XM_INLINE bool TestFloatLess(float f0, float f1, float tol)
	{
		return ((f0 - f1) < tol);
	}

	//------------------------------------------------------------------------------
	//	A fuzzy floating point greater-then check.
	//------------------------------------------------------------------------------
	XM_INLINE bool TestFloatGreater(float f0, float f1, float tol)
	{
		return ((f0 - f1) > tol);
	}
	//------------------------------------------------------------------------------
	//	Clamp a value against lower und upper boundary.
	//------------------------------------------------------------------------------
	XM_INLINE float Clamp(float val, float lower, float upper)
	{
		if (val < lower)      return lower;
		else if (val > upper) return upper;
		else                  return val;
	}

	//------------------------------------------------------------------------------
	//	Saturate a value (clamps between 0.0f and 1.0f)
	//------------------------------------------------------------------------------
	XM_INLINE float Saturate(float val)
	{
		if (val < 0.0f)      return 0.0f;
		else if (val > 1.0f) return 1.0f;
		else return val;
	}

	//------------------------------------------------------------------------------
	//	Linearly interpolate between 2 values: ret = x + l * (y - x)
	//------------------------------------------------------------------------------
	XM_INLINE float Lerp(float x, float y, float l)
	{
		return x + l * (y - x);
	}

	//------------------------------------------------------------------------------
	//	Linearly interpolate between 2 values: ret = x + l * (y - x)
	//------------------------------------------------------------------------------
	XM_INLINE double n_lerp(double x, double y, double l)
	{
		return x + l * (y - x);
	}

	//------------------------------------------------------------------------------
	//	Returns true if the input float is denormalized (#DEN)
	//------------------------------------------------------------------------------
	XM_INLINE bool IsDenormal(float s)
	{
		return (((*(UINT*)&s)&0x7f800000)==0);
	}

	//------------------------------------------------------------------------------
	//	Returns 0 if float is denormal.
	//------------------------------------------------------------------------------
	XM_INLINE float Undenormalize(float s)
	{
		if (IsDenormal(s))
		{
			return 0.0f;
		}
		else
		{
			return s;
		}
	}

	//------------------------------------------------------------------------------
	//	test of nearly equal given a tolerance (epsilon)
	//------------------------------------------------------------------------------
	XM_INLINE bool NearEqual(float a, float b, float epsilon)
	{
		return Abs(a - b) <= epsilon;
	}

	//------------------------------------------------------------------------------
	//	Return a pseudo random number between 0 and 1.
	//------------------------------------------------------------------------------
	XM_INLINE float n_rand()
	{
		return float(rand()) / float(RAND_MAX);
	}

	//------------------------------------------------------------------------------
	//	Return a pseudo random number between min and max.
	//------------------------------------------------------------------------------
	XM_INLINE float Rand(float min, float max)
	{
		const float unit = (float)rand() / RAND_MAX;
		const float diff = max - min;
		return min + unit * diff;
	}

	//------------------------------------------------------------------------------
	XM_INLINE float Sqrt(float x)
	{
	#if __XBOX360__
		return __fsqrts(x);
	#else
		return sqrtf(x);
	#endif
	}

	//------------------------------------------------------------------------------
	XM_INLINE float Cot(float x)
	{
		return float(1.0) / Tan(x);
	}

	//------------------------------------------------------------------------------
	XM_INLINE int  FloatToInt( float f)
	{
		/// @todo type cast to int is slow!
		return int(f);
	}

	//------------------------------------------------------------------------------
	//	Normalize an angular value into the range rad(0) to rad(360).
	//------------------------------------------------------------------------------
	XM_INLINE float ModAngle( float a)
	{
		// we had different results for
		//   win32 release:  3.141593 == XMScalarModAngle(N_PI)
		//   win32 debug  : -3.141593 == XMScalarModAngle(N_PI)
		// so we have to map it on our own
		static const float REVOLUTION = 6.283185307179586476925286766559f;

		float ret = DirectX::XMScalarModAngle(a);

		if(ret < -TURBOMATH_PI) ret += REVOLUTION;
		if(ret >= TURBOMATH_PI) ret -= REVOLUTION;

		return ret;
	}

	//------------------------------------------------------------------------------
	//	Get angular distance.
	//------------------------------------------------------------------------------
	XM_INLINE float AngularDistance( float from, float to)
	{
		float normFrom = ModAngle(from);
		float normTo   = ModAngle(to);
		float dist = normTo - normFrom;
		if (dist < Deg2Rad(-180.0f))
		{
			dist += Deg2Rad(360.0f);
		}
		else if (dist > Deg2Rad(180.0f))
		{
			dist -= Deg2Rad(360.0f);
		}
		return dist;
	}

	//------------------------------------------------------------------------------
	//	log2() function.
	//------------------------------------------------------------------------------
	XM_INLINE float Log2( float f)
	{
		const static float LN_2 = 0.693147180559945f;

		return logf(f) / LN_2;
	}

	//------------------------------------------------------------------------------
	XM_INLINE float Exp( float x)
	{
		return expf(x);
	}

	//------------------------------------------------------------------------------
	//	Round float to integer.
	//------------------------------------------------------------------------------
	XM_INLINE int RoundFloatToInt( float f)
	{
		return FloatToInt(floorf(f + 0.5f));
	}

	//------------------------------------------------------------------------------
	XM_INLINE float Fmod( float x,  float y)
	{
		return fmodf(x, y);
	}

	//------------------------------------------------------------------------------
	XM_INLINE float Pow( float x,  float y)
	{
		return powf(x, y);
	}

	//------------------------------------------------------------------------------
	//	get logarithm of x
	//------------------------------------------------------------------------------
	XM_INLINE float Log(float x)
	{
		return logf(x);
	}

	//-----------------------------------------------------------------------------
	static XM_INLINE void FastIntersectOrientedBoxPlane( FXMVECTOR Center, FXMVECTOR Extents, FXMVECTOR Axis0, CXMVECTOR Axis1,
		CXMVECTOR Axis2, CXMVECTOR Plane, XMVECTOR& Outside, XMVECTOR& Inside )
	{
		// Compute the distance to the center of the box.
		const XMVECTOR Dist = XMVector4Dot( Center, Plane );

		// Project the axes of the box onto the normal of the plane.  Half the
		// length of the projection (sometime called the "radius") is equal to
		// h(u) * abs(n dot b(u))) + h(v) * abs(n dot b(v)) + h(w) * abs(n dot b(w))
		// where h(i) are extents of the box, n is the plane normal, and b(i) are the
		// axes of the box.
		XMVECTOR Radius = XMVector3Dot( Plane, Axis0 );
		Radius = XMVectorInsert( Radius, XMVector3Dot( Plane, Axis1 ), 0, 0, 1, 0, 0 );
		Radius = XMVectorInsert( Radius, XMVector3Dot( Plane, Axis2 ), 0, 0, 0, 1, 0 );
		Radius = XMVector3Dot( Extents, XMVectorAbs( Radius ) );

		// Outside the plane?
		Outside = XMVectorGreater( Dist, Radius );

		// Fully inside the plane?
		Inside = XMVectorLess( Dist, XMVectorNegate(Radius) );
	}

	//-----------------------------------------------------------------------------
	static XM_INLINE bool SolveCubic( const float e, const float f, const float g, float* t, float* u, float* v )
	{
		float p, q, h, rc, d, theta, costh3, sinth3;

		p = f - e * e / 3.0f;
		q = g - e * f / 3.0f + e * e * e * 2.0f / 27.0f;
		h = q * q / 4.0f + p * p * p / 27.0f;

		if( h > 0.0 )
		{
			return false; // only one real root
		}

		if( ( h == 0.0 ) && ( q == 0.0 ) ) // all the same root
		{
			*t = - e / 3;
			*u = - e / 3;
			*v = - e / 3;

			return true;
		}

		d = sqrtf( q * q / 4.0f - h );
		if( d < 0 )
			rc = -powf( -d, 1.0f / 3.0f );
		else
			rc = powf( d, 1.0f / 3.0f );

		theta = acosf( -q / ( 2.0f * d ) );
		costh3 = cosf( theta / 3.0f );
		sinth3 = sqrtf( 3.0f ) * sinf( theta / 3.0f );
		*t = 2.0f * rc * costh3 - e / 3.0f;
		*u = -rc * ( costh3 + sinth3 ) - e / 3.0f;
		*v = -rc * ( costh3 - sinth3 ) - e / 3.0f;

		return true;
	}

	//-----------------------------------------------------------------------------
	static XM_INLINE XMVECTOR CalculateEigenVector(const float m11, const float m12, const float m13,
		const float m22, const float m23, const float m33, float e )
	{
		float f1, f2, f3;

		float fTmp[3];
		fTmp[0] = ( float )( m12 * m23 - m13 * ( m22 - e ) );
		fTmp[1] = ( float )( m13 * m12 - m23 * ( m11 - e ) );
		fTmp[2] = ( float )( ( m11 - e ) * ( m22 - e ) - m12 * m12 );

		XMVECTOR vTmp = XMLoadFloat3( (XMFLOAT3*)fTmp );

		if( XMVector3Equal( vTmp, XMVectorZero() ) ) // planar or linear
		{
			// we only have one equation - find a valid one
			if( ( m11 - e != 0.0 ) || ( m12 != 0.0 ) || ( m13 != 0.0 ) )
			{
				f1 = m11 - e; f2 = m12; f3 = m13;
			}
			else if( ( m12 != 0.0 ) || ( m22 - e != 0.0 ) || ( m23 != 0.0 ) )
			{
				f1 = m12; f2 = m22 - e; f3 = m23;
			}
			else if( ( m13 != 0.0 ) || ( m23 != 0.0 ) || ( m33 - e != 0.0 ) )
			{
				f1 = m13; f2 = m23; f3 = m33 - e;
			}
			else
			{
				// error, we'll just make something up - we have NO context
				f1 = 1.0; f2 = 0.0; f3 = 0.0;
			}

			if( f1 == 0.0 )
				vTmp = XMVectorSetX( vTmp, 0.0f );
			else
				vTmp = XMVectorSetX( vTmp, 1.0f );

			if( f2 == 0.0 )
				vTmp = XMVectorSetY( vTmp, 0.0f );
			else
				vTmp = XMVectorSetY( vTmp, 1.0f );

			if( f3 == 0.0 )
			{
				vTmp = XMVectorSetZ( vTmp, 0.0f );
				// recalculate y to make equation work
				if( m12 != 0.0 )
					vTmp = XMVectorSetY( vTmp, ( float )( -f1 / f2 ) );
			}
			else
			{
				vTmp = XMVectorSetZ( vTmp, ( float )( ( f2 - f1 ) / f3 ) );
			}
		}

		if( XMVectorGetX( XMVector3LengthSq( vTmp ) ) > 1e-5f )
		{
			return XMVector3Normalize( vTmp );
		}
		else
		{
			// Multiply by a value large enough to make the vector non-zero.
			vTmp *= 1e5f;
			return XMVector3Normalize( vTmp );
		}
	}

	//-----------------------------------------------------------------------------
	static XM_INLINE bool CalculateEigenVectors( const float m11, const float m12, const float m13,
		const float m22, const float m23, const float m33,
		const float e1,  const float e2,  const float e3,
		XMVECTOR* pV1, XMVECTOR* pV2, XMVECTOR* pV3 )
	{
		XMVECTOR vTmp, vUp, vRight;

		bool v1z, v2z, v3z, e12, e13, e23;

		vUp = XMVectorSetBinaryConstant( 0, 1, 0, 0 );
		vRight = XMVectorSetBinaryConstant( 1, 0, 0, 0 );

		*pV1 = CalculateEigenVector( m11, m12, m13, m22, m23, m33, e1 );
		*pV2 = CalculateEigenVector( m11, m12, m13, m22, m23, m33, e2 );
		*pV3 = CalculateEigenVector( m11, m12, m13, m22, m23, m33, e3 );

		v1z = v2z = v3z = false;

		XMVECTOR Zero = XMVectorZero();

		if ( XMVector3Equal( *pV1, Zero ) )
			v1z = true;

		if ( XMVector3Equal( *pV2, Zero ) )
			v2z = true;

		if ( XMVector3Equal( *pV3, Zero ))
			v3z = true;

		e12 = ( fabsf( XMVectorGetX( XMVector3Dot( *pV1, *pV2 ) ) ) > 0.1f ); // check for non-orthogonal vectors
		e13 = ( fabsf( XMVectorGetX( XMVector3Dot( *pV1, *pV3 ) ) ) > 0.1f );
		e23 = ( fabsf( XMVectorGetX( XMVector3Dot( *pV2, *pV3 ) ) ) > 0.1f );

		if( ( v1z && v2z && v3z ) || ( e12 && e13 && e23 ) ||
			( e12 && v3z ) || ( e13 && v2z ) || ( e23 && v1z ) ) // all eigenvectors are 0- any basis set
		{
			*pV1 = XMVectorSetBinaryConstant( 1, 0, 0, 0 );
			*pV2 = XMVectorSetBinaryConstant( 0, 1, 0, 0 );
			*pV3 = XMVectorSetBinaryConstant( 0, 0, 1, 0 );
			return true;
		}

		if( v1z && v2z )
		{
			vTmp = XMVector3Cross( vUp, *pV3 );
			if( XMVectorGetX( XMVector3LengthSq( vTmp ) ) < 1e-5f )
			{
				vTmp = XMVector3Cross( vRight, *pV3 );
			}
			*pV1 = XMVector3Normalize( vTmp );
			*pV2 = XMVector3Cross( *pV3, *pV1 );
			return true;
		}

		if( v3z && v1z )
		{
			vTmp = XMVector3Cross( vUp, *pV2 );
			if( XMVectorGetX( XMVector3LengthSq( vTmp ) ) < 1e-5f )
			{
				vTmp = XMVector3Cross( vRight, *pV2 );
			}
			*pV3 = XMVector3Normalize( vTmp );
			*pV1 = XMVector3Cross( *pV2, *pV3 );
			return true;
		}

		if( v2z && v3z )
		{
			vTmp = XMVector3Cross( vUp, *pV1 );
			if( XMVectorGetX( XMVector3LengthSq( vTmp ) ) < 1e-5f )
			{
				vTmp = XMVector3Cross( vRight, *pV1 );
			}
			*pV2 = XMVector3Normalize( vTmp );
			*pV3 = XMVector3Cross( *pV1, *pV2 );
			return true;
		}

		if( ( v1z ) || e12 )
		{
			*pV1 = XMVector3Cross( *pV2, *pV3 );
			return true;
		}

		if( ( v2z ) || e23 )
		{
			*pV2 = XMVector3Cross( *pV3, *pV1 );
			return true;
		}

		if( ( v3z ) || e13 )
		{
			*pV3 = XMVector3Cross( *pV1, *pV2 );
			return true;
		}

		return true;
	}

	//-----------------------------------------------------------------------------
	static XM_INLINE bool CalculateEigenVectorsFromCovarianceMatrix( const float Cxx, const float Cyy, const float Czz,
		const float Cxy, const float Cxz, const float Cyz,
		XMVECTOR* pV1, XMVECTOR* pV2, XMVECTOR* pV3 )
	{
		float e, f, g, ev1, ev2, ev3;

		// Calculate the eigenvalues by solving a cubic equation.
		e = -( Cxx + Cyy + Czz );
		f = Cxx * Cyy + Cyy * Czz + Czz * Cxx - Cxy * Cxy - Cxz * Cxz - Cyz * Cyz;
		g = Cxy * Cxy * Czz + Cxz * Cxz * Cyy + Cyz * Cyz * Cxx - Cxy * Cyz * Cxz * 2.0f - Cxx * Cyy * Czz;

		if( !SolveCubic( e, f, g, &ev1, &ev2, &ev3 ) )
		{
			// set them to arbitrary orthonormal basis set
			*pV1 = XMVectorSetBinaryConstant( 1, 0, 0, 0 );
			*pV2 = XMVectorSetBinaryConstant( 0, 1, 0, 0 );
			*pV3 = XMVectorSetBinaryConstant( 0, 0, 1, 0 );
			return false;
		}

		return CalculateEigenVectors( Cxx, Cxy, Cxz, Cyy, Cyz, Czz, ev1, ev2, ev3, pV1, pV2, pV3 );
	}

	//-----------------------------------------------------------------------------
	static XM_INLINE void FastIntersectAxisAlignedBoxPlane( const AABB& Box, const Plane& Plane0,	XMVECTOR& Outside, XMVECTOR& Inside )
	{
		// Compute the distance to the center of the box.
		const XMVECTOR Dist = XMVector4Dot( Box.GetCenter(), Plane0.Get() );

		// Project the axes of the box onto the normal of the plane.  Half the
		// length of the projection (sometime called the "radius") is equal to
		// h(u) * abs(n dot b(u))) + h(v) * abs(n dot b(v)) + h(w) * abs(n dot b(w))
		// where h(i) are extents of the box, n is the plane normal, and b(i) are the
		// axes of the box. In this case b(i) = [(1,0,0), (0,1,0), (0,0,1)].
		const XMVECTOR Radius = XMVector3Dot( Box.GetExtents(), XMVectorAbs( Plane0.Get() ) );

		// Outside the plane?
		Outside = XMVectorGreater( Dist, Radius );

		// Fully inside the plane?
		Inside = XMVectorLess( Dist, XMVectorNegate(Radius ) );
	}

}; // namespace TurboMath



#endif