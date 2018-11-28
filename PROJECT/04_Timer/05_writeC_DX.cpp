#include "05_writeC_DX.h"
using namespace D2D1;


writeC_DX::writeC_DX()
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
}

//객체 생성
HRESULT writeC_DX::CreateDeviceIR()
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

HRESULT writeC_DX::CreateDeviceR(IDXGISurface1* pSurface)
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
	V_RETURN(m_pD2dRT->CreateSolidColorBrush(ColorF(1,1,1,1),&m_pD2dSCB));

	return hr;	
}


//객체 삭제
void writeC_DX::DiscardDeviceIR()
{
	SAFE_RELEASE(m_pD2dFactory);
	SAFE_RELEASE(m_pDWriteFactory);
	SAFE_RELEASE(m_pTextFormat);
}

void writeC_DX::DiscardDeviceR()
{
	SAFE_RELEASE(m_pD2dRT);
	SAFE_RELEASE(m_pD2dSCB);
}

//초기화
bool writeC_DX::Init()
{
	HRESULT hr;
	//독립적인 객체 생성
	V(CreateDeviceIR());
	return true;
}

bool writeC_DX::Set(IDXGISurface1* m_pSurface)
{
	HRESULT hr;
	//종속적인 객체 생성 (화면 크기 변경시 재생성해줘야 한다.) //작업 필요
	V(CreateDeviceR(m_pSurface));

	return true;
}

//랜더링
void writeC_DX::setTextFormat(DWRITE_TEXT_ALIGNMENT textAlignment, DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment)
{
	//TextFormat 지정
	m_pTextFormat->SetTextAlignment(textAlignment);
	m_pTextFormat->SetParagraphAlignment(paragraphAlignment);
}

bool writeC_DX::DrawText(RECT rc, TCHAR* pText, D2D1::ColorF Color)
{
	//D2D Draw는 Begin과 End사이에서 이루어져야한다.

	D2D1_POINT_2F point;
	point.x = 200;
	point.y = 200;

	if (m_pD2dRT) {
		m_pD2dRT->BeginDraw();
	}

	if (m_pD2dRT && m_pD2dSCB) {
		//위치 지정
		//m_pD2dRT->SetTransform(D2D1::Matrix3x2F::Rotation(sin(g_GameTimer) * 180 + 180, point));

		//글씨를 사각형 만들기 (파워포인트랑 똑같이 생각하면 됨)
		D2D1_RECT_F layoutRect = RectF((float)rc.left, (float)rc.top, (float)rc.right, (float)rc.bottom);

		//색상 변경
		//m_pD2dSCB->SetColor(Color);
		m_pD2dRT->DrawTextW(pText, (UINT)_tcslen(pText), m_pTextFormat, layoutRect, m_pD2dSCB);
	}

	if (m_pD2dRT && FAILED(m_pD2dRT->EndDraw())) {
		return false;
	}
	return true;

}

//전체 삭제
bool writeC_DX::Release()
{
	DiscardDeviceIR();
	DiscardDeviceR();

	return true;
}

writeC_DX::~writeC_DX()
{
	Release();
}