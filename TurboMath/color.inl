
// -------------------------------------------------------------------
// File			:	Color.inl
//
// Project		:	TurboMath
//
// Description	:	Inline-Code for Color-Class
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

#define		I3D_COLOR_CONV  0.003921568627450980392156862745098f // = 1/255					// Für umrechnen der Farben in Byte-Werte



/****************************************************************************
 *
 * Color
 *
 ****************************************************************************/

namespace TurboMath
{
		__forceinline Color::Color()
		{
		}

		__forceinline Color::Color(const Color& c)
		{
			color = c.color;
		}

		__forceinline Color::Color(const float f)
		{
			SetRGBA(f,f,f,1.0f);
		}

		__forceinline Color::Color(const float _r, const float _g, const float _b)
		{
			SetRGBA(_r,_g,_b,1.0f);
		}

		__forceinline Color::Color(const float _r, const float _g, const float _b, const float _a)
		{
			SetRGBA(_r,_g,_b,_a);
		}

		__forceinline Color::Color(const float* pfComponent)
		{
			SetRGBA( pfComponent[0], pfComponent[1], pfComponent[2], pfComponent[3]);
		}

		__forceinline Color::Color(const char _r, const char _g, const char _b)
		{
			SetRGBA( (float)(_r) * I3D_COLOR_CONV, (float)(_g) * I3D_COLOR_CONV, (float)(_b) * I3D_COLOR_CONV, 1.0f );
		}

		__forceinline Color::Color(const char _r, const char _g, const char _b, const char _a) 
		{
			SetRGBA( (float)(_r) * I3D_COLOR_CONV, (float)(_g) * I3D_COLOR_CONV, (float)(_b) * I3D_COLOR_CONV, (float)(_a) * I3D_COLOR_CONV);	
		}

		__forceinline Color::Color(const char* pComponent)
		{
			SetRGBA( (float)(pComponent[0]) * I3D_COLOR_CONV, (float)(pComponent[1]) * I3D_COLOR_CONV, (float)(pComponent[2]) * I3D_COLOR_CONV, (float)(pComponent[3]) * I3D_COLOR_CONV );
		}

		__forceinline Color::Color(const Vector4& rhs)
		{
			color = rhs;
		}

		__forceinline Color::Color(const XMVECTOR& rhs)
		{
			color = rhs;
		}

		__forceinline Color::Color(uint16_t r, uint16_t g, uint16_t b, uint16_t a, uint16_t bitDepth)
		{
			color = XMVectorScale(XMVectorSet(r, g, b, a), 1.0f / ((1 << bitDepth) - 1));
		}

		__forceinline Color::Color(uint32_t u32)
		{
			float r = (float)((u32 >> 0) & 0xFF);
			float g = (float)((u32 >> 8) & 0xFF);
			float b = (float)((u32 >> 16) & 0xFF);
			float a = (float)((u32 >> 24) & 0xFF);
			color = XMVectorScale(XMVectorSet(r, g, b, a), 1.0f / 255.0f);
		}
		//------------------------------------------------------------
		// assignment
		// -----------------------------------------------------------

		/// assignment operator
		__forceinline void Color::operator=(  Color& rhs)
		{
			color = rhs.color;
		}

		/// assign an XMFLOAT4
		__forceinline void Color::operator=( XMFLOAT4 rhs)
		{
			SetRGBA(rhs.x,rhs.y,rhs.z,rhs.w);
		}

		/// assign a float
		__forceinline Color Color::operator=( float f)
		{
			SetRGBA(f,f,f,1.0f);
			return *this;
		}

		/// assign a XMVECTOR
		__forceinline void Color::operator=( XMVECTOR rhs)
		{
			color = rhs;
		}


		/// Set Red
		__forceinline void Color::SetR(const float red)
		{
			this->color = XMVectorSetXPtr(this->color, &red);
		}

		/// Set Green
		__forceinline void Color::SetG(const float green)
		{
			this->color = XMVectorSetYPtr(this->color, &green);
		}

		/// Set Blue
		__forceinline void Color::SetB(const float blue)
		{
			this->color = XMVectorSetZPtr(this->color, &blue);
		}

