#include "12_TextureSample.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInst = hInst;

	TextureSample GameWnd(_T("GameWindow"));


	GameWnd.runWindow();

}