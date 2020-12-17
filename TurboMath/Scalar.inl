
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

	__forceinline const float ACos( float value) noexcept
	{
		return XMScalarACos(value);
	}

	__forceinline const float ACosEst(const float value)
	{
		return XMScalarACosEst(value);
	}

	__forceinline const float ASin(const float value)
	{
		return XMScalarASin(value);
	}

	__forceinline const float ASinEst(const float value)
	{
		return XMScalarASinEst(value);
	}

	__forceinline const float ATan(const float value)
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorATanEst(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	__forceinline const float ATanEst(const float value)
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorATanEst(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	__forceinline const float ATan2(const float y, const float x)
	{
		auto vector1 = XMLoadFloat(&y);
		auto vector2 = XMLoadFloat(&x);

		vector1 = XMVectorATan2(vector1, vector2);

		float ret;
		XMStoreFloat(&ret, vector1);

		return ret;
	}

	__forceinline const float ATan2Est(const float y, const float x)
	{
		auto vector1 = XMLoadFloat(&y);
		auto vector2 = XMLoadFloat(&x);

		vector1 = XMVectorATan2Est(vector1, vector2);

		float ret;
		XMStoreFloat(&ret, vector1);

		return ret;
	}

	__forceinline const float Cos(const float value)
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorCos(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	__forceinline const float CosEst(const float value)
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorCosEst(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	__forceinline const float Sin(const float value)
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorSin(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	__forceinline const float SinEst(const float value)
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorSinEst(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	__forceinline const float Tan(const float value)
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorTan(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	__forceinline const float TanEst(const float value)
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorTanEst(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;

	}

	__forceinline const float CosH(const float value)
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorCosH(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	__forceinline const float SinH(const float value)
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorSinH(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	__forceinline const float TanH(const float value)
	{
		auto vector = XMLoadFloat(&value);

		vector = XMVectorTanH(vector);

		float ret;
		XMStoreFloat(&ret, vector);

		return ret;
	}

	__forceinline void SinCos(const float value, float* sin, float* cos)
	{
		auto vector1 = XMLoadFloat(sin);
		auto vector2 = XMLoadFloat(cos);
		auto vector3 = XMLoadFloat(&value);

		XMVectorSinCos(&vector1, &vector2, vector3);

		XMStoreFloat(sin, vector1);
		XMStoreFloat(cos, vector2);
	}


	__forceinline void SinCosEst(const float value, float* sin, float* cos)
	{
		auto vector1 = XMLoadFloat(sin);
		auto vector2 = XMLoadFloat(cos);
		auto vector3 = XMLoadFloat(&value);

		XMVectorSinCos(&vector1, &vector2, vector3);

		XMStoreFloat(sin, vector1);
		XMStoreFloat(cos, vector2);
	}

	__forceinline const float ToDegrees(const float radians)
	{
		return XMConvertToDegrees(radians);
	}

	__forceinline const float ToRadians(const float degrees)
	{
		return XMConvertToRadians(degrees);
	}

	__forceinline const float WrapAngle(const float angle)
	{
		return XMScalarModAngle(angle);
	}


}// Namespace
