
// -------------------------------------------------------------------
// File			:	Scalar.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for Scalar
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
 * Scalar
 *
 ****************************************************************************/

namespace TurboMath
{

	 XM_INLINE const float ACos( const float value) noexcept
	{
		return XMScalarACos(value);
	}

	 XM_INLINE const float ACosEst(const float value) noexcept
	{
		return XMScalarACosEst(value);
	}

	 XM_INLINE const float ASin(const float value) noexcept
	{
		return XMScalarASin(value);
	}

	 XM_INLINE const float ASinEst(const float value) noexcept
	{
		return XMScalarASinEst(value);
	}

	 XM_INLINE const float ATan(const float value) noexcept
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorATanEst(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	 XM_INLINE const float ATanEst(const float value) noexcept
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorATanEst(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	 XM_INLINE const float ATan2(const float y, const float x) noexcept
	{
		auto vector1 = XMLoadFloat(&y);
		auto vector2 = XMLoadFloat(&x);

		vector1 = XMVectorATan2(vector1, vector2);

		float ret;
		XMStoreFloat(&ret, vector1);

		return ret;
	}

	 XM_INLINE const float ATan2Est(const float y, const float x) noexcept
	{
		auto vector1 = XMLoadFloat(&y);
		auto vector2 = XMLoadFloat(&x);

		vector1 = XMVectorATan2Est(vector1, vector2);

		float ret;
		XMStoreFloat(&ret, vector1);

		return ret;
	}

	 XM_INLINE const float Cos(const float value) noexcept
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorCos(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	 XM_INLINE const float CosEst(const float value) noexcept
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorCosEst(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	 XM_INLINE const float Sin(const float value) noexcept
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorSin(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	 XM_INLINE const float SinEst(const float value) noexcept
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorSinEst(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	 XM_INLINE const float Tan(const float value) noexcept
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorTan(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	 XM_INLINE const float TanEst(const float value) noexcept
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorTanEst(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;

	}

	 XM_INLINE const float CosH(const float value) noexcept
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorCosH(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	 XM_INLINE const float SinH(const float value) noexcept
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorSinH(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	 XM_INLINE const float TanH(const float value) noexcept
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorTanH(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	 XM_INLINE void SinCos(const float value, float* sin, float* cos) noexcept
	{
		auto vector1 = XMLoadFloat(sin);
		auto vector2 = XMLoadFloat(cos);
		auto vector3 = XMLoadFloat(&value);

		XMVectorSinCos(&vector1, &vector2, vector3);

		XMStoreFloat(sin, vector1);
		XMStoreFloat(cos, vector2);
	}


	 XM_INLINE void SinCosEst(const float value, float* sin, float* cos) noexcept
	{
		auto vector1 = XMLoadFloat(sin);
		auto vector2 = XMLoadFloat(cos);
		auto vector3 = XMLoadFloat(&value);

		XMVectorSinCos(&vector1, &vector2, vector3);

		XMStoreFloat(sin, vector1);
		XMStoreFloat(cos, vector2);
	}

	 XM_INLINE const float ToDegrees(const float radians) noexcept
	{
		return XMConvertToDegrees(radians);
	}

	 XM_INLINE const float ToRadians(const float degrees) noexcept
	{
		return XMConvertToRadians(degrees);
	}

	 XM_INLINE const float WrapAngle(const float angle) noexcept
	{
		return XMScalarModAngle(angle);
	}


}// Namespace
