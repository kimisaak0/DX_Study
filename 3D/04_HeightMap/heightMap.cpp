#include "heightMap.h"

heightMap::heightMap() 
{
	m_fScaleHeight = 1;
	m_fHeightList.resize(0);

	m_iNumRowsVertice = 0;
	m_iNumColsVertice = 0;
}

bool heightMap::CreateHeightMap(T_STR HeightMapPath)
{
	HRESULT hr = S_OK;
	//D3DX11_IMAGE_INFO imageinfo; //활용 용도를 아직 모르겠음.
	ID3D11Resource* pLoadTexture = nullptr;
	
	D3DX11_IMAGE_LOAD_INFO info;
	ZeroMemory(&info, sizeof(info));
	info.MipLevels = 1;
	info.Usage = D3D11_USAGE_STAGING;
	info.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	info.Format = DXGI_FORMAT_FROM_FILE;
	//info.pSrcInfo = &imageinfo;
	if (FAILED(hr = D3DX11CreateTextureFromFile(g_pD3dDevice, HeightMapPath.c_str(), &info, nullptr, &pLoadTexture, nullptr))) {
		return false;
	}

	ID3D11Texture2D* pTex2D = nullptr;
	if (FAILED(pLoadTexture->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTex2D))) {
		return false;
	}
	SAFE_RELEASE(pLoadTexture);

	D3D11_TEXTURE2D_DESC desc;
	pTex2D->GetDesc(&desc);

	m_fHeightList.resize(desc.Width*desc.Height);

	D3D11_MAPPED_SUBRESOURCE map;
	UINT index = D3D11CalcSubresource(0, 0, 1);

	if (SUCCEEDED(g_pD3dContext->Map(pTex2D, index, D3D11_MAP_READ, 0, &map))) {
		UCHAR* pTexels = (UCHAR*)map.pData;

		for (UINT iRow = 0; iRow < desc.Height; iRow++) {
			UINT rowStart = iRow * map.RowPitch;

			for (UINT iCol = 0; iCol < desc.Width; iCol++) {
				UINT colStart = iCol * 4;
				UCHAR uRed = pTexels[rowStart + colStart + 0]; //0 : red, 1 : green, 2: blue, 3 : alpha
				m_fHeightList[iRow*desc.Width + iCol] = uRed;
			}

		}

		g_pD3dContext->Unmap(pTex2D, index);
	}

	m_iNumRowsVertice = desc.Width; //타일의 가로 정점갯수 * 2^(rowScale-1) + 1 (맵의 정점갯수를 2^n + 1개로 맞추는 것이 목적)
	m_iNumColsVertice = desc.Height; //타일의 세로 정점갯수 * 2^(colScale-1) + 1 (맵의 정점갯수를 2^n + 1개로 맞추는 것이 목적)
	
	return true;
}

bool heightMap::CreateMap(MapDesc TileDesc)
{
	if(m_iNumRowsVertice == 0 || m_iNumColsVertice == 0){
		m_iNumRowsVertice = TileDesc.iNumRowsVertice + 1; //타일의 가로 정점갯수 + 1 (맵의 정점갯수를 2^n + 1개로 맞추는 것이 목적)
		m_iNumColsVertice = TileDesc.iNumColsVertice + 1; //타일의 세로 정점갯수 + 1 (맵의 정점갯수를 2^n + 1개로 맞추는 것이 목적)
	}

	m_iNumRowsCell = m_iNumRowsVertice - 1; //맵의 가로 셀 개수. 정점갯수는 2^n+1개로 맞췄으므로 셀의 갯수는 2^n개
	m_iNumColsCell = m_iNumColsVertice - 1;	//맵의 세로 셀 개수. 정점갯수는 2^n+1개로 맞췄으므로 셀의 갯수는 2^n개

	m_iNumVertice = m_iNumRowsVertice * m_iNumColsVertice; //맵의 모든 정점수
	m_iNumFace = m_iNumRowsCell * m_iNumColsCell * 2;

	m_fCellDistance = TileDesc.fDistance;
	m_fScaleHeight = TileDesc.fScaleHeight;

	Shape_DX::Create(TileDesc.szVSFilePath, TileDesc.szPSFilePath, TileDesc.szGSFilePath, TileDesc.szTexFilePath);

	return true;
}

