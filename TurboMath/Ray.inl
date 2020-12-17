
// -------------------------------------------------------------------
// File			:	Ray.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for Ray-Class
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


namespace TurboMath
{
	
	//------------------------------------------------------------------------------
	__forceinline Ray::Ray()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline Ray::Ray(const Vector4& startPoint, const Vector4& direction) :
	orig(startPoint),
	dir(direction)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline Ray::Ray(const Ray& rhs) :
	orig(rhs.orig),
	dir(rhs.dir)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline void Ray::Set(const Vector4& startPoint, const Vector4& direction)
	{
		this->orig = startPoint;
		this->dir = direction;
	}

	//------------------------------------------------------------------------------
	__forceinline void Ray::SetStartPoint(const Vector4& startPoint)
	{
		this->orig = startPoint;
	}

	//------------------------------------------------------------------------------
	__forceinline void Ray::SetDirection(const Vector4& direction)
	{
		this->dir = direction;
	}

	//------------------------------------------------------------------------------
	__forceinline const Vector4& Ray::GetStartPoint() const
	{
		return this->orig;
	}

	//------------------------------------------------------------------------------
	__forceinline Vector4 Ray::GetDirection() const
	{
		return this->dir;
	}

	//------------------------------------------------------------------------------
	__forceinline void Ray::SetLength(const float l)
	{
		Normalize();
		this->dir = this->dir * l;;
	}

	//------------------------------------------------------------------------------
	__forceinline const float Ray::GetLength() const
	{
		return this->dir.Length();
	}

	//------------------------------------------------------------------------------
	__forceinline void Ray::Normalize()
	{
		this->dir = Vector4::Normalize(this->dir);
	}

	//------------------------------------------------------------------------------
	__forceinline void Ray::CopyOf(const Ray& cpyRay)
	{
		this->dir = cpyRay.GetDirection();
		this->orig = cpyRay.GetStartPoint();
	}

	//------------------------------------------------------------------------------
	// assignment operator
	__forceinline void Ray::operator=(const Ray& rhs)
	{
		this->dir = rhs.GetDirection();
		this->orig = rhs.GetStartPoint();
	}


