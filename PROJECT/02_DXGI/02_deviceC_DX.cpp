#include "02_deviceC_DX.h"

#ifndef V_FRETURN
  #define V_FRETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; } }
#endif

//추가된 부분 1
static HMODULE s_hModDXGI   = NULL;
static HMODULE s_hModD3D11 = NULL;


typedef HRESULT (WINAPI* LPCREATEDXGIFACTORY)(REFIID, void**);
typedef HRESULT(WINAPI* LPD3D11CREATEDEVICE)(
	__in_opt IDXGIAdapter* pAdapter,
	D3D_DRIVER_TYPE DriverType,
	HMODULE Software,
	UINT Flags,
	__in_ecount_opt(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
	UINT FeatureLevels,
	UINT SDKVersion,
	__out_opt ID3D11Device** ppDevice,
	__out_opt D3D_FEATURE_LEVEL* pFeatureLevel,
	__out_opt ID3D11DeviceContext** ppImmediateContext
);
	
static LPCREATEDXGIFACTORY s_DynamicCreateDXGIFactory = NULL;
static LPD3D11CREATEDEVICE s_DynamicD3D11CreateDevice = NULL;

//DX11이 설치되어 있는지 확인하는 함수
static bool EnsureD3d10APIs()
{
	if (s_hModD3D11 != NULL || s_hModDXGI != NULL) { return true; }

	//This may fail if Direct3D 11 isn't installed.
	s_hModD3D11 = LoadLibrary(_T("d3d11.dll"));

	if (s_hModD3D11) {
		s_DynamicD3D11CreateDevice = (LPD3D11CREATEDEVICE)GetProcAddress(s_hModD3D11, "D3D11CreateDevice");
	}

	s_hModDXGI = LoadLibrary(_T("dxgi.dll"));
	if (s_hModDXGI) {
		s_DynamicCreateDXGIFactory = (LPCREATEDXGIFACTORY)GetProcAddress(s_hModDXGI, "CreateDXGIFactory");
	}

	return (s_hModDXGI != NULL) && (s_hModD3D11 != NULL);
}

//=======

deviceC_DX::deviceC_DX()
{
	m_d3dDriverType = D3D_DRIVER_TYPE_NULL;
	m_d3dFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	//g_d3dViewPort = ... 현재 결정 불가?

	m_pD3dDevice = nullptr;
	m_pSwapChain = nullptr;
	m_pRenderTagetView = nullptr;
	m_pImmediateContext = nullptr;
	//g_pGIFactory         = nullptr;
}

//추가된 부분 2
bool   deviceC_DX::Start()
{
	if (!EnsureD3d10APIs()) {
		WCHAR strBuffer[512];
		wcscpy_s(strBuffer, ARRAYSIZE(strBuffer), _T(" This application requires a Direct3D11 class \n device (hardware or reference rasterizer) running on Windows Vistar (or later)."));
		MessageBox(0, strBuffer, _T("Could not initialize Direct3D11"), MB_OK);
		return false;
	}
	return true;
}

//요청한 모드의 기능 이상의 모드를 검색한다.
DXGI_MODE_DESC deviceC_DX::FindClosesMatchingMode(DXGI_MODE_DESC& Desc, ID3D11Device* pd3dDevice)
{
	DXGI_MODE_DESC FindDesc;
	enumAdapterC_DX* pAdapterInfo;

	for (int i = 0; i < m_enumeratoin.m_eacInfo_vector.size(); i++) {
		pAdapterInfo = m_enumeratoin.m_eacInfo_vector[i];

		//지원여부에 대한 확인이지만 11에서는 의미가 없다.
		//LARGE_INTEGER DriverVersion; //user mode driver version
		//if (pAdapterInfo->m_pAdapter->CheckInterfaceSupport(__uuidof(ID3D11Device), &DriverVersion) != DXGI_ERROR_UNSUPPORTED) {
		//	continue;
		//}

		enumOutputC_DX* pOutputInfo;
		for (int i = 0; i < pAdapterInfo->m_eocInfo_vector.size(); i++) {
			pOutputInfo = pAdapterInfo->m_eocInfo_vector[i];
			if (SUCCEEDED(pOutputInfo->m_pOutput->FindClosestMatchingMode(&Desc, &FindDesc, pd3dDevice))) {
				return FindDesc;
			}
		}
	}
	return FindDesc;
}

//====

//ID3D11Device 인터페이스를 생성한다.
HRESULT deviceC_DX::CreateDevice()
{
	HRESULT hr;
	UINT uCrateDeviceFlags = 0;

#ifdef _DEBUG
	uCrateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE dxDriverTypes[] =
	{
		D3D_DRIVER_TYPE_UNKNOWN,
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT uNumDriverTypes = sizeof(dxDriverTypes) / sizeof(dxDriverTypes[0]);

	D3D_FEATURE_LEVEL dxFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
	};
	UINT uNumFeatureLevels = sizeof(dxFeatureLevels) / sizeof(dxFeatureLevels[0]);

	//IDXGIAdapter* pAdapter = NULL;        
	//m_pGIFactory->EnumAdapters( 0, &pAdapter ); 

	for (UINT uDriverTypeIndex = 0; uDriverTypeIndex < uNumDriverTypes; uDriverTypeIndex++) {
		m_d3dDriverType = dxDriverTypes[uDriverTypeIndex];

		hr = D3D11CreateDevice(
			nullptr,               //__in_opt IDXGIAdapter* pAdapter,
			m_d3dDriverType,       //D3D_DRIVER_TYPE DriverType,
			NULL,                  //HMODULE Software,
			uCrateDeviceFlags,     //UINT Flags,
			dxFeatureLevels,       //__in_ecount_opt(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
			uNumFeatureLevels,     //UINT FeatureLevels,
			D3D11_SDK_VERSION,     //UINT SDKVersion,
			&m_pD3dDevice,         //__out_opt ID3D11Device** ppDevice,
			&m_d3dFeatureLevel,    //__out_opt D3D_FEATURE_LEVEL* pFeatureLevel,
			&m_pImmediateContext); //__out_opt ID3D11DeviceContext** ppImmediateContext

		if (SUCCEEDED(hr)) {
			if (FAILED(hr) || m_d3dFeatureLevel < D3D_FEATURE_LEVEL_11_0) {
				if (m_pImmediateContext) { m_pImmediateContext->Release(); }
				if (m_pD3dDevice) { m_pD3dDevice->Release(); }
				continue;
			} break;
		}
	}
	// if(pAdapter) { pAdapter->Release(); }

	V_FRETURN(hr);
	return S_OK;
}

//DXGIFactory 인터페이스를 생성한다.
HRESULT	deviceC_DX::CreateGIFactory()
{
	//추가(수정)된 부분 3
	HRESULT hr = s_DynamicCreateDXGIFactory(__uuidof(IDXGIFactory), (LPVOID*)(&m_pGIFactory));

	if (FAILED(m_enumeratoin.Enumerate(m_pGIFactory))) {
		return hr;
	}

	return hr;
}

//DXGIFactory 인터페이스로부터 IDXGISwapChain 인터페이스를 생성한다.
HRESULT	deviceC_DX::CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight)
{
	HRESULT hr = S_OK;
	if (m_pGIFactory == nullptr) { return S_FALSE; }

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	//UINT BufferCount;
	sd.BufferCount = 1;

	//DXGI_MODE_DESC BufferDesc;
	sd.BufferDesc.Width = iWidth;                        //UINT Width;
	sd.BufferDesc.Height = iHeight;                      //UINT Height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;   //DXGI_FORMAT Format;
	sd.BufferDesc.RefreshRate.Numerator = 60;            //DXGI_RATIONAL RefreshRate; // 분자
	sd.BufferDesc.RefreshRate.Denominator = 1;           //DXGI_RATIONAL RefreshRate; // 분모
														 //sd.BufferDesc.ScanlineOrdering  //기본값 사용      //DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
														 //sd.BufferDesc.Scaling           //기본값 사용      //DXGI_MODE_SCALING Scaling;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    //DXGI_USAGE BufferUsage;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;    //UINT Count;
	sd.SampleDesc.Quality = 0;  //UINT Quality;
	sd.Windowed = true; 		//BOOL Windowed;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//sd.SwapEffect             //기본값 사용

	hr = m_pGIFactory->CreateSwapChain(m_pD3dDevice, &sd, &m_pSwapChain);

	V_FRETURN(hr);

	return hr;
}

