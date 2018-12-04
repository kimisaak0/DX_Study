#include "defaultmap.h"

DefaultMap::DefaultMap() { }


bool DefaultMap::CreateMap(MapDesc TileDesc, UINT rowScale, UINT colScale, float tileScale)
{
	m_iNumRowsVertice = TileDesc.iNumRowsVertice * (int)pow(2, rowScale - 1) + 1; //Ÿ���� ���� �������� * 2^(rowScale-1) + 1 (���� ���������� 2^n + 1���� ���ߴ� ���� ����)
	m_iNumColsVertice = TileDesc.iNumColsVertice * (int)pow(2, colScale - 1) + 1; //Ÿ���� ���� �������� * 2^(colScale-1) + 1 (���� ���������� 2^n + 1���� ���ߴ� ���� ����)

	m_iNumRowsCell = m_iNumRowsVertice - 1; //���� ���� �� ����. ���������� 2^n+1���� �������Ƿ� ���� ������ 2^n��
	m_iNumColsCell = m_iNumColsVertice - 1;	//���� ���� �� ����. ���������� 2^n+1���� �������Ƿ� ���� ������ 2^n��

	m_iNumVertice = m_iNumRowsVertice * m_iNumColsVertice; //���� ��� ������
	m_iNumFace = m_iNumRowsCell * m_iNumColsCell * 2;

	m_fCellDistance = TileDesc.fDistance * tileScale;

	Shape_DX::Create(TileDesc.szVSFilePath, TileDesc.szPSFilePath, TileDesc.szGSFilePath, TileDesc.szTexFilePath);

	return true;
}

HRESULT DefaultMap::CreateVertexData()
{
	Shape_DX::m_iNumVertex = m_iNumVertice;
	m_VertexList.resize(m_iNumVertice);
	
	float fHalfRows = (m_iNumRowsVertice - 1) / 2.0f;     //���� �߾��� �������� �����ϱ� ���� X��ǥ ����
	float fHalfCols = (m_iNumColsVertice - 1) / 2.0f;     //���� �߾��� �������� �����ϱ� ���� Z��ǥ ����
	float fTexcoodUnitU = 1.0f / (m_iNumRowsVertice - 1); //�ؽ��� ��ǥ�� u�� ����ġ.
	float fTexcoodUnitV = 1.0f / (m_iNumColsVertice - 1); //�ؽ��� ��ǥ�� v�� ����ġ.

	for (int iRow = 0; iRow < m_iNumRowsVertice; iRow++) {
		for (int iCol = 0; iCol < m_iNumColsVertice; iCol++) {
			int iIndex = iRow * m_iNumColsVertice + iCol;
			m_VertexList[iIndex].p.x = (iCol - fHalfCols)*m_fCellDistance;
			m_VertexList[iIndex].p.y = GetHeightOfVertex(iIndex); //�⺻ �ʿ����� ���̰��� �� ���Ƿ� 0.
			m_VertexList[iIndex].p.z = -((iRow - fHalfRows)*m_fCellDistance);
			m_VertexList[iIndex].n = GetNomalOfVertex(iIndex);
			m_VertexList[iIndex].c = GetColorOfVertex(iIndex);
			m_VertexList[iIndex].t = GetTextureOfVertex(fTexcoodUnitU*iCol, fTexcoodUnitV*iRow);
		}
	}

	return S_OK;
}

HRESULT DefaultMap::CreateIndexData()
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

D3DXVECTOR2 DefaultMap::GetTextureOfVertex(float fU, float fV)
{
	return D3DXVECTOR2(fU, fV);
}

D3DXVECTOR3 DefaultMap::GetNomalOfVertex(int iIndex)
{
	return D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

D3DXVECTOR4 DefaultMap::GetColorOfVertex(int iIndex)
{
	return D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}

float DefaultMap::GetHeightOfVertex(int iIndex)
{
	return -10.f;
}

bool DefaultMap::Init()
{
	return true;
}

bool DefaultMap::Frame()
{
	Shape_DX::Frame();
	return true;
}

bool DefaultMap::Render()
{
	Shape_DX::Render();
	return true;
}

bool DefaultMap::Release()
{
	Shape_DX::Release();
	return true;
}


DefaultMap::~DefaultMap() { }