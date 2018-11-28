#include "Shape_DX.h"

Shape_DX::Shape_DX()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);

	m_vLook = { 1,0,0 };
	m_vSide = { 0,1,0 };
	m_vUp = { 0,0,1 };
	m_vPosition = { 0,0,0 };

	m_Primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	m_iVertexSize = sizeof(PNCT_VERTEX);
}


//protected
HRESULT Shape_DX::CreateVertexData()
{ //���� ���� ����
	return S_OK;
}

HRESULT Shape_DX::CreateIndexData()
{//�ε��� ���� ����
	return S_OK;
}

HRESULT Shape_DX::CreateVertexBuffer()
{//���� ���� ����
	HRESULT hr = S_OK;
	m_dxObj.m_pVertexBuffer = D3D::CreateVertexBuffer(m_iNumVertex, sizeof(PNCT_VERTEX), &m_VertexList.at(0));
	return hr;
}

HRESULT Shape_DX::CreateIndexBuffer()
{//�ε��� ���� ����
	HRESULT hr = S_OK;
	m_dxObj.m_pIndexBuffer = D3D::CreateIndexBuffer(m_iNumIndex, sizeof(DWORD), &m_IndexList.at(0));
	return hr;
}

HRESULT Shape_DX::CreateConstantBuffer()
{//��� ���� ����
	HRESULT hr = S_OK;
	m_dxObj.m_pConstantBuffer = D3D::CreateConstantBuffer(sizeof(T_CB_DATA), &m_cbData);
	return hr;
}

HRESULT Shape_DX::CreateInputLayout()
{//��ǲ ���̾ƿ� ����
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT numElemnts = sizeof(layout) / sizeof(layout[0]);

	//InputLayout ���� (���� ���۸� IAStage(���̴�)�� �ѱ������ ������ ���� �������̽�) (�Է� ��� ����ü �迭�� ���� �ּ�, ���� ����, �����ϵ� ���̴��� ������ ������, �������� ũ��, ��ȯ����) 
	g_pD3dDevice->CreateInputLayout(layout, numElemnts, m_dxObj.m_pVSBlob->GetBufferPointer(), m_dxObj.m_pVSBlob->GetBufferSize(), m_dxObj.m_pInputLayout.GetAddressOf());

	return hr;
}

HRESULT Shape_DX::LoadVertexShader(T_STR szName)
{//���� ���̴� �ҷ�����
	if (szName != L"NULL") {
		HRESULT hr = S_OK;
		m_dxObj.m_pVertexShader.Attach(D3D::LoadVertexShaderFile(szName.c_str(), m_dxObj.m_pVSBlob.GetAddressOf()));
		return hr;
	}
	return S_OK;
}

HRESULT Shape_DX::LoadPixelShader(T_STR szName)
{//�ȼ� ���̴� �ҷ�����
	if (szName != L"NULL") {
		HRESULT hr = S_OK;
		m_dxObj.m_pPixelShader.Attach(D3D::LoadPixelShaderFile(szName.c_str()));
		return hr;
	}
	return S_OK;
}
HRESULT Shape_DX::LoadGeoShader(T_STR szName)
{//���� ���̴� �ҷ�����
	if (szName != L"NULL") {
		HRESULT hr = S_OK;
		m_dxObj.m_pGeoShader.Attach(D3D::LoadGeoShaderFile(szName.c_str()));
		return hr;
	}
	return S_OK;
}


HRESULT Shape_DX::LoadTexture(T_STR szName)
{//�ؽ��� �ҷ�����
	if (szName != L"NULL") {
		HRESULT hr = S_OK;
		D3DX11_IMAGE_LOAD_INFO loadinfo;
		ZeroMemory(&loadinfo, sizeof(loadinfo));
		loadinfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		loadinfo.Format = DXGI_FORMAT_FROM_FILE;

		hr = D3DX11CreateShaderResourceViewFromFile(g_pD3dDevice, szName.c_str(), &loadinfo, nullptr, m_dxObj.m_pTextureRV.GetAddressOf(), nullptr);
		return hr;
	}
	return S_OK;
}

//public
void Shape_DX::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{//��� �����ϱ�
	if (pWorld != nullptr) { m_matWorld = *pWorld; }
	if (pView != nullptr) { m_matView = *pView; }
	if (pProj != nullptr) { m_matProj = *pProj; }

	//�׷��� ī��� ���켱 ������� �����ϹǷ� ����� ��ġ�ؼ� �����ؾ���.
	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);

	m_vLook     = { m_matWorld._11, m_matWorld._12, m_matWorld._13 };
	m_vSide     = { m_matWorld._21, m_matWorld._22, m_matWorld._23 };
	m_vUp       = { m_matWorld._31, m_matWorld._32, m_matWorld._33 };
	m_vPosition = { m_matWorld._41, m_matWorld._42, m_matWorld._43 };
}

void Shape_DX::SetColor(D3DXVECTOR4 vColor)
{
	m_cbData.vColor = vColor;
}


bool Shape_DX::Create(T_STR szVSName, T_STR szPSName, T_STR szGSName, T_STR szTextureName)
{
	HRESULT hr = S_OK;

	V_RF(CreateVertexData());
	V_RF(CreateIndexData());

	V_RF(CreateVertexBuffer());
	V_RF(CreateIndexBuffer());
	V_RF(CreateConstantBuffer());

	V_RF(LoadVertexShader(szVSName));
	V_RF(LoadPixelShader(szPSName));
	V_RF(LoadGeoShader(szGSName));

	V_RF(CreateInputLayout());

	V_RF(LoadTexture(szTextureName));

	return true;
}

bool Shape_DX::Init()
{
	return true;
}

bool Shape_DX::Frame()
{
	return true;
}

bool Shape_DX::PreRender()
{
	m_dxObj.PreRender(m_iVertexSize);
	return true;
}
bool Shape_DX::Render()
{
	g_pD3dContext->UpdateSubresource(m_dxObj.m_pConstantBuffer.Get(), 0, nullptr, &m_cbData, 0, 0);
	g_pD3dContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)m_Primitive);
	PreRender();
	PostRender();
	return true;
}
bool Shape_DX::PostRender()
{
	m_dxObj.PostRender(m_iVertexSize,m_iNumIndex);
	return true;
}
	 
bool Shape_DX::Release()
{
	return true;
}

Shape_DX::~Shape_DX() { }