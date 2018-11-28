#pragma once
#include "00_header_DX.h"

class writeC_DX
{
protected:
	double m_dDpiScaleX;  //화면 스케일 (출력 영역의 크기를 지정할 때 사용된다.) 
	double m_dDpiScaleY;  //화면 스케일 (출력 영역의 크기를 지정할 때 사용된다.)
	FLOAT m_FDpiX;        //화면의 인치당 도트수 (요즘 모니터는 대부분 96.0F이다.)
	FLOAT m_FDpiY;        //화면의 인치당 도트수 (요즘 모니터는 대부분 96.0F이다.)
	
	//DXGI에 독립적인 객체
	ID2D1Factory* m_pD2dFactory;       //d2d 팩토리
	IDWriteFactory* m_pDWriteFactory;  //DW 팩토리
	IDWriteTextFormat* m_pTextFormat;  //텍스트포맷

	//DXGI에 종속적인 객체
	ID2D1RenderTarget* m_pD2dRT;       //d2d 렌더타켓뷰
	ID2D1SolidColorBrush* m_pD2dSCB;   //d2d 브러쉬

public:
	//초기화
	bool Init();
	bool Set(IDXGISurface1* m_pSurface);

	//객체 생성 및 소멸
	HRESULT CreateDeviceIR();
	HRESULT CreateDeviceR(IDXGISurface1* pSurface);
	void DiscardDeviceIR();
	void DiscardDeviceR();

	//랜더링
	void setTextFormat(DWRITE_TEXT_ALIGNMENT textAlignment, DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment);
	bool DrawText(RECT rc, TCHAR* pText, D2D1::ColorF Color = D2D1::ColorF(1, 0, 0, 1));

	//전체 삭제
	bool Release();

public:
	writeC_DX();
	virtual ~writeC_DX();
};