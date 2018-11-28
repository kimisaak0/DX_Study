#include "12_TextureSample.h"

TextureSample::TextureSample(LPCTSTR LWndName) : coreC_DX(LWndName)
{
	m_pTextureDesert = nullptr;
	m_pTextureKoala = nullptr;
}

void             TextureSample::ErrorMessageBox(bool bPrint)
{
	TCHAR* lpMsgBuf;
	
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		          nullptr, GetLastError(),
		          MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		          (TCHAR*)&lpMsgBuf, 0, NULL);
	OutputDebugString((TCHAR*)lpMsgBuf);
	MessageBox(g_hWnd, lpMsgBuf, _T("�����߻�"), MB_OK);

	LocalFree(lpMsgBuf);
}

ID3D11Texture2D* TextureSample::GetTexture2DFromFile(LPCWSTR filename, D3DX11_IMAGE_LOAD_INFO* pLoadInfo)
{
	ID3D11Texture2D* Texture = nullptr;
	ID3D11Resource* pRes = nullptr;

	HRESULT hr = D3DX11CreateTextureFromFile(m_pD3dDevice, filename, pLoadInfo, nullptr, &pRes, nullptr);
	
	if (FAILED(hr)) {
		return nullptr;
	}

	pRes->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&Texture);
	pRes->Release();

	return Texture;
}

bool TextureSample::Init()
{
	HRESULT hr = getSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
	if (FAILED(hr)) {
		return false;
	}
	m_pBackBuffer->GetDesc(&m_descBackBuffer);

	//����ۿ� �����ϱ� ���� ���� �ؽ����� ��ȯ�� �����Ѵ�.
	//CopyResource()�Լ��� ����� ����̱� ������ �ݵ�� ������� ����,���� ũ�� �̻��̾�� �Ѵ�.
	D3DX11_IMAGE_LOAD_INFO loadInfo;
	ZeroMemory(&loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
	loadInfo.Width      = m_descBackBuffer.Width;
	loadInfo.Height     = m_descBackBuffer.Height;
	loadInfo.Depth      = D3DX11_DEFAULT;
	loadInfo.MipLevels  = 1; 
	loadInfo.Usage      = D3D11_USAGE_DEFAULT;
	loadInfo.Format     = m_descBackBuffer.Format;
	loadInfo.Filter     = D3DX11_FILTER_LINEAR;
	loadInfo.MipFilter  = D3DX11_FILTER_NONE;

	m_pTextureDesert = GetTexture2DFromFile(TEXT("../../INPUT/DATA/image/Desert.jpg"), &loadInfo);
	if (m_pTextureDesert == nullptr) {
		ErrorMessageBox(false);
		return false;
	}
	m_pTextureDesert->GetDesc(&m_descDesert);

	ZeroMemory(&loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
	loadInfo.Width = 300;
	loadInfo.Height = 400;
	loadInfo.Depth = D3DX11_DEFAULT;
	loadInfo.MipLevels = 1;
	loadInfo.Usage = D3D11_USAGE_DEFAULT;
	loadInfo.Format = m_descBackBuffer.Format;
	loadInfo.Filter = D3DX11_FILTER_LINEAR;
	loadInfo.MipFilter = D3DX11_FILTER_NONE;

	m_pTextureKoala = GetTexture2DFromFile(TEXT("../../INPUT/DATA/image/Koala.jpg"), &loadInfo);
	if (m_pTextureKoala == nullptr) {
		ErrorMessageBox(false);
		return false;
	}
	m_pTextureKoala->GetDesc(&m_descKoala);

	return true;
}

bool TextureSample::Frame()
{
	int iCenterX = m_descBackBuffer.Width / 2 - m_descKoala.Width / 2;
	int iCenterY = m_descBackBuffer.Height / 2 - m_descKoala.Height / 2;
	m_iPosX = cos(m_GameTimer.GetGameTime()) * iCenterX + iCenterX;
	m_iPosY = sin(m_GameTimer.GetGameTime()) * iCenterY + iCenterY;
	
	return true;
}

bool TextureSample::Render()
{
	//�ؽ��� ��ü�� �����Ѵ�. (��, ������� ���˰� �ؽ����� ������ ȣȯ �����ؾ� �Ѵ�.)
	m_pImmediateContext->CopyResource(m_pBackBuffer, m_pTextureDesert);

	//���� �ؽ�ó�� ��ü ���� �� �Ϻ� ���� ����
	D3D11_BOX srcRegion;
	srcRegion.left = 0;                    //�ؽ�ó�� X��ǥ ���۰�
	srcRegion.right = m_descKoala.Width;   //�ؽ�ó�� X��ǥ ����
	srcRegion.top = 0;                     //�ؽ�ó�� Y��ǥ ���۰�
	srcRegion.bottom = m_descKoala.Height; //�ؽ�ó�� Y��ǥ ����
	srcRegion.front = 0;
	srcRegion.back = 1;
	//���� �ؽ�ó�� ��ü �Ǵ� �Ϻ� ������ ������� 0,0 ��ġ�� �����Ѵ�.
	//(����)�ؽ�ó�� ������ ������� ������ ����� ���â�� ��� �޽����� �߻���.

	m_pImmediateContext->CopySubresourceRegion(m_pBackBuffer, 0, m_iPosX, m_iPosY, 0, m_pTextureKoala, 0, &srcRegion);

	return true;
}

bool TextureSample::Release()
{
	SAFE_RELEASE(m_pBackBuffer);
	SAFE_RELEASE(m_pTextureDesert);
	SAFE_RELEASE(m_pTextureKoala);

	return true;
}


//-----
bool TextureSample::gameInit()
{
	//����̽� ���� �۾� ����.
	InitDevice();
	m_GameTimer.Init();


	//SwapChain�� ����� ������ DXWrite��ü ���� 
	IDXGISurface1* pBackBuffer = nullptr;
	HRESULT hr = getSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
	m_Font.Init();
	m_Font.Set(pBackBuffer);

	if (pBackBuffer) {
		pBackBuffer->Release();
	}

	//DXInput Device ����
	if (!I_Input.InitDirectInput(true, true)) {
		return false;
	}

	//DXInput �ʱ�ȭ
	if (!I_Input.Init()) {
		return false;
	}

	Init();

	return true;
}

bool TextureSample::gameRun()
{
	gameFrame();
	gamePreRender();
	gameRender();
	gamePostRender();
	return true;
}

bool TextureSample::gameFrame()
{
	m_GameTimer.Frame();

	if (!I_Input.Frame()) { return false; }

	Frame();

	return true;
}

bool TextureSample::gamePreRender()
{
	DXGI_SWAP_CHAIN_DESC CurrentSD;
	m_pSwapChain->GetDesc(&CurrentSD);
	GetClientRect(g_hWnd, &g_rtClient);

	m_Font.DrawTextBegin();
	return true;
}

bool TextureSample::gameRender()
{
	//ID3D11RenderTargetView ��ü�� �÷��� ä���. (BackBuffer�� �����.)
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

bool TextureSample::gamePostRender()
{
	//IDXGISwapChain ��ü�� ����Ͽ� �ÿ�(���)�Ѵ�.
	//��� ������ �۾����� present�տ��� �̷����� �Ѵ�.
	m_Font.DrawTextEnd();
	m_pSwapChain->Present(0, 0);
	return true;
}

bool TextureSample::gameRelease()
{
	Release();
	if (!I_Input.Release()) { return false; }
	if (!m_Font.Release()) { return false; }
	if (!m_GameTimer.Release()) { return false; }
	if (!CleanupDevice()) { return false; }
	return true;
}

//--


TextureSample::~TextureSample()
{

}