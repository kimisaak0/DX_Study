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
			DEBUGMSG(L"�̹��� �ҷ����� ����");
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
						//������ ��ġ�� �ȼ��� ���� �ٲ۴�.
						*pDest++ = 0;   //R
						*pDest++ = 0;   //G
						*pDest++ = 255; //B
						*pDest++ = 255; //A
					}
					else {
						pDest += 4; // ����Ʈ �̵�.
					}
				}
				//����Ʈ �̵�
				pDestBytes += MappedFaceDest.RowPitch;
			}
			g_pD3dContext->Unmap(pTexDest, 0);
		}
	}

	bool Sample::Init()
	{
		//����ü�ο� ������ ������ ũ��� ����۸� �����. 
		HRESULT hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
		if (FAILED(hr)) {
			return false;
		}
		//����� ������ �����´�.
		m_pBackBuffer->GetDesc(&m_BackBuffereDesc);

		//CopyResource()�Լ��� ����� ��� �ݵ�� �� ������ ũ�⺸�� ũ�ų� ���ƾ� �Ѵ�.
		//CopyResourceRegion()�Լ��� ����� ��� ���ϴ� ũ��� ������ �� �ִ�.
		D3DX11_IMAGE_LOAD_INFO loadInfo;
		loadInfo.Width             = m_BackBuffereDesc.Width;   // �ؽ����� �ʺ�. �ؽ��� ũ��� �ٸ� ��� �ڵ����� Ȯ��,��Ұ� �̷�����.
		loadInfo.Height            = m_BackBuffereDesc.Height;  // �ؽ����� ����. �ؽ��� ũ��� �ٸ� ��� �ڵ����� Ȯ��,��Ұ� �̷�����.
		loadInfo.Depth             = D3DX11_DEFAULT;            // �ؽ����� ����. ���� �ؽ�ó���� ����ȴ�.
		loadInfo.FirstMipLevel     = 0;                         // �ؽ��� �ְ� �ػ� �Ӹ� ����. 
		loadInfo.MipLevels         = 1;                         // �ؽ��� �Ӹ��� �ִ� ��. (�ּ� 1�̾�� �Ѵ�.)
		loadInfo.Usage             = D3D11_USAGE_STAGING;       // �ؽ��� ���ҽ��� �뵵
		loadInfo.BindFlags         = 0;	                        // �ؽ��ĸ� ���ε��� ���������� �ܰ�.
		loadInfo.CpuAccessFlags    
			= D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;   // CPU�� �ؽ��Ŀ� ������ �� �ִ� ���� ����. �а� ���Ⱑ �����ϰ� ����.
		loadInfo.MiscFlags         = 0;                         // ���ҽ��� ���� ��Ÿ �Ӽ���. 
		loadInfo.Format            = m_BackBuffereDesc.Format;  // �ؽ��İ� �ε�� ���� ����
		loadInfo.Filter            = D3DX11_FILTER_LINEAR;      // ������ ���͸� ����Ͽ� �ؽ��� ���͸�.
		loadInfo.MipFilter         = D3DX11_FILTER_NONE;        // ������ ���͸� ����Ͽ� ������ �Ӹ��� ���͸�.
		loadInfo.pSrcInfo          = 0;                         // ���� �̹����� ���� ����. 

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
		//CopyResourceRegion()�Լ� : �����ؽ����� ��ü �� �Ϻ� ������ �� ������ 0,0 ��ġ�� ������.
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