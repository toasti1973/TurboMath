
// -------------------------------------------------------------------
// File			:	WayPoints.h
//
// Project		:	TurboMath
//
// Description	:	Class for Waypoints
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


#ifndef _TURBOBOOSTER_MATH_WAYPOINTS_H_
#define _TURBOBOOSTER_MATH_WAYPOINTS_H_

#include <vector>
#include <string>

namespace TurboMath
{



	/// This is ONE Waypoit
	CACHE_ALIGN(16) class PathPoint
	{
	public :

		void	XM_CALLCONV			SetPoint(Vector4& Pos)	 noexcept		{m_vPoint = Pos;}
		void	XM_CALLCONV			SetLockAt(Vector4& Rot)	 noexcept		{m_vLockAt = Rot;}
		void	XM_CALLCONV			SetStartTime(float Time) noexcept		{m_StartTime = Time;}
		void	XM_CALLCONV			SetMoveTime(float Time)	 noexcept		{m_MoveTime = Time;}

		Vector4	XM_CALLCONV			GetPoint()	const	 noexcept		{return m_vPoint;}
		Vector4	XM_CALLCONV			GetLockAt() 	const	 noexcept		{return m_vLockAt;}
		float	XM_CALLCONV			GetStartTime()	const	 noexcept		{return m_StartTime;}
		float	XM_CALLCONV			GetMoveTime()	const	 noexcept		{return m_MoveTime;}

		void	XM_CALLCONV			Reset() noexcept
		{
			m_vPoint = Vector4::NullVec();								// Reset
			m_vLockAt = Vector4::ForewardVec();
			m_StartTime = 0.0f;
			m_MoveTime = 0.0f;
		}

		// Ctor / Dtor

		PathPoint() noexcept
		{
			Reset();
		}

		PathPoint(const PathPoint& cpyPoint) noexcept
		{
			m_vPoint = cpyPoint.GetPoint();
			m_vLockAt = cpyPoint.GetLockAt();
			m_StartTime = cpyPoint.GetStartTime();
			m_MoveTime = cpyPoint.GetMoveTime();
		}

	private:

		Vector4				m_vPoint;						// Start Point
		Vector4				m_vLockAt;						// Lock-At
		float				m_StartTime;						// Start Time
		float				m_MoveTime;						// MoveTime for this part
	};

	/// This is the WayPoint-List
	CACHE_ALIGN(16) class WayPoints
	{
	public:
		enum PathPointType
		{
			PATH_LOCKAT_NONE = 0,			// Only for Lock-AT
			PATH_STRAIGHT,
			PATH_CURVED,

			PATHPOINT_FORCE_DWORD           = 0x7fffffff, /* force 32-bit size enum */
		};

	private:

		std::vector<PathPoint, AAllocator<PathPoint> >	m_PathPointList;							// Liste der Punkte

		Vector4				m_Position;										// Aktuelle Position auf dem Pfad
		Vector4				m_LockAt;										// act. Lock-At-Vector

		Vector4				m_ComputePoints[4];									// Diese Punkte werden für die Interpolation benutzt

		double				m_CurrentTime;										// Aktuelle Zeit
		float				m_Speed;										// Speed

		PathPointType			m_PathTypePosition;									// Linie, Curve oder was ?
		PathPointType			m_PathTypeLockAt;									// Linie, Curve oder was ?
		
		bool				m_ReverseAble;										// Pfad zurück gehen am Ende

		std::wstring			m_RouteName;										// Name der Route

	public:

		// Ctor / Dtor
		WayPoints() noexcept
		{
			m_PathTypePosition = PATH_STRAIGHT;
			m_PathTypeLockAt = PATH_STRAIGHT;

			m_Speed = 0.025f;
			m_CurrentTime = 0.0f;
		}

		virtual ~WayPoints() noexcept
		{
			DeletePath();
		}

		// Functions

		/// Get num Points in List
		const size_t XM_CALLCONV	GetNumPathPoints()	 noexcept			{return m_PathPointList.size();}

		/// Add Point to List
		void	XM_CALLCONV		AddPathPoint(PathPoint& newPoint) noexcept;

		/// Set the Path-Type for Position
		void	XM_CALLCONV		SetPathTypePosition(const PathPointType& type) noexcept
		{
			m_PathTypePosition = type;
		}

		/// Set the Path-Type for Lock-At
		void	XM_CALLCONV		SetPathTypeLockAt(const PathPointType& type) noexcept
		{
			m_PathTypeLockAt = type;
		}

		/// Delete Path
		void	XM_CALLCONV		DeletePath() noexcept;

		/// Update the Actual position on WList
		const bool	XM_CALLCONV	Update(const float fTime) noexcept
		{
			if (m_PathPointList.size() == 0)  return false;							// No Path

			m_CurrentTime += (m_Speed * fTime);
			if(m_CurrentTime > 1.0f) m_CurrentTime = 0.0f;

			// Calc Position
			if (m_PathTypePosition == PATH_STRAIGHT) 
			{
				// Lineare Interpolation
				ExecuteLinearInterpolation(fTime,&m_Position);	

			}
			else 
			{
				// Curve Interpolation
				ExecuteCatmullRomInterpolation(fTime,&m_Position);	 
			}

			//Calc Lock-At
			if (m_PathTypeLockAt == PATH_STRAIGHT) 
			{
				// Lineare Interpolation
				ExecuteLinearInterpolation(fTime,&m_LockAt);	

			}
			else if (m_PathTypeLockAt == PATH_CURVED)
			{
				// Curve Interpolation
				ExecuteCatmullRomInterpolation(fTime,&m_LockAt);	 
			}

			return true;
		}

		Vector4& XM_CALLCONV		GetPosition()	 noexcept			{return m_Position;}				// Position auf dem Pfad
		Vector4& XM_CALLCONV		GetLockAt()	 noexcept			{return m_LockAt;}				// Get Lock-At-Vector

		const std::wstring& XM_CALLCONV	GetRouteName()	 noexcept			{return m_RouteName;}				// Name der Route zurück
		void	XM_CALLCONV		SetRouteName(const std::wstring& Name) noexcept	{m_RouteName = Name;}				// Namen zuweisen

		/// Restart Path
		void	XM_CALLCONV		Restart() noexcept
		{
			m_CurrentTime = 0.0f;
		}

		void	XM_CALLCONV		SetReverseAble(const bool Status) noexcept		{m_ReverseAble = Status;}			// ReverseAble setzen
		const bool XM_CALLCONV		GetReverseAble() noexcept				{return m_ReverseAble;}				// ReverseAble abfragen

		void	XM_CALLCONV		SetSpeed(const float fSpeed)	 noexcept		{m_Speed = 1.0f / fSpeed;}			// Set Speed
		const float XM_CALLCONV		GetSpeed()	 noexcept				{return m_Speed;}					// Get Speed

	private:

		/// Linerare Interpolation
		const bool XM_CALLCONV		ExecuteLinearInterpolation( const float fTime,Vector4* pResult = NULL) noexcept;

		/// Catmull-Rom Interpolation
		const bool XM_CALLCONV		ExecuteCatmullRomInterpolation(const float fTime,Vector4* pResult = NULL) noexcept;
	};

}; // end of namespace 


#endif