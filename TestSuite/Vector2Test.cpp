
// -------------------------------------------------------------------
// File			:	Vector2Test - TestSuite
//
// Description	:	Test for Vector2 from TurboMath
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

bool Vector2Test()
{
	Vector2 p1,p2,p3,p4,p5;

	p1.NullVec();
	p2.NullVec();
	p3.NullVec();
	p4.NullVec();
	p5.NullVec();

	// Test add
	p5 = Vector2(1.0f,1.0f);

	p1 = p5;

	assert(p1 == p5);
	assert(! (p1 != p5) );

	p1 += p5;
	assert(p1 == Vector2(2.0f,2.0f));

	p1 *= p1;
	assert(p1 == Vector2(4.0f,4.0f));

	p1 -= p5;
	assert(p1 == Vector2(3.0f,3.0f));

	p1 *= 3.0f;
	assert(p1 == Vector2(9.0f,9.0f));

	p1.Set(5.0f,10.0f);

//	p1 /= 2.0f;

	// Ready and return
	return true;

}