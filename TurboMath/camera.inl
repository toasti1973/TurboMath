
// -------------------------------------------------------------------
// File			:	Camera.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for a Camera-Class
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


#ifdef _MSC_VER
#pragma once
#endif


namespace TurboMath
{

	
	XM_INLINE Camera::Camera(void)
	{
		m_Position		= Vector4(0.0f, 0.0f, -1.0f);
		m_Target			= Vector4(0.0f, 0.0f, 0.0f);
		m_Up				= m_Position + Vector4(0, 1, 0);

		this->initViewMatrix();

		m_Angle			= 0.0f;
		m_ClientWidth	= 0.0f;
		m_ClientHeight	= 0.0f;
		m_Nearest		= 0.0f;
		m_Farthest		= 0.0f;

		m_View = Matrix::Identity();
		m_Proj = Matrix::Identity();
		m_Ortho = Matrix::Identity();
	}

	XM_INLINE Camera::Camera(const Camera& camera)
	{
		*this = camera;
	}

	XM_INLINE Camera& Camera::operator=(const Camera& camera)
	{
		m_Position		= camera.m_Position;
		m_Target		= camera.m_Target;
		m_Up			= camera.m_Up;

		m_Angle			= camera.m_Angle;
		m_ClientWidth	= camera.m_ClientWidth;
		m_ClientHeight	= camera.m_ClientHeight;
		m_Nearest		= camera.m_Nearest;
		m_Farthest		= camera.m_Farthest;

		m_View			= camera.m_View;
		m_Proj			= camera.m_Proj;
		m_Ortho			= camera.m_Ortho;

		return *this;
	}

	XM_INLINE void XM_CALLCONV Camera::initViewMatrix() noexcept
	{
		m_View = Matrix::LookAtLH(m_Position,m_Target,m_Up);
	}

	XM_INLINE void XM_CALLCONV Camera::InitProjMatrix(const float angle, const float client_width, const float client_height, const float near_plane, const float far_plane) noexcept
	{
		m_Angle = angle;
		m_ClientWidth = client_width;
		m_ClientHeight = client_height;
		m_Nearest = near_plane;
		m_Farthest = far_plane;

		m_Proj = Matrix::PerspectiveProjectionFovLH(angle, client_width/client_height, near_plane, far_plane);

		// Update View-Frustum
		m_ViewFrustum.ComputeFrustumFromProjection(m_Proj);
		m_ViewFrustum.SetOrigin(m_Position);
	}

	XM_INLINE void XM_CALLCONV  Camera::Move(const Vector4& direction) noexcept
	{
		m_Position = Vector4::Transform(m_Position, Matrix::Translation(direction.GetX(), direction.GetY(), direction.GetZ()));
		m_Target = Vector4::Transform(m_Target, Matrix::Translation(direction.GetX(), direction.GetY(), direction.GetZ()));
		m_Up = Vector4::Transform(m_Up, Matrix::Translation(direction.GetX(), direction.GetY(), direction.GetZ()));

		this->initViewMatrix();

		m_ViewFrustum.SetOrigin(m_Position);
	}

	/// Strafe	
	XM_INLINE void XM_CALLCONV Camera::Strafe(const float distance) noexcept
	{
		const Vector4 vRight = Vector4::Cross(m_Up, m_Target);

		m_Position += Vector4(distance * vRight);

		this->initViewMatrix();

		m_ViewFrustum.SetOrigin(m_Position);
	}

	/// Walk
	XM_INLINE void XM_CALLCONV Camera::Walk(const float distance) noexcept
	{
		m_Position = Vector4(distance * m_Target);

		this->initViewMatrix();

		m_ViewFrustum.SetOrigin(m_Position);
	}

	/// RotateX
	XM_INLINE void XM_CALLCONV Camera::RotateX(const float angle) noexcept
	{
		const Matrix R = Matrix::RotationX(angle);
		
		Vector4 vRight = Vector4::Cross(m_Up, m_Target);
		vRight = Vector4::Transform(vRight, R);

        m_Up = Vector4::Transform(m_Up, R);
        m_Target = Vector4::Transform(m_Target, R);

		// Update Matrix
		this->initViewMatrix();

		// Update View-Frustum
		m_ViewFrustum.Rotate(Quat::RotationMatrix(R));
 	}

	/// RotateY
	XM_INLINE void XM_CALLCONV Camera::RotateY(const float angle) noexcept
	{
		const Matrix R = Matrix::RotationY(angle);
		
		Vector4 vRight = Vector4::Cross(m_Up, m_Target);
		vRight = Vector4::Transform(vRight, R);

        m_Up = Vector4::Transform(m_Up, R);
        m_Target = Vector4::Transform(m_Target, R);

		// Update Matrix
		this->initViewMatrix();

		// Update View-Frustum
		m_ViewFrustum.Rotate(Quat::RotationMatrix(R));
 	}

