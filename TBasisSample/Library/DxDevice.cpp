#include "DxDevice.h"

namespace Lypi
{
	ID3D11Device*              g_pD3dDevice;           // 디바이스 객체
	ID3D11DeviceContext*       g_pD3dContext;	       // 디바이스 컨텍스트
	IDXGISwapChain*            g_pSwapChain;		   // 스왑체인 객체
	ID3D11RenderTargetView*    g_pRenderTagetView;     // 메인 렌더타켓뷰 정보 얻기
	ID3D11DepthStencilView*    g_pDepthStencilView;    // 깊이 스텐실 정보 얻기
	D3D11_VIEWPORT             g_d3dViewPort;          // 뷰포트 정보 얻기

	DxDevice::DxDevice()
	{
		//어댑터(그래픽카드)를 사용하여 디바이스 객체를 생성해야 하므로 NULL로 선택.
		m_d3dDriverType = D3D_DRIVER_TYPE_NULL;

		//쉐이더5.0을 사용해야 하므로 11을 선택.
		m_d3dFeatureLevel = D3D_FEATURE_LEVEL_11_0;

		//선언 후 생성 전 초기화. 
		m_pD3dDevice = nullptr;
		m_pD3dContext = nullptr;
		m_pGIFactory = nullptr;
		m_pSwapChain = nullptr;

		m_pRenderTagetView = nullptr;
		m_pDepthStencilView = nullptr;
	}

#pragma region //디바이스 생성
	//ID3D11Device 인터페이스를 생성한다.
	HRESULT DxDevice::CreateDevice()
	{
		HRESULT hr;
		//d2d를 쓰려면 이 플래그를 써야함.
		UINT uCreateDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;  //디바이스 생성 플래그

		#if defined(DEBUG) || defined(_DEBUG)
		uCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif
		//디바이스 생성 타입
		D3D_DRIVER_TYPE dxDriverTypes[] =
		{
			//D3D_DRIVER_TYPE_UNKNOWN,    //디바이스 객체를 생성할 수 있는 최상의 드라이브 타입이 자동적으로 선택된다는데...?
			D3D_DRIVER_TYPE_HARDWARE,   //최선
			D3D_DRIVER_TYPE_WARP,       //차선
			D3D_DRIVER_TYPE_REFERENCE   //최악 (그래픽 카드가 안 받쳐줄때 개발용으로 사용)
		};
		UINT uNumDriverTypes = sizeof(dxDriverTypes) / sizeof(dxDriverTypes[0]);

		//선택될 수 있는 피처레벨 배열
		D3D_FEATURE_LEVEL dxFeatureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
		};
		UINT uNumFeatureLevels = sizeof(dxFeatureLevels) / sizeof(dxFeatureLevels[0]);

		//피쳐레벨이 11로 생성될 때까지 돌리기 위한 반복문
		for (UINT uDriverTypeIndex = 0; uDriverTypeIndex < uNumDriverTypes; uDriverTypeIndex++) {

			m_d3dDriverType = dxDriverTypes[uDriverTypeIndex];

			hr = D3D11CreateDevice(
				NULL,                  //디스플레이 시스템(어댑터) NULL이면 주디스플레이로 자동 선택됨.
				m_d3dDriverType,       //드라이버 타입 지정.
				NULL,                  //특정 소프트웨어의 모듈을 사용하는 디바이스를 만들때 사용.
				uCreateDeviceFlags,    //디바이스 생성 플래그
				dxFeatureLevels,       //선택될 수 있는 피처 레벨이 담겨있는 배열
				uNumFeatureLevels,     //위의 배열의 원소수
				D3D11_SDK_VERSION,     //SDK 버전
				&m_pD3dDevice,         //생성된 디바이스를 반환받을 주소
				&m_d3dFeatureLevel,    //선택된 피처레벨을 반환받을 주소.
				&m_pD3dContext);       //생성된 DC를 반환받을 주소.

		    //디바이스를 생성하는데 성공하였지만 버전이 11이 아닐 경우 다시 생성하게 한다.
			if (SUCCEEDED(hr)) {
				if (FAILED(hr) || m_d3dFeatureLevel < D3D_FEATURE_LEVEL_11_0) {
					if (m_pD3dContext) { m_pD3dContext->Release(); }
					if (m_pD3dDevice) { m_pD3dDevice->Release(); }
					continue;
				} break;
			}
		}

