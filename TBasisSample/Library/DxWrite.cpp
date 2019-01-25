#include "DxWrite.h"

namespace Lypi
{
	DxWrite& DxWrite::GetInstance()
	{
		static DxWrite inst;
		return inst;
	}

	DxWrite::DxWrite()
	{
		m_pD2dFactory = nullptr;
		m_pD2dRT = nullptr;
		m_pD2dSCB = nullptr;

		m_pDWriteFactory = nullptr;
		m_pTextFormat = nullptr;

		m_dDpiScaleX = 0;
		m_dDpiScaleY = 0;
		m_FDpiX = 0;
		m_FDpiY = 0;

		//흰색을 기본값으로 함.
		m_D2dTextColor = ColorF(1, 1, 1, 1);
	}

	//객체 생성
	HRESULT DxWrite::CreateDeviceIR()
	{
		HRESULT hr;
		//D2D 팩토리 생성
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2dFactory);

		//사실 어차피 96이고 나누면 1이다(..)
		m_pD2dFactory->GetDesktopDpi(&m_FDpiX, &m_FDpiY);
		m_dDpiScaleX = m_FDpiX / 96.0;
		m_dDpiScaleY = m_FDpiY / 96.0;

		//DW 팩토리 생성
		if (SUCCEEDED(hr)) {
			hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pDWriteFactory);
		}

		//텍스트 포맷 생성
		if (SUCCEEDED(hr)) {
			hr = m_pDWriteFactory->CreateTextFormat(
				_T("고딕"),
				NULL,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_ULTRA_EXPANDED,
				15.0f,
				_T("ko-kr"),
				&m_pTextFormat
			);
		}

		return hr;
	}

	HRESULT DxWrite::CreateDeviceR(IDXGISurface1* pSurface)
	{
		HRESULT hr = S_OK;
		//렌더링 옵션을 설정하는 구조체.
		D2D1_RENDER_TARGET_PROPERTIES props;
		props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
		props.pixelFormat = PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_IGNORE);
		props.dpiX = m_FDpiX;
		props.dpiY = m_FDpiY;
		props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
		props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

		//D2D렌더타겟 생성
		hr = m_pD2dFactory->CreateDxgiSurfaceRenderTarget(pSurface, &props, &m_pD2dRT);
		if (FAILED(hr)) {
			return hr;
		}

		//정해진 색 사용시 ColorF(ColorF::Coral)
		V_FRETURN(m_pD2dRT->CreateSolidColorBrush(m_D2dTextColor, &m_pD2dSCB));

		return hr;
	}

	//객체 삭제
	void DxWrite::DiscardDeviceIR()
	{
		SAFE_RELEASE(m_pD2dFactory);
		SAFE_RELEASE(m_pDWriteFactory);
		SAFE_RELEASE(m_pTextFormat);
	}

	void DxWrite::DiscardDeviceR()
	{
		SAFE_RELEASE(m_pD2dRT);
		SAFE_RELEASE(m_pD2dSCB);
	}

	//초기화
	bool DxWrite::Init()
	{
		HRESULT hr;
		//독립적인 객체 생성
		V(CreateDeviceIR());
		return true;
	}

	bool DxWrite::Set(IDXGISurface1* m_pSurface)
	{
		HRESULT hr;
		//종속적인 객체 생성 (화면 크기 변경시 재생성함)
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2dFactory);
		V(CreateDeviceR(m_pSurface));
		return true;
	}

	bool DxWrite::Set(HWND hWnd, int iWidth, int iHeight, IDXGISurface1* pSurface)
	{
		if (!Init()) {
			return false;
		}

		CreateDeviceIR();
		CreateDeviceR(pSurface);
		SetText(Point2F(iWidth, iHeight), L"TBasisSmaple", Colorf(1, 1, 1, 1));
	}

	//포맷 변경
	void DxWrite::SetAlignment(DWRITE_TEXT_ALIGNMENT textAlignment, DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment)
	{
		//TextFormat 지정
		m_pTextFormat->SetTextAlignment(textAlignment);
		m_pTextFormat->SetParagraphAlignment(paragraphAlignment);
	}

	void DxWrite::SetlayoutRt(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom)
	{
		m_D2rtLayoutRect = RectF(left, top, right, bottom);
	}

	void DxWrite::SetTextPos(const D2D1_MATRIX_3X2_F& transform)
	{
		m_pD2dRT->SetTransform(transform);
	}

	ColorF DxWrite::SetTextColor(ColorF color)
	{
		ColorF oldColor(m_D2dTextColor.r, m_D2dTextColor.g, m_D2dTextColor.b, m_D2dTextColor.a);
		m_D2dTextColor = color;
		m_pD2dSCB->SetColor(m_D2dTextColor);

		return oldColor;
	}

	//HRESULT DxWrite::SetText(D2D1_POINT_2F size, wchar_t* text, ColorF Color)
	//{
	//	HRESULT hr = S_OK;
	//	m_cTextLength = (UINT32)wcslen(text);
	//	m_wszText.clear();
	//	m_wszText = text;

	//	SAFE_RELEASE(m_pTextLayout);
	//}

	//DrawText
	void DxWrite::DrawTextBegin()
	{
		m_pD2dRT->BeginDraw();
	}

	bool DxWrite::Drawtxt(TCHAR* pText)
	{
		//D2D Draw는 Begin과 End사이에서 이루어져야한다.

		if (m_pD2dRT && m_pD2dSCB) {
			//텍스트 출력
			m_pD2dRT->DrawTextW(pText, (UINT)_tcslen(pText), m_pTextFormat, m_D2rtLayoutRect, m_pD2dSCB);
		}

		return true;
	}

	void DxWrite::DrawTextEnd()
	{
		m_pD2dRT->EndDraw();
	}

	//전체 삭제
	bool DxWrite::Release()
	{
		DiscardDeviceIR();
		DiscardDeviceR();

		return true;
	}

	DxWrite::~DxWrite()
	{
		Release();
	}
}