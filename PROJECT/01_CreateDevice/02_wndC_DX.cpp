#pragma once
#include "02_wndC_DX.h"

//전역변수로 선언
HINSTANCE g_hInst;             //윈도우의 인스턴스 핸들값
HWND      g_hWnd;			   //생성된 윈도우의 핸들값
RECT      g_rtWindow;		   //윈도우 영역
RECT      g_rtClient;		   //클라이언트 영역 (작업영역)
UINT      g_uClientWidth;	   //작업영역 넓이
UINT      g_uClientHegiht;	   //작업영역 높이

wndC_DX* g_pWindow;            //현재 생성된 윈도우에 대한 포인터

wndC_DX::wndC_DX(LPCTSTR LWndName)
{
	//생성된 윈도우 클래스. 자기자신을 갖는 포인터.
	g_pWindow  = this;

	//윈도우 등록 및 생성에 실패하면 종료
	//assert()는 인자값이 true면 넘어가고, false면 에러를 띄운다.
	bool debug = registWnd(LWndName);
	assert(debug);

	GetWindowRect(g_hWnd, &g_rtWindow);   //윈도우 RECT 가져오기
	GetWindowRect(g_hWnd, &g_rtClient);   //클라이언트 RECT 가져오기
}


//윈도우 프로시져 
//아예 전역으로 만들어서 합쳐둠 (샘플에는 두개로 나눠져 있다.)
LRESULT CALLBACK wndC_DX::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);

	switch (iMsg) {
		//윈도우를 생성할 때 발생하는 메시지
		case WM_CREATE: {
		}break;

		//윈도우의 크기를 바꾸면 발생하는 메시지
		case WM_SIZE: { 
			GetWindowRect(g_hWnd, &g_rtWindow);
			GetClientRect(g_hWnd, &g_rtClient);
		} break;

		//윈도우를 종료할 때 발생하는 메시지 (프로그램 종료와는 별도)
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

	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MsgProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = g_hInst;
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"TBasis3D11_Sample";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	if (!RegisterClassEx(&wcex))
		return false;

	// Create window
	//g_hInst = hInstance;
	RECT rc = { 0, 0, 800, 600 };
	// 작업영역(  타이틀 바/경계선/메뉴/스크롤 바 등의 영역을 제외한 영역), 윈도우 스타일, 메뉴여부
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, //WS_EX_TOPMOST,// | WS_EX_TOOLWINDOW,
		L"TBasis3D11_Sample", L"dfaf", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, g_hInst,
		NULL);
	if (!g_hWnd)
		return false;

	// 윈도우 스타일을 저장하고 스크린 영역과 클라이언트 영역을 얻는다.
	//GetWindowRect(m_hWnd, &m_rcWindowBounds);
	//GetClientRect(m_hWnd, &m_rcWindowClient);

	CenterWindow(g_hWnd);
	UpdateWindow(g_hWnd);

	// 윈도우 클라이언트 넓이와 높이를 얻는다.
	//m_iWindowWidth = m_rcWindowClient.right - m_rcWindowClient.left;
	//m_iWindowHeight = m_rcWindowClient.bottom - m_rcWindowClient.top;

	ShowWindow(g_hWnd, SW_SHOW);
	return true;

	////Regist wndClass
	//ZeroMemory(&m_wndC, sizeof(WNDCLASSEX));
	//m_wndC.cbSize = sizeof(WNDCLASSEX);
	//m_wndC.hInstance = g_hInst;
	//m_wndC.lpfnWndProc = MsgProc;
	//m_wndC.lpszClassName = LWndName;
	//m_wndC.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	////m_wndC.style = CS_NOCLOSE;
	////각 값의 의미는 문서 참조
	//if (!RegisterClassEx(&m_wndC)) {
	//	return false;
	//}

	////Create Window
	//RECT rc = { 0, 0, 800, 600 };

	////클라이언트 영역 크기를 원하는 크기로 지정해서 만들어줌.
	//AdjustWindowRect(&rc, WS_SYSMENU, true); //(작업영역, 윈도우 스타일, 메뉴여부)

	//g_hWnd = CreateWindowEx(NULL, //WS_EX_TOPMOST,             // 윈도우 확장 스타일
	//	m_wndC.lpszClassName, m_wndC.lpszClassName,	   // 윈도우 클래스 이름(중요), 타이틀 바에 나타날 문자열.
	//	WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE,       // 생성될 윈도우의 스타일 지정
	//	CW_USEDEFAULT, CW_USEDEFAULT,				   // 윈도우 X,Y 좌표
	//	rc.right - rc.left, rc.bottom - rc.top,		   // 윈도우 수평, 수직 크기 (픽셀 단위)
	//	NULL, NULL, g_hInst, 			               // 부모 윈도우의 핸들 지정, 메뉴 핸들 지정, 윈도우를 생성하는 인스턴스 핸들
	//	NULL);                                         // WM_CREATE메시지의 lParam으로 전달될 CREATESTRUCT구조체 포인터
	//												   //윈도우 스타일에 대한 부분은 문서 참조

	////윈도우가 생성되지 않았으면 false를 리턴한다.
	//if (g_hWnd == NULL) {
	//	return false;
	//}

	////생성된 크기를 전역 변수에 대입한다.
	//GetWindowRect(g_hWnd, &g_rtWindow);
	//GetClientRect(g_hWnd, &g_rtClient);

	//CenterWindow(g_hWnd); //윈도우를 화면 중앙으로 이동시킨다.

	//return true;
}


//윈도우 돌리기
bool wndC_DX::runWindow()
{

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