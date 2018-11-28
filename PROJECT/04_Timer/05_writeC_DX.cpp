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

//��ü ����
HRESULT writeC_DX::CreateDeviceIR()
{
	HRESULT hr;
	//D2D ���丮 ����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2dFactory);

	//��� ������ 96�̰� ������ 1�̴�(..)
	m_pD2dFactory->GetDesktopDpi(&m_FDpiX, &m_FDpiY);
	m_dDpiScaleX = m_FDpiX / 96.0;
	m_dDpiScaleY = m_FDpiY / 96.0;

	//DW ���丮 ����
	if (SUCCEEDED(hr)) {
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pDWriteFactory);
	}

	//�ؽ�Ʈ ���� ����
	if (SUCCEEDED(hr)) {
		hr = m_pDWriteFactory->CreateTextFormat(
			_T("���"),
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
	//������ �ɼ��� �����ϴ� ����ü.
	D2D1_RENDER_TARGET_PROPERTIES props;
	props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	props.pixelFormat = PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_IGNORE);
	props.dpiX = m_FDpiX;
	props.dpiY = m_FDpiY;
	props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	//D2D����Ÿ�� ����
	hr = m_pD2dFactory->CreateDxgiSurfaceRenderTarget(pSurface, &props, &m_pD2dRT);
	if (FAILED(hr)) {
		return hr;
	}

	//������ �� ���� ColorF(ColorF::Coral)
	V_RETURN(m_pD2dRT->CreateSolidColorBrush(ColorF(1,1,1,1),&m_pD2dSCB));

	return hr;	
}


//��ü ����
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

//�ʱ�ȭ
bool writeC_DX::Init()
{
	HRESULT hr;
	//�������� ��ü ����
	V(CreateDeviceIR());
	return true;
}

bool writeC_DX::Set(IDXGISurface1* m_pSurface)
{
	HRESULT hr;
	//�������� ��ü ���� (ȭ�� ũ�� ����� ���������� �Ѵ�.) //�۾� �ʿ�
	V(CreateDeviceR(m_pSurface));

	return true;
}

//������
void writeC_DX::setTextFormat(DWRITE_TEXT_ALIGNMENT textAlignment, DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment)
{
	//TextFormat ����
	m_pTextFormat->SetTextAlignment(textAlignment);
	m_pTextFormat->SetParagraphAlignment(paragraphAlignment);
}

bool writeC_DX::DrawText(RECT rc, TCHAR* pText, D2D1::ColorF Color)
{
	//D2D Draw�� Begin�� End���̿��� �̷�������Ѵ�.

	D2D1_POINT_2F point;
	point.x = 200;
	point.y = 200;

	if (m_pD2dRT) {
		m_pD2dRT->BeginDraw();
	}

	if (m_pD2dRT && m_pD2dSCB) {
		//��ġ ����
		//m_pD2dRT->SetTransform(D2D1::Matrix3x2F::Rotation(sin(g_GameTimer) * 180 + 180, point));

		//�۾��� �簢�� ����� (�Ŀ�����Ʈ�� �Ȱ��� �����ϸ� ��)
		D2D1_RECT_F layoutRect = RectF((float)rc.left, (float)rc.top, (float)rc.right, (float)rc.bottom);

		//���� ����
		//m_pD2dSCB->SetColor(Color);
		m_pD2dRT->DrawTextW(pText, (UINT)_tcslen(pText), m_pTextFormat, layoutRect, m_pD2dSCB);
	}

	if (m_pD2dRT && FAILED(m_pD2dRT->EndDraw())) {
		return false;
	}
	return true;

}

//��ü ����
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