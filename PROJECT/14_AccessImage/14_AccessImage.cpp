#include "14_AccessImage.h"

AccessImage::AccessImage(LPCTSTR LWndName) : coreC_DX(LWndName)
{
	m_pTextureSrc = nullptr;
	m_pTextureDest = nullptr;
	m_pBackBuffer = nullptr;
}

//--

ID3D11Texture2D* AccessImage::GetTexture2DFromFile(LPCWSTR filename, D3DX11_IMAGE_LOAD_INFO* pLoadInfo)
{
	ID3D11Texture2D* texture = nullptr;
	ID3D11Resource* pRes = nullptr;

	HRESULT hr;

	hr = D3DX11CreateTextureFromFile(m_pD3dDevice, filename, pLoadInfo, NULL, &pRes, NULL);
	if (FAILED(hr)) {
		return NULL;
	}

	pRes->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&texture);
	pRes->Release();
	return texture;
}


ID3D11Texture2D* AccessImage::CopyTexture(ID3D11Texture2D* pSrcTexture)
{
	D3D11_TEXTURE2D_DESC desc;
	pSrcTexture->GetDesc(&desc);

	ID3D11Texture2D* NewTexture2D;
	//원본과 같은 정보로 2DTexture를 생성한 후 
	HRESULT hr = m_pD3dDevice->CreateTexture2D(&desc, 0, &NewTexture2D);
	if (FAILED(hr)) {
		MessageBox(0, L"CreateTexture2D FAILED", 0, 0);
		return NULL;
	}

	//원본을 복사함. 
	m_pImmediateContext->CopyResource(NewTexture2D, pSrcTexture);
	return NewTexture2D;
}

void AccessImage:: WriteDotPixel(ID3D11Texture2D* pTexDest)
{
	D3D11_TEXTURE2D_DESC desc;
	pTexDest->GetDesc(&desc);

	D3D11_MAPPED_SUBRESOURCE MappedFaceDest;

	if (SUCCEEDED(m_pImmediateContext->Map((ID3D11Resource*)pTexDest, 0, D3D11_MAP_READ_WRITE, 0, &MappedFaceDest))) {
		BYTE* pDestBytes = (BYTE*)MappedFaceDest.pData;

		for (UINT y = 0; y < desc.Height; y++) {
			BYTE* pDest = pDestBytes;
			for (UINT x = 0; x < desc.Width; x++) {
				if (x % 20 == 0 || y % 20 == 0) {
					*pDest++ = 0;    //B
					*pDest++ = 0;    //G
					*pDest++ = 255;  //R
					*pDest++ = 0;
				}
				else {
					pDest += 4;
				}
			}
			pDestBytes += MappedFaceDest.RowPitch;
		}
		m_pImmediateContext->Unmap(pTexDest, 0);
	}
}

bool AccessImage::Init()
{
	HRESULT hr = getSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
	if (FAILED(hr)) {
		return false;
	}

	m_pBackBuffer->GetDesc(&m_descBackBuffer);

	D3DX11_IMAGE_LOAD_INFO d3d_image_load_info;
	d3d_image_load_info.Usage = D3D11_USAGE_STAGING;
	d3d_image_load_info.CpuAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	d3d_image_load_info.BindFlags = 0;
	d3d_image_load_info.MipLevels = 1;
	d3d_image_load_info.Width = m_descBackBuffer.Width;
	d3d_image_load_info.Height = m_descBackBuffer.Height;
	d3d_image_load_info.Format = m_descBackBuffer.Format;
	d3d_image_load_info.Filter = D3DX11_FILTER_LINEAR;

	m_pTextureSrc = GetTexture2DFromFile(TEXT("../../INPUT/DATA/image/Desert.jpg"), &d3d_image_load_info);
	if (m_pTextureSrc == NULL) {
		return false;
	}
	
	m_pTextureDest = CopyTexture(m_pTextureSrc); //원본을 복사

	WriteDotPixel(m_pTextureDest); //복사된 텍스쳐의 짝수번째 픽셀에 빨강색을 넣음.

	//D3DX11SaveTextureToFile(m_pImmediateContext, m_pTextureDest, D3DX11_IFF_BMP, _T("../../INPUT/DATA/image/aaa.bmp"));

	m_pTextureDest->GetDesc(&m_descDesert);
	m_SrcRegion.left = 0;
	m_SrcRegion.right = m_descDesert.Width;
	m_SrcRegion.top = 0;
	m_SrcRegion.bottom = m_descDesert.Height;
	m_SrcRegion.front = 0;
	m_SrcRegion.back = 1;

	return true;
}

bool AccessImage::Render()
{
	m_pImmediateContext->CopySubresourceRegion(m_pBackBuffer, 0, 0, 0, 0, m_pTextureDest, 0, &m_SrcRegion);
	return true;
}

bool AccessImage::Release()
{
	if (m_pTextureSrc) { m_pTextureSrc->Release(); }
	if (m_pTextureDest) { m_pTextureDest->Release(); }
	if (m_pBackBuffer) { m_pBackBuffer->Release(); }

	return true;
}



//--

