
// -------------------------------------------------------------------
// File			:	Point4Test - TestSuite
//
// Description	:	Test for Point4 from TurboMath
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

#include "..\TurboMath\TurboMath.h"
#include <assert.h>
#include <windows.h>

using namespace TurboMath;

bool Point4Test()
{
	Point4 p1,p2,p5;

	p1.SetZero();
	p2.SetZero();
	p5.SetZero();

	// Test add
	p5 = Point4(1.0f,1.0f,1.0f,1.0f);

	p1 = p5;

	assert(p1 == p5);
	assert(! (p1 != p5) );

	p1 += p5;
	assert(p1 == Point4(2.0f,2.0f,2.0f,2.0f));

	p1 *= p1;
	assert(p1 == Point4(4.0f,4.0f,4.0f,4.0f));

	p1 -= p5;
	assert(p1 == Point4(3.0f,3.0f,3.0f,3.0f));

	p1 *= 3.0f;
	assert(p1 == Point4(9.0f,9.0f,9.0f,9.0f));

	p5.Set(5.0f,10.0f,20.0f,40.0f);

	p5 /= 2.0f;

	// Ready and return
	return true;

}