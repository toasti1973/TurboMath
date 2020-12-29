
// -------------------------------------------------------------------
// File			:	Point4
//
// Project		:	TurboMath
//
// Description	:	Class for 4D-Point
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
	XM_INLINE   Line::Line() noexcept
	{
		// empty
	}

	//------------------------------------------------------------------------------
	XM_INLINE   Line::Line(const Vector4& startPoint, const Vector4& endPoint)  noexcept:
	b(startPoint),
	m(endPoint - startPoint)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	XM_INLINE   Line::Line(const Vector4& startPoint, const Vector4& dir, const float length) noexcept
	{
		b = startPoint;
		m = dir * length;
	}

	//------------------------------------------------------------------------------
	XM_INLINE   Line::Line(const Line& rhs) noexcept :
	b(rhs.b),
	m(rhs.m)
	{
		// empty
	}

	//------------------------------------------------------------------------------
	XM_INLINE   void  XM_CALLCONV Line::Set(const Vector4& startPoint, const Vector4& endPoint) noexcept
	{
		this->b = startPoint;
		this->m = endPoint - startPoint;
	}

	//------------------------------------------------------------------------------
	XM_INLINE   const Vector4&  XM_CALLCONV Line::GetStartPoint() const noexcept
	{
		return this->b;
	}

	//------------------------------------------------------------------------------
	XM_INLINE   const Vector4  XM_CALLCONV Line::GetEndPoint() const noexcept
	{
		return this->b + this->m;
	}

	//------------------------------------------------------------------------------
	XM_INLINE   const Vector4&  XM_CALLCONV Line::DirectionVector() const noexcept
	{
		return this->m;
	}

	//------------------------------------------------------------------------------
	XM_INLINE   const float  XM_CALLCONV Line::Length() const noexcept
	{
		return this->m.Length();
	}

	//------------------------------------------------------------------------------
	XM_INLINE   const float  XM_CALLCONV Line::Lengthsq() const noexcept
	{
		return this->m.Lengthsq();
	}

	//------------------------------------------------------------------------------
	//	Returns a point on the Line which is closest to a another point in space.
	//	This just returns the parameter t on where the point is located. If t is
	//	between 0 and 1, the point is on the Line, otherwise not. To get the
	//	actual 3d point p:
	//
	//	p = m + b*t
	//-------------------------------------------------------------------------------
	XM_INLINE   const float  XM_CALLCONV Line::ClosestPoint(const Vector4& p) const noexcept
	{
		Vector4 diff(p - this->b);

		const float l = Vector4::Dot(this->m, this->m);
		if (l > 0.0f)
		{
			const float t = Vector4::Dot(this->m, diff) / l;
			return t;
		}
		else
		{
			return 0.0f;
		}
	}

	//------------------------------------------------------------------------------
	XM_INLINE   const float  XM_CALLCONV Line::Distance(const Vector4& p) const noexcept
	{
		Vector4 diff(p - this->b);

		const float l = Vector4::Dot(this->m, this->m);
		if (l > 0.0f)
		{
			const float t = Vector4::Dot(this->m, diff) / l;
			diff = diff - this->m * t;
			return diff.Length();
		}
		else
		{
			// Line is really a point...
			const Vector4 v(p - this->b);
			return v.Length();
		}
	}

	//------------------------------------------------------------------------------
	//	Returns p = b + m * t, given t. Note that the point is not on the Line
	//	if 0.0 > t > 1.0
	//------------------------------------------------------------------------------
	XM_INLINE   const Vector4  XM_CALLCONV Line::PointAt(const float t) const noexcept
	{
		return this->b + this->m * t;
	}

	//------------------------------------------------------------------------------
	//	Get line/line intersection. Returns the shortest line between two lines.
	//------------------------------------------------------------------------------
	XM_INLINE   const bool  XM_CALLCONV Line::Intersect(const Line& l, Vector4& pa, Vector4& pb) const noexcept
	{
		const float EPS = 2.22e-16f;
		const Vector4 p1 = this->b;
		const Vector4 p2 = this->PointAt(10.0f);
		const Vector4 p3 = l.b;
		const Vector4 p4 = l.PointAt(10.0f);

		const Vector4 p13 = p1 - p3;
		const Vector4 p43 = p4 - p3;
		const Vector4 p21 = p2 - p1;
		if (p43.Lengthsq() < EPS) return false;
		if (p21.Lengthsq() < EPS) return false;

		const float d1343 = Vector4::Dot(p13, p43);
		const float d4321 = Vector4::Dot(p43, p21);
		const float d1321 = Vector4::Dot(p13, p21);
		const float d4343 = Vector4::Dot(p43, p43);
		const float d2121 = Vector4::Dot(p21, p21);

		const float denom = d2121 * d4343 - d4321 * d4321;
		if (Abs(denom) < EPS) return false;
		const float numer = d1343 * d4321 - d1321 * d4343;

		const float mua = numer / denom;
		const float mub = (d1343 + d4321 * (mua)) / d4343;

		pa = p1 + p21 * mua;
		pb = p3 + p43 * mub;

		return true;
	}

	//-----------------------------------------------------------------------------
	// Return the point on the line segement (S1, S2) nearest the point P.
	//-----------------------------------------------------------------------------
	XM_INLINE   const Vector4  XM_CALLCONV Line::PointOnLineSegmentNearestPoint(const Vector4& P ) noexcept
	{
		const Vector4 Dir = this->b - this->m;
		float t1 = ( Vector4::Dot( P, Dir ) - Vector4::Dot( this->b, Dir ) );
		const Vector4 Projection(t1);
		t1 = Vector4::Dot( Dir, Dir );
		const Vector4 LengthSq(t1);

		Vector4 t = Projection * Vector4::Reciprocal( LengthSq );
		Vector4 Point = this->b + t * Dir;

		// t < 0
		const Vector4 SelectS1 = Vector4::Less( Projection, Vector4::NullVec() );
		Point = Vector4::Select( Point, b, SelectS1 );

		// t > 1
		const XMVECTOR SelectS2 = XMVectorGreater( Projection, LengthSq );
		Point = XMVectorSelect( Point, this->m, SelectS2 );

		return Point;
	}

	//-----------------------------------------------------------------------------
	/// Intersect Plane / Line
	//-----------------------------------------------------------------------------
	XM_INLINE   const bool  XM_CALLCONV Line::IntersectPlane( const Plane& plane) const noexcept
	{
		const float d1 = plane.Dot(b);
		const float d2 = plane.Dot(m);

		if (d1 <= 0.0f) if (d2 >= 0.0f) return true;
		if (d1 >= 0.0f) if (d2 <= 0.0f) return true;

		return false;
	}

}; // namespace TurboMath

