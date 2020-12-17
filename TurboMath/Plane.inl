
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
	__forceinline Plane::Plane()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline Plane::Plane(float a, float b, float c, float d)
	{
		this->vec = XMVectorSet(a, b, c, d);
	}

	//------------------------------------------------------------------------------
	__forceinline Plane::Plane(const Vector4& p0, const Vector4& p1, const Vector4& p2)
	{
		this->vec = XMPlaneFromPoints(p0, p1, p2);
	}

	//------------------------------------------------------------------------------
	__forceinline Plane::Plane(const Vector4& p0, const Vector4& n)
	{
		assert( n != Vector4::NullVec() );
		this->vec = XMPlaneFromPointNormal(p0, n);
	}

	//------------------------------------------------------------------------------
	__forceinline Plane::Plane(XMVECTOR rhs) :
	vec(rhs)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	__forceinline void Plane::Set(const Vector4& point, const Vector4& normal)
	{
		this->vec = XMPlaneFromPointNormal(point, normal);
	}

	//------------------------------------------------------------------------------
	__forceinline void Plane::Set(float a, float b, float c, float d)
	{
		this->vec = XMVectorSet(a, b, c, d);
	}

	//------------------------------------------------------------------------------
	__forceinline void Plane::Set(const Vector4& Data)
	{
		this->vec = Data;
	}

	//------------------------------------------------------------------------------
	__forceinline void Plane::Set(const XMVECTOR& Data)
	{
		this->vec = Data;
	}

	//------------------------------------------------------------------------------
	__forceinline void Plane::Set(const Vector4& p0, const Vector4& p1, const Vector4& p2)
	{
		this->vec = XMPlaneFromPoints(p0, p1, p2);
	}

	//------------------------------------------------------------------------------
	__forceinline  float& Plane::a()
	{
	#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.x;
	#elif __WIN32__
		return this->vec.m128_f32[0];
	#endif
	}

	//------------------------------------------------------------------------------
	__forceinline float Plane::a() const
	{
		return Vector4::Unpack_X(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline float& Plane::b()
	{
	#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.y;
	#elif __WIN32__
		return this->vec.m128_f32[1];
	#endif
	}

	//------------------------------------------------------------------------------
	__forceinline float Plane::b() const
	{
		return Vector4::Unpack_Y(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline float& Plane::c()
	{
	#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.z;
	#elif __WIN32__
		return this->vec.m128_f32[2];
	#endif
	}

	//------------------------------------------------------------------------------
	__forceinline float Plane::c() const
	{
		return Vector4::Unpack_Z(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline float& Plane::d()
	{
	#if __XBOX360__ || defined(_XM_NO_INTRINSICS_)
		return this->vec.w;
	#elif __WIN32__
		return this->vec.m128_f32[3];
	#endif
	}

	//------------------------------------------------------------------------------
	__forceinline float Plane::d() const
	{
		return Vector4::Unpack_W(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline const float Plane::GetA() const
	{
		return Vector4::Unpack_X(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline const float Plane::GetB() const
	{
		return Vector4::Unpack_Y(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline const float Plane::GetC() const
	{
		return Vector4::Unpack_Z(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline const float Plane::GetD() const
	{
		return Vector4::Unpack_W(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline float Plane::Dot(const Vector4& v) const
	{
		return Vector4::Unpack_X(XMPlaneDot(this->vec, v));
	}

	//------------------------------------------------------------------------------
	__forceinline bool Plane::Intersectline(const Vector4& startPoint, const Vector4& endPoint, Vector4& outIntersectPoint)
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
	__forceinline Plane Plane::Normalize(const Plane& p)
	{
		return Plane(XMPlaneNormalize(p.vec));
	}

	__forceinline void Plane::Normalize()
	{
		XMPlaneNormalize(this->vec);
	}

	//------------------------------------------------------------------------------
	__forceinline void  Plane::SetA(float a)
	{
		this->vec = XMVectorSetXPtr(this->vec, &a);
	}

	//------------------------------------------------------------------------------
	__forceinline void Plane::SetB(float b)
	{
		this->vec = XMVectorSetYPtr(this->vec, &b);
	}

	//------------------------------------------------------------------------------
	__forceinline void  Plane::SetC(float c)
	{
		this->vec = XMVectorSetZPtr(this->vec, &c);
	}

	//------------------------------------------------------------------------------
	__forceinline void Plane::SetD(float d)
	{
		this->vec = XMVectorSetWPtr(this->vec, &d);
	}

	//------------------------------------------------------------------------------
	__forceinline void Plane::Inverse()
	{
		this->vec *= -1.0f;
	}

	//------------------------------------------------------------------------------
	__forceinline Vector4 Plane::Get() const
	{
		return this->vec;
	}

	//------------------------------------------------------------------------------
	__forceinline Vector4 Plane::GetNormal() const
	{
		Vector4 Normal = this->vec;
		Normal.SetW(0);

		return Normal;
	}

	//------------------------------------------------------------------------------
	__forceinline const float Plane::DistanceToPoint(const Vector4& pt) const
	{
		return (this->a() * pt.GetX() + this->b() * pt.GetY() + this->c() * pt.GetZ() + this->d());
	}

	//------------------------------------------------------------------------------
	__forceinline const Vector4 Plane::Reflect(const Vector4& vec) const
	{
		const float d = DistanceToPoint(vec) * 2.0f;

		return Vector4(vec + (Vector4( -GetA(), -GetB(), -GetC() )*d) );
	}

	//------------------------------------------------------------------------------
	__forceinline const Vector4 Plane::Project(const Vector4& p) const
	{
		const float h = DistanceToPoint(p);

		return Vector4(   p.GetX() - a() * h, p.GetY() - b() * h, p.GetZ() - c() * h);
	}

	//------------------------------------------------------------------------------
	__forceinline  const bool Plane::operator == (const Plane& p) const
	{
		return (0 != XMVector4Equal(this->vec, p.vec));
	}

	//------------------------------------------------------------------------------
	__forceinline  const bool Plane::operator != (const Plane& p) const
	{
		return (0 != XMVector4NotEqual(this->vec, p.vec));
	}

	//------------------------------------------------------------------------------
	__forceinline   Plane Plane::XZ_PLANE()
	{
		return Plane(Vector4::ZERO(), Vector4::UNIT_Y());
	}

	//------------------------------------------------------------------------------
	__forceinline   Plane Plane::XY_PLANE()
	{
		return Plane(Vector4::ZERO(), Vector4::UNIT_Z());
	}

	//------------------------------------------------------------------------------
	__forceinline   Plane Plane::YZ_PLANE()
	{
		return Plane(Vector4::ZERO(), Vector4::UNIT_X());
	}
	
	//------------------------------------------------------------------------------
	__forceinline void  Plane::Transform(const Matrix& m)
	{
		this->vec = XMPlaneTransform(this->vec,m.mx);
	}

	//------------------------------------------------------------------------------
	__forceinline void	Plane::Transform(const Quat& Rotation,const Vector4& Translation )
	{
		const XMVECTOR Normal = XMVector3Rotate( this->vec, Rotation.Get() );
		const XMVECTOR D = XMVectorSubtract( XMVectorSplatW( this->vec ) , XMVector3Dot( Normal, Translation.GetRaw() ) );

		this->vec = XMVectorInsert( Normal, D, 0, 0, 0, 0, 1 );
	}

	//------------------------------------------------------------------------------
	// Classify point to plane.
	__forceinline const eCullClassify Plane::Classify(const Vector4& vcPoint)
	{
		const float f = this->Dot(vcPoint);

		if (f >  TURBOMATH_EPSILON) return FRONT;
		if (f < -TURBOMATH_EPSILON) return BACK;
		return PLANAR;
	}

	//------------------------------------------------------------------------------
/*	__forceinline const eCullClassify Plane::Classify(const Polygon& Pol)
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
	const bool Plane::Clip(const Line& iLine, float fL, Line* pFrontLine, Line* pBackLine)
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
	const bool Plane::IsUnit() const 
	{
		static const XMVECTOR g_UnitPlaneEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		XMVECTOR Difference = XMVector3Length( vec ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), g_UnitPlaneEpsilon );
	}

	//------------------------------------------------------------------------------
	__forceinline bool Plane::IsUnit(const XMVECTOR p) 
	{
		static const XMVECTOR g_UnitPlaneEpsilon =
		{
			1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f
		};

		XMVECTOR Difference = XMVector3Length( p ) - XMVectorSplatOne();
		return XMVector4Less( XMVectorAbs( Difference ), g_UnitPlaneEpsilon );
	}

}// end of Namespace TurboMath