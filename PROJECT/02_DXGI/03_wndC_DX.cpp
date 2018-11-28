#pragma once
#include "03_wndC_DX.h"

//전역변수로 선언
HINSTANCE g_hInst;
HWND      g_hWnd;
DWORD     g_dwWindowStyle;
RECT      g_rtWindow;
RECT      g_rtClient;
UINT      g_uClientWidth;
UINT      g_uClientHegiht;

//
wndC_DX* g_pWindow;

wndC_DX::wndC_DX(LPCTSTR LWndName)
{
	g_pWindow = this;

	//윈도우 등록 및 생성에 실패하면 종료
	//assert()는 인자값이 true면 넘어가고, false면 에러를 띄운다.
	bool debug = registWnd(LWndName);
	if (!debug) { MessageBox(0, _T("윈도우 초기화 실패"), _T("Fatal error"), MB_OK); }
	assert(debug);

	GetWindowRect(g_hWnd, &g_rtWindow);
	GetWindowRect(g_hWnd, &g_rtClient);
}


//윈도우 프로시져 
//아예 전역으로 만들어서 합쳐둠 (샘플에는 두개로 나눠져 있다.)
LRESULT CALLBACK wndC_DX::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);

	switch (iMsg) {
		//case WM_CREATE: {
		//}break;

		case WM_DESTROY: {
			PostQuitMessage(0);
		}break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}


//윈도우를 중앙으로 옮기는 함수.
void wndC_DX::CenterWindow(HWND hwnd)
{
	// 화면 스크린의 해상도(넓이와 높이)을 얻는다.
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

	// 윈도우 클라이언트 중앙과 화면 스크린 중앙을 맞춘다.
	int iDestX = (iScreenWidth - (g_rtWindow.right - g_rtWindow.left)) / 2;
	int iDestY = (iScreenHeight - (g_rtWindow.bottom - g_rtWindow.top)) / 2;

	// 윈도우를 화면중앙으로 이동시킨다.
	MoveWindow(hwnd, iDestX, iDestY,
		g_rtWindow.right - g_rtWindow.left,
		g_rtWindow.bottom - g_rtWindow.top,
		true);
}

//윈도우 등록 및 생성
bool wndC_DX::registWnd(LPCTSTR LWndName)
{
	//Regist wndClass
	ZeroMemory(&m_wndC, sizeof(WNDCLASSEX));
	m_wndC.cbSize = sizeof(WNDCLASSEX);
	m_wndC.hInstance = g_hInst;
	m_wndC.lpfnWndProc = MsgProc;
	m_wndC.lpszClassName = LWndName;
	m_wndC.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	if (!RegisterClassEx(&m_wndC)) {
		return false;
	}

	//Create Window
	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, NULL, true); //(작업영역, 윈도우 스타일, 메뉴여부)

	g_hWnd = CreateWindowEx(NULL,             // 윈도우 확장 스타일
		m_wndC.lpszClassName, m_wndC.lpszClassName,	   // 윈도우 클래스 이름(중요), 타이틀 바에 나타날 문자열.
		WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE,	   // 생성될 윈도우의 스타일 지정
		CW_USEDEFAULT, CW_USEDEFAULT,				   // 윈도우 X,Y 좌표
		rc.right - rc.left, rc.bottom - rc.top,		   // 윈도우 수평, 수직 크기 (픽셀 단위)
		NULL, NULL, g_hInst, 			               // 부모 윈도우의 핸들 지정, 메뉴 핸들 지정, 윈도우를 생성하는 인스턴스 핸들
		NULL);                                         // WM_CREATE메시지의 lParam으로 전달될 CREATESTRUCT구조체 포인터

	if (g_hWnd == NULL) {
		return false;
	}
	g_dwWindowStyle = GetWindowLong(g_hWnd, GWL_STYLE);
	GetWindowRect(g_hWnd, &g_rtWindow);
	GetClientRect(g_hWnd, &g_rtClient);

	CenterWindow(g_hWnd);

	return true;
}

//윈도우 돌리기
bool wndC_DX::runWindow()
{
	if (!deviceC_DX::Start()) { return false; }
	if (!gameInit()) { return false; }

	//Main message loop
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else {
			gameRun();
		}
	}

	if (!gameRelease()) { return false; }

	return true;
}

wndC_DX::~wndC_DX()
{

}