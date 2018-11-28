#include "01_deviceC_DX.h"

#ifndef V_FRETURN
  #define V_FRETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; } }
#endif

#ifndef SAFE_RELEASE
  #define SAFE_RELEASE(A)	 { if(A) { (A)->Release(); (A)=NULL; } }
#endif 

deviceC_DX::deviceC_DX()
{
	//어댑터(그래픽카드)를 사용하여 디바이스 객체를 생성해야 하므로 NULL로 선택.
	m_d3dDriverType = D3D_DRIVER_TYPE_NULL;

	//쉐이더5.0을 사용해야 하므로 11을 선택.
	m_d3dFeatureLevel = D3D_FEATURE_LEVEL_11_0; 

	//선언 후 생성 전 초기화. 
	m_pD3dDevice         = nullptr;
	m_pImmediateContext  = nullptr;
	m_pSwapChain         = nullptr;
	
	m_pRenderTagetView   = nullptr;
	//g_d3dViewPort = 아직 설정 안됨.

	m_pGIFactory         = nullptr;
}


//ID3D11Device 인터페이스를 생성한다.
HRESULT deviceC_DX::CreateDevice()
{
	HRESULT hr;
	UINT uCreateDeviceFlags = 0;  //디바이스 생성 플래그

#ifdef _DEBUG
	uCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; //디버그 레이어 생성
#endif

	//디바이스 생성 타입
	D3D_DRIVER_TYPE dxDriverTypes[] =
	{
		//D3D_DRIVER_TYPE_UNKNOWN,  //디바이스 객체를 생성할 수 있는 최상의 드라이브 타입이 자동적으로 선택된다는데...?
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
			nullptr,               //디스플레이 시스템(어댑터) NULL이면 주디스플레이로 자동 선택됨.
			m_d3dDriverType,       //드라이버 타입 지정.
			NULL,                  //특정 소프트웨어의 모듈을 사용하는 디바이스를 만들때 사용.
			uCreateDeviceFlags,    //디바이스 생성 플래그
			dxFeatureLevels,       //선택될 수 있는 피처 레벨이 담겨있는 배열
			uNumFeatureLevels,     //위의 배열의 원소수
			D3D11_SDK_VERSION,     //SDK 버전
			&m_pD3dDevice,         //생성된 디바이스를 반환받을 주소
			&m_d3dFeatureLevel,    //선택된 피처레벨을 반환받을 주소.
			&m_pImmediateContext); //생성된 DC를 반환받을 주소.

		//디바이스를 생성하는데 성공하였지만 버전이 11이 아닐 경우 다시 생성하게 한다.
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

//DXGIFactory 인터페이스를 생성한다.
HRESULT	deviceC_DX::CreateGIFactory()
{
	HRESULT hr;

	V_FRETURN(CreateDXGIFactory(__uuidof(IDXGIFactory), (LPVOID*)(&m_pGIFactory)));

	return hr;
}

//DXGIFactory 인터페이스로부터 IDXGISwapChain 인터페이스를 생성한다.
HRESULT	deviceC_DX::CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight)
{
	HRESULT hr = S_OK;
	if (m_pGIFactory == nullptr) { return S_FALSE; }

	//스왑체인 구조체를 생성한 뒤 필요한 내용을 채워서 이를 이용해 스왑체인 객체를 생성한다.
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount = 1;  //1이상 필수 입력         
	
	sd.BufferDesc.Width = iWidth;                        //버퍼의 넓이
	sd.BufferDesc.Height = iHeight;                      //버퍼의 높이
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;   //버퍼의 색상 포맷 (필수)
	sd.BufferDesc.RefreshRate.Numerator = 60;            //화면 주사율 (분자)
	sd.BufferDesc.RefreshRate.Denominator = 1;           //화면 주사율 (분모)
	//sd.BufferDesc.ScanlineOrdering                     //플릿핑한 뒤 버퍼 내용을 어떻게 처리할지
	//sd.BufferDesc.Scaling                              //사이즈 조절.

	sd.SampleDesc.Count = 1;      // 몇번 뿌릴지 (1이상 필수) 1이면 멀티샘플링 안하는거 (
	sd.SampleDesc.Quality = 0;    //이미지 품질 수준
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //버퍼 용도
	sd.OutputWindow = hWnd; //어느 윈도우에 뿌릴지 (필수)
	sd.Windowed = true;     //0으로 초기화하면 전체화면으로 실행됨
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //
	//sd.SwapEffect //기본값 사용 


	V_FRETURN(m_pGIFactory->CreateSwapChain(m_pD3dDevice, &sd, &m_pSwapChain));

	return hr;
}


//렌더타겟뷰 생성 및 세팅
HRESULT	deviceC_DX::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	
	ID3D11Texture2D* pBackBuffer;

	//백버퍼를 받아옴
	V_FRETURN(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer));

	//렌더 타겟 뷰 생성
	V_FRETURN(m_pD3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTagetView));

	//렌더타겟뷰 세팅
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTagetView, nullptr);
	return S_OK;
}

//뷰포트 세팅
HRESULT	deviceC_DX::SetViewPort()
{
	//스왑체인 정보를 가져옴.
	DXGI_SWAP_CHAIN_DESC Desc;
	m_pSwapChain->GetDesc(&Desc);
	

	//뷰포트의 높이와 넓이를 스왑체인 버퍼의 크기로 설정
	m_d3dViewPort.Width = (FLOAT)Desc.BufferDesc.Width;
	m_d3dViewPort.Height = (FLOAT)Desc.BufferDesc.Height;
	m_d3dViewPort.MinDepth = 0.0f;  //깊이값은 0에서 1사이로 제한됨
	m_d3dViewPort.MaxDepth = 1.0f;
	m_d3dViewPort.TopLeftX = 0;     //작업영역의 시작 좌표값
	m_d3dViewPort.TopLeftY = 0;
	
	m_pImmediateContext->RSSetViewports(1, &m_d3dViewPort);

	return S_OK;
}


bool deviceC_DX::CreanupDevice()
{
	//삭제는 생성의 역순.
	//세팅값을 복원시켜주고 삭제한다.
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
////한꺼번에 만드는 경우
//HRESULT deviceC_DX::CreateDeviceAndSwapChain()
//{
//	//실제로 쓰진 않을거라... 앞부분 생략
//	HRESULT hr;
//	hr = D3D11CreateDeviceAndSwapChain(
//		//디스플레이 시스템(어댑터)값, NULL이면 주디스플레이어를 기본으로 선택,
//		//디바이스 드라이버 타입
//		//원하는 소프트웨어의 DLL핸들값을 넘겨줘서 그 소프트웨어의 모듈을 사용하는 디바이스를 반환하게 할 수 있다. 안 쓰려면 NULL.
//		//디바이스 생성 플래그 값
//		//선택될 수 있는 피처 레벨 배열
//		//피처 레벨 배열의 원소수
//		//SDK 버전
//		//스왑체인 속성 지정
//		//반환되는 IDXGISwapChain 인터페이스 주소
//		//반환되는 ID3D11Device 인터페이스 주소
//		//함수 호출 성공시 첫번째 피처레벨 반환
//		//ID3D11DeviceContext 인터페이스 반환
//	);
//
//}
