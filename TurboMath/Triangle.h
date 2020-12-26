
// -------------------------------------------------------------------
// File			:	Triangle
//
// Project		:	TurboMath
//
// Description	:	Class for a Triangle
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
//---------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _TURBOBOOSTER_MATH_TRIANGLE_H_
#define _TURBOBOOSTER_MATH_TRIANGLE_H_

namespace TurboMath
{

	CACHE_ALIGN(16) class Triangle
	{
	public:
		//-----------------------------------------------------------------------------
		// Constructor / Destructor
		//-----------------------------------------------------------------------------
		Triangle()
		{
		}

		explicit Triangle( const Vector4& vec1, const Vector4& vec2, const Vector4& vec3)
		{
			v[0] = vec1;
			v[1] = vec2;
			v[2] = vec3;
		}

		~Triangle() {}

		// Functions
		void				Set(const Vector4& vec1, const Vector4& vec2, const Vector4& vec3);
		void				SetVector1(const Vector4& vec);
		void				SetVector2(const Vector4& vec);
		void				SetVector3(const Vector4& vec);

		const Vector4		GetVector1() const;
		const Vector4		GetVector2() const;
		const Vector4		GetVector3() const;
		const Vector4		GetNormalVector() const;
		const AABB			GetAABB() const;
		void				GetAABB(AABB& box) const;
		const Plane			GetPlane() const;
		void				GetPlane(Plane& p) const;
		void				SetUserData(const UINT& UData);
		const UINT			GetUserData() const;

		// Triangle-Matrix product
		const Triangle operator * (const Matrix& m) const;
		/// muliply by a Matrix component-wise
		void operator*=(const Matrix& m);

	protected:

		Vector4		v[3];
	};
}; // end of namespace


#endif