

// -------------------------------------------------------------------
// File			:	Frustum.inl
//
// Project		:	TurboMath
//
// Description	:	Class for a View-Frustum
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

	__forceinline Frustum::Frustum()
	{
		Origin.NullVec();
		Orientation.NullQuat();

		RightSlope = 0.0f;
		LeftSlope = 0.0f;
		TopSlope = 0.0f;
		BottomSlope = 0.0f;
		Near = 0.0f;
		Far = 0.0f;
	}

	__forceinline Frustum::Frustum(const Frustum& cpyFrustum)
	{
		Origin = cpyFrustum.GetOrigin();
		Orientation= cpyFrustum.GetOrientation();

		RightSlope = cpyFrustum.GetRightSlope();
		LeftSlope = cpyFrustum.GetLeftSlope();
		TopSlope = cpyFrustum.GetTopSlope();
		BottomSlope = cpyFrustum.GetBottomSlope();
		Near = cpyFrustum.GetNearPlane();
		Far = cpyFrustum.GetFarPlane();
	}

	
	__forceinline void Frustum::SetOrigin(const Vector4& orig)
	{
		Origin = orig;
	}

	__forceinline const Vector4 Frustum::GetOrigin() const
	{
		return Origin;
	}

	__forceinline void Frustum::SetOrientation(const Quat& NewQuat)	
	{
		Orientation = NewQuat;
	}

	__forceinline const Quat Frustum::GetOrientation() const				
	{
		return Orientation;
	}

	__forceinline void Frustum::SetRightSlope(const float rf)		
	{
		RightSlope = rf;
	}

	__forceinline const float Frustum::GetRightSlope() const				
	{
		return RightSlope;
	}

	__forceinline void Frustum::SetLeftSlope(const float lf)
	{
		LeftSlope = lf;
	}

	__forceinline const float Frustum::GetLeftSlope() const				
	{
		return LeftSlope;
	}

	__forceinline void Frustum::SetTopSlope(const float tf)	
	{
		TopSlope = tf;
	}

	__forceinline const float Frustum::GetTopSlope() const					
	{
		return TopSlope;
	}

	__forceinline void Frustum::SetBottonSlope(const float bf)
	{
		BottomSlope = bf;
	}

	__forceinline const float Frustum::GetBottomSlope() const				
	{
		return BottomSlope;
	}

	__forceinline void Frustum::SetNearPlane(const float fNear)		
	{
		Near = fNear;
	}

	__forceinline const float Frustum::GetNearPlane() const
	{
		return Near;
	}

	__forceinline void Frustum::SetFarPlane(const float fFar)
	{
		Far = fFar;
	}

	__forceinline const float Frustum::GetFarPlane() const					
	{
		return Far;
	}


	//-----------------------------------------------------------------------------
	// Transform a plane by a rotation and translation.
	//-----------------------------------------------------------------------------
	static __forceinline XMVECTOR TransformPlane( FXMVECTOR Plane, FXMVECTOR Rotation, FXMVECTOR Translation )
	{
		const XMVECTOR Normal = XMVector3Rotate( Plane, Rotation );
		const XMVECTOR D = XMVectorSubtract(XMVectorSplatW( Plane ) , XMVector3Dot( Normal, Translation ) );

		return XMVectorInsert( Normal, D, 0, 0, 0, 0, 1 );
	}

	__forceinline void Frustum::ComputeFrustumFromProjection(const Matrix& Projection )
	{
			// Corners of the projection frustum in homogenous space.
		const static XMVECTOR HomogenousPoints[6] =
		{
			{  1.0f,  0.0f, 1.0f, 1.0f },   // right (at far plane)
			{ -1.0f,  0.0f, 1.0f, 1.0f },   // left
			{  0.0f,  1.0f, 1.0f, 1.0f },   // top
			{  0.0f, -1.0f, 1.0f, 1.0f },   // bottom

			{ 0.0f, 0.0f, 0.0f, 1.0f },     // near
			{ 0.0f, 0.0f, 1.0f, 1.0f }      // far
		};

		XMVECTOR Determinant;
		const XMMATRIX matInverse = XMMatrixInverse( &Determinant, Projection.mx );

		// Compute the frustum corners in world space.
		XMVECTOR Points[6];

		for( int i = 0; i < 6; i++ )
		{
			// Transform point.
			Points[i] = XMVector4Transform( HomogenousPoints[i], matInverse );
		}

		this->Origin.Set( 0.0f, 0.0f, 0.0f );
		this->Orientation.Set( 0.0f, 0.0f, 0.0f, 1.0f );

		// Compute the slopes.
		Points[0] = XMVectorMultiply(Points[0] , XMVectorReciprocal( XMVectorSplatZ( Points[0] ) ) );
		Points[1] = XMVectorMultiply(Points[1] , XMVectorReciprocal( XMVectorSplatZ( Points[1] ) ) );
		Points[2] = XMVectorMultiply(Points[2] , XMVectorReciprocal( XMVectorSplatZ( Points[2] ) ) );
		Points[3] = XMVectorMultiply(Points[3] , XMVectorReciprocal( XMVectorSplatZ( Points[3] ) ) );

		this->RightSlope = XMVectorGetX( Points[0] );
		this->LeftSlope = XMVectorGetX( Points[1] );
		this->TopSlope = XMVectorGetY( Points[2] );
		this->BottomSlope = XMVectorGetY( Points[3] );

		// Compute near and far.
		Points[4] = XMVectorMultiply(Points[4] , XMVectorReciprocal( XMVectorSplatW( Points[4] ) ) );
		Points[5] = XMVectorMultiply(Points[5] , XMVectorReciprocal( XMVectorSplatW( Points[5] ) ) );

		this->Near = XMVectorGetZ( Points[4] );
		this->Far = XMVectorGetZ( Points[5] );

		return;
	}

	__forceinline void Frustum::ComputePlanes( Plane& Plane0, Plane& Plane1, Plane& Plane2,Plane& Plane3, Plane& Plane4, Plane& Plane5 ) const
	{
		// Load origin and orientation of the frustum.
		const XMVECTOR Origin = XMLoadFloat3( (XMFLOAT3*)&this->Origin );
		const XMVECTOR Orientation = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );

		// Build the frustum planes.
		XMVECTOR mPlane0 = XMVectorSet( 0.0f, 0.0f, -1.0f, this->Near );
		XMVECTOR mPlane1 = XMVectorSet( 0.0f, 0.0f, 1.0f, -this->Far );
		XMVECTOR mPlane2 = XMVectorSet( 1.0f, 0.0f, -this->RightSlope, 0.0f );
		XMVECTOR mPlane3 = XMVectorSet( -1.0f, 0.0f, this->LeftSlope, 0.0f );
		XMVECTOR mPlane4 = XMVectorSet( 0.0f, 1.0f, -this->TopSlope, 0.0f );
		XMVECTOR mPlane5 = XMVectorSet( 0.0f, -1.0f, this->BottomSlope, 0.0f );

		mPlane0 = TransformPlane( mPlane0, Orientation, Origin );
		mPlane1 = TransformPlane( mPlane1, Orientation, Origin );
		mPlane2 = TransformPlane( mPlane2, Orientation, Origin );
		mPlane3 = TransformPlane( mPlane3, Orientation, Origin );
		mPlane4 = TransformPlane( mPlane4, Orientation, Origin );
		mPlane5 = TransformPlane( mPlane5, Orientation, Origin );

		Plane0.Set(XMPlaneNormalize( mPlane0 ));
		Plane1.Set(XMPlaneNormalize( mPlane1 ));
		Plane2.Set(XMPlaneNormalize( mPlane2 ));
		Plane3.Set(XMPlaneNormalize( mPlane3 ));
		Plane4.Set(XMPlaneNormalize( mPlane4 ));
		Plane5.Set(XMPlaneNormalize( mPlane5 ));
	}

	//-----------------------------------------------------------------------------
	// Transform a frustum by an angle preserving transform.
	//-----------------------------------------------------------------------------
	__forceinline void Frustum::Transform(const float Scale, Quat& Rotation,const Vector4& Translation )
	{
		// Composite the frustum rotation and the transform rotation.
		this->Orientation *= Rotation;

		// Transform the origin.
		this->Origin.Rotate(Rotation,Scale ) + Translation;

		// Scale the near and far distances (the slopes remain the same).
		this->Near *= Scale;
		this->Far *= Scale;
	}

	//-----------------------------------------------------------------------------
	__forceinline void Frustum::Rotate(const Vector4& axis, float degrees)
	{
		const Quat qRot = Quat::RotationMatrix( Matrix::RotationAxis(axis, XMConvertToRadians(degrees)) );

		this->Orientation *= qRot;
	}

	//-----------------------------------------------------------------------------
	__forceinline void Frustum::Rotate(const Quat& q)
	{
		this->Orientation *= q;
	}

	//-----------------------------------------------------------------------------
	__forceinline const bool Frustum::IntersectPoint(const Vector4& Point) const
	{
		static const XMVECTORU32 SelectW = {XM_SELECT_0, XM_SELECT_0, XM_SELECT_0, XM_SELECT_1};
		static const XMVECTORU32 SelectZ = {XM_SELECT_0, XM_SELECT_0, XM_SELECT_1, XM_SELECT_0};

		static const XMVECTOR BasePlanes[6] =
		{
			{  0.0f,  0.0f, -1.0f, 0.0f },
			{  0.0f,  0.0f,  1.0f, 0.0f },
			{  1.0f,  0.0f,  0.0f, 0.0f },
			{ -1.0f,  0.0f,  0.0f, 0.0f },
			{  0.0f,  1.0f,  0.0f, 0.0f },
			{  0.0f, -1.0f,  0.0f, 0.0f },
		};

		// Build frustum planes.
		XMVECTOR Planes[6];
		Planes[0] = XMVectorSelect( BasePlanes[0], XMVectorSplatX(  XMLoadFloat( &this->Near ) ),	SelectW );
		Planes[1] = XMVectorSelect( BasePlanes[1], XMVectorSplatX(  XMVectorNegate(XMLoadFloat( &this->Far ) ) ),	SelectW );
		Planes[2] = XMVectorSelect( BasePlanes[2], XMVectorSplatX(  XMVectorNegate(XMLoadFloat( &this->RightSlope ) ) ),		SelectZ );
		Planes[3] = XMVectorSelect( BasePlanes[3], XMVectorSplatX(  XMLoadFloat( &this->LeftSlope ) ),		SelectZ );
		Planes[4] = XMVectorSelect( BasePlanes[4], XMVectorSplatX(  XMVectorNegate(XMLoadFloat( &this->TopSlope ) ) ),		SelectZ );
		Planes[5] = XMVectorSelect( BasePlanes[5], XMVectorSplatX(  XMLoadFloat( &this->BottomSlope ) ),	SelectZ );

		// Transform point into local space of frustum.
		const Vector4 tmpPoint = Point - Origin;
		XMVECTOR TPoint = XMVector3InverseRotate( tmpPoint, Orientation.Get() );

		// Set w to one.
		TPoint = XMVectorInsert( TPoint, XMVectorSplatOne(), 0, 0, 0, 0, 1);

		const XMVECTOR Zero = XMVectorZero();
		XMVECTOR Outside = Zero;

		// Test point against each plane of the frustum.
		for( int i = 0; i < 6; i++ )
		{
			const XMVECTOR Dot = XMVector4Dot( TPoint, Planes[i] );
			Outside = XMVectorOrInt( Outside, XMVectorGreater( Dot, Zero ) );
		}

		return XMVector4NotEqualInt( Outside, XMVectorTrueInt() );
	}

	//-----------------------------------------------------------------------------
	// Frustum intersection testing routines.
	// Return values: 0 = no intersection,
	//                1 = intersection,
	//                2 = A is completely inside B
	//-----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	// Exact triangle vs frustum test.
	// Return values: 0 = no intersection,
	//                1 = intersection,
	//                2 = triangle is completely inside frustum
	//-----------------------------------------------------------------------------
	_inline const eCullClassify Frustum::IntersectTriangle(const Vector4& V0,const Vector4& V1,const Vector4& V2) const
	{
		// Build the frustum planes (NOTE: D is negated from the usual).
		XMVECTOR Planes[6];
		Planes[0] = XMVectorSet( 0.0f, 0.0f, -1.0f, -this->Near );
		Planes[1] = XMVectorSet( 0.0f, 0.0f, 1.0f, this->Far );
		Planes[2] = XMVectorSet( 1.0f, 0.0f, -this->RightSlope, 0.0f );
		Planes[3] = XMVectorSet( -1.0f, 0.0f, this->LeftSlope, 0.0f );
		Planes[4] = XMVectorSet( 0.0f, 1.0f, -this->TopSlope, 0.0f );
		Planes[5] = XMVectorSet( 0.0f, -1.0f, this->BottomSlope, 0.0f );

		// Transform triangle into the local space of frustum.
		const XMVECTOR TV0 = XMVector3InverseRotate( XMVECTOR( (V0 - Origin) ), this->Orientation.Get() );
		const XMVECTOR TV1 = XMVector3InverseRotate( XMVECTOR( (V1 - Origin) ), this->Orientation.Get() );
		const XMVECTOR TV2 = XMVector3InverseRotate( XMVECTOR( (V2 - Origin) ), this->Orientation.Get() );

		// Test each vertex of the triangle against the frustum planes.
		XMVECTOR Outside = XMVectorFalseInt();
		XMVECTOR InsideAll = XMVectorTrueInt();

		for( int i = 0; i < 6; i++ )
		{
			const XMVECTOR Dist0 = XMVector3Dot( TV0, Planes[i] );
			const XMVECTOR Dist1 = XMVector3Dot( TV1, Planes[i] );
			const XMVECTOR Dist2 = XMVector3Dot( TV2, Planes[i] );

			XMVECTOR MinDist = XMVectorMin( Dist0, Dist1 );
			MinDist = XMVectorMin( MinDist, Dist2 );
			XMVECTOR MaxDist = XMVectorMax( Dist0, Dist1 );
			MaxDist = XMVectorMax( MaxDist, Dist2 );

			const XMVECTOR PlaneDist = XMVectorSplatW( Planes[i] );

			// Outside the plane?
			Outside = XMVectorOrInt( Outside, XMVectorGreater( MinDist, PlaneDist ) );

			// Fully inside the plane?
			InsideAll = XMVectorAndInt( InsideAll, XMVectorLessOrEqual( MaxDist, PlaneDist ) );
		}

		// If the triangle is outside any of the planes it is outside.
		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED;  // 0

		// If the triangle is inside all planes it is fully inside.
		if ( XMVector4EqualInt( InsideAll, XMVectorTrueInt() ) )
			return VISIBLE;  // 2

		// Build the corners of the frustum.
		const XMVECTOR RightTop = XMVectorSet( this->RightSlope, this->TopSlope, 1.0f, 0.0f );
		const XMVECTOR RightBottom = XMVectorSet( this->RightSlope, this->BottomSlope, 1.0f, 0.0f );
		const XMVECTOR LeftTop = XMVectorSet( this->LeftSlope, this->TopSlope, 1.0f, 0.0f );
		const XMVECTOR LeftBottom = XMVectorSet( this->LeftSlope, this->BottomSlope, 1.0f, 0.0f );
		const XMVECTOR Near = XMVectorReplicatePtr( &this->Near );
		const XMVECTOR Far = XMVectorReplicatePtr( &this->Far );

		XMVECTOR Corners[8];
		Corners[0] = XMVectorMultiply(RightTop , Near);
		Corners[1] = XMVectorMultiply(RightBottom , Near);
		Corners[2] = XMVectorMultiply(LeftTop , Near);
		Corners[3] = XMVectorMultiply(LeftBottom , Near);
		Corners[4] = XMVectorMultiply(RightTop , Far);
		Corners[5] = XMVectorMultiply(RightBottom , Far);
		Corners[6] = XMVectorMultiply(LeftTop , Far);
		Corners[7] = XMVectorMultiply(LeftBottom , Far);

		// Test the plane of the triangle.
		const XMVECTOR Normal = XMVector3Cross( XMVECTOR( (V1 - V0) ), XMVECTOR( (V2 - V0) ) );
		const XMVECTOR Dist = XMVector3Dot( Normal, V0 );

		XMVECTOR MinDist, MaxDist;
		MinDist = MaxDist = XMVector3Dot( Corners[0], Normal );
		for( int i = 1; i < 8; i++ )
		{
			const XMVECTOR Temp = XMVector3Dot( Corners[i], Normal );
			MinDist = XMVectorMin( MinDist, Temp );
			MaxDist = XMVectorMax( MaxDist, Temp );
		}

		Outside = XMVectorOrInt( XMVectorGreater( MinDist, Dist ), XMVectorLess( MaxDist, Dist ) );
		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED;  // 0

		// Check the edge/edge axes (3*6).
		XMVECTOR TriangleEdgeAxis[3];
		TriangleEdgeAxis[0] = XMVECTOR( (V1 - V0));
		TriangleEdgeAxis[1] = XMVECTOR( (V2 - V1));
		TriangleEdgeAxis[2] = XMVECTOR( (V0 - V2));

		XMVECTOR FrustumEdgeAxis[6];
		FrustumEdgeAxis[0] = RightTop;
		FrustumEdgeAxis[1] = RightBottom;
		FrustumEdgeAxis[2] = LeftTop;
		FrustumEdgeAxis[3] = LeftBottom;
		FrustumEdgeAxis[4] = XMVectorSubtract(RightTop , LeftTop);
		FrustumEdgeAxis[5] = XMVectorSubtract(LeftBottom , LeftTop);

		for( int i = 0; i < 3; i++ )
		{
			for( int j = 0; j < 6; j++ )
			{
				// Compute the axis we are going to test.
				const XMVECTOR Axis = XMVector3Cross( TriangleEdgeAxis[i], FrustumEdgeAxis[j] );

				// Find the min/max of the projection of the triangle onto the axis.
				XMVECTOR MinA, MaxA;

				const XMVECTOR Dist0 = XMVector3Dot( V0, Axis );
				const XMVECTOR Dist1 = XMVector3Dot( V1, Axis );
				const XMVECTOR Dist2 = XMVector3Dot( V2, Axis );

				MinA = XMVectorMin( Dist0, Dist1 );
				MinA = XMVectorMin( MinA, Dist2 );
				MaxA = XMVectorMax( Dist0, Dist1 );
				MaxA = XMVectorMax( MaxA, Dist2 );

				// Find the min/max of the projection of the frustum onto the axis.
				XMVECTOR MinB, MaxB;

				MinB = MaxB = XMVector3Dot( Axis, Corners[0] );

				for( int k = 1; k < 8; k++ )
				{
					const XMVECTOR Temp = XMVector3Dot( Axis, Corners[k] );
					MinB = XMVectorMin( MinB, Temp );
					MaxB = XMVectorMax( MaxB, Temp );
				}

				// if (MinA > MaxB || MinB > MaxA) reject;
				Outside = XMVectorOrInt( Outside, XMVectorGreater( MinA, MaxB ) );
				Outside = XMVectorOrInt( Outside, XMVectorGreater( MinB, MaxA ) );
			}
		}

		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED; // 0

		// If we did not find a separating plane then the triangle must intersect the frustum.
		return CLIPPED; // 1
	}

	//-----------------------------------------------------------------------------
	// Exact sphere vs frustum test.  The algorithm first checks the sphere against
	// the planes of the frustum, then if the plane checks were indeterminate finds
	// the nearest feature (plane, line, point) on the frustum to the center of the
	// sphere and compares the distance to the nearest feature to the radius of the
	// sphere (it is so cool that all the comment lines above are the same length).
	// Return values: 0 = no intersection,
	//                1 = intersection,
	//                2 = sphere is completely inside frustum
	//-----------------------------------------------------------------------------
	_inline const eCullClassify Frustum::IntersectSphere( const Sphere& pVolumeA) const
	{
		const XMVECTOR Zero = XMVectorZero();

		// Build the frustum planes.
		XMVECTOR Planes[6];
		Planes[0] = XMVectorSet( 0.0f, 0.0f, -1.0f, this->Near );
		Planes[1] = XMVectorSet( 0.0f, 0.0f, 1.0f, -this->Far );
		Planes[2] = XMVectorSet( 1.0f, 0.0f, -this->RightSlope, 0.0f );
		Planes[3] = XMVectorSet( -1.0f, 0.0f, this->LeftSlope, 0.0f );
		Planes[4] = XMVectorSet( 0.0f, 1.0f, -this->TopSlope, 0.0f );
		Planes[5] = XMVectorSet( 0.0f, -1.0f, this->BottomSlope, 0.0f );

		// Normalize the planes so we can compare to the sphere radius.
		Planes[2] = XMVector3Normalize( Planes[2] );
		Planes[3] = XMVector3Normalize( Planes[3] );
		Planes[4] = XMVector3Normalize( Planes[4] );
		Planes[5] = XMVector3Normalize( Planes[5] );

		// Load the sphere.
		XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&pVolumeA.GetCenter() );
		const float VolArad = pVolumeA.GetRadius();
		const XMVECTOR Radius = XMVectorReplicatePtr( &VolArad );

		// Transform the center of the sphere into the local space of frustum.
		Center = XMVector3InverseRotate( XMVectorSubtract(Center , this->Origin) , this->Orientation.Get() );

		// Set w of the center to one so we can dot4 with the plane.
		Center = XMVectorInsert( Center, XMVectorSplatOne(), 0, 0, 0, 0, 1);

		// Check against each plane of the frustum.
		XMVECTOR Outside = XMVectorFalseInt();
		XMVECTOR InsideAll = XMVectorTrueInt();
		XMVECTOR CenterInsideAll = XMVectorTrueInt();

		XMVECTOR Dist[6];

		for( int i = 0; i < 6; i++ )
		{
			Dist[i] = XMVector4Dot( Center, Planes[i] );

			// Outside the plane?
			Outside = XMVectorOrInt( Outside, XMVectorGreater( Dist[i], Radius ) );

			// Fully inside the plane?
			InsideAll = XMVectorAndInt( InsideAll, XMVectorLessOrEqual( Dist[i], XMVectorNegate(Radius ) ) );

			// Check if the center is inside the plane.
			CenterInsideAll = XMVectorAndInt( CenterInsideAll, XMVectorLessOrEqual( Dist[i], Zero ) );
		}

		// If the sphere is outside any of the planes it is outside.
		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED; // 0

		// If the sphere is inside all planes it is fully inside.
		if ( XMVector4EqualInt( InsideAll, XMVectorTrueInt() ) )
			return VISIBLE;  // 2

		// If the center of the sphere is inside all planes and the sphere intersects
		// one or more planes then it must intersect.
		if ( XMVector4EqualInt( CenterInsideAll, XMVectorTrueInt() ) )
			return CLIPPED; // 1

		// The sphere may be outside the frustum or intersecting the frustum.
		// Find the nearest feature (face, edge, or corner) on the frustum
		// to the sphere.

		// The faces adjacent to each face are:
		static const int adjacent_faces[6][4] =
		{
			{ 2, 3, 4, 5 },    // 0
			{ 2, 3, 4, 5 },    // 1
			{ 0, 1, 4, 5 },    // 2
			{ 0, 1, 4, 5 },    // 3
			{ 0, 1, 2, 3 },    // 4
			{ 0, 1, 2, 3 }
		};  // 5

		XMVECTOR Intersects = XMVectorFalseInt();

		// Check to see if the nearest feature is one of the planes.
		for( int i = 0; i < 6; i++ )
		{
			// Find the nearest point on the plane to the center of the sphere.
			XMVECTOR Point = XMVectorSubtract(Center , (XMVectorMultiply( Planes[i] , Dist[i]) ) );

			// Set w of the point to one.
			Point = XMVectorInsert( Point, XMVectorSplatOne(), 0, 0, 0, 0, 1 );

			// If the point is inside the face (inside the adjacent planes) then
			// this plane is the nearest feature.
			XMVECTOR InsideFace = XMVectorTrueInt();

			for ( int j = 0; j < 4; j++ )
			{
				const int plane_index = adjacent_faces[i][j];

				InsideFace = XMVectorAndInt( InsideFace,XMVectorLessOrEqual( XMVector4Dot( Point, Planes[plane_index] ), Zero ) );
			}

			// Since we have already checked distance from the plane we know that the
			// sphere must intersect if this plane is the nearest feature.
			Intersects = XMVectorOrInt( Intersects,
				XMVectorAndInt( XMVectorGreater( Dist[i], Zero ), InsideFace ) );
		}

		if ( XMVector4EqualInt( Intersects, XMVectorTrueInt() ) )
			return CLIPPED; // 1

		// Build the corners of the frustum.
		const XMVECTOR RightTop = XMVectorSet( this->RightSlope, this->TopSlope, 1.0f, 0.0f );
		const XMVECTOR RightBottom = XMVectorSet( this->RightSlope, this->BottomSlope, 1.0f, 0.0f );
		const XMVECTOR LeftTop = XMVectorSet( this->LeftSlope, this->TopSlope, 1.0f, 0.0f );
		const XMVECTOR LeftBottom = XMVectorSet( this->LeftSlope, this->BottomSlope, 1.0f, 0.0f );
		const XMVECTOR Near = XMVectorReplicatePtr( &this->Near );
		const XMVECTOR Far = XMVectorReplicatePtr( &this->Far );

		XMVECTOR Corners[8];
		Corners[0] = XMVectorMultiply(RightTop , Near);
		Corners[1] = XMVectorMultiply(RightBottom , Near);
		Corners[2] = XMVectorMultiply(LeftTop , Near);
		Corners[3] = XMVectorMultiply(LeftBottom , Near);
		Corners[4] = XMVectorMultiply(RightTop , Far);
		Corners[5] = XMVectorMultiply(RightBottom , Far);
		Corners[6] = XMVectorMultiply(LeftTop , Far);
		Corners[7] = XMVectorMultiply(LeftBottom , Far);

		// The Edges are:
		static const int edges[12][2] =
		{
			{ 0, 1 }, { 2, 3 }, { 0, 2 }, { 1, 3 },    // Near plane
			{ 4, 5 }, { 6, 7 }, { 4, 6 }, { 5, 7 },    // Far plane
			{ 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
		}; // Near to far

		const XMVECTOR RadiusSq = XMVectorMultiply(Radius , Radius);

		Line LineSegment;

		// Check to see if the nearest feature is one of the edges (or corners).
		for( int i = 0; i < 12; i++ )
		{
			int ei0 = edges[i][0];
			int ei1 = edges[i][1];

			// Find the nearest point on the edge to the center of the sphere.
			// The corners of the frustum are included as the endpoints of the edges.
			LineSegment.Set(Corners[ei0],Corners[ei1]);

			const XMVECTOR Point = LineSegment.PointOnLineSegmentNearestPoint( Vector4(Center) );

			const XMVECTOR Delta = XMVectorSubtract(Center , Point);

			const XMVECTOR DistSq = XMVector3Dot( Delta, Delta );

			// If the distance to the center of the sphere to the point is less than
			// the radius of the sphere then it must intersect.
			Intersects = XMVectorOrInt( Intersects, XMVectorLessOrEqual( DistSq, RadiusSq ) );
		}

		if ( XMVector4EqualInt( Intersects, XMVectorTrueInt() ) )
			return CLIPPED; // 1

		// The sphere must be outside the frustum.
		return CULLED; // 0
	}

	//-----------------------------------------------------------------------------
	// Exact axis alinged box vs frustum test.  Constructs an oriented box and uses
	// the oriented box vs frustum test.
	//
	// Return values: 0 = no intersection,
	//                1 = intersection,
	//                2 = box is completely inside frustum
	//-----------------------------------------------------------------------------
	__forceinline const eCullClassify Frustum::IntersectAABB( const AABB& pVolumeA) const
	{
		// Make the axis aligned box oriented and do an OBB vs frustum test.
		OBB BoxA;

		BoxA.SetCenter(pVolumeA.GetCenter() );
		BoxA.SetExtents(pVolumeA.GetExtents() );
		BoxA.SetOrientation( Quat(0.0f,0.0f,0.0f,1.0f) );

		return IntersectOBB( BoxA );
	}

	//-----------------------------------------------------------------------------
	// Exact oriented box vs frustum test.
	// Return values: 0 = no intersection,
	//                1 = intersection,
	//                2 = box is completely inside frustum
	//-----------------------------------------------------------------------------
	__forceinline const eCullClassify Frustum::IntersectOBB( const OBB& pVolumeA) const
	{
		static const XMVECTORI32 SelectY =
		{
			XM_SELECT_0, XM_SELECT_1, XM_SELECT_0, XM_SELECT_0
		};
		static const XMVECTORI32 SelectZ =
		{
			XM_SELECT_0, XM_SELECT_0, XM_SELECT_1, XM_SELECT_0
		};

		const XMVECTOR Zero = XMVectorZero();

		// Build the frustum planes.
		XMVECTOR Planes[6];
		Planes[0] = XMVectorSet( 0.0f, 0.0f, -1.0f, this->Near );
		Planes[1] = XMVectorSet( 0.0f, 0.0f, 1.0f, -this->Far );
		Planes[2] = XMVectorSet( 1.0f, 0.0f, -this->RightSlope, 0.0f );
		Planes[3] = XMVectorSet( -1.0f, 0.0f, this->LeftSlope, 0.0f );
		Planes[4] = XMVectorSet( 0.0f, 1.0f, -this->TopSlope, 0.0f );
		Planes[5] = XMVectorSet( 0.0f, -1.0f, this->BottomSlope, 0.0f );

		// Load the box.
		XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&pVolumeA.GetCenter() );
		const XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&pVolumeA.GetExtents() );
		XMVECTOR BoxOrientation = XMLoadFloat4( (XMFLOAT4*)&pVolumeA.GetOrientation().Get() );

		// Transform the oriented box into the space of the frustum in order to
		// minimize the number of transforms we have to do.
		Center = XMVector3InverseRotate( XMVectorSubtract(Center , Origin), this->Orientation.Get() );
		BoxOrientation = XMQuaternionMultiply( BoxOrientation, XMQuaternionConjugate( this->Orientation.Get() ) );

		// Set w of the center to one so we can dot4 with the plane.
		Center = XMVectorInsert( Center, XMVectorSplatOne(), 0, 0, 0, 0, 1);

		// Build the 3x3 rotation matrix that defines the box axes.
		const XMMATRIX R = XMMatrixRotationQuaternion( BoxOrientation );

		// Check against each plane of the frustum.
		XMVECTOR Outside = XMVectorFalseInt();
		XMVECTOR InsideAll = XMVectorTrueInt();
		XMVECTOR CenterInsideAll = XMVectorTrueInt();

		for( int i = 0; i < 6; i++ )
		{
			// Compute the distance to the center of the box.
			const XMVECTOR Dist = XMVector4Dot( Center, Planes[i] );

			// Project the axes of the box onto the normal of the plane.  Half the
			// length of the projection (sometime called the "radius") is equal to
			// h(u) * abs(n dot b(u))) + h(v) * abs(n dot b(v)) + h(w) * abs(n dot b(w))
			// where h(i) are extents of the box, n is the plane normal, and b(i) are the
			// axes of the box.
			XMVECTOR Radius = XMVector3Dot( Planes[i], R.r[0] );
			Radius = XMVectorSelect( Radius, XMVector3Dot( Planes[i], R.r[1] ), SelectY );
			Radius = XMVectorSelect( Radius, XMVector3Dot( Planes[i], R.r[2] ), SelectZ );
			Radius = XMVector3Dot( Extents, XMVectorAbs( Radius ) );

			// Outside the plane?
			Outside = XMVectorOrInt( Outside, XMVectorGreater( Dist, Radius ) );

			// Fully inside the plane?
			InsideAll = XMVectorAndInt( InsideAll, XMVectorLessOrEqual( Dist, XMVectorNegate(Radius ) ) );

			// Check if the center is inside the plane.
			CenterInsideAll = XMVectorAndInt( CenterInsideAll, XMVectorLessOrEqual( Dist, Zero ) );
		}

		// If the box is outside any of the planes it is outside.
		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED; // 0

		// If the box is inside all planes it is fully inside.
		if ( XMVector4EqualInt( InsideAll, XMVectorTrueInt() ) )
			return VISIBLE; // 2

		// If the center of the box is inside all planes and the box intersects
		// one or more planes then it must intersect.
		if ( XMVector4EqualInt( CenterInsideAll, XMVectorTrueInt() ) )
			return CLIPPED; // 1

		// Build the corners of the frustum.
		XMVECTOR RightTop = XMVectorSet( this->RightSlope, this->TopSlope, 1.0f, 0.0f );
		XMVECTOR RightBottom = XMVectorSet( this->RightSlope, this->BottomSlope, 1.0f, 0.0f );
		XMVECTOR LeftTop = XMVectorSet( this->LeftSlope, this->TopSlope, 1.0f, 0.0f );
		XMVECTOR LeftBottom = XMVectorSet( this->LeftSlope, this->BottomSlope, 1.0f, 0.0f );
		XMVECTOR Near = XMVectorReplicatePtr( &this->Near );
		XMVECTOR Far = XMVectorReplicatePtr( &this->Far );

		XMVECTOR Corners[8];
		Corners[0] = XMVectorMultiply(RightTop , Near);
		Corners[1] = XMVectorMultiply(RightBottom , Near);
		Corners[2] = XMVectorMultiply(LeftTop , Near);
		Corners[3] = XMVectorMultiply(LeftBottom , Near);
		Corners[4] = XMVectorMultiply(RightTop , Far);
		Corners[5] = XMVectorMultiply(RightBottom , Far);
		Corners[6] = XMVectorMultiply(LeftTop , Far);
		Corners[7] = XMVectorMultiply(LeftBottom , Far);

		// Test against box axes (3)
		{
			// Find the min/max values of the projection of the frustum onto each axis.
			XMVECTOR FrustumMin, FrustumMax;

			FrustumMin = XMVector3Dot( Corners[0], R.r[0] );
			FrustumMin = XMVectorSelect( FrustumMin, XMVector3Dot( Corners[0], R.r[1] ), SelectY );
			FrustumMin = XMVectorSelect( FrustumMin, XMVector3Dot( Corners[0], R.r[2] ), SelectZ );
			FrustumMax = FrustumMin;

			for( int i = 1; i < 8; i++ )
			{
				XMVECTOR Temp = XMVector3Dot( Corners[i], R.r[0] );
				Temp = XMVectorSelect( Temp, XMVector3Dot( Corners[i], R.r[1] ), SelectY );
				Temp = XMVectorSelect( Temp, XMVector3Dot( Corners[i], R.r[2] ), SelectZ );

				FrustumMin = XMVectorMin( FrustumMin, Temp );
				FrustumMax = XMVectorMax( FrustumMax, Temp );
			}

			// Project the center of the box onto the axes.
			XMVECTOR BoxDist = XMVector3Dot( Center, R.r[0] );
			BoxDist = XMVectorSelect( BoxDist, XMVector3Dot( Center, R.r[1] ), SelectY );
			BoxDist = XMVectorSelect( BoxDist, XMVector3Dot( Center, R.r[2] ), SelectZ );

			// The projection of the box onto the axis is just its Center and Extents.
			// if (min > box_max || max < box_min) reject;
			XMVECTOR Result = XMVectorOrInt( XMVectorGreater( FrustumMin, XMVectorAdd(BoxDist , Extents  ) ),
				XMVectorLess( FrustumMax, XMVectorSubtract(BoxDist , Extents ) ) );

			if( XMVector3AnyTrue( Result ) )
				return CULLED; // 0
		}

		// Test against edge/edge axes (3*6).
		XMVECTOR FrustumEdgeAxis[6];

		FrustumEdgeAxis[0] = RightTop;
		FrustumEdgeAxis[1] = RightBottom;
		FrustumEdgeAxis[2] = LeftTop;
		FrustumEdgeAxis[3] = LeftBottom;
		FrustumEdgeAxis[4] = XMVectorSubtract(RightTop , LeftTop);
		FrustumEdgeAxis[5] = XMVectorSubtract(LeftBottom , LeftTop);

		for( int i = 0; i < 3; i++ )
		{
			for( int j = 0; j < 6; j++ )
			{
				// Compute the axis we are going to test.
				XMVECTOR Axis = XMVector3Cross( R.r[i], FrustumEdgeAxis[j] );

				// Find the min/max values of the projection of the frustum onto the axis.
				XMVECTOR FrustumMin, FrustumMax;

				FrustumMin = FrustumMax = XMVector3Dot( Axis, Corners[0] );

				for( int k = 1; k < 8; k++ )
				{
					XMVECTOR Temp = XMVector3Dot( Axis, Corners[k] );
					FrustumMin = XMVectorMin( FrustumMin, Temp );
					FrustumMax = XMVectorMax( FrustumMax, Temp );
				}

				// Project the center of the box onto the axis.
				const XMVECTOR Dist = XMVector3Dot( Center, Axis );

				// Project the axes of the box onto the axis to find the "radius" of the box.
				XMVECTOR Radius = XMVector3Dot( Axis, R.r[0] );
				Radius = XMVectorSelect( Radius, XMVector3Dot( Axis, R.r[1] ), SelectY );
				Radius = XMVectorSelect( Radius, XMVector3Dot( Axis, R.r[2] ), SelectZ );
				Radius = XMVector3Dot( Extents, XMVectorAbs( Radius ) );

				// if (center > max + radius || center < min - radius) reject;
				Outside = XMVectorOrInt( Outside, XMVectorGreater( Dist, XMVectorAdd(FrustumMax , Radius ) ) );
				Outside = XMVectorOrInt( Outside, XMVectorLess( Dist, XMVectorSubtract(FrustumMin , Radius ) ) );
			}
		}

		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED; // 0

		// If we did not find a separating plane then the box must intersect the frustum.
		return CLIPPED; // 1
	}

	//-----------------------------------------------------------------------------
	// Exact frustum vs frustum test.
	// Return values: 0 = no intersection,
	//                1 = intersection,
	//                2 = frustum A is completely inside frustum B
	//-----------------------------------------------------------------------------
	_inline const eCullClassify Frustum::IntersectFrustum( const Frustum& pVolumeA) const
	{
		// Load origin and orientation of frustum B.
		XMVECTOR OriginB = XMLoadFloat3( (XMFLOAT3*)&this->Origin );
		XMVECTOR OrientationB = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );

		// Build the planes of frustum B.
		XMVECTOR AxisB[6];
		AxisB[0] = XMVectorSet( 0.0f, 0.0f, -1.0f, 0.0f );
		AxisB[1] = XMVectorSet( 0.0f, 0.0f, 1.0f, 0.0f );
		AxisB[2] = XMVectorSet( 1.0f, 0.0f, -this->RightSlope, 0.0f );
		AxisB[3] = XMVectorSet( -1.0f, 0.0f, this->LeftSlope, 0.0f );
		AxisB[4] = XMVectorSet( 0.0f, 1.0f, -this->TopSlope, 0.0f );
		AxisB[5] = XMVectorSet( 0.0f, -1.0f, this->BottomSlope, 0.0f );

		XMVECTOR PlaneDistB[6];
		PlaneDistB[0] = XMVectorNegate(XMVectorReplicatePtr( &this->Near ));
		PlaneDistB[1] = XMVectorReplicatePtr( &this->Far );
		PlaneDistB[2] = XMVectorZero();
		PlaneDistB[3] = XMVectorZero();
		PlaneDistB[4] = XMVectorZero();
		PlaneDistB[5] = XMVectorZero();

		// Load origin and orientation of frustum A.
		XMVECTOR OriginA = XMLoadFloat3( (XMFLOAT3*)&pVolumeA.Origin );
		XMVECTOR OrientationA = XMLoadFloat4( (XMFLOAT4*)&pVolumeA.Orientation.Get() );

