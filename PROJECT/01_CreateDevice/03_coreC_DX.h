#pragma once
#include "02_wndC_DX.h"

#ifndef _EMPTY
  #define _EMPTY { return true; }
#endif

class coreC_DX : public wndC_DX
{
public:
	//게임 전체적인 처리 순서에 대한 함수들. 게임에 관한 부분과 윈도우 생성에 관한 부분을 분리
	bool gameInit() override ;
	bool gameRun() override;
	bool gameFrame() override;
	bool gamePreRender() override;
	bool gameRender() override;
	bool gamePostRender() override;
	bool gameRelease() override;

public:
	//클래스 각각에 대한 처리 순서에 관한 함수들. 
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

