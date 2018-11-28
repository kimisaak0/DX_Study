#include "11_PrimitiveSample.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInst = hInst;

	VertexSample GameWnd(_T("GameWindow"));


	GameWnd.runWindow();

}