//---core꺼
bool AccessImage::gameInit()
{
	//디바이스 생성 작업 실행.
	InitDevice();
	m_GameTimer.Init();


	//SwapChain의 백버퍼 정보로 DXWrite객체 생성 
	IDXGISurface1* pBackBuffer = nullptr;
	HRESULT hr = getSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
	m_Font.Init();
	m_Font.Set(pBackBuffer);

	if (pBackBuffer) {
		pBackBuffer->Release();
	}

	//DXInput Device 생성
	if (!I_Input.InitDirectInput(true, true)) {
		return false;
	}

	//DXInput 초기화
	if (!I_Input.Init()) {
		return false;
	}

	Init();

	return true;
}

bool AccessImage::gameRun()
{
	gameFrame();
	gamePreRender();
	gameRender();
	gamePostRender();
	return true;
}

bool AccessImage::gameFrame()
{
	m_GameTimer.Frame();

	if (!I_Input.Frame()) { return false; }

	Frame();

	return true;
}

bool AccessImage::gamePreRender()
{
	DXGI_SWAP_CHAIN_DESC CurrentSD;
	m_pSwapChain->GetDesc(&CurrentSD);
	GetClientRect(g_hWnd, &g_rtClient);

	m_Font.DrawTextBegin();
	return true;
}

bool AccessImage::gameRender()
{
	//ID3D11RenderTargetView 객체에 컬러를 채운다. (BackBuffer를 지운다.)
	float r = 0.21f;
	float g = 0.32f;
	float b = 0.45f;

	float ClearColor[4] = { r, g, b, 0.0f }; //r,g,b,a
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTagetView, ClearColor);

	TCHAR pBuffer[256];
	memset(pBuffer, 0, sizeof(TCHAR) * 256);

	m_Font.SetTextPos();
	m_Font.SetlayoutRt(0, 0, (FLOAT)g_uClientWidth, (FLOAT)g_uClientHeight);
	m_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	m_Font.SetTextColor(ColorF(1, 1, 1, 1));

	_stprintf_s(pBuffer, _T("FPS:%d, SPF:%10.5f, GameTime:%10.2f"),
		m_GameTimer.GetFPS(), m_GameTimer.GetSPF(), m_GameTimer.GetGameTime());
	m_Font.DrawText(pBuffer);


	m_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	//m_Font.SetTextPos(Matrix3x2F::Rotation(g_GameTimer*100, Point2F(400, 300)));
	m_Font.SetTextColor(ColorF(1, 0, 0, 1));

	int iCount = 0;

	static LONG MousePosX = I_Input.m_MouseCurState.lX;
	static LONG MousePosY = I_Input.m_MouseCurState.lY;
	static LONG MousePosZ = I_Input.m_MouseCurState.lZ;

	MousePosX += I_Input.m_MouseCurState.lX;
	MousePosY += I_Input.m_MouseCurState.lY;
	MousePosZ += I_Input.m_MouseCurState.lZ;

	_stprintf_s(pBuffer, _T("Mouse X:%ld, Y:%ld, Z:%ld"), MousePosX, MousePosY, MousePosZ);

	FLOAT iStartX = 0;
	FLOAT iStartY = (FLOAT)(50 + (20 * iCount));
	m_Font.SetlayoutRt(iStartX, iStartY, (FLOAT)g_uClientWidth, (FLOAT)g_uClientHeight);
	m_Font.DrawText(pBuffer);
	iCount++;


	for (int iKey = 0; iKey < KeyStateCount; iKey++) {
		if (I_Input.m_KeyCurState[iKey] & 0x80) {
			_stprintf_s(pBuffer, _T("Key State : 0x%02x : %d"), iKey, I_Input.m_KeyCurState[iKey]);
			UINT iStartX = 0;
			UINT iStartY = 50 + (20 * iCount);
			m_Font.SetlayoutRt((FLOAT)iStartX, (FLOAT)iStartY, (FLOAT)g_uClientWidth, (FLOAT)g_uClientHeight);
			m_Font.DrawText(pBuffer);

			iCount++;
		}
	}

	for (int iKey = 0; iKey < 4; iKey++) {
		if (I_Input.m_MouseCurState.rgbButtons[iKey] & 0x80) {
			_stprintf_s(pBuffer, _T("Mouse Button State : %02d"), iKey);
			UINT iStartX = 0;
			UINT iStartY = 50 + (20 * iCount);
			m_Font.SetlayoutRt((FLOAT)iStartX, (FLOAT)iStartY, (FLOAT)g_uClientWidth, (FLOAT)g_uClientHeight);
			m_Font.DrawText(pBuffer);

			iCount++;
		}
	}

	Render();

	return true;
}

bool AccessImage::gamePostRender()
{
	//IDXGISwapChain 객체를 사용하여 시연(출력)한다.
	//모든 렌더링 작업들은 present앞에서 이뤄져야 한다.
	m_Font.DrawTextEnd();
	m_pSwapChain->Present(0, 0);
	return true;
}

bool AccessImage::gameRelease()
{
	Release();
	if (!I_Input.Release()) { return false; }
	if (!m_Font.Release()) { return false; }
	if (!m_GameTimer.Release()) { return false; }
	if (!CleanupDevice()) { return false; }
	return true;
}
//core꺼

AccessImage::~AccessImage()
{

}