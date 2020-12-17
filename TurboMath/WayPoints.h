
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

		void				SetPoint(Vector4& Pos)			{m_vPoint = Pos;}
		void				SetLockAt(Vector4& Rot)			{m_vLockAt = Rot;}
		void				SetStartTime(float Time)		{m_StartTime = Time;}
		void				SetMoveTime(float Time)			{m_MoveTime = Time;}

		Vector4				GetPoint()	const				{return m_vPoint;}
		Vector4				GetLockAt() const				{return m_vLockAt;}
		float				GetStartTime()	const			{return m_StartTime;}
		float				GetMoveTime()	const			{return m_MoveTime;}

		void				Reset()
		{
			m_vPoint = Vector4::NullVec();								// Reset
			m_vLockAt = Vector4::ForewardVec();
			m_StartTime = 0.0f;
			m_MoveTime = 0.0f;
		}

		// Ctor / Dtor

		PathPoint()
		{
			Reset();
		}

		PathPoint(const PathPoint& cpyPoint)
		{
			m_vPoint = cpyPoint.GetPoint();
			m_vLockAt = cpyPoint.GetLockAt();
			m_StartTime = cpyPoint.GetStartTime();
			m_MoveTime = cpyPoint.GetMoveTime();
		}

	private:

		Vector4				m_vPoint;						// Start Point
		Vector4				m_vLockAt;						// Lock-At
		float				m_StartTime;					// Start Time
		float				m_MoveTime;						// MoveTime for this part
	};

	/// This is the WayPoint-List
	CACHE_ALIGN(16) class WayPoints
	{
	public:
		enum PathPointType
		{
			PATH_STRAIGHT = 0,
			PATH_CURVED,

			PATHPOINT_FORCE_DWORD           = 0x7fffffff, /* force 32-bit size enum */
		};

	private:

		std::vector<PathPoint, AAllocator<PathPoint> >	m_PathPointList;							// Liste der Punkte

		Vector4				m_Position;																// Aktuelle Position auf dem Pfad
		Vector4				m_LockAt;																// act. Lock-At-Vector

		Vector4				m_ComputePoints[4];														// Diese Punkte werden für die Interpolation benutzt

		double				m_CurrentTime;															// Aktuelle Zeit
		float				m_Speed;																// Speed

		PathPointType		m_PathTypePosition;														// Linie, Curve oder was ?
		PathPointType		m_PathTypeLockAt;														// Linie, Curve oder was ?
		
		bool				m_ReverseAble;															// Pfad zurück gehen am Ende

		std::wstring		m_RouteName;															// Name der Route

	public:

		// Ctor / Dtor
		WayPoints()
		{
			m_PathTypePosition = PATH_STRAIGHT;
			m_PathTypeLockAt = PATH_STRAIGHT;

			m_Speed = 0.025f;
			m_CurrentTime = 0.0f;
		}

		virtual ~WayPoints()
		{
			DeletePath();
		}

		// Functions

		/// Get num Points in List
		const size_t	GetNumPathPoints()						{return m_PathPointList.size();}

		/// Add Point to List
		void			AddPathPoint(PathPoint& newPoint);

		/// Set the Path-Type for Position
		void			SetPathTypePosition(const PathPointType& type)
		{
			m_PathTypePosition = type;
		}
		/// Set the Path-Type for Lock-At
		void			SetPathTypeLockAt(const PathPointType& type)
		{
			m_PathTypeLockAt = type;
		}

		/// Delete Path
		void			DeletePath();

		/// Update the Actual position on WList
		const bool		Update(const float fTime)
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
			else 
			{
				// Curve Interpolation
				ExecuteCatmullRomInterpolation(fTime,&m_LockAt);	 
			}

			return true;
		}

		Vector4&		GetPosition()							{return m_Position;}				// Position auf dem Pfad
		Vector4&		GetLockAt()								{return m_LockAt;}					// Get Lock-At-Vector

		const std::wstring&	GetRouteName()						{return m_RouteName;}				// Name der Route zurück
		void			SetRouteName(const std::wstring& Name)	{m_RouteName = Name;}				// Namen zuweisen

		/// Restart Path
		void			Restart()
		{
			m_CurrentTime = 0.0f;
		}

		void			SetReverseAble(const bool Status)		{m_ReverseAble = Status;}			// ReverseAble setzen
		const bool		GetReverseAble()						{return m_ReverseAble;}				// ReverseAble abfragen

		void			SetSpeed(const float fSpeed)			{m_Speed = 1.0f / fSpeed;}			// Set Speed
		const float		GetSpeed()								{return m_Speed;}					// Get Speed

	private:

		/// Linerare Interpolation
		const bool		ExecuteLinearInterpolation( const float fTime,Vector4* pResult = NULL);

		/// Catmull-Rom Interpolation
		const bool		ExecuteCatmullRomInterpolation(const float fTime,Vector4* pResult = NULL);
	};

}; // end of namespace 


#endif