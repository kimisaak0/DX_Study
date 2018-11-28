#include "01_deviceC_DX.h"

deviceC_DX::deviceC_DX()
{
	//�����(�׷���ī��)�� ����Ͽ� ����̽� ��ü�� �����ؾ� �ϹǷ� NULL�� ����.
	m_d3dDriverType = D3D_DRIVER_TYPE_NULL;

	//���̴�5.0�� ����ؾ� �ϹǷ� 11�� ����.
	m_d3dFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	//���� �� ���� �� �ʱ�ȭ. 
	m_pD3dDevice = nullptr;
	m_pImmediateContext = nullptr;
	m_pGIFactory = nullptr;
	m_pSwapChain = nullptr;

	m_pRenderTagetView = nullptr;

	m_bFullScrFlag = FALSE;
}


//ID3D11Device �������̽��� �����Ѵ�.
HRESULT deviceC_DX::CreateDevice()
{
	HRESULT hr;
	//d2d�� ������ �� �÷��׸� �����.
	UINT uCreateDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;  //����̽� ���� �÷���

#ifdef _DEBUG
	uCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; //����� ���̾� ����
#endif

													 //����̽� ���� Ÿ��
	D3D_DRIVER_TYPE dxDriverTypes[] =
	{
		D3D_DRIVER_TYPE_UNKNOWN,  //����̽� ��ü�� ������ �� �ִ� �ֻ��� ����̺� Ÿ���� �ڵ������� ���õȴٴµ�...?
		D3D_DRIVER_TYPE_HARDWARE,   //�ּ�
		D3D_DRIVER_TYPE_WARP,       //����
		D3D_DRIVER_TYPE_REFERENCE   //�־� (�׷��� ī�尡 �� �����ٶ� ���߿����� ���)
	};
	UINT uNumDriverTypes = sizeof(dxDriverTypes) / sizeof(dxDriverTypes[0]);

	//���õ� �� �ִ� ��ó���� �迭
	D3D_FEATURE_LEVEL dxFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
	};
	UINT uNumFeatureLevels = sizeof(dxFeatureLevels) / sizeof(dxFeatureLevels[0]);

	//���ķ����� 11�� ������ ������ ������ ���� �ݺ���
	for (UINT uDriverTypeIndex = 0; uDriverTypeIndex < uNumDriverTypes; uDriverTypeIndex++) {

		m_d3dDriverType = dxDriverTypes[uDriverTypeIndex];
	
		hr = D3D11CreateDevice(
			NULL,                  //���÷��� �ý���(�����) NULL�̸� �ֵ��÷��̷� �ڵ� ���õ�.
			m_d3dDriverType,       //����̹� Ÿ�� ����.
			NULL,                  //Ư�� ����Ʈ������ ����� ����ϴ� ����̽��� ���鶧 ���.
			uCreateDeviceFlags,    //����̽� ���� �÷���
			dxFeatureLevels,       //���õ� �� �ִ� ��ó ������ ����ִ� �迭
			uNumFeatureLevels,     //���� �迭�� ���Ҽ�
			D3D11_SDK_VERSION,     //SDK ����
			&m_pD3dDevice,         //������ ����̽��� ��ȯ���� �ּ�
			&m_d3dFeatureLevel,    //���õ� ��ó������ ��ȯ���� �ּ�.
			&m_pImmediateContext); //������ DC�� ��ȯ���� �ּ�.

		//����̽��� �����ϴµ� �����Ͽ����� ������ 11�� �ƴ� ��� �ٽ� �����ϰ� �Ѵ�.
		if (SUCCEEDED(hr)) {
			if (FAILED(hr) || m_d3dFeatureLevel < D3D_FEATURE_LEVEL_11_0) {
				if (m_pImmediateContext) { m_pImmediateContext->Release(); }
				if (m_pD3dDevice) { m_pD3dDevice->Release(); }
				continue;
			} break;
		}
	}

	if (FAILED(hr)) {
		return false;
	}
	return S_OK;
}

//DXGIFactory �������̽��� �����Ѵ�. 
HRESULT	deviceC_DX::CreateGIFactory()
{
	if (m_pD3dDevice == nullptr) { return E_FAIL; }
	HRESULT hr;

	IDXGIDevice* pDXGIDevice;
	IDXGIAdapter* pDXGIAdapter;

	//�����Ǿ� �ִ� ID3D11Device�κ��� ����ؼ� IDXGIFactory�� �Ѱܹ޴´�.
	hr = m_pD3dDevice-> QueryInterface  (__uuidof(IDXGIDevice),  (LPVOID*)(&pDXGIDevice));
	hr = pDXGIDevice->  GetParent       (__uuidof(IDXGIAdapter), (LPVOID*)(&pDXGIAdapter));
	hr = pDXGIAdapter-> GetParent       (__uuidof(IDXGIFactory), (LPVOID*)(&m_pGIFactory));

	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	return hr;
}

