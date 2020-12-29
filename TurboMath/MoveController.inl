
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
	XM_INLINE const Vector4	XM_CALLCONV MovementController::GetPos() const noexcept
	{
		return m_vcPos;
	}

	XM_INLINE const Vector4 XM_CALLCONV MovementController::GetRight() const noexcept	
	{
		return m_vcRight;
	}

	XM_INLINE const Vector4	XM_CALLCONV MovementController::GetUp() const noexcept	
	{
		return m_vcUp;
	}

	XM_INLINE const Vector4	XM_CALLCONV MovementController::GetDir() const noexcept
	{
		return m_vcDir;
	}

	XM_INLINE const Vector4	XM_CALLCONV MovementController::GetVelocity() const noexcept
	{
		return m_vcV;
	}

	XM_INLINE const Vector4	XM_CALLCONV MovementController::GetMoveVector() const noexcept		
	{
		return m_MoveVector;
	}
	
	XM_INLINE const Quat	XM_CALLCONV MovementController::GetRotation() const noexcept
	{
		return m_Quat;
	}

	
	XM_INLINE MovementController::MovementController()	 noexcept			// Konstruktor
	{
		Init();
	}

	XM_INLINE MovementController::~MovementController()	
	{
	};		


	XM_INLINE void XM_CALLCONV MovementController::Init() noexcept
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

	XM_INLINE void XM_CALLCONV MovementController::RecalcAxes(void) noexcept
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

	XM_INLINE MovementControllerFree::MovementControllerFree() noexcept
	{
		MovementController::Init();
	}

	XM_INLINE MovementControllerFree::~MovementControllerFree()	 noexcept		
	{
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::SetRotationSpeedX(const float f) noexcept
	{
		m_fPitchSpd = f;
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::SetRotationSpeedY(const float f) noexcept		
	{
		m_fYawSpd = f;
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::SetRotationSpeedZ(const float f) noexcept			
	{
		m_fRollSpd = f;
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::AddThrust(const float f)	 noexcept
	{
		m_fThrust += f;
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::SetThrust(const float f)	 noexcept	
	{
		m_fThrust  = f;
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::SetPos(const Vector4& vc) noexcept	
	{
		m_vcPos = vc;
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::SetRight(const Vector4& vc) noexcept
	{
		m_vcRight = vc;
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::SetUp(const Vector4& vc) noexcept		
	{
		m_vcUp = vc;
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::SetDir(const Vector4& vc) noexcept		
	{
		m_vcDir = vc;
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::SetRotation(const float x, const float y, const float z) noexcept
	{
		m_fRotX = x;
		m_fRotY = y;
		m_fRotZ = z;

		RecalcAxes();
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::AddRotationSpeed(const float sx, const float sy, const float sz) noexcept
	{
		m_fPitchSpd += sx;
		m_fYawSpd   += sy;
		m_fRollSpd  *= sz;
	}

	XM_INLINE void XM_CALLCONV  MovementControllerFree::SetRotationSpeed(const float sx, const float sy, const float sz) noexcept
	{
		m_fPitchSpd = sx;
		m_fYawSpd   = sy;
		m_fRollSpd  = sz;
	}

	XM_INLINE void XM_CALLCONV MovementControllerFree::Update(const float fET) noexcept
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

	XM_INLINE MovementControllerEgo::MovementControllerEgo()	 noexcept	
	: MovementController()
	{
		MovementController::Init();
		m_fSpeed = 0;
		m_fSlide = 0;
	}

	XM_INLINE MovementControllerEgo::~MovementControllerEgo() noexcept
	{
	}

	XM_INLINE void XM_CALLCONV MovementControllerEgo::SetRotationSpeedX(const float f) noexcept
	{
		m_fPitchSpd = f;
	}

	XM_INLINE void XM_CALLCONV MovementControllerEgo::SetRotationSpeedY(const float f) noexcept	
	{
		m_fYawSpd = f;
	}

	XM_INLINE void XM_CALLCONV MovementControllerEgo::SetSpeed(const float f) noexcept		
	{
		m_fSpeed = f;
	}

	XM_INLINE void XM_CALLCONV MovementControllerEgo::SetSlideSpeed(const float f) noexcept
	{
		m_fSlide = f;
	}

	XM_INLINE void XM_CALLCONV MovementControllerEgo::SetPos(const Vector4& vc) noexcept
	{
		m_vcPos = vc;
	}

	XM_INLINE void XM_CALLCONV MovementControllerEgo::SetRight(const Vector4& vc)	 noexcept	
	{
		m_vcRight = vc;
	}

	XM_INLINE void XM_CALLCONV MovementControllerEgo::SetUp(const Vector4& vc) noexcept	
	{
		m_vcUp = vc;
	}

	XM_INLINE void XM_CALLCONV MovementControllerEgo::SetDir(const Vector4& vc) noexcept	
	{
		m_vcDir = vc;
	}

	XM_INLINE void XM_CALLCONV MovementControllerEgo::SetRotation(const float rx, const float ry, const float rz) noexcept
	{
		m_fRotX = rx;
		m_fRotY = ry;
		m_fRotZ = rz;
		RecalcAxes();
	}

	XM_INLINE void XM_CALLCONV MovementControllerEgo::GetRotation(float* x, float* y, float* z) noexcept
	{
		if(x) *x = m_fRotX;
		if(y) *y = m_fRotY;
		if(z) *z = m_fRotZ;
	}

	XM_INLINE const Vector4 XM_CALLCONV MovementControllerEgo::GetRotation() noexcept
	{
		return Vector4(m_fRotX,m_fRotY,m_fRotZ);
	}

	XM_INLINE void XM_CALLCONV MovementControllerEgo::RecalcAxes() noexcept
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

	XM_INLINE void XM_CALLCONV MovementControllerEgo::Update(const float fTime) noexcept
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