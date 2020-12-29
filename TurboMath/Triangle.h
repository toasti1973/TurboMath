
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

	class Triangle
	{
	public:
		//-----------------------------------------------------------------------------
		// Constructor / Destructor
		//-----------------------------------------------------------------------------
		Triangle()
		{
		}

		explicit Triangle( const Vector4& vec1, const Vector4& vec2, const Vector4& vec3) noexcept
		{
			v[0] = vec1;
			v[1] = vec2;
			v[2] = vec3;
		}

		~Triangle() {}

		// Functions
		void	 XM_CALLCONV 			Set(const Vector4& vec1, const Vector4& vec2, const Vector4& vec3) noexcept;
		void	 XM_CALLCONV 			SetVector1(const Vector4& vec) noexcept;
		void	 XM_CALLCONV 			SetVector2(const Vector4& vec) noexcept;
		void	 XM_CALLCONV 			SetVector3(const Vector4& vec) noexcept;

		const Vector4	 XM_CALLCONV 		GetVector1() const noexcept;
		const Vector4	 XM_CALLCONV 		GetVector2() const noexcept;
		const Vector4	 XM_CALLCONV 		GetVector3() const noexcept;
		const Vector4	 XM_CALLCONV 		GetNormalVector() const noexcept;
		const AABB	 XM_CALLCONV 		GetAABB() const noexcept;
		void		 XM_CALLCONV 		GetAABB(AABB& box) const noexcept;
		const Plane	 XM_CALLCONV 		GetPlane() const noexcept;
		void		 XM_CALLCONV 		GetPlane(Plane& p) const noexcept;
		void		 XM_CALLCONV 		SetUserData(const UINT& UData) noexcept;
		const UINT	 XM_CALLCONV 		GetUserData() const noexcept;

		// Triangle-Matrix product
		const Triangle  XM_CALLCONV operator * (const Matrix& m) const noexcept;
		/// muliply by a Matrix component-wise
		void  XM_CALLCONV operator*=(const Matrix& m) noexcept;

	protected:

		Vector4		v[3];
	};
}; // end of namespace


#endif