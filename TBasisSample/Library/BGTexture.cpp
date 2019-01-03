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

		//����ü�ο� ������ ������ ũ��� ����۸� �����.
		hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
		if (FAILED(hr)) {
			return false;
		}
		//����� ������ �����´�.
		m_pBackBuffer->GetDesc(&m_BackBuffereDesc);

		//CopyResource()�Լ��� ����� ��� �ݵ�� �� ������ ũ�⺸�� ũ�ų� ���ƾ� �Ѵ�.
		//CopyResourceRegion()�Լ��� ����� ��� ���ϴ� ũ��� ������ �� �ִ�.
		D3DX11_IMAGE_LOAD_INFO loadInfo;
		loadInfo.Width = m_BackBuffereDesc.Width;   // �ؽ����� �ʺ�. �ؽ��� ũ��� �ٸ� ��� �ڵ����� Ȯ��,��Ұ� �̷�����.
		loadInfo.Height = m_BackBuffereDesc.Height;  // �ؽ����� ����. �ؽ��� ũ��� �ٸ� ��� �ڵ����� Ȯ��,��Ұ� �̷�����.
		loadInfo.Depth = D3DX11_DEFAULT;            // �ؽ����� ����. ���� �ؽ�ó���� ����ȴ�.
		loadInfo.FirstMipLevel = 0;                         // �ؽ��� �ְ� �ػ� �Ӹ� ����.
		loadInfo.MipLevels = 1;                         // �ؽ��� �Ӹ��� �ִ� ��. (�ּ� 1�̾�� �Ѵ�.)
		loadInfo.Usage = D3D11_USAGE_DEFAULT;       // �ؽ��� ���ҽ��� �뵵
		loadInfo.BindFlags = 0;                         // �ؽ��ĸ� ���ε��� ���������� �ܰ�.
		loadInfo.CpuAccessFlags = 0;                         // CPU�� �ؽ��Ŀ� ������ �� �ִ� ���� ����. 0�̸� ���� �Ұ�.
		loadInfo.MiscFlags = 0;                         // ���ҽ��� ���� ��Ÿ �Ӽ���.
		loadInfo.Format = m_BackBuffereDesc.Format;  // �ؽ��İ� �ε�� ���� ����
		loadInfo.Filter = D3DX11_FILTER_LINEAR;      // ������ ���͸� ����Ͽ� �ؽ��� ���͸�.
		loadInfo.MipFilter = D3DX11_FILTER_NONE;        // ������ ���͸� ����Ͽ� ������ �Ӹ��� ���͸�.
		loadInfo.pSrcInfo = 0;                         // ���� �̹����� ���� ����.

		hr = D3DX11CreateTextureFromFile(g_pD3dDevice, filename, &loadInfo, nullptr, &pRes, nullptr);
		if (FAILED(hr)) {
			DEBUGMSG(L"�̹��� �ҷ����� ����");
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
		//CopyResource()�Լ��� ����� ��� �ݵ�� �� ������ ũ�⺸�� ũ�ų� ���ƾ� �Ѵ�.
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
