
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
					Line();
		
					/// component constructor
		explicit	Line(const Vector4& startPoint, const Vector4& endPoint);
		
		/// component constructor
		explicit	Line(const Vector4& startPoint, const Vector4& dir, const float lenght);
		
		/// copy constructor
					Line(const Line& rhs);
		
					
		/// set start and end point
		void Set(const Vector4& startPoint, const Vector4& endPoint);
		
		/// get start point
		const Vector4& GetStartPoint() const;
		
		/// get end point
		Vector4 GetEndPoint() const;
		
		/// get vector
		const Vector4& DirectionVector() const;
		
		/// get length
		const float Length() const;
		
		/// get squared length
		const float Lengthsq() const;
		
		/// minimal distance of point to Line
		const float Distance(const Vector4& p) const;
		
		/// intersect with Line
		const bool Intersect(const Line& l, Vector4& pa, Vector4& pb) const;
		
		/// return t of the closest point on the Line
		const float ClosestPoint(const Vector4& p) const;
		
		/// return p = b + m*t
		Vector4 PointAt(float t) const;
		
		/// Return the point on the line segement  nearest the point P.
		Vector4 PointOnLineSegmentNearestPoint(const Vector4& P );
		
		/// Intersect Plane / Line
		const bool IntersectPlane( const Plane& plane) const;


	protected:
		Vector4 b;					// begin
		Vector4 m;					// dir
	};

}; // end of namespace

#endif