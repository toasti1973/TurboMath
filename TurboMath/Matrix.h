
// -------------------------------------------------------------------
// File			:	Matrix
//
// Project		:	TurboMath
//
// Description	:	Class for Matrix
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


#ifndef _TURBOMATH_MATRIX_H_
#define _TURBOMATH_MATRIX_H_


namespace TurboMath
{

	CACHE_ALIGN(16) class Matrix
	{
	public:
		
		/// default constructor, NOTE: setup components to Identity!
					Matrix();
		/// construct from components
		explicit	Matrix(Vector4 const &row0, Vector4 const &row1, Vector4 const &row2, Vector4 const &row3);
		/// construct from XMMATRIX
					Matrix(const XMMATRIX& rhs);
		/// C++11 Move Constructor
					Matrix(_In_ Matrix&& other) noexcept;
		/// constructs from Matrix
					Matrix::Matrix(const Matrix& rhs) noexcept;

		/// assignment operator
		void XM_CALLCONV operator=(const Matrix& rhs) noexcept;
	
		/// assign XMMATRIX
		void XM_CALLCONV operator=(const XMMATRIX& rhs) noexcept;
		
		/// equality operator
		bool XM_CALLCONV operator==(const Matrix& rhs) const noexcept;
		
		/// inequality operator
		bool XM_CALLCONV operator!=(const Matrix& rhs) const noexcept;
		
		// matrix-Vector product
		const Vector4 XM_CALLCONV operator * (const Vector4& v) const noexcept;

		/// C++11 Move
		Matrix& XM_CALLCONV operator=( Matrix&& other) noexcept;
		
		// member access
		float	XM_CALLCONV	operator()	( const int iRow, const int iCol ) const;
		float&	XM_CALLCONV	operator()	( const int iRow, const int iCol );
		float	XM_CALLCONV	operator[]	( const int iPos ) const;
		float&	XM_CALLCONV	operator[]	( const int iPos );

		operator float* ()			{return (float*)&mx;}
		operator const float* () const		{return (float*)&mx;}

		// arithmetic operations
		Matrix XM_CALLCONV operator+ ( const Matrix& Matrix ) const noexcept;
		Matrix XM_CALLCONV operator- (const Matrix& Matrix) const noexcept;
		Matrix XM_CALLCONV operator* ( const Matrix& Matrix ) const noexcept;
		Matrix XM_CALLCONV operator* ( float fScalar ) const noexcept;
		Matrix XM_CALLCONV operator/ ( float fScalar ) const noexcept;
		Matrix XM_CALLCONV operator- () const noexcept;

		// arithmetic updates
		Matrix& XM_CALLCONV operator+= ( const Matrix& Matrix ) noexcept;
		Matrix& XM_CALLCONV operator-= ( const Matrix& Matrix ) noexcept;
		Matrix& XM_CALLCONV operator*= ( const Matrix& Matrix ) noexcept;
		Matrix& XM_CALLCONV operator*= ( float fScalar ) noexcept;
		Matrix& XM_CALLCONV operator/= ( float fScalar ) noexcept;

		/// load content from 16-byte-aligned memory
		void XM_CALLCONV Load(const float* ptr) noexcept;
		
		/// load content from unaligned memory
		void XM_CALLCONV LoadU(const float* ptr) noexcept;
		
		/// write content to 16-byte-aligned memory through the write cache
		void XM_CALLCONV Store(float* ptr) const noexcept;
		
		/// write content to unaligned memory through the write cache
		void XM_CALLCONV StoreU(float* ptr) const noexcept;
		
		/// stream content to 16-byte-aligned memory circumventing the write-cache
		void XM_CALLCONV Stream(float* ptr) const noexcept;
		
		/// set content
		void XM_CALLCONV Set(Vector4 const &row0, Vector4 const &row1, Vector4 const &row2, Vector4 const &row3) noexcept;
		
		/// write access to x component
		void XM_CALLCONV SetRow0(Vector4 const &row0) noexcept;
		
		/// write access to y component
		void XM_CALLCONV SetRow1(Vector4 const &row1) noexcept;
		
		/// write access to z component
		void XM_CALLCONV SetRow2(Vector4 const &row2) noexcept;
		
		/// write access to w component
		void XM_CALLCONV SetRow3(Vector4 const &row3) noexcept;
		
		/// read-only access to x component
		const Vector4&  XM_CALLCONV GetRow0() const noexcept;
		
		/// read-only access to y component
		const Vector4&  XM_CALLCONV GetRow1() const noexcept;
		
		/// read-only access to z component
		const Vector4&  XM_CALLCONV GetRow2() const noexcept;
		
		/// read-only access to w component
		const Vector4&  XM_CALLCONV GetRow3() const noexcept;

		/// Get access to M11 element
		const float	XM_CALLCONV GetM11() const noexcept;
		
		/// Get access to M12 element
		const float	XM_CALLCONV GetM12() const noexcept;
		
		/// Get access to M13 element
		const float	XM_CALLCONV GetM13() const noexcept;
		
		/// Get access to M14 element
		const float	XM_CALLCONV GetM14() const noexcept;
		
		/// Get access to M21 element
		const float	XM_CALLCONV GetM21() const noexcept;
		
		/// Get access to M22 element
		const float	XM_CALLCONV GetM22() const noexcept;
		
		/// Get access to M13 element
		const float	XM_CALLCONV GetM23() const noexcept;
		
		/// Get access to M14 element
		const float	XM_CALLCONV GetM24() const noexcept;
		
		/// Get access to M31 element
		const float	XM_CALLCONV GetM31() const noexcept;
		
		/// Get access to M32 element
		const float	XM_CALLCONV GetM32() const noexcept;
		
		/// Get access to M33 element
		const float	XM_CALLCONV GetM33() const noexcept;
		
		/// Get access to M34 element
		const float	XM_CALLCONV GetM34() const noexcept;
		
		/// Get access to M41 element
		const float	XM_CALLCONV GetM41() const noexcept;
		
		/// Get access to M42 element
		const float	XM_CALLCONV GetM42() const noexcept;
		
		/// Get access to M43 element
		const float	XM_CALLCONV GetM43() const noexcept;
		
		/// Get access to M44 element
		const float	XM_CALLCONV GetM44() const noexcept;
		
		/// Get	Basis X
		const Vector4&	XM_CALLCONV GetBasisX() const noexcept;
		
		/// Get Basis Y
		const Vector4&	XM_CALLCONV GetBasisY() const noexcept;
		
		/// Get Basis Z
		const Vector4&	XM_CALLCONV GetBasisZ() const noexcept;
		
		/// Get Translation
		const Vector4&	XM_CALLCONV GetTranslation() const noexcept;
		
		/// Rotation
		const Matrix	XM_CALLCONV GetRotation() const noexcept;
		
		/// Set Rotation
		void		XM_CALLCONV SetRotation( const Matrix& Rot ) noexcept;
		
		/// Set Translation
		void		XM_CALLCONV SetTranslation( const Vector4& Trans ) noexcept;

		/// Set access to M11 element
		void		XM_CALLCONV SetM11(const float m11) noexcept;
		
		/// Set access to M12 element
		void		XM_CALLCONV SetM12(const float m12) noexcept;
		
		/// Set access to M13 element
		void		XM_CALLCONV SetM13(const float m13) noexcept;
		
		/// Set access to M14 element
		void		XM_CALLCONV SetM14(const float m14) noexcept;
		
		/// Set access to M21 element
		void		XM_CALLCONV SetM21(const float m21) noexcept;
		
		/// Set access to M22 element
		void		XM_CALLCONV SetM22(const float m22) noexcept;
		
		/// Set access to M13 element
		void		XM_CALLCONV SetM23(const float m23) noexcept;
		
		/// Set access to M14 element
		void		XM_CALLCONV SetM24(const float m24) noexcept;
		
		/// Set access to M31 element
		void		XM_CALLCONV SetM31(const float m31) noexcept;
		
		/// Set access to M32 element
		void		XM_CALLCONV SetM32(const float m32) noexcept;
		
		/// Set access to M33 element
		void		XM_CALLCONV SetM33(const float m33) noexcept;
		
		/// Set access to M34 element
		void		XM_CALLCONV SetM34(const float m34) noexcept;
		
		/// Set access to M41 element
		void		XM_CALLCONV SetM41(const float m41) noexcept;
		
		/// Set access to M42 element
		void		XM_CALLCONV SetM42(const float m42) noexcept;
		
		/// Set access to M43 element
		void		XM_CALLCONV SetM43(const float m43) noexcept;
		
		/// Set access to M44 element
		void		XM_CALLCONV SetM44(const float m44) noexcept;
		
		/// write access to x component
		void		XM_CALLCONV Set_X_Axis(Vector4 const &x) noexcept;
		
		/// write access to y component
		void		XM_CALLCONV Set_Y_Axis(Vector4 const &y) noexcept;
		
		/// write access to z component
		void		XM_CALLCONV Set_Z_Axis(Vector4 const &z) noexcept;
		
		/// write access to w component / pos component
		void		XM_CALLCONV Set_Position(Vector4 const &pos) noexcept;
		
		/// read access to x component
		const Vector4&	XM_CALLCONV Get_X_Axis() const noexcept;
		
		/// read access to y component
		const Vector4&	XM_CALLCONV Get_Y_Axis() const noexcept;
		
		/// read access to z component
		const Vector4&	XM_CALLCONV Get_Z_Axis() const noexcept;
		
		/// read access to w component / pos component
		const Vector4&	XM_CALLCONV Get_Position() const noexcept;
		
		/// add a translation to pos_component
		void		XM_CALLCONV Translate(Vector4 const &t);
		
		/// scale matrix
		void		XM_CALLCONV Scale(Vector4 const &v) noexcept;
		
		/// Computer Matrix from Axis, rotation Angle, a Scale and a Translation
		Matrix		XM_CALLCONV MakeWorldMatrix(const Vector3& rotAxis, const float rotAngle, const Vector3& scale, const Vector3& translation) noexcept ;

		/// return true if matrix is identity
		bool		XM_CALLCONV IsIdentity() const noexcept;
		
		/// return determinant of matrix
		float		XM_CALLCONV Determinant() const noexcept;
		
		/// decompose into scale, rotation and translation
		void		XM_CALLCONV Decompose(Vector4& outScale, Quat& outRotation, Vector4& outTranslation) const;

		/// build identity matrix
		static Matrix	XM_CALLCONV Identity() noexcept;
		
		/// Make all elements Zero
		static Matrix	XM_CALLCONV MakeZero() noexcept;
		
		/// build matrix from affine transformation
		static Matrix	XM_CALLCONV AffineTransformation(float scaling, Vector4 const &rotationCenter, const Quat& rotation, Vector4 const &translation) noexcept;
		
		/// compute the inverse of a matrix
		static Matrix	XM_CALLCONV Inverse(const Matrix& m) noexcept;
		
		/// build left handed lookat matrix
		static Matrix	XM_CALLCONV LookAtLH(Vector4 const &eye, Vector4 const &at, Vector4 const &up) noexcept;
		
		/// build right handed lookat matrix
		static Matrix	XM_CALLCONV LookAtRH(Vector4 const &eye, Vector4 const &at, Vector4 const &up) noexcept;
		
		/// build left handed lookto matrix
		static Matrix	XM_CALLCONV LookToLH(Vector4 const &eye, Vector4 const &at, Vector4 const &up) noexcept;
		
		/// build right handed lookto matrix
		static Matrix	XM_CALLCONV LookToRH(Vector4 const &eye, Vector4 const &at, Vector4 const &up) noexcept;
		
		/// multiply 2 matrices
		static Matrix	XM_CALLCONV Multiply(const Matrix& m0, const Matrix& m1) noexcept;
		
		/// build left handed orthogonal projection matrix
		static Matrix	XM_CALLCONV OrthoLH(float w, float h, float zn, float zf) noexcept;
		
		/// build right handed orthogonal projection matrix
		static Matrix	XM_CALLCONV OrthoRH(float w, float h, float zn, float zf) noexcept;
		
		/// build left-handed off-center orthogonal projection matrix
		static Matrix	XM_CALLCONV OrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf) noexcept;
		
