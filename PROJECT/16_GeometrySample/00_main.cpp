#include "16_geo.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInst = hInst;

	GeoSample GameWnd(_T("±‚«œºŒ¿Ã¥ı"));


	GameWnd.runWindow();

}