//DXGIFactory �������̽��κ��� IDXGISwapChain �������̽��� �����Ѵ�.
HRESULT	deviceC_DX::CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight)
{
	HRESULT hr = S_OK;
	if (m_pGIFactory == nullptr) { return S_FALSE; }

	//����ü�� ����ü�� ������ �� �ʿ��� ������ ä���� �̸� �̿��� ����ü�� ��ü�� �����Ѵ�.
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount = 1;  //1�̻� �ʼ� �Է�         

	sd.BufferDesc.Width = iWidth;                        //������ ����
	sd.BufferDesc.Height = iHeight;                      //������ ����
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;   //������ ���� ���� (�ʼ�)
	sd.BufferDesc.RefreshRate.Numerator = 60;            //ȭ�� �ֻ��� (����)
	sd.BufferDesc.RefreshRate.Denominator = 1;           //ȭ�� �ֻ��� (�и�)
	//sd.BufferDesc.ScanlineOrdering                     //�ø����� �� ���� ������ ��� ó������
	//sd.BufferDesc.Scaling                              //������ ����.

	sd.SampleDesc.Count = 1;      // ��� �Ѹ��� (1�̻� �ʼ�) 1�̸� ��Ƽ���ø� ���ϴ°� (
	sd.SampleDesc.Quality = 0;    //�̹��� ǰ�� ����
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //���� �뵵
	sd.OutputWindow = hWnd; //��� �����쿡 �Ѹ��� (�ʼ�)
	sd.Windowed = true;     //0���� �ʱ�ȭ�ϸ� ��üȭ������ ����� (false ��üȭ��, true â���)
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // IDXGISwapChain::ResizeTarget�� ȣ���Ͽ� ��带 ��ȯ�� �� �ְ� ��.
						                               // ��üȭ�� ���� ��ȯ�� ���� ȭ�� �ػ󵵸� �������� ������ ũ�Ⱑ �ڵ����� ������� �ʰ� ��.
	//sd.SwapEffect //�⺻�� ���

	//����ü�� ����
	hr = m_pGIFactory->CreateSwapChain(m_pD3dDevice, &sd, &m_pSwapChain);

	if (FAILED(hr)) {
		return hr;
	}

	return hr;
}

//����Ÿ�ٺ� ���� �� ����
HRESULT	deviceC_DX::SetRenderTargetView()
{
	HRESULT hr = S_OK;

	ID3D11Texture2D* pBackBuffer;

	//����۸� �޾ƿ�
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr)) {
		return hr;
	}

	//���� Ÿ�� �� ����
	hr = m_pD3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTagetView);
	pBackBuffer->Release();
	if (FAILED(hr)) {
		return hr;
	}

	//����Ÿ�ٺ� ����
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTagetView, nullptr);
	return S_OK;
}

//����Ʈ ����
HRESULT	deviceC_DX::SetViewPort()
{
	//����ü�� ������ ������.
	DXGI_SWAP_CHAIN_DESC Desc;
	m_pSwapChain->GetDesc(&Desc);

	g_uClientWidth = Desc.BufferDesc.Width;
	g_uClientHeight = Desc.BufferDesc.Height;

	//����Ʈ�� ���̿� ���̸� ����ü�� ������ ũ��� ����
	m_d3dViewPort.Width = (FLOAT)Desc.BufferDesc.Width;
	m_d3dViewPort.Height = (FLOAT)Desc.BufferDesc.Height;
	m_d3dViewPort.MinDepth = 0.0f;  //���̰��� 0���� 1���̷� ���ѵ�
	m_d3dViewPort.MaxDepth = 1.0f;
	m_d3dViewPort.TopLeftX = 0;     //�۾������� ���� ��ǥ��
	m_d3dViewPort.TopLeftY = 0;

	//����Ÿ�Ϻ� ����
	m_pImmediateContext->RSSetViewports(1, &m_d3dViewPort);

	return S_OK;
}