		/// Set Alpha
		__forceinline void Color::SetA(const float alpha)
		{
			this->color = XMVectorSetWPtr(this->color, &alpha);
		}

		/// Set RGB
		__forceinline void Color::SetRGB(const float red,const float green, const float blue)
		{
			this->color = XMVectorSet(red, green, blue, 1.0f);
		}

		/// Set RGBA
		__forceinline void Color::SetRGBA(const float red,const float green, const float blue, const float alpha)
		{
			this->color = XMVectorSet(red, green, blue, alpha);
		}

		/// Get Red
		__forceinline const float Color::GetR() const
		{
			float r;
			XMVectorGetXPtr(&r, color);
			return r;
		}

		/// Get Green
		__forceinline const float Color::GetG() const
		{
			float g;
			XMVectorGetYPtr(&g, color);
			return g;
		}

		/// Get Blue
		__forceinline const float Color::GetB() const
		{
			float b;
			XMVectorGetZPtr(&b, color);
			return b;
		}

		/// Get Alpha
		__forceinline const float Color::GetA() const
		{
			float a;
			XMVectorGetWPtr(&a, color);
			return a;
		}

		/// Get as DWORD
		__forceinline const DWORD Color::GetAsDWORD() const
		{
			return DWORD (PackedVector::XMCOLOR((float*)&color) );
		}

		/// Get as XMFLOAT4
		__forceinline const XMFLOAT4 Color::GetAsXMFLOAT4() const
		{
			XMFLOAT4 tmp;
			XMStoreFloat4(&tmp,color);
			return tmp;
		}

		//------------------------------------------------------------------------------
		__forceinline XMVECTOR Color::GetRaw() const
		{
			return this->color;
		}

		//------------------------------------------------------------------------------
		__forceinline XMVECTOR* Color::GetRawPtr()
		{
			return &this->color;
		}

		//------------------------------------------------------------------------------
		__forceinline float*	Color::GetFloatPtr()
		{
			return (float*)&color; 
		}

		__forceinline void Color::Clamp()
		{
			if (GetR() > 1.0f) SetR(1.0f);
			if (GetG() > 1.0f) SetG(1.0f);
			if (GetB() > 1.0f) SetB(1.0f);
			if (GetA() > 1.0f) SetA(1.0f);

			if (GetR() < 0.0f) SetR(0.0f);
			if (GetG() < 0.0f) SetG(0.0f);
			if (GetB() < 0.0f) SetB(0.0f);
			if (GetA() < 0.0f) SetA(0.0f);
		}


		__forceinline Color& Color::operator += (const Color& c) 
		{
			this->color = XMVectorAdd(this->color, c.color);

			return( *this );
		}

		__forceinline Color& Color::operator -= (const Color& c) 
		{
			this->color = XMVectorSubtract(this->color, c.color);

			return( *this );
		}

		__forceinline Color& Color::operator *= (const Color& c) 
		{
			this->color = XMVectorMultiply(this->color, c.color);

			return( *this );
		}

		__forceinline Color& Color::operator *= (const float f) 
		{
			this->color = XMVectorScale(this->color, f);

			return( *this );
		}

		__forceinline Color& Color::operator /= (const Color& c) 
		{
			const float r = c.GetR() != 0.0f ? this->GetR() / c.GetR() : 0.0f;
			const float g = c.GetG() != 0.0f ? this->GetG() / c.GetG() : 0.0f;
			const float b = c.GetB() != 0.0f ? this->GetB() / c.GetB() : 0.0f;
			const float a = c.GetA() != 0.0f ? this->GetA() / c.GetA() : 0.0f;

			this->SetRGBA(r,g,b,a);

			return( *this );
		}

		__forceinline Color& Color::operator /= (const float f) 
		{
			// Add simple Data ti the float, so we don´t have a Division by Zero!
			const float div = f + 0.000001f;

			SetR(this->GetR() / div);
			SetG(this->GetG() / div);
			this->SetB(this->GetB() / div);
			this->SetA(this->GetA() / div);

			return( *this );
		}


		__forceinline Color Color::operator + (const Color& a) const
		{
			return Color(XMVectorAdd(this->color, a.color));
		}

