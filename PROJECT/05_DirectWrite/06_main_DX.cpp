#include "03_coreC_DX.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	
	coreC_DX GameWnd(_T("GameWindow"));


	GameWnd.runWindow();

}