HRESULT heightMap::CreateVertexData()
{
	Shape_DX::m_iNumVertex = m_iNumVertice;
	m_VertexList.resize(m_iNumVertice);

	float fHalfRows = (m_iNumRowsVertice - 1) / 2.0f;     //맵의 중앙을 원점으로 설정하기 위해 X좌표 설정
	float fHalfCols = (m_iNumColsVertice - 1) / 2.0f;     //맵의 중앙을 원점으로 설정하기 위해 Z좌표 설정
	float fTexcoodUnitU = 1.0f / (m_iNumRowsVertice - 1); //텍스쳐 좌표의 u값 증가치.
	float fTexcoodUnitV = 1.0f / (m_iNumColsVertice - 1); //텍스쳐 좌표의 v값 증가치.

	for (int iRow = 0; iRow < m_iNumRowsVertice; iRow++) {
		for (int iCol = 0; iCol < m_iNumColsVertice; iCol++) {
			int iIndex = iRow * m_iNumColsVertice + iCol;
			m_VertexList[iIndex].p.x = (iCol - fHalfCols)*m_fCellDistance;
			m_VertexList[iIndex].p.y = GetHeightOfVertex(iIndex); //기본 맵에서는 높이값을 안 쓰므로 0.
			m_VertexList[iIndex].p.z = -((iRow - fHalfRows)*m_fCellDistance);
			m_VertexList[iIndex].n = GetNomalOfVertex(iIndex);
			m_VertexList[iIndex].c = GetColorOfVertex(iIndex);
			m_VertexList[iIndex].t = GetTextureOfVertex(fTexcoodUnitU*iCol, fTexcoodUnitV*iRow);
		}
	}

	return S_OK;
}

HRESULT heightMap::CreateIndexData()
{
	m_iNumIndex = m_iNumFace * 3;
	m_IndexList.resize(m_iNumIndex);
	int iIndex = 0;
	for (int iRow = 0; iRow < m_iNumRowsCell; iRow++) {
		for (int iCol = 0; iCol < m_iNumColsCell; iCol++) {
			int iNextRow = iRow + 1;
			m_IndexList[iIndex + 0] = iRow * m_iNumColsVertice + iCol;
			m_IndexList[iIndex + 1] = m_IndexList[iIndex + 0] + 1;
			m_IndexList[iIndex + 2] = iNextRow * m_iNumColsVertice + iCol;
			m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
			m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
			m_IndexList[iIndex + 5] = m_IndexList[iIndex + 2] + 1;
			iIndex += 6;
		}
	}
	return S_OK;
}

D3DXVECTOR2 heightMap::GetTextureOfVertex(float fU, float fV)
{
	return D3DXVECTOR2(fU*50, fV*50);
}

D3DXVECTOR3 heightMap::GetNomalOfVertex(int iIndex)
{
	return D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

D3DXVECTOR4 heightMap::GetColorOfVertex(int iIndex)
{
	return D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}

float heightMap::GetHeightOfVertex(int iIndex)
{
	if (m_fHeightList.size() == 0) {
		return 0.0f;
	}
	else {
		return (m_fHeightList[iIndex] * m_fScaleHeight) - 100.f;
	}
	
}

bool heightMap::Init()
{
	return true;
}

bool heightMap::Frame()
{
	Shape_DX::Frame();
	return true;
}

bool heightMap::Render()
{
	Shape_DX::Render();
	return true;
}

bool heightMap::Release()
{
	Shape_DX::Release();
	return true;
}


heightMap::~heightMap() { }