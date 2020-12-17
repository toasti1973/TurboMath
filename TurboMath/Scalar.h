
// -------------------------------------------------------------------
// File			:	Scalar
//
// Project		:	TurboMath
//
// Description	:	Scalar
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

#ifndef _TURBOMATH_SCALAR_H_
#define _TURBOMATH_SCALAR_H_

namespace TurboMath
{
	const float ACos(float value) noexcept;
	const float ACosEst(const float value);
	const float ASin(const float value);
	const float ASinEst(const float value);
	const float ATan(const float value);
	const float ATanEst(const float value);
	const float ATan2(const float y, const float x);
	const float ATan2Est(const float y, const float x);

	const float Cos(const float value);
	const float CosEst(const float value);
	const float Sin(const float value);
	const float SinEst(const float value);
	const float Tan(const float value);
	const float TanEst(const float value);

	const float CosH(const float value);
	const float SinH(const float value);
	const float TanH(const float value);

	void SinCos(const float value, float* sin, float* cos);

	void SinCosEst(const float value, float* sin, float* cos);

	const float ToDegrees(const float radians);
	const float ToRadians(const float degrees);
	const float WrapAngle(const float angle);

}; // namespace TurboMath



#endif