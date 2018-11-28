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

public:
	//�ʱ�ȭ
	bool Init();
	bool Set(IDXGISurface1* m_pSurface);

	//��ü ���� �� �Ҹ�
	HRESULT CreateDeviceIR();
	HRESULT CreateDeviceR(IDXGISurface1* pSurface);
	void DiscardDeviceIR();
	void DiscardDeviceR();

	//������
	void setTextFormat(DWRITE_TEXT_ALIGNMENT textAlignment, DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment);
	bool DrawText(RECT rc, TCHAR* pText, D2D1::ColorF Color = D2D1::ColorF(1, 0, 0, 1));

	//��ü ����
	bool Release();

public:
	writeC_DX();
	virtual ~writeC_DX();
};