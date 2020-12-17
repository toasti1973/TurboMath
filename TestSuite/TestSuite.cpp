
// -------------------------------------------------------------------
// File			:	TestSuite
//
// Description	:	Test for TurboMath in Cpp
//
// Author		:	Thorsten Polte
// -------------------------------------------------------------------
// (c) 2011 by Innovation3D-Studio´s
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

bool Point2Test();
bool Point3Test();
bool Point4Test();


bool Vector2Test();
bool Vector3Test();
bool Vector4Test();

int main()
{
	// First Test - Point2
	Point2Test();

	// Next Test - Point3
	Point3Test();

	// Next Test - Point4
	Point4Test();

	const Matrix mat1 = mat1.Identity();

	Matrix mat2 = mat1;
	const Matrix mat3(mat1);

	// Ready
	return 0;
}