		__forceinline Color Color::operator - (const Color& a) const
		{
			return Color(XMVectorSubtract(this->color, a.color));
		}

		__forceinline Color Color::operator * (const Color& a) const
		{
			return Color( XMVectorMultiply(this->color, a.color) );
		}

		__forceinline Color Color::operator * (const float f) const
		{
			return Color(XMVectorScale(this->color, f));
		}

		__forceinline Color Color::operator / (const Color& a) const
		{
			// Add simple Data ti the float, so we don´t have a Division by Zero!
			const float divr = a.GetR() + 0.000001f;
			const float divg = a.GetG() + 0.000001f;
			const float divb = a.GetB() + 0.000001f;
			const float diva = a.GetA() + 0.000001f;

			const float r = this->GetR() / divr;
			const float g = this->GetG() / divg;
			const float b = this->GetB() / divb;
			const float alpha = this->GetA() / diva;
			
			return Color(r,g,b,alpha);
		}

		__forceinline Color Color::operator / ( const float f) const
		{
			// Add simple Data ti the float, so we don´t have a Division by Zero!
			const float div = f + 0.000001f;

			const float r = this->GetR() / div;
			const float g = this->GetG() / div;
			const float b = this->GetB() / div;
			const float a = this->GetA() / div;

			return Color(r,g,b,a);
		}


		__forceinline bool Color::operator == (const Color& a) const
		{
			return (0 != XMVector4Equal(this->color, a.color));
		}

		__forceinline bool Color::operator != (const Color& a) const
		{
			return (0 != XMVector4NotEqual(this->color, a.color));
		}


		__forceinline Color& Color::operator=(const Vector4 &rhs) 
		{
			this->color = rhs.GetRaw();

			return( *this );
		}

		/// Functions

		__forceinline unsigned char Color::Pack_RGB332() const
		{
			static_assert(sizeof(Color) == 16, "Class TurboMath::Color wrong size");

			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);
		
