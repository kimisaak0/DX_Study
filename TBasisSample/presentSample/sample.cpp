#include "sample.h"

namespace Lypi
{
	Sample::Sample(LPCTSTR LWndName) : zCore(LWndName)
	{

	}

	bool Sample::Init()
	{
		HRESULT hr;

		SimpleVertex vertices[] =
		{
			-0.5f,  0.5f, 0.5f, 0.0f, 0.0f,
			 0.5f,  0.5f, 0.5f, 1.0f, 0.0f,
			 0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
		};

		UINT numVertices = sizeof(vertices) / sizeof(vertices[0]);
		m_dxobj.g_pVertexBuffer.Attach(CreateVertexBuffer(g_pD3dDevice, vertices, numVertices, sizeof(SimpleVertex)));

		DWORD indices[] = { 0,1,2, 0,3,2 };
		UINT iNumIndex = sizeof(indices) / sizeof(indices[0]);
		m_dxobj.g_pIndexBuffer.Attach(CreateIndexBuffer(g_pD3dDevice, indices, iNumIndex, sizeof(DWORD)));

		m_dxobj.g_pVertexShader.Attach(LoadVertexShaderFile(g_pD3dDevice, L"VS.hlsl", m_dxobj.g_pVSBlob.GetAddressOf()));

		m_dxobj.g_pPixelShader.Attach(LoadPixelShaderFile(g_pD3dDevice, L"PS.hlsl"));

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		UINT numElements = sizeof(layout) / sizeof(layout[0]);
		m_dxobj.g_pInputlayout.Attach(CreateInputlayout(g_pD3dDevice, m_dxobj.g_pVSBlob.Get()->GetBufferSize))


		return true;
	}

	bool Sample::Frame()
	{
		m_Hero.Frame();
		//T1.Frame();
		return true;
	}

	bool Sample::Render()
	{
		m_Hero.Render();
		//bg.Render();
		//T1.Render();
		return true;
	}


	bool Sample::Release()
	{
		m_Hero.Release();
		return true;
	}

	Sample::~Sample(void)
	{
	}
}