#pragma once
#include "stdHeader_L.h"

namespace Lypi
{
	class DxWrite
	{
	protected:
		FLOAT m_fDpiScaleX;                 //ȭ�� ������ (��� ������ ũ�⸦ ������ �� ���ȴ�.) 
		FLOAT m_fDpiScaleY;                 //ȭ�� ������ (��� ������ ũ�⸦ ������ �� ���ȴ�.)
		FLOAT m_FDpiX;                      //ȭ���� ��ġ�� ��Ʈ�� (���� ����ʹ� ��κ� 96.0F�̴�.)
		FLOAT m_FDpiY;                      //ȭ���� ��ġ�� ��Ʈ�� (���� ����ʹ� ��κ� 96.0F�̴�.)

		//DXGI�� �������� ��ü
		ID2D1Factory* m_pD2dFactory;       //d2d ���丮
		IDWriteFactory* m_pDWriteFactory;  //DW ���丮
		IDWriteTextFormat* m_pTextFormat;  //�ؽ�Ʈ����

		//DXGI�� �������� ��ü
		ID2D1RenderTarget* m_pD2dRT;       //d2d ����Ÿ�Ϻ�
		ID2D1SolidColorBrush* m_pD2dSCB;   //d2d �귯��

		//�ؽ�Ʈ ���� ����
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
		//�ʱ�ȭ
		bool Init();
		bool Set(IDXGISurface1* m_pSurface);
		bool Set(HWND hWnd, int iWidth, int iHeight, IDXGISurface1* pSurface);

		//��ü ���� �� �Ҹ�
		HRESULT CreateDeviceIR();
		HRESULT CreateDeviceR(IDXGISurface1* pSurface);
		void DiscardDeviceIR();
		void DiscardDeviceR();

		//���� ����
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

		//�ؽ�Ʈ �׸���
		bool Begin();
		HRESULT Drawtxt(RECT rc, TCHAR* pText, ColorF color = ColorF(1, 0, 0, 1));
		HRESULT Drawtxt(TCHAR* pText);
		bool End();

		//��ü ����
		bool Release();

	public:
		static DxWrite& GetInstance();

	protected:
		DxWrite();
		virtual ~DxWrite();
	};

#define I_Font DxWrite::GetInstance()
}