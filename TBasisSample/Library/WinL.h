#pragma once
#include "DxDevice.h"

namespace Lypi
{
	class winL : public DxDevice
	{
	protected:
		WNDCLASSEX   m_wndC;               //������ Ŭ����
		LPCWSTR      m_lWndName;           //������ �̸�

		HWND         m_hWnd;			   //������ �������� �ڵ鰪
		RECT         m_rtWindow;		   //������ ����
		RECT         m_rtClient;		   //Ŭ���̾�Ʈ ���� (�۾�����)
		winL*        m_pWindow;            //���� ������ �����쿡 ���� ������

	public:
		bool registWnd(LPCTSTR LWndName);   //������ ���.
		LRESULT MsgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);  //������ ���ν���
		virtual bool runWindow();   //������ ������
		
		virtual LRESULT	MsgProcA(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); //������ �޽����� �̿��� �� �ھ�� ȣ��

		void CenterWindow();       //�����츦 �߾����� �ű�� �Լ�

	public:
		virtual bool gameInit() = 0;            //���� ��ü�� �ʱ�ȭ�� ���
		virtual bool gameRun() = 0;             //������ �� ������ ����.
		virtual bool gameFrame() = 0;           //������ �� ������ ����� ���.
		virtual bool gamePreRender() = 0;       //������ �� ������ ������ �� �ʿ��� ������ ���.
		virtual bool gameRender() = 0;          //������ �� ������ �������� ���.
		virtual bool gamePostRender() = 0;      //������ �� ������ ������ �� �ʿ��� ������ ���.
		virtual bool gameRelease() = 0;         //���� ��ü�� �޸� �Ҹ� �� ��ü ������ ���.

		virtual bool ResetRT() = 0;

	public:
		winL(LPCTSTR LWndName);
		virtual ~winL();
	};
}