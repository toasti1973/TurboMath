

// -------------------------------------------------------------------
// File			:	OBB.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for OBB-Class
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
	//-----------------------------------------------------------------------------
	// Constructor / Destructor
	//-----------------------------------------------------------------------------
	XM_INLINE OBB::OBB(const Vector4& c, const Vector4& e, const Quat& o) noexcept :
    	Center(c), Extents(e), Orientation(o)
	{
	}

	OBB::OBB() noexcept
	{
        	Reset();
	}
	
	// Get / Set-Functions
	XM_INLINE void XM_CALLCONV OBB::SetCenter(const Vector4& newCenter) noexcept
	{
		Center = newCenter;
	}

	XM_INLINE void XM_CALLCONV OBB::SetExtents(const Vector4& newExtents) noexcept
	{
		Extents = newExtents;
	}

	XM_INLINE void XM_CALLCONV OBB::SetOrientation(const Quat& newOrientation) noexcept
	{
		Orientation = newOrientation;
	}

	XM_INLINE const Vector4 XM_CALLCONV OBB::GetCenter() const noexcept
	{
		return Center;
	}

	XM_INLINE const Vector4 XM_CALLCONV OBB::GetExtents() const noexcept
	{
		return Extents;
	}

	XM_INLINE const Quat XM_CALLCONV OBB::GetOrientation() const noexcept
	{
		return Orientation;
	}

	XM_INLINE void XM_CALLCONV OBB::Reset() noexcept
	{
       		Center.NullVec();
        	Extents.NullVec();
        	Orientation.Identity();
	}
	

	//-----------------------------------------------------------------------------
	// Find the approximate minimum oriented bounding box containing a set of
	// points.  Exact computation of minimum oriented bounding box is possible but
	// is slower and requires a more complex algorithm.
	// The algorithm works by computing the inertia tensor of the points and then
	// using the eigenvectors of the intertia tensor as the axes of the box.
	// Computing the intertia tensor of the convex hull of the points will usually
	// result in better bounding box but the computation is more complex.
	// Exact computation of the minimum oriented bounding box is possible but the
	// best know algorithm is O(N^3) and is significanly more complex to implement.
	//-----------------------------------------------------------------------------
	void XM_CALLCONV OBB::ComputeBoundingOBBFromPoints( UINT Count, const XMFLOAT3* pPoints, UINT Stride )
	{
		static constexpr XMVECTORI32 PermuteXXY =
		{
			XM_PERMUTE_0X, XM_PERMUTE_0X, XM_PERMUTE_0Y, XM_PERMUTE_0W
		};
		static constexpr XMVECTORI32 PermuteYZZ =
		{
			XM_PERMUTE_0Y, XM_PERMUTE_0Z, XM_PERMUTE_0Z, XM_PERMUTE_0W
		};

		assert( Count > 0 );
		assert( pPoints );

		XMVECTOR CenterOfMass = XMVectorZero();

		// Compute the center of mass and inertia tensor of the points.
		for( UINT i = 0; i < Count; i++ )
		{
//			XM_PREFETCH( ( char* )pPoints + (i+1) * Stride )
			XMVECTOR Point = XMLoadFloat3( ( XMFLOAT3* )( ( char* )pPoints + i * Stride ) );

			CenterOfMass += Point;
		}

		CenterOfMass *= XMVectorReciprocal( XMVectorReplicate( float( Count ) ) );

		// Compute the inertia tensor of the points around the center of mass.
		// Using the center of mass is not strictly necessary, but will hopefully
		// improve the stability of finding the eigenvectors.
		XMVECTOR XX_YY_ZZ = XMVectorZero();
		XMVECTOR XY_XZ_YZ = XMVectorZero();

		for( UINT i = 0; i < Count; i++ )
		{
			const XMVECTOR Point = XMVectorSubtract(XMLoadFloat3( ( XMFLOAT3* )( ( char* )pPoints + i * Stride ) ) , CenterOfMass);

			XX_YY_ZZ += XMVectorMultiply(Point , Point);

//			XMVECTOR XXY = XMVectorPermute( Point, Point, PermuteXXY );
			XMVECTOR XXY = XMVectorPermute<XM_PERMUTE_0X, XM_PERMUTE_0X, XM_PERMUTE_0Y, XM_PERMUTE_0W>( Point, Point );
//			XMVECTOR YZZ = XMVectorPermute( Point, Point, PermuteYZZ );
			XMVECTOR YZZ = XMVectorPermute<XM_PERMUTE_0Y, XM_PERMUTE_0Z, XM_PERMUTE_0Z, XM_PERMUTE_0W>( Point, Point );

			XY_XZ_YZ += XMVectorMultiply(XXY , YZZ);
		}

		XMVECTOR v1, v2, v3;

		// Compute the eigenvectors of the inertia tensor.
		CalculateEigenVectorsFromCovarianceMatrix( XMVectorGetX( XX_YY_ZZ ), XMVectorGetY( XX_YY_ZZ ),
			XMVectorGetZ( XX_YY_ZZ ),
			XMVectorGetX( XY_XZ_YZ ), XMVectorGetY( XY_XZ_YZ ),
			XMVectorGetZ( XY_XZ_YZ ),
			&v1, &v2, &v3 );

		// Put them in a matrix.
		XMMATRIX R;

		R.r[0] = XMVectorSetW( v1, 0.f );
		R.r[1] = XMVectorSetW( v2, 0.f );
		R.r[2] = XMVectorSetW( v3, 0.f );
		R.r[3] = XMVectorSetBinaryConstant( 0, 0, 0, 1 );

		// Multiply by -1 to convert the matrix into a right handed coordinate
		// system (Det ~= 1) in case the eigenvectors form a left handed
		// coordinate system (Det ~= -1) because XMQuaternionRotationMatrix only
		// works on right handed matrices.
		const XMVECTOR Det = XMMatrixDeterminant( R );

		if( XMVector4Less( Det, XMVectorZero() ) )
		{
			constexpr XMVECTORF32 VectorNegativeOne =
			{
				-1.0f, -1.0f, -1.0f, -1.0f
			};

			R.r[0] *= VectorNegativeOne;
			R.r[1] *= VectorNegativeOne;
			R.r[2] *= VectorNegativeOne;
		}

		// Get the rotation quaternion from the matrix.
		XMVECTOR Orientation = XMQuaternionRotationMatrix( R );

		// Make sure it is normal (in case the vectors are slightly non-orthogonal).
		Orientation = XMQuaternionNormalize( Orientation );

		// Rebuild the rotation matrix from the quaternion.
		R = XMMatrixRotationQuaternion( Orientation );

		// Build the rotation into the rotated space.
		const XMMATRIX InverseR = XMMatrixTranspose( R );

		// Find the minimum OBB using the eigenvectors as the axes.
		XMVECTOR vMin, vMax;

		vMin = vMax = XMVector3TransformNormal( XMLoadFloat3( pPoints ), InverseR );

		for( UINT i = 1; i < Count; i++ )
		{
			const XMVECTOR Point = XMVector3TransformNormal( XMLoadFloat3( ( XMFLOAT3* )( ( char* )pPoints + i * Stride ) ), InverseR );

			vMin = XMVectorMin( vMin, Point );
			vMax = XMVectorMax( vMax, Point );
		}

		// Rotate the center into world space.
		XMVECTOR Center = XMVectorMultiply(XMVectorAdd( vMin , vMax ) , XMVectorReplicate(0.5f));
		Center = XMVector3TransformNormal( Center, R );

		// Store center, extents, and orientation.
		XMStoreFloat3( (XMFLOAT3*)&this->Center.GetRaw(), Center );
		XMStoreFloat3( (XMFLOAT3*)&this->Extents.GetRaw(), XMVectorMultiply(XMVectorSubtract( vMax , vMin ) , XMVectorReplicate(0.5f) ) );
		XMStoreFloat4( (XMFLOAT4*)&this->Orientation.Get(), Orientation );

		return;
	}

	//-----------------------------------------------------------------------------
	// Transform an oriented box by an angle preserving transform.
	//-----------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV OBB::Transform( const float Scale, const Quat& Rotation,const Vector4& Translation )
	{
		assert( Rotation.IsUnit() );

		// Load the box.
		XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center.GetRaw() );
		XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&this->Extents.GetRaw() );
		XMVECTOR Orientation = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );

		assert( Quat::IsUnit(Orientation) );

		// Composite the box rotation and the transform rotation.
		Orientation = XMQuaternionMultiply( Orientation, Rotation.Get() );

		// Transform the center.
		XMVECTOR VectorScale = XMVectorReplicate( Scale );
		Center = XMVectorAdd(XMVector3Rotate( XMVectorMultiply(Center , VectorScale) , Rotation.Get() ) , Translation.GetRaw());

		// Scale the box extents.
		Extents = XMVectorMultiply(Extents , VectorScale);

		// Store the box.
		XMStoreFloat3( (XMFLOAT3*)&this->Center.GetRaw(), Center );
		XMStoreFloat3( (XMFLOAT3*)&this->Extents.GetRaw(), Extents );
		XMStoreFloat4( (XMFLOAT4*)&this->Orientation.Get(), Orientation );

		return;
	}

	//-----------------------------------------------------------------------------
	// Point in oriented box test.
	//-----------------------------------------------------------------------------
	XM_INLINE const bool XM_CALLCONV OBB::IntersectPoint( const Vector4& Point )
	{
		const XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center.GetRaw() );
		const XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&this->Extents.GetRaw() );
		const XMVECTOR Orientation = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );

		assert( Quat::IsUnit(Orientation) );

		// Transform the point to be local to the box.
		const XMVECTOR TPoint = XMVector3InverseRotate( XMVectorSubtract(Point.GetRaw() , Center) , Orientation );

		return XMVector3InBounds( TPoint, Extents );
	}

	//-----------------------------------------------------------------------------
	// Fast oriented box / oriented box intersection test using the separating axis
	// theorem.
	//-----------------------------------------------------------------------------
	const bool XM_CALLCONV OBB::IntersectOBB( const OBB* pVolumeB )
	{
		assert( pVolumeB );

		// Build the 3x3 rotation matrix that defines the orientation of B relative to A.
		const XMVECTOR A_quat = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );
		const XMVECTOR B_quat = XMLoadFloat4( (XMFLOAT4*)&pVolumeB->Orientation.Get() );

		assert( Quat::IsUnit(A_quat) );
		assert( Quat::IsUnit(B_quat) );

		const XMVECTOR Q = XMQuaternionMultiply( A_quat, XMQuaternionConjugate( B_quat ) );
		XMMATRIX R = XMMatrixRotationQuaternion( Q );

		// Compute the translation of B relative to A.
		const XMVECTOR A_cent = XMLoadFloat3( (XMFLOAT3*)&this->Center.GetRaw() );
		const XMVECTOR B_cent = XMLoadFloat3( (XMFLOAT3*)&pVolumeB->Center.GetRaw() );
		const XMVECTOR t = XMVector3InverseRotate( XMVectorSubtract(B_cent , A_cent), A_quat );

		//
		// h(A) = extents of A.
		// h(B) = extents of B.
		//
		// a(u) = axes of A = (1,0,0), (0,1,0), (0,0,1)
		// b(u) = axes of B relative to A = (r00,r10,r20), (r01,r11,r21), (r02,r12,r22)
		//
		// For each possible separating axis l:
		//   d(A) = sum (for i = u,v,w) h(A)(i) * abs( a(i) dot l )
		//   d(B) = sum (for i = u,v,w) h(B)(i) * abs( b(i) dot l )
		//   if abs( t dot l ) > d(A) + d(B) then disjoint
		//

		// Load extents of A and B.
		const XMVECTOR h_A = XMLoadFloat3( (XMFLOAT3*)&this->Extents.GetRaw() );
		const XMVECTOR h_B = XMLoadFloat3( (XMFLOAT3*)&pVolumeB->Extents.GetRaw() );

		// Rows. Note R[0,1,2]X.w = 0.
		const XMVECTOR R0X = R.r[0];
		const XMVECTOR R1X = R.r[1];
		const XMVECTOR R2X = R.r[2];

		R = XMMatrixTranspose( R );

		// Columns. Note RX[0,1,2].w = 0.
		const XMVECTOR RX0 = R.r[0];
		const XMVECTOR RX1 = R.r[1];
		const XMVECTOR RX2 = R.r[2];

		// Absolute value of rows.
		const XMVECTOR AR0X = XMVectorAbs( R0X );
		const XMVECTOR AR1X = XMVectorAbs( R1X );
		const XMVECTOR AR2X = XMVectorAbs( R2X );

		// Absolute value of columns.
		const XMVECTOR ARX0 = XMVectorAbs( RX0 );
		const XMVECTOR ARX1 = XMVectorAbs( RX1 );
		const XMVECTOR ARX2 = XMVectorAbs( RX2 );

		// Test each of the 15 possible seperating axii.
		XMVECTOR d, d_A, d_B;

		// l = a(u) = (1, 0, 0)
		// t dot l = t.x
		// d(A) = h(A).x
		// d(B) = h(B) dot abs(r00, r01, r02)
		d = XMVectorSplatX( t );
		d_A = XMVectorSplatX( h_A );
		d_B = XMVector3Dot( h_B, AR0X );
		XMVECTOR NoIntersection = XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) );

		// l = a(v) = (0, 1, 0)
		// t dot l = t.y
		// d(A) = h(A).y
		// d(B) = h(B) dot abs(r10, r11, r12)
		d = XMVectorSplatY( t );
		d_A = XMVectorSplatY( h_A );
		d_B = XMVector3Dot( h_B, AR1X );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = a(w) = (0, 0, 1)
		// t dot l = t.z
		// d(A) = h(A).z
		// d(B) = h(B) dot abs(r20, r21, r22)
		d = XMVectorSplatZ( t );
		d_A = XMVectorSplatZ( h_A );
		d_B = XMVector3Dot( h_B, AR2X );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = b(u) = (r00, r10, r20)
		// d(A) = h(A) dot abs(r00, r10, r20)
		// d(B) = h(B).x
		d = XMVector3Dot( t, RX0 );
		d_A = XMVector3Dot( h_A, ARX0 );
		d_B = XMVectorSplatX( h_B );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = b(v) = (r01, r11, r21)
		// d(A) = h(A) dot abs(r01, r11, r21)
		// d(B) = h(B).y
		d = XMVector3Dot( t, RX1 );
		d_A = XMVector3Dot( h_A, ARX1 );
		d_B = XMVectorSplatY( h_B );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = b(w) = (r02, r12, r22)
		// d(A) = h(A) dot abs(r02, r12, r22)
		// d(B) = h(B).z
		d = XMVector3Dot( t, RX2 );
		d_A = XMVector3Dot( h_A, ARX2 );
		d_B = XMVectorSplatZ( h_B );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = a(u) x b(u) = (0, -r20, r10)
		// d(A) = h(A) dot abs(0, r20, r10)
		// d(B) = h(B) dot abs(0, r02, r01)
		d = XMVector3Dot( t, XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_1Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( RX0, XMVectorNegate(RX0) ) );
		d_A = XMVector3Dot( h_A, XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_0Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( ARX0, ARX0 ) );
		d_B = XMVector3Dot( h_B, XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_0Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( AR0X, AR0X ) );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = a(u) x b(v) = (0, -r21, r11)
		// d(A) = h(A) dot abs(0, r21, r11)
		// d(B) = h(B) dot abs(r02, 0, r00)
		d = XMVector3Dot( t, XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_1Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( RX1, XMVectorNegate(RX1) ) );
		d_A = XMVector3Dot( h_A, XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_0Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( ARX1, ARX1 ) );
		d_B = XMVector3Dot( h_B, XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_0X, XM_PERMUTE_0Y>( AR0X, AR0X ) );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = a(u) x b(w) = (0, -r22, r12)
		// d(A) = h(A) dot abs(0, r22, r12)
		// d(B) = h(B) dot abs(r01, r00, 0)
		d = XMVector3Dot( t, XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_1Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( RX2, XMVectorNegate(RX2)) );
		d_A = XMVector3Dot( h_A, XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_0Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( ARX2, ARX2 ) );
		d_B = XMVector3Dot( h_B, XMVectorPermute<XM_PERMUTE_0Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( AR0X, AR0X ) );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = a(v) x b(u) = (r20, 0, -r00)
		// d(A) = h(A) dot abs(r20, 0, r00)
		// d(B) = h(B) dot abs(0, r12, r11)
		d = XMVector3Dot( t, XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_1X, XM_PERMUTE_0Y>( RX0, XMVectorNegate(RX0)  ) );
		d_A = XMVector3Dot( h_A, XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_0X, XM_PERMUTE_0Y>( ARX0, ARX0 ) );
		d_B = XMVector3Dot( h_B, XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_0Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( AR1X, AR1X ) );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = a(v) x b(v) = (r21, 0, -r01)
		// d(A) = h(A) dot abs(r21, 0, r01)
		// d(B) = h(B) dot abs(r12, 0, r10)
		d = XMVector3Dot( t, XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_1X, XM_PERMUTE_0Y>( RX1, XMVectorNegate(RX1) ) );
		d_A = XMVector3Dot( h_A, XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_0X, XM_PERMUTE_0Y>( ARX1, ARX1 ) );
		d_B = XMVector3Dot( h_B, XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_0X, XM_PERMUTE_0Y>( AR1X, AR1X ) );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = a(v) x b(w) = (r22, 0, -r02)
		// d(A) = h(A) dot abs(r22, 0, r02)
		// d(B) = h(B) dot abs(r11, r10, 0)
		d = XMVector3Dot( t, XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_1X, XM_PERMUTE_0Y>( RX2, XMVectorNegate(RX2) ) );
		d_A = XMVector3Dot( h_A, XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_0X, XM_PERMUTE_0Y>( ARX2, ARX2 ) );
		d_B = XMVector3Dot( h_B, XMVectorPermute<XM_PERMUTE_0Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( AR1X, AR1X ) );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = a(w) x b(u) = (-r10, r00, 0)
		// d(A) = h(A) dot abs(r10, r00, 0)
		// d(B) = h(B) dot abs(0, r22, r21)
		d = XMVector3Dot( t, XMVectorPermute<XM_PERMUTE_1Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( RX0, XMVectorNegate(RX0) ) );
		d_A = XMVector3Dot( h_A, XMVectorPermute<XM_PERMUTE_0Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( ARX0, ARX0 ) );
		d_B = XMVector3Dot( h_B, XMVectorPermute<XM_PERMUTE_0W, XM_PERMUTE_0Z, XM_PERMUTE_0Y, XM_PERMUTE_0X>( AR2X, AR2X) );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = a(w) x b(v) = (-r11, r01, 0)
		// d(A) = h(A) dot abs(r11, r01, 0)
		// d(B) = h(B) dot abs(r22, 0, r20)
		d = XMVector3Dot( t, XMVectorPermute<XM_PERMUTE_1Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( RX1, XMVectorNegate(RX1) ) );
		d_A = XMVector3Dot( h_A, XMVectorPermute<XM_PERMUTE_0Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( ARX1, ARX1 ) );
		d_B = XMVector3Dot( h_B, XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_0W, XM_PERMUTE_0X, XM_PERMUTE_0Y>( AR2X, AR2X ) );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// l = a(w) x b(w) = (-r12, r02, 0)
		// d(A) = h(A) dot abs(r12, r02, 0)
		// d(B) = h(B) dot abs(r21, r20, 0)
		d = XMVector3Dot( t, XMVectorPermute<XM_PERMUTE_1Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( RX2, XMVectorNegate(RX2)) );
		d_A = XMVector3Dot( h_A, XMVectorPermute<XM_PERMUTE_0Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( ARX2, ARX2 ) );
		d_B = XMVector3Dot( h_B, XMVectorPermute<XM_PERMUTE_0Y, XM_PERMUTE_0X, XM_PERMUTE_0W, XM_PERMUTE_0Z>( AR2X, AR2X ) );
		NoIntersection = XMVectorOrInt( NoIntersection,	XMVectorGreater( XMVectorAbs(d), XMVectorAdd( d_A, d_B ) ) );

		// No seperating axis found, boxes must intersect.
		return XMVector4NotEqualInt( NoIntersection, XMVectorTrueInt() );
	}

	//-----------------------------------------------------------------------------
	// Compute the intersection of a ray (Origin, Direction) with an oriented box
	// using the slabs method.
	//-----------------------------------------------------------------------------
	const bool XM_CALLCONV OBB::IntersectRay( Ray& theRay, float* pDist )
	{
		assert( pDist );
		assert( theRay.GetDirection().IsUnit() );

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
		static constexpr XMVECTORI32 SelectY =
		{
			XM_SELECT_0, XM_SELECT_1, XM_SELECT_0, XM_SELECT_0
		};
		static constexpr XMVECTORI32 SelectZ =
		{
			XM_SELECT_0, XM_SELECT_0, XM_SELECT_1, XM_SELECT_0
		};

		// Load the box.
		const XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center.GetRaw() );
		const XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&this->Extents.GetRaw() );
		const XMVECTOR Orientation = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );

		assert( Quat::IsUnit( Orientation ) );

		// Get the boxes normalized side directions.
		const XMMATRIX R = XMMatrixRotationQuaternion( Orientation );

		// Adjust ray origin to be relative to center of the box.
		const XMVECTOR TOrigin = XMVectorSubtract(Center, theRay.GetStartPoint().GetRaw());

		// Compute the dot product againt each axis of the box.
		XMVECTOR AxisDotOrigin = XMVector3Dot( R.r[0], TOrigin );
		AxisDotOrigin = XMVectorSelect( AxisDotOrigin, XMVector3Dot( R.r[1], TOrigin ), SelectY );
		AxisDotOrigin = XMVectorSelect( AxisDotOrigin, XMVector3Dot( R.r[2], TOrigin ), SelectZ );

		XMVECTOR AxisDotDirection = XMVector3Dot( R.r[0], theRay.GetDirection() );
		AxisDotDirection = XMVectorSelect( AxisDotDirection, XMVector3Dot( R.r[1], theRay.GetDirection() ), SelectY );
		AxisDotDirection = XMVectorSelect( AxisDotDirection, XMVector3Dot( R.r[2], theRay.GetDirection() ), SelectZ );

		// if (fabs(AxisDotDirection) <= Epsilon) the ray is nearly parallel to the slab.
		const XMVECTOR IsParallel = XMVectorLessOrEqual( XMVectorAbs( AxisDotDirection ), Epsilon );

		// Test against all three axes simultaneously.
		const XMVECTOR InverseAxisDotDirection = XMVectorReciprocal( AxisDotDirection );
		const XMVECTOR t1 = XMVectorMultiply( XMVectorSubtract( AxisDotOrigin , Extents ) , InverseAxisDotDirection);
		const XMVECTOR t2 = XMVectorMultiply(XMVectorAdd(AxisDotOrigin , Extents ) , InverseAxisDotDirection);

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


		const XMVECTOR C = XMVectorSwizzle( NoIntersection, 0, 1, 2, 0 );

		if( !XMComparisonAnyTrue( XMVector4EqualIntR( C, XMVectorTrueInt() ) ) )
		{
			// Store the x-component to *pDist
			XMStoreFloat( pDist, t_min );
			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------------
	XM_INLINE const bool XM_CALLCONV OBB::IntersectTriangle( const Vector4& V0, const Vector4& V1, const Vector4& V2 )
	{
		// Load the box center & orientation.
		const XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center.GetRaw() );
		const XMVECTOR Orientation = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );

		assert( Quat::IsUnit(Orientation) );

		// Transform the triangle vertices into the space of the box.
		const XMVECTOR TV0 = XMVector3InverseRotate( XMVectorSubtract(V0.GetRaw() , Center), Orientation );
		const XMVECTOR TV1 = XMVector3InverseRotate( XMVectorSubtract(V1.GetRaw() , Center), Orientation );
		const XMVECTOR TV2 = XMVector3InverseRotate( XMVectorSubtract(V2.GetRaw() , Center) , Orientation );

		AABB Box;
		Box.SetCenter( Vector4(0.0f, 0.0f, 0.0f,0.0f) );
		Box.SetExtents( this->Extents );

		// Use the triangle vs axis aligned box intersection routine.
		return Box.IntersectTriangle( TV0, TV1, TV2 );
	}

	//-----------------------------------------------------------------------------
	const bool XM_CALLCONV OBB::IntersectSphere( const Sphere* pVolumeA )
	{
		assert( pVolumeA );

		XMVECTOR SphereCenter = XMLoadFloat3( (XMFLOAT3*)&pVolumeA->GetCenter() );
		const float VolArad = pVolumeA->GetRadius();
		const XMVECTOR SphereRadius = XMVectorReplicatePtr( &VolArad );

		const XMVECTOR BoxCenter = XMLoadFloat3( (XMFLOAT3*)&this->Center.GetRaw() );
		const XMVECTOR BoxExtents = XMLoadFloat3( (XMFLOAT3*)&this->Extents.GetRaw() );
		const XMVECTOR BoxOrientation = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );

		assert( Quat::IsUnit(BoxOrientation) );

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
	// Frustum intersection testing routines.
	// Return values: 0 = no intersection,
	//                1 = intersection,
	//                2 = A is completely inside B
	//-----------------------------------------------------------------------------
	XM_INLINE const eCullClassify XM_CALLCONV OBB::IntersectFrustum( Frustum* pVolumeB )
	{
		assert(pVolumeB);

		return pVolumeB->IntersectOBB(*this);
	}

	XM_INLINE const bool XM_CALLCONV OBB::IntersectAABB( AABB& pVolumeB )
	{
		return pVolumeB.IntersectOBB(*this);
	}

	//-----------------------------------------------------------------------------
	// Test an oriented box vs 6 planes (typically forming a frustum).
	// Return values: 0 = no intersection,
	//                1 = may be intersecting,
	//                2 = box is inside all planes
	//-----------------------------------------------------------------------------
	const eCullClassify XM_CALLCONV OBB::Intersect6Planes( const Plane& Plane0, const Plane& Plane1, const Plane& Plane2,const Plane& Plane3, const Plane& Plane4, const Plane& Plane5 )
	{
		// Load the box.
		XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center.GetRaw() );
		const XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&this->Extents.GetRaw() );
		const XMVECTOR BoxOrientation = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );

		assert( Quat::IsUnit(BoxOrientation) );

		// Set w of the center to one so we can dot4 with a plane.
		Center = XMVectorInsert( Center, XMVectorSplatOne(), 0, 0, 0, 0, 1 );

		// Build the 3x3 rotation matrix that defines the box axes.
		const XMMATRIX R = XMMatrixRotationQuaternion( BoxOrientation );

		XMVECTOR Outside, Inside;

		// Test against each plane.
		FastIntersectOrientedBoxPlane( Center, Extents, R.r[0], R.r[1], R.r[2], Plane0.Get(), Outside, Inside );

		XMVECTOR AnyOutside = Outside;
		XMVECTOR AllInside = Inside;

		FastIntersectOrientedBoxPlane( Center, Extents, R.r[0], R.r[1], R.r[2], Plane1.Get(), Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectOrientedBoxPlane( Center, Extents, R.r[0], R.r[1], R.r[2], Plane2.Get(), Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectOrientedBoxPlane( Center, Extents, R.r[0], R.r[1], R.r[2], Plane3.Get(), Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectOrientedBoxPlane( Center, Extents, R.r[0], R.r[1], R.r[2], Plane4.Get(), Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		FastIntersectOrientedBoxPlane( Center, Extents, R.r[0], R.r[1], R.r[2], Plane5.Get(), Outside, Inside );
		AnyOutside = XMVectorOrInt( AnyOutside, Outside );
		AllInside = XMVectorAndInt( AllInside, Inside );

		// If the box is outside any plane it is outside.
		if ( XMVector4EqualInt( AnyOutside, XMVectorTrueInt() ) )
			return CULLED;

		// If the box is inside all planes it is inside.
		if ( XMVector4EqualInt( AllInside, XMVectorTrueInt() ) )
			return VISIBLE;

		// The box is not inside all planes or outside a plane, it may intersect.
		return CLIPPED;
	}

	//-----------------------------------------------------------------------------
	// Volume vs plane intersection testing routines.
	// Return values: 0 = volume is outside the plane (on the positive sideof the plane),
	//                1 = volume intersects the plane,
	//                2 = volume is inside the plane (on the negative side of the plane)
	//-----------------------------------------------------------------------------
	XM_INLINE const eCullClassify XM_CALLCONV OBB::IntersectPlane( const Plane& Plane )
	{
		assert( Plane.IsUnit() );

		// Load the box.
		XMVECTOR Center = XMLoadFloat3( (XMFLOAT3*)&this->Center.GetRaw() );
		const XMVECTOR Extents = XMLoadFloat3( (XMFLOAT3*)&this->Extents.GetRaw() );
		const XMVECTOR BoxOrientation = XMLoadFloat4( (XMFLOAT4*)&this->Orientation.Get() );

		assert( Quat::IsUnit(BoxOrientation) );

		// Set w of the center to one so we can dot4 with a plane.
		Center = XMVectorInsert( Center, XMVectorSplatOne(), 0, 0, 0, 0, 1);

		// Build the 3x3 rotation matrix that defines the box axes.
		const XMMATRIX R = XMMatrixRotationQuaternion( BoxOrientation );

		XMVECTOR Outside, Inside;
		FastIntersectOrientedBoxPlane( Center, Extents, R.r[0], R.r[1], R.r[2], Plane.Get(), Outside, Inside );

		// If the box is outside any plane it is outside.
		if ( XMVector4EqualInt( Outside, XMVectorTrueInt() ) )
			return CULLED;

		// If the box is inside all planes it is inside.
		if ( XMVector4EqualInt( Inside, XMVectorTrueInt() ) )
			return VISIBLE;

		// The box is not inside all planes or outside a plane it intersects.
		return CLIPPED;
	}

	//-------------------------------------------------------------------------------
	// Get the 8 EdgePoints from the OBB
	// We MUST give a Array from 8 TurboMath::Vector4 Members for the EdgePoints
	//-------------------------------------------------------------------------------
	XM_INLINE void XM_CALLCONV OBB::GetEdgePoints( Vector4* pPointlist)
	{
		assert(pPointlist);

		static constexpr XMVECTOR verts[8] =
		{
			{ -1, -1, -1, 0 },
			{ 1, -1, -1, 0 },
			{ 1, -1, 1, 0 },
			{ -1, -1, 1, 0 },
			{ -1, 1, -1, 0 },
			{ 1, 1, -1, 0 },
			{ 1, 1, 1, 0 },
			{ -1, 1, 1, 0 }
		};

		XMMATRIX matWorld = XMMatrixRotationQuaternion( XMLoadFloat4( (XMFLOAT4*)&Orientation.Get() ) );
		const XMMATRIX matScale = XMMatrixScaling( Extents.GetX(), Extents.GetY(), Extents.GetZ() );
		matWorld = XMMatrixMultiply( matScale, matWorld );
		const XMVECTOR position = XMLoadFloat3( (XMFLOAT3*)&Center.GetRaw() );
		matWorld.r[3] = XMVectorSelect( matWorld.r[3], position, XMVectorSelectControl( 1, 1, 1, 0 ) );

		XMFLOAT3* pVerts = (XMFLOAT3*)pPointlist;

		for( int i=0; i < 8; ++i )
		{
			const XMVECTOR v = XMVector3Transform( verts[i], matWorld );
			XMStoreFloat3( &pVerts[i], v );
		}
	}
}// end of Namespace TurboMath
