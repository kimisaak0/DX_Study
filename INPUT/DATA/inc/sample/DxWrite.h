#pragma once
#include "stdHeader_L.h"

namespace Lypi
{
	class DxWrite
	{
	protected:
		FLOAT m_fDpiScaleX;                 //화면 스케일 (출력 영역의 크기를 지정할 때 사용된다.) 
		FLOAT m_fDpiScaleY;                 //화면 스케일 (출력 영역의 크기를 지정할 때 사용된다.)
		FLOAT m_FDpiX;                      //화면의 인치당 도트수 (요즘 모니터는 대부분 96.0F이다.)
		FLOAT m_FDpiY;                      //화면의 인치당 도트수 (요즘 모니터는 대부분 96.0F이다.)

		//DXGI에 독립적인 객체
		ID2D1Factory* m_pD2dFactory;       //d2d 팩토리
		IDWriteFactory* m_pDWriteFactory;  //DW 팩토리
		IDWriteTextFormat* m_pTextFormat;  //텍스트포맷

		//DXGI에 종속적인 객체
		ID2D1RenderTarget* m_pD2dRT;       //d2d 렌더타켓뷰
		ID2D1SolidColorBrush* m_pD2dSCB;   //d2d 브러쉬

		//텍스트 포맷 관련
		D2D1_RECT_F m_D2rtLayoutRect;
		D2D1_COLOR_F m_D2dTextColor;

		IDWriteTextLayout* m_pTextLayout; 

	public:
		DWRITE_FONT_WEIGHT m_fontWeight;
		DWRITE_FONT_STYLE  m_fontStyle;
		BOOL               m_fontUnderline;
		wstring            m_wszFontFamily;

		float              m_fontSize;
		wstring            m_wszText;
		UINT32             m_cTextLength;


	public:
		//초기화
		bool Init();
		bool Set(IDXGISurface1* m_pSurface);
		bool Set(HWND hWnd, int iWidth, int iHeight, IDXGISurface1* pSurface);

		//객체 생성 및 소멸
		HRESULT CreateDeviceIR();
		HRESULT CreateDeviceR(IDXGISurface1* pSurface);
		void DiscardDeviceIR();
		void DiscardDeviceR();

		//포맷 변경
		void SetAlignment(DWRITE_TEXT_ALIGNMENT textAlignment, DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment);
		void SetlayoutRt(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom);
		void SetTextPos(const D2D1_MATRIX_3X2_F& transform = Matrix3x2F::Identity());
		ColorF SetTextColor(ColorF color);

		HRESULT SetText(wchar_t* text, ColorF Color);
		HRESULT SetFont(wchar_t* fontFamily);
		HRESULT SetFontSize(float size);
		HRESULT SetBold(bool bold);
		HRESULT SetItalic(bool italic);
		HRESULT SetUnderline(bool underline);

		//텍스트 그리기
		bool Begin();
		HRESULT Drawtxt(RECT rc, TCHAR* pText, ColorF color = ColorF(1, 0, 0, 1));
		HRESULT Drawtxt(TCHAR* pText);
		bool End();

		//전체 삭제
		bool Release();

	public:
		static DxWrite& GetInstance();

	protected:
		DxWrite();
		virtual ~DxWrite();
	};

#define I_Font DxWrite::GetInstance()
}