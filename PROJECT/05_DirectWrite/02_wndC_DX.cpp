#pragma once
#include "02_wndC_DX.h"

//���������� ����
HINSTANCE    g_hInst;              //�������� �ν��Ͻ� �ڵ鰪
HWND         g_hWnd;			   //������ �������� �ڵ鰪
RECT         g_rtWindow;		   //������ ����
RECT         g_rtClient;		   //Ŭ���̾�Ʈ ���� (�۾�����)
UINT         g_uClientWidth;	   //�۾����� ����
UINT         g_uClientHegiht;	   //�۾����� ����

wndC_DX* g_pWindow;            //���� ������ �����쿡 ���� ������

wndC_DX::wndC_DX(LPCTSTR LWndName)
{
	//������ ������ Ŭ����. �ڱ��ڽ��� ���� ������.
	g_pWindow = this;

	//������ ��� �� ������ �����ϸ� ����
	//assert()�� ���ڰ��� true�� �Ѿ��, false�� ������ ����.
	bool debug = registWnd(LWndName);
	assert(debug);

	GetWindowRect(g_hWnd, &g_rtWindow);   //������ RECT ��������
	GetWindowRect(g_hWnd, &g_rtClient);   //Ŭ���̾�Ʈ RECT ��������
}

//static�Լ� (���� �ܺ� �Լ�)
//������ ���ν��� Static�Լ�
LRESULT CALLBACK wndC_DX::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);

	switch (iMsg) {

		case WM_KEYDOWN: {
			switch (wParam) {
				case '0': {
					//��üȭ��� ������ ��� ��ȯ
					int w = GetSystemMetrics(SM_CXFULLSCREEN);
					int h = GetSystemMetrics(SM_CYFULLSCREEN);

					g_pWindow->m_pSwapChain->SetFullscreenState(!(g_pWindow->m_bFullScrFlag), NULL);
					g_pWindow->SetFullScrFlag(!(g_pWindow->m_bFullScrFlag));

					DXGI_SWAP_CHAIN_DESC desc;
					g_pWindow->m_pSwapChain->GetDesc(&desc);

					if ((g_pWindow->m_bFullScrFlag)==FALSE) {
						//��üȭ�鿡�� â���� ����� 800,600���� ����
						desc.BufferDesc.Width = 800;
						desc.BufferDesc.Height = 600;

						g_pWindow->m_pSwapChain->ResizeTarget(&(desc.BufferDesc));
						g_pWindow->CenterWindow(g_hWnd);

					ShowWindow(g_hWnd, SW_SHOW);
					}
					else {
						//��üȭ������ ����� �ü�� �ػ󵵷� ����
						desc.BufferDesc.Width = w;
						desc.BufferDesc.Height = h;

						g_pWindow->m_pSwapChain->ResizeTarget(&(desc.BufferDesc));
					}
				} break;

				case VK_ESCAPE: {
					SendMessage(g_hWnd, WM_CLOSE, 0, 0);
				}break;
			}
		} break;

		//�����츦 ������ �� �߻��ϴ� �޽���
		case WM_CREATE: {
		}break;

		//�������� ũ�⸦ �ٲٸ� �߻��ϴ� �޽���
		case WM_SIZE: {
			if (SUCCEEDED(g_pWindow->InitDevice())) {
				g_pWindow->ResizeDevice(LOWORD(lParam), HIWORD(lParam));
				g_pWindow->ResetRT();
			}
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
	//Regist wndClass
	ZeroMemory(&m_wndC, sizeof(WNDCLASSEX));
	m_wndC.cbSize = sizeof(WNDCLASSEX);
	m_wndC.hInstance = g_hInst;
	m_wndC.lpfnWndProc = MsgProc;
	m_wndC.lpszClassName = LWndName;
	//m_wndC.style = CS_NOCLOSE; //�������α׷��� ��Ÿ�� �Ӽ� �� (���� ����)
	//�� ���� �ǹ̴� ���� ����
	if (!RegisterClassEx(&m_wndC)) {
		return false;
	}

	//Create Window
	RECT rc = { 0, 0, 800, 600 };

	//Ŭ���̾�Ʈ ���� ũ�⸦ ���ϴ� ũ��� �����ؼ� �������.
	AdjustWindowRect(&rc, WS_SYSMENU, true); //(�۾�����, ������ ��Ÿ��, �޴�����)

	g_hWnd = CreateWindowEx(NULL, //WS_EX_TOPMOST,     // ������ â Ȯ�� ��Ÿ��
		m_wndC.lpszClassName, m_wndC.lpszClassName,	   // ������ Ŭ���� �̸�(�߿�), Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�.
		WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE,       // ������ ������ â�� ��Ÿ�� ���� 
		CW_USEDEFAULT, CW_USEDEFAULT,				   // ������ X,Y ��ǥ
		rc.right - rc.left, rc.bottom - rc.top,		   // ������ ����, ���� ũ�� (�ȼ� ����)
		NULL, NULL, g_hInst, 			               // �θ� �������� �ڵ� ����, �޴� �ڵ� ����, �����츦 �����ϴ� �ν��Ͻ� �ڵ�
		NULL);                                         // WM_CREATE�޽����� lParam���� ���޵� CREATESTRUCT����ü ������
		//â ��Ÿ�ϰ� â Ȯ�� ��Ÿ�Ͽ� ���� �κ��� ���� ����

	//�����찡 �������� �ʾ����� false�� �����Ѵ�.
	if (g_hWnd == NULL) {
		return false;
	}

	//������ ũ�⸦ ���� ������ �����Ѵ�.
	GetWindowRect(g_hWnd, &g_rtWindow);
	GetClientRect(g_hWnd, &g_rtClient);

	CenterWindow(g_hWnd); //�����츦 ȭ�� �߾����� �̵���Ų��.

	return true;
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