
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
		XM_INLINE Color::Color() noexcept
		{
		}

		XM_INLINE Color::Color(const Color& c) noexcept
		{
			color = c.color;
		}

		XM_INLINE Color::Color(const float f) noexcept
		{
			SetRGBA(f,f,f,1.0f);
		}

		XM_INLINE Color::Color(const float _r, const float _g, const float _b) noexcept
		{
			SetRGBA(_r,_g,_b,1.0f);
		}

		XM_INLINE Color::Color(const float _r, const float _g, const float _b, const float _a) noexcept
		{
			SetRGBA(_r,_g,_b,_a);
		}

		XM_INLINE Color::Color(const float* pfComponent) noexcept
		{
			SetRGBA( pfComponent[0], pfComponent[1], pfComponent[2], pfComponent[3]);
		}

		XM_INLINE Color::Color(const char _r, const char _g, const char _b) noexcept
		{
			SetRGBA( (float)(_r) * I3D_COLOR_CONV, (float)(_g) * I3D_COLOR_CONV, (float)(_b) * I3D_COLOR_CONV, 1.0f );
		}

		XM_INLINE Color::Color(const char _r, const char _g, const char _b, const char _a)  noexcept
		{
			SetRGBA( (float)(_r) * I3D_COLOR_CONV, (float)(_g) * I3D_COLOR_CONV, (float)(_b) * I3D_COLOR_CONV, (float)(_a) * I3D_COLOR_CONV);	
		}

		XM_INLINE Color::Color(const char* pComponent) noexcept
		{
			SetRGBA( (float)(pComponent[0]) * I3D_COLOR_CONV, (float)(pComponent[1]) * I3D_COLOR_CONV, (float)(pComponent[2]) * I3D_COLOR_CONV, (float)(pComponent[3]) * I3D_COLOR_CONV );
		}

		XM_INLINE Color::Color(const Vector4& rhs) noexcept
		{
			color = rhs;
		}

		XM_INLINE Color::Color(const XMVECTOR& rhs) noexcept
		{
			color = rhs;
		}

		XM_INLINE Color::Color(uint16_t r, uint16_t g, uint16_t b, uint16_t a, uint16_t bitDepth) noexcept
		{
			color = XMVectorScale(XMVectorSet(r, g, b, a), 1.0f / ((1 << bitDepth) - 1));
		}

		XM_INLINE Color::Color(uint32_t u32) noexcept
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
		XM_INLINE void  XM_CALLCONV Color::operator=(  Color& rhs) noexcept
		{
			color = rhs.color;
		}

		/// assign an XMFLOAT4
		XM_INLINE void  XM_CALLCONV Color::operator=( XMFLOAT4 rhs) noexcept
		{
			SetRGBA(rhs.x,rhs.y,rhs.z,rhs.w);
		}

		/// assign a float
		XM_INLINE Color  XM_CALLCONV Color::operator=( float f) noexcept
		{
			SetRGBA(f,f,f,1.0f);
			return *this;
		}

		/// assign a XMVECTOR
		XM_INLINE void  XM_CALLCONV Color::operator=( XMVECTOR rhs) noexcept
		{
			color = rhs;
		}


		/// Set Red
		XM_INLINE void  XM_CALLCONV Color::SetR(const float red) noexcept
		{
			this->color = XMVectorSetXPtr(this->color, &red);
		}

		/// Set Green
		XM_INLINE void  XM_CALLCONV Color::SetG(const float green) noexcept
		{
			this->color = XMVectorSetYPtr(this->color, &green);
		}

		/// Set Blue
		XM_INLINE void  XM_CALLCONV Color::SetB(const float blue) noexcept
		{
			this->color = XMVectorSetZPtr(this->color, &blue);
		}

		/// Set Alpha
		XM_INLINE void  XM_CALLCONV Color::SetA(const float alpha) noexcept
		{
			this->color = XMVectorSetWPtr(this->color, &alpha);
		}

		/// Set RGB
		XM_INLINE void  XM_CALLCONV Color::SetRGB(const float red,const float green, const float blue) noexcept
		{
			this->color = XMVectorSet(red, green, blue, 1.0f);
		}

		/// Set RGBA
		XM_INLINE void  XM_CALLCONV Color::SetRGBA(const float red,const float green, const float blue, const float alpha) noexcept
		{
			this->color = XMVectorSet(red, green, blue, alpha);
		}

		/// Get Red
		XM_INLINE const float XM_CALLCONV  Color::GetR() const noexcept
		{
			float r;
			XMVectorGetXPtr(&r, color);
			return r;
		}

		/// Get Green
		XM_INLINE const float XM_CALLCONV  Color::GetG() const noexcept
		{
			float g;
			XMVectorGetYPtr(&g, color);
			return g;
		}

		/// Get Blue
		XM_INLINE const float XM_CALLCONV  Color::GetB() const noexcept
		{
			float b;
			XMVectorGetZPtr(&b, color);
			return b;
		}

		/// Get Alpha
		XM_INLINE const float XM_CALLCONV  Color::GetA() const noexcept
		{
			float a;
			XMVectorGetWPtr(&a, color);
			return a;
		}

		/// Get as DWORD
		XM_INLINE const DWORD  XM_CALLCONV Color::GetAsDWORD() const noexcept
		{
			return DWORD (PackedVector::XMCOLOR((float*)&color) );
		}

		/// Get as XMFLOAT4
		XM_INLINE const XMFLOAT4 XM_CALLCONV  Color::GetAsXMFLOAT4() const noexcept
		{
			XMFLOAT4 tmp;
			XMStoreFloat4(&tmp,color);
			return tmp;
		}

		//------------------------------------------------------------------------------
		XM_INLINE XMVECTOR XM_CALLCONV  Color::GetRaw() const noexcept
		{
			return this->color;
		}

		//------------------------------------------------------------------------------
		XM_INLINE XMVECTOR* XM_CALLCONV  Color::GetRawPtr() noexcept
		{
			return &this->color;
		}

		//------------------------------------------------------------------------------
		XM_INLINE float* XM_CALLCONV 	Color::GetFloatPtr() noexcept
		{
			return (float*)&color; 
		}

		XM_INLINE void  XM_CALLCONV Color::Clamp() noexcept
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


		XM_INLINE Color& XM_CALLCONV  Color::operator += (const Color& c)  noexcept
		{
			this->color = XMVectorAdd(this->color, c.color);

			return( *this );
		}

		XM_INLINE Color& XM_CALLCONV Color::operator -= (const Color& c)  noexcept
		{
			this->color = XMVectorSubtract(this->color, c.color);

			return( *this );
		}

		XM_INLINE Color&  XM_CALLCONV Color::operator *= (const Color& c)  noexcept
		{
			this->color = XMVectorMultiply(this->color, c.color);

			return( *this );
		}

		XM_INLINE Color& XM_CALLCONV  Color::operator *= (const float f)  noexcept
		{
			this->color = XMVectorScale(this->color, f);

			return( *this );
		}

		XM_INLINE Color&  XM_CALLCONV Color::operator /= (const Color& c)  noexcept
		{
			const float r = c.GetR() != 0.0f ? this->GetR() / c.GetR() : 0.0f;
			const float g = c.GetG() != 0.0f ? this->GetG() / c.GetG() : 0.0f;
			const float b = c.GetB() != 0.0f ? this->GetB() / c.GetB() : 0.0f;
			const float a = c.GetA() != 0.0f ? this->GetA() / c.GetA() : 0.0f;

			this->SetRGBA(r,g,b,a);

			return( *this );
		}

		XM_INLINE Color&  XM_CALLCONV Color::operator /= (const float f)  noexcept
		{
			// Add simple Data ti the float, so we don´t have a Division by Zero!
			const float div = f + 0.000001f;

			SetR(this->GetR() / div);
			SetG(this->GetG() / div);
			this->SetB(this->GetB() / div);
			this->SetA(this->GetA() / div);

			return( *this );
		}


		XM_INLINE Color  XM_CALLCONV Color::operator + (const Color& a) const noexcept
		{
			return Color(XMVectorAdd(this->color, a.color));
		}

		XM_INLINE Color XM_CALLCONV  Color::operator - (const Color& a) const noexcept
		{
			return Color(XMVectorSubtract(this->color, a.color));
		}

		XM_INLINE Color XM_CALLCONV  Color::operator * (const Color& a) const noexcept
		{
			return Color( XMVectorMultiply(this->color, a.color) );
		}

		XM_INLINE Color XM_CALLCONV  Color::operator * (const float f) const noexcept
		{
			return Color(XMVectorScale(this->color, f));
		}

		XM_INLINE Color XM_CALLCONV  Color::operator / (const Color& a) const noexcept
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

		XM_INLINE Color XM_CALLCONV  Color::operator / ( const float f) const noexcept
		{
			// Add simple Data ti the float, so we don´t have a Division by Zero!
			const float div = f + 0.000001f;

			const float r = this->GetR() / div;
			const float g = this->GetG() / div;
			const float b = this->GetB() / div;
			const float a = this->GetA() / div;

			return Color(r,g,b,a);
		}


		XM_INLINE bool XM_CALLCONV  Color::operator == (const Color& a) const noexcept
		{
			return (0 != XMVector4Equal(this->color, a.color));
		}

		XM_INLINE bool XM_CALLCONV  Color::operator != (const Color& a) const noexcept
		{
			return (0 != XMVector4NotEqual(this->color, a.color));
		}


		XM_INLINE Color& XM_CALLCONV  Color::operator=(const Vector4 &rhs)  noexcept
		{
			this->color = rhs.GetRaw();

			return( *this );
		}

		/// Functions

		XM_INLINE unsigned char XM_CALLCONV  Color::Pack_RGB332() const
		{
			static_assert(sizeof(Color) == 16, "Class TurboMath::Color wrong size");

			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);
		
			return ((cr >> 5) << 5) | ((cg >> 5) << 2) | (cb >> 5);
		}

		XM_INLINE unsigned short XM_CALLCONV  Color::Pack_ARGB4444() const noexcept
		{
			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);
			const unsigned char ca = (unsigned char)(GetA() * 255.0f);
	
			return ((ca >> 4) << 12) | ((cr >> 4) << 8) | ((cg >> 4) << 4) | (cb >> 4);
		}

		XM_INLINE unsigned short XM_CALLCONV  Color::Pack_RGB555() const noexcept
		{
			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);

			return ((cr >> 3) << 10) | ((cg >> 3) << 5) | (cb >> 3);
		}

		XM_INLINE unsigned short  XM_CALLCONV Color::Pack_RGB565() const noexcept
		{
			const unsigned char cr = (unsigned short)(GetR() * 255.0f);
			const unsigned char cg = (unsigned short)(GetG() * 255.0f);
			const unsigned char cb = (unsigned short)(GetB() * 255.0f);
			
			return ((cr >> 3) << 11) |	((cg >> 2) << 5) | (cb >> 3);
		}

		XM_INLINE unsigned int XM_CALLCONV  Color::Pack_RGB888() const noexcept
		{
			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);
		
			return (cr << 16) | (cg << 8) | cb;
		}

		XM_INLINE unsigned int XM_CALLCONV  Color::Pack_ABGR8888() const noexcept
		{
			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);
			const unsigned char ca = (unsigned char)(GetA() * 255.0f);
	
			return (ca << 24) | (cb << 16) | (cg << 8) | cr;
		}

		XM_INLINE unsigned int XM_CALLCONV  Color::Pack_ARGB8888() const noexcept
		{
		
			const unsigned char cr = (unsigned char)(GetR() * 255.0f);
			const unsigned char cg = (unsigned char)(GetG() * 255.0f);
			const unsigned char cb = (unsigned char)(GetB() * 255.0f);
			const unsigned char ca = (unsigned char)(GetA() * 255.0f);
			
			return (ca << 24) | (cr << 16) | (cg << 8) | cb;
		}

		XM_INLINE void XM_CALLCONV  Color::Clamp(const float bottom, const float top) noexcept
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

		XM_INLINE void XM_CALLCONV  Color::AdjustContrast(const float c) noexcept
		{
			SetR( 0.5f + c * (GetR() - 0.5f) );
			SetG( 0.5f + c * (GetG() - 0.5f) );
			SetB( 0.5f + c * (GetB() - 0.5f) );
			SetA( 0.5f + c * (GetA() - 0.5f) );
		}

		XM_INLINE void  XM_CALLCONV Color::AdjustSaturation(const float s) noexcept
		{
			// Approximate values for each component's contribution to luminance.
			// Based upon the NTSC standard described in ITU-R Recommendation BT.709.
			const float grey = GetR() * 0.2125f + GetG() * 0.7154f + GetB() * 0.0721f;

			SetR(grey + s * (GetR() - grey));
			SetG(grey + s * (GetG() - grey));
			SetB(grey + s * (GetB() - grey));
			SetA(grey + s * (GetA() - grey));
		}

		XM_INLINE void XM_CALLCONV  Color::LerpFloat(const Color& ca, const Color& cb, float s) noexcept
		{
			SetR( ca.GetR() + s * (cb.GetR() - ca.GetR() ) );
			SetG( ca.GetG() + s * (cb.GetG() - ca.GetG() ) );
			SetB( ca.GetB() + s * (cb.GetB() - ca.GetB() ) );
			SetA( ca.GetA() + s * (cb.GetA() - ca.GetA() ) );
		}

		XM_INLINE void XM_CALLCONV  Color::Negative() noexcept
		{
			SetR( 1.0f - GetR() );
			SetG( 1.0f - GetG() );
			SetB( 1.0f - GetB() );
			SetA( 1.0f - GetA() );
		}

		XM_INLINE void XM_CALLCONV  Color::Grey() noexcept
		{
			const float m = (GetR() + GetG() + GetB()) / 3.0f;

			SetRGBA(m,m,m,GetA());
		}

		XM_INLINE unsigned int XM_CALLCONV  Color::toARGB( ) noexcept
		{
			unsigned int result = 0;

			Clamp();

			result += (unsigned int)(255 * GetB());
			result += ((unsigned int)(255 * GetG()) << 8);
			result += ((unsigned int)(255 * GetR()) << 16);
			result += ((unsigned int)(255 * GetA()) << 24);

			return( result );
		}

		XM_INLINE unsigned int XM_CALLCONV  Color::toRGBA( ) noexcept
		{
			unsigned int result = 0;

			Clamp();

			result += (unsigned int)(255 * GetA());
			result += ((unsigned int)(255 * GetB()) << 8);
			result += ((unsigned int)(255 * GetG()) << 16);
			result += ((unsigned int)(255 * GetR()) << 24);

			return( result );
		}

		XM_INLINE void XM_CALLCONV  Color::fromARGB( unsigned int color ) noexcept
		{
			SetR( (float)((color & 0x00ff0000) >> 16)/(255.0f) );	// red channel
			SetG( (float)((color & 0x0000ff00) >> 8)/(255.0f) );	// green channel
			SetB( (float)((color & 0x000000ff))/(255.0f) );			// blue channel
			SetA( (float)((color & 0xff000000) >> 24)/(255.0f) );	// alpha channel
		}


		XM_INLINE float XM_CALLCONV 	Brightness(const Color& c)	 noexcept
		{
			return c.GetR() * 0.299f + c.GetG() * 0.587f + c.GetB() * 0.114f;
		}

		XM_INLINE Color XM_CALLCONV  Interpolate( Color& c1,  Color& c2, const float p) noexcept
		{
			return c1 + (c2 - c1) * p;
		}

		XM_INLINE Color XM_CALLCONV 	Min(const Color& c1, const Color& c2)	 noexcept	
		{
			return Color(TB_min(c1.GetR(), c2.GetR()), TB_min(c1.GetG(), c2.GetG()), TB_min(c1.GetB(), c2.GetB()), TB_min(c1.GetA(), c2.GetA()));
		}

		XM_INLINE Color XM_CALLCONV  Max(const Color& c1, const Color& c2)	 noexcept			
		{
			return Color(TB_max(c1.GetR(), c2.GetR()), TB_max(c1.GetG(), c2.GetG()), TB_max(c1.GetB(), c2.GetB()), TB_max(c1.GetA(), c2.GetA()));
		}

		XM_INLINE Color XM_CALLCONV 	Random(const float fAlpha) noexcept		
		{
			return Color(Rand(0.0f, 1.0f), Rand(0.0f, 1.0f), Rand(0.0f, 1.0f), fAlpha < 0.0f ? Rand(0.0f, 1.0f) : fAlpha);
		}

		XM_INLINE Color XM_CALLCONV  Color::ToSRGB(void) const noexcept
		{
			XMVECTOR T = XMVectorSaturate(color);
			XMVECTOR result = XMVectorSubtract(XMVectorScale(XMVectorPow(T, XMVectorReplicate(1.0f / 2.4f)), 1.055f), XMVectorReplicate(0.055f));
			result = XMVectorSelect(result, XMVectorScale(T, 12.92f), XMVectorLess(T, XMVectorReplicate(0.0031308f)));
			return Color(XMVectorSelect(T, result, g_XMSelect1110));
		}

		XM_INLINE Color XM_CALLCONV  Color::FromSRGB(void) const noexcept
		{
			XMVECTOR T = XMVectorSaturate(color);
			XMVECTOR result = XMVectorPow(XMVectorScale(XMVectorAdd(T, XMVectorReplicate(0.055f)), 1.0f / 1.055f), XMVectorReplicate(2.4f));
			result = XMVectorSelect(result, XMVectorScale(T, 1.0f / 12.92f), XMVectorLess(T, XMVectorReplicate(0.0031308f)));
			return Color(XMVectorSelect(T, result, g_XMSelect1110));
		}

		XM_INLINE Color  XM_CALLCONV Color::ToREC709(void) const noexcept
		{
			XMVECTOR T = XMVectorSaturate(color);
			XMVECTOR result = XMVectorSubtract(XMVectorScale(XMVectorPow(T, XMVectorReplicate(0.45f)), 1.099f), XMVectorReplicate(0.099f));
			result = XMVectorSelect(result, XMVectorScale(T, 4.5f), XMVectorLess(T, XMVectorReplicate(0.0018f)));
			return Color(XMVectorSelect(T, result, g_XMSelect1110));
		}

		XM_INLINE Color XM_CALLCONV  Color::FromREC709(void) const noexcept
		{
			XMVECTOR T = XMVectorSaturate(color);
			XMVECTOR result = XMVectorPow(XMVectorScale(XMVectorAdd(T, XMVectorReplicate(0.099f)), 1.0f / 1.099f), XMVectorReplicate(1.0f / 0.45f));
			result = XMVectorSelect(result, XMVectorScale(T, 1.0f / 4.5f), XMVectorLess(T, XMVectorReplicate(0.0081f)));
			return Color(XMVectorSelect(T, result, g_XMSelect1110));
		}

		XM_INLINE uint32_t XM_CALLCONV  Color::R10G10B10A2(void) const noexcept
		{
			XMVECTOR result = XMVectorRound(XMVectorMultiply(XMVectorSaturate(color), XMVectorSet(1023.0f, 1023.0f, 1023.0f, 3.0f)));
			result = _mm_castsi128_ps(_mm_cvttps_epi32(result));
			uint32_t r = XMVectorGetIntX(result);
			uint32_t g = XMVectorGetIntY(result);
			uint32_t b = XMVectorGetIntZ(result);
			uint32_t a = XMVectorGetIntW(result) >> 8;
			return a << 30 | b << 20 | g << 10 | r;
		}

		XM_INLINE uint32_t XM_CALLCONV  Color::R8G8B8A8(void) const noexcept
		{
			XMVECTOR result = XMVectorRound(XMVectorMultiply(XMVectorSaturate(color), XMVectorReplicate(255.0f)));
			result = _mm_castsi128_ps(_mm_cvttps_epi32(result));
			uint32_t r = XMVectorGetIntX(result);
			uint32_t g = XMVectorGetIntY(result);
			uint32_t b = XMVectorGetIntZ(result);
			uint32_t a = XMVectorGetIntW(result);
			return a << 24 | b << 16 | g << 8 | r;
		}

/*		XM_INLINE Color& XM_CALLCONV  Color::operator /= (const Color& c) noexcept
		{
			const float r = c.R() != 0.0f ? this->R() / c.R() : 0.0f;
			const float g = c.G() != 0.0f ? this->G() / c.G() : 0.0f;
			const float b = c.B() != 0.0f ? this->B() / c.B() : 0.0f;
			const float a = c.A() != 0.0f ? this->A() / c.A() : 0.0f;

			this->SetRGBA(r, g, b, a);

			return(*this);
		}
*/
/*		XM_INLINE Color&  XM_CALLCONV Color::operator /= (const float f) noexcept
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

