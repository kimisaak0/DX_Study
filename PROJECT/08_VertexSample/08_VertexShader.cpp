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
		MessageBox(0, _T("CreateTrangle1  실패"), _T("Fatal error"), MB_OK);
		return false;
	}
	if (FAILED(LoadShaderAndInputLayout()))
	{
		MessageBox(0, _T("CreateTrangle2  실패"), _T("Fatal error"), MB_OK);
		return false;
	}
	return true;
}

HRESULT VertexSample::CreateVertexBuffer()
{
	HRESULT hr = S_OK;

	//시계 방향으로 지정할 것.
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
	bd.Usage = D3D11_USAGE_DEFAULT;               // 디폴트
	bd.ByteWidth = sizeof(SimpleVertex) * (sizeof(vertices) / sizeof(vertices[0]));	  // 버퍼 크기 지정
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	  // 정점 버퍼 생성
	bd.CPUAccessFlags = 0;						  // Usage가 디폴트가 아닐때 CPU로 연산할 떄 사용하는 값
	bd.MiscFlags = 0;                             
	//여기까지는 할당만 한 것

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	//할당과 동시에 초기화 (두번째 인자값)
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

	//d3dx11.h에 있음
	//다렉 오리지날이 있고 확장버전이 있음. X가 들어간 버전은 다 확장버전임.
	//쉐이더 컴파일 하기. 파일로드해서 컴파일해줌, "VS"함수로 "vs_5_0"컴파일러로 ID3DBlob값 필수 컴파일된 결과를 받는 곳.
	//컴파일된 결과로 보내줘야함.
	//GetBufferPointer() 시작주소, GetBufferSize() 크기
	V_FRETURN(D3DX11CompileFromFile(L"Vertex.vsh", NULL, NULL, "VS", "vs_5_0", dwShaderFlags, NULL, NULL, &pVSBuf, NULL, NULL));

	V_FRETURN(g_pD3dDevice->CreateVertexShader((DWORD*)pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), NULL, &m_pVS));

	// Compile the PS from the file //픽셀 쉐이더 만드는 것도 똑같음. (하나의 파일에 다 넣어도 됨)
	ID3DBlob* pPSBuf = NULL;
	V_FRETURN(D3DX11CompileFromFile(L"Pixel.psh", NULL, NULL, "PS", "ps_5_0", dwShaderFlags, NULL, NULL, &pPSBuf, NULL, NULL));
	V_FRETURN(g_pD3dDevice->CreatePixelShader((DWORD*)pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), NULL, &m_pPS));

	// Create our vertex input layout
	//레이아웃 만들기 (정점 쉐이더의 결과로 만들어짐)
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//정점쉐이더안의 POSITION시멘틱의 의미를 지정.
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	//레이아웃을 생성.
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
	//IASetVertexBuffers : 1개 정점의 메모리 크기
	g_pD3dContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	g_pD3dContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
	g_pD3dContext->Draw(6, 0);
	return true;
}

bool VertexSample::Release()
{
	SAFE_RELEASE(m_pVertexLayout); // 정정레이아웃 소멸
	SAFE_RELEASE(m_pVertexBuffer); // 정점버퍼 소멸	
	SAFE_RELEASE(m_pVS);         // 정점쉐이더 소멸
	SAFE_RELEASE(m_pPS);         // 픽쉘쉐이더 소멸 
	return true;
}


VertexSample::~VertexSample(void)
{
}