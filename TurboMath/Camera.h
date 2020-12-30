
// -------------------------------------------------------------------
// File			:	Camera
//
// Project		:	TurboMath
//
// Description	:	Class for a Camera
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


#ifndef _TURBOMATH_CAMERA_H_
#define _TURBOMATH_CAMERA_H_

namespace TurboMath
{


	CACHE_ALIGN(16) class Camera
	{
	public:
		// Constructs default camera looking at 0,0,0
		// placed at 0,0,-1 with up vector 0,1,0 (note that mUp is NOT a vector - it's vector's end)
		Camera(void) noexcept;
	
		// Create camera, based on another one
		Camera(const Camera& camera) noexcept;
	
		// Copy all camera's parameters
		Camera& operator=(const Camera& camera)noexcept;
    
		// Initialize camera's perspective Projection matrix
		void XM_CALLCONV InitProjMatrix(const float angle, const float client_width, const float client_height, const float nearest, const float farthest) noexcept;
		
		// Initialize camera's orthogonal projection
		void XM_CALLCONV InitOrthoMatrix(const float client_width, const float client_height, const float near_plane, const float far_plane) noexcept;

		// Resize matrices when window size changes
		void XM_CALLCONV OnResize(const Vector2& newsize) noexcept;

		///////////////////////////////////////////////
		/*** View matrix transformation interfaces ***/
		///////////////////////////////////////////////

		/// Move camera
		void XM_CALLCONV Move(const Vector4& direction) noexcept;

		/// Strafe	
		void XM_CALLCONV Strafe(const float distance) noexcept;

		/// Walk
		void XM_CALLCONV Walk(const float distance) noexcept;

		/// RotateX
		void XM_CALLCONV RotateX(const float angle) noexcept;

		/// RotateY
		void XM_CALLCONV RotateY(const float angle) noexcept;

		/// RotateZ
		void XM_CALLCONV RotateZ(const float angle) noexcept;

		/// Pitch
		void XM_CALLCONV Pitch(const float angle) noexcept;

		/// Yaw
		void XM_CALLCONV Yaw(const float angle) noexcept;
	
		/// Rotate camera around `axis` by `degrees`. Camera's position is a 
		/// pivot point of rotation, so it doesn't change
		void XM_CALLCONV Rotate(const Vector4& axis, float degrees) noexcept;
		void XM_CALLCONV SetRotation(Quat basisRotation) noexcept;
	
		/// Set camera position coordinates
		void XM_CALLCONV SetPosition(const Vector4& new_position) noexcept;
	
		/// Get camera position coordinates
		const Vector4& XM_CALLCONV GetPosition() const noexcept;
	
		/// Change camera target position
		void XM_CALLCONV SetTarget(const Vector4& new_target) noexcept;

		/// Get camera's target position coordinates
		const Vector4& XM_CALLCONV GetTarget() const  noexcept;
	
		/// Get camera's up vector
		const Vector4& XM_CALLCONV GetUp() const noexcept;
	
		/// Get camera's look at target vector
		const Vector4& XM_CALLCONV GetLookAtTargetVector() const noexcept;
	
		/// Returns transposed camera's View matrix	
		const Matrix& XM_CALLCONV GetViewMatrix() const noexcept;

		/// Returns the ReProjectionMatrix
		const Matrix& XM_CALLCONV GetReprojectionMatrix() const noexcept;

		/// Set EyeUp Vector
		void XM_CALLCONV SetEyeAtUp(Vector4 eye, Vector4 at, Vector4 up) noexcept;

		/// Set Look Direction 
		void XM_CALLCONV SetLookDirection(Vector4 forward, Vector4 up) noexcept;
		
		// Call this function once per frame and after you've changed any state.  This
		// regenerates all matrices.  Calling it more or less than once per frame will break
		// temporal effects and cause unpredictable results.
		void XM_CALLCONV Update() noexcept;

		/////////////////////////////////////////////////////
		/*** Projection matrix transformation interfaces ***/
		/////////////////////////////////////////////////////

		/// Set view frustum's angle
		void XM_CALLCONV SetViewAngle(float angle) noexcept;
	
		/// Get view frustum's angle
		const float& XM_CALLCONV GetAngle() const noexcept;

		/// Set nearest culling plane distance from view frustum's projection plane
		void XM_CALLCONV SetNearestPlane(float nearest) noexcept;

		/// Set farthest culling plane distance from view frustum's projection plane
		void XM_CALLCONV SetFarthestPlane(float farthest) noexcept;

		/// Returns transposed camera's Projection matrix
		const Matrix& XM_CALLCONV GetProjMatrix() const noexcept;
	
		/// Returns transposed orthogonal camera matrix
		const Matrix& XM_CALLCONV GetOrthoMatrix() const noexcept;

		// Get NearPlane (as Float)
		const float& XM_CALLCONV GetNearClip() const noexcept;

		// Get FarPlane as FLoat
		const float& XM_CALLCONV GetFarClip() const noexcept;

	private:
		// Initialize camera's View matrix from mPosition, mTarget and mUp coordinates
		void XM_CALLCONV initViewMatrix() noexcept;

		/*** Camera parameters ***/
		Vector4 m_Position;		// Camera's coordinates
		Vector4 m_Target;		// View target's coordinates
		Vector4 m_Up;			// Camera's up vector end coordinates

		Matrix  m_View;			// View matrix
		Matrix	m_Proj;			// Projection matrix
		Matrix	m_Ortho;		// Ortho matrix for drawing without tranformation
		Matrix  m_ViewProj;		// View matrix

		Matrix m_ReprojectMatrix; 	// Projects a clip-space coordinate to the previous frame (useful for temporal effects).
		Matrix m_PreviousViewProjMatrix;// The view-projection matrix from the previous frame

		// ViewFrustum
		Frustum m_ViewFrustum;		// Camera-View-Frustum

		/*** Projection parameters ***/
		float m_Angle;			// Angle of view frustum
		float m_ClientWidth;		// Window's width
		float m_ClientHeight;		// Window's height
		float m_Nearest;		// Nearest view frustum plane
		float m_Farthest;		// Farthest view frustum plane

	};

}; // end of namespace

#endif