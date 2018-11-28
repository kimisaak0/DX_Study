#pragma once
#include "02_wndC_DX.h"

//���������� ����
HINSTANCE g_hInst;             //�������� �ν��Ͻ� �ڵ鰪
HWND      g_hWnd;			   //������ �������� �ڵ鰪
RECT      g_rtWindow;		   //������ ����
RECT      g_rtClient;		   //Ŭ���̾�Ʈ ���� (�۾�����)
UINT      g_uClientWidth;	   //�۾����� ����
UINT      g_uClientHegiht;	   //�۾����� ����

wndC_DX* g_pWindow;            //���� ������ �����쿡 ���� ������

wndC_DX::wndC_DX(LPCTSTR LWndName)
{
	//������ ������ Ŭ����. �ڱ��ڽ��� ���� ������.
	g_pWindow  = this;

	//������ ��� �� ������ �����ϸ� ����
	//assert()�� ���ڰ��� true�� �Ѿ��, false�� ������ ����.
	bool debug = registWnd(LWndName);
	assert(debug);

	GetWindowRect(g_hWnd, &g_rtWindow);   //������ RECT ��������
	GetWindowRect(g_hWnd, &g_rtClient);   //Ŭ���̾�Ʈ RECT ��������
}


//������ ���ν��� 
//�ƿ� �������� ���� ���ĵ� (���ÿ��� �ΰ��� ������ �ִ�.)
LRESULT CALLBACK wndC_DX::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);

	switch (iMsg) {
		//�����츦 ������ �� �߻��ϴ� �޽���
		case WM_CREATE: {
		}break;

		//�������� ũ�⸦ �ٲٸ� �߻��ϴ� �޽���
		case WM_SIZE: { 
			GetWindowRect(g_hWnd, &g_rtWindow);
			GetClientRect(g_hWnd, &g_rtClient);
		} break;

		//�����츦 ������ �� �߻��ϴ� �޽��� (���α׷� ����ʹ� ����)
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
	// �۾�����(  Ÿ��Ʋ ��/��輱/�޴�/��ũ�� �� ���� ������ ������ ����), ������ ��Ÿ��, �޴�����
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, //WS_EX_TOPMOST,// | WS_EX_TOOLWINDOW,
		L"TBasis3D11_Sample", L"dfaf", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, g_hInst,
		NULL);
	if (!g_hWnd)
		return false;

	// ������ ��Ÿ���� �����ϰ� ��ũ�� ������ Ŭ���̾�Ʈ ������ ��´�.
	//GetWindowRect(m_hWnd, &m_rcWindowBounds);
	//GetClientRect(m_hWnd, &m_rcWindowClient);

	CenterWindow(g_hWnd);
	UpdateWindow(g_hWnd);

	// ������ Ŭ���̾�Ʈ ���̿� ���̸� ��´�.
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
	////�� ���� �ǹ̴� ���� ����
	//if (!RegisterClassEx(&m_wndC)) {
	//	return false;
	//}

	////Create Window
	//RECT rc = { 0, 0, 800, 600 };

	////Ŭ���̾�Ʈ ���� ũ�⸦ ���ϴ� ũ��� �����ؼ� �������.
	//AdjustWindowRect(&rc, WS_SYSMENU, true); //(�۾�����, ������ ��Ÿ��, �޴�����)

	//g_hWnd = CreateWindowEx(NULL, //WS_EX_TOPMOST,             // ������ Ȯ�� ��Ÿ��
	//	m_wndC.lpszClassName, m_wndC.lpszClassName,	   // ������ Ŭ���� �̸�(�߿�), Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�.
	//	WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE,       // ������ �������� ��Ÿ�� ����
	//	CW_USEDEFAULT, CW_USEDEFAULT,				   // ������ X,Y ��ǥ
	//	rc.right - rc.left, rc.bottom - rc.top,		   // ������ ����, ���� ũ�� (�ȼ� ����)
	//	NULL, NULL, g_hInst, 			               // �θ� �������� �ڵ� ����, �޴� �ڵ� ����, �����츦 �����ϴ� �ν��Ͻ� �ڵ�
	//	NULL);                                         // WM_CREATE�޽����� lParam���� ���޵� CREATESTRUCT����ü ������
	//												   //������ ��Ÿ�Ͽ� ���� �κ��� ���� ����

	////�����찡 �������� �ʾ����� false�� �����Ѵ�.
	//if (g_hWnd == NULL) {
	//	return false;
	//}

	////������ ũ�⸦ ���� ������ �����Ѵ�.
	//GetWindowRect(g_hWnd, &g_rtWindow);
	//GetClientRect(g_hWnd, &g_rtClient);

	//CenterWindow(g_hWnd); //�����츦 ȭ�� �߾����� �̵���Ų��.

	//return true;
}


//������ ������
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