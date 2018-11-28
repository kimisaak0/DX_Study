#include "14_AccessImage.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInst = hInst;

	AccessImage GameWnd(_T("GameWindow"));


	GameWnd.runWindow();

}