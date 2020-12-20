
// -------------------------------------------------------------------
// File			:	Point2Test - TestSuite
//
// Description	:	Test for Point2 from TurboMath
//
// Author		:	Thorsten Polte
// -------------------------------------------------------------------
// (c) 2012 by Innovation3D-Studio´s
// --------------------------------------------------------------------
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//---------------------------------------------------------------------

#include "stdafx.h"
#include "..\TurboMath\TurboMath.h"
#include <assert.h>
#include <windows.h>

using namespace TurboMath;

bool Point2Test()
{
	Point2 p1,p2,p3,p4,p5;
//	XMFLOAT2 r1,r2;

	p1.SetZero();
	p2.SetZero();
	p3.SetZero();
	p4.SetZero();
	p5.SetZero();

	// Test add
	p5 = Point2(1.0f,1.0f);

	p1 = p5;

	assert(p1 == p5);
	assert(! (p1 != p5) );

	p1 += p5;
	assert(p1 == Point2(2.0f,2.0f));

	p1 *= p1;
	assert(p1 == Point2(4.0f,4.0f));

	p1 -= p5;
	assert(p1 == Point2(3.0f,3.0f));

	p1 *= 3.0f;
	assert(p1 == Point2(9.0f,9.0f));

	p1.Set(5.0f,10.0f);

	p1 /= 2.0f;

	// Ready and return
	return true;

}