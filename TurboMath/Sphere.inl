
// -------------------------------------------------------------------
// File			:	Sphere.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for Sphere-Class
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
#pragma once

namespace TurboMath
{
	
	
	__forceinline void Sphere::SetCenter(const Vector4& center)
	{
		const float radius = this->Center.GetW();

		this->Center = center;

		this->Center.SetW(radius);
	}

	//------------------------------------------------------------------------------
	__forceinline const Vector4 Sphere::GetCenter() const
	{
		return this->Center;
	}

	//------------------------------------------------------------------------------
	__forceinline void Sphere::SetRadius(const float radius)
	{
		this->Center.SetW(radius);
	}

	//------------------------------------------------------------------------------
	__forceinline const float Sphere::GetRadius() const
	{
		return this->Center.GetW();
	}

	//------------------------------------------------------------------------------
	__forceinline void Sphere::Set(const Vector4& center, const float radius)
	{
		this->Center = center;
		this->Center.SetW(radius);
	}

	//------------------------------------------------------------------------------
	__forceinline  const bool Sphere::operator == (const Sphere& s) const
	{
		return this->GetCenter() == s.GetCenter() || this->GetRadius() == s.GetRadius();
	}

	//------------------------------------------------------------------------------
	__forceinline  const bool Sphere::operator != (const Sphere& s) const
	{
		return this->GetCenter() != s.GetCenter() || this->GetRadius() != s.GetRadius();
	}

	//------------------------------------------------------------------------------
	__forceinline  const bool Sphere::IsEmpty()
	{ 
		return this->GetRadius() <= TURBOMATH_EPSILON;
	}

	//-----------------------------------------------------------------------------
	// Find the approximate smallest enclosing bounding sphere for a set of
	// points. Exact computation of the smallest enclosing bounding sphere is
	// possible but is slower and requires a more complex algorithm.
	// The algorithm is based on  Jack Ritter, "An Efficient Bounding Sphere",
	// Graphics Gems.
	//-----------------------------------------------------------------------------
	_inline void	Sphere::ComputeBoundingSphereFromPoints(const UINT Count, Vector4* pPoints, const UINT Stride )
	{
		assert( Count > 0 );
		assert( pPoints );

		// Find the points with minimum and maximum x, y, and z
		XMVECTOR MinX, MaxX, MinY, MaxY, MinZ, MaxZ;

		MinX = MaxX = MinY = MaxY = MinZ = MaxZ = XMLoadFloat3( (XMFLOAT3*)&pPoints->GetRaw() );

		for( UINT i = 1; i < Count; i++ )
		{
			const XMVECTOR Point = XMLoadFloat3( ( XMFLOAT3* )( ( char* )pPoints + i * Stride ) );

			const float px = XMVectorGetX( Point );
			const float py = XMVectorGetY( Point );
			const float pz = XMVectorGetZ( Point );

			if( px < XMVectorGetX( MinX ) )
				MinX = Point;

			if( px > XMVectorGetX( MaxX ) )
				MaxX = Point;

			if( py < XMVectorGetY( MinY ) )
				MinY = Point;

			if( py > XMVectorGetY( MaxY ) )
				MaxY = Point;

			if( pz < XMVectorGetZ( MinZ ) )
				MinZ = Point;

			if( pz > XMVectorGetZ( MaxZ ) )
				MaxZ = Point;
		}

		// Use the min/max pair that are farthest apart to form the initial sphere.
		const XMVECTOR DeltaX = XMVectorSubtract(MaxX , MinX);
		const XMVECTOR DistX = XMVector3Length( DeltaX );

		const XMVECTOR DeltaY = XMVectorSubtract(MaxY , MinY);
		const XMVECTOR DistY = XMVector3Length( DeltaY );

		const XMVECTOR DeltaZ = XMVectorSubtract(MaxZ , MinZ);
		const XMVECTOR DistZ = XMVector3Length( DeltaZ );

		XMVECTOR Center;
		XMVECTOR Radius;

		if( XMVector3Greater( DistX, DistY ) )
		{
			if( XMVector3Greater( DistX, DistZ ) )
			{
				// Use min/max x.
				Center = XMVectorMultiply(XMVectorAdd(MaxX , MinX)  ,  XMVectorReplicate( 0.5f ));
				Radius = XMVectorMultiply(DistX , XMVectorReplicate( 0.5f ));
			}
			else
			{
				// Use min/max z.
				Center = XMVectorMultiply(XMVectorAdd(MaxZ , MinZ) , XMVectorReplicate(0.5f) );
				Radius = XMVectorMultiply(DistZ , XMVectorReplicate(0.5f) );
			}
		}
		else // Y >= X
		{
			if( XMVector3Greater( DistY, DistZ ) )
			{
				// Use min/max y.
				Center = XMVectorMultiply( XMVectorAdd( MaxY , MinY ) , XMVectorReplicate(0.5f) );
				Radius = XMVectorMultiply( DistY , XMVectorReplicate(0.5f) );
			}
			else
			{
				// Use min/max z.
				Center = XMVectorMultiply( XMVectorAdd(MaxZ , MinZ ) , XMVectorReplicate(0.5f) );
				Radius = XMVectorMultiply(DistZ , XMVectorReplicate(0.5f));
			}
		}

		// Add any points not inside the sphere.
		for( UINT i = 0; i < Count; i++ )
		{
			const XMVECTOR Point = XMLoadFloat3( ( XMFLOAT3* )( ( char* )pPoints + i * Stride ) );

			const XMVECTOR Delta = XMVectorSubtract(Point , Center);

			const XMVECTOR Dist = XMVector3Length( Delta );

			if( XMVector3Greater( Dist, Radius ) )
			{
				// Adjust sphere to include the new point.
				Radius = XMVectorMultiply( XMVectorAdd( Radius , Dist ) , XMVectorReplicate(0.5f) );
				Center += XMVectorMultiply( XMVectorMultiply( XMVectorSubtract( XMVectorReplicate( 1.0f ) , Radius ) , XMVectorReciprocal( Dist ) ) , Delta);
			}
		}

		this->Center = Center;
		float rad = this->GetRadius();
		XMStoreFloat( &rad, Radius );

		return;
	}

