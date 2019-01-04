#pragma once
#include "deviceC_DX.h"

class wndC_DX : public deviceC_DX
{
protected:
	WNDCLASSEX   m_wndC;        //������ Ŭ����
	LPCWSTR      m_lWndName;    //������ �̸�

public:
	void CenterWindow();       //�����츦 �߾����� �ű�� �Լ�

	//������ ���ν���
	LRESULT MsgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT	MsgProcA(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

	bool registWnd(LPCTSTR LWndName);   //������ ���.

	virtual bool runWindow();           //������ ������

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
	wndC_DX(LPCTSTR LWndName);
	wndC_DX();
	virtual ~wndC_DX();
};