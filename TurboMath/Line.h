
// -------------------------------------------------------------------
// File			:	Line
//
// Project		:	TurboMath
//
// Description	:	Class for Line´s
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


#ifndef _TURBOMATH_LINE_H_
#define _TURBOMATH_LINE_H_

namespace TurboMath
{


	CACHE_ALIGN(16) class Line
	{
	public:
		
		/// default constructor
				Line() noexcept;
		
					/// component constructor
		explicit	Line(const Vector4& startPoint, const Vector4& endPoint) noexcept;
		
		/// component constructor
		explicit	Line(const Vector4& startPoint, const Vector4& dir, const float lenght) noexcept;
		
		/// copy constructor
				Line(const Line& rhs) noexcept;
		
					
		/// set start and end point
		void  XM_CALLCONV Set(const Vector4& startPoint, const Vector4& endPoint) noexcept;
		
		/// get start point
		const Vector4&  XM_CALLCONV GetStartPoint() const noexcept;
		
		/// get end point
		const Vector4  XM_CALLCONV GetEndPoint() const noexcept;
		
		/// get vector
		const Vector4&  XM_CALLCONV DirectionVector() const noexcept;
		
		/// get length
		const float  XM_CALLCONV Length() const noexcept;
		
		/// get squared length
		const float  XM_CALLCONV Lengthsq() const noexcept;
		
		/// minimal distance of point to Line
		const float  XM_CALLCONV Distance(const Vector4& p) const noexcept;
		
		/// intersect with Line
		const bool  XM_CALLCONV Intersect(const Line& l, Vector4& pa, Vector4& pb) const noexcept;
		
		/// return t of the closest point on the Line
		const float  XM_CALLCONV ClosestPoint(const Vector4& p) const noexcept;
		
		/// return p = b + m*t
		const Vector4  XM_CALLCONV PointAt(const float t) const noexcept;
		
		/// Return the point on the line segement  nearest the point P.
		const Vector4  XM_CALLCONV PointOnLineSegmentNearestPoint(const Vector4& P ) noexcept;
		
		/// Intersect Plane / Line
		const bool  XM_CALLCONV IntersectPlane( const Plane& plane) const noexcept;


	protected:
		Vector4 b;					// begin
		Vector4 m;					// dir
	};

}; // end of namespace

#endif