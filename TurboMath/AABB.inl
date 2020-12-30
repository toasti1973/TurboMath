
// -------------------------------------------------------------------
// File			:	AABB.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for AABB-Class
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

	XM_INLINE AABB::AABB(const Vector4& c,const Vector4& e) noexcept
		: Center(c),Extents(e)
	{
	}

	XM_INLINE AABB::AABB() noexcept
	{
		Reset();
	}

	XM_INLINE AABB::AABB( OBB& o ) noexcept
	{
		Vector4 tmp[8];

		o.GetEdgePoints(&tmp[0]);

		this->ComputeBoundingAABBFromPoints(8, &tmp[0],4);
	}

	
	XM_INLINE void XM_CALLCONV	AABB::Set(const Vector4& c, const Vector4& e)  noexcept
	{
		Center = c;
		Extents = e;
	}

	XM_INLINE void XM_CALLCONV	AABB::SetCenter(const Vector4& c) noexcept
	{
		Center = c;
	}

	XM_INLINE void XM_CALLCONV	AABB::SetExtents(const Vector4& e) noexcept
	{
		Extents = e;
	}

	XM_INLINE const Vector4 XM_CALLCONV	AABB::GetCenter() const noexcept
	{
		return Center;
	}

	XM_INLINE const Vector4 XM_CALLCONV	AABB::GetExtents() const noexcept
	{
		return Extents;
	}

	XM_INLINE const Vector4 XM_CALLCONV	AABB::GetMinExtents() const noexcept
	{
		return Center - Extents;
	}

	XM_INLINE const Vector4 XM_CALLCONV	AABB::GetMaxExtents() const noexcept
	{
		return Center + Extents;
	}

	void XM_CALLCONV	AABB::SetMinMaxExtents(const Vector4& vMin, const Vector4& vMax)  noexcept
	{
		Center = (vMin + vMax) * 0.5f;
		Extents = (vMax - vMin) * 0.5f;

		float tmp = Extents.GetX();
		if (tmp < 0)
		{
			tmp = -tmp;
			Extents.SetX(tmp);
		}

		tmp = Extents.GetY();
		if (tmp < 0)
		{
			tmp = -tmp;
			Extents.SetY(tmp);
		}

		tmp = Extents.GetZ();
		if (tmp < 0)
		{
			tmp = -tmp;
			Extents.SetZ(tmp);
		}
	}

	XM_INLINE void XM_CALLCONV	AABB::Reset()  noexcept
	{
		Center = Vector4::NullVec();
		Extents = Vector4::NullVec();
	}

	XM_INLINE const bool XM_CALLCONV	AABB::IsReset() const  noexcept
	{
		return (Extents == Vector4::NullVec() );
	}

	XM_INLINE const float XM_CALLCONV	AABB::GetVolume() const noexcept
	{
		if (IsReset()) return 0.0f;			// empty -> no Volume

		const Vector4 min = GetMinExtents();
		const Vector4 max = GetMaxExtents();

		return max.GetX()-min.GetX() * max.GetY()-min.GetY() * max.GetZ()-min.GetZ();
	}

	XM_INLINE void XM_CALLCONV	AABB::Move(const Vector4& vec)  noexcept
	{
		if (!IsReset())
		{
			Center += vec;
		}
	}


	const Vector4 XM_CALLCONV	AABB::GetPoint(const int index) const noexcept
	{
		switch(index)
		{
			case 0: return Vector4( Center.GetX() - Extents.GetX(), Center.GetY() - Extents.GetY(), Center.GetZ() - Extents.GetZ() );
			case 1: return Vector4( Center.GetX() + Extents.GetX(), Center.GetY() - Extents.GetY(), Center.GetZ() - Extents.GetZ() );
			case 2: return Vector4( Center.GetX() - Extents.GetX(), Center.GetY() + Extents.GetY(), Center.GetZ() - Extents.GetZ() );
			case 3: return Vector4( Center.GetX() + Extents.GetX(), Center.GetY() + Extents.GetY(), Center.GetZ() - Extents.GetZ() );
			case 4: return Vector4( Center.GetX() - Extents.GetX(), Center.GetY() - Extents.GetY(), Center.GetZ() + Extents.GetZ() );
			case 5: return Vector4( Center.GetX() + Extents.GetX(), Center.GetY() - Extents.GetY(), Center.GetZ() + Extents.GetZ() );
			case 6: return Vector4( Center.GetX() - Extents.GetX(), Center.GetY() + Extents.GetY(), Center.GetZ() + Extents.GetZ() );
			case 7: return Vector4( Center.GetX() + Extents.GetX(), Center.GetY() + Extents.GetY(), Center.GetY() + Extents.GetZ() );
			default: return Vector4::NullVec();
		}
	}

	const Vector4 XM_CALLCONV	AABB::GetVertexNormal( const int index) const noexcept
	{
		switch(index) 
		{
			case 0: return Vector4(-0.57735026919f, -0.57735026919f, -0.57735026919f);
			case 1: return Vector4(+0.57735026919f, -0.57735026919f, -0.57735026919f);
			case 2: return Vector4(-0.57735026919f, +0.57735026919f, -0.57735026919f);
			case 3: return Vector4(+0.57735026919f, +0.57735026919f, -0.57735026919f);
			case 4: return Vector4(-0.57735026919f, -0.57735026919f, +0.57735026919f);
			case 5: return Vector4(+0.57735026919f, -0.57735026919f, +0.57735026919f);
			case 6: return Vector4(-0.57735026919f, +0.57735026919f, +0.57735026919f);
			case 7: return Vector4(+0.57735026919f, +0.57735026919f, +0.57735026919f);
			default: return Vector4::NullVec();
		}
	}

	const Vector4 XM_CALLCONV	AABB::GetFaceNormal( const ePlane which) const noexcept
	{
		switch(which) 
		{
			case LEFT_PLANE:	return Vector4(-1,  0,  0);
			case RIGHT_PLANE:	return Vector4( 1,  0,  0);
			case BOTTOM_PLANE:	return Vector4( 0, -1,  0);
			case TOP_PLANE:		return Vector4( 0,  1,  0);
			case NEAR_PLANE:	return Vector4( 0,  0, -1);
			case FAR_PLANE:		return Vector4( 0,  0,  1);
			default: return Vector4::NullVec();
		}
	}

	const Plane XM_CALLCONV	AABB::GetPlane(const ePlane which) const noexcept
	{
		Plane plane;

		switch(which) 
		{
			case 0: plane.Set(Vector4(Center.GetX() - Extents.GetX(), 0, 0), GetFaceNormal(which));
			case 1: plane.Set(Vector4(Center.GetX() + Extents.GetX(), 0, 0), GetFaceNormal(which));
			case 2: plane.Set(Vector4(0, Center.GetY() - Extents.GetY(), 0), GetFaceNormal(which));
			case 3: plane.Set(Vector4(0, Center.GetY() + Extents.GetY(), 0), GetFaceNormal(which));
			case 4: plane.Set(Vector4(0, 0, Center.GetZ() - Extents.GetZ()), GetFaceNormal(which));
			case 5: plane.Set(Vector4(0, 0, Center.GetZ() + Extents.GetZ()), GetFaceNormal(which));
			default: plane = Plane(0, 0, 0, 0);
		}
		return plane;
	}

	XM_INLINE  bool XM_CALLCONV	AABB::operator == (const AABB& box) const noexcept
	{
		return this->Center == box.Center && this->Extents == box.Extents;
	}


	XM_INLINE  bool XM_CALLCONV	AABB:: operator != (const AABB& box) const noexcept
	{
		return this->Center != box.Center || this->Extents != box.Extents;
	}



	
	//-----------------------------------------------------------------------------
	// Find the minimum axis aligned bounding box containing a set of points.
	//-----------------------------------------------------------------------------
	void XM_CALLCONV	AABB::ComputeBoundingAABBFromPoints(UINT Count, Vector4* pPoints, UINT Stride  )
	{
		assert( Count > 0 );
		assert( pPoints );

		// Find the minimum and maximum x, y, and z
		XMVECTOR vMin, vMax;

		vMin = vMax = XMLoadFloat3( (XMFLOAT3*)&pPoints );

		for( UINT i = 1; i < Count; i++ )
		{
			const XMVECTOR Point = XMLoadFloat3( ( XMFLOAT3* )( ( char* )pPoints + i * Stride ) );

			vMin = XMVectorMin( vMin, Point );
			vMax = XMVectorMax( vMax, Point );
		}

		// Store center and extents.
		XMStoreFloat3( (XMFLOAT3*)&this->Center, XMVectorMultiply(XMVectorAdd( vMin , vMax ) , XMVectorReplicate(0.5f)  ) );
		XMStoreFloat3( (XMFLOAT3*)&this->Extents, XMVectorMultiply(XMVectorAdd( vMax , vMin ) , XMVectorReplicate(0.5f) ) );

		return;
	}

	//-----------------------------------------------------------------------------
	// Transform an axis aligned box by an angle preserving transform.
	//-----------------------------------------------------------------------------
	void XM_CALLCONV	AABB::Transform(  const AABB* pIn,const float Scale, const Quat& Rotation, const Vector4& Translation )
	{
		assert( pIn );
		assert(  Rotation.IsUnit()  );

		constexpr static XMVECTOR Offset[8] =
		{
			{ -1.0f, -1.0f, -1.0f, 0.0f },
			{ -1.0f, -1.0f,  1.0f, 0.0f },
			{ -1.0f,  1.0f, -1.0f, 0.0f },
			{ -1.0f,  1.0f,  1.0f, 0.0f },
			{  1.0f, -1.0f, -1.0f, 0.0f },
			{  1.0f, -1.0f,  1.0f, 0.0f },
			{  1.0f,  1.0f, -1.0f, 0.0f },
			{  1.0f,  1.0f,  1.0f, 0.0f }
		};

		// Load center and extents.
		const XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&pIn->Center );
		const XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&pIn->Extents );

		const XMVECTOR VectorScale = XMVectorReplicate( Scale );

		// Compute and transform the corners and find new min/max bounds.
		XMVECTOR Corner = XMVectorAdd(Center , XMVectorMultiply(Extents , Offset[0]) );
		Corner = XMVectorAdd( XMVector3Rotate( XMVectorMultiply(Corner , VectorScale), Rotation.Get() ) , Translation);

		XMVECTOR Min, Max;
		Min = Max = Corner;

		for( int i = 1; i < 8; i++ )
		{
			Corner = XMVectorAdd( Center , XMVectorMultiply(Extents , Offset[i]));
			Corner = XMVectorAdd( XMVector3Rotate( XMVectorMultiply(Corner , VectorScale), Rotation.Get() ) , Translation);

			Min = XMVectorMin( Min, Corner );
			Max = XMVectorMax( Max, Corner );
		}

		// Store center and extents.
		XMStoreFloat3( (XMFLOAT3*)&this->Center, XMVectorMultiply( XMVectorAdd( Min , Max ) , XMVectorReplicate(0.5f)) );
		XMStoreFloat3( (XMFLOAT3*)&this->Extents, XMVectorMultiply( XMVectorSubtract( Max , Min ) , XMVectorReplicate(0.5f) ) );

		return;
	}

	//-----------------------------------------------------------------------------
	// Point in axis aligned box test.
	//-----------------------------------------------------------------------------
	XM_INLINE  const bool XM_CALLCONV	AABB::IntersectPoint( const Vector4& Point) const noexcept
	{
		const XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&this->Extents );

		return XMVector3InBounds( XMVectorSubtract(Point.GetRaw() , Center) , Extents );
	}

	//-----------------------------------------------------------------------------
	// Compute the intersection of a ray (Origin, Direction) with an axis aligned
	// box using the slabs method.
	//-----------------------------------------------------------------------------
	const bool XM_CALLCONV	AABB::IntersectRay( const Ray& theRay,float* pDist ) const
	{
		assert( pDist );
		assert( theRay.GetDirection().IsUnit()  );

		static constexpr XMVECTOR Epsilon =
		{
			1e-20f, 1e-20f, 1e-20f, 1e-20f
		};
		static constexpr XMVECTOR FltMin =
		{
			-FLT_MAX, -FLT_MAX, -FLT_MAX, -FLT_MAX
		};
		static constexpr XMVECTOR FltMax =
		{
			FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX
		};

		// Load the box.
		const XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&this->Extents );

		// Adjust ray origin to be relative to center of the box.
		const XMVECTOR TOrigin = XMVectorSubtract( Center , theRay.GetStartPoint().GetRaw() );

		// Compute the dot product againt each axis of the box.
		// Since the axii are (1,0,0), (0,1,0), (0,0,1) no computation is necessary.
		const XMVECTOR AxisDotOrigin = TOrigin;
		const XMVECTOR AxisDotDirection = theRay.GetDirection();

		// if (fabs(AxisDotDirection) <= Epsilon) the ray is nearly parallel to the slab.
		const XMVECTOR IsParallel = XMVectorLessOrEqual( XMVectorAbs( AxisDotDirection ), Epsilon );

		// Test against all three axii simultaneously.
		const XMVECTOR InverseAxisDotDirection = XMVectorReciprocal( AxisDotDirection );
		const XMVECTOR t1 =  XMVectorMultiply( XMVectorSubtract(AxisDotOrigin , Extents)  , InverseAxisDotDirection);
		const XMVECTOR t2 =  XMVectorMultiply( XMVectorAdd(AxisDotOrigin , Extents)  , InverseAxisDotDirection);

		// Compute the max of min(t1,t2) and the min of max(t1,t2) ensuring we don't
		// use the results from any directions parallel to the slab.
		XMVECTOR t_min = XMVectorSelect( XMVectorMin( t1, t2 ), FltMin, IsParallel );
		XMVECTOR t_max = XMVectorSelect( XMVectorMax( t1, t2 ), FltMax, IsParallel );

		// t_min.x = maximum( t_min.x, t_min.y, t_min.z );
		// t_max.x = minimum( t_max.x, t_max.y, t_max.z );
		t_min = XMVectorMax( t_min, XMVectorSplatY( t_min ) );  // x = max(x,y)
		t_min = XMVectorMax( t_min, XMVectorSplatZ( t_min ) );  // x = max(max(x,y),z)
		t_max = XMVectorMin( t_max, XMVectorSplatY( t_max ) );  // x = min(x,y)
		t_max = XMVectorMin( t_max, XMVectorSplatZ( t_max ) );  // x = min(min(x,y),z)

		// if ( t_min > t_max ) return false;
		XMVECTOR NoIntersection = XMVectorGreater( XMVectorSplatX( t_min ), XMVectorSplatX( t_max ) );

		// if ( t_max < 0.0f ) return false;
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( XMVectorSplatX( t_max ), XMVectorZero() ) );

		// if (IsParallel && (-Extents > AxisDotOrigin || Extents < AxisDotOrigin)) return false;
		const XMVECTOR ParallelOverlap = XMVectorInBounds( AxisDotOrigin, Extents );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorAndCInt( IsParallel, ParallelOverlap ) );

		if( !XMVector3AnyTrue( NoIntersection ) )
		{
			// Store the x-component to *pDist
			XMStoreFloat( pDist, t_min );
			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------------
	const bool XM_CALLCONV	AABB::IntersectTriangle( const Vector4& V0, const Vector4& V1, const Vector4& V2 ) const noexcept
	{
		const XMVECTOR Zero = XMVectorZero();

		// Load the box.
		const XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&this->Extents );

		const XMVECTOR BoxMin = XMVectorSubtract(Center , Extents);
		const XMVECTOR BoxMax = XMVectorAdd(Center , Extents);

		// Test the axes of the box (in effect test the AAB against the minimal AAB
		// around the triangle).
		const XMVECTOR TriMin = XMVectorMin( XMVectorMin( V0, V1 ), V2 );
		const XMVECTOR TriMax = XMVectorMax( XMVectorMax( V0, V1 ), V2 );

		// for each i in (x, y, z) if a_min(i) > b_max(i) or b_min(i) > a_max(i) then disjoint
		const XMVECTOR Disjoint = XMVectorOrInt( XMVectorGreater( TriMin, BoxMax ), XMVectorGreater( BoxMin, TriMax ) );
		if( XMVector3AnyTrue( Disjoint ) )
			return false;

		// Test the plane of the triangle.
		const XMVECTOR Normal = XMVector3Cross( V1 - V0, V2 - V0 );
		const XMVECTOR Dist = XMVector3Dot( Normal, V0 );

		// Assert that the triangle is not degenerate.
		assert( !XMVector3Equal( Normal, Zero ) );

		// for each i in (x, y, z) if n(i) >= 0 then v_min(i)=b_min(i), v_max(i)=b_max(i)
		// else v_min(i)=b_max(i), v_max(i)=b_min(i)
		const XMVECTOR NormalSelect = XMVectorGreater( Normal, Zero );
		const XMVECTOR V_Min = XMVectorSelect( BoxMax, BoxMin, NormalSelect );
		const XMVECTOR V_Max = XMVectorSelect( BoxMin, BoxMax, NormalSelect );

		// if n dot v_min + d > 0 || n dot v_max + d < 0 then disjoint
		const XMVECTOR MinDist = XMVector3Dot( V_Min, Normal );
		const XMVECTOR MaxDist = XMVector3Dot( V_Max, Normal );

		XMVECTOR NoIntersection = XMVectorGreater( MinDist, Dist );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( MaxDist, Dist ) );

		// Move the box center to zero to simplify the following tests.
		const XMVECTOR TV0 = XMVectorSubtract(V0.GetRaw() , Center);
		const XMVECTOR TV1 = XMVectorSubtract(V1.GetRaw() , Center);
		const XMVECTOR TV2 = XMVectorSubtract(V2.GetRaw() , Center);

		// Test the edge/edge axes (3*3).
		XMVECTOR e0 = XMVectorSubtract(TV1 , TV0);
		XMVECTOR e1 = XMVectorSubtract(TV2 , TV1);
		XMVECTOR e2 = XMVectorSubtract(TV0 , TV2);

		// Make w zero.
		e0 = XMVectorInsert( e0, Zero, 0, 0, 0, 0, 1 );
		e1 = XMVectorInsert( e1, Zero, 0, 0, 0, 0, 1 );
		e2 = XMVectorInsert( e2, Zero, 0, 0, 0, 0, 1 );

		XMVECTOR Axis;
		XMVECTOR p0, p1, p2;
		XMVECTOR Min, Max;
		XMVECTOR Radius;

		// Axis == (1,0,0) x e0 = (0, -e0.z, e0.y)
		Axis = XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_1Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( e0, XMVectorNegate(e0) );
		p0 = XMVector3Dot( TV0, Axis );
		// p1 = XMVector3Dot( V1, Axis ); // p1 = p0;
		p2 = XMVector3Dot( TV2, Axis );
		Min = XMVectorMin( p0, p2 );
		Max = XMVectorMax( p0, p2 );
		Radius = XMVector3Dot( Extents, XMVectorAbs( Axis ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( Min, Radius ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( Max, XMVectorNegate(Radius) ) );

		// Axis == (1,0,0) x e1 = (0, -e1.z, e1.y)
		Axis = XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_1Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( e1, XMVectorNegate(e1) );
		p0 = XMVector3Dot( TV0, Axis );
		p1 = XMVector3Dot( TV1, Axis );
		// p2 = XMVector3Dot( V2, Axis ); // p2 = p1;
		Min = XMVectorMin( p0, p1 );
		Max = XMVectorMax( p0, p1 );
		Radius = XMVector3Dot( Extents, XMVectorAbs( Axis ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( Min, Radius ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( Max, XMVectorNegate(Radius) ) );

		// Axis == (1,0,0) x e2 = (0, -e2.z, e2.y)
		Axis = XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_1Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( e2, XMVectorNegate(e2) );
		p0 = XMVector3Dot( TV0, Axis );
		p1 = XMVector3Dot( TV1, Axis );
		// p2 = XMVector3Dot( V2, Axis ); // p2 = p0;
		Min = XMVectorMin( p0, p1 );
		Max = XMVectorMax( p0, p1 );
		Radius = XMVector3Dot( Extents, XMVectorAbs( Axis ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( Min, Radius ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( Max, XMVectorNegate(Radius) ) );

		// Axis == (0,1,0) x e0 = (e0.z, 0, -e0.x)
		Axis = XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_1X, XM_PERMUTE_0Y>( e0, XMVectorNegate(e0) );
		p0 = XMVector3Dot( TV0, Axis );
		// p1 = XMVector3Dot( V1, Axis ); // p1 = p0;
		p2 = XMVector3Dot( TV2, Axis );
		Min = XMVectorMin( p0, p2 );
		Max = XMVectorMax( p0, p2 );
		Radius = XMVector3Dot( Extents, XMVectorAbs( Axis ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( Min, Radius ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( Max, XMVectorNegate(Radius) ) );

		// Axis == (0,1,0) x e1 = (e1.z, 0, -e1.x)
		Axis = XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_1X, XM_PERMUTE_0Y>( e1, XMVectorNegate(e1) );
		p0 = XMVector3Dot( TV0, Axis );
		p1 = XMVector3Dot( TV1, Axis );
		// p2 = XMVector3Dot( V2, Axis ); // p2 = p1;
		Min = XMVectorMin( p0, p1 );
		Max = XMVectorMax( p0, p1 );
		Radius = XMVector3Dot( Extents, XMVectorAbs( Axis ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( Min, Radius ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( Max, XMVectorNegate(Radius) ) );

		// Axis == (0,0,1) x e2 = (e2.z, 0, -e2.x)
		Axis = XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_1X, XM_PERMUTE_0Y>( e2, XMVectorNegate(e2) );
		p0 = XMVector3Dot( TV0, Axis );
		p1 = XMVector3Dot( TV1, Axis );
		// p2 = XMVector3Dot( V2, Axis ); // p2 = p0;
		Min = XMVectorMin( p0, p1 );
		Max = XMVectorMax( p0, p1 );
		Radius = XMVector3Dot( Extents, XMVectorAbs( Axis ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( Min, Radius ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( Max, XMVectorNegate(Radius) ) );

		// Axis == (0,0,1) x e0 = (-e0.y, e0.x, 0)
		Axis = XMVectorPermute<XM_PERMUTE_1Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( e0, XMVectorNegate(e0) );
		p0 = XMVector3Dot( TV0, Axis );
		// p1 = XMVector3Dot( V1, Axis ); // p1 = p0;
		p2 = XMVector3Dot( TV2, Axis );
		Min = XMVectorMin( p0, p2 );
		Max = XMVectorMax( p0, p2 );
		Radius = XMVector3Dot( Extents, XMVectorAbs( Axis ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( Min, Radius ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( Max, XMVectorNegate(Radius) ) );

		// Axis == (0,0,1) x e1 = (-e1.y, e1.x, 0)
		Axis = XMVectorPermute<XM_PERMUTE_1Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( e1, XMVectorNegate(e1) );
		p0 = XMVector3Dot( TV0, Axis );
		p1 = XMVector3Dot( TV1, Axis );
		// p2 = XMVector3Dot( V2, Axis ); // p2 = p1;
		Min = XMVectorMin( p0, p1 );
		Max = XMVectorMax( p0, p1 );
		Radius = XMVector3Dot( Extents, XMVectorAbs( Axis ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( Min, Radius ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( Max, XMVectorNegate(Radius) ) );

		// Axis == (0,0,1) x e2 = (-e2.y, e2.x, 0)
		Axis = XMVectorPermute<XM_PERMUTE_1Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( e2, XMVectorNegate(e2) );
		p0 = XMVector3Dot( TV0, Axis );
		p1 = XMVector3Dot( TV1, Axis );
		// p2 = XMVector3Dot( V2, Axis ); // p2 = p0;
		Min = XMVectorMin( p0, p1 );
		Max = XMVectorMax( p0, p1 );
		Radius = XMVector3Dot( Extents, XMVectorAbs( Axis ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorGreater( Min, Radius ) );
		NoIntersection = XMVectorOrInt( NoIntersection, XMVectorLess( Max, XMVectorNegate(Radius) ) );

		return XMVector4NotEqualInt( NoIntersection, XMVectorTrueInt() );
	}

	XM_INLINE  const bool XM_CALLCONV	AABB::IntersectSphere( Sphere& pVolumeA ) const noexcept
	{
		return pVolumeA.IntersectAABB(  this );
	}

	//-----------------------------------------------------------------------------
	const bool XM_CALLCONV	AABB::IntersectAABB(  AABB& pVolumeB ) const noexcept
	{
		const XMVECTOR CenterA = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const XMVECTOR ExtentsA = XMLoadFloat3( (XMFLOAT3*)&this->Extents );

		const XMVECTOR CenterB = XMLoadFloat3( (XMFLOAT3*)&pVolumeB.Center );
		const XMVECTOR ExtentsB = XMLoadFloat3( (XMFLOAT3*)&pVolumeB.Extents );

		const XMVECTOR MinA = XMVectorSubtract(CenterA , ExtentsA);
		const XMVECTOR MaxA = XMVectorAdd(CenterA , ExtentsA);

		const XMVECTOR MinB = XMVectorSubtract(CenterB , ExtentsB);
		const XMVECTOR MaxB = XMVectorAdd(CenterB , ExtentsB);

		// for each i in (x, y, z) if a_min(i) > b_max(i) or b_min(i) > a_max(i) then return false
		XMVECTOR Disjoint = XMVectorOrInt( XMVectorGreater( MinA, MaxB ), XMVectorGreater( MinB, MaxA ) );

		return !XMVector3AnyTrue( Disjoint );
	}

	//-----------------------------------------------------------------------------
	const bool XM_CALLCONV	AABB::IntersectOBB( OBB& pVolumeB ) const noexcept
	{
		// Make the axis aligned box oriented and do an OBB vs OBB test.
		OBB BoxA;

		BoxA.SetCenter( this->Center );
		BoxA.SetExtents( this->Extents );
		BoxA.SetOrientation( Quat(0.0f,0.0f,0.0f,1.0f) );

		return BoxA.IntersectOBB( &pVolumeB );
	}

	const eCullClassify XM_CALLCONV	AABB::IntersectFrustum( Frustum* pVolumeB ) const
	{
		assert(pVolumeB);

		return pVolumeB->IntersectAABB(*this);
	}

	const eCullClassify XM_CALLCONV	AABB::Intersect6Planes(  Plane& Plane0, Plane& Plane1, Plane& Plane2, Plane& Plane3, Plane& Plane4, Plane& Plane5 ) const noexcept
	{
		// Load the box.
		XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&this->Extents );

		// Set w of the center to one so we can dot4 with a plane.
		Center = XMVectorInsert( Center, XMVectorSplatOne(), 0, 0, 0, 0, 1 );

		XMVECTOR Outside, Inside;

		// Test against each plane.
		FastIntersectAxisAlignedBoxPlane( *this, Plane0, Outside, Inside );

		XMVECTOR AnyOutside = Outside;
		XMVECTOR AllInside = Inside;

		FastIntersectAxisAlignedBoxPlane( *this, Plane1, Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectAxisAlignedBoxPlane( *this, Plane2, Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectAxisAlignedBoxPlane( *this, Plane3, Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectAxisAlignedBoxPlane( *this, Plane4, Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectAxisAlignedBoxPlane( *this, Plane5, Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		// If the box is outside any plane it is outside.
		if ( XMVector4EqualInt( AnyOutside, XMVectorTrueInt() ) )
			return CULLED; // 0

		// If the box is inside all planes it is inside.
		if ( XMVector4EqualInt( AllInside, XMVectorTrueInt() ) )
			return VISIBLE; // 2

		// The box is not inside all planes or outside a plane, it may intersect.
		return CLIPPED; // 1
	}

	const eCullClassify XM_CALLCONV	AABB::IntersectPlane( Plane& Plane0 ) const noexcept
	{
		// Load the box.
		XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center );
		const XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&this->Extents );

		// Set w of the center to one so we can dot4 with a plane.
		Center = XMVectorInsert( Center, XMVectorSplatOne(), 0, 0, 0, 0, 1);

		XMVECTOR Outside, Inside;
		FastIntersectAxisAlignedBoxPlane( *this, Plane0, Outside, Inside );

		// If the box is outside any plane it is outside.
		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED; // 0

		// If the box is inside all planes it is inside.
		if ( XMVector4EqualInt( Inside, XMVectorTrueInt() ) )
			return VISIBLE; // 2

		// The box is not inside all planes or outside a plane it intersects.
		return CLIPPED; // 1
	}

	const void XM_CALLCONV	AABB::GetPlanes(  Plane& Plane0, Plane& Plane1, Plane& Plane2, Plane& Plane3, Plane& Plane4, Plane& Plane5 ) const noexcept
	{
		Vector4 vcN;
		const Vector4 vcMax = GetMaxExtents();
		const Vector4 vcMin = GetMinExtents();

		// right side
		vcN.Set(1.0f, 0.0f, 0.0f);
		Plane0.Set(vcMax, vcN);

		// left side
		vcN.Set(-1.0f, 0.0f, 0.0f);
		Plane1.Set(vcMin,vcN);

		// front side
		vcN.Set(0.0f, 0.0f, -1.0f);
		Plane2.Set(vcMin, vcN);

		// back side
		vcN.Set(0.0f, 0.0f, 1.0f);
		Plane3.Set(vcMax, vcN);

		// top side
		vcN.Set(0.0f, 1.0f, 0.0f);
		Plane4.Set(vcMax, vcN);

		// bottom side
		vcN.Set(0.0f, -1.0f, 0.0f);
		Plane5.Set(vcMin, vcN);
	}

	// does aabb contain ray
	const bool XM_CALLCONV	AABB::Contains(const Ray& ray, float fL) const noexcept
	{
		Vector4 vcEnd;

		vcEnd = ray.GetStartPoint() + (ray.GetDirection() * fL);

		return ( IntersectPoint(ray.GetStartPoint()) && IntersectPoint(vcEnd) );
	} // Contains


	const Line XM_CALLCONV	AABB::GetEdge(const int index) const noexcept
	{
		const float x0 = Center.GetX() - Extents.GetX();
		const float y0 = Center.GetY() - Extents.GetY();
		const float z0 = Center.GetZ() - Extents.GetZ();
		const float x1 = Center.GetX() + Extents.GetX();
		const float y1 = Center.GetY() + Extents.GetY();
		const float z1 = Center.GetZ() + Extents.GetZ();

		switch(index)
		{
			case 0: return Line(Vector4(x0, y0, z0), Vector4(x1, y0, z0));
			case 1: return Line(Vector4(x1, y0, z0), Vector4(x1, y1, z0));
			case 2: return Line(Vector4(x1, y1, z0), Vector4(x0, y1, z0));
			case 3: return Line(Vector4(x0, y1, z0), Vector4(x0, y0, z0));

			case 4: return Line(Vector4(x0, y0, z1), Vector4(x1, y0, z1));
			case 5: return Line(Vector4(x1, y0, z1), Vector4(x1, y1, z1));
			case 6: return Line(Vector4(x1, y1, z1), Vector4(x0, y1, z1));
			case 7: return Line(Vector4(x0, y1, z1), Vector4(x0, y0, z1));

			case 8: return Line(Vector4(x0, y0, z0), Vector4(x0, y0, z1));
			case 9: return Line(Vector4(x1, y0, z0), Vector4(x1, y0, z1));
			case 10: return Line(Vector4(x1, y1, z0), Vector4(x1, y1, z1));
			case 11: return Line(Vector4(x0, y1, z0), Vector4(x0, y1, z1));

			default: return Line(Vector4::NullVec(), Vector4::NullVec());
		}
	}

}// end of Namespace TurboMath