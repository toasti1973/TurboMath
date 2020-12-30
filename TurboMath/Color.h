
// -------------------------------------------------------------------
// File			:	Color
//
// Project		:	TurboMath
//
// Description	:	Class for Color
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

#ifndef _TURBOMATH_COLOR
#define _TURBOMATH_COLOR




namespace TurboMath
{

	CACHE_ALIGN(16) class  Color
	{

	public:
		//------------------------------------------------------------
		// Constructor
		// -----------------------------------------------------------

				Color()	noexcept;																																						
				Color(const Color& c) noexcept;																																	
		explicit	Color(const float f) noexcept;	
		explicit	Color(const float r, const float g, const float b) noexcept;	
		explicit	Color(const float r, const float g, const float b, const float a) noexcept;
		explicit	Color(const float* pfComponent)	noexcept;	
		explicit	Color(const char r, const char g, const char b) noexcept;
		explicit	Color(const char r, const char g, const char b, const char a) noexcept;
		explicit	Color(const char* pComponent) noexcept;
		explicit	Color(const Vector4& rhs) noexcept;
		explicit	Color(const XMVECTOR& rhs) noexcept;

				Color(uint16_t r, uint16_t g, uint16_t b, uint16_t a = 255, uint16_t bitDepth = 8) noexcept;
		explicit	Color(uint32_t rgbaLittleEndian) noexcept;
		
		//------------------------------------------------------------
		// assignment
		// -----------------------------------------------------------

		/// assignment operator
		void  XM_CALLCONV operator=( Color& rhs) noexcept;

		/// assign an XMFLOAT4
		void  XM_CALLCONV operator=( XMFLOAT4 rhs) noexcept;

		/// assign a float
		Color  XM_CALLCONV operator=(  float rhs) noexcept;

		/// assign an XMVECTOR
		void  XM_CALLCONV operator=( XMVECTOR rhs) noexcept;


		//------------------------------------------------------------
		// Casting-Operatoren
		//------------------------------------------------------------

		XM_CALLCONV operator XMVECTOR& () noexcept			{return color;}
		XM_CALLCONV operator const XMVECTOR& () const noexcept		{return color;}
	
		XM_CALLCONV operator XMVECTOR* () noexcept			{return &color;}
		XM_CALLCONV operator const XMVECTOR* () const noexcept		{return &color;}
		
		XM_CALLCONV operator float* () noexcept				{return (float*)&color;}
		XM_CALLCONV operator const float* () const noexcept		{return (float*)&color;}

		XM_CALLCONV operator PackedVector::XMCOLOR () noexcept		{return PackedVector::XMCOLOR((float*)&color);}
		XM_CALLCONV operator const PackedVector::XMCOLOR () noexcept	{return PackedVector::XMCOLOR((float*)&color);}
	
		XM_CALLCONV operator DWORD () noexcept				{return DWORD (PackedVector::XMCOLOR((float*)&color) );}
		XM_CALLCONV operator const DWORD ()	 noexcept		{return DWORD (PackedVector::XMCOLOR((float*)&color) );}

		XM_CALLCONV operator XMFLOAT4 () noexcept			{return XMFLOAT4((float*)&color) ;}
		XM_CALLCONV operator const XMFLOAT4 () noexcept			{return XMFLOAT4((float*)&color) ;}
		//------------------------------------------------------------
		// Set-Functions
		//------------------------------------------------------------

		/// Set Red
		void  XM_CALLCONV SetR(const float red) noexcept;

		/// Set Green
		void  XM_CALLCONV SetG(const float green) noexcept;

		/// Set Blue
		void  XM_CALLCONV SetB(const float blue) noexcept;

		/// Set Alpha
		void  XM_CALLCONV SetA(const float alpha) noexcept;

		/// Set RGB
		void  XM_CALLCONV SetRGB(const float red,const float green, const float blue) noexcept;

		/// Set RGBA
		void  XM_CALLCONV SetRGBA(const float red,const float green, const float blue, const float alpha) noexcept;

		//------------------------------------------------------------
		// Read / Write Access
		//------------------------------------------------------------

		/// Get Red
		const float  XM_CALLCONV GetR() const noexcept;

		/// Get Green
		const float  XM_CALLCONV GetG() const noexcept;

		/// Get Blue
		const float  XM_CALLCONV GetB() const noexcept;

		/// Get Alpha
		const float XM_CALLCONV  GetA() const noexcept;

		/// Get as DWORD
		const DWORD  XM_CALLCONV GetAsDWORD() const noexcept;

		/// Get as XMFLOAT4
		const XMFLOAT4  XM_CALLCONV GetAsXMFLOAT4() const noexcept;

		/// Get RawData
		XMVECTOR  XM_CALLCONV GetRaw() const noexcept;

		/// Get RawDataPtr
		XMVECTOR*  XM_CALLCONV GetRawPtr() noexcept;

		// Get Float Pointer
		float* XM_CALLCONV GetFloatPtr() noexcept;

		//------------------------------------------------------------
		// operator
		//------------------------------------------------------------
		Color&  XM_CALLCONV operator += (const Color& c) noexcept;
		Color&  XM_CALLCONV operator -= (const Color& c) noexcept;
		Color&  XM_CALLCONV operator *= (const Color& c) noexcept;
		Color&  XM_CALLCONV operator *= (const float f) noexcept;
		Color&  XM_CALLCONV operator /= (const Color& c) noexcept;
		Color&  XM_CALLCONV operator /= (const float f) noexcept;


		Color  XM_CALLCONV operator + (const Color& a) const noexcept;
		Color  XM_CALLCONV operator - (const Color& a) const noexcept;
		Color  XM_CALLCONV operator * (const Color& a) const noexcept;
		Color  XM_CALLCONV operator * (const float f)  const noexcept;
		Color  XM_CALLCONV operator / (const Color& a) const noexcept;
		Color  XM_CALLCONV operator / ( const float f) const noexcept;


		bool  XM_CALLCONV operator == (const Color& a) const noexcept;
		bool  XM_CALLCONV operator != (const Color& a) const noexcept;

		/// assignment operator
		Color&  XM_CALLCONV operator=(const Vector4 &rhs) noexcept;

		//------------------------------------------------------------
		// Packing
		//------------------------------------------------------------

		unsigned char	 XM_CALLCONV Pack_RGB332()   const;
		unsigned short	 XM_CALLCONV Pack_ARGB4444() const noexcept;
		unsigned short	 XM_CALLCONV Pack_RGB555()   const noexcept;
		unsigned short	 XM_CALLCONV Pack_RGB565()   const noexcept;
		unsigned int	 XM_CALLCONV Pack_RGB888()   const noexcept;
		unsigned int	 XM_CALLCONV Pack_ABGR8888() const noexcept;
		unsigned int	 XM_CALLCONV Pack_ARGB8888() const noexcept;
		
		//------------------------------------------------------------
		/// Functions
		//------------------------------------------------------------

		void  XM_CALLCONV 		Clamp() noexcept;

		void  XM_CALLCONV 		Clamp(const float bottom, const float top) noexcept;
		
		void  XM_CALLCONV 		AdjustContrast(const float c) noexcept;

		void  XM_CALLCONV 		AdjustSaturation(const float s) noexcept;

		void  XM_CALLCONV 		LerpFloat(const Color& ca, const Color& cb, float s) noexcept;

		void  XM_CALLCONV 		Negative() noexcept;

		void  XM_CALLCONV 		Grey() noexcept;
	
		unsigned int  XM_CALLCONV 	toARGB( ) noexcept;

		unsigned int  XM_CALLCONV 	toRGBA( ) noexcept;
	
		void  XM_CALLCONV 		fromARGB( unsigned int color ) noexcept;

		Color	 XM_CALLCONV 		Negate(const Color& c) noexcept;	

		float	 XM_CALLCONV 		Brightness(const Color& c) noexcept;	

		Color	 XM_CALLCONV 		Interpolate( Color& c1,  Color& c2, const float p) noexcept;

		Color	 XM_CALLCONV 		Min(const Color& c1, const Color& c2) noexcept;	

		Color	 XM_CALLCONV 		Max(const Color& c1, const Color& c2) noexcept;	

		Color	 XM_CALLCONV 		Random(const float fAlpha) noexcept;	

		Color	 XM_CALLCONV 		ToSRGB() const noexcept;
		Color	 XM_CALLCONV 		FromSRGB() const noexcept;
		Color	 XM_CALLCONV 		ToREC709() const noexcept;
		Color	 XM_CALLCONV 		FromREC709() const noexcept;

		uint32_t  XM_CALLCONV 		R10G10B10A2() const noexcept;
		uint32_t XM_CALLCONV  		R8G8B8A8() const noexcept;

	protected:
		// Variablen
		XMVECTOR		color;

	};


