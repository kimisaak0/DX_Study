#pragma once
#include "00_header_DX.h"

class writeC_DX
{
protected:
	double m_dDpiScaleX;  //ȭ�� ������ (��� ������ ũ�⸦ ������ �� ���ȴ�.) 
	double m_dDpiScaleY;  //ȭ�� ������ (��� ������ ũ�⸦ ������ �� ���ȴ�.)
	FLOAT m_FDpiX;        //ȭ���� ��ġ�� ��Ʈ�� (���� ����ʹ� ��κ� 96.0F�̴�.)
	FLOAT m_FDpiY;        //ȭ���� ��ġ�� ��Ʈ�� (���� ����ʹ� ��κ� 96.0F�̴�.)
	
	//DXGI�� �������� ��ü
	ID2D1Factory* m_pD2dFactory;       //d2d ���丮
	IDWriteFactory* m_pDWriteFactory;  //DW ���丮
	IDWriteTextFormat* m_pTextFormat;  //�ؽ�Ʈ����

	//DXGI�� �������� ��ü
	ID2D1RenderTarget* m_pD2dRT;       //d2d ����Ÿ�Ϻ�
	ID2D1SolidColorBrush* m_pD2dSCB;   //d2d �귯��

	D2D1_RECT_F m_D2rtLayoutRect;      //�ؽ�Ʈ�� �׷��� �簢�� ����.

public:
	//�ʱ�ȭ
	bool Init();
	bool Set(IDXGISurface1* m_pSurface);

	//��ü ���� �� �Ҹ�
	HRESULT CreateDeviceIR();
	HRESULT CreateDeviceR(IDXGISurface1* pSurface);
	void DiscardDeviceIR();
	void DiscardDeviceR();

	//���� ����
	void SetAlignment(DWRITE_TEXT_ALIGNMENT textAlignment, DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment);
	void SetlayoutRt(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom);

	//�ؽ�Ʈ �׸���
	void DrawTextBegin();
	bool DrawText(TCHAR* pText);
	void DrawTextEnd();

	//��ü ����
	bool Release();

public:
	writeC_DX();
	virtual ~writeC_DX();
};