// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


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

#include "stdafx.h"
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

bool MatrixTest();

int _tmain(int argc, _TCHAR* argv[])
{
	// First Test - Point2
	Point2Test();

	// Next Test - Point3
	Point3Test();

	// Next Test - Point4
	Point4Test();

	// First Test - Vector2
	Vector2Test();

	// Next Test - Vector3
	Vector3Test();

	// Next Test - Vector4
	Vector4Test();

	// Next Test - Matrix
	MatrixTest();

	// Ready
	return 0;
}