	//-----------------------------------------------------------------------------
	// Transform a sphere by an angle preserving transform.
	//-----------------------------------------------------------------------------
	__forceinline void	Sphere::Transform( const Sphere* pIn, const float Scale,const Quat& Rotation, const Vector4& Translation )
	{
		assert( pIn );
		assert( Rotation.IsUnit() );

		// Load the center of the sphere.
		XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&pIn->Center );

		// Transform the center of the sphere.
		Center = XMVectorAdd(XMVector3Rotate( XMVectorMultiply(Center , XMVectorReplicate( Scale )) , Rotation.Get() ) , Translation);

		// Store the center sphere.
		XMStoreFloat3( (XMFLOAT3*)&this->Center, Center );

		// Scale the radius of the pshere.
		this->SetRadius( pIn->GetRadius() * Scale );

		return;
	}

	//-----------------------------------------------------------------------------
	// Intersection testing routines.
	//-----------------------------------------------------------------------------
	__forceinline const bool	Sphere::IntersectPoint( const Vector4& Point)
	{
		const XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const float rad = this->GetRadius();
		const XMVECTOR Radius = XMVectorReplicatePtr( &rad );

		const XMVECTOR DistanceSquared = XMVector3LengthSq( XMVectorSubtract( Point.GetRaw() , Center ) );
		const XMVECTOR RadiusSquared = XMVectorMultiply(Radius , Radius);

		return XMVector4LessOrEqual( DistanceSquared, RadiusSquared );
	}

	//------------------------------------------------------------------------------
	__forceinline const bool	Sphere::IntersectRay(  const Ray& theRay, float* pDist  )
	{
		assert( pDist );
		assert( theRay.GetDirection().IsUnit() );

		const XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const float rad = this->GetRadius();
		const XMVECTOR Radius = XMVectorReplicatePtr( &rad );

		// l is the vector from the ray origin to the center of the sphere.
		const XMVECTOR l = XMVectorSubtract(Center , theRay.GetStartPoint());

		// s is the projection of the l onto the ray direction.
		const XMVECTOR s = XMVector3Dot( l, theRay.GetDirection() );

		const XMVECTOR l2 = XMVector3Dot( l, l );

		const XMVECTOR r2 = XMVectorMultiply(Radius , Radius);

		// m2 is squared distance from the center of the sphere to the projection.
		const XMVECTOR m2 = XMVectorSubtract(l2 , XMVectorMultiply(s , s));

		XMVECTOR NoIntersection;

		// If the ray origin is outside the sphere and the center of the sphere is
		// behind the ray origin there is no intersection.
		NoIntersection = XMVectorAndInt( XMVectorLess( s, XMVectorZero() ), XMVectorGreater( l2, r2 ) );

		// If the squared distance from the center of the sphere to the projection
		// is greater than the radius squared the ray will miss the sphere.
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( m2, r2 ) );

		// The ray hits the sphere, compute the nearest intersection point.
		const XMVECTOR q = XMVectorSqrt( XMVectorSubtract(r2 , m2) );
		const XMVECTOR t1 = XMVectorSubtract(s , q);
		const XMVECTOR t2 = XMVectorAdd(s , q);

		const XMVECTOR OriginInside = XMVectorLessOrEqual( l2, r2 );
		const XMVECTOR t = XMVectorSelect( t1, t2, OriginInside );

		if( XMVector4NotEqualInt( NoIntersection, XMVectorTrueInt() ) )
		{
			// Store the x-component to *pDist.
			XMStoreFloat( pDist, t );
			return true;
		}

		return false;
	}

	//------------------------------------------------------------------------------
	__forceinline const bool	Sphere::IntersectTriangle( const Vector4& V0, const Vector4& V1, const Vector4& V2)
	{
		// Load the sphere.
		const XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center.GetRaw() );
		const float rad = this->GetRadius();
		const XMVECTOR Radius = XMVectorReplicatePtr( &rad );

		// Compute the plane of the triangle (has to be normalized).
		const XMVECTOR N = XMVector3Normalize( XMVector3Cross( (V1 - V0).GetRaw(),  (V2 - V0).GetRaw() )  );

		// Assert that the triangle is not degenerate.
		assert( !XMVector3Equal( N, XMVectorZero() ) );

		// Find the nearest feature on the triangle to the sphere.
		const XMVECTOR Dist = XMVector3Dot( XMVectorSubtract(Center , V0.GetRaw()) , N );

		// If the center of the sphere is farther from the plane of the triangle than
		// the radius of the sphere, then there cannot be an intersection.
		XMVECTOR NoIntersection = XMVectorLess( Dist, XMVectorNegate(Radius) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( Dist, Radius ) );

		// Project the center of the sphere onto the plane of the triangle.
		XMVECTOR Point = XMVectorSubtract(Center ,( XMVectorMultiply(N , Dist) ) );

		// Is it inside all the edges? If so we intersect because the distance
		// to the plane is less than the radius.
		XMVECTOR Intersection = PointOnPlaneInsideTriangle( Point, V0, V1, V2 ).GetRaw();

		// Find the nearest point on each edge.
		const XMVECTOR RadiusSq = XMVectorMultiply(Radius , Radius);

		// Edge 0,1
		Line tmpLine;
		Vector4 tmpCenter(Center);

		tmpLine.Set(V0,V1);
		Point = tmpLine.PointOnLineSegmentNearestPoint( tmpCenter ).GetRaw();

		// If the distance to the center of the sphere to the point is less than
		// the radius of the sphere then it must intersect.
		Intersection = XMVectorOrInt( Intersection, XMVectorLessOrEqual( XMVector3LengthSq( XMVectorSubtract(Center , Point) ), RadiusSq ) );

		// Edge 1,2
		tmpLine.Set(V1,V2);
		Point = tmpLine.PointOnLineSegmentNearestPoint( tmpCenter ).GetRaw();

		// If the distance to the center of the sphere to the point is less than
		// the radius of the sphere then it must intersect.
		Intersection = XMVectorOrInt( Intersection, XMVectorLessOrEqual( XMVector3LengthSq( XMVectorSubtract(Center , Point) ), RadiusSq ) );

		// Edge 2,0
		tmpLine.Set(V2,V0);
		Point = tmpLine.PointOnLineSegmentNearestPoint(tmpCenter ).GetRaw();

		// If the distance to the center of the sphere to the point is less than
		// the radius of the sphere then it must intersect.
		Intersection = XMVectorOrInt( Intersection, XMVectorLessOrEqual( XMVector3LengthSq( XMVectorSubtract(Center , Point) ), RadiusSq ) );

		return XMVector4EqualInt( XMVectorAndCInt( Intersection, NoIntersection ), XMVectorTrueInt() );
	}

	//------------------------------------------------------------------------------
	__forceinline const bool	Sphere::IntersectSphere( const Sphere* pVolumeA)
	{
		assert( pVolumeA );

		// Load A.
		const XMVECTOR CenterA = XMLoadFloat3( (XMFLOAT3*)&pVolumeA->Center );
		const float radA = pVolumeA->GetRadius();
		const XMVECTOR RadiusA = XMVectorReplicatePtr( &radA );

		// Load B.
		const XMVECTOR CenterB = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const float radB = this->GetRadius();
		const XMVECTOR RadiusB = XMVectorReplicatePtr( &radB );

		// Distance squared between centers.
		const XMVECTOR Delta = XMVectorSubtract(CenterB , CenterA);
		const XMVECTOR DistanceSquared = XMVector3LengthSq( Delta );

		// Sum of the radii sqaured.
		XMVECTOR RadiusSquared = XMVectorAdd(RadiusA , RadiusB);
		RadiusSquared = XMVectorMultiply(RadiusSquared , RadiusSquared);

		return XMVector4LessOrEqual( DistanceSquared, RadiusSquared );
	}

	//------------------------------------------------------------------------------
	__forceinline const bool	Sphere::IntersectAABB( const AABB* pVolumeB )
	{
		assert( pVolumeB );

		const XMVECTOR SphereCenter = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const float rad = this->GetRadius();
		const XMVECTOR SphereRadius = XMVectorReplicatePtr( &rad );

		const XMVECTOR BoxCenter = XMLoadFloat3( (XMFLOAT3*)&pVolumeB->GetCenter() );
		const XMVECTOR BoxExtents = XMLoadFloat3( (XMFLOAT3*)&pVolumeB->GetExtents() );

		const XMVECTOR BoxMin = XMVectorSubtract(BoxCenter , BoxExtents);
		const XMVECTOR BoxMax = XMVectorAdd(BoxCenter , BoxExtents);

		// Find the distance to the nearest point on the box.
		// for each i in (x, y, z)
		// if (SphereCenter(i) < BoxMin(i)) d2 += (SphereCenter(i) - BoxMin(i)) ^ 2
		// else if (SphereCenter(i) > BoxMax(i)) d2 += (SphereCenter(i) - BoxMax(i)) ^ 2

		XMVECTOR d = XMVectorZero();

		// Compute d for each dimension.
		const XMVECTOR LessThanMin = XMVectorLess( SphereCenter, BoxMin );
		const XMVECTOR GreaterThanMax = XMVectorGreater( SphereCenter, BoxMax );

		const XMVECTOR MinDelta = XMVectorSubtract(SphereCenter , BoxMin);
		const XMVECTOR MaxDelta = XMVectorSubtract(SphereCenter , BoxMax);

		// Choose value for each dimension based on the comparison.
		d = XMVectorSelect( d, MinDelta, LessThanMin );
		d = XMVectorSelect( d, MaxDelta, GreaterThanMax );

		// Use a dot-product to square them and sum them together.
		const XMVECTOR d2 = XMVector3Dot( d, d );

		return XMVector4LessOrEqual( d2, XMVectorMultiply( SphereRadius, SphereRadius ) );
	}

	//------------------------------------------------------------------------------
	__forceinline const bool	Sphere::IntersectOBB(const OBB* pVolumeB )
	{
		assert( pVolumeB );

		XMVECTOR SphereCenter = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const float rad = this->GetRadius();
		const XMVECTOR SphereRadius = XMVectorReplicatePtr( &rad );

		const XMVECTOR BoxCenter = XMLoadFloat3( (XMFLOAT3*)&pVolumeB->GetCenter() );
		const XMVECTOR BoxExtents = XMLoadFloat3( (XMFLOAT3*)&pVolumeB->GetExtents() );
		const XMVECTOR BoxOrientation = XMLoadFloat4( (XMFLOAT4*)&pVolumeB->GetOrientation() );

		assert( Quat::IsUnit( BoxOrientation ) );

		// Transform the center of the sphere to be local to the box.
		// BoxMin = -BoxExtents
		// BoxMax = +BoxExtents
		SphereCenter = XMVector3InverseRotate( XMVectorSubtract(SphereCenter , BoxCenter), BoxOrientation );

		// Find the distance to the nearest point on the box.
		// for each i in (x, y, z)
		// if (SphereCenter(i) < BoxMin(i)) d2 += (SphereCenter(i) - BoxMin(i)) ^ 2
		// else if (SphereCenter(i) > BoxMax(i)) d2 += (SphereCenter(i) - BoxMax(i)) ^ 2

		XMVECTOR d = XMVectorZero();

		// Compute d for each dimension.
		const XMVECTOR LessThanMin = XMVectorLess( SphereCenter, XMVectorNegate(BoxExtents) );
		const XMVECTOR GreaterThanMax = XMVectorGreater( SphereCenter, BoxExtents );

		const XMVECTOR MinDelta = XMVectorAdd(SphereCenter , BoxExtents);
		const XMVECTOR MaxDelta = XMVectorSubtract(SphereCenter , BoxExtents);

		// Choose value for each dimension based on the comparison.
		d = XMVectorSelect( d, MinDelta, LessThanMin );
		d = XMVectorSelect( d, MaxDelta, GreaterThanMax );

		// Use a dot-product to square them and sum them together.
		const XMVECTOR d2 = XMVector3Dot( d, d );

		return XMVector4LessOrEqual( d2, XMVectorMultiply( SphereRadius, SphereRadius ) );
	}

	//-----------------------------------------------------------------------------
	// Volume vs plane intersection testing routines.
	// Return values: 0 = volume is outside the plane (on the positive sideof the plane),
	//                1 = volume intersects the plane,
	//                2 = volume is inside the plane (on the negative side of the plane)
	//-----------------------------------------------------------------------------
	__forceinline const eCullClassify	Sphere::IntersectFrustum( Frustum* pVolumeB )
	{
		assert(pVolumeB);

		return pVolumeB->IntersectSphere(*this);
	}

	//------------------------------------------------------------------------------
	__forceinline const eCullClassify	Sphere::Intersect6Planes( const Plane& Plane0, const Plane& Plane1, const Plane& Plane2,const Plane& Plane3, const Plane& Plane4, const Plane& Plane5 )
	{
		// Load the sphere.
		XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const float rad = this->GetRadius();
		const XMVECTOR Radius = XMVectorReplicatePtr( &rad );

		// Set w of the center to one so we can dot4 with a plane.
		Center = XMVectorInsert( Center, XMVectorSplatOne(), 0, 0, 0, 0, 1);

		XMVECTOR Outside, Inside;

		// Test against each plane.
		FastIntersectSpherePlane( Vector4(Center), Vector4(Radius), Plane0, Outside, Inside );

		XMVECTOR AnyOutside = Outside;
		XMVECTOR AllInside = Inside;

		FastIntersectSpherePlane( Vector4(Center), Vector4(Radius), Plane1, Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectSpherePlane( Vector4(Center), Vector4(Radius), Plane2, Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectSpherePlane( Vector4(Center), Vector4(Radius), Plane3, Outside, Inside);
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectSpherePlane( Vector4(Center), Vector4(Radius), Plane4, Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectSpherePlane( Vector4(Center), Vector4(Radius), Plane5, Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		// If the sphere is outside any plane it is outside.
		if ( XMVector4EqualInt( AnyOutside, XMVectorTrueInt() ) )
			return CULLED;

		// If the sphere is inside all planes it is inside.
		if ( XMVector4EqualInt( AllInside, XMVectorTrueInt() ) )
			return VISIBLE;

		// The sphere is not inside all planes or outside a plane, it may intersect.
		return CLIPPED;
	}

	//------------------------------------------------------------------------------
	__forceinline const eCullClassify	Sphere::IntersectPlane( const Plane& Plane )
	{
		assert(  Plane.IsUnit()  );

		// Load the sphere.
		XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const float rad = this->GetRadius();
		const XMVECTOR Radius = XMVectorReplicatePtr( &rad );

		// Set w of the center to one so we can dot4 with a plane.
		Center = XMVectorInsert( Center, XMVectorSplatOne(), 0, 0, 0, 0, 1 );

		XMVECTOR Outside, Inside;
		FastIntersectSpherePlane( Vector4(Center), Vector4(Radius), Plane, Outside, Inside );

		// If the sphere is outside any plane it is outside.
		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED;

		// If the sphere is inside all planes it is inside.
		if ( XMVector4EqualInt( Inside, XMVectorTrueInt() ) )
			return VISIBLE;

		// The sphere is not inside all planes or outside a plane it intersects.
		return CLIPPED;
	}

}// end of Namespace TurboMath