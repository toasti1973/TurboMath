
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

		MovementController();
		virtual ~MovementController();

		virtual void Update( const float fTime )=0;					// Virtual !!!!!
		
		// Zugriffs-Methoden für die MemberVariablen

		const Vector4		GetPos() const;
		const Vector4		GetRight() const;
		const Vector4		GetUp() const;
		const Vector4		GetDir() const;
		const Vector4		GetVelocity() const;
		const Vector4		GetMoveVector() const;
		const Quat			GetRotation() const;
		
	protected:

		// Methoden
		virtual void RecalcAxes();
		virtual void Init();

		Vector4		m_vcPos;					// Position
		Vector4		m_vcRight;					// RechtsVector
		Vector4		m_vcUp;						// Hoch-Vector
		Vector4		m_vcDir;					// RichtungsVector
		Vector4		m_vcV;						// Geschwindigkeits-Vector
		Quat		m_Quat;						// Quaternion für Rotation

		Vector4		m_MoveVector;				// Bewegungsvector (schon mit Zeit verrechnet !)

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

		MovementControllerFree();
		virtual ~MovementControllerFree();

		virtual void Update(const float fTime);

		// Die Methoden für die Bewegung

		void AddRotationSpeed(const float sx, const float sy, const float sz);
		void SetRotationSpeed(const float sx, const float sy, const float sz);
		void SetRotationSpeedX(const float f);
		void SetRotationSpeedY(const float f);
		void SetRotationSpeedZ(const float f);
		void AddThrust(const float f);
		void SetThrust(const float f);

		// Die Attribute direkt einstellen ... nur für INIT !!!
		void SetRotation(const float rx, const float ry, const float rz);

		void SetPos(const Vector4& vc)	;
		void SetRight(const Vector4& vc);
		void SetUp(const Vector4& vc);
		void SetDir(const Vector4& vc)	;

	};



	
	class MovementControllerEgo : public MovementController
	{
	public:

		MovementControllerEgo();					// Konstruktor
		virtual ~MovementControllerEgo();			// Destruktor

		virtual void Update(const float fTime);

		// Die Methoden für die Bewegung

		void			GetRotation(float* x, float* y, float *z);
		const Vector4	GetRotation();
		void			SetRotationSpeedX(const float f);
		void			SetRotationSpeedY(const float f);
		void			SetSpeed(const float f);
		void			SetSlideSpeed(const float f);



		// Die Attribute direkt einstellen ... nur für INIT !!!

		void SetRotation(const float rx, const float ry, const float rz);
		void SetPos(const Vector4& vc);
		void SetRight(const Vector4& vc);
		void SetUp(const Vector4& vc);
		void SetDir(const Vector4& vc);

	private:

		float m_fSpeed;
		float m_fSlide;
		void RecalcAxes(void);
	};

}; // end of namespace
#endif