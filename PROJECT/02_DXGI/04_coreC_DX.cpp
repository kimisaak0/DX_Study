#include "04_coreC_DX.h"

coreC_DX::coreC_DX(LPCTSTR LWndName) : wndC_DX(LWndName)
{
}

bool coreC_DX::gameInit()
{
	deviceC_DX::CreateGIFactory();

	FILE* fp;
	_tfopen_s(&fp,_T("DeviceInfo.txt"), _T("wt"));
	if (!fp) {
		MessageBox(NULL, _T("파일을 생성하지 못했습니다."), _T("파일생성에러"), MB_ICONERROR);
		return false;
	}

	enumAdapterC_DX* pAdapterInfo;
	_ftprintf(fp, L"Num Adapter : %d\n", (int)m_enumeratoin.m_eacInfo_vector.size());

	for (int i = 0; i < m_enumeratoin.m_eacInfo_vector.size(); i++) {
		pAdapterInfo = m_enumeratoin.m_eacInfo_vector[i];
		_ftprintf(fp, L"Description[%d] : %s, Num Output: %d\n", i, pAdapterInfo->m_diaDesc.Description, (int)pAdapterInfo->m_eocInfo_vector.size());
		//m_diaDesc.Description : 어댑터 종류에 대한 문자열 (나머지 정보는 그다지..)

		enumOutputC_DX* pOutputInfo;
		for (int i = 0; i < pAdapterInfo->m_eocInfo_vector.size(); i++) {
			pOutputInfo = pAdapterInfo->m_eocInfo_vector[i];
			_ftprintf(fp, L"\n\tOutput[%d] m_Desc:%s\t DesktopCoordinates:%d, %d, %d, %d : NumDisplayMode : %d\t\n", i,
				pOutputInfo->m_dioDesc.DeviceName,
				pOutputInfo->m_dioDesc.DesktopCoordinates.left,
				pOutputInfo->m_dioDesc.DesktopCoordinates.top,
				pOutputInfo->m_dioDesc.DesktopCoordinates.right,
				pOutputInfo->m_dioDesc.DesktopCoordinates.bottom,
				(int)pOutputInfo->m_dimMode_Vector.size()
			);
			//연장시에는 left:1680, right : 3360;

			DXGI_MODE_DESC* pModeDesc;
			for (int i = 0; i < pOutputInfo->m_dimMode_Vector.size(); i++) {
				pModeDesc = &pOutputInfo->m_dimMode_Vector[i];
				_ftprintf(fp, L"\t\tDislayMode[%d] Width : %d height : %d FORMAT : %d RefreshRate: %d-%d \t\n",
					i, pModeDesc->Width, pModeDesc->Height, pModeDesc->Format,
					pModeDesc->RefreshRate.Numerator, pModeDesc->RefreshRate.Denominator);
			}
		}
	}

	fclose(fp);
	MessageBox(NULL, _T("DeviceInfo.txt 파일을 성공적으로 생성하였습니다."), _T("파일생성"), MB_OK);

	HRESULT hr = S_OK;

	V_FRETURN(CreateGIFactory());
	V_FRETURN(CreateDevice());
	V_FRETURN(CreateSwapChain(g_hWnd, g_uClientWidth, g_uClientHegiht));
	V_FRETURN(SetRenderTargetView());
	V_FRETURN(SetViewPort());

	return true;
}

bool coreC_DX::gameRun()
{
	gameFrame();
	gamePreRender();
	gameRender();
	gamePostRender();
	return true;
}

bool coreC_DX::gameFrame()
{
	return true;
}

bool coreC_DX::gamePreRender()
{
	return true;
}

bool coreC_DX::gameRender()
{
	DXGI_SWAP_CHAIN_DESC CurrentSD;
	m_pSwapChain->GetDesc(&CurrentSD);
	GetClientRect(g_hWnd, &g_rtClient);

	float ClearColor[4] = { 1.0f, 1.0f, 1.0f, 0.0f }; //r,g,b,a
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTagetView, ClearColor);

	m_pSwapChain->Present(0, 0);
	return true;
}

bool coreC_DX::gamePostRender()
{
	return true;
}

bool coreC_DX::gameRelease()
{
	if (!CreanupDevice()) { return false; }
	return true;
}

coreC_DX::~coreC_DX()
{
}