	_inline const bool	Ray::IntersectTriangle( const Vector4& V0, const Vector4& V1, const Vector4& V2,float* pDist) const
	{
		//-----------------------------------------------------------------------------
		// Compute the intersection of a ray (Origin, Direction) with a triangle
		// (V0, V1, V2).  Return TRUE if there is an intersection and also set *pDist
		// to the distance along the ray to the intersection.
		//
		// The algorithm is based on Moller, Tomas and Trumbore, "Fast, Minimum Storage
		// Ray-Triangle Intersection", Journal of Graphics Tools, vol. 2, no. 1,
		// pp 21-28, 1997.
		//-----------------------------------------------------------------------------

		assert(pDist);

		static const XMVECTOR Epsilon =
		{
			1e-20f, 1e-20f, 1e-20f, 1e-20f
		};

		const XMVECTOR Zero = XMVectorZero();

		const XMVECTOR e1 = XMVectorSubtract(V1.GetRaw() , V0.GetRaw());
		const XMVECTOR e2 = XMVectorSubtract(V2.GetRaw() , V0.GetRaw());

		// p = Direction ^ e2;
		const XMVECTOR p = XMVector3Cross( this->dir.GetRaw(), e2 );

		// det = e1 * p;
		const XMVECTOR det = XMVector3Dot( e1, p );

		XMVECTOR u, v, t;

		if( XMVector3GreaterOrEqual( det, Epsilon ) )
		{
			// Determinate is positive (front side of the triangle).
			const XMVECTOR s = (this->orig - V0).GetRaw();

			// u = s * p;
			u = XMVector3Dot( s, p );

			XMVECTOR NoIntersection = XMVectorLess( u, Zero );
			NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( u, det ) );

			// q = s ^ e1;
			const XMVECTOR q = XMVector3Cross( s, e1 );

			// v = Direction * q;
			v = XMVector3Dot( this->dir.GetRaw(), q );

			NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( v, Zero ) );
			NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( XMVectorAdd(u , v), det ) );

			// t = e2 * q;
			t = XMVector3Dot( e2, q );

			NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( t, Zero ) );

			if( XMVector4EqualInt( NoIntersection, XMVectorTrueInt() ) )
				return false;
		}
		else if( XMVector3LessOrEqual( det, XMVectorNegate(Epsilon) ) )
		{
			// Determinate is negative (back side of the triangle).
			const XMVECTOR s = (this->orig - V0).GetRaw();

			// u = s * p;
			u = XMVector3Dot( s, p );

			XMVECTOR NoIntersection = XMVectorGreater( u, Zero );
			NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( u, det ) );

			// q = s ^ e1;
			const XMVECTOR q = XMVector3Cross( s, e1 );

			// v = Direction * q;
			v = XMVector3Dot( this->dir.GetRaw(), q );

			NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( v, Zero ) );
			NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( XMVectorAdd(u , v), det ) );

			// t = e2 * q;
			t = XMVector3Dot( e2, q );

			NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( t, Zero ) );

			if ( XMVector4EqualInt( NoIntersection, XMVectorTrueInt() ) )
				return false;
		}
		else
		{
			// Parallel ray.
			return false;
		}

		const XMVECTOR inv_det = XMVectorReciprocal( det );

		t *= inv_det;

		// u * inv_det and v * inv_det are the barycentric cooridinates of the intersection.

		// Store the x-component to *pDist
		XMStoreFloat( pDist, t );

		return true;
	}

	__forceinline const bool	Ray::IntersectTriangle( const Vector4& V0, const Vector4& V1, const Vector4& V2,float length ,float* pDist) const
	{
		const bool ret = IntersectTriangle(V0,V1,V2,pDist);

		if ( *pDist > length) return false;

		return ret;
	}

	__forceinline const bool	Ray::IntersectSphere( Sphere* pVolumeA,float* pDist) const
	{
		assert(pVolumeA);
		assert(pDist);

		return pVolumeA->IntersectRay(*this,pDist);
	}

	__forceinline const bool	Ray::IntersectSphere( Sphere* pVolumeA, float length, float* pDist) const
	{
		assert(pVolumeA);
		assert(pDist);

		const bool ret = pVolumeA->IntersectRay(*this,pDist);

		if ( *pDist > length) return false;

		return ret;
	}

	__forceinline const bool	Ray::IntersectAABB( AABB* pVolumeB,float* pDist ) const
	{
		assert(pVolumeB);
		assert(pDist);

		return pVolumeB->IntersectRay(*this,pDist);
	}

	__forceinline const bool	Ray::IntersectAABB( AABB* pVolumeB, float length ,float* pDist ) const
	{
		assert(pVolumeB);
		assert(pDist);

		const bool ret = pVolumeB->IntersectRay(*this,pDist);

		if ( *pDist > length) return false;

		return ret;
	}

	__forceinline const bool	Ray::IntersectOBB( OBB* pVolumeB,float* pDist )
	{
		assert(pVolumeB);
		assert(pDist);

		return pVolumeB->IntersectRay(*this,pDist);
	}

	__forceinline const bool	Ray::IntersectOBB( OBB* pVolumeB, float length, float* pDist ) 
	{
		assert(pVolumeB);
		assert(pDist);

		const bool ret = pVolumeB->IntersectRay(*this,pDist);

		if ( *pDist > length) return false;

		return ret;
	}

	__forceinline void Ray::DeTransform(const Matrix& _m)
	{
		Matrix	mInv,m;

		m	= _m;

		orig.SetX(	-  m.GetRow3().GetX() );		// m41 -> Verschiebung aus der Matrix entfernen
		orig.SetY( -  m.GetRow3().GetY() );		// m 42und speichern
		orig.SetZ(	-  m.GetRow3().GetZ() );

		m.SetRow3(Vector4(0,0,0));

		mInv = m.Inverse(m);
		orig	= orig	* mInv;
		dir		= dir	* mInv;
	}

	__forceinline const bool Ray::IntersectPlane( const Plane& plane,float* pDist, Vector4* vHit) const
	{
		const float Vd = Vector4::Dot( plane.GetNormal(), dir);

		const float EPSILON	 = 0.00001f;

		if ( fabs(Vd) < EPSILON) return false;

		const float Vo = - ((Vector4::Dot( plane.GetNormal(), orig)) + plane.GetD() );

		const float _t = Vo / Vd;

		if (_t < 0.0f) return false;

		if (vHit)
		{
			(*vHit) = orig + (dir * _t);
		}

		if (pDist)	*pDist = _t;

		return true;
	}

	__forceinline const bool	Ray::IntersectPlane( const Plane& plane,float length, float* pDist, Vector4* vHit) const
	{
		const float EPSILON	 = 0.00001f;

		const float Vd = Vector4::Dot( plane.GetNormal(), dir);
		
		if ( fabs(Vd) < EPSILON) return false;

		const float Vo = - ((Vector4::Dot( plane.GetNormal(), orig)) + plane.GetD() );

		const float _t = Vo / Vd;

		if ((_t < 0.0f) || (_t > length)) return false;

		if (vHit)
		{
			(*vHit) = orig + ( dir * _t);
		}

		if (pDist)	*pDist = _t;

		return true;
	}

}// end of Namespace TurboMath
