
// -------------------------------------------------------------------
// File			:	Triangle.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for a Triangle-Class
//
// Author		:	Thorsten Polte
// -------------------------------------------------------------------
// (c) 2013-2020 by Innovation3D-Studio´s
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
	
	// Functions
	XM_INLINE void  XM_CALLCONV Triangle::Set(const Vector4& vec1, const Vector4& vec2, const Vector4& vec3) noexcept
	{
		static_assert(sizeof(Triangle) == 48, "Class TurboMath::Triangle wrong size");

		v[0] = vec1;
		v[1] = vec2;
		v[2] = vec3;
	}

	XM_INLINE void  XM_CALLCONV Triangle::SetVector1(const Vector4& vec) noexcept
	{
		v[0] = vec;
	}

	XM_INLINE void  XM_CALLCONV Triangle::SetVector2(const Vector4& vec) noexcept
	{
		v[1] = vec;
	}

	XM_INLINE void   XM_CALLCONV Triangle::SetVector3(const Vector4& vec) noexcept
	{
		v[2] = vec;
	}

	XM_INLINE const Vector4  XM_CALLCONV Triangle::GetVector1() const noexcept
	{
		return v[0];
	}

	XM_INLINE const Vector4  XM_CALLCONV Triangle::GetVector2() const noexcept
	{
		return v[1];
	}

	XM_INLINE const Vector4  XM_CALLCONV Triangle::GetVector3() const noexcept
	{
		return v[2];
	}

	XM_INLINE const Vector4  XM_CALLCONV Triangle::GetNormalVector() const noexcept
	{
		Plane p(v[0],v[1],v[2]);

		return p.GetNormal();
	}

	XM_INLINE const AABB  XM_CALLCONV Triangle::GetAABB() const noexcept
	{
		Vector4 vcMin;
		Vector4 vcMax;

		// Boundingbox
		for( UINT j = 0; j < 3; j++)
		{
				if (v[j].GetX() > vcMax.GetX())	vcMax.SetX( v[j].GetX() );
				else if (v[j].GetX() < vcMin.GetX()) vcMin.SetX( v[j].GetX() );

				if (v[j].GetY() > vcMax.GetY())	vcMax.SetY( v[j].GetY() );
				else if (v[j].GetY() < vcMin.GetY()) vcMin.SetY( v[j].GetY() );

				if (v[j].GetZ() > vcMax.GetZ())	vcMax.SetZ( v[j].GetZ() );
				else if (v[j].GetZ() < vcMin.GetZ()) vcMin.SetZ( v[j].GetZ() );
		}

		AABB box;
		box.Set(vcMin,vcMax);

		return box;
	}

	XM_INLINE void  XM_CALLCONV Triangle::GetAABB(AABB& box) const noexcept
	{
		Vector4 vcMin;
		Vector4 vcMax;

		// Boundingbox
		for( UINT j = 0; j < 3; j++)
		{
				if (v[j].GetX() > vcMax.GetX())	vcMax.SetX( v[j].GetX() );
				else if (v[j].GetX() < vcMin.GetX()) vcMin.SetX( v[j].GetX() );

				if (v[j].GetY() > vcMax.GetY())	vcMax.SetY( v[j].GetY() );
				else if (v[j].GetY() < vcMin.GetY()) vcMin.SetY( v[j].GetY() );

				if (v[j].GetZ() > vcMax.GetZ())	vcMax.SetZ( v[j].GetZ() );
				else if (v[j].GetZ() < vcMin.GetZ()) vcMin.SetZ( v[j].GetZ() );
		}

		box.Set(vcMin,vcMax);
	}

	XM_INLINE  const Plane  XM_CALLCONV Triangle::GetPlane() const noexcept
	{
		Plane p(v[0],v[1],v[2]);

		return p;
	}

	XM_INLINE void  XM_CALLCONV Triangle::GetPlane(Plane& p) const noexcept
	{
		p.Set(v[0],v[1],v[2]);
	}

	XM_INLINE void  XM_CALLCONV Triangle::operator*=(const Matrix& m) noexcept
	{
		this->v[0] *= this->v[0] * m;
		this->v[1] *= this->v[1] * m;
		this->v[2] *= this->v[2] * m;
	}

	XM_INLINE const Triangle  XM_CALLCONV Triangle::operator * (const Matrix& m) const noexcept
	{
		Triangle tri;

		tri.SetVector1(v[0] * m);
		tri.SetVector2(v[1] * m);
		tri.SetVector3(v[2] * m);

		return tri;
	}

	XM_INLINE void  XM_CALLCONV Triangle::SetUserData(const UINT& UData) noexcept
	{
		const float tmp = (float) UData;

		v[0].SetZ(tmp);
	}

	XM_INLINE const UINT  XM_CALLCONV Triangle::GetUserData() const noexcept
	{
		const float tmp = v[0].GetZ();

		return (UINT)tmp;
	}


	
}// end of Namespace TurboMath