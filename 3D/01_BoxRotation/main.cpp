#include "sample.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInst = hInst;

	Sample GameWnd(_T("GameWindow"));

	GameWnd.runWindow();
}