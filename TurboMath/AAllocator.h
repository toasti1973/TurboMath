
// -------------------------------------------------------------------
// File			:	AAllocator
//
// Project		:	TurboMath
//
// Description	:	Aligned-Allocator for STL-Container Use
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


#ifndef _TURBOMATH_AALLOCATOR_H_
#define _TURBOMATH_AALLOCATOR_H_

namespace TurboMath
{
	/// aligned allocator (required for x86)
	/// Usage : std::vector<Vector4, AAllocator<Vector4> >
	template <typename T, size_t N = 16>
	class AAllocator
	{
	
	public:
		typedef T			value_type;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;


	public:

		XM_INLINE  AAllocator () throw(){}

		template <typename T2>
		XM_INLINE  AAllocator(const AAllocator<T2, N> &) throw(){}

		XM_INLINE  ~AAllocator() throw(){}

		XM_INLINE  pointer            adress    (reference r)  const noexcept                     { return &r; }
		XM_INLINE  const_pointer      adress    (const_reference r) const  noexcept		          { return &r; }
		XM_INLINE  pointer            allocate  (size_type n)									  { return (pointer)_mm_malloc(n*sizeof(value_type), N); }
		XM_INLINE  void               deallocate(pointer p, size_type)							  { _mm_free(p); }
		XM_INLINE  void               construct (pointer p, const value_type & wert)			  { new(p) value_type(wert); }
		XM_INLINE  void               destroy   (pointer p)										  { p; p->~value_type(); }
		XM_INLINE  size_type          max_size  () const throw ()							      { size_t count = size_type(-1) / sizeof(value_type); return(0 < count ? count : 1); }

		template <typename T2>
		struct rebind { typedef AAllocator<T2, N> other; };
	};


}; // end of namespace

#endif