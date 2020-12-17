
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
	void __forceinline Triangle::Set(const Vector4& vec1, const Vector4& vec2, const Vector4& vec3)
	{
		static_assert(sizeof(Triangle) == 48, "Class TurboMath::Triangle wrong size");

		v[0] = vec1;
		v[1] = vec2;
		v[2] = vec3;
	}

	void __forceinline Triangle::SetVector1(const Vector4& vec)
	{
		v[0] = vec;
	}

	void __forceinline Triangle::SetVector2(const Vector4& vec)
	{
		v[1] = vec;
	}

	void  __forceinline Triangle::SetVector3(const Vector4& vec)
	{
		v[2] = vec;
	}

	const Vector4 __forceinline Triangle::GetVector1() const
	{
		return v[0];
	}

	const Vector4 __forceinline Triangle::GetVector2() const
	{
		return v[1];
	}

	const Vector4 __forceinline Triangle::GetVector3() const
	{
		return v[2];
	}

	const Vector4 __forceinline Triangle::GetNormalVector() const
	{
		Plane p(v[0],v[1],v[2]);

		return p.GetNormal();
	}

	const AABB __forceinline Triangle::GetAABB() const
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

	void __forceinline Triangle::GetAABB(AABB& box) const
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

	const Plane __forceinline Triangle::GetPlane() const
	{
		Plane p(v[0],v[1],v[2]);

		return p;
	}

	void __forceinline Triangle::GetPlane(Plane& p) const
	{
		p.Set(v[0],v[1],v[2]);
	}

	void __forceinline Triangle::operator*=(const Matrix& m)
	{
		this->v[0] *= this->v[0] * m;
		this->v[1] *= this->v[1] * m;
		this->v[2] *= this->v[2] * m;
	}

	const Triangle __forceinline Triangle::operator * (const Matrix& m) const
	{
		Triangle tri;

		tri.SetVector1(v[0] * m);
		tri.SetVector2(v[1] * m);
		tri.SetVector3(v[2] * m);

		return tri;
	}

	void __forceinline Triangle::SetUserData(const UINT& UData)
	{
		const float tmp = (float) UData;

		v[0].SetZ(tmp);
	}

	const UINT __forceinline Triangle::GetUserData() const
	{
		const float tmp = v[0].GetZ();

		return (UINT)tmp;
	}


	
}// end of Namespace TurboMath