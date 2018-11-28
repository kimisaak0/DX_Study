#pragma once
#include "01_deviceC_DX.h"

//----------------------------------------------------------------------------//
//-deviceC_DX�� wndC_DX�� ��ӹ޴´ٴ� ���� ������ �������� �������̴�.-------//
//-������ ������ ��� �� ������ �������� ũ�� ������ ���� ���븸 ������ �ִ�.-//
//----------------------------------------------------------------------------//

#ifndef _FURE
#define _FURE = 0;
#endif

class wndC_DX : public deviceC_DX
{
protected:
	WNDCLASSEX   m_wndC;        //������ Ŭ����
	LPCWSTR      m_lWndName;    //������ �̸�

private:
	//�����츦 �߾����� �ű�� �Լ�
	void CenterWindow(HWND hwnd);

	//������ ���ν��� - �ƿ� ���� �Լ�ȭ ���ѵ�.
	static LRESULT CALLBACK MsgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	bool registWnd(LPCTSTR LWndName);   //������ ��� ... �����ڿ��� ȣ����.

public:
	virtual bool runWindow();                   //������ ������

public:
	virtual bool gameInit() _FURE            //���� ��ü�� �ʱ�ȭ�� ���
	virtual bool gameRun() _FURE             //������ �� ������ ����.
	virtual bool gameFrame() _FURE           //������ �� ������ ����� ���.
	virtual bool gamePreRender() _FURE       //������ �� ������ ������ �� �ʿ��� ������ ���.
	virtual bool gameRender() _FURE          //������ �� ������ �������� ���.
	virtual bool gamePostRender() _FURE      //������ �� ������ ������ �� �ʿ��� ������ ���.
	virtual bool gameRelease() _FURE         //���� ��ü�� �޸� �Ҹ� �� ��ü ������ ���.

	
public:
	wndC_DX(LPCTSTR LWndName);
	virtual ~wndC_DX();
};