		/// build right-handed off-center orthogonal projection matrix
		static Matrix	XM_CALLCONV OrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf) noexcept;
		
		/// build left-handed perspective projection matrix based on field-of-view
		static Matrix	XM_CALLCONV PerspectiveProjectionFovLH(float fovy, float aspect, float zn, float zf) noexcept;
		
		/// build right-handed perspective projection matrix based on field-of-view
		static Matrix	XM_CALLCONV PerspectiveProjectionFovRH(float fovy, float aspect, float zn, float zf) noexcept;
		
		/// build left-handed perspective projection matrix
		static Matrix	XM_CALLCONV PerspectiveProjectionLH(float w, float h, float zn, float zf) noexcept;
		
		/// build right-handed perspective projection matrix
		static Matrix	XM_CALLCONV PerspectiveProjectionRH(float w, float h, float zn, float zf) noexcept;
		
		/// build left-handed off-center perspective projection matrix
		static Matrix	XM_CALLCONV PerspOffCenterLH(float l, float r, float b, float t, float zn, float zf) noexcept;
		
		/// build right-handed off-center perspective projection matrix
		static Matrix	XM_CALLCONV PerspOffCenterRH(float l, float r, float b, float t, float zn, float zf) noexcept;
		
		/// build matrix that reflects coordinates about a plance
		static Matrix	XM_CALLCONV Reflect(const Plane& p) noexcept;
		
		/// build rotation matrix around arbitrary axis
		static Matrix	XM_CALLCONV RotationAxis(Vector4 const &axis, float angle) noexcept;
		
		/// build rotation matrix from quaternion
		static Matrix	XM_CALLCONV RotationQuaternion(const Quat& q) noexcept;
		
		/// build x-axis-rotation matrix
		static Matrix	XM_CALLCONV RotationX(float angle) noexcept;
		
		/// build y-axis-rotation matrix
		static Matrix	XM_CALLCONV RotationY(float angle) noexcept;
		
		/// build z-axis-rotation matrix
		static Matrix	XM_CALLCONV RotationZ(float angle) noexcept;
		
		/// build Rotation Matrix
		void		XM_CALLCONV Rotation(const Vector3& rot) noexcept;
		
		/// build rotation matrix from yaw, pitch and roll
		static Matrix	XM_CALLCONV RotationYawPitchRoll(float yaw, float pitch, float roll) noexcept;
		
		/// build a scaling matrix from components
		static Matrix	XM_CALLCONV Scaling(float sx, float sy, float sz) noexcept;
		
		/// build a scaling matrix from components
		static Matrix	XM_CALLCONV Scaling(float s) noexcept;
		
		/// build a scaling matrix from Vector4
		static Matrix	XM_CALLCONV Scaling(Vector4 const &s) noexcept;
		
		/// build a transformation matrix
		static Matrix	XM_CALLCONV Transformation(Vector4 const &scalingCenter, const Quat& scalingRotation, Vector4 const &scaling, Vector4 const &rotationCenter, const Quat& rotation, Vector4 const &translation) noexcept;
		
		/// build a translation matrix
		static Matrix	XM_CALLCONV Translation(float x, float y, float z) noexcept;
		
		/// build a translation matrix from point
		static Matrix	XM_CALLCONV Translation(Vector4 const &t) noexcept;
		
		/// return the transpose of a matrix
		static Matrix	XM_CALLCONV Transpose(const Matrix& m) noexcept;
		
		/// transform 4d vector by Matrix, faster inline version than Vector4::transform
		static Vector4	XM_CALLCONV Transform(const Vector4 &v, const Matrix &m) noexcept;
		
		/// return a quaternion from rotational part of the 4x4 matrix
		static Quat	XM_CALLCONV 	RotationMatrix(const Matrix& m) noexcept;
		
		// transform a plane with a matrix
		static Plane	XM_CALLCONV Transform(const Plane& p, const Matrix& m) noexcept;


		/// Easy acces Matrix Members
		/// So it is possible to do something like this:
		/// Matrix matrix;
		/// float value = matrix[Matrix::M11];

		static constexpr int M11 = 0;
		static constexpr int M12 = 1;
		static constexpr int M13 = 2;
		static constexpr int M14 = 3;

		static constexpr int M21 = 4;
		static constexpr int M22 = 5;
		static constexpr int M23 = 6;
		static constexpr int M24 = 7;
		
		static constexpr int M31 = 8;
		static constexpr int M32 = 9;
		static constexpr int M33 = 10;
		static constexpr int M34 = 11;

		static constexpr int M41 = 12;
		static constexpr int M42 = 13;
		static constexpr int M43 = 14;
		static constexpr int M44 = 15;

		/// friend-classes
		friend class Vector2;
		friend class Vector3;
		friend class Vector4;
		friend class Plane;
		friend class Quat;
		friend class Frustum;

	protected:
		XMMATRIX mx;
	};// End of Class : Matrix



}; // Namespace TurboMath

#endif