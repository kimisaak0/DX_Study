#include "04_coreC_DX.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//���α׷� �ڵ��� ���������� ����
	g_hInst = hInst;

	coreC_DX GameWnd(L"DXGI Infomation");

	GameWnd.runWindow();

}