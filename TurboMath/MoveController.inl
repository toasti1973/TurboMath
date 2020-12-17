
// -------------------------------------------------------------------
// File			:	MoveController.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for a MoveController-Class
//					We have a Base-Class, and 2 Samples Classes
//					- a fully free
//					- a Ego-Perpective
//
// Author		:	Thorsten Polte
// -------------------------------------------------------------------
// (c) 2013-2020 by Innovation3D-Studio´s
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


#pragma once
#pragma warning(disable:4244)


namespace TurboMath
{
	__forceinline const Vector4	MovementController::GetPos() const
	{
		return m_vcPos;
	}

	__forceinline const Vector4	MovementController::GetRight() const	
	{
		return m_vcRight;
	}

	__forceinline const Vector4	MovementController::GetUp() const	
	{
		return m_vcUp;
	}

	__forceinline const Vector4	MovementController::GetDir() const
	{
		return m_vcDir;
	}

	__forceinline const Vector4	MovementController::GetVelocity() const
	{
		return m_vcV;
	}

	__forceinline const Vector4	MovementController::GetMoveVector() const		
	{
		return m_MoveVector;
	}
	
	__forceinline const Quat	MovementController::GetRotation() const
	{
		return m_Quat;
	}

	
	__forceinline MovementController::MovementController()				// Konstruktor
	{
		Init();
	}

	__forceinline MovementController::~MovementController()	
	{
	};		


	__forceinline void MovementController::Init()
	{
		m_vcPos.Set(0.0f,0.0f,0.0f);
		m_vcRight.Set(1.0f,0.0f,0.0f);
		m_vcUp.Set(0.0f,1.0f,0.0f);
		m_vcDir.Set(0.0f,0.0f,1.0f);
		m_vcV.Set(0.0f,0.0f,0.0f);
		m_fRotX = m_fRotY = m_fRotZ = m_fThrust = 0.0f;
		m_fRollSpd = m_fPitchSpd = m_fYawSpd = 0.0f;
		m_Quat.Set(0.0f, 0.0f, 0.0f, 1.0f);

		// Max-Werte begrenzen
		m_fRollSpdMax = m_fPitchSpdMax = m_fYawSpdMax = 10.0f;
	}

	__forceinline void MovementController::RecalcAxes(void)
	{
		Quat	qFrame;
		Matrix	mat;

		// Rotation im Bereich von 360 Grad halten
		if(m_fRotX > TURBOMATH_PI) m_fRotX -= TURBOMATH_PI;
		else if (m_fRotX < -TURBOMATH_PI) m_fRotX += TURBOMATH_PI;

		if(m_fRotY > TURBOMATH_PI) m_fRotY -= TURBOMATH_PI;
		else if (m_fRotY < -TURBOMATH_PI) m_fRotY += TURBOMATH_PI;

		if(m_fRotZ > TURBOMATH_PI) m_fRotZ -= TURBOMATH_PI;
		else if (m_fRotZ < -TURBOMATH_PI) m_fRotZ += TURBOMATH_PI;

		// neues Quaternion für die Rotation ....

		qFrame.MakeFromEuler(m_fRotX,m_fRotY,m_fRotZ);


		// zur bisherigen Rot. addieren
		m_Quat *= qFrame;

		// lokale Achsen aus dem Quaternion holen
		mat = Quat::GetMatrix(m_Quat);

		m_vcRight.SetX(mat.GetM11());
		m_vcRight.SetY(mat.GetM21());
		m_vcRight.SetZ(mat.GetM31());

		m_vcUp.SetX(mat.GetM12());
		m_vcUp.SetY(mat.GetM22());
		m_vcUp.SetZ(mat.GetM32());

		m_vcDir.SetX(mat.GetM13());
		m_vcDir.SetY(mat.GetM23());
		m_vcDir.SetZ(mat.GetM33());

	}

	// -------------------------------------------------------------------------------------

	__forceinline MovementControllerFree::MovementControllerFree()
	{
		MovementController::Init();
	}

	__forceinline MovementControllerFree::~MovementControllerFree()			
	{
	}

	__forceinline void MovementControllerFree::SetRotationSpeedX(const float f)
	{
		m_fPitchSpd = f;
	}

	__forceinline void MovementControllerFree::SetRotationSpeedY(const float f)		
	{
		m_fYawSpd = f;
	}

	__forceinline void MovementControllerFree::SetRotationSpeedZ(const float f)			
	{
		m_fRollSpd = f;
	}

	__forceinline void MovementControllerFree::AddThrust(const float f)	
	{
		m_fThrust += f;
	}

	__forceinline void MovementControllerFree::SetThrust(const float f)		
	{
		m_fThrust  = f;
	}

	__forceinline void MovementControllerFree::SetPos(const Vector4& vc)	
	{
		m_vcPos = vc;
	}

	__forceinline void MovementControllerFree::SetRight(const Vector4& vc)
	{
		m_vcRight = vc;
	}

	__forceinline void MovementControllerFree::SetUp(const Vector4& vc)		
	{
		m_vcUp = vc;
	}

	__forceinline void MovementControllerFree::SetDir(const Vector4& vc)		
	{
		m_vcDir = vc;
	}

	__forceinline void MovementControllerFree::SetRotation(const float x, const float y, const float z)
	{
		m_fRotX = x;
		m_fRotY = y;
		m_fRotZ = z;

		RecalcAxes();
	}

