#include "defaultmap.h"

DefaultMap::DefaultMap() { }


bool DefaultMap::CreateMap(MapDesc TileDesc, int rowScale, int colScale, float tileScale)
{
	m_iNumRowsVertice = TileDesc.iNumRowsVertice * rowScale * 2 + 1;
	m_iNumColsVertice = TileDesc.iNumColsVertice * colScale * 2 + 1;
	
	m_iNumRowsCell = m_iNumRowsVertice - 1;
	m_iNumColsCell = m_iNumColsVertice - 1;

	m_iNumVertice = m_iNumRowsVertice * m_iNumColsVertice;
	m_iNumFace = m_iNumRowsCell * m_iNumColsCell * 2;
	
	m_fCellDistance = TileDesc.fDistance * tileScale;
}					

bool DefaultMap::load(MapDesc TileDesc)
{

}


HRESULT DefaultMap::CreateVertexData()
{
	Shape_DX::m_iNumVertex = m_iNumVertice;
	m_VertexList.resize(m_iNumVertice);
}

HRESULT DefaultMap::CreateIndexData()
{

}

D3DXVECTOR2 DefaultMap::GetTextureOfVertex(float fU, float fV);
D3DXVECTOR3 DefaultMap::GetNomalOfVertex(int iIndex);
D3DXVECTOR4 DefaultMap::GetColorOfVertex(int iIndex);


bool DefaultMap::Init();
bool DefaultMap::Frame();
bool DefaultMap::Render();
bool DefaultMap::Release();


DefaultMap::~DefaultMap() { }