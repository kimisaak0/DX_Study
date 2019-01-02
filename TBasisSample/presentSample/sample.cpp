#include "sample.h"

namespace Lypi
{
	Sample::Sample(LPCTSTR LWndName) : zCore(LWndName)
	{
		m_pTextureSrc = nullptr;
		m_pTextureDest = nullptr;
		m_pBackBuffer = nullptr;
	}

	ID3D11Texture2D* Sample::GetTexture2DFromFile(LPCWSTR filename, D3DX11_IMAGE_LOAD_INFO* pLoadInfo)
	{
		HRESULT hr;

		ID3D11Texture2D* texture = nullptr;
		ID3D11Resource* pRes = nullptr;

		hr = D3DX11CreateTextureFromFile(g_pD3dDevice, filename, pLoadInfo, nullptr, &pRes, nullptr);
		if (FAILED(hr)) {
			DEBUGMSG(L"이미지 불러오기 실패");
			return nullptr;
		}

		pRes->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&texture);
		pRes->Release();

		return texture;
	}

	ID3D11Texture2D* Sample::CopyTexture(ID3D11Texture2D* pSrcTexture)
	{
		HRESULT hr;
		
		D3D11_TEXTURE2D_DESC desc;
		pSrcTexture->GetDesc(&desc);

		ID3D11Texture2D* NewTexture2D;

		hr = g_pD3dDevice->CreateTexture2D(&desc, 0, &NewTexture2D);
		if (FAILED(hr)) {
			MessageBox(0, L"CreateTexture2D FAILED", 0, 0);
			return nullptr;
		}
		g_pD3dContext->CopyResource(NewTexture2D, pSrcTexture);
		return NewTexture2D;
	}

	void Sample::WriteDotPixel(ID3D11Texture2D* pTexDest)
	{
		HRESULT hr;

		D3D11_TEXTURE2D_DESC desc;
		pTexDest->GetDesc(&desc);

		D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
		hr = g_pD3dContext->Map((ID3D11Resource*)pTexDest, 0, D3D11_MAP_READ_WRITE, 0, &MappedFaceDest);
		if (SUCCEEDED(hr))
		{
			BYTE* pDestBytes = (BYTE*)MappedFaceDest.pData;

			for (UINT y = 0; y < desc.Height; y++) {
				BYTE* pDest = pDestBytes;
				for (UINT x = 0; x < desc.Width; x++) {
					if (x % 100 == 0) {
						//지정된 위치의 픽셀의 색을 바꾼다.
						*pDest++ = 0;   //R
						*pDest++ = 0;   //G
						*pDest++ = 255; //B
						*pDest++ = 255; //A
					}
					else {
						pDest += 4; // 바이트 이동.
					}
				}
				//바이트 이동
				pDestBytes += MappedFaceDest.RowPitch;
			}
			g_pD3dContext->Unmap(pTexDest, 0);
		}
	}

	bool Sample::Init()
	{
		//스왑체인에 지정된 버퍼의 크기로 백버퍼를 만든다. 
		HRESULT hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
		if (FAILED(hr)) {
			return false;
		}
		//백버퍼 정보를 가져온다.
		m_pBackBuffer->GetDesc(&m_BackBuffereDesc);

		//CopyResource()함수를 사용할 경우 반드시 백 버퍼의 크기보다 크거나 같아야 한다.
		//CopyResourceRegion()함수를 사용할 경우 원하는 크기로 지정할 수 있다.
		D3DX11_IMAGE_LOAD_INFO loadInfo;
		loadInfo.Width             = m_BackBuffereDesc.Width;   // 텍스쳐의 너비. 텍스쳐 크기와 다를 경우 자동으로 확대,축소가 이뤄진다.
		loadInfo.Height            = m_BackBuffereDesc.Height;  // 텍스쳐의 높이. 텍스쳐 크기와 다를 경우 자동으로 확대,축소가 이뤄진다.
		loadInfo.Depth             = D3DX11_DEFAULT;            // 텍스쳐의 깊이. 볼륨 텍스처에만 적용된다.
		loadInfo.FirstMipLevel     = 0;                         // 텍스쳐 최고 해상도 밉맵 수준. 
		loadInfo.MipLevels         = 1;                         // 텍스쳐 밉맵의 최대 수. (최소 1이어야 한다.)
		loadInfo.Usage             = D3D11_USAGE_STAGING;       // 텍스쳐 리소스의 용도
		loadInfo.BindFlags         = 0;	                        // 텍스쳐를 바인딩할 파이프라인 단계.
		loadInfo.CpuAccessFlags    
			= D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;   // CPU가 텍스쳐에 접근할 수 있는 권한 설정. 읽고 쓰기가 가능하게 설정.
		loadInfo.MiscFlags         = 0;                         // 리소스에 대한 기타 속성들. 
		loadInfo.Format            = m_BackBuffereDesc.Format;  // 텍스쳐가 로드된 후의 형식
		loadInfo.Filter            = D3DX11_FILTER_LINEAR;      // 지정된 필터를 사용하여 텍스쳐 필터링.
		loadInfo.MipFilter         = D3DX11_FILTER_NONE;        // 지정된 필터를 사용하여 생성된 밉맵을 필터링.
		loadInfo.pSrcInfo          = 0;                         // 기존 이미지에 대한 정보. 

		m_pTextureSrc = GetTexture2DFromFile(TEXT("../../INPUT/DATA/image/Desert.jpg"), &loadInfo);
		if (m_pTextureSrc == nullptr) {
			return false;
		}

		m_pTextureDest = CopyTexture(m_pTextureSrc.Get());
		WriteDotPixel(m_pTextureDest.Get());

		return true;
	}

	bool Sample::Frame()
	{
		return true;
	}

	bool Sample::Render()
	{
		//CopyResourceRegion()함수 : 원본텍스쳐의 전체 및 일부 영역을 백 버퍼의 0,0 위치에 복사함.
		g_pD3dContext->CopyResource(m_pBackBuffer.Get(), m_pTextureDest.Get());
		return true;
	}


	bool Sample::Release()
	{
		return true;
	}

	Sample::~Sample(void)
	{
	}
}