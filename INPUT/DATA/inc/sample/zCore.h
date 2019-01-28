#pragma once
#include "WinL.h"
#include "DxWrite.h"
#include "DxTimer.h"
#include "DxInput.h"

namespace Lypi
{
	class zCore : public winL
	{
		DxTimer m_GameTimer;
		DxWrite m_Font;

		ID3D11RasterizerState* m_pRSSolid;

	private:
		bool m_swTimerRender;
		bool m_swKeyRender;

		HRESULT SetRasterizerState();

	public:
		//게임 전체적인 처리 순서에 대한 함수들. 게임에 관한 부분과 윈도우 생성에 관한 부분을 분리
		bool gameInit() override;
		bool gameRun() override;
		bool gameFrame() override;
		bool gamePreRender() override;
		bool gameRender() override;
		bool gamePostRender() override;
		bool gameRelease() override;

	public:
		virtual bool Init() = 0;
		virtual bool Frame() = 0;
		virtual bool Render() = 0;
		virtual bool Release() = 0;

	public:

	public:
		zCore(LPCTSTR LWndName);
		virtual ~zCore();
	};



}