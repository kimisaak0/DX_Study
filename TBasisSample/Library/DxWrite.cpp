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

		//����� �⺻������ ��.
		m_D2dTextColor = ColorF(1, 1, 1, 1);
	}

	//��ü ����
	HRESULT DxWrite::CreateDeviceIR()
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

	HRESULT DxWrite::CreateDeviceR(IDXGISurface1* pSurface)
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
		V_FRETURN(m_pD2dRT->CreateSolidColorBrush(m_D2dTextColor, &m_pD2dSCB));

		return hr;
	}

	//��ü ����
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

	//�ʱ�ȭ
	bool DxWrite::Init()
	{
		HRESULT hr;
		//�������� ��ü ����
		V(CreateDeviceIR());
		return true;
	}

	bool DxWrite::Set(IDXGISurface1* m_pSurface)
	{
		HRESULT hr;
		//�������� ��ü ���� (ȭ�� ũ�� ����� �������)
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

	//���� ����
	void DxWrite::SetAlignment(DWRITE_TEXT_ALIGNMENT textAlignment, DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment)
	{
		//TextFormat ����
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
		//D2D Draw�� Begin�� End���̿��� �̷�������Ѵ�.

		if (m_pD2dRT && m_pD2dSCB) {
			//�ؽ�Ʈ ���
			m_pD2dRT->DrawTextW(pText, (UINT)_tcslen(pText), m_pTextFormat, m_D2rtLayoutRect, m_pD2dSCB);
		}

		return true;
	}

	void DxWrite::DrawTextEnd()
	{
		m_pD2dRT->EndDraw();
	}

	//��ü ����
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