#include "sample.h"

namespace Lypi
{
	Sample::Sample(LPCTSTR LWndName) : zCore(LWndName)
	{
		m_pVertexBuffer = nullptr;
		m_pIndexBuffer = nullptr;
	
		m_pVertexLayout = nullptr;

		m_pStreamTo = nullptr;
		m_pDrawFrom = nullptr;
	
		m_pVS = nullptr;
		m_pGS = nullptr;
		m_pSO = nullptr;
		m_pPS = nullptr;
	}

	HRESULT Sample::LoadShaderAndInputLayout()
	{
		HRESULT hr = S_OK;
	
		ID3DBlob* pErrors = nullptr;
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	
#if defined( _DEBUG ) || defined( _DEBUG )
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
		ID3DBlob* pVSBuf = nullptr;
		hr = D3DX11CompileFromFile(L"../../INPUT/DATA/Shader/sample/VS.hlsl", nullptr, nullptr, "VS", "vs_5_0", dwShaderFlags, NULL, nullptr, &pVSBuf, &pErrors, nullptr);
		V_FRETURN(hr);
		V_FRETURN(g_pD3dDevice->CreateVertexShader((DWORD*)pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), nullptr, &m_pVS));

		ID3DBlob* pGSBuf = nullptr;
		V_FRETURN(D3DX11CompileFromFile(L"../../INPUT/DATA/Shader/sample/GS.hlsl", nullptr, nullptr, "GS", "gs_5_0", dwShaderFlags, NULL, nullptr, &pGSBuf, &pErrors, nullptr));
		V_FRETURN(g_pD3dDevice->CreateGeometryShader((DWORD*)pGSBuf->GetBufferPointer(), pGSBuf->GetBufferSize(), nullptr, &m_pGS));

		ID3DBlob* pPSBuf = nullptr;
		V_FRETURN(D3DX11CompileFromFile(L"../../INPUT/DATA/Shader/sample/PS.hlsl", nullptr, nullptr, "PS", "ps_5_0", dwShaderFlags, NULL, nullptr, &pPSBuf, &pErrors, nullptr));
		V_FRETURN(g_pD3dDevice->CreatePixelShader((DWORD*)pPSBuf->GetBufferPointer(), pPSBuf->GetBufferSize(), nullptr, &m_pPS));

		//중요! 출력 슬롯의 정점 버퍼에있는 정점 요소에 대한 설명
		// ...예를 들어 위치의 y 및 z 구성 요소로만 출력하려면 StartComponent가 1이고 ComponentCount가 2여야합니다. 
		D3D11_SO_DECLARATION_ENTRY pDecl[] =
		{
			{ 0, "SV_POSITION", 0, 0, 3, 0 },
			{ 0, "COLOR", 0, 0, 4, 0 },
		};

		UINT elems = ARRAYSIZE(pDecl);
		// == UINT elems = sizeof(pDecl) / sizeof(pDecl[0]);	 
		// == UINT elems = sizeof(pDecl) / sizeof(D3D11_SO_DECLARATION_ENTRY);

		UINT stride[] = { sizeof(PC_VERTEX) }; // SO에서 반환되는 정점 한개의 크기.
		//UINT stride = 7 * sizeof(float); // *NOT* sizeof the above array!

		V_FRETURN(g_pD3dDevice->CreateGeometryShaderWithStreamOutput(pGSBuf->GetBufferPointer(), pGSBuf->GetBufferSize(), pDecl, elems, stride, 1, 0, NULL, &m_pSO));

		UINT m_nBufferSize = 100000; // Streamoutput Stage를 돌리면 정점이 기하급수적으로 늘어남으로 최대치로 잡는 것이 좋다.
									 //그렇다고 너무 크게 잡으면 디바이스가 멈춤... 어느정도가 최대치인지는 잘 모르겠다.
		
		CD3D11_BUFFER_DESC bufferDesc(m_nBufferSize, D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT);

