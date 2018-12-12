#pragma once
#include "WinL.h"

namespace Lypi
{
	//�������� ����
	HINSTANCE    g_hInst;              //�������� �ν��Ͻ� �ڵ鰪

	HWND         g_hWnd;			   //������ �������� �ڵ鰪
	winL*        g_pWindow;            //���� ������ �����쿡 ���� ������
	RECT         g_rtWindow;		   //������ ����
	RECT         g_rtClient;		   //Ŭ���̾�Ʈ ���� (�۾�����)

	//�����Լ� ����
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); 	

	//-------------

	winL::winL(LPCTSTR LWndName)
	{
		m_pWindow = this;
		g_pWindow = this;

		registWnd(LWndName);
	}

	//������ ��� �� ����
	bool winL::registWnd(LPCTSTR LWndName)
	{
		//Regist wndClass
		ZeroMemory(&m_wndC, sizeof(WNDCLASSEX));
		m_wndC.cbSize = sizeof(WNDCLASSEX);
		m_wndC.hInstance = g_hInst;
		m_wndC.lpfnWndProc = WndProc;
		m_wndC.lpszClassName = LWndName;
		m_wndC.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);

		if (!RegisterClassEx(&m_wndC)) {
			return false;
		}

		m_hWnd = CreateWindowEx(0,//WS_EX_TOPMOST,         // ������ â Ȯ�� ��Ÿ��
			m_wndC.lpszClassName, m_wndC.lpszClassName,	   // ������ Ŭ���� �̸�(�߿�), Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�.
			WS_SYSMENU | WS_BORDER | WS_VISIBLE,           // ������ ������ â�� ��Ÿ�� ���� 
			CW_USEDEFAULT, CW_USEDEFAULT,				   // ������ X,Y ��ǥ
			1516, 789,	                 	               // ������ ����, ���� ũ�� (�ȼ� ����) (x+16, y+39)
			NULL, NULL, g_hInst, 	 		               // �θ� �������� �ڵ� ����, �޴� �ڵ� ����, �����츦 �����ϴ� �ν��Ͻ� �ڵ�
			NULL);                                         // WM_CREATE�޽����� lParam���� ���޵� CREATESTRUCT����ü ������
													
		if (m_hWnd == NULL) {
			return false;
		}

		g_hWnd = m_hWnd;

		GetWindowRect(m_hWnd, &m_rtWindow);  	g_rtWindow = m_rtWindow;
		GetClientRect(m_hWnd, &m_rtClient);     g_rtClient = m_rtClient;

		return true;
	}

	//in-class Msg Proc
	LRESULT winL::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		assert(m_pWindow);

		MsgProcA(hWnd, iMsg, wParam, lParam);

		switch (iMsg) {
			
			case WM_CREATE: {
				//�����츦 ������ �� �߻��ϴ� �޽���
			}break;

			case WM_SIZE: {
			}break;

			case WM_DESTROY: {
				//�����츦 ������ �� �߻��ϴ� �޽��� (���α׷� ����ʹ� ����)
				PostQuitMessage(0); //���α׷� ���� ���
			}break;
		}

		return 1;
	}

	LRESULT	winL::MsgProcA(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return 1;
	}

	//������ ������
	bool winL::runWindow()
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

	//�����츦 �߾����� �ű�� �Լ�.
	void winL::CenterWindow()
	{
		// ȭ�� ��ũ���� �ػ�(���̿� ����)�� ��´�.
		int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
		int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

		// ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� �����.
		int iDestX = (iScreenWidth - m_rtClient.right) / 2;
		int iDestY = (iScreenHeight - m_rtClient.bottom) / 2;

		// �����츦 ȭ���߾����� �̵���Ų��.
		MoveWindow(m_hWnd, iDestX, iDestY, m_rtClient.right, m_rtClient.bottom, true);
	}

	winL::~winL()
	{

	}
	
	//�����Լ�
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		assert(g_pWindow != NULL);

		g_pWindow->MsgProc(hWnd, msg, wParam, lParam);

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

}