	/// RotateZ
	XM_INLINE void XM_CALLCONV Camera::RotateZ(const float angle) noexcept
	{
		const Matrix R = Matrix::RotationZ(angle);
		
		Vector4 vRight = Vector4::Cross(m_Up, m_Target);
		vRight = Vector4::Transform(vRight, R);

        m_Up = Vector4::Transform(m_Up, R);
        m_Target = Vector4::Transform(m_Target, R);

		// Update Matrix
		this->initViewMatrix();	

		// Update View-Frustum
		m_ViewFrustum.Rotate(Quat::RotationMatrix(R));
 	}

	/// Pitch
	XM_INLINE void XM_CALLCONV Camera::Pitch(const float angle) noexcept
	{
		// Rotate up and look vector about the right vector.
		Vector4 vRight = Vector4::Cross(m_Up, m_Target);

        const Matrix rotation = Matrix::RotationAxis(vRight, angle);
 
		m_Up = Vector4::Transform(m_Up, rotation);
        m_Target =Vector4::Transform(m_Target, rotation);
 
		// Update Matrix
		this->initViewMatrix();

		// Update View-Frustum
		m_ViewFrustum.Rotate(Quat::RotationMatrix(rotation));
		m_ViewFrustum.SetOrigin(m_Position);
	}

	/// YAW
	XM_INLINE void XM_CALLCONV Camera::Yaw(const float angle) noexcept
	{
		// Rotate the basis vectors about the world y-axis.
        const Matrix rotation = Matrix::RotationY(angle);
 
        m_Up = Vector4::Transform(m_Up, rotation);
        m_Target = Vector4::Transform(m_Target, rotation); 

		// Update Matrix
		this->initViewMatrix();

		// Update View-Frustum
		m_ViewFrustum.Rotate(Quat::RotationMatrix(rotation));
		m_ViewFrustum.SetOrigin(m_Position);
	}

	XM_INLINE void XM_CALLCONV Camera::Rotate(const Vector4& axis, float degrees) noexcept
	{
		if (axis == Vector4::ZERO() ||	degrees == 0.0f)	return;

		// rotate vectors
		Vector4 look_at_target = m_Target - m_Position;
		Vector4 look_at_up = m_Up - m_Position;

		look_at_target = Vector4::Transform(look_at_target, Matrix::RotationAxis(axis, XMConvertToRadians(degrees)));
		look_at_up = Vector4::Transform(look_at_up, Matrix::RotationAxis(axis, XMConvertToRadians(degrees)));

		// restore vectors's end points mTarget and mUp from new rotated vectors
		m_Target = m_Position + look_at_target;
		m_Up = m_Position + look_at_up;

		// Update Matrix
		this->initViewMatrix();	

		// Update View-Frustum
		m_ViewFrustum.Rotate(Quat::RotationAxis(axis,degrees));
	}

	XM_INLINE void XM_CALLCONV Camera::SetTarget(const Vector4& new_target) noexcept
	{
		if ((new_target == m_Position) ||	(new_target == m_Target))	return;

		const Vector4 old_look_at_target = m_Target - m_Position;	
		const Vector4 new_look_at_target = new_target - m_Position;

		const float angle = XMConvertToDegrees( Vector4::Angle( Vector4::Normalize(old_look_at_target), Vector4::Normalize(new_look_at_target)) );

		if (angle != 0.0f && angle != 360.0f && angle != 180.0f)
		{
			const Vector4 axis = Vector4::Cross(old_look_at_target, new_look_at_target);
			Rotate(axis, angle);
		}

		m_Target = new_target;

		this->initViewMatrix();
	}

	// Set camera position
	XM_INLINE void XM_CALLCONV Camera::SetPosition(const Vector4& new_position) noexcept
	{
		const Vector4 move_vector = new_position - m_Position;
		const Vector4 target = m_Target;

		this->Move(move_vector);
		this->SetTarget(target);

		this->initViewMatrix();

		// Update View-Frustum
		m_ViewFrustum.SetOrigin(m_Position);
	}

	XM_INLINE void XM_CALLCONV Camera::SetViewAngle(float angle) noexcept
	{
		m_Angle = angle;

		InitProjMatrix(m_Angle, m_ClientWidth, m_ClientHeight, m_Nearest, m_Farthest);
	}

