
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
					Matrix(_In_ Matrix&& other);
		/// constructs from Matrix
					Matrix::Matrix(const Matrix& rhs);

		/// assignment operator
		void operator=(const Matrix& rhs);
	
		/// assign XMMATRIX
		void operator=(const XMMATRIX& rhs);
		
		/// equality operator
		bool operator==(const Matrix& rhs) const;
		
		/// inequality operator
		bool operator!=(const Matrix& rhs) const;
		
		// matrix-Vector product
		const Vector4 operator * (const Vector4& v) const;

		/// C++11 Move
		Matrix& operator=( Matrix&& other);
		
		// member access
		float operator()	( const int iRow, const int iCol ) const;
		float& operator()	( const int iRow, const int iCol );
		float operator[]	( const int iPos ) const;
		float& operator[]	( const int iPos );

		operator float* ()					{return (float*)&mx;}
		operator const float* () const		{return (float*)&mx;}

		// arithmetic operations
		Matrix operator+ ( const Matrix& Matrix ) const;
		Matrix operator- ( const Matrix& Matrix ) const;
		Matrix operator* ( const Matrix& Matrix ) const;
		Matrix operator* ( float fScalar ) const;
		Matrix operator/ ( float fScalar ) const;
		Matrix operator- () const;

		// arithmetic updates
		Matrix& operator+= ( const Matrix& Matrix );
		Matrix& operator-= ( const Matrix& Matrix );
		Matrix& operator*= ( const Matrix& Matrix );
		Matrix& operator*= ( float fScalar );
		Matrix& operator/= ( float fScalar );

		/// load content from 16-byte-aligned memory
		void Load(const float* ptr);
		
		/// load content from unaligned memory
		void LoadU(const float* ptr);
		
		/// write content to 16-byte-aligned memory through the write cache
		void Store(float* ptr) const;
		
		/// write content to unaligned memory through the write cache
		void StoreU(float* ptr) const;
		
		/// stream content to 16-byte-aligned memory circumventing the write-cache
		void Stream(float* ptr) const;
		
		/// set content
		void Set(Vector4 const &row0, Vector4 const &row1, Vector4 const &row2, Vector4 const &row3);
		
		/// write access to x component
		void SetRow0(Vector4 const &row0);
		
		/// write access to y component
		void SetRow1(Vector4 const &row1);
		
		/// write access to z component
		void SetRow2(Vector4 const &row2);
		
		/// write access to w component
		void SetRow3(Vector4 const &row3);
		
		/// read-only access to x component
		const Vector4& GetRow0() const;
		
		/// read-only access to y component
		const Vector4& GetRow1() const;
		
		/// read-only access to z component
		const Vector4& GetRow2() const;
		
		/// read-only access to w component
		const Vector4& GetRow3() const;

		/// Get access to M11 element
		const float		GetM11() const;
		
		/// Get access to M12 element
		const float		GetM12() const;
		
		/// Get access to M13 element
		const float		GetM13() const;
		
		/// Get access to M14 element
		const float		GetM14() const;
		
		/// Get access to M21 element
		const float		GetM21() const;
		
		/// Get access to M22 element
		const float		GetM22() const;
		
		/// Get access to M13 element
		const float		GetM23() const;
		
		/// Get access to M14 element
		const float		GetM24() const;
		
		/// Get access to M31 element
		const float		GetM31() const;
		
		/// Get access to M32 element
		const float		GetM32() const;
		
		/// Get access to M33 element
		const float		GetM33() const;
		
		/// Get access to M34 element
		const float		GetM34() const;
		
		/// Get access to M41 element
		const float		GetM41() const;
		
		/// Get access to M42 element
		const float		GetM42() const;
		
		/// Get access to M43 element
		const float		GetM43() const;
		
		/// Get access to M44 element
		const float		GetM44() const;
		
		/// Get	Basis X
		const Vector4&	GetBasisX() const;
		
		/// Get Basis Y
		const Vector4&	GetBasisY() const;
		
		/// Get Basis Z
		const Vector4&	GetBasisZ() const;
		
		/// Get Translation
		const Vector4&	 GetTranslation() const;
		
		/// Rotation
		const Matrix	GetRotation() const;
		
		/// Set Rotation
		void			SetRotation( const Matrix& Rot );
		
		/// Set Translation
		void			SetTranslation( const Vector4& Trans );

		/// Set access to M11 element
		void			SetM11(const float m11);
		
		/// Set access to M12 element
		void			SetM12(const float m12);
		
		/// Set access to M13 element
		void			SetM13(const float m13);
		
		/// Set access to M14 element
		void			SetM14(const float m14);
		
		/// Set access to M21 element
		void			SetM21(const float m21);
		
		/// Set access to M22 element
		void			SetM22(const float m22);
		
		/// Set access to M13 element
		void			SetM23(const float m23);
		
		/// Set access to M14 element
		void			SetM24(const float m24);
		
		/// Set access to M31 element
		void			SetM31(const float m31);
		
		/// Set access to M32 element
		void			SetM32(const float m32);
		
		/// Set access to M33 element
		void			SetM33(const float m33);
		
		/// Set access to M34 element
		void			SetM34(const float m34);
		
		/// Set access to M41 element
		void			SetM41(const float m41);
		
		/// Set access to M42 element
		void			SetM42(const float m42);
		
		/// Set access to M43 element
		void			SetM43(const float m43);
		
		/// Set access to M44 element
		void			SetM44(const float m44);
		
		/// write access to x component
		void			Set_X_Axis(Vector4 const &x);
		
		/// write access to y component
		void			Set_Y_Axis(Vector4 const &y);
		
		/// write access to z component
		void			Set_Z_Axis(Vector4 const &z);
		
		/// write access to w component / pos component
		void			Set_Position(Vector4 const &pos);
		
		/// read access to x component
		const Vector4&	Get_X_Axis() const;
		
		/// read access to y component
		const Vector4&	Get_Y_Axis() const;
		
		/// read access to z component
		const Vector4&	Get_Z_Axis() const;
		
		/// read access to w component / pos component
		const Vector4&	Get_Position() const;
		
		/// add a translation to pos_component
		void			Translate(Vector4 const &t);
		
		/// scale matrix
		void			Scale(Vector4 const &v);
		
		/// Computer Matrix from Axis, rotation Angle, a Scale and a Translation
		Matrix			MakeWorldMatrix(const Vector3& rotAxis, const float rotAngle, const Vector3& scale, const Vector3& translation) ;

		/// return true if matrix is identity
		bool			IsIdentity() const;
		
		/// return determinant of matrix
		float			Determinant() const;
		
		/// decompose into scale, rotation and translation
		void			Decompose(Vector4& outScale, Quat& outRotation, Vector4& outTranslation) const;

		/// build identity matrix
		static Matrix	Identity();
		
		/// Make all elements Zero
		static Matrix	MakeZero();
		
		/// build matrix from affine transformation
		static Matrix	AffineTransformation(float scaling, Vector4 const &rotationCenter, const Quat& rotation, Vector4 const &translation);
		
		/// compute the inverse of a matrix
		static Matrix	Inverse(const Matrix& m);
		
		/// build left handed lookat matrix
		static Matrix	LookAtLH(Vector4 const &eye, Vector4 const &at, Vector4 const &up);
		
		/// build right handed lookat matrix
		static Matrix	LookAtRH(Vector4 const &eye, Vector4 const &at, Vector4 const &up);
		
		/// build left handed lookto matrix
		static Matrix	LookToLH(Vector4 const &eye, Vector4 const &at, Vector4 const &up);
		
		/// build right handed lookto matrix
		static Matrix	LookToRH(Vector4 const &eye, Vector4 const &at, Vector4 const &up);
		
		/// multiply 2 matrices
		static Matrix	Multiply(const Matrix& m0, const Matrix& m1);
		
		/// build left handed orthogonal projection matrix
		static Matrix	OrthoLH(float w, float h, float zn, float zf);
		
		/// build right handed orthogonal projection matrix
		static Matrix	OrthoRH(float w, float h, float zn, float zf);
		
		/// build left-handed off-center orthogonal projection matrix
		static Matrix	OrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf);
		
		/// build right-handed off-center orthogonal projection matrix
		static Matrix	OrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf);
		
		/// build left-handed perspective projection matrix based on field-of-view
		static Matrix	PerspectiveProjectionFovLH(float fovy, float aspect, float zn, float zf);
		
		/// build right-handed perspective projection matrix based on field-of-view
		static Matrix	PerspectiveProjectionFovRH(float fovy, float aspect, float zn, float zf);
		
		/// build left-handed perspective projection matrix
		static Matrix	PerspectiveProjectionLH(float w, float h, float zn, float zf);
		
		/// build right-handed perspective projection matrix
		static Matrix	PerspectiveProjectionRH(float w, float h, float zn, float zf);
		
		/// build left-handed off-center perspective projection matrix
		static Matrix	PerspOffCenterLH(float l, float r, float b, float t, float zn, float zf);
		
		/// build right-handed off-center perspective projection matrix
		static Matrix	PerspOffCenterRH(float l, float r, float b, float t, float zn, float zf);
		
		/// build matrix that reflects coordinates about a plance
		static Matrix	Reflect(const Plane& p);
		
		/// build rotation matrix around arbitrary axis
		static Matrix	RotationAxis(Vector4 const &axis, float angle);
		
		/// build rotation matrix from quaternion
		static Matrix	RotationQuaternion(const Quat& q);
		
		/// build x-axis-rotation matrix
		static Matrix	RotationX(float angle);
		
		/// build y-axis-rotation matrix
		static Matrix	RotationY(float angle);
		
		/// build z-axis-rotation matrix
		static Matrix	RotationZ(float angle);
		
		/// build Rotation Matrix
		void			Rotation(const Vector3& rot);
		
		/// build rotation matrix from yaw, pitch and roll
		static Matrix	RotationYawPitchRoll(float yaw, float pitch, float roll);
		
		/// build a scaling matrix from components
		static Matrix	Scaling(float sx, float sy, float sz);
		
		/// build a scaling matrix from components
		static Matrix	Scaling(float s);
		
		/// build a scaling matrix from Vector4
		static Matrix	Scaling(Vector4 const &s);
		
		/// build a transformation matrix
		static Matrix	Transformation(Vector4 const &scalingCenter, const Quat& scalingRotation, Vector4 const &scaling, Vector4 const &rotationCenter, const Quat& rotation, Vector4 const &translation);
		
		/// build a translation matrix
		static Matrix	Translation(float x, float y, float z);
		
		/// build a translation matrix from point
		static Matrix	Translation(Vector4 const &t);
		
		/// return the transpose of a matrix
		static Matrix	Transpose(const Matrix& m);
		
		/// transform 4d vector by Matrix, faster inline version than Vector4::transform
		static Vector4	Transform(const Vector4 &v, const Matrix &m);
		
		/// return a quaternion from rotational part of the 4x4 matrix
		static Quat		RotationMatrix(const Matrix& m);
		
		// transform a plane with a matrix
		static Plane	Transform(const Plane& p, const Matrix& m);


		/// Easy acces Matrix Members
		/// So it is possible to do something like this:
		/// Matrix matrix;
		/// float value = matrix[Matrix::M11];

		static const int M11 = 0;
		static const int M12 = 1;
		static const int M13 = 2;
		static const int M14 = 3;

		static const int M21 = 4;
		static const int M22 = 5;
		static const int M23 = 6;
		static const int M24 = 7;
		
		static const int M31 = 8;
		static const int M32 = 9;
		static const int M33 = 10;
		static const int M34 = 11;

		static const int M41 = 12;
		static const int M42 = 13;
		static const int M43 = 14;
		static const int M44 = 15;

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