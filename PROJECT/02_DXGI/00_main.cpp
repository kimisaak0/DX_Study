#include "04_coreC_DX.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//프로그램 핸들을 전역변수로 대입
	g_hInst = hInst;

	coreC_DX GameWnd(L"DXGI Infomation");

	GameWnd.runWindow();

}