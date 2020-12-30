
// -------------------------------------------------------------------
// File			:	Matrix.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for Matrix-Class
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


namespace TurboMath
{

		// The Matrix Functions

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix::Matrix():
	mx(XMMatrixIdentity())
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->mx,16));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix::Matrix(Vector4 const &row0, Vector4 const &row1, Vector4 const &row2, Vector4 const &row3)
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->mx,16));

		this->mx.r[0] = row0;
		this->mx.r[1] = row1;
		this->mx.r[2] = row2;
		this->mx.r[3] = row3;
	}

	//------------------------------------------------------------------------------
	/**
	*/

	XM_INLINE   Matrix::Matrix( Matrix&& rhs) noexcept
	{
		this->mx.r[0] = rhs.mx.r[0];
		this->mx.r[1] = rhs.mx.r[1];
		this->mx.r[2] = rhs.mx.r[2];
		this->mx.r[3] = rhs.mx.r[3];
	}


	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix::Matrix(const XMMATRIX& rhs) :
	mx(rhs)
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->mx,16));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix::Matrix(const Matrix& rhs) noexcept:
	mx(rhs)
	{
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV Matrix::operator=(const Matrix& rhs) noexcept
	{
		this->mx = rhs.mx;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV Matrix::operator=(const XMMATRIX& rhs) noexcept
	{
		this->mx = rhs;
	}

	//------------------------------------------------------------------------------
	/**
	*/ 
	/// C++11 Move
	XM_INLINE   Matrix& XM_CALLCONV Matrix::operator=( Matrix&& other) noexcept
	{
		this->mx = other.mx;
		return *this;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   bool XM_CALLCONV Matrix::operator==(const Matrix& rhs) const noexcept
	{
		return XMVector4Equal(this->mx.r[0], rhs.mx.r[0]) &&
			XMVector4Equal(this->mx.r[1], rhs.mx.r[1]) &&
			XMVector4Equal(this->mx.r[2], rhs.mx.r[2]) &&
			XMVector4Equal(this->mx.r[3], rhs.mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   bool XM_CALLCONV Matrix::operator!=(const Matrix& rhs) const noexcept
	{
		return XMVector4NotEqual(this->mx.r[0], rhs.mx.r[0]) ||
			XMVector4NotEqual(this->mx.r[1], rhs.mx.r[1]) ||
			XMVector4NotEqual(this->mx.r[2], rhs.mx.r[2]) ||
			XMVector4NotEqual(this->mx.r[3], rhs.mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   const Vector4 XM_CALLCONV Matrix::operator * (const Vector4& v) const noexcept
	{
		XMVector3Transform(v, this->mx );

		return v;
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   float XM_CALLCONV Matrix::operator[] ( const int iPos ) const
	{
		assert (iPos < 16);

		const int iRow = iPos / 4;
		const int iCol = iPos % 4;

		assert (iRow < 4);
		assert (iCol < 4);

		return mx.r[iRow].m128_f32[iCol];
	}
	//----------------------------------------------------------------------------------------------------
	XM_INLINE   float& XM_CALLCONV Matrix::operator[] ( const int iPos )
	{
		assert (iPos < 16);

		const int iRow = iPos / 4;
		const int iCol = iPos % 4;

		assert (iRow < 4);
		assert (iCol < 4);

		return mx.r[iRow].m128_f32[iCol];
	}
	//----------------------------------------------------------------------------------------------------
	XM_INLINE   float XM_CALLCONV Matrix::operator() ( const int iRow, const int iCol ) const
	{
		assert (iRow < 4);
		assert (iCol < 4);

		return mx.r[iRow].m128_f32[iCol];
	}
	//----------------------------------------------------------------------------------------------------
	XM_INLINE   float& XM_CALLCONV  Matrix::operator() ( const int iRow, const int iCol )
	{
		assert (iRow < 4);
		assert (iCol < 4);

		return mx.r[iRow].m128_f32[iCol];
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV Matrix::Load(const float* ptr) noexcept
	{
		this->mx.r[0] = XMLoadFloat4A((XMFLOAT4A*)ptr);
		this->mx.r[1] = XMLoadFloat4A((XMFLOAT4A*)(ptr + 4));
		this->mx.r[2] = XMLoadFloat4A((XMFLOAT4A*)(ptr + 8));
		this->mx.r[3] = XMLoadFloat4A((XMFLOAT4A*)(ptr + 12));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV Matrix::LoadU(const float* ptr) noexcept
	{
		this->mx.r[0] = XMLoadFloat4((XMFLOAT4*)ptr);
		this->mx.r[1] = XMLoadFloat4((XMFLOAT4*)(ptr + 4));
		this->mx.r[2] = XMLoadFloat4((XMFLOAT4*)(ptr + 8));
		this->mx.r[3] = XMLoadFloat4((XMFLOAT4*)(ptr + 12));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV Matrix::Store(float* ptr) const noexcept
	{
		XMStoreFloat4A((XMFLOAT4A*)ptr, this->mx.r[0]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 4), this->mx.r[1]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 8), this->mx.r[2]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 12), this->mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV Matrix::StoreU(float* ptr) const noexcept
	{
		XMStoreFloat4((XMFLOAT4*)ptr, this->mx.r[0]);
		XMStoreFloat4((XMFLOAT4*)(ptr + 4), this->mx.r[1]);
		XMStoreFloat4((XMFLOAT4*)(ptr + 8), this->mx.r[2]);
		XMStoreFloat4((XMFLOAT4*)(ptr + 12), this->mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV Matrix::Stream(float* ptr) const noexcept
	{
		XMStoreFloat4A((XMFLOAT4A*)ptr, this->mx.r[0]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 4), this->mx.r[1]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 8), this->mx.r[2]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 12), this->mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV  Matrix::Set(Vector4 const &row0, Vector4 const &row1, Vector4 const &row2, Vector4 const &row3) noexcept
	{
		this->mx.r[0] = row0;
		this->mx.r[1] = row1;
		this->mx.r[2] = row2;
		this->mx.r[3] = row3;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV 	Matrix::SetRow0(Vector4 const &r) noexcept
	{
		this->mx.r[0] = r;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   const Vector4& XM_CALLCONV 	Matrix::GetRow0() const noexcept
	{
		return *(Vector4*)&(this->mx.r[0]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV 	Matrix::SetRow1(Vector4 const &r) noexcept
	{
		this->mx.r[1] = r;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   const Vector4& XM_CALLCONV  Matrix::GetRow1() const noexcept
	{
		return *(Vector4*)&(this->mx.r[1]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV 	Matrix::SetRow2(Vector4 const &r) noexcept
	{
		this->mx.r[2] = r;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   const Vector4& XM_CALLCONV 	Matrix::GetRow2() const noexcept
	{
		return *(Vector4*)&(this->mx.r[2]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV 	Matrix::SetRow3(Vector4 const &r) noexcept
	{
		this->mx.r[3] = r;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   const Vector4& XM_CALLCONV 	Matrix::GetRow3() const noexcept
	{
		return *(Vector4*)&(this->mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV 	Matrix::Set_X_Axis(Vector4 const &x) noexcept
	{
		this->mx.r[0] = x;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV 	Matrix::Set_Y_Axis(Vector4 const &y) noexcept
	{
		this->mx.r[1] = y;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV 	Matrix::Set_Z_Axis(Vector4 const &z) noexcept
	{
		this->mx.r[2] = z;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV 	Matrix::Set_Position(Vector4 const &pos) noexcept
	{
		this->mx.r[3] = pos;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   const Vector4& XM_CALLCONV 	Matrix::Get_X_Axis() const noexcept
	{
		return *(Vector4*)&(this->mx.r[0]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   const Vector4& XM_CALLCONV 	Matrix::Get_Y_Axis() const noexcept
	{
		return *(Vector4*)&(this->mx.r[1]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   const Vector4& XM_CALLCONV 	Matrix::Get_Z_Axis() const noexcept
	{
		return *(Vector4*)&(this->mx.r[2]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   const Vector4& XM_CALLCONV 	Matrix::Get_Position() const noexcept
	{
		return *(Vector4*)&(this->mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void  XM_CALLCONV 	Matrix::Translate(Vector4 const &t)
	{
		assert(t.GetW() == 0 && "w component not 0, use vector for translation not a point!");

		this->mx.r[3] += t;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   void XM_CALLCONV 	Matrix::Scale(Vector4 const &s) noexcept
	{
		// need to make sure that last column isn't erased
		Vector4 scl = s;
		scl.SetW(1.0f);

		this->mx.r[0] = Vector4::Multiply(this->mx.r[0], scl);
		this->mx.r[1] = Vector4::Multiply(this->mx.r[1], scl);
		this->mx.r[2] = Vector4::Multiply(this->mx.r[2], scl);
		this->mx.r[3] = Vector4::Multiply(this->mx.r[3], scl);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   bool XM_CALLCONV 	Matrix::IsIdentity() const noexcept
	{
		return (0 != XMMatrixIsIdentity(this->mx));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   float XM_CALLCONV 	Matrix::Determinant() const noexcept
	{
		return Vector4::Unpack_X(XMMatrixDeterminant(this->mx));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::Identity() noexcept
	{
		return XMMatrixIdentity();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::MakeZero() noexcept
	{
		Matrix temp;

		temp.SetRow0( Vector4::NullVec());
		temp.SetRow1( Vector4::NullVec());
		temp.SetRow2( Vector4::NullVec());
		temp.SetRow3( Vector4::NullVec());

		return temp;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::Inverse(const Matrix& m) noexcept
	{
		XMVECTOR det;
		return XMMatrixInverse(&det, m.mx);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::LookAtLH(Vector4 const &eye, Vector4 const &at, Vector4 const &up) noexcept
	{
		return XMMatrixLookAtLH(eye,at,up);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::LookAtRH(Vector4 const &eye, Vector4 const &at, Vector4 const &up) noexcept
	{
		return XMMatrixLookAtRH(eye,at,up);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::LookToLH(Vector4 const &eye, Vector4 const &at, Vector4 const &up) noexcept
	{
		return XMMatrixLookToLH(eye,at,up);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::LookToRH(Vector4 const &eye, Vector4 const &at, Vector4 const &up) noexcept
	{
		return XMMatrixLookToRH(eye,at,up);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::Multiply(const Matrix& m0, const Matrix& m1) noexcept
	{
		return XMMatrixMultiply(m0.mx, m1.mx);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::OrthoLH(float w, float h, float zn, float zf) noexcept
	{
		return XMMatrixOrthographicLH(w, h, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::OrthoRH(float w, float h, float zn, float zf) noexcept
	{
		return XMMatrixOrthographicRH(w, h, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::OrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf) noexcept
	{
		return XMMatrixOrthographicOffCenterLH(l, r, b, t, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::OrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf) noexcept
	{
		return XMMatrixOrthographicOffCenterRH(l, r, b, t, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::PerspectiveProjectionFovLH(float fovy, float aspect, float zn, float zf) noexcept
	{
		return XMMatrixPerspectiveFovLH(fovy, aspect, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::PerspectiveProjectionFovRH(float fovy, float aspect, float zn, float zf) noexcept
	{
		return XMMatrixPerspectiveFovRH(fovy, aspect, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::PerspectiveProjectionLH(float w, float h, float zn, float zf) noexcept
	{
		return XMMatrixPerspectiveLH(w, h, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::PerspectiveProjectionRH(float w, float h, float zn, float zf) noexcept
	{
		return XMMatrixPerspectiveRH(w, h, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::PerspOffCenterLH(float l, float r, float b, float t, float zn, float zf) noexcept
	{
		return XMMatrixPerspectiveOffCenterLH(l, r, b, t, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::PerspOffCenterRH(float l, float r, float b, float t, float zn, float zf) noexcept
	{
		return XMMatrixPerspectiveOffCenterRH(l, r, b, t, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::RotationAxis(Vector4 const &axis, float angle) noexcept
	{
		return XMMatrixRotationAxis(axis, angle);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::RotationX(float angle) noexcept
	{
		return XMMatrixRotationX(angle);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::RotationY(float angle) noexcept
	{
		return XMMatrixRotationY(angle);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::RotationZ(float angle) noexcept
	{
		return XMMatrixRotationZ(angle);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV 	Matrix::RotationYawPitchRoll(float yaw, float pitch, float roll) noexcept
	{
		return XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	}
	//------------------------------------------------------------------------------
	/**
	*/

	XM_INLINE   void XM_CALLCONV 	Matrix::Rotation( const Vector3& rot ) noexcept
	{
		Matrix mRot1;
		Matrix mRot2;

		mRot1 = TurboMath::Matrix::RotationZ(rot.GetZ());
		mRot2 = TurboMath::Matrix::RotationX(rot.GetX());
		mRot1 *= mRot2;
		mRot2 = TurboMath::Matrix::RotationY(rot.GetY());
		mRot1 *= mRot2;

		*this = mRot1;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV Matrix::Scaling(float sx, float sy, float sz) noexcept
	{
		return XMMatrixScaling(sx, sy, sz);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV Matrix::Scaling(float s) noexcept
	{
		return XMMatrixScaling(s, s, s);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV Matrix::Scaling(Vector4 const &s) noexcept
	{
		return XMMatrixScalingFromVector(s);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV Matrix::Translation(float x, float y, float z) noexcept
	{
		return XMMatrixTranslation(x, y, z);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV Matrix::Translation(Vector4 const &t) noexcept
	{
		return XMMatrixTranslationFromVector(t);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Matrix XM_CALLCONV Matrix::Transpose(const Matrix& m) noexcept
	{
		return XMMatrixTranspose(m.mx);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Vector4 XM_CALLCONV Matrix::Transform(const Vector4 &v, const Matrix &m) noexcept
	{
		return XMVector4Transform(v, m.mx);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Quat XM_CALLCONV Matrix::RotationMatrix(const Matrix& m) noexcept
	{
		return XMQuaternionRotationMatrix(m.mx);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	XM_INLINE   Plane XM_CALLCONV Matrix::Transform(const Plane &p, const Matrix& m) noexcept
	{
		return Plane(XMPlaneTransform(p.vec, m.mx));
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M11 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM11() const noexcept
	{
		return mx.r[0].m128_f32[0];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M12 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM12() const noexcept
	{
		return mx.r[0].m128_f32[1];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M13 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM13() const noexcept
	{
		return mx.r[0].m128_f32[2];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M14 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM14() const noexcept
	{
		return mx.r[0].m128_f32[3];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M21 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM21() const noexcept
	{
		return mx.r[1].m128_f32[0];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M22 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM22() const noexcept
	{
		return mx.r[1].m128_f32[1];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M23 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM23() const noexcept
	{
		return mx.r[1].m128_f32[2];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M24 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM24() const noexcept
	{
		return mx.r[1].m128_f32[3];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M31 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM31() const noexcept
	{
		return mx.r[2].m128_f32[0];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M32 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM32() const noexcept
	{
		return mx.r[2].m128_f32[1];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M33 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM33() const noexcept
	{
		return mx.r[2].m128_f32[2];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M34 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM34() const noexcept
	{
		return mx.r[2].m128_f32[3];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M41 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM41() const noexcept
	{
		return mx.r[3].m128_f32[0];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M42 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM42() const noexcept
	{
		return mx.r[3].m128_f32[1];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M43 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM43() const noexcept
	{
		return mx.r[3].m128_f32[2];
	}

	//----------------------------------------------------------------------------------------------------
	/// Get access to M44 element
	XM_INLINE   const float	XM_CALLCONV Matrix::GetM44() const noexcept
	{
		return mx.r[3].m128_f32[3];
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M11 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM11(const float m11) noexcept
	{
		XMVectorSetXPtr(this->mx.r[0], &m11);
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M12 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM12(const float m12) noexcept
	{
		XMVectorSetYPtr(this->mx.r[0], &m12);
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M13 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM13(const float m13) noexcept
	{
		XMVectorSetZPtr(this->mx.r[0], &m13);
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M14 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM14(const float m14) noexcept
	{
		XMVectorSetWPtr(this->mx.r[0], &m14);
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M21 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM21(const float m21) noexcept
	{
		XMVectorSetXPtr(this->mx.r[1], &m21);
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M22 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM22(const float m22) noexcept
	{
		XMVectorSetYPtr(this->mx.r[1], &m22);
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M13 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM23(const float m23) noexcept
	{
		XMVectorSetZPtr(this->mx.r[1], &m23);;
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M14 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM24(const float m24) noexcept
	{
		XMVectorSetWPtr(this->mx.r[1], &m24);;
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M31 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM31(const float m31) noexcept
	{
		XMVectorSetXPtr(this->mx.r[2], &m31);;
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M32 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM32(const float m32) noexcept
	{
		XMVectorSetYPtr(this->mx.r[2], &m32);;
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M33 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM33(const float m33) noexcept
	{
		XMVectorSetZPtr(this->mx.r[2], &m33);;
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M34 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM34(const float m34) noexcept
	{
		XMVectorSetWPtr(this->mx.r[2], &m34);;
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M41 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM41(const float m41) noexcept
	{
		XMVectorSetXPtr(this->mx.r[3], &m41);;
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M42 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM42(const float m42) noexcept
	{
		XMVectorSetYPtr(this->mx.r[3], &m42);;
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M43 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM43(const float m43) noexcept
	{
		XMVectorSetZPtr(this->mx.r[3], &m43);;
	}

	//----------------------------------------------------------------------------------------------------
	/// Set access to M44 element
	XM_INLINE   void XM_CALLCONV Matrix::SetM44(const float m44) noexcept
	{
		XMVectorSetWPtr(this->mx.r[3], &m44);;
	}

	//----------------------------------------------------------------------------------------------------
	// arithmetic operations
	XM_INLINE   Matrix XM_CALLCONV Matrix::operator+ ( const Matrix& Mat ) const noexcept
	{
		Matrix tmp;

		tmp.mx.r[0] = XMVectorAdd( this->mx.r[0], Mat.mx.r[0] );
		tmp.mx.r[1] = XMVectorAdd( this->mx.r[1], Mat.mx.r[1] );
		tmp.mx.r[2] = XMVectorAdd( this->mx.r[2], Mat.mx.r[2] );
		tmp.mx.r[3] = XMVectorAdd( this->mx.r[3], Mat.mx.r[3] );

		return tmp;
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   Matrix XM_CALLCONV Matrix::operator- ( const Matrix& Mat ) const noexcept
	{
		Matrix tmp;

		tmp.mx.r[0] = XMVectorSubtract( this->mx.r[0], Mat.mx.r[0] );
		tmp.mx.r[1] = XMVectorSubtract( this->mx.r[1], Mat.mx.r[1] );
		tmp.mx.r[2] = XMVectorSubtract( this->mx.r[2], Mat.mx.r[2] );
		tmp.mx.r[3] = XMVectorSubtract( this->mx.r[3], Mat.mx.r[3] );

		return tmp;
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   Matrix XM_CALLCONV Matrix::operator* ( const Matrix& Mat ) const noexcept
	{
#if XM_AVX2_INTRINSICS
	 	XMMATRIX mResult;

    		// Use vW to hold the original row
    		XMVECTOR vW = M1.this->GetRow0();
    		// Splat the component X,Y,Z then W
    		XMVECTOR vX = _mm_broadcastss_ps(vW);
    		XMVECTOR vY = _mm_permute_ps(vW,_MM_SHUFFLE(1,1,1,1));
    		XMVECTOR vZ = _mm_permute_ps(vW,_MM_SHUFFLE(2,2,2,2));
    		vW = _mm_permute_ps(vW,_MM_SHUFFLE(3,3,3,3));
    		// Perform the operation on the first row
    		vX = _mm_mul_ps(vX,Mat.GetRow0());
    		vX = _mm_fmadd_ps(vY,Mat.GetRow1(),vX);
    		vX = _mm_fmadd_ps(vZ,Mat.GetRow2(),vX);
    		vX = _mm_fmadd_ps(vW,Mat.GetRow3(),vX);
    		mResult.r[0] = vX;

    		// Repeat for the other 3 rows
    		vW = this->GetRow1();
    		vX = _mm_broadcastss_ps(vW);
    		vY = _mm_permute_ps(vW,_MM_SHUFFLE(1,1,1,1));
    		vZ = _mm_permute_ps(vW,_MM_SHUFFLE(2,2,2,2));
    		vW = _mm_permute_ps(vW,_MM_SHUFFLE(3,3,3,3));
    		vX = _mm_mul_ps(vX,Mat.GetRow0());
    		vX = _mm_fmadd_ps(vY,Mat.GetRow1(),vX);
    		vX = _mm_fmadd_ps(vZ,Mat.GetRow2(),vX);
    		vX = _mm_fmadd_ps(vW,Mat.GetRow3(),vX);
    		mResult.r[1] = vX;

    		vW = this->GetRow2();
    		vX = _mm_broadcastss_ps(vW);
    		vY = _mm_permute_ps(vW,_MM_SHUFFLE(1,1,1,1));
    		vZ = _mm_permute_ps(vW,_MM_SHUFFLE(2,2,2,2));
    		vW = _mm_permute_ps(vW,_MM_SHUFFLE(3,3,3,3));
    		vX = _mm_mul_ps(vX,Mat.GetRow0());
    		vX = _mm_fmadd_ps(vY,Mat.GetRow1(),vX);
    		vX = _mm_fmadd_ps(vZ,Mat.GetRow2(),vX);
    		vX = _mm_fmadd_ps(vW,Mat.GetRow3(),vX);
    		mResult.r[2] = vX;

    		vW = this->GetRow3();
    		vX = _mm_broadcastss_ps(vW);
    		vY = _mm_permute_ps(vW,_MM_SHUFFLE(1,1,1,1));
    		vZ = _mm_permute_ps(vW,_MM_SHUFFLE(2,2,2,2));
    		vW = _mm_permute_ps(vW,_MM_SHUFFLE(3,3,3,3));
    		vX = _mm_mul_ps(vX,Mat.GetRow0());
    		vX = _mm_fmadd_ps(vY,Mat.GetRow1(),vX);
    		vX = _mm_fmadd_ps(vZ,Mat.GetRow2(),vX);
    		vX = _mm_fmadd_ps(vW,Mat.GetRow3(),vX);
    		mResult.r[3] = vX;

   		return Matrix(mResult);
#endif
		return XMMatrixMultiply(this->mx, Mat.mx);
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   Matrix XM_CALLCONV Matrix::operator* ( float fScalar ) const noexcept
	{
		return Scaling(fScalar,fScalar,fScalar);
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   Matrix XM_CALLCONV Matrix::operator/ ( float fScalar ) const noexcept
	{
		const float t = 1.0f / fScalar;

		return Scaling(t,t,t);
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   Matrix XM_CALLCONV Matrix::operator- () const noexcept
	{
		Matrix tmp;

		tmp.mx.r[0] = XMVectorNegate( this->mx.r[0] );
		tmp.mx.r[1] = XMVectorNegate( this->mx.r[1] );
		tmp.mx.r[2] = XMVectorNegate( this->mx.r[2] );
		tmp.mx.r[3] = XMVectorNegate( this->mx.r[3] );

		return tmp;
	}

	//----------------------------------------------------------------------------------------------------
	// arithmetic updates
	XM_INLINE   Matrix& XM_CALLCONV Matrix::operator+= ( const Matrix& Mat ) noexcept
	{
		this->mx.r[0] = XMVectorAdd( this->mx.r[0], Mat.mx.r[0] );
		this->mx.r[1] = XMVectorAdd( this->mx.r[1], Mat.mx.r[1] );
		this->mx.r[2] = XMVectorAdd( this->mx.r[2], Mat.mx.r[2] );
		this->mx.r[3] = XMVectorAdd( this->mx.r[3], Mat.mx.r[3] );

		return *this;
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   Matrix& XM_CALLCONV Matrix::operator-= ( const Matrix& Mat ) noexcept
	{
		this->mx.r[0] = XMVectorSubtract( this->mx.r[0], Mat.mx.r[0] );
		this->mx.r[1] = XMVectorSubtract( this->mx.r[1], Mat.mx.r[1] );
		this->mx.r[2] = XMVectorSubtract( this->mx.r[2], Mat.mx.r[2] );
		this->mx.r[3] = XMVectorSubtract( this->mx.r[3], Mat.mx.r[3] );

		return *this;
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   Matrix& XM_CALLCONV Matrix::operator*= ( const Matrix& Mat ) noexcept
	{
		this->mx = XMMatrixMultiply(this->mx, Mat.mx);

		return *this;
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   Matrix& XM_CALLCONV Matrix::operator*= ( float fScalar ) noexcept
	{
		this->mx = XMMatrixScaling(fScalar,fScalar,fScalar);

		return *this;
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   Matrix& XM_CALLCONV Matrix::operator/= ( float fScalar ) noexcept
	{
		const float t = 1.0f / fScalar;

		this->mx = XMMatrixScaling(t, t, t);

		return *this;
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   const Vector4& XM_CALLCONV Matrix::GetBasisX() const noexcept
	{
		return( this->GetRow0() );
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   const Vector4&  XM_CALLCONV Matrix::GetBasisY() const noexcept
	{
		return( this->GetRow1() );
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   const Vector4&  XM_CALLCONV Matrix::GetBasisZ()const noexcept
	{
		return( this->GetRow2() );
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   const Vector4& XM_CALLCONV Matrix::GetTranslation() const noexcept
	{
		return( this->GetRow3() );
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   void XM_CALLCONV Matrix::SetTranslation( const Vector4& Trans ) noexcept
	{
		const float m44 = this->GetM44();
		this->SetRow3( Trans );
		this->SetM44(m44);
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   const Matrix XM_CALLCONV  Matrix::GetRotation() const noexcept
	{
		Matrix mRet;

		mRet.SetRow0( GetBasisX() );
		mRet.SetRow1( GetBasisY() );
		mRet.SetRow2( GetBasisZ() );

		return( mRet );
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   void XM_CALLCONV Matrix::SetRotation( const Matrix& Rot ) noexcept
	{
		this->SetRow0(Rot.GetBasisX());
		this->SetRow1(Rot.GetBasisY());
		this->SetRow2(Rot.GetBasisZ());
	}

	//----------------------------------------------------------------------------------------------------
	XM_INLINE   Matrix XM_CALLCONV Matrix::MakeWorldMatrix(const Vector3& rotAxis, const float rotAngle, const Vector3& scale, const Vector3& translation) noexcept
	{
		XMVECTOR	axisVec = XMVector3Normalize(XMLoadFloat3(&rotAxis.GetRaw()));
		Matrix		world;

		world.mx = XMMatrixRotationNormal(axisVec, rotAngle);

		world.mx.r[0] = XMVectorScale(world.mx.r[0], scale.GetX() );
		world.mx.r[1] = XMVectorScale(world.mx.r[1], scale.GetY() );
		world.mx.r[2] = XMVectorScale(world.mx.r[2], scale.GetZ() );

		world.mx.r[3] = XMVectorSetW(XMLoadFloat3(&translation.GetRaw()), 1.0f);

		return world;
	}
	
	//------------------------------------------------------------------------------
	XM_INLINE   Matrix XM_CALLCONV Matrix::Reflect( const Plane& p) noexcept
	{
		return XMMatrixReflect(p.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE   void XM_CALLCONV Matrix::Decompose( Vector4& outScale,  Quat& outRotation,  Vector4& outTranslation) const
	{
		const bool result = XMMatrixDecompose(outScale.GetRawPtr(),&outRotation.vec, outTranslation.GetRawPtr(),this->mx);
		assert(result);
		outScale.SetW(0.0f);
		outTranslation.SetW(0.0f);
	}

	//------------------------------------------------------------------------------
	XM_INLINE   Matrix XM_CALLCONV Matrix::AffineTransformation( float scaling,  Vector4 const &rotationCenter,  const Quat& rotation,  Vector4 const &translation) noexcept
	{
		return XMMatrixAffineTransformation(XMVectorReplicate(scaling), rotationCenter, rotation.vec, translation);
	}

	//------------------------------------------------------------------------------
	XM_INLINE   Matrix XM_CALLCONV Matrix::RotationQuaternion(_In_ const Quat& q) noexcept
	{
		return XMMatrixRotationQuaternion(q.vec);
	}

	//------------------------------------------------------------------------------
	XM_INLINE   Matrix XM_CALLCONV Matrix::Transformation( Vector4 const &scalingCenter,  const Quat& scalingRotation,  Vector4 const &scaling,  Vector4 const &rotationCenter,  const Quat& rotation,  Vector4 const &translation) noexcept
	{
		return XMMatrixTransformation(scalingCenter,scalingRotation.vec,scaling,rotationCenter,rotation.vec,translation);
	}


}; // Namespace TurboMath

