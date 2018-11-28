#pragma once
#include "02_wndC_DX.h"

#ifndef _EMPTY
  #define _EMPTY { return true; }
#endif

class coreC_DX : public wndC_DX
{
public:
	//���� ��ü���� ó�� ������ ���� �Լ���. ���ӿ� ���� �κа� ������ ������ ���� �κ��� �и�
	bool gameInit() override ;
	bool gameRun() override;
	bool gameFrame() override;
	bool gamePreRender() override;
	bool gameRender() override;
	bool gamePostRender() override;
	bool gameRelease() override;

public:
	//Ŭ���� ������ ���� ó�� ������ ���� �Լ���. 
	virtual bool Init() _EMPTY
	virtual bool Frame() _EMPTY
	virtual bool PreRender() _EMPTY
	virtual bool Render() _EMPTY
	virtual bool PostRender() _EMPTY
	virtual bool Release() _EMPTY

public:
	coreC_DX(LPCTSTR LWndName);
	virtual ~coreC_DX();
};