//��ü �����ϱ�
HRESULT deviceC_DX::InitDevice()
{
	HRESULT hr = S_OK;

	if (FAILED(hr = CreateDevice())) {
		//MessageBox(0, _T("Failed Create Device"), _T("Fatal Error"), MB_OK);
		return hr;
	}

	if (FAILED(hr = CreateGIFactory())) {
		//MessageBox(0, _T("Failed Create GIFactory"), _T("Fatal Error"), MB_OK);
		return hr;
	}
		
	if (FAILED(hr = CreateSwapChain(g_hWnd, g_uClientWidth, g_uClientHeight))) {
		//MessageBox(0, _T("Failed Create SwapChain"), _T("Fatal Error"), MB_OK);
		return hr; 
	}

	if (FAILED(hr = SetRenderTargetView())) { 
		//MessageBox(0, _T("Failed Set RenderTargetView"), _T("Fatal Error"), MB_OK);
		return hr; 
	}

	if (FAILED(hr = SetViewPort())) { 
		//MessageBox(0, _T("Failed Set ViewPort"), _T("Fatal Error"), MB_OK);
		return hr;
	}

	//ALT+ENTER�� �޽���ť ����͸��� ���´�.
	m_pGIFactory->MakeWindowAssociation(g_hWnd, DXGI_MWA_NO_ALT_ENTER  | DXGI_MWA_NO_WINDOW_CHANGES); 

	return hr;
}

//�����ϱ�
bool deviceC_DX::CreanupDevice()
{
	//â���� ������ �����Ѵ�.
	m_pSwapChain->SetFullscreenState(FALSE, NULL);

	//������ ������ ����.
	//���ð��� ���������ְ� �����Ѵ�.
	if (m_pImmediateContext) { m_pImmediateContext->ClearState(); }
	if (m_pImmediateContext) { m_pImmediateContext->Release(); }
	m_pImmediateContext = nullptr;

	if (m_pRenderTagetView) { m_pRenderTagetView->Release(); }
	m_pRenderTagetView = nullptr;

	if (m_pSwapChain) { m_pSwapChain->Release(); }
	m_pSwapChain = nullptr;

	if (m_pD3dDevice) { m_pD3dDevice->Release(); }
	m_pD3dDevice = nullptr;

	if (m_pGIFactory) { m_pGIFactory->Release(); }
	m_pGIFactory = nullptr;

	return true;
}

//get�Լ�
ID3D11Device *           deviceC_DX::getDevice()
{
	assert(m_pD3dDevice);
	return m_pD3dDevice;
}

ID3D11DeviceContext*   	 deviceC_DX::getContext()
{
	assert(m_pImmediateContext);
	return m_pImmediateContext;
}

IDXGIFactory*          	 deviceC_DX::getGIFactory()
{
	assert(m_pGIFactory);
	return m_pGIFactory;
}

IDXGISwapChain*          deviceC_DX::getSwapChain()
{
	assert(m_pSwapChain);
	return m_pSwapChain;
}

ID3D11RenderTargetView*	 deviceC_DX::getRenderTargetView()
{
	assert(m_pRenderTagetView);
	return m_pRenderTagetView;
}

//��ũ�� ��� ����
bool deviceC_DX::GetFullScrFlag()
{
	return m_bFullScrFlag;
}

void deviceC_DX::SetFullScrFlag(bool bFlag)
{
	m_bFullScrFlag = bFlag;
}

//��Ÿ �Լ�

//ȭ�� ũ�Ⱑ ����Ǹ� ���۹��� ũ�⸦ �����ϰ� ������ ������ ����Ÿ�Ϻ並 ������Ѵ�.
HRESULT deviceC_DX::ResizeDevice(UINT iWidth, UINT iHeight)
{
	//����̽��� �������� ������ false�� ��ȯ.
	if (m_pD3dDevice == nullptr) { return false; }

	HRESULT hr;

	//���� Ÿ�� �� ���� �� ����
	m_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	if (m_pRenderTagetView) { m_pRenderTagetView->Release(); }

	//������� ũ�⸦ �����Ѵ�.
	DXGI_SWAP_CHAIN_DESC CurrentSD, AfterSD;
	m_pSwapChain->GetDesc(&CurrentSD);
	m_pSwapChain->ResizeBuffers(
		CurrentSD.BufferCount,                  // ����ü�� ���ۼ�
		iWidth, 					            // ���Ӱ� ������ ������� ����
		iHeight, 					            // ���Ӱ� ������ ������� ����
		CurrentSD.BufferDesc.Format,            // ���Ӱ� ������ ������� ��������
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH  // ���Ӱ� ������ ����ü�� ��� �÷���.  DXGI_SWAP_CHAIN_FLAG���� �ϳ�
	);								 

	//����� �� ������ ũ�⸦ ��´�.
	m_pSwapChain->GetDesc(&AfterSD);
	GetClientRect(g_hWnd, &g_rtClient);
	g_uClientWidth = AfterSD.BufferDesc.Width;
	g_uClientHeight = AfterSD.BufferDesc.Height;

	//����Ÿ�Ϻ�� ����Ʈ�� ���� �� �����Ѵ�.
	if (FAILED(hr = SetRenderTargetView())) { return hr; }
	if (FAILED(hr = SetViewPort())) { return hr; }

	return S_OK;
}

deviceC_DX::~deviceC_DX()
{

}