	XM_INLINE void XM_CALLCONV Camera::SetNearestPlane(float nearest) noexcept
	{
		m_Nearest = nearest;

		OnResize( Vector2(m_ClientWidth, m_ClientHeight) );
	}

	XM_INLINE void XM_CALLCONV Camera::SetFarthestPlane(float farthest) noexcept
	{
		m_Farthest = farthest;

		OnResize( Vector2(m_ClientWidth, m_ClientHeight) );
	}

	XM_INLINE void XM_CALLCONV Camera::InitOrthoMatrix(const float clientWidth, const float clientHeight,	const float nearZ, const float fartherZ) noexcept
	{
		m_Ortho = Matrix::OrthoLH(clientWidth, clientHeight, 0.0f, fartherZ);
	}

	XM_INLINE void XM_CALLCONV Camera::OnResize(const Vector2& newsize) noexcept
	{
		m_ClientWidth = newsize.GetX();
		m_ClientHeight = newsize.GetY();

		InitProjMatrix(m_Angle, static_cast<float>(m_ClientWidth), static_cast<float>(m_ClientHeight), m_Nearest, m_Farthest);
		InitOrthoMatrix(static_cast<float>(m_ClientWidth), static_cast<float>(m_ClientHeight), 0.0f, m_Farthest);
	}

	// Returns transposed camera's Projection matrix
	XM_INLINE const Matrix& XM_CALLCONV Camera::GetProjMatrix() const noexcept
	{ 
		return Matrix::Transpose(m_Proj);
	}
	
	// Returns transposed orthogonal camera matrix
	XM_INLINE const Matrix& XM_CALLCONV Camera::GetOrthoMatrix()const noexcept
	{ 
		return Matrix::Transpose(m_Ortho); 
	}
	
	// Get view frustum's angle
	XM_INLINE const float& XM_CALLCONV Camera::GetAngle() const noexcept
	{ 
		return m_Angle;
	}

	// Get camera's target position coordinates
	XM_INLINE const Vector4& XM_CALLCONV Camera::GetTarget() const noexcept
	{
		return m_Target;
	}
	
	// Get camera's up vector
	XM_INLINE const Vector4& XM_CALLCONV Camera::GetUp() const noexcept
	{ 
		return m_Up- m_Position;
	}
	
	// Get camera's look at target vector
	XM_INLINE const Vector4& XM_CALLCONV Camera::GetLookAtTargetVector()  const noexcept
	{ 
		return m_Target - m_Position; 
	}	
	
	// Returns transposed camera's View matrix	
	XM_INLINE const Matrix& XM_CALLCONV Camera::GetViewMatrix() const noexcept
	{
		return Matrix::Transpose(m_View); 
	}

	// Get camera position coordinates
	XM_INLINE const Vector4& XM_CALLCONV Camera::GetPosition() const noexcept
	{ 
		return m_Position; 
	}

	// Get NearPlane (as Float)
	XM_INLINE const float& XM_CALLCONV Camera::GetNearClip() const noexcept
	{
		return m_Nearest;
	}

	// Get FarPlane as FLoat
	XM_INLINE const float& XM_CALLCONV Camera::GetFarClip() const noexcept
	{
		return m_Farthest;
	}

	// Returns the ReProjectionMatrix
	XM_INLINE const Matrix& XM_CALLCONV Camera::GetReprojectionMatrix() const noexcept
	{ 
		return m_ReprojectMatrix; 
	}

	XM_INLINE void XM_CALLCONV Camera::SetLookDirection(Vector4 forward, Vector4 up) noexcept
	{
//		SetLookDirection(forward, up);
	}

	XM_INLINE void XM_CALLCONV Camera::Update() noexcept
	{
		m_PreviousViewProjMatrix = m_ViewProj;

//		m_View. = Matrix(~m_CameraToWorld);
//		m_ViewProj = m_Proj * m_View;
//		m_ReprojectMatrix = m_PreviousViewProjMatrix * Invert(GetViewProjMatrix());

		m_ViewFrustum.ComputeFrustumFromProjection(m_Proj);

	}

	XM_INLINE void XM_CALLCONV Camera::SetEyeAtUp(Vector4 eye, Vector4 at, Vector4 up) noexcept
	{
		SetLookDirection(at - eye, up);
		SetPosition(eye);
	}

	XM_INLINE void XM_CALLCONV Camera::SetRotation(Quat basisRotation) noexcept
	{
//		m_CameraToWorld.SetRotation(Normalize(basisRotation));
//		m_Basis = Matrix3(m_CameraToWorld.GetRotation());
	}


}// end of Namespace TurboMath