//		XMASSERT( XMQuaternionIsUnit( OrientationA ) );

		// Transform frustum A into the space of the frustum B in order to
		// minimize the number of transforms we have to do.
		OriginA = XMVector3InverseRotate( XMVectorSubtract(OriginA , OriginB) , OrientationB );
		OrientationA = XMQuaternionMultiply( OrientationA, XMQuaternionConjugate( OrientationB ) );

		// Build the corners of frustum A (in the local space of B).
		XMVECTOR RightTopA = XMVectorSet( pVolumeA.RightSlope, pVolumeA.TopSlope, 1.0f, 0.0f );
		XMVECTOR RightBottomA = XMVectorSet( pVolumeA.RightSlope, pVolumeA.BottomSlope, 1.0f, 0.0f );
		XMVECTOR LeftTopA = XMVectorSet( pVolumeA.LeftSlope, pVolumeA.TopSlope, 1.0f, 0.0f );
		XMVECTOR LeftBottomA = XMVectorSet( pVolumeA.LeftSlope, pVolumeA.BottomSlope, 1.0f, 0.0f );
		XMVECTOR NearA = XMVectorReplicatePtr( &pVolumeA.Near );
		XMVECTOR FarA = XMVectorReplicatePtr( &pVolumeA.Far );

		RightTopA = XMVector3Rotate( RightTopA, OrientationA );
		RightBottomA = XMVector3Rotate( RightBottomA, OrientationA );
		LeftTopA = XMVector3Rotate( LeftTopA, OrientationA );
		LeftBottomA = XMVector3Rotate( LeftBottomA, OrientationA );

		XMVECTOR CornersA[8];
		CornersA[0] = XMVectorAdd(OriginA , XMVectorMultiply(RightTopA , NearA));
		CornersA[1] = XMVectorAdd(OriginA , XMVectorMultiply(RightBottomA , NearA));
		CornersA[2] = XMVectorAdd(OriginA , XMVectorMultiply(LeftTopA , NearA));
		CornersA[3] = XMVectorAdd(OriginA , XMVectorMultiply(LeftBottomA , NearA));
		CornersA[4] = XMVectorAdd(OriginA , XMVectorMultiply(RightTopA , FarA));
		CornersA[5] = XMVectorAdd(OriginA , XMVectorMultiply(RightBottomA , FarA));
		CornersA[6] = XMVectorAdd(OriginA , XMVectorMultiply(LeftTopA , FarA));
		CornersA[7] = XMVectorAdd(OriginA , XMVectorMultiply(LeftBottomA , FarA));

		// Check frustum A against each plane of frustum B.
		XMVECTOR Outside = XMVectorFalseInt();
		XMVECTOR InsideAll = XMVectorTrueInt();

		for( int i = 0; i < 6; i++ )
		{
			// Find the min/max projection of the frustum onto the plane normal.
			XMVECTOR Min, Max;

			Min = Max = XMVector3Dot( AxisB[i], CornersA[0] );

			for( int j = 1; j < 8; j++ )
			{
				const XMVECTOR Temp = XMVector3Dot( AxisB[i], CornersA[j] );
				Min = XMVectorMin( Min, Temp );
				Max = XMVectorMax( Max, Temp );
			}

			// Outside the plane?
			Outside = XMVectorOrInt( Outside, XMVectorGreater( Min, PlaneDistB[i] ) );

			// Fully inside the plane?
			InsideAll = XMVectorAndInt( InsideAll, XMVectorLessOrEqual( Max, PlaneDistB[i] ) );
		}

		// If the frustum A is outside any of the planes of frustum B it is outside.
		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED; // 0

		// If frustum A is inside all planes of frustum B it is fully inside.
		if ( XMVector4EqualInt( InsideAll, XMVectorTrueInt() ) )
			return VISIBLE; // 2

		// Build the corners of frustum B.
		XMVECTOR RightTopB = XMVectorSet( this->RightSlope, this->TopSlope, 1.0f, 0.0f );
		XMVECTOR RightBottomB = XMVectorSet( this->RightSlope, this->BottomSlope, 1.0f, 0.0f );
		XMVECTOR LeftTopB = XMVectorSet( this->LeftSlope, this->TopSlope, 1.0f, 0.0f );
		XMVECTOR LeftBottomB = XMVectorSet( this->LeftSlope, this->BottomSlope, 1.0f, 0.0f );
		XMVECTOR NearB = XMVectorReplicatePtr( &this->Near );
		XMVECTOR FarB = XMVectorReplicatePtr( &this->Far );

		XMVECTOR CornersB[8];
		CornersB[0] = XMVectorMultiply(RightTopB , NearB);
		CornersB[1] = XMVectorMultiply(RightBottomB , NearB);
		CornersB[2] = XMVectorMultiply(LeftTopB , NearB);
		CornersB[3] = XMVectorMultiply(LeftBottomB , NearB);
		CornersB[4] = XMVectorMultiply(RightTopB , FarB);
		CornersB[5] = XMVectorMultiply(RightBottomB , FarB);
		CornersB[6] = XMVectorMultiply(LeftTopB , FarB);
		CornersB[7] = XMVectorMultiply(LeftBottomB , FarB);

		// Build the planes of frustum A (in the local space of B).
		XMVECTOR AxisA[6];
		XMVECTOR PlaneDistA[6];

		AxisA[0] = XMVectorSet( 0.0f, 0.0f, -1.0f, 0.0f );
		AxisA[1] = XMVectorSet( 0.0f, 0.0f, 1.0f, 0.0f );
		AxisA[2] = XMVectorSet( 1.0f, 0.0f, -pVolumeA.RightSlope, 0.0f );
		AxisA[3] = XMVectorSet( -1.0f, 0.0f, pVolumeA.LeftSlope, 0.0f );
		AxisA[4] = XMVectorSet( 0.0f, 1.0f, -pVolumeA.TopSlope, 0.0f );
		AxisA[5] = XMVectorSet( 0.0f, -1.0f, pVolumeA.BottomSlope, 0.0f );

		AxisA[0] = XMVector3Rotate( AxisA[0], OrientationA );
		AxisA[1] = XMVectorNegate(AxisA[0]);
		AxisA[2] = XMVector3Rotate( AxisA[2], OrientationA );
		AxisA[3] = XMVector3Rotate( AxisA[3], OrientationA );
		AxisA[4] = XMVector3Rotate( AxisA[4], OrientationA );
		AxisA[5] = XMVector3Rotate( AxisA[5], OrientationA );

		PlaneDistA[0] = XMVector3Dot( AxisA[0], CornersA[0] );  // Re-use corner on near plane.
		PlaneDistA[1] = XMVector3Dot( AxisA[1], CornersA[4] );  // Re-use corner on far plane.
		PlaneDistA[2] = XMVector3Dot( AxisA[2], OriginA );
		PlaneDistA[3] = XMVector3Dot( AxisA[3], OriginA );
		PlaneDistA[4] = XMVector3Dot( AxisA[4], OriginA );
		PlaneDistA[5] = XMVector3Dot( AxisA[5], OriginA );

		// Check each axis of frustum A for a seperating plane (5).
		for( int i = 0; i < 6; i++ )
		{
			// Find the minimum projection of the frustum onto the plane normal.
			XMVECTOR Min;

			Min = XMVector3Dot( AxisA[i], CornersB[0] );

			for( int j = 1; j < 8; j++ )
			{
				const XMVECTOR Temp = XMVector3Dot( AxisA[i], CornersB[j] );
				Min = XMVectorMin( Min, Temp );
			}

			// Outside the plane?
			Outside = XMVectorOrInt( Outside, XMVectorGreater( Min, PlaneDistA[i] ) );
		}

		// If the frustum B is outside any of the planes of frustum A it is outside.
		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED; // 0

		// Check edge/edge axes (6 * 6).
		XMVECTOR FrustumEdgeAxisA[6];
		FrustumEdgeAxisA[0] = RightTopA;
		FrustumEdgeAxisA[1] = RightBottomA;
		FrustumEdgeAxisA[2] = LeftTopA;
		FrustumEdgeAxisA[3] = LeftBottomA;
		FrustumEdgeAxisA[4] = XMVectorSubtract(RightTopA , LeftTopA);
		FrustumEdgeAxisA[5] = XMVectorSubtract(LeftBottomA , LeftTopA);

		XMVECTOR FrustumEdgeAxisB[6];
		FrustumEdgeAxisB[0] = RightTopB;
		FrustumEdgeAxisB[1] = RightBottomB;
		FrustumEdgeAxisB[2] = LeftTopB;
		FrustumEdgeAxisB[3] = LeftBottomB;
		FrustumEdgeAxisB[4] = XMVectorSubtract(RightTopB , LeftTopB);
		FrustumEdgeAxisB[5] = XMVectorSubtract(LeftBottomB , LeftTopB);

		for( int i = 0; i < 6; i++ )
		{
			for( int j = 0; j < 6; j++ )
			{
				// Compute the axis we are going to test.
				const XMVECTOR Axis = XMVector3Cross( FrustumEdgeAxisA[i], FrustumEdgeAxisB[j] );

				// Find the min/max values of the projection of both frustums onto the axis.
				XMVECTOR MinA, MaxA;
				XMVECTOR MinB, MaxB;

				MinA = MaxA = XMVector3Dot( Axis, CornersA[0] );
				MinB = MaxB = XMVector3Dot( Axis, CornersB[0] );

				for( int k = 1; k < 8; k++ )
				{
					const XMVECTOR TempA = XMVector3Dot( Axis, CornersA[k] );
					MinA = XMVectorMin( MinA, TempA );
					MaxA = XMVectorMax( MaxA, TempA );

					const XMVECTOR TempB = XMVector3Dot( Axis, CornersB[k] );
					MinB = XMVectorMin( MinB, TempB );
					MaxB = XMVectorMax( MaxB, TempB );
				}

				// if (MinA > MaxB || MinB > MaxA) reject
				Outside = XMVectorOrInt( Outside, XMVectorGreater( MinA, MaxB ) );
				Outside = XMVectorOrInt( Outside, XMVectorGreater( MinB, MaxA ) );
			}
		}

		// If there is a seperating plane, then the frustums do not intersect.
		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED; // 0

		// If we did not find a separating plane then the frustums intersect.
		return CLIPPED; // 1
	}

	_inline const eCullClassify Frustum::Intersect6Planes( const Plane& Plane0,const Plane& Plane1, const Plane& Plane2,const Plane& Plane3,const  Plane& Plane4, const Plane& Plane5 ) const
	{
		// Load origin and orientation of the frustum.
		XMVECTOR Origin = XMLoadFloat3( (XMFLOAT3*)&this->Origin );
		XMVECTOR Orientation = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );

		assert( Quat::IsUnit( Orientation ) );

		// Set w of the origin to one so we can dot4 with a plane.
		Origin = XMVectorInsert( Origin, XMVectorSplatOne(), 0, 0, 0, 0, 1 );

		// Build the corners of the frustum (in world space).
		XMVECTOR RightTop = XMVectorSet( this->RightSlope, this->TopSlope, 1.0f, 0.0f );
		XMVECTOR RightBottom = XMVectorSet( this->RightSlope, this->BottomSlope, 1.0f, 0.0f );
		XMVECTOR LeftTop = XMVectorSet( this->LeftSlope, this->TopSlope, 1.0f, 0.0f );
		XMVECTOR LeftBottom = XMVectorSet( this->LeftSlope, this->BottomSlope, 1.0f, 0.0f );
		XMVECTOR Near = XMVectorSet( this->Near, this->Near, this->Near, 0.0f );
		XMVECTOR Far = XMVectorSet( this->Far, this->Far, this->Far, 0.0f );

		RightTop = XMVector3Rotate( RightTop, Orientation );
		RightBottom = XMVector3Rotate( RightBottom, Orientation );
		LeftTop = XMVector3Rotate( LeftTop, Orientation );
		LeftBottom = XMVector3Rotate( LeftBottom, Orientation );

		const XMVECTOR Corners0 = XMVectorAdd(Origin , XMVectorMultiply(RightTop , Near));
		const XMVECTOR Corners1 = XMVectorAdd(Origin , XMVectorMultiply(RightBottom , Near));
		const XMVECTOR Corners2 = XMVectorAdd(Origin , XMVectorMultiply(LeftTop , Near));
		const XMVECTOR Corners3 = XMVectorAdd(Origin , XMVectorMultiply(LeftBottom , Near));
		const XMVECTOR Corners4 = XMVectorAdd(Origin , XMVectorMultiply(RightTop , Far));
		const XMVECTOR Corners5 = XMVectorAdd(Origin , XMVectorMultiply(RightBottom , Far));
		const XMVECTOR Corners6 = XMVectorAdd(Origin , XMVectorMultiply(LeftTop , Far));
		const XMVECTOR Corners7 = XMVectorAdd(Origin , XMVectorMultiply(LeftBottom , Far));

		XMVECTOR Outside, Inside;

		// Test against each plane.
		FastIntersectFrustumPlane( Vector4(Corners0), Vector4(Corners1), Vector4(Corners2), Vector4(Corners3),Vector4(Corners4),
			Vector4(Corners5), Vector4(Corners6),Vector4(Corners7),Plane(Plane0), Outside, Inside );

		XMVECTOR AnyOutside = Outside;
		XMVECTOR AllInside = Inside;

		FastIntersectFrustumPlane( Vector4(Corners0), Vector4(Corners1), Vector4(Corners2), Vector4(Corners3),Vector4(Corners4),
			Vector4(Corners5), Vector4(Corners6),Vector4(Corners7),Plane(Plane1), Outside, Inside );

		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectFrustumPlane( Vector4(Corners0), Vector4(Corners1), Vector4(Corners2), Vector4(Corners3),Vector4(Corners4),
			Vector4(Corners5), Vector4(Corners6),Vector4(Corners7),Plane(Plane2), Outside, Inside );

		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectFrustumPlane( Vector4(Corners0), Vector4(Corners1), Vector4(Corners2), Vector4(Corners3),Vector4(Corners4),
			Vector4(Corners5), Vector4(Corners6),Vector4(Corners7),Plane(Plane3), Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectFrustumPlane( Vector4(Corners0), Vector4(Corners1), Vector4(Corners2), Vector4(Corners3),Vector4(Corners4),
			Vector4(Corners5), Vector4(Corners6),Vector4(Corners7),Plane(Plane4), Outside, Inside );

		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectFrustumPlane( Vector4(Corners0), Vector4(Corners1), Vector4(Corners2), Vector4(Corners3),Vector4(Corners4),
			Vector4(Corners5), Vector4(Corners6),Vector4(Corners7),Plane(Plane5), Outside, Inside );

		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		// If the frustum is outside any plane it is outside.
		if ( XMVector4EqualInt( AnyOutside, XMVectorTrueInt() ) )
			return CULLED; // 0

		// If the frustum is inside all planes it is inside.
		if ( XMVector4EqualInt( AllInside, XMVectorTrueInt() ) )
			return VISIBLE; // 2

		// The frustum is not inside all planes or outside a plane, it may intersect.
		return CLIPPED; // 1
	}

	_inline const eCullClassify Frustum::IntersectPlane( const Plane& Plane0 ) const
	{
		assert( Plane0.IsUnit() );

		// Load origin and orientation of the frustum.
		XMVECTOR Origin = XMLoadFloat3( (XMFLOAT3*)&this->Origin );
		XMVECTOR Orientation = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );

		assert( Quat::IsUnit( Orientation ) );

		// Set w of the origin to one so we can dot4 with a plane.
		Origin = XMVectorInsert( Origin, XMVectorSplatOne(), 0, 0, 0, 0, 1);

		// Build the corners of the frustum (in world space).
		XMVECTOR RightTop = XMVectorSet( this->RightSlope, this->TopSlope, 1.0f, 0.0f );
		XMVECTOR RightBottom = XMVectorSet( this->RightSlope, this->BottomSlope, 1.0f, 0.0f );
		XMVECTOR LeftTop = XMVectorSet( this->LeftSlope, this->TopSlope, 1.0f, 0.0f );
		XMVECTOR LeftBottom = XMVectorSet( this->LeftSlope, this->BottomSlope, 1.0f, 0.0f );
		XMVECTOR Near = XMVectorSet( this->Near, this->Near, this->Near, 0.0f );
		XMVECTOR Far = XMVectorSet( this->Far, this->Far, this->Far, 0.0f );

		RightTop = XMVector3Rotate( RightTop, Orientation );
		RightBottom = XMVector3Rotate( RightBottom, Orientation );
		LeftTop = XMVector3Rotate( LeftTop, Orientation );
		LeftBottom = XMVector3Rotate( LeftBottom, Orientation );

		const XMVECTOR Corners0 = XMVectorAdd(Origin , XMVectorMultiply(RightTop , Near));
		const XMVECTOR Corners1 = XMVectorAdd(Origin , XMVectorMultiply(RightBottom , Near));
		const XMVECTOR Corners2 = XMVectorAdd(Origin , XMVectorMultiply(LeftTop , Near));
		const XMVECTOR Corners3 = XMVectorAdd(Origin , XMVectorMultiply(LeftBottom , Near));
		const XMVECTOR Corners4 = XMVectorAdd(Origin , XMVectorMultiply(RightTop , Far));
		const XMVECTOR Corners5 = XMVectorAdd(Origin , XMVectorMultiply(RightBottom , Far));
		const XMVECTOR Corners6 = XMVectorAdd(Origin , XMVectorMultiply(LeftTop , Far));
		const XMVECTOR Corners7 = XMVectorAdd(Origin , XMVectorMultiply(LeftBottom , Far));

		XMVECTOR Outside, Inside;
		FastIntersectFrustumPlane( Vector4(Corners0), Vector4(Corners1), Vector4(Corners2), Vector4(Corners3),
			Vector4(Corners4), Vector4(Corners5), Vector4(Corners6), Vector4(Corners7), Plane0, Outside, Inside );

		// If the frustum is outside any plane it is outside.
		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED; // 0

		// If the frustum is inside all planes it is inside.
		if ( XMVector4EqualInt( Inside, XMVectorTrueInt() ) )
			return VISIBLE; // 2

		// The frustum is not inside all planes or outside a plane it intersects.
		return CLIPPED; // 1
	}
}// end of Namespace TurboMath