			return ((cr >> 5) << 5) | ((cg >> 5) << 2) | (cb >> 5);
		}

		__forceinline unsigned short Color::Pack_ARGB4444() const
		{
			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);
			const unsigned char ca = (unsigned char)(GetA() * 255.0f);
	
			return ((ca >> 4) << 12) | ((cr >> 4) << 8) | ((cg >> 4) << 4) | (cb >> 4);
		}

		__forceinline unsigned short Color::Pack_RGB555() const
		{
			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);

			return ((cr >> 3) << 10) | ((cg >> 3) << 5) | (cb >> 3);
		}

		__forceinline unsigned short Color::Pack_RGB565() const
		{
			const unsigned char cr = (unsigned short)(GetR() * 255.0f);
			const unsigned char cg = (unsigned short)(GetG() * 255.0f);
			const unsigned char cb = (unsigned short)(GetB() * 255.0f);
			
			return ((cr >> 3) << 11) |	((cg >> 2) << 5) | (cb >> 3);
		}

		__forceinline unsigned int Color::Pack_RGB888() const
		{
			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);
		
			return (cr << 16) | (cg << 8) | cb;
		}

		__forceinline unsigned int Color::Pack_ABGR8888() const
		{
			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);
			const unsigned char ca = (unsigned char)(GetA() * 255.0f);
	
			return (ca << 24) | (cb << 16) | (cg << 8) | cr;
		}

		__forceinline unsigned int Color::Pack_ARGB8888() const
		{
		
			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);
			const unsigned char ca = (unsigned char)(GetA() * 255.0f);
			
			return (ca << 24) | (cr << 16) | (cg << 8) | cb;
		}

		__forceinline void Color::Clamp(const float bottom, const float top)
		{
			if(GetR() < bottom)		SetR(bottom);
			else if(GetR() > top)	SetR(top);

			if(GetG() < bottom)		SetG(bottom);
			else if(GetG() > top)	SetG(top);

			if(GetB() < bottom)		SetB(bottom);
			else if(GetB() > top)	SetB(top);
			
			if(GetA() < bottom)		SetA(bottom);
			else if(GetA() > top)	SetA(top);
		}

		__forceinline void Color::AdjustContrast(const float c)
		{
			SetR( 0.5f + c * (GetR() - 0.5f) );
			SetG( 0.5f + c * (GetG() - 0.5f) );
			SetB( 0.5f + c * (GetB() - 0.5f) );
			SetA( 0.5f + c * (GetA() - 0.5f) );
		}

		__forceinline void Color::AdjustSaturation(const float s)
		{
			// Approximate values for each component's contribution to luminance.
			// Based upon the NTSC standard described in ITU-R Recommendation BT.709.
			const float grey = GetR() * 0.2125f + GetG() * 0.7154f + GetB() * 0.0721f;

			SetR(grey + s * (GetR() - grey));
			SetG(grey + s * (GetG() - grey));
			SetB(grey + s * (GetB() - grey));
			SetA(grey + s * (GetA() - grey));
		}

		__forceinline void Color::LerpFloat(const Color& ca, const Color& cb, float s)
		{
			SetR( ca.GetR() + s * (cb.GetR() - ca.GetR() ) );
			SetG( ca.GetG() + s * (cb.GetG() - ca.GetG() ) );
			SetB( ca.GetB() + s * (cb.GetB() - ca.GetB() ) );
			SetA( ca.GetA() + s * (cb.GetA() - ca.GetA() ) );
		}

		__forceinline void Color::Negative()
		{
			SetR( 1.0f - GetR() );
			SetG( 1.0f - GetG() );
			SetB( 1.0f - GetB() );
			SetA( 1.0f - GetA() );
		}

		__forceinline void Color::Grey()
		{
			const float m = (GetR() + GetG() + GetB()) / 3.0f;

			SetRGBA(m,m,m,GetA());
		}

		__forceinline unsigned int Color::toARGB( )
		{
			unsigned int result = 0;

			Clamp();

			result += (unsigned int)(255 * GetB());
			result += ((unsigned int)(255 * GetG()) << 8);
			result += ((unsigned int)(255 * GetR()) << 16);
			result += ((unsigned int)(255 * GetA()) << 24);

			return( result );
		}

		__forceinline unsigned int Color::toRGBA( )
		{
			unsigned int result = 0;

			Clamp();

			result += (unsigned int)(255 * GetA());
			result += ((unsigned int)(255 * GetB()) << 8);
			result += ((unsigned int)(255 * GetG()) << 16);
			result += ((unsigned int)(255 * GetR()) << 24);

			return( result );
		}

		__forceinline void Color::fromARGB( unsigned int color )
		{
			SetR( (float)((color & 0x00ff0000) >> 16)/(255.0f) );	// red channel
			SetG( (float)((color & 0x0000ff00) >> 8)/(255.0f) );	// green channel
			SetB( (float)((color & 0x000000ff))/(255.0f) );			// blue channel
			SetA( (float)((color & 0xff000000) >> 24)/(255.0f) );	// alpha channel
		}


		__forceinline float	Brightness(const Color& c)	
		{
			return c.GetR() * 0.299f + c.GetG() * 0.587f + c.GetB() * 0.114f;
		}

		__forceinline Color Interpolate( Color& c1,  Color& c2, const float p)
		{
			return c1 + (c2 - c1) * p;
		}

		__forceinline Color	Min(const Color& c1, const Color& c2)		
		{
			return Color(TB_min(c1.GetR(), c2.GetR()), TB_min(c1.GetG(), c2.GetG()), TB_min(c1.GetB(), c2.GetB()), TB_min(c1.GetA(), c2.GetA()));
		}

		__forceinline Color Max(const Color& c1, const Color& c2)				
		{
			return Color(TB_max(c1.GetR(), c2.GetR()), TB_max(c1.GetG(), c2.GetG()), TB_max(c1.GetB(), c2.GetB()), TB_max(c1.GetA(), c2.GetA()));
		}

		__forceinline Color	Random(const float fAlpha)		
		{
			return Color(Rand(0.0f, 1.0f), Rand(0.0f, 1.0f), Rand(0.0f, 1.0f), fAlpha < 0.0f ? Rand(0.0f, 1.0f) : fAlpha);
		}

		__forceinline Color Color::ToSRGB(void) const
		{
			XMVECTOR T = XMVectorSaturate(color);
			XMVECTOR result = XMVectorSubtract(XMVectorScale(XMVectorPow(T, XMVectorReplicate(1.0f / 2.4f)), 1.055f), XMVectorReplicate(0.055f));
			result = XMVectorSelect(result, XMVectorScale(T, 12.92f), XMVectorLess(T, XMVectorReplicate(0.0031308f)));
			return Color(XMVectorSelect(T, result, g_XMSelect1110));
		}

		__forceinline Color Color::FromSRGB(void) const
		{
			XMVECTOR T = XMVectorSaturate(color);
			XMVECTOR result = XMVectorPow(XMVectorScale(XMVectorAdd(T, XMVectorReplicate(0.055f)), 1.0f / 1.055f), XMVectorReplicate(2.4f));
			result = XMVectorSelect(result, XMVectorScale(T, 1.0f / 12.92f), XMVectorLess(T, XMVectorReplicate(0.0031308f)));
			return Color(XMVectorSelect(T, result, g_XMSelect1110));
		}

		__forceinline Color Color::ToREC709(void) const
		{
			XMVECTOR T = XMVectorSaturate(color);
			XMVECTOR result = XMVectorSubtract(XMVectorScale(XMVectorPow(T, XMVectorReplicate(0.45f)), 1.099f), XMVectorReplicate(0.099f));
			result = XMVectorSelect(result, XMVectorScale(T, 4.5f), XMVectorLess(T, XMVectorReplicate(0.0018f)));
			return Color(XMVectorSelect(T, result, g_XMSelect1110));
		}

		__forceinline Color Color::FromREC709(void) const
		{
			XMVECTOR T = XMVectorSaturate(color);
			XMVECTOR result = XMVectorPow(XMVectorScale(XMVectorAdd(T, XMVectorReplicate(0.099f)), 1.0f / 1.099f), XMVectorReplicate(1.0f / 0.45f));
			result = XMVectorSelect(result, XMVectorScale(T, 1.0f / 4.5f), XMVectorLess(T, XMVectorReplicate(0.0081f)));
			return Color(XMVectorSelect(T, result, g_XMSelect1110));
		}

		__forceinline uint32_t Color::R10G10B10A2(void) const
		{
			XMVECTOR result = XMVectorRound(XMVectorMultiply(XMVectorSaturate(color), XMVectorSet(1023.0f, 1023.0f, 1023.0f, 3.0f)));
			result = _mm_castsi128_ps(_mm_cvttps_epi32(result));
			uint32_t r = XMVectorGetIntX(result);
			uint32_t g = XMVectorGetIntY(result);
			uint32_t b = XMVectorGetIntZ(result);
			uint32_t a = XMVectorGetIntW(result) >> 8;
			return a << 30 | b << 20 | g << 10 | r;
		}

		__forceinline uint32_t Color::R8G8B8A8(void) const
		{
			XMVECTOR result = XMVectorRound(XMVectorMultiply(XMVectorSaturate(color), XMVectorReplicate(255.0f)));
			result = _mm_castsi128_ps(_mm_cvttps_epi32(result));
			uint32_t r = XMVectorGetIntX(result);
			uint32_t g = XMVectorGetIntY(result);
			uint32_t b = XMVectorGetIntZ(result);
			uint32_t a = XMVectorGetIntW(result);
			return a << 24 | b << 16 | g << 8 | r;
		}

/*		__forceinline Color& Color::operator /= (const Color& c)
		{
			const float r = c.R() != 0.0f ? this->R() / c.R() : 0.0f;
			const float g = c.G() != 0.0f ? this->G() / c.G() : 0.0f;
			const float b = c.B() != 0.0f ? this->B() / c.B() : 0.0f;
			const float a = c.A() != 0.0f ? this->A() / c.A() : 0.0f;

			this->SetRGBA(r, g, b, a);

			return(*this);
		}
*/
/*		__forceinline Color& Color::operator /= (const float f)
		{
			// Add simple Data ti the float, so we don´t have a Division by Zero!
			const float div = f + 0.000001f;

			this->SetR(this->R() / div);
			this->SetG(this->G() / div);
			this->SetB(this->B() / div);
			this->SetA(this->A() / div);

			return(*this);
		}
*/
};// Namespace

