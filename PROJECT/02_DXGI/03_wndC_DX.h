#pragma once
#pragma once
#include "02_deviceC_DX.h"

#ifndef _FURE
  #define _FURE              = 0;
#endif

//----------------------------------------------------------------------------//
//-deviceC_DX를 wndC_DX과 상속받는다는 것이 윈도우 버전과의 차이점이다.-------//
//-윈도우 생성과 등록 및 생성된 윈도우의 크기 정보에 대한 내용만 가지고 있다.-//
//----------------------------------------------------------------------------//

//전역변수로 선언 (cpp에서 정의함)
//HINSTANCE g_hInst;
//HWND      g_hWnd;
//RECT      g_rtWindow;
//RECT      g_rtClient;
//UINT      g_uClientWidth;
//UINT      g_uClientHegiht;

class wndC_DX : public deviceC_DX
{
protected:
	WNDCLASSEX   m_wndC;        //윈도우 클래스
	LPCWSTR      m_lWndName;    //윈도우 이름

private:
	//윈도우를 중앙으로 옮기는 함수
	void CenterWindow(HWND hwnd);

	//윈도우 프로시저 - 아예 전역 함수화 시켜둠.
	static LRESULT CALLBACK MsgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	bool registWnd(LPCTSTR LWndName);   //윈도우 등록 ... 생성자에서 호출함.

public:
	virtual bool runWindow();                //윈도우 돌리기

public:
	virtual bool gameInit()       _FURE      //게임 전체의 초기화를 담당
	virtual bool gameRun()        _FURE      //게임의 전 과정을 실행.
	virtual bool gameFrame()      _FURE      //게임의 매 프레임 계산을 담당.
	virtual bool gamePreRender()  _FURE      //게임의 매 프레임 렌더링 전 필요한 절차를 담당.
	virtual bool gameRender()     _FURE      //게임의 매 프레임 렌더링을 담당.
	virtual bool gamePostRender() _FURE      //게임의 매 프레임 렌더링 후 필요한 절차를 담당.
	virtual bool gameRelease()    _FURE      //게임 전체의 메모리 소멸 및 객체 해제를 담당.


public:
	wndC_DX(LPCTSTR LWndName);
	virtual ~wndC_DX();
};