	// Farben vor definieren

	const static Color	Color_White					(	1.000000f,	1.000000f,	1.000000f,	1.000000f);		// White
	const static Color	Color_Black					(	0.000000f,	0.000000f,	0.000000f,	1.000000f);		// Black
	const static Color	Color_Blue					(	0.000000f,	0.000000f,	1.000000f,	1.000000f);		// Blue
	const static Color	Color_Yellow				(	1.000000f,	1.000000f,	0.000000f,	1.000000f);		// Yellow
	const static Color	Color_Cyan					(	0.000000f,	1.000000f,	1.000000f,	1.000000f);		// Cyan
	const static Color	Color_Magenta				(	1.000000f,	0.000000f,	1.000000f,	1.000000f);		// Magenta
	const static Color	Color_Green					(	0.000000f,	1.000000f,	0.000000f,	1.000000f);		// Green
	const static Color	Color_Red					(	1.000000f,	0.000000f,	0.000000f,	1.000000f);		// Red
	const static Color	Color_Beach_Sand			(	1.000000f,	0.960000f,	0.620000f,	1.000000f);		// Beach Sand
	const static Color	Color_Light_Yellow_Green	(	0.480000f,	0.770000f,	0.460000f,	1.000000f);		// Light Yellow-Green
	const static Color	Color_Dark_Yellow_Green		(	0.100000f,	0.480000f,	0.190000f,	1.000000f);		// Dark Yellow-Green
	const static Color	Color_Dark_Brown			(	0.450000f,	0.390000f,	0.340000f,	1.000000f);		// Dard Brown
	const static Color	Color_Aquamarine			(	0.439216f,	0.858824f,	0.576471f,	1.000000f);		// Aquamarine
	const static Color	Color_BlueViolet			(	0.623529f,	0.372549f,	0.623529f,	1.000000f);		// Blue Violet
	const static Color	Color_Brown					(	0.647059f,	0.164706f,	0.164706f,	1.000000f);		// Brown
	const static Color	Color_CadetBlue				(	0.372549f,	0.623529f,	0.623529f,	1.000000f);		// Cadetblue
	const static Color	Color_Coral					(	1.000000f,	0.498039f,	0.000000f,	1.000000f);		// Coral
	const static Color	Color_CornflowerBlue		(	0.258824f,	0.258824f,	0.435294f,	1.000000f);		// Crownflower Blue
	const static Color	Color_DarkGray				(	0.500000f,	0.500000f,	0.500000f,	1.000000f);		// Dark Grey
	const static Color	Color_DarkGreen				(	0.184314f,	0.309804f,	0.184314f,	1.000000f);		// Dark Green
	const static Color	Color_DarkOliveGreen		(	0.309804f,	0.309804f,	0.184314f,	1.000000f);		// Dark Olive Green
	const static Color	Color_DarkOrchildColorF 	(	0.600000f,	0.196078f,	0.800000f,	1.000000f);
	const static Color	Color_DarkSlateBlue			(	0.419608f,	0.137255f,	0.556863f,	1.000000f);
	const static Color	Color_DarkSlateGray			(	0.184314f,	0.309804f,	0.309804f,	1.000000f);
	const static Color	Color_DarkSlateGrey			(	0.184314f,	0.309804f,	0.309804f,	1.000000f);
	const static Color	Color_DarkTurquoise			(	0.439216f,	0.576471f,	0.858824f,	1.000000f);
	const static Color	Color_DarkWood				(	0.050000f,	0.010000f,	0.005000f,	1.000000f);
	const static Color	Color_DimGray				(	0.329412f,	0.329412f,	0.329412f,	1.000000f);
	const static Color	Color_DimGrey				(	0.329412f,	0.329412f,	0.329412f,	1.000000f);
	const static Color	Color_FireBrick				(	0.900000f,	0.400000f,	0.300000f,	1.000000f);
	const static Color	Color_ForestGreen			(	0.137255f,	0.556863f,	0.137255f,	1.000000f);
	const static Color	Color_Gold					(	0.800000f,	0.498039f,	0.196078f,	1.000000f);
	const static Color	Color_Goldenrod				(	0.858824f,	0.858824f,	0.439216f,	1.000000f);
	const static Color	Color_Gray					(	0.752941f,	0.752941f,	0.752941f,	1.000000f);
	const static Color	Color_GreenYellow			(	0.576471f,	0.858824f,	0.439216f,	1.000000f);
	const static Color	Color_Grey					(	0.752941f,	0.752941f,	0.752941f,	1.000000f);
	const static Color	Color_IndianRed				(	0.309804f,	0.184314f,	0.184314f,	1.000000f);
	const static Color	Color_Khaki					(	0.623529f,	0.623529f,	0.372549f,	1.000000f);
	const static Color	Color_LightBlue				(	0.749020f,	0.847059f,	0.847059f,	1.000000f);
	const static Color	Color_LightGray				(	0.658824f,	0.658824f,	0.658824f,	1.000000f);
	const static Color	Color_LightSteelBlue		(	0.560784f,	0.560784f,	0.737255f,	1.000000f);
	const static Color	Color_LightWood				(	0.600000f,	0.240000f,	0.100000f,	1.000000f);
	const static Color	Color_LimeGreen				(	0.196078f,	0.800000f,	0.196078f,	1.000000f);
	const static Color	Color_Maroon				(	0.556863f,	0.137255f,	0.419608f,	1.000000f);
	const static Color	Color_MedianWood			(	0.300000f,	0.120000f,	0.030000f,	1.000000f);
	const static Color	Color_MediumAquamarine		(	0.196078f,	0.800000f,	0.600000f,	1.000000f);
	const static Color	Color_MediumBlue			(	0.196078f,	0.196078f,	0.800000f,	1.000000f);
	const static Color	Color_MediumForestGreen		(	0.419608f,	0.556863f,	0.137255f,	1.000000f);
	const static Color	Color_MediumGoldenrod		(	0.917647f,	0.917647f,	0.678431f,	1.000000f);
	const static Color	Color_MediumOrchid			(	0.576471f,	0.439216f,	0.858824f,	1.000000f);
	const static Color	Color_MediumSeaGreen		(	0.258824f,	0.435294f,	0.258824f,	1.000000f);
	const static Color	Color_MediumSlateBlue		(	0.498039f,	0.000000f,	1.000000f,	1.000000f);
	const static Color	Color_MediumSpringGreen		(	0.498039f,	1.000000f,	0.000000f,	1.000000f);
	const static Color	Color_MediumTurquoise		(	0.439216f,	0.858824f,	0.858824f,	1.000000f);
	const static Color	Color_MediumVioletRed		(	0.858824f,	0.439216f,	0.576471f,	1.000000f);
	const static Color	Color_MidnightBlue			(	0.184314f,	0.184314f,	0.309804f,	1.000000f);
	const static Color	Color_Navy					(	0.137255f,	0.137255f,	0.556863f,	1.000000f);
	const static Color	Color_NavyBlue				(	0.137255f,	0.137255f,	0.556863f,	1.000000f);
	const static Color	Color_Orange				(	0.800000f,	0.196078f,	0.196078f,	1.000000f);
	const static Color	Color_OrangeRed				(	0.000000f,	0.000000f,	0.498039f,	1.000000f);
	const static Color	Color_Orchid				(	0.858824f,	0.439216f,	0.858824f,	1.000000f);
	const static Color	Color_PaleGreen				(	0.560784f,	0.737255f,	0.560784f,	1.000000f);
	const static Color	Color_Pink					(	0.737255f,	0.560784f,	0.560784f,	1.000000f);
	const static Color	Color_Plum					(	0.917647f,	0.678431f,	0.917647f,	1.000000f);
	const static Color	Color_Salmon				(	0.435294f,	0.258824f,	0.258824f,	1.000000f);
	const static Color	Color_SeaGreen				(	0.137255f,	0.556863f,	0.419608f,	1.000000f);
	const static Color	Color_Sienna				(	0.556863f,	0.419608f,	0.137255f,	1.000000f);
	const static Color	Color_SkyBlue				(	0.196078f,	0.600000f,	0.800000f,	1.000000f);
	const static Color	Color_SlateBlue				(	0.000000f,	0.498039f,	1.000000f,	1.000000f);
	const static Color	Color_SpringGreen			(	0.000000f,	1.000000f,	0.498039f,	1.000000f);
	const static Color	Color_SteelBlue				(	0.137255f,	0.419608f,	0.556863f,	1.000000f);
	const static Color	Color_Tan					(	0.858824f,	0.576471f,	0.439216f,	1.000000f);
	const static Color	Color_Thistle				(	0.847059f,	0.749020f,	0.847059f,	1.000000f);
	const static Color	Color_Turquoise				(	0.678431f,	0.917647f,	0.917647f,	1.000000f);
	const static Color	Color_Violet				(	0.309804f,	0.184314f,	0.309804f,	1.000000f);
	const static Color	Color_VioletRed				(	0.800000f,	0.196078f,	0.600000f,	1.000000f);
	const static Color	Color_Wheat					(	0.847059f,	0.847059f,	0.749020f,	1.000000f);
	const static Color	Color_YellowGreen			(	0.600000f,	0.800000f,	0.196078f,	1.000000f);

}; // end of namespace

#endif

