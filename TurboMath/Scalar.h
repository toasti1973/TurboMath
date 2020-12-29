
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
	const float ACos(const float value) noexcept;
	const float ACosEst(const float value) noexcept;
	const float ASin(const float value) noexcept;
	const float ASinEst(const float value) noexcept;
	const float ATan(const float value) noexcept;
	const float ATanEst(const float value) noexcept;
	const float ATan2(const float y, const float x) noexcept;
	const float ATan2Est(const float y, const float x) noexcept;

	const float Cos(const float value) noexcept;
	const float CosEst(const float value) noexcept;
	const float Sin(const float value) noexcept;
	const float SinEst(const float value) noexcept;
	const float Tan(const float value) noexcept;
	const float TanEst(const float value) noexcept;

	const float CosH(const float value) noexcept;
	const float SinH(const float value) noexcept;
	const float TanH(const float value) noexcept;

	void SinCos(const float value, float* sin, float* cos) noexcept;

	void SinCosEst(const float value, float* sin, float* cos) noexcept;

	const float ToDegrees(const float radians) noexcept;
	const float ToRadians(const float degrees) noexcept;
	const float WrapAngle(const float angle) noexcept;

}; // namespace TurboMath



#endif