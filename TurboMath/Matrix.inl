
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
	__forceinline	Matrix::Matrix():
	mx(XMMatrixIdentity())
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->mx,16));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline	Matrix::Matrix(Vector4 const &row0, Vector4 const &row1, Vector4 const &row2, Vector4 const &row3)
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

	__forceinline Matrix::Matrix( Matrix&& rhs) 
	{
		this->mx.r[0] = rhs.mx.r[0];
		this->mx.r[1] = rhs.mx.r[1];
		this->mx.r[2] = rhs.mx.r[2];
		this->mx.r[3] = rhs.mx.r[3];
	}


	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline	Matrix::Matrix(const XMMATRIX& rhs) :
	mx(rhs)
	{
		// Check 16Byte Alligment
		assert(IsAligned(&this->mx,16));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline	Matrix::Matrix(const Matrix& rhs) :
	mx(rhs)
	{
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::operator=(const Matrix& rhs)
	{
		this->mx = rhs.mx;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::operator=(const XMMATRIX& rhs)
	{
		this->mx = rhs;
	}

	//------------------------------------------------------------------------------
	/**
	*/ 
	/// C++11 Move
	__forceinline Matrix& Matrix::operator=( Matrix&& other)
	{
		this->mx = other.mx;
		return *this;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline bool	Matrix::operator==(const Matrix& rhs) const
	{
		return XMVector4Equal(this->mx.r[0], rhs.mx.r[0]) &&
			XMVector4Equal(this->mx.r[1], rhs.mx.r[1]) &&
			XMVector4Equal(this->mx.r[2], rhs.mx.r[2]) &&
			XMVector4Equal(this->mx.r[3], rhs.mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline bool	Matrix::operator!=(const Matrix& rhs) const
	{
		return XMVector4NotEqual(this->mx.r[0], rhs.mx.r[0]) ||
			XMVector4NotEqual(this->mx.r[1], rhs.mx.r[1]) ||
			XMVector4NotEqual(this->mx.r[2], rhs.mx.r[2]) ||
			XMVector4NotEqual(this->mx.r[3], rhs.mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline const Vector4 Matrix::operator * (const Vector4& v) const
	{
		XMVector3Transform(v, this->mx );

		return v;
	}

	//----------------------------------------------------------------------------------------------------
	__forceinline float Matrix::operator[] ( const int iPos ) const
	{
		assert (iPos < 16);

		const int iRow = iPos / 4;
		const int iCol = iPos % 4;

		assert (iRow < 4);
		assert (iCol < 4);

		return mx.r[iRow].m128_f32[iCol];
	}
	//----------------------------------------------------------------------------------------------------
	__forceinline float& Matrix::operator[] ( const int iPos )
	{
		assert (iPos < 16);

		const int iRow = iPos / 4;
		const int iCol = iPos % 4;

		assert (iRow < 4);
		assert (iCol < 4);

		return mx.r[iRow].m128_f32[iCol];
	}
	//----------------------------------------------------------------------------------------------------
	__forceinline float Matrix::operator() ( const int iRow, const int iCol ) const
	{
		assert (iRow < 4);
		assert (iCol < 4);

		return mx.r[iRow].m128_f32[iCol];
	}
	//----------------------------------------------------------------------------------------------------
	__forceinline float& Matrix::operator() ( const int iRow, const int iCol )
	{
		assert (iRow < 4);
		assert (iCol < 4);

		return mx.r[iRow].m128_f32[iCol];
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::Load(const float* ptr)
	{
		this->mx.r[0] = XMLoadFloat4A((XMFLOAT4A*)ptr);
		this->mx.r[1] = XMLoadFloat4A((XMFLOAT4A*)(ptr + 4));
		this->mx.r[2] = XMLoadFloat4A((XMFLOAT4A*)(ptr + 8));
		this->mx.r[3] = XMLoadFloat4A((XMFLOAT4A*)(ptr + 12));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::LoadU(const float* ptr)
	{
		this->mx.r[0] = XMLoadFloat4((XMFLOAT4*)ptr);
		this->mx.r[1] = XMLoadFloat4((XMFLOAT4*)(ptr + 4));
		this->mx.r[2] = XMLoadFloat4((XMFLOAT4*)(ptr + 8));
		this->mx.r[3] = XMLoadFloat4((XMFLOAT4*)(ptr + 12));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::Store(float* ptr) const
	{
		XMStoreFloat4A((XMFLOAT4A*)ptr, this->mx.r[0]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 4), this->mx.r[1]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 8), this->mx.r[2]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 12), this->mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::StoreU(float* ptr) const
	{
		XMStoreFloat4((XMFLOAT4*)ptr, this->mx.r[0]);
		XMStoreFloat4((XMFLOAT4*)(ptr + 4), this->mx.r[1]);
		XMStoreFloat4((XMFLOAT4*)(ptr + 8), this->mx.r[2]);
		XMStoreFloat4((XMFLOAT4*)(ptr + 12), this->mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::Stream(float* ptr) const
	{
		XMStoreFloat4A((XMFLOAT4A*)ptr, this->mx.r[0]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 4), this->mx.r[1]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 8), this->mx.r[2]);
		XMStoreFloat4A((XMFLOAT4A*)(ptr + 12), this->mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::Set(Vector4 const &row0, Vector4 const &row1, Vector4 const &row2, Vector4 const &row3)
	{
		this->mx.r[0] = row0;
		this->mx.r[1] = row1;
		this->mx.r[2] = row2;
		this->mx.r[3] = row3;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::SetRow0(Vector4 const &r)
	{
		this->mx.r[0] = r;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline const Vector4&	Matrix::GetRow0() const
	{
		return *(Vector4*)&(this->mx.r[0]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::SetRow1(Vector4 const &r)
	{
		this->mx.r[1] = r;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline const Vector4&	Matrix::GetRow1() const
	{
		return *(Vector4*)&(this->mx.r[1]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::SetRow2(Vector4 const &r)
	{
		this->mx.r[2] = r;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline const Vector4&	Matrix::GetRow2() const
	{
		return *(Vector4*)&(this->mx.r[2]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::SetRow3(Vector4 const &r)
	{
		this->mx.r[3] = r;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline const Vector4&	Matrix::GetRow3() const
	{
		return *(Vector4*)&(this->mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::Set_X_Axis(Vector4 const &x)
	{
		this->mx.r[0] = x;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::Set_Y_Axis(Vector4 const &y)
	{
		this->mx.r[1] = y;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::Set_Z_Axis(Vector4 const &z)
	{
		this->mx.r[2] = z;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::Set_Position(Vector4 const &pos)
	{
		this->mx.r[3] = pos;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline const Vector4&	Matrix::Get_X_Axis() const
	{
		return *(Vector4*)&(this->mx.r[0]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline const Vector4&	Matrix::Get_Y_Axis() const
	{
		return *(Vector4*)&(this->mx.r[1]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline const Vector4&	Matrix::Get_Z_Axis() const
	{
		return *(Vector4*)&(this->mx.r[2]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline const Vector4&	Matrix::Get_Position() const
	{
		return *(Vector4*)&(this->mx.r[3]);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline	void 	Matrix::Translate(Vector4 const &t)
	{
		assert(t.GetW() == 0 && "w component not 0, use vector for translation not a point!");

		this->mx.r[3] += t;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline void	Matrix::Scale(Vector4 const &s)
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
	__forceinline bool	Matrix::IsIdentity() const
	{
		return (0 != XMMatrixIsIdentity(this->mx));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline float	Matrix::Determinant() const
	{
		return Vector4::Unpack_X(XMMatrixDeterminant(this->mx));
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::Identity()
	{
		return XMMatrixIdentity();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::MakeZero()
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
	__forceinline Matrix	Matrix::Inverse(const Matrix& m)
	{
		XMVECTOR det;
		return XMMatrixInverse(&det, m.mx);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::LookAtLH(Vector4 const &eye, Vector4 const &at, Vector4 const &up)
	{
		return XMMatrixLookAtLH(eye,at,up);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::LookAtRH(Vector4 const &eye, Vector4 const &at, Vector4 const &up)
	{
		return XMMatrixLookAtRH(eye,at,up);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::LookToLH(Vector4 const &eye, Vector4 const &at, Vector4 const &up)
	{
		return XMMatrixLookToLH(eye,at,up);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::LookToRH(Vector4 const &eye, Vector4 const &at, Vector4 const &up)
	{
		return XMMatrixLookToRH(eye,at,up);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::Multiply(const Matrix& m0, const Matrix& m1)
	{
		return XMMatrixMultiply(m0.mx, m1.mx);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::OrthoLH(float w, float h, float zn, float zf)
	{
		return XMMatrixOrthographicLH(w, h, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::OrthoRH(float w, float h, float zn, float zf)
	{
		return XMMatrixOrthographicRH(w, h, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::OrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf)
	{
		return XMMatrixOrthographicOffCenterLH(l, r, b, t, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::OrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf)
	{
		return XMMatrixOrthographicOffCenterRH(l, r, b, t, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::PerspectiveProjectionFovLH(float fovy, float aspect, float zn, float zf)
	{
		return XMMatrixPerspectiveFovLH(fovy, aspect, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::PerspectiveProjectionFovRH(float fovy, float aspect, float zn, float zf)
	{
		return XMMatrixPerspectiveFovRH(fovy, aspect, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::PerspectiveProjectionLH(float w, float h, float zn, float zf)
	{
		return XMMatrixPerspectiveLH(w, h, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::PerspectiveProjectionRH(float w, float h, float zn, float zf)
	{
		return XMMatrixPerspectiveRH(w, h, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::PerspOffCenterLH(float l, float r, float b, float t, float zn, float zf)
	{
		return XMMatrixPerspectiveOffCenterLH(l, r, b, t, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::PerspOffCenterRH(float l, float r, float b, float t, float zn, float zf)
	{
		return XMMatrixPerspectiveOffCenterRH(l, r, b, t, zn, zf);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::RotationAxis(Vector4 const &axis, float angle)
	{
		return XMMatrixRotationAxis(axis, angle);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::RotationX(float angle)
	{
		return XMMatrixRotationX(angle);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::RotationY(float angle)
	{
		return XMMatrixRotationY(angle);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::RotationZ(float angle)
	{
		return XMMatrixRotationZ(angle);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::RotationYawPitchRoll(float yaw, float pitch, float roll)
	{
		return XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	}
	//------------------------------------------------------------------------------
	/**
	*/

	__forceinline void	Matrix::Rotation( const Vector3& rot )
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
	__forceinline Matrix	Matrix::Scaling(float sx, float sy, float sz)
	{
		return XMMatrixScaling(sx, sy, sz);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::Scaling(float s)
	{
		return XMMatrixScaling(s, s, s);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::Scaling(Vector4 const &s)
	{
		return XMMatrixScalingFromVector(s);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::Translation(float x, float y, float z)
	{
		return XMMatrixTranslation(x, y, z);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::Translation(Vector4 const &t)
	{
		return XMMatrixTranslationFromVector(t);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Matrix	Matrix::Transpose(const Matrix& m)
	{
		return XMMatrixTranspose(m.mx);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline	Vector4	Matrix::Transform(const Vector4 &v, const Matrix &m)
	{
		return XMVector4Transform(v, m.mx);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline Quat	Matrix::RotationMatrix(const Matrix& m)
	{
		return XMQuaternionRotationMatrix(m.mx);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	__forceinline	Plane	Matrix::Transform(const Plane &p, const Matrix& m)
	{
		return Plane(XMPlaneTransform(p.vec, m.mx));
	}

	/// Get access to M11 element
	__forceinline	const float		Matrix::GetM11() const
	{
		return mx.r[0].m128_f32[0];
	}
	/// Get access to M12 element
	__forceinline	const float		Matrix::GetM12() const
	{
		return mx.r[0].m128_f32[1];
	}
	/// Get access to M13 element
	__forceinline	const float		Matrix::GetM13() const
	{
		return mx.r[0].m128_f32[2];
	}
	/// Get access to M14 element
	__forceinline	const float		Matrix::GetM14() const
	{
		return mx.r[0].m128_f32[3];
	}
	/// Get access to M21 element
	__forceinline	const float		Matrix::GetM21() const
	{
		return mx.r[1].m128_f32[0];
	}
	/// Get access to M22 element
	__forceinline	const float		Matrix::GetM22() const
	{
		return mx.r[1].m128_f32[1];
	}
	/// Get access to M13 element
	__forceinline	const float		Matrix::GetM23() const
	{
		return mx.r[1].m128_f32[2];
	}
	/// Get access to M14 element
	__forceinline	const float		Matrix::GetM24() const
	{
		return mx.r[1].m128_f32[3];
	}
	/// Get access to M31 element
	__forceinline	const float		Matrix::GetM31() const
	{
		return mx.r[2].m128_f32[0];
	}
	/// Get access to M32 element
	__forceinline	const float		Matrix::GetM32() const
	{
		return mx.r[2].m128_f32[1];
	}
	/// Get access to M33 element
	__forceinline	const float		Matrix::GetM33() const
	{
		return mx.r[2].m128_f32[2];
	}
	/// Get access to M34 element
	__forceinline	const float		Matrix::GetM34() const
	{
		return mx.r[2].m128_f32[3];
	}
	/// Get access to M41 element
	__forceinline	const float		Matrix::GetM41() const
	{
		return mx.r[3].m128_f32[0];
	}
	/// Get access to M42 element
	__forceinline	const float		Matrix::GetM42() const
	{
		return mx.r[3].m128_f32[1];
	}
	/// Get access to M43 element
	__forceinline	const float		Matrix::GetM43() const
	{
		return mx.r[3].m128_f32[2];
	}
	/// Get access to M44 element
	__forceinline	const float		Matrix::GetM44() const
	{
		return mx.r[3].m128_f32[3];
	}

	/// Set access to M11 element
	__forceinline	void	Matrix::SetM11(const float m11)
	{
		XMVectorSetXPtr(this->mx.r[0], &m11);
	}
	/// Set access to M12 element
	__forceinline	void	Matrix::SetM12(const float m12)
	{
		XMVectorSetYPtr(this->mx.r[0], &m12);
	}
	/// Set access to M13 element
	__forceinline	void	Matrix::SetM13(const float m13)
	{
		XMVectorSetZPtr(this->mx.r[0], &m13);
	}
	/// Set access to M14 element
	__forceinline	void	Matrix::SetM14(const float m14)
	{
		XMVectorSetWPtr(this->mx.r[0], &m14);
	}
	/// Set access to M21 element
	__forceinline	void	Matrix::SetM21(const float m21)
	{
		XMVectorSetXPtr(this->mx.r[1], &m21);
	}
	/// Set access to M22 element
	__forceinline	void	Matrix::SetM22(const float m22)
	{
		XMVectorSetYPtr(this->mx.r[1], &m22);
	}
	/// Set access to M13 element
	__forceinline	void	Matrix::SetM23(const float m23)
	{
		XMVectorSetZPtr(this->mx.r[1], &m23);;
	}
	/// Set access to M14 element
	__forceinline	void	Matrix::SetM24(const float m24)
	{
		XMVectorSetWPtr(this->mx.r[1], &m24);;
	}
	/// Set access to M31 element
	__forceinline	void	Matrix::SetM31(const float m31)
	{
		XMVectorSetXPtr(this->mx.r[2], &m31);;
	}
	/// Set access to M32 element
	__forceinline	void	Matrix::SetM32(const float m32)
	{
		XMVectorSetYPtr(this->mx.r[2], &m32);;
	}
	/// Set access to M33 element
	__forceinline	void	Matrix::SetM33(const float m33)
	{
		XMVectorSetZPtr(this->mx.r[2], &m33);;
	}
	/// Set access to M34 element
	__forceinline	void	Matrix::SetM34(const float m34)
	{
		XMVectorSetWPtr(this->mx.r[2], &m34);;
	}
	/// Set access to M41 element
	__forceinline	void	Matrix::SetM41(const float m41)
	{
		XMVectorSetXPtr(this->mx.r[3], &m41);;
	}
	/// Set access to M42 element
	__forceinline	void	Matrix::SetM42(const float m42)
	{
		XMVectorSetYPtr(this->mx.r[3], &m42);;
	}
	/// Set access to M43 element
	__forceinline	void	Matrix::SetM43(const float m43)
	{
		XMVectorSetZPtr(this->mx.r[3], &m43);;
	}
	/// Set access to M44 element
	__forceinline	void	Matrix::SetM44(const float m44)
	{
		XMVectorSetWPtr(this->mx.r[3], &m44);;
	}

	// arithmetic operations
	__forceinline	Matrix Matrix::operator+ ( const Matrix& Mat ) const
	{
		Matrix tmp;

		tmp.mx.r[0] = XMVectorAdd( this->mx.r[0], Mat.mx.r[0] );
		tmp.mx.r[1] = XMVectorAdd( this->mx.r[1], Mat.mx.r[1] );
		tmp.mx.r[2] = XMVectorAdd( this->mx.r[2], Mat.mx.r[2] );
		tmp.mx.r[3] = XMVectorAdd( this->mx.r[3], Mat.mx.r[3] );

		return tmp;
	}

	__forceinline	Matrix Matrix::operator- ( const Matrix& Mat ) const
	{
		Matrix tmp;

		tmp.mx.r[0] = XMVectorSubtract( this->mx.r[0], Mat.mx.r[0] );
		tmp.mx.r[1] = XMVectorSubtract( this->mx.r[1], Mat.mx.r[1] );
		tmp.mx.r[2] = XMVectorSubtract( this->mx.r[2], Mat.mx.r[2] );
		tmp.mx.r[3] = XMVectorSubtract( this->mx.r[3], Mat.mx.r[3] );

		return tmp;
	}

	__forceinline	Matrix Matrix::operator* ( const Matrix& Mat ) const
	{
		return XMMatrixMultiply(this->mx, Mat.mx);
	}

	__forceinline	Matrix Matrix::operator* ( float fScalar ) const
	{
		return Scaling(fScalar,fScalar,fScalar);
	}

	__forceinline	Matrix Matrix::operator/ ( float fScalar ) const
	{
		const float t = 1.0f / fScalar;

		return Scaling(t,t,t);
	}

	__forceinline	Matrix Matrix::operator- () const
	{
		Matrix tmp;

		tmp.mx.r[0] = XMVectorNegate( this->mx.r[0] );
		tmp.mx.r[1] = XMVectorNegate( this->mx.r[1] );
		tmp.mx.r[2] = XMVectorNegate( this->mx.r[2] );
		tmp.mx.r[3] = XMVectorNegate( this->mx.r[3] );

		return tmp;
	}

	// arithmetic updates
	__forceinline	Matrix& Matrix::operator+= ( const Matrix& Mat )
	{
		this->mx.r[0] = XMVectorAdd( this->mx.r[0], Mat.mx.r[0] );
		this->mx.r[1] = XMVectorAdd( this->mx.r[1], Mat.mx.r[1] );
		this->mx.r[2] = XMVectorAdd( this->mx.r[2], Mat.mx.r[2] );
		this->mx.r[3] = XMVectorAdd( this->mx.r[3], Mat.mx.r[3] );

		return *this;
	}

	__forceinline	Matrix& Matrix::operator-= ( const Matrix& Mat )
	{
		this->mx.r[0] = XMVectorSubtract( this->mx.r[0], Mat.mx.r[0] );
		this->mx.r[1] = XMVectorSubtract( this->mx.r[1], Mat.mx.r[1] );
		this->mx.r[2] = XMVectorSubtract( this->mx.r[2], Mat.mx.r[2] );
		this->mx.r[3] = XMVectorSubtract( this->mx.r[3], Mat.mx.r[3] );

		return *this;
	}
	__forceinline	Matrix& Matrix::operator*= ( const Matrix& Mat )
	{
		this->mx = XMMatrixMultiply(this->mx, Mat.mx);

		return *this;
	}

	__forceinline	Matrix& Matrix::operator*= ( float fScalar )
	{
		this->mx = XMMatrixScaling(fScalar,fScalar,fScalar);

		return *this;
	}

	__forceinline	Matrix& Matrix::operator/= ( float fScalar )
	{
		const float t = 1.0f / fScalar;

		this->mx = XMMatrixScaling(t, t, t);

		return *this;
	}

	__forceinline	const Vector4& Matrix::GetBasisX() const
	{
		return( this->GetRow0() );
	}
	//----------------------------------------------------------------------------------------------------
	__forceinline	const Vector4&  Matrix::GetBasisY() const
	{
		return( this->GetRow1() );
	}
	//----------------------------------------------------------------------------------------------------
	__forceinline	const Vector4&  Matrix::GetBasisZ()const
	{
		return( this->GetRow2() );
	}

	//----------------------------------------------------------------------------------------------------
	__forceinline	const Vector4& Matrix::GetTranslation() const
	{
		return( this->GetRow3() );
	}
	//----------------------------------------------------------------------------------------------------
	__forceinline	void Matrix::SetTranslation( const Vector4& Trans )
	{
		const float m44 = this->GetM44();
		this->SetRow3( Trans );
		this->SetM44(m44);
	}
	//----------------------------------------------------------------------------------------------------
	__forceinline	const Matrix Matrix::GetRotation() const
	{
		Matrix mRet;

		mRet.SetRow0( GetBasisX() );
		mRet.SetRow1( GetBasisY() );
		mRet.SetRow2( GetBasisZ() );

		return( mRet );
	}
	//----------------------------------------------------------------------------------------------------
	__forceinline	void Matrix::SetRotation( const Matrix& Rot )
	{
		this->SetRow0(Rot.GetBasisX());
		this->SetRow1(Rot.GetBasisY());
		this->SetRow2(Rot.GetBasisZ());
	}

	//----------------------------------------------------------------------------------------------------
	__forceinline Matrix Matrix::MakeWorldMatrix(const Vector3& rotAxis, const float rotAngle, const Vector3& scale, const Vector3& translation)
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
	__forceinline Matrix	Matrix::Reflect( const Plane& p)
	{
		return XMMatrixReflect(p.vec);
	}

	//------------------------------------------------------------------------------
	__forceinline void Matrix::Decompose( Vector4& outScale,  Quat& outRotation,  Vector4& outTranslation) const
	{
		const bool result = XMMatrixDecompose(outScale.GetRawPtr(),&outRotation.vec, outTranslation.GetRawPtr(),this->mx);
		assert(result);
		outScale.SetW(0.0f);
		outTranslation.SetW(0.0f);
	}

	//------------------------------------------------------------------------------
	__forceinline Matrix Matrix::AffineTransformation( float scaling,  Vector4 const &rotationCenter,  const Quat& rotation,  Vector4 const &translation)
	{
		return XMMatrixAffineTransformation(XMVectorReplicate(scaling), rotationCenter, rotation.vec, translation);
	}

	//------------------------------------------------------------------------------
	__forceinline Matrix Matrix::RotationQuaternion(_In_ const Quat& q)
	{
		return XMMatrixRotationQuaternion(q.vec);
	}

	//------------------------------------------------------------------------------
	__forceinline Matrix Matrix::Transformation( Vector4 const &scalingCenter,  const Quat& scalingRotation,  Vector4 const &scaling,  Vector4 const &rotationCenter,  const Quat& rotation,  Vector4 const &translation)
	{
		return XMMatrixTransformation(scalingCenter,scalingRotation.vec,scaling,rotationCenter,rotation.vec,translation);
	}


}; // Namespace TurboMath