		if (FAILED(hr)) {
			return false;
		}

		g_pD3dDevice = m_pD3dDevice;
		g_pD3dContext = m_pD3dContext;

		return S_OK;
	}

	//DXGIFactory 인터페이스를 생성한다. 
	HRESULT	DxDevice::CreateGIFactory()
	{
		if (m_pD3dDevice == nullptr) { return E_FAIL; }

		HRESULT hr;
		IDXGIDevice* pDXGIDevice;
		IDXGIAdapter* pDXGIAdapter;

		//생성되어 있는 ID3D11Device로부터 출발해서 IDXGIFactory를 넘겨받는다.
		hr = m_pD3dDevice->QueryInterface(__uuidof(IDXGIDevice), (LPVOID*)(&pDXGIDevice));
		hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (LPVOID*)(&pDXGIAdapter));
		hr = pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (LPVOID*)(&m_pGIFactory));

		pDXGIDevice->Release();
		pDXGIAdapter->Release();
		return hr;
	}

	//DXGIFactory 인터페이스로부터 IDXGISwapChain 인터페이스를 생성한다.
	HRESULT	DxDevice::CreateSwapChain()
	{
		HRESULT hr = S_OK;
		if (m_pGIFactory == nullptr) { return S_FALSE; }

		//스왑체인 구조체를 생성한 뒤 필요한 내용을 채워서 이를 이용해 스왑체인 객체를 생성한다.
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));

		sd.BufferCount = 1;                                  //버퍼 개수         
		sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;   //버퍼의 색상 포맷 (필수)
		sd.BufferDesc.RefreshRate.Numerator = 60;            //화면 주사율 (분자)
		sd.BufferDesc.RefreshRate.Denominator = 1;           //화면 주사율 (분모)
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    //버퍼 용도
		sd.OutputWindow = g_hWnd;                            //어느 윈도우에 뿌릴지 (필수)
		sd.Windowed = true;                                  //false 전체화면, true 창모드
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		//샘플링 수준
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;

		//스왑체인 버퍼의 크기. 깊이스텐실뷰와 같은 크기로 생성해야 호환이 된다.
		//왜냐하면 스왑체인에서 백버퍼를 생성할 것이기 때문.
		sd.BufferDesc.Width = g_rtClient.right;
		sd.BufferDesc.Height = g_rtClient.bottom;

		//화면 크기 변경을 막아놓았기 때문에 
		//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; 
		//는 쓰지 않았다.

		//스왑체인 생성
		hr = m_pGIFactory->CreateSwapChain(m_pD3dDevice, &sd, &m_pSwapChain);
		if (FAILED(hr)) { return hr; }

		g_pSwapChain = m_pSwapChain;

		return hr;
	}

	//깊이 스텐실 뷰 생성
	HRESULT DxDevice::CreateDpethStencilView()
	{
		if (m_pD3dDevice == nullptr) { return E_FAIL; }

		HRESULT hr = S_OK;
		ID3D11Texture2D* m_pTex2D;  // 깊이 스텐실 버퍼

		D3D11_TEXTURE2D_DESC td;
		td.MipLevels = 1;    // 밉맵 갯수.
		td.ArraySize = 1;    // 텍스쳐 배열의 텍스쳐 수

		td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		td.Usage = D3D11_USAGE_DEFAULT;
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		//기타 옵션
		td.CPUAccessFlags = 0;
		td.MiscFlags = 0;

		//샘플링 수준
		td.SampleDesc.Count = 1;
		td.SampleDesc.Quality = 0;

		//깊이스텐실 버퍼의 크기. 백버퍼의 크기와 같아야 한다.
		td.Width = g_rtClient.right;
		td.Height = g_rtClient.bottom;

		hr = g_pD3dDevice->CreateTexture2D(&td, 0, &m_pTex2D);
		if (FAILED(hr)) { return hr; }

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		dsvd.Format = td.Format;

		//3차원이니까 2차원 자원을 깊이스텐실맵으로 사용.
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Texture2D.MipSlice = 0; //밉맵의 첫번째 인덱스.
		dsvd.Flags = 0;              //옵션값

		//깊이스텐실뷰 생성 (생성에 사용할 리소스, 생성 정보, 반환인자)
		hr = g_pD3dDevice->CreateDepthStencilView(m_pTex2D, &dsvd, &m_pDepthStencilView);
		if (FAILED(hr)) { return hr; }

		g_pDepthStencilView = m_pDepthStencilView;

		return hr;
	}

	//렌더타겟뷰 생성 및 세팅
	HRESULT	DxDevice::SetRenderTargetView()
	{
		HRESULT hr;
		ID3D11Texture2D* pBackBuffer;

		hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);  	//백버퍼를 받아옴
		hr = m_pD3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTagetView);  	//렌더 타겟 뷰 생성
		pBackBuffer->Release();

		g_pRenderTagetView = m_pRenderTagetView;

		return S_OK;
	}

	//뷰포트 세팅
	HRESULT	DxDevice::SetViewPort()
	{
		//스왑체인 정보를 가져옴.
		DXGI_SWAP_CHAIN_DESC Desc;
		m_pSwapChain->GetDesc(&Desc);

		//뷰포트의 시작 좌표
		m_d3dViewPort.TopLeftX = 0;
		m_d3dViewPort.TopLeftY = 0;

		//스왑체인값에서 뷰포트 크기를 가져옴
		m_d3dViewPort.Width = (FLOAT)Desc.BufferDesc.Width;
		m_d3dViewPort.Height = (FLOAT)Desc.BufferDesc.Height;

		//뷰포트의 깊이값은 0에서 1사이로 제한됨
		m_d3dViewPort.MinDepth = 0.0f;
		m_d3dViewPort.MaxDepth = 1.0f;

		//렌더타켓뷰 세팅
		m_pD3dContext->RSSetViewports(1, &m_d3dViewPort);

		g_d3dViewPort = m_d3dViewPort;

		return S_OK;
	}

	//전체 생성하기
	HRESULT DxDevice::InitDevice()
	{
		HRESULT hr;

		if (FAILED(hr = CreateDevice())) { return hr; }
		if (FAILED(hr = CreateGIFactory())) { return hr; }
		if (FAILED(hr = CreateSwapChain())) { return hr; }
		if (FAILED(hr = CreateDpethStencilView())) { return hr; }
		if (FAILED(hr = SetRenderTargetView())) { return hr; }
		if (FAILED(hr = SetViewPort())) { return hr; }

		//ALT+ENTER와 메시지큐 모니터링을 막는다.
		m_pGIFactory->MakeWindowAssociation(g_hWnd, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);

		return hr;
	}
#pragma endregion

	//정리하기
	bool DxDevice::CreanupDevice()
	{
		//삭제는 생성의 역순.
		//세팅값을 복원시켜주고 삭제한다.
		if (m_pD3dContext) { m_pD3dContext->ClearState(); }
		if (m_pD3dContext) { m_pD3dContext->Release(); }
		m_pD3dContext = g_pD3dContext = nullptr;

		if (m_pDepthStencilView) { m_pDepthStencilView->Release(); }
		m_pDepthStencilView = g_pDepthStencilView = nullptr;

		if (m_pRenderTagetView) { m_pRenderTagetView->Release(); }
		m_pRenderTagetView = g_pRenderTagetView = nullptr;

		if (m_pSwapChain) { m_pSwapChain->Release(); }
		m_pSwapChain = g_pSwapChain = nullptr;

		if (m_pD3dDevice) { m_pD3dDevice->Release(); }
		m_pD3dDevice = g_pD3dDevice = nullptr;

		if (m_pGIFactory) { m_pGIFactory->Release(); }
		m_pGIFactory = nullptr;

		return true;
	}


	DxDevice::~DxDevice()
	{

	}

}