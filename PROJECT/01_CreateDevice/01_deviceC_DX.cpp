#include "01_deviceC_DX.h"

#ifndef V_FRETURN
  #define V_FRETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; } }
#endif

#ifndef SAFE_RELEASE
  #define SAFE_RELEASE(A)	 { if(A) { (A)->Release(); (A)=NULL; } }
#endif 

deviceC_DX::deviceC_DX()
{
	//�����(�׷���ī��)�� ����Ͽ� ����̽� ��ü�� �����ؾ� �ϹǷ� NULL�� ����.
	m_d3dDriverType = D3D_DRIVER_TYPE_NULL;

	//���̴�5.0�� ����ؾ� �ϹǷ� 11�� ����.
	m_d3dFeatureLevel = D3D_FEATURE_LEVEL_11_0; 

	//���� �� ���� �� �ʱ�ȭ. 
	m_pD3dDevice         = nullptr;
	m_pImmediateContext  = nullptr;
	m_pSwapChain         = nullptr;
	
	m_pRenderTagetView   = nullptr;
	//g_d3dViewPort = ���� ���� �ȵ�.

	m_pGIFactory         = nullptr;
}


//ID3D11Device �������̽��� �����Ѵ�.
HRESULT deviceC_DX::CreateDevice()
{
	HRESULT hr;
	UINT uCreateDeviceFlags = 0;  //����̽� ���� �÷���

#ifdef _DEBUG
	uCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; //����� ���̾� ����
#endif

	//����̽� ���� Ÿ��
	D3D_DRIVER_TYPE dxDriverTypes[] =
	{
		//D3D_DRIVER_TYPE_UNKNOWN,  //����̽� ��ü�� ������ �� �ִ� �ֻ��� ����̺� Ÿ���� �ڵ������� ���õȴٴµ�...?
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
			nullptr,               //���÷��� �ý���(�����) NULL�̸� �ֵ��÷��̷� �ڵ� ���õ�.
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
				if(m_pImmediateContext) { m_pImmediateContext->Release(); }
				if (m_pD3dDevice) { m_pD3dDevice->Release(); }
				continue;
			} break;
		}
	}

	V_FRETURN(hr);

	return S_OK;
}

//DXGIFactory �������̽��� �����Ѵ�.
HRESULT	deviceC_DX::CreateGIFactory()
{
	HRESULT hr;

	V_FRETURN(CreateDXGIFactory(__uuidof(IDXGIFactory), (LPVOID*)(&m_pGIFactory)));

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
	sd.Windowed = true;     //0���� �ʱ�ȭ�ϸ� ��üȭ������ �����
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //
	//sd.SwapEffect //�⺻�� ��� 


	V_FRETURN(m_pGIFactory->CreateSwapChain(m_pD3dDevice, &sd, &m_pSwapChain));

	return hr;
}


//����Ÿ�ٺ� ���� �� ����
HRESULT	deviceC_DX::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	
	ID3D11Texture2D* pBackBuffer;

	//����۸� �޾ƿ�
	V_FRETURN(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer));

	//���� Ÿ�� �� ����
	V_FRETURN(m_pD3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTagetView));

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
	

	//����Ʈ�� ���̿� ���̸� ����ü�� ������ ũ��� ����
	m_d3dViewPort.Width = (FLOAT)Desc.BufferDesc.Width;
	m_d3dViewPort.Height = (FLOAT)Desc.BufferDesc.Height;
	m_d3dViewPort.MinDepth = 0.0f;  //���̰��� 0���� 1���̷� ���ѵ�
	m_d3dViewPort.MaxDepth = 1.0f;
	m_d3dViewPort.TopLeftX = 0;     //�۾������� ���� ��ǥ��
	m_d3dViewPort.TopLeftY = 0;
	
	m_pImmediateContext->RSSetViewports(1, &m_d3dViewPort);

	return S_OK;
}


bool deviceC_DX::CreanupDevice()
{
	//������ ������ ����.
	//���ð��� ���������ְ� �����Ѵ�.
	if (m_pImmediateContext) { m_pImmediateContext->ClearState(); }

	SAFE_RELEASE(m_pImmediateContext);
	SAFE_RELEASE(m_pRenderTagetView);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pD3dDevice);
	SAFE_RELEASE(m_pGIFactory);

	return true;
}

	
deviceC_DX::~deviceC_DX()
{

}
//
////�Ѳ����� ����� ���
//HRESULT deviceC_DX::CreateDeviceAndSwapChain()
//{
//	//������ ���� �����Ŷ�... �պκ� ����
//	HRESULT hr;
//	hr = D3D11CreateDeviceAndSwapChain(
//		//���÷��� �ý���(�����)��, NULL�̸� �ֵ��÷��̾ �⺻���� ����,
//		//����̽� ����̹� Ÿ��
//		//���ϴ� ����Ʈ������ DLL�ڵ鰪�� �Ѱ��༭ �� ����Ʈ������ ����� ����ϴ� ����̽��� ��ȯ�ϰ� �� �� �ִ�. �� ������ NULL.
//		//����̽� ���� �÷��� ��
//		//���õ� �� �ִ� ��ó ���� �迭
//		//��ó ���� �迭�� ���Ҽ�
//		//SDK ����
//		//����ü�� �Ӽ� ����
//		//��ȯ�Ǵ� IDXGISwapChain �������̽� �ּ�
//		//��ȯ�Ǵ� ID3D11Device �������̽� �ּ�
//		//�Լ� ȣ�� ������ ù��° ��ó���� ��ȯ
//		//ID3D11DeviceContext �������̽� ��ȯ
//	);
//
//}
