
// -------------------------------------------------------------------
// File			:	Plane.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for Plane-Class
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

/****************************************************************************
 *
 * Point2
 *
 ****************************************************************************/

namespace TurboMath
{

	//------------------------------------------------------------------------------
	 XM_INLINE Plane::Plane() noexcept
	{
		// empty
	}

	//------------------------------------------------------------------------------
	 XM_INLINE Plane::Plane(float a, float b, float c, float d) noexcept
	{
		this->vec = XMVectorSet(a, b, c, d);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE Plane::Plane(const Vector4& p0, const Vector4& p1, const Vector4& p2) noexcept
	{
		this->vec = XMPlaneFromPoints(p0, p1, p2);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE Plane::Plane(const Vector4& p0, const Vector4& n)
	{
		assert( n != Vector4::NullVec() );
		this->vec = XMPlaneFromPointNormal(p0, n);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE Plane::Plane(XMVECTOR rhs) noexcept :
	vec(rhs)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	 XM_INLINE void XM_CALLCONV Plane::Set(const Vector4& point, const Vector4& normal) noexcept
	{
		this->vec = XMPlaneFromPointNormal(point, normal);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE void XM_CALLCONV  Plane::Set(const float a, const float b, const float c, const float d) noexcept
	{
		this->vec = XMVectorSet(a, b, c, d);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE void XM_CALLCONV  Plane::Set(const Vector4& Data) noexcept
	{
		this->vec = Data;
	}

	//------------------------------------------------------------------------------
	 XM_INLINE void XM_CALLCONV  Plane::Set(const XMVECTOR& Data) noexcept
	{
		this->vec = Data;
	}

	//------------------------------------------------------------------------------
	 XM_INLINE void XM_CALLCONV  Plane::Set(const Vector4& p0, const Vector4& p1, const Vector4& p2) noexcept
	{
		this->vec = XMPlaneFromPoints(p0, p1, p2);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE float& XM_CALLCONV  Plane::a() noexcept
	{
		return this->vec.m128_f32[0];
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const float XM_CALLCONV  Plane::a() const noexcept
	{
		return Vector4::Unpack_X(this->vec);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE float& XM_CALLCONV  Plane::b() noexcept
	{
		return this->vec.m128_f32[1];
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const float XM_CALLCONV  Plane::b() const noexcept
	{
		return Vector4::Unpack_Y(this->vec);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE float& XM_CALLCONV  Plane::c() noexcept
	{
		return this->vec.m128_f32[2];
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const float XM_CALLCONV  Plane::c() const noexcept
	{
		return Vector4::Unpack_Z(this->vec);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE float& XM_CALLCONV  Plane::d() noexcept
	{
		return this->vec.m128_f32[3];
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const float XM_CALLCONV  Plane::d() const noexcept
	{
		return Vector4::Unpack_W(this->vec);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const float XM_CALLCONV  Plane::GetA() const noexcept
	{
		return Vector4::Unpack_X(this->vec);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const float XM_CALLCONV  Plane::GetB() const noexcept
	{
		return Vector4::Unpack_Y(this->vec);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const float XM_CALLCONV  Plane::GetC() const noexcept
	{
		return Vector4::Unpack_Z(this->vec);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const float XM_CALLCONV  Plane::GetD() const noexcept
	{
		return Vector4::Unpack_W(this->vec);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const float XM_CALLCONV  Plane::Dot(const Vector4& v) const noexcept
	{
		return Vector4::Unpack_X(XMPlaneDot(this->vec, v));
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const bool XM_CALLCONV  Plane::Intersectline(const Vector4& startPoint, const Vector4& endPoint, Vector4& outIntersectPoint) noexcept
	{
		outIntersectPoint = XMPlaneIntersectLine(this->vec, startPoint, endPoint);
		if (XMPlaneIsNaN(outIntersectPoint))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	//------------------------------------------------------------------------------
	 XM_INLINE Plane XM_CALLCONV  Plane::Normalize(const Plane& p) noexcept
	{
		return Plane(XMPlaneNormalize(p.vec));
	}

	 XM_INLINE void XM_CALLCONV  Plane::Normalize() noexcept
	{
		XMPlaneNormalize(this->vec);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE void XM_CALLCONV   Plane::SetA(const float a) noexcept
	{
		this->vec = XMVectorSetXPtr(this->vec, &a);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE void XM_CALLCONV  Plane::SetB(const float b) noexcept
	{
		this->vec = XMVectorSetYPtr(this->vec, &b);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE void  XM_CALLCONV  Plane::SetC(const float c) noexcept
	{
		this->vec = XMVectorSetZPtr(this->vec, &c);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE void XM_CALLCONV  Plane::SetD(const float d) noexcept
	{
		this->vec = XMVectorSetWPtr(this->vec, &d);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE void XM_CALLCONV  Plane::Inverse() noexcept
	{
		this->vec *= -1.0f;
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const Vector4 XM_CALLCONV  Plane::Get() const noexcept
	{
		return this->vec;
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const Vector4 XM_CALLCONV  Plane::GetNormal() const noexcept
	{
		Vector4 Normal = this->vec;
		Normal.SetW(0);

		return Normal;
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const float  XM_CALLCONV Plane::DistanceToPoint(const Vector4& pt) const noexcept
	{
		return (this->a() * pt.GetX() + this->b() * pt.GetY() + this->c() * pt.GetZ() + this->d());
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const Vector4 XM_CALLCONV  Plane::Reflect(const Vector4& vec) const noexcept
	{
		const float d = DistanceToPoint(vec) * 2.0f;

		return Vector4(vec + (Vector4( -GetA(), -GetB(), -GetC() )*d) );
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const Vector4  XM_CALLCONV Plane::Project(const Vector4& p) const noexcept
	{
		const float h = DistanceToPoint(p);

		return Vector4(   p.GetX() - a() * h, p.GetY() - b() * h, p.GetZ() - c() * h);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const bool  XM_CALLCONV Plane::operator == (const Plane& p) const noexcept
	{
		return (0 != XMVector4Equal(this->vec, p.vec));
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const bool  XM_CALLCONV Plane::operator != (const Plane& p) const noexcept
	{
		return (0 != XMVector4NotEqual(this->vec, p.vec));
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const Plane  XM_CALLCONV Plane::XZ_PLANE() noexcept
	{
		return Plane(Vector4::ZERO(), Vector4::UNIT_Y());
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const Plane XM_CALLCONV  Plane::XY_PLANE() noexcept
	{
		return Plane(Vector4::ZERO(), Vector4::UNIT_Z());
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const Plane  XM_CALLCONV Plane::YZ_PLANE() noexcept
	{
		return Plane(Vector4::ZERO(), Vector4::UNIT_X());
	}
	
	//------------------------------------------------------------------------------
	 XM_INLINE void   XM_CALLCONV Plane::Transform(const Matrix& m) noexcept
	{
		this->vec = XMPlaneTransform(this->vec,m.mx);
	}

	//------------------------------------------------------------------------------
	 XM_INLINE void	 XM_CALLCONV Plane::Transform(const Quat& Rotation,const Vector4& Translation ) noexcept
	{
		const XMVECTOR Normal = XMVector3Rotate( this->vec, Rotation.Get() );
		const XMVECTOR D = XMVectorSubtract( XMVectorSplatW( this->vec ) , XMVector3Dot( Normal, Translation.GetRaw() ) );

		this->vec = XMVectorInsert( Normal, D, 0, 0, 0, 0, 1 );
	}

	//------------------------------------------------------------------------------
	// Classify point to plane.
	 XM_INLINE const eCullClassify  XM_CALLCONV Plane::Classify(const Vector4& vcPoint) noexcept
	{
		const float f = this->Dot(vcPoint);

		if (f >  TURBOMATH_EPSILON) return FRONT;
		if (f < -TURBOMATH_EPSILON) return BACK;
		return PLANAR;
	}

	//------------------------------------------------------------------------------
/*	 XM_INLINE const eCullClassify  XM_CALLCONV Plane::Classify(const Polygon& Pol) noexcept
	{
		int NumFront=0, NumBack=0, NumPlanar=0;

		// cast away const
		Polygon* pPoly = ((Polygon*)&Pol);

		int NumPoints = pPoly->GetNumPoints();

		// loop through all points
		for (int i=0; i < NumPoints; i++)
		{
			const eCullClassify nClass = Classify( pPoly->m_pPoints[i] );

			if (nClass == FRONT)     NumFront++;
			else if (nClass == BACK) NumBack++;
			else
			{
				NumFront++;
				NumBack++;
				NumPlanar++;
			}
		} // for

		// all points are planar
		if (NumPlanar == NumPoints)
			return PLANAR;
		// all points are in front of plane
		else if (NumFront == NumPoints)
			return FRONT;
		// all points are on backside of plane
		else if (NumBack == NumPoints)
			return BACK;
		// poly is intersecting the plane
		else
			return CLIPPED;
	}
*/
	//------------------------------------------------------------------------------
	// clips a ray into two segments if it Collision the plane
	const bool  XM_CALLCONV Plane::Clip(const Line& iLine, float fL, Line* pFrontLine, Line* pBackLine) noexcept
	{
		Vector4 vcHit(0.0f,0.0f,0.0f);

		// ray Collision plane at all?
		if ( !this->Intersectline(iLine.GetStartPoint(),iLine.GetEndPoint(),vcHit) )
			return false;

		const eCullClassify n = Classify( iLine.GetStartPoint() );

		// ray comes fron planes backside
		if ( n == BACK )
		{
			if (pBackLine) pBackLine->Set(iLine.GetStartPoint(), iLine.DirectionVector());
			if (pFrontLine) pFrontLine->Set(vcHit, iLine.DirectionVector());
		}
		// ray comes from planes front side
		else if ( n == FRONT )
		{
			if (pFrontLine) pFrontLine->Set(iLine.GetStartPoint(), iLine.DirectionVector());
			if (pBackLine) pBackLine->Set(vcHit, iLine.DirectionVector());
		}

		return true;
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const bool  XM_CALLCONV Plane::IsUnit() const  noexcept
	{
		static const XMVECTOR g_UnitPlaneEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		XMVECTOR Difference = XMVector3Length( vec ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), g_UnitPlaneEpsilon );
	}

	//------------------------------------------------------------------------------
	 XM_INLINE const bool  XM_CALLCONV Plane::IsUnit(const XMVECTOR p)  noexcept
	{
		static const XMVECTOR g_UnitPlaneEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		XMVECTOR Difference = XMVector3Length( p ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), g_UnitPlaneEpsilon );
	}

}// end of Namespace TurboMath