	__forceinline void MovementControllerFree::AddRotationSpeed(const float sx, const float sy, const float sz)
	{
		m_fPitchSpd += sx;
		m_fYawSpd   += sy;
		m_fRollSpd  *= sz;
	}

	__forceinline void MovementControllerFree::SetRotationSpeed(const float sx, const float sy, const float sz)
	{
		m_fPitchSpd = sx;
		m_fYawSpd   = sy;
		m_fRollSpd  = sz;
	}

	__forceinline void MovementControllerFree::Update(const float fET)
	{
		// Rotationsgeschwindigkeit addieren

		m_fRotX = (m_fPitchSpd * fET);
		m_fRotY = (m_fYawSpd   * fET);
		m_fRotZ = (m_fRollSpd  * fET);

		// Geschwindidkeitsvector berechnen

		m_vcV = m_vcDir * m_fThrust * fET;

		m_MoveVector = m_vcV;

		// Position verschieben
		m_vcPos += m_vcV;										// neue berechnen

		// Achsen neu berechnen
		RecalcAxes();
	}


	// -------------------------------------------------------------------------------------

	__forceinline MovementControllerEgo::MovementControllerEgo()		
	: MovementController()
	{
		MovementController::Init();
		m_fSpeed = 0;
		m_fSlide = 0;
	}

	__forceinline MovementControllerEgo::~MovementControllerEgo()
	{
	}

	__forceinline void MovementControllerEgo::SetRotationSpeedX(const float f)
	{
		m_fPitchSpd = f;
	}

	__forceinline void MovementControllerEgo::SetRotationSpeedY(const float f)	
	{
		m_fYawSpd = f;
	}

	__forceinline void MovementControllerEgo::SetSpeed(const float f)		
	{
		m_fSpeed = f;
	}

	__forceinline void MovementControllerEgo::SetSlideSpeed(const float f)
	{
		m_fSlide = f;
	}

	__forceinline void MovementControllerEgo::SetPos(const Vector4& vc)
	{
		m_vcPos = vc;
	}

	__forceinline void MovementControllerEgo::SetRight(const Vector4& vc)		
	{
		m_vcRight = vc;
	}

	__forceinline void MovementControllerEgo::SetUp(const Vector4& vc)	
	{
		m_vcUp = vc;
	}

	__forceinline void MovementControllerEgo::SetDir(const Vector4& vc)	
	{
		m_vcDir = vc;
	}

	__forceinline void MovementControllerEgo::SetRotation(const float rx, const float ry, const float rz)
	{
		m_fRotX = rx;
		m_fRotY = ry;
		m_fRotZ = rz;
		RecalcAxes();
	}

	__forceinline void MovementControllerEgo::GetRotation(float* x, float* y, float* z)
	{
		if(x) *x = m_fRotX;
		if(y) *y = m_fRotY;
		if(z) *z = m_fRotZ;
	}

	__forceinline const Vector4 MovementControllerEgo::GetRotation()
	{
		return Vector4(m_fRotX,m_fRotY,m_fRotZ);
	}

	__forceinline void MovementControllerEgo::RecalcAxes()
	{
		Matrix mat;

		// Bewegung einschränken

		// Drehen
		if (m_fRotY > TURBOMATH_TWO_PI) m_fRotY -= TURBOMATH_TWO_PI;
		else if (m_fRotY < -TURBOMATH_TWO_PI) m_fRotY += TURBOMATH_TWO_PI;

		// Blick nach Oben/Unten
		if (m_fRotX > 1.4f) m_fRotX = 1.4f;
		else if (m_fRotX < -1.4f) m_fRotX = -1.4f;

		// Achsen Initialisieren
		m_vcRight.Set(1.0f,0.0f,0.0f);
		m_vcUp.Set(0.0f,1.0f,0.0f);
		m_vcDir.Set(0.0f,0.0f,1.0f);

		// Rotiere um Y-Achse
		mat		  = Matrix::RotationAxis(m_vcUp,m_fRotY);
		m_vcRight = m_vcRight * mat;
		m_vcDir   = m_vcDir * mat;

		//Rotiere um Z-Achse
		mat		  = Matrix::RotationAxis(m_vcRight,m_fRotX);
		m_vcUp	  = m_vcUp * mat;
		m_vcDir	  = m_vcDir * mat;

		// Rundungsfehler korrigieren
		m_vcDir   = Vector4::Normalize(m_vcDir);
		m_vcRight = Vector4::Cross(m_vcUp,m_vcDir);
		m_vcRight = Vector4::Normalize(m_vcRight);
		m_vcUp    = Vector4::Cross(m_vcDir,m_vcRight);
		m_vcUp	  = Vector4::Normalize(m_vcUp);
	}

	__forceinline void MovementControllerEgo::Update(const float fTime)
	{
		Vector4 vcS;

		// Rotationsgeschwindigkeit addieren
		m_fRotX += (m_fPitchSpd * fTime);
		m_fRotY += (m_fYawSpd * fTime);
		m_fRotZ += (m_fRollSpd * fTime);

		// Achsen neu berechnen

		RecalcAxes();

		// Geschwindgikeits-Vector berechnen

		m_vcV = m_vcDir * m_fSpeed * fTime;
		vcS	  = m_vcRight * m_fSlide * fTime;

		m_MoveVector = m_vcV + vcS;								// Bewegungsvector ausrechnen

		// Position bewegen
		m_vcPos += m_MoveVector;								// neue berechnen

	}



}// end of Namespace TurboMath