		//동일한 기하 쉐이더 버퍼2개 생성	
		V_FRETURN(g_pD3dDevice->CreateBuffer(&bufferDesc, NULL, &m_pDrawFrom));
		V_FRETURN(g_pD3dDevice->CreateBuffer(&bufferDesc, NULL, &m_pStreamTo));

		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		V_FRETURN(g_pD3dDevice->CreateInputLayout(layout, 2, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), &m_pVertexLayout));

		SAFE_RELEASE(pVSBuf);
		SAFE_RELEASE(pGSBuf);
		SAFE_RELEASE(pPSBuf);
		SAFE_RELEASE(pErrors);

		RSChange();

		//스트림 출력( 스트림 출력 스테이지 )
		//처음에 VertexBuffer로 한번은 꼭 돌려야한다.
		HandleEffects(m_pVertexBuffer);

		//for (int iCnt = 0; iCnt < 1; iCnt++) 	//기하 쉐이더를 몇번 돌릴지 결정.
		//{
		//	HandleEffects(m_pDrawFrom);
		//}

		return hr;
	}

	HRESULT Sample::HandleEffects(ID3D11Buffer* pBuffer)
	{
		HRESULT hr = S_OK;

		g_pD3dContext->IASetInputLayout(m_pVertexLayout);

		g_pD3dContext->VSSetShader(m_pVS, NULL, 0);
		g_pD3dContext->GSSetShader(m_pSO, NULL, 0); //SO로 세팅되면 PS로 넘어가지 않음

		UINT stride = sizeof(PC_VERTEX);
		UINT Offsets[] = { 0 };
		ID3D11Buffer* pVB[] = { pBuffer };

		g_pD3dContext->SOSetTargets(1, &m_pStreamTo, Offsets);   //삼각형당 쪼개진 데이터가 저장되서 나옴.
		g_pD3dContext->IASetVertexBuffers(0, 1, pVB, &stride, Offsets);
		g_pD3dContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		
		g_pD3dContext->RSSetState(m_pRS);
		g_pD3dContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)m_uPrimType);

		if (pBuffer == m_pVertexBuffer) {
			(g_pD3dContext->DrawIndexed(3, 0, 0));
		}
		else {
			(g_pD3dContext->DrawAuto());
		}

		//더블버퍼링과 같은 개념
		ID3D11Buffer* pTemp = m_pStreamTo;
		m_pStreamTo = m_pDrawFrom;
		m_pDrawFrom = pTemp;

		//여기에 있어야 함. 중요함.
		pVB[0] = NULL;
		g_pD3dContext->SOSetTargets(0, pVB, Offsets);

		return hr;
	}

	HRESULT Sample::CreateVertexBuffer()
	{
		HRESULT hr = S_OK;
	
		//시계 방향으로 지정할 것.
		PC_VERTEX vertices[] =
		{
			{ float3 (-0.0f, +0.7f, 0.5f), float4(1.f,1.f,1.f,1.f)},
			{ float3 (+0.5f, -0.2f, 0.5f), float4(1.f,1.f,1.f,1.f)},
			{ float3 (-0.5f, -0.2f, 0.5f), float4(1.f,1.f,1.f,1.f)},
		};
	
		UINT numVertices = sizeof(vertices) / sizeof(vertices[0]);
		//// CD3D11_BUFFER_DESC : 버퍼 크기와 버퍼 용도만 결정하면 나머지는 기본값으로 생성해주는 구조체.
		CD3D11_BUFFER_DESC cbc(sizeof(PC_VERTEX) * numVertices, D3D11_BIND_VERTEX_BUFFER);
	
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
	
		V_FRETURN(g_pD3dDevice->CreateBuffer(&cbc, &InitData, &m_pVertexBuffer));
		return hr;
	}
	
	HRESULT Sample::CreateIndexBuffer()
	{
		HRESULT hr = S_OK;
	
		DWORD indices[] =
		{
			0,1,2,
			//0,2,3,
		};
	
		UINT iNumIndex = sizeof(indices) / sizeof(indices[0]);
	
		// Create an Index Buffer
		CD3D11_BUFFER_DESC cib(iNumIndex * sizeof(DWORD), D3D11_BIND_INDEX_BUFFER);
	
		D3D11_SUBRESOURCE_DATA ibInitData;
		ZeroMemory(&ibInitData, sizeof(D3D11_SUBRESOURCE_DATA));
		ibInitData.pSysMem = indices;
	
		V_FRETURN(g_pD3dDevice->CreateBuffer(&cib, &ibInitData, &m_pIndexBuffer));
	
		return hr;

	}

	bool Sample::Init()
	{
		if (FAILED(CreateVertexBuffer()))
		{
			MessageBox(0, _T("CreateTrangle  실패"), _T("Fatal error"), MB_OK);
			return false;
		}

		if (FAILED(CreateIndexBuffer()))
		{
			MessageBox(0, _T("CreateIndexBuffer  실패"), _T("Fatal error"), MB_OK);
			return false;
		}

		if (FAILED(LoadShaderAndInputLayout()))
		{
			MessageBox(0, _T("LoadShaderAndInputLayout  실패"), _T("Fatal error"), MB_OK);
			return false;
		}

		g_pD3dContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)m_uPrimType);
		return true;
	}

	bool Sample::Frame()
	{
		if (I_Input.IsKeyDownOnce(DIK_F1)) {
			(m_uPrimType + 1 > 5) ? (m_uPrimType = 1) : (m_uPrimType += 1);
		}

		if (I_Input.IsKeyDownOnce(DIK_F2)) {
			(m_uCullMode + 1 > 3) ? (m_uCullMode = 1) : (m_uCullMode += 1);
			RSChange();
		}

		if (I_Input.IsKeyDownOnce(DIK_F3)) {
			(m_uFillMode + 1 > 3) ? (m_uFillMode = 2) : (m_uFillMode += 1);
			RSChange();
		}

		//D키를 누르면 분할한다.
		if (I_Input.IsKeyDownOnce(DIK_D)) {
			HandleEffects(m_pDrawFrom);
		}

		return true;
	}

	bool Sample::Render()
	{
		// Shaders
		g_pD3dContext->VSSetShader(m_pVS, NULL, 0);
		g_pD3dContext->PSSetShader(m_pPS, NULL, 0);
	
		// Set the input layout
		g_pD3dContext->IASetInputLayout(m_pVertexLayout);
	
		UINT stride[] = { sizeof(PC_VERTEX) };
		UINT offset[] = { 0 };
	
		// Set vertex buffer
		g_pD3dContext->IASetVertexBuffers(0, 1, &m_pDrawFrom, stride, offset);
		g_pD3dContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		g_pD3dContext->RSSetState(m_pRS);
		g_pD3dContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)m_uPrimType);
	
		//쪼개진 이후이므로 DrawAuto로 출력해야 제대로 분할된게 출력된다.
		/*g_pD3dContext->DrawIndexed(3, 0, 0);*/
		g_pD3dContext->DrawAuto();
		return true;
	}


	bool Sample::Release()
	{
		SAFE_RELEASE(m_pVertexBuffer);    // 정점 버퍼 릴리즈
	
		SAFE_RELEASE(m_pVertexLayout);    // 정점 레이아웃 릴리즈
	
		SAFE_RELEASE(m_pVS);              // 정점 쉐이더 릴리즈
		SAFE_RELEASE(m_pGS);              // 기하 쉐이더 릴리즈
		SAFE_RELEASE(m_pSO);              // SO 릴리즈
		SAFE_RELEASE(m_pPS);              // 픽쉘 쉐이더 릴리즈
	
		SAFE_RELEASE(m_pStreamTo);
		SAFE_RELEASE(m_pDrawFrom);

		SAFE_RELEASE(m_pRS);
	
		return true;
	}

	Sample::~Sample(void)
	{
	}


}