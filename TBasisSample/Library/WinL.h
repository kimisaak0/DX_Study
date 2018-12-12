#pragma once
#include "DxDevice.h"

namespace Lypi
{
	class winL : public DxDevice
	{
	protected:
		WNDCLASSEX   m_wndC;               //윈도우 클래스
		LPCWSTR      m_lWndName;           //윈도우 이름

		HWND         m_hWnd;			   //생성된 윈도우의 핸들값
		RECT         m_rtWindow;		   //윈도우 영역
		RECT         m_rtClient;		   //클라이언트 영역 (작업영역)
		winL*        m_pWindow;            //현재 생성된 윈도우에 대한 포인터

	public:
		bool registWnd(LPCTSTR LWndName);   //윈도우 등록.
		LRESULT MsgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);  //윈도우 프로시저
		virtual bool runWindow();   //윈도우 돌리기
		
		virtual LRESULT	MsgProcA(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); //윈도우 메시지를 이용할 때 코어에서 호출

		void CenterWindow();       //윈도우를 중앙으로 옮기는 함수

	public:
		virtual bool gameInit() = 0;            //게임 전체의 초기화를 담당
		virtual bool gameRun() = 0;             //게임의 전 과정을 실행.
		virtual bool gameFrame() = 0;           //게임의 매 프레임 계산을 담당.
		virtual bool gamePreRender() = 0;       //게임의 매 프레임 렌더링 전 필요한 절차를 담당.
		virtual bool gameRender() = 0;          //게임의 매 프레임 렌더링을 담당.
		virtual bool gamePostRender() = 0;      //게임의 매 프레임 렌더링 후 필요한 절차를 담당.
		virtual bool gameRelease() = 0;         //게임 전체의 메모리 소멸 및 객체 해제를 담당.

		virtual bool ResetRT() = 0;

	public:
		winL(LPCTSTR LWndName);
		virtual ~winL();
	};
}