HRESULT	deviceC_DX::SetRenderTargetView()
{
	HRESULT hr = S_OK;

	//Create a render target view
	ID3D11Texture2D* pBackBuffer;
	V_FRETURN(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer));
	V_FRETURN(m_pD3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTagetView));
	
	SAFE_RELEASE(pBackBuffer);

	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTagetView, nullptr);
	return S_OK;
}

HRESULT	deviceC_DX::SetViewPort()
{
	DXGI_SWAP_CHAIN_DESC Desc;
	m_pSwapChain->GetDesc(&Desc);

	//Setup the viewport
	m_d3dViewPort.Width = (FLOAT)Desc.BufferDesc.Width;
	m_d3dViewPort.Height = (FLOAT)Desc.BufferDesc.Height;
	m_d3dViewPort.MinDepth = 0.0f;
	m_d3dViewPort.MaxDepth = 1.0f;
	m_d3dViewPort.TopLeftX = 0;
	m_d3dViewPort.TopLeftY = 0;

	m_pImmediateContext->RSSetViewports(1, &m_d3dViewPort);

	return S_OK;
}


bool deviceC_DX::CreanupDevice()
{
	m_enumeratoin.ClearAdapterInfoList();

	FreeLibrary(s_hModD3D11);
	FreeLibrary(s_hModDXGI);

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