
// -------------------------------------------------------------------
// File			:	Quat
//
// Project		:	TurboMath
//
// Description	:	Class for Quat
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

#ifndef _TURBOMATH_QUAT_H_
#define _TURBOMATH_QUAT_H_

namespace TurboMath
{
	CACHE_ALIGN(16) class Quat
	{
	public:
		//------------------------------------------------------------
		// Constructor
		// -----------------------------------------------------------

		/// default constructor, NOTE: does NOT setup components!
		Quat();

		/// construct from components
		Quat(float x, float y, float z, float w);

		/// construct from Vector4
		Quat(Vector4 const &rhs);

		/// copy constructor
		Quat(const Quat& rhs);

		/// construct from XMVECTOR
		Quat(XMVECTOR rhs);


		// -----------------------------------------------------------
		/// assignment operator
		// -----------------------------------------------------------

		void operator=(const Quat& rhs);
	
		/// assign XMVECTOR
		void operator=(XMVECTOR rhs);
	
		/// equality operator
		bool operator==(const Quat& rhs) const;
	
		/// inequality operator
		bool operator!=(const Quat& rhs) const;

		// -----------------------------------------------------------
		// Set 
		// -----------------------------------------------------------

		/// set content
		void Set(const float x,const float y,const float z,const float w);
	
		/// set from Vector4
		void Set(Vector4 const &f4);
	
		/// set from XMVECTOR
		void Set(XMVECTOR const &f4);
	
		/// set the x component
		void Set_X(const float x);
	
		/// set the y component
		void Set_Y(const float y);
		
		/// set the z component
		void Set_Z(const float z);

		/// set the w component
		void Set_W(const float w);

		// -----------------------------------------------------------
		// Read Write
		// -----------------------------------------------------------

		/// read/write access to x component
		float& X();
	
		/// read/write access to y component
		float& Y();
	
		/// read/write access to z component
		float& Z();
		
		/// read/write access to w component
		float& W();
	
		/// read-only access to x component
		float X() const;
	
		/// read-only access to y component
		float Y() const;
	
		/// read-only access to z component
		float Z() const;
	
		/// read-only access to w component
		float W() const;
	
		// Get Quaternion by XMVECTOR
		const XMVECTOR Get() const;

		// -----------------------------------------------------------
		// operator
		// -----------------------------------------------------------

		/// muliply by a Quat component-wise
		void operator*=(const Quat& rhs);

	
		// -----------------------------------------------------------
		// Functions
		// -----------------------------------------------------------

		/// return the null vector
		static Quat NullQuat();

		/// returns length
		float Length() const;

		/// returns length squared
		float Lengthsq() const;

		/// un-denormalize Quat (this is sort of a hack since Maya likes to return denormal Quats)
		void Undenormalize();

		/// return true if Quat is identity
		bool IsIdentity() const;

		/// return Quat in barycentric coordinates
		static Quat Barycentric(const Quat& q0, const Quat& q1, const Quat& q2, float f, float g);

		/// return conjugate of a normalized Quat
		static Quat Conjugate(const Quat& q);

		/// return dot product of two normalized Quats
		static float Dot(const Quat& q0, const Quat& q1);

		/// calculate the exponential
		static Quat Exp(const Quat& q0);

		/// returns an identity Quat
		static Quat Identity();

		/// conjugates and renormalizes Quat
		static Quat Inverse(const Quat& q);

		/// calculate the natural logarithm
		static Quat ln(const Quat& q);

		/// multiply 2 Quats
		static Quat Multiply(const Quat& q0, const Quat& q1);

		/// compute unit length Quat
		static Quat Normalize(const Quat& q);

		/// build Quat from axis and clockwise rotation angle in radians
		static Quat RotationAxis(const Vector4& axis, float angle);

		/// build Quat from rotation matrix
		static Quat RotationMatrix(const Matrix& m);

		/// build Quat from yaw, pitch and roll
		static Quat RotationYawPitchRoll(float yaw, float pitch, float roll);

		/// build Quaterion from roll,pitch and yaw
		static Quat RotationRollPitchYaw(const float roll,const float pitch, const float yaw);

		/// interpolate between 2 Quat using spherical interpolation
		static Quat Slerp(const Quat& q1, const Quat& q2, float t);

		/// setup control points for spherical quadrangle interpolation
		static void SquadSetup(const Quat& q0, const Quat& q1, const Quat& q2, const Quat& q3, Quat& aOut, Quat& bOut, Quat& cOut);

		/// interpolate between Quats using spherical quadrangle interpolation
		static Quat Squad(const Quat& q1, const Quat& a, const Quat& b, const Quat& c, float t);

		/// convert Quat to axis and angle
		static void To_AxisAngle(const Quat& q, Vector4& outAxis, float& outAngle);

		/// IsUnit ?
		bool IsUnit() const ;

		/// IsUnit ?
		static bool IsUnit(const XMVECTOR q);

		/// Get Matrix from Quat
		static Matrix GetMatrix(const Quat& q);

		/// Make from Euler
		static Quat MakeFromEuler(const float fPitch, const float fYaw, const float fRoll);

		/// Get Euler from Quat
		static void GetEulers(const Quat& q, float *fPitch, float *fYaw, float *fRoll);

		friend class Matrix;

protected:
		XMVECTOR vec;
	};

}; // namespace TurboMath



#endif