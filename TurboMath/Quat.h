
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
		Quat() noexcept;

		/// construct from components
		Quat(const float x, const float y,const float z, const float w) noexcept;

		/// construct from Vector4
		Quat(Vector4 const &rhs) noexcept;

		/// copy constructor
		Quat(const Quat& rhs) noexcept;

		/// construct from XMVECTOR
		Quat(XMVECTOR rhs) noexcept;


		// -----------------------------------------------------------
		/// assignment operator
		// -----------------------------------------------------------

		void XM_CALLCONV operator=(const Quat& rhs) noexcept;
	
		/// assign XMVECTOR
		void XM_CALLCONV operator=(XMVECTOR rhs) noexcept;
	
		/// equality operator
		bool XM_CALLCONV operator==(const Quat& rhs) const noexcept;
	
		/// inequality operator
		bool XM_CALLCONV operator!=(const Quat& rhs) const noexcept;

		// -----------------------------------------------------------
		// Set 
		// -----------------------------------------------------------

		/// set content
		void XM_CALLCONV Set(const float x,const float y,const float z,const float w) noexcept;
	
		/// set from Vector4
		void XM_CALLCONV Set(Vector4 const &f4) noexcept;
	
		/// set from XMVECTOR
		void XM_CALLCONV Set(XMVECTOR const &f4) noexcept;
	
		/// set the x component
		void XM_CALLCONV Set_X(const float x) noexcept;
	
		/// set the y component
		void XM_CALLCONV Set_Y(const float y) noexcept;
		
		/// set the z component
		void XM_CALLCONV Set_Z(const float z) noexcept;

		/// set the w component
		void XM_CALLCONV Set_W(const float w) noexcept;

		// -----------------------------------------------------------
		// Read Write
		// -----------------------------------------------------------

		/// read/write access to x component
		float& XM_CALLCONV X() noexcept;
	
		/// read/write access to y component
		float& XM_CALLCONV Y() noexcept;
	
		/// read/write access to z component
		float& XM_CALLCONV Z() noexcept;
		
		/// read/write access to w component
		float& XM_CALLCONV W() noexcept;
	
		/// read-only access to x component
		float XM_CALLCONV X() const noexcept;
	
		/// read-only access to y component
		float XM_CALLCONV Y() const noexcept;
	
		/// read-only access to z component
		float XM_CALLCONV Z() const noexcept;
	
		/// read-only access to w component
		float XM_CALLCONV W() const noexcept;
	
		// Get Quaternion by XMVECTOR
		const XMVECTOR XM_CALLCONV Get() const noexcept;

		// -----------------------------------------------------------
		// operator
		// -----------------------------------------------------------

		/// muliply by a Quat component-wise
		void XM_CALLCONV operator*=(const Quat& rhs) noexcept;

	
		// -----------------------------------------------------------
		// Functions
		// -----------------------------------------------------------

		/// return the null vector
		static Quat XM_CALLCONV NullQuat() noexcept;

		/// returns length
		float XM_CALLCONV Length() const noexcept;

		/// returns length squared
		float XM_CALLCONV Lengthsq() const noexcept;

		/// un-denormalize Quat (this is sort of a hack since Maya likes to return denormal Quats)
		void XM_CALLCONV Undenormalize() noexcept;

		/// return true if Quat is identity
		bool XM_CALLCONV IsIdentity() const noexcept;

		/// return Quat in barycentric coordinates
		static Quat XM_CALLCONV Barycentric(const Quat& q0, const Quat& q1, const Quat& q2, float f, float g) noexcept;

		/// return conjugate of a normalized Quat
		static Quat XM_CALLCONV Conjugate(const Quat& q) noexcept;

		/// return dot product of two normalized Quats
		static float XM_CALLCONV Dot(const Quat& q0, const Quat& q1) noexcept;

		/// calculate the exponential
		static Quat XM_CALLCONV Exp(const Quat& q0) noexcept;

		/// returns an identity Quat
		static Quat XM_CALLCONV Identity() noexcept;

		/// conjugates and renormalizes Quat
		static Quat XM_CALLCONV Inverse(const Quat& q) noexcept;

		/// calculate the natural logarithm
		static Quat XM_CALLCONV ln(const Quat& q) noexcept;

		/// multiply 2 Quats
		static Quat XM_CALLCONV Multiply(const Quat& q0, const Quat& q1) noexcept;

		/// compute unit length Quat
		static Quat XM_CALLCONV Normalize(const Quat& q) noexcept;

		/// build Quat from axis and clockwise rotation angle in radians
		static Quat XM_CALLCONV RotationAxis(const Vector4& axis, float angle) noexcept;

		/// build Quat from rotation matrix
		static Quat XM_CALLCONV RotationMatrix(const Matrix& m) noexcept;

		/// build Quat from yaw, pitch and roll
		static Quat XM_CALLCONV RotationYawPitchRoll(float yaw, float pitch, float roll) noexcept;

		/// build Quaterion from roll,pitch and yaw
		static Quat XM_CALLCONV RotationRollPitchYaw(const float roll,const float pitch, const float yaw) noexcept;

		/// interpolate between 2 Quat using spherical interpolation
		static Quat XM_CALLCONV Slerp(const Quat& q1, const Quat& q2, float t) noexcept;

		/// setup control points for spherical quadrangle interpolation
		static void XM_CALLCONV SquadSetup(const Quat& q0, const Quat& q1, const Quat& q2, const Quat& q3, Quat& aOut, Quat& bOut, Quat& cOut) noexcept;

		/// interpolate between Quats using spherical quadrangle interpolation
		static Quat XM_CALLCONV Squad(const Quat& q1, const Quat& a, const Quat& b, const Quat& c, float t) noexcept;

		/// convert Quat to axis and angle
		static void XM_CALLCONV To_AxisAngle(const Quat& q, Vector4& outAxis, float& outAngle) noexcept;

		/// IsUnit ?
		bool XM_CALLCONV IsUnit() const  noexcept;

		/// IsUnit ?
		static bool XM_CALLCONV IsUnit(const XMVECTOR q) noexcept;

		/// Get Matrix from Quat
		static Matrix XM_CALLCONV GetMatrix(const Quat& q) noexcept;

		/// Make from Euler
		static Quat XM_CALLCONV MakeFromEuler(const float fPitch, const float fYaw, const float fRoll) noexcept;

		/// Get Euler from Quat
		static void XM_CALLCONV GetEulers(const Quat& q, float *fPitch, float *fYaw, float *fRoll);

		friend class Matrix;

protected:
		XMVECTOR vec;
	};

}; // namespace TurboMath



#endif