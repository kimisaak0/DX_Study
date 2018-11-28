#pragma once
#include "03_wndC_DX.h"

//���������� ����
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

	//������ ��� �� ������ �����ϸ� ����
	//assert()�� ���ڰ��� true�� �Ѿ��, false�� ������ ����.
	bool debug = registWnd(LWndName);
	if (!debug) { MessageBox(0, _T("������ �ʱ�ȭ ����"), _T("Fatal error"), MB_OK); }
	assert(debug);

	GetWindowRect(g_hWnd, &g_rtWindow);
	GetWindowRect(g_hWnd, &g_rtClient);
}


//������ ���ν��� 
//�ƿ� �������� ���� ���ĵ� (���ÿ��� �ΰ��� ������ �ִ�.)
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


//�����츦 �߾����� �ű�� �Լ�.
void wndC_DX::CenterWindow(HWND hwnd)
{
	// ȭ�� ��ũ���� �ػ�(���̿� ����)�� ��´�.
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

	// ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� �����.
	int iDestX = (iScreenWidth - (g_rtWindow.right - g_rtWindow.left)) / 2;
	int iDestY = (iScreenHeight - (g_rtWindow.bottom - g_rtWindow.top)) / 2;

	// �����츦 ȭ���߾����� �̵���Ų��.
	MoveWindow(hwnd, iDestX, iDestY,
		g_rtWindow.right - g_rtWindow.left,
		g_rtWindow.bottom - g_rtWindow.top,
		true);
}

//������ ��� �� ����
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
	AdjustWindowRect(&rc, NULL, true); //(�۾�����, ������ ��Ÿ��, �޴�����)

	g_hWnd = CreateWindowEx(NULL,             // ������ Ȯ�� ��Ÿ��
		m_wndC.lpszClassName, m_wndC.lpszClassName,	   // ������ Ŭ���� �̸�(�߿�), Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�.
		WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE,	   // ������ �������� ��Ÿ�� ����
		CW_USEDEFAULT, CW_USEDEFAULT,				   // ������ X,Y ��ǥ
		rc.right - rc.left, rc.bottom - rc.top,		   // ������ ����, ���� ũ�� (�ȼ� ����)
		NULL, NULL, g_hInst, 			               // �θ� �������� �ڵ� ����, �޴� �ڵ� ����, �����츦 �����ϴ� �ν��Ͻ� �ڵ�
		NULL);                                         // WM_CREATE�޽����� lParam���� ���޵� CREATESTRUCT����ü ������

	if (g_hWnd == NULL) {
		return false;
	}
	g_dwWindowStyle = GetWindowLong(g_hWnd, GWL_STYLE);
	GetWindowRect(g_hWnd, &g_rtWindow);
	GetClientRect(g_hWnd, &g_rtClient);

	CenterWindow(g_hWnd);

	return true;
}

//������ ������
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