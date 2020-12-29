
// -------------------------------------------------------------------
// File			:	MoveController
//
// Project		:	TurboMath
//
// Description	:	Class for MoveController
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

#ifndef _TURBOMATH_MOVECONTROLLER_H_
#define _TURBOMATH_MOVECONTROLLER_H_


namespace TurboMath
{

	class MovementController
	{
	public:

		MovementController() noexcept;
		virtual ~MovementController() noexcept;

		virtual void XM_CALLCONV Update( const float fTime )=0;					// Virtual !!!!!
		
		// Zugriffs-Methoden für die MemberVariablen

		const Vector4	XM_CALLCONV 	GetPos() const noexcept;
		const Vector4	XM_CALLCONV 	GetRight() const noexcept;
		const Vector4	XM_CALLCONV 	GetUp() const noexcept;
		const Vector4	XM_CALLCONV 	GetDir() const noexcept;
		const Vector4	XM_CALLCONV 	GetVelocity() const noexcept;
		const Vector4	XM_CALLCONV 	GetMoveVector() const noexcept;
		const Quat		XM_CALLCONV 	GetRotation() const noexcept;
		
	protected:

		// Methoden
		virtual void XM_CALLCONV RecalcAxes() noexcept;
		virtual void XM_CALLCONV Init() noexcept;

		Vector4		m_vcPos;					// Position
		Vector4		m_vcRight;					// RechtsVector
		Vector4		m_vcUp;						// Hoch-Vector
		Vector4		m_vcDir;					// RichtungsVector
		Vector4		m_vcV;						// Geschwindigkeits-Vector
		Quat		m_Quat;						// Quaternion für Rotation

		Vector4		m_MoveVector;					// Bewegungsvector (schon mit Zeit verrechnet !)

		// Rotation-Speed on every Axis
		float		m_fRollSpd;
		float		m_fPitchSpd;
		float		m_fYawSpd;

		float		m_fRollSpdMax;
		float		m_fPitchSpdMax;
		float		m_fYawSpdMax;

		// Rotation on local Axis
		float		m_fRotX;
		float		m_fRotY;
		float		m_fRotZ;

		float		m_fThrust;
	};


	
	class MovementControllerFree : public MovementController
	{
	public:

		MovementControllerFree() noexcept;
		virtual ~MovementControllerFree() noexcept;

		virtual void XM_CALLCONV Update(const float fTime) noexcept;

		// Die Methoden für die Bewegung

		void XM_CALLCONV AddRotationSpeed(const float sx, const float sy, const float sz) noexcept;
		void XM_CALLCONV SetRotationSpeed(const float sx, const float sy, const float sz) noexcept;
		void XM_CALLCONV SetRotationSpeedX(const float f) noexcept;
		void XM_CALLCONV SetRotationSpeedY(const float f) noexcept;
		void XM_CALLCONV SetRotationSpeedZ(const float f) noexcept;
		void XM_CALLCONV AddThrust(const float f) noexcept;
		void XM_CALLCONV SetThrust(const float f) noexcept;

		// Die Attribute direkt einstellen ... nur für INIT !!!
		void XM_CALLCONV SetRotation(const float rx, const float ry, const float rz) noexcept;

		void XM_CALLCONV SetPos(const Vector4& vc) noexcept;
		void XM_CALLCONV SetRight(const Vector4& vc) noexcept;
		void XM_CALLCONV SetUp(const Vector4& vc) noexcept;
		void XM_CALLCONV SetDir(const Vector4& vc) noexcept;

	};



	
	class MovementControllerEgo : public MovementController
	{
	public:

		MovementControllerEgo() noexcept;					// Konstruktor
		virtual ~MovementControllerEgo() noexcept;			// Destruktor

		virtual void XM_CALLCONV Update(const float fTime) noexcept;

		// Die Methoden für die Bewegung

		void		XM_CALLCONV GetRotation(float* x, float* y, float *z) noexcept;
		const Vector4 	XM_CALLCONV GetRotation() noexcept;
		void		XM_CALLCONV SetRotationSpeedX(const float f) noexcept;
		void		XM_CALLCONV SetRotationSpeedY(const float f) noexcept;
		void		XM_CALLCONV SetSpeed(const float f) noexcept;
		void		XM_CALLCONV SetSlideSpeed(const float f) noexcept;



		// Die Attribute direkt einstellen ... nur für INIT !!!

		void XM_CALLCONV SetRotation(const float rx, const float ry, const float rz) noexcept;
		void XM_CALLCONV SetPos(const Vector4& vc) noexcept;
		void XM_CALLCONV SetRight(const Vector4& vc) noexcept;
		void XM_CALLCONV SetUp(const Vector4& vc) noexcept;
		void XM_CALLCONV SetDir(const Vector4& vc) noexcept;

	private:

		float m_fSpeed;
		float m_fSlide;
		void XM_CALLCONV RecalcAxes(void) noexcept;
	};

}; // end of namespace
#endif