#include "sample.h"

using namespace Lypi;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInst = hInst;

	Sample GameWnd(_T("GameWindow"));

	GameWnd.runWindow();

	return 0;

}

