// -------------------------------------------------------------------
// File			:	WayPoints.inl
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

#pragma once
#pragma warning(disable:4244)

namespace TurboMath
{
	/// Add Point to List
	XM_INLINE   void  XM_CALLCONV WayPoints::AddPathPoint(PathPoint& newPoint) noexcept
	{
		m_PathTypePosition = PATH_STRAIGHT;
		m_PathTypeLockAt = PATH_STRAIGHT;

		m_PathPointList.push_back(newPoint);
	}

	/// Delete Path
	XM_INLINE   void  XM_CALLCONV WayPoints::DeletePath() noexcept
	{
		m_PathPointList.clear();

		m_PathTypePosition = PATH_STRAIGHT;
		m_PathTypeLockAt = PATH_STRAIGHT;
	}

	/// Linerare Interpolation
	XM_INLINE   const bool  XM_CALLCONV WayPoints::ExecuteLinearInterpolation( const float fTime,Vector4* pResult) noexcept
	{
		assert(pResult);
		if (!pResult) return false;

		const size_t NumPoints = m_PathPointList.size();

		if (NumPoints == 0) return false;

		assert(NumPoints > 0);																		// Have we any Points in the List ?

		const float fCurrentPoint = m_CurrentTime * (float)NumPoints;
		const size_t	CurrentPoint = (size_t)floor(fCurrentPoint);

		const float segmentLength = (1.0f / (float)NumPoints);
		const float timeStart = (float)CurrentPoint * segmentLength;

		float segmentTime = (m_CurrentTime - timeStart) / segmentLength;

		size_t nextPoint = 0;
		if(CurrentPoint < NumPoints-2) nextPoint = CurrentPoint+1;

		m_ComputePoints[0] = m_PathPointList[CurrentPoint].GetPoint();
		m_ComputePoints[1] = m_PathPointList[nextPoint].GetPoint();

		*pResult = Vector4::Lerp(m_ComputePoints[0],m_ComputePoints[1],segmentTime);

		// Ready
		return true;
	}

	/// Catmull-Rom Interpolation
	XM_INLINE   const bool  XM_CALLCONV WayPoints::ExecuteCatmullRomInterpolation(const float fTime,Vector4* pResult) noexcept
	{
		assert(pResult);
		if (!pResult) return false;

		const size_t NumPoints = m_PathPointList.size();

		if (NumPoints == 0) return true;

		assert(NumPoints > 0);																		// Have we any Points in the List ?

		const float fCurrentPoint = m_CurrentTime * (float)NumPoints;
		size_t	CurrentPoint = (size_t)floor(fCurrentPoint);

		const float segmentLength = (1.0f / (float)NumPoints);
		const float timeStart = (float)CurrentPoint * segmentLength;

		float segmentTime = (m_CurrentTime - timeStart) / segmentLength;

		size_t p1,p2,p3,p4;

		if (CurrentPoint > 0) p1 = CurrentPoint -1;
		else p1 = NumPoints - 1;

		p2 = CurrentPoint;

		if (CurrentPoint < NumPoints -1) p3 = CurrentPoint +1;
		else p3 = 0;

		if(CurrentPoint < NumPoints -2) p4 = CurrentPoint +2;
		else p4 = 1;

		m_ComputePoints[0] = m_PathPointList[p1].GetPoint();
		m_ComputePoints[1] = m_PathPointList[p2].GetPoint();
		m_ComputePoints[2] = m_PathPointList[p3].GetPoint();
		m_ComputePoints[3] = m_PathPointList[p4].GetPoint();

		*pResult = Vector4::Catmullrom(m_ComputePoints[0], m_ComputePoints[1], m_ComputePoints[2], m_ComputePoints[3], segmentTime);

		// Ready
		return true;
	}
}// end of Namespace TurboMath