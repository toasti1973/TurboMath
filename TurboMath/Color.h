
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

					Color()	;																																						
					Color(const Color& c);																																	
		explicit	Color(const float f);	
		explicit	Color(const float r, const float g, const float b);	
		explicit	Color(const float r, const float g, const float b, const float a);
		explicit	Color(const float* pfComponent);	
		explicit	Color(const char r, const char g, const char b);
		explicit	Color(const char r, const char g, const char b, const char a);
		explicit	Color(const char* pComponent);
		explicit	Color(const Vector4& rhs);
		explicit	Color(const XMVECTOR& rhs);

					Color(uint16_t r, uint16_t g, uint16_t b, uint16_t a = 255, uint16_t bitDepth = 8);
		explicit	Color(uint32_t rgbaLittleEndian);
		
		//------------------------------------------------------------
		// assignment
		// -----------------------------------------------------------

		/// assignment operator
		void operator=( Color& rhs);

		/// assign an XMFLOAT4
		void operator=( XMFLOAT4 rhs);

		/// assign a float
		Color operator=(  float rhs);

		/// assign an XMVECTOR
		void operator=( XMVECTOR rhs);


		//------------------------------------------------------------
		// Casting-Operatoren
		//------------------------------------------------------------

		operator XMVECTOR& ()					{return color;}
		operator const XMVECTOR& () const		{return color;}
	
		operator XMVECTOR* ()					{return &color;}
		operator const XMVECTOR* () const		{return &color;}
		
		operator float* ()						{return (float*)&color;}
		operator const float* () const			{return (float*)&color;}

		operator PackedVector::XMCOLOR ()		{return PackedVector::XMCOLOR((float*)&color);}
		operator const PackedVector::XMCOLOR ()	{return PackedVector::XMCOLOR((float*)&color);}
	
		operator DWORD ()						{return DWORD (PackedVector::XMCOLOR((float*)&color) );}
		operator const DWORD ()					{return DWORD (PackedVector::XMCOLOR((float*)&color) );}

		operator XMFLOAT4 ()					{return XMFLOAT4((float*)&color) ;}
		operator const XMFLOAT4 ()				{return XMFLOAT4((float*)&color) ;}

		//------------------------------------------------------------
		// Set-Functions
		//------------------------------------------------------------

		/// Set Red
		void SetR(const float red);

		/// Set Green
		void SetG(const float green);

		/// Set Blue
		void SetB(const float blue);

		/// Set Alpha
		void SetA(const float alpha);

		/// Set RGB
		void SetRGB(const float red,const float green, const float blue);

		/// Set RGBA
		void SetRGBA(const float red,const float green, const float blue, const float alpha);

		//------------------------------------------------------------
		// Read / Write Access
		//------------------------------------------------------------

		/// Get Red
		const float GetR() const;

		/// Get Green
		const float GetG() const;

		/// Get Blue
		const float GetB() const;

		/// Get Alpha
		const float GetA() const;

		/// Get as DWORD
		const DWORD GetAsDWORD() const;

		/// Get as XMFLOAT4
		const XMFLOAT4 GetAsXMFLOAT4() const;

		/// Get RawData
		XMVECTOR	GetRaw() const;

		/// Get RawDataPtr
		XMVECTOR*	GetRawPtr();

		// Get Float Pointer
		float*	GetFloatPtr();

		//------------------------------------------------------------
		// operator
		//------------------------------------------------------------
		Color& operator += (const Color& c);
		Color& operator -= (const Color& c);
		Color& operator *= (const Color& c);
		Color& operator *= (const float f);
		Color& operator /= (const Color& c);
		Color& operator /= (const float f);


		Color operator + (const Color& a) const;
		Color operator - (const Color& a) const;
		Color operator * (const Color& a) const;
		Color operator * (const float f) const;
		Color operator / (const Color& a) const;
		Color operator / ( const float f) const;


		bool operator == (const Color& a) const;
		bool operator != (const Color& a) const;

		/// assignment operator
		Color& operator=(const Vector4 &rhs);

		//------------------------------------------------------------
		// Packing
		//------------------------------------------------------------

		unsigned char	Pack_RGB332() const;
		unsigned short	Pack_ARGB4444() const;
		unsigned short	Pack_RGB555() const;
		unsigned short	Pack_RGB565() const;
		unsigned int	Pack_RGB888() const;
		unsigned int	Pack_ABGR8888() const;
		unsigned int	Pack_ARGB8888() const;
		
		//------------------------------------------------------------
		/// Functions
		//------------------------------------------------------------

		void Clamp();

		void Clamp(const float bottom, const float top);
		
		void AdjustContrast(const float c);

		void AdjustSaturation(const float s);

		void LerpFloat(const Color& ca, const Color& cb, float s);

		void Negative();

		void Grey();
	
		unsigned int toARGB( );

		unsigned int toRGBA( );
	
		void fromARGB( unsigned int color );

		Color	Negate(const Color& c);	

		float	Brightness(const Color& c);	

		Color	Interpolate( Color& c1,  Color& c2, const float p);

		Color	Min(const Color& c1, const Color& c2);	

		Color	Max(const Color& c1, const Color& c2);	

		Color	Random(const float fAlpha);	

		Color	ToSRGB() const;
		Color	FromSRGB() const;
		Color	ToREC709() const;
		Color	FromREC709() const;

		uint32_t R10G10B10A2() const;
		uint32_t R8G8B8A8() const;

	protected:
		// Variablen
		XMVECTOR		color;

	};


	// Farben vor definieren

	const static Color	Color_White				(	1.000000f,	1.000000f,	1.000000f,	1.000000f);		// White
	const static Color	Color_Black				(	0.000000f,	0.000000f,	0.000000f,	1.000000f);		// Black
	const static Color	Color_Blue				(	0.000000f,	0.000000f,	1.000000f,	1.000000f);		// Blue
	const static Color	Color_Yellow			(	1.000000f,	1.000000f,	0.000000f,	1.000000f);		// Yellow
	const static Color	Color_Cyan				(	0.000000f,	1.000000f,	1.000000f,	1.000000f);		// Cyan
	const static Color	Color_Magenta			(	1.000000f,	0.000000f,	1.000000f,	1.000000f);		// Magenta
	const static Color	Color_Green				(	0.000000f,	1.000000f,	0.000000f,	1.000000f);		// Green
	const static Color	Color_Red				(	1.000000f,	0.000000f,	0.000000f,	1.000000f);		// Red
	const static Color	Color_Beach_Sand		(	1.000000f,	0.960000f,	0.620000f,	1.000000f);		// Beach Sand
	const static Color	Color_Light_Yellow_Green(	0.480000f,	0.770000f,	0.460000f,	1.000000f);		// Light Yellow-Green
	const static Color	Color_Dark_Yellow_Green	(	0.100000f,	0.480000f,	0.190000f,	1.000000f);		// Dark Yellow-Green
	const static Color	Color_Dark_Brown		(	0.450000f,	0.390000f,	0.340000f,	1.000000f);		// Dard Brown
	const static Color	Color_Aquamarine		(	0.439216f,	0.858824f,	0.576471f,	1.000000f);
	const static Color	Color_BlueViolet		(	0.623529f,	0.372549f,	0.623529f,	1.000000f);
	const static Color	Color_Brown				(	0.647059f,	0.164706f,	0.164706f,	1.000000f);
	const static Color	Color_CadetBlue			(	0.372549f,	0.623529f,	0.623529f,	1.000000f);
	const static Color	Color_Coral				(	1.000000f,	0.498039f,	0.000000f,	1.000000f);
	const static Color	Color_CornflowerBlue	(	0.258824f,	0.258824f,	0.435294f,	1.000000f);
	const static Color	Color_DarkGray			(	0.500000f,	0.500000f,	0.500000f,	1.000000f);
	const static Color	Color_DarkGreen			(	0.184314f,	0.309804f,	0.184314f,	1.000000f);
	const static Color	Color_DarkOliveGreen	(	0.309804f,	0.309804f,	0.184314f,	1.000000f);
	const static Color	Color_DarkOrchildColorF (	0.600000f,	0.196078f,	0.800000f,	1.000000f);
	const static Color	Color_DarkSlateBlue		(	0.419608f,	0.137255f,	0.556863f,	1.000000f);
	const static Color	Color_DarkSlateGray		(	0.184314f,	0.309804f,	0.309804f,	1.000000f);
	const static Color	Color_DarkSlateGrey		(	0.184314f,	0.309804f,	0.309804f,	1.000000f);
	const static Color	Color_DarkTurquoise		(	0.439216f,	0.576471f,	0.858824f,	1.000000f);
	const static Color	Color_DarkWood			(	0.050000f,	0.010000f,	0.005000f,	1.000000f);
	const static Color	Color_DimGray			(	0.329412f,	0.329412f,	0.329412f,	1.000000f);
	const static Color	Color_DimGrey			(	0.329412f,	0.329412f,	0.329412f,	1.000000f);
	const static Color	Color_FireBrick			(	0.900000f,	0.400000f,	0.300000f,	1.000000f);
	const static Color	Color_ForestGreen		(	0.137255f,	0.556863f,	0.137255f,	1.000000f);
	const static Color	Color_Gold				(	0.800000f,	0.498039f,	0.196078f,	1.000000f);
	const static Color	Color_Goldenrod			(	0.858824f,	0.858824f,	0.439216f,	1.000000f);
	const static Color	Color_Gray				(	0.752941f,	0.752941f,	0.752941f,	1.000000f);
	const static Color	Color_GreenYellow		(	0.576471f,	0.858824f,	0.439216f,	1.000000f);
	const static Color	Color_Grey				(	0.752941f,	0.752941f,	0.752941f,	1.000000f);
	const static Color	Color_IndianRed			(	0.309804f,	0.184314f,	0.184314f,	1.000000f);
	const static Color	Color_Khaki				(	0.623529f,	0.623529f,	0.372549f,	1.000000f);
	const static Color	Color_LightBlue			(	0.749020f,	0.847059f,	0.847059f,	1.000000f);
	const static Color	Color_LightGray			(	0.658824f,	0.658824f,	0.658824f,	1.000000f);
	const static Color	Color_LightSteelBlue	(	0.560784f,	0.560784f,	0.737255f,	1.000000f);
	const static Color	Color_LightWood			(	0.600000f,	0.240000f,	0.100000f,	1.000000f);
	const static Color	Color_LimeGreen			(	0.196078f,	0.800000f,	0.196078f,	1.000000f);
	const static Color	Color_Maroon			(	0.556863f,	0.137255f,	0.419608f,	1.000000f);
	const static Color	Color_MedianWood		(	0.300000f,	0.120000f,	0.030000f,	1.000000f);
	const static Color	Color_MediumAquamarine	(	0.196078f,	0.800000f,	0.600000f,	1.000000f);
	const static Color	Color_MediumBlue		(	0.196078f,	0.196078f,	0.800000f,	1.000000f);
	const static Color	Color_MediumForestGreen	(	0.419608f,	0.556863f,	0.137255f,	1.000000f);
	const static Color	Color_MediumGoldenrod	(	0.917647f,	0.917647f,	0.678431f,	1.000000f);
	const static Color	Color_MediumOrchid		(	0.576471f,	0.439216f,	0.858824f,	1.000000f);
	const static Color	Color_MediumSeaGreen	(	0.258824f,	0.435294f,	0.258824f,	1.000000f);
	const static Color	Color_MediumSlateBlue	(	0.498039f,	0.000000f,	1.000000f,	1.000000f);
	const static Color	Color_MediumSpringGreen	(	0.498039f,	1.000000f,	0.000000f,	1.000000f);
	const static Color	Color_MediumTurquoise	(	0.439216f,	0.858824f,	0.858824f,	1.000000f);
	const static Color	Color_MediumVioletRed	(	0.858824f,	0.439216f,	0.576471f,	1.000000f);
	const static Color	Color_MidnightBlue		(	0.184314f,	0.184314f,	0.309804f,	1.000000f);
	const static Color	Color_Navy				(	0.137255f,	0.137255f,	0.556863f,	1.000000f);
	const static Color	Color_NavyBlue			(	0.137255f,	0.137255f,	0.556863f,	1.000000f);
	const static Color	Color_Orange			(	0.800000f,	0.196078f,	0.196078f,	1.000000f);
	const static Color	Color_OrangeRed			(	0.000000f,	0.000000f,	0.498039f,	1.000000f);
	const static Color	Color_Orchid			(	0.858824f,	0.439216f,	0.858824f,	1.000000f);
	const static Color	Color_PaleGreen			(	0.560784f,	0.737255f,	0.560784f,	1.000000f);
	const static Color	Color_Pink				(	0.737255f,	0.560784f,	0.560784f,	1.000000f);
	const static Color	Color_Plum				(	0.917647f,	0.678431f,	0.917647f,	1.000000f);
	const static Color	Color_Salmon			(	0.435294f,	0.258824f,	0.258824f,	1.000000f);
	const static Color	Color_SeaGreen			(	0.137255f,	0.556863f,	0.419608f,	1.000000f);
	const static Color	Color_Sienna			(	0.556863f,	0.419608f,	0.137255f,	1.000000f);
	const static Color	Color_SkyBlue			(	0.196078f,	0.600000f,	0.800000f,	1.000000f);
	const static Color	Color_SlateBlue			(	0.000000f,	0.498039f,	1.000000f,	1.000000f);
	const static Color	Color_SpringGreen		(	0.000000f,	1.000000f,	0.498039f,	1.000000f);
	const static Color	Color_SteelBlue			(	0.137255f,	0.419608f,	0.556863f,	1.000000f);
	const static Color	Color_Tan				(	0.858824f,	0.576471f,	0.439216f,	1.000000f);
	const static Color	Color_Thistle			(	0.847059f,	0.749020f,	0.847059f,	1.000000f);
	const static Color	Color_Turquoise			(	0.678431f,	0.917647f,	0.917647f,	1.000000f);
	const static Color	Color_Violet			(	0.309804f,	0.184314f,	0.309804f,	1.000000f);
	const static Color	Color_VioletRed			(	0.800000f,	0.196078f,	0.600000f,	1.000000f);
	const static Color	Color_Wheat				(	0.847059f,	0.847059f,	0.749020f,	1.000000f);
	const static Color	Color_YellowGreen		(	0.600000f,	0.800000f,	0.196078f,	1.000000f);

}; // end of namespace

#endif

