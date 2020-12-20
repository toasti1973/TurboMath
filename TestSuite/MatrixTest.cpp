
// -------------------------------------------------------------------
// File			:	MatrxTest - TestSuite
//
// Description	:	Test for Matrix from TurboMath
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

bool MatrixTest()
{
	const Matrix mat1 = mat1.Identity();

	Matrix mat2 = mat1;
	const Matrix mat3(mat1);

	// Ready and return
	return true;

}