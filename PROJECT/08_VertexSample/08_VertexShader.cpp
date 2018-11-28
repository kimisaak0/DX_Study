#include "08_VertexShader.h"

VertexSample::VertexSample(LPCTSTR LWndName) : coreC_DX(LWndName)
{
	m_pVertexLayout = NULL;
	m_pVertexBuffer = NULL;
	m_pVS = NULL;
	m_pPS = NULL;
}



bool VertexSample::Init()
{

	if (FAILED(CreateVertexBuffer()))
	{
		MessageBox(0, _T("CreateTrangle1  ����"), _T("Fatal error"), MB_OK);
		return false;
	}
	if (FAILED(LoadShaderAndInputLayout()))
	{
		MessageBox(0, _T("CreateTrangle2  ����"), _T("Fatal error"), MB_OK);
		return false;
	}
	return true;
}

HRESULT VertexSample::CreateVertexBuffer()
{
	HRESULT hr = S_OK;

	//�ð� �������� ������ ��.
	SimpleVertex vertices[] =
	{
		{ 0.0f, 0.5f, 0.5f },
		{ 0.4f, 0.1f, 0.5f },
		{ 0.2f, -0.5f, 0.5f },
		{ -0.2f, -0.5f, 0.5f },
		{ -0.4f, 0.1f, 0.5f },
		{ 0.0f, 0.5f, 0.5f },
	};

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;               // ����Ʈ
	bd.ByteWidth = sizeof(SimpleVertex) * (sizeof(vertices) / sizeof(vertices[0]));	  // ���� ũ�� ����
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	  // ���� ���� ����
	bd.CPUAccessFlags = 0;						  // Usage�� ����Ʈ�� �ƴҶ� CPU�� ������ �� ����ϴ� ��
	bd.MiscFlags = 0;                             
	//��������� �Ҵ縸 �� ��

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	//�Ҵ�� ���ÿ� �ʱ�ȭ (�ι�° ���ڰ�)
	return g_pD3dDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
}

HRESULT VertexSample::LoadShaderAndInputLayout()
{
	HRESULT hr = S_OK;
	// Create the effect
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	//WCHAR str[MAX_PATH];   
	ID3DBlob* pVSBuf = NULL;

#if defined( _DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	//d3dx11.h�� ����
	//�ٷ� ���������� �ְ� Ȯ������� ����. X�� �� ������ �� Ȯ�������.
	//���̴� ������ �ϱ�. ���Ϸε��ؼ� ����������, "VS"�Լ��� "vs_5_0"�����Ϸ��� ID3DBlob�� �ʼ� �����ϵ� ����� �޴� ��.
	//�����ϵ� ����� ���������.
	//GetBufferPointer() �����ּ�, GetBufferSize() ũ��
	V_FRETURN(D3DX11CompileFromFile(L"Vertex.vsh", NULL, NULL, "VS", "vs_5_0", dwShaderFlags, NULL, NULL, &pVSBuf, NULL, NULL));

	V_FRETURN(g_pD3dDevice->CreateVertexShader((DWORD*)pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), NULL, &m_pVS));

	// Compile the PS from the file //�ȼ� ���̴� ����� �͵� �Ȱ���. (�ϳ��� ���Ͽ� �� �־ ��)
	ID3DBlob* pPSBuf = NULL;
	V_FRETURN(D3DX11CompileFromFile(L"Pixel.psh", NULL, NULL, "PS", "ps_5_0", dwShaderFlags, NULL, NULL, &pPSBuf, NULL, NULL));
	V_FRETURN(g_pD3dDevice->CreatePixelShader((DWORD*)pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &m_pPS));

	// Create our vertex input layout
	//���̾ƿ� ����� (���� ���̴��� ����� �������)
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//�������̴����� POSITION�ø�ƽ�� �ǹ̸� ����.
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	//���̾ƿ��� ����.
	V_FRETURN(g_pD3dDevice->CreateInputLayout(layout, 1, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(),
		&m_pVertexLayout));

	SAFE_RELEASE(pVSBuf);
	SAFE_RELEASE(pPSBuf);
	return hr;
}

bool VertexSample::Render()
{
	// Set the input layout
	g_pD3dContext->IASetInputLayout(m_pVertexLayout);
	// Shaders
	g_pD3dContext->VSSetShader(m_pVS, NULL, 0);
	//m_pImmediateContext->HSSetShader( NULL, NULL, 0 );
	//m_pImmediateContext->DSSetShader( NULL, NULL, 0 );
	//m_pImmediateContext->GSSetShader( NULL, NULL, 0 );
	g_pD3dContext->PSSetShader(m_pPS, NULL, 0);

	// // Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	//IASetVertexBuffers : 1�� ������ �޸� ũ��
	g_pD3dContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	g_pD3dContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
	g_pD3dContext->Draw(6, 0);
	return true;
}

bool VertexSample::Release()
{
	SAFE_RELEASE(m_pVertexLayout); // �������̾ƿ� �Ҹ�
	SAFE_RELEASE(m_pVertexBuffer); // �������� �Ҹ�	
	SAFE_RELEASE(m_pVS);         // �������̴� �Ҹ�
	SAFE_RELEASE(m_pPS);         // �Ƚ����̴� �Ҹ� 
	return true;
}


VertexSample::~VertexSample(void)
{
}