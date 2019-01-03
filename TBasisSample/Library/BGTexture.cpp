#include "BGTexture.h"

namespace Lypi
{
	BGTexture::BGTexture()
	{
		m_pTexture = nullptr;
	}

	ID3D11Texture2D* BGTexture::LoadTexture(LPCWSTR filename)
	{
		HRESULT hr;

		ID3D11Texture2D* texture = nullptr;
		ID3D11Resource* pRes = nullptr;

		//스왑체인에 지정된 버퍼의 크기로 백버퍼를 만든다.
		hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
		if (FAILED(hr)) {
			return false;
		}
		//백버퍼 정보를 가져온다.
		m_pBackBuffer->GetDesc(&m_BackBuffereDesc);

		//CopyResource()함수를 사용할 경우 반드시 백 버퍼의 크기보다 크거나 같아야 한다.
		//CopyResourceRegion()함수를 사용할 경우 원하는 크기로 지정할 수 있다.
		D3DX11_IMAGE_LOAD_INFO loadInfo;
		loadInfo.Width = m_BackBuffereDesc.Width;   // 텍스쳐의 너비. 텍스쳐 크기와 다를 경우 자동으로 확대,축소가 이뤄진다.
		loadInfo.Height = m_BackBuffereDesc.Height;  // 텍스쳐의 높이. 텍스쳐 크기와 다를 경우 자동으로 확대,축소가 이뤄진다.
		loadInfo.Depth = D3DX11_DEFAULT;            // 텍스쳐의 깊이. 볼륨 텍스처에만 적용된다.
		loadInfo.FirstMipLevel = 0;                         // 텍스쳐 최고 해상도 밉맵 수준.
		loadInfo.MipLevels = 1;                         // 텍스쳐 밉맵의 최대 수. (최소 1이어야 한다.)
		loadInfo.Usage = D3D11_USAGE_DEFAULT;       // 텍스쳐 리소스의 용도
		loadInfo.BindFlags = 0;                         // 텍스쳐를 바인딩할 파이프라인 단계.
		loadInfo.CpuAccessFlags = 0;                         // CPU가 텍스쳐에 접근할 수 있는 권한 설정. 0이면 접근 불가.
		loadInfo.MiscFlags = 0;                         // 리소스에 대한 기타 속성들.
		loadInfo.Format = m_BackBuffereDesc.Format;  // 텍스쳐가 로드된 후의 형식
		loadInfo.Filter = D3DX11_FILTER_LINEAR;      // 지정된 필터를 사용하여 텍스쳐 필터링.
		loadInfo.MipFilter = D3DX11_FILTER_NONE;        // 지정된 필터를 사용하여 생성된 밉맵을 필터링.
		loadInfo.pSrcInfo = 0;                         // 기존 이미지에 대한 정보.

		hr = D3DX11CreateTextureFromFile(g_pD3dDevice, filename, &loadInfo, nullptr, &pRes, nullptr);
		if (FAILED(hr)) {
			DEBUGMSG(L"이미지 불러오기 실패");
			return nullptr;
		}

		pRes->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&texture);
		pRes->Release();

		return texture;
	}

	bool BGTexture::Init()
	{

		m_pTexture->GetDesc(&m_TextureDesc);

		return true;
	}

	bool BGTexture::Frame()
	{
		return true;
	}

	bool BGTexture::Render()
	{
		//CopyResource()함수를 사용할 경우 반드시 백 버퍼의 크기보다 크거나 같아야 한다.
		g_pD3dContext->CopyResource(m_pBackBuffer.Get(), m_pTexture.Get());
		return true;
	}


	bool BGTexture::Release()
	{
		return true;
	}

	BGTexture::~BGTexture(void)
	{
	}
}
