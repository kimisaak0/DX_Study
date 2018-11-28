#include "12_Shapes_ext.h"

//Direction Line (방향 지정 선)

Dir_Line::Dir_Line() {}

HRESULT Dir_Line::CreateVertexData()
{
	m_VertexList.resize(6);

	m_VertexList[0] = PNCT_VERTEX({ 0.0f, 0.0f, 0.0f },      { 0.0f, 0.0f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f});
	m_VertexList[1] = PNCT_VERTEX({ 100.0f, 0.0f, 0.0f },    { 0.0f, 0.0f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f});
	m_VertexList[2] = PNCT_VERTEX({ 0.0f, 0.0f, 0.0f },      { 0.0f, 0.0f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f});
	m_VertexList[3] = PNCT_VERTEX({ 0.0f, 100.0f, 0.0f },    { 0.0f, 0.0f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f});
	m_VertexList[4] = PNCT_VERTEX({ 0.0f, 0.0f, 0.0f },      { 0.0f, 0.0f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	m_VertexList[5] = PNCT_VERTEX({ 0.0f, 0.0f, 100.0f },    { 0.0f, 0.0f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	
	m_iNumVertex = (UINT)m_VertexList.size();

	return S_OK;
}

HRESULT Dir_Line::CreateIndexData()
{
	m_IndexList.resize(6);

	int iIndex = 0;
	m_IndexList[iIndex++] = 0; m_IndexList[iIndex++] = 1; m_IndexList[iIndex++] = 2; 
	m_IndexList[iIndex++] = 3; m_IndexList[iIndex++] = 4; m_IndexList[iIndex++] = 5;
	
	m_iNumIndex = (UINT)m_IndexList.size();
	
	return S_OK;
}
		
HRESULT Dir_Line::LoadGeometryShader(T_STR  szName)
{
	return S_OK;
}

bool Dir_Line::Render()
{
	m_Primitive = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
	Line_Shape::Render();
	m_Primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	return true;
}


Dir_Line::~Dir_Line() {}

// Sphere(구)
Sphere_Shape::Sphere_Shape() { }

//로컬 정점의 크기를 정규화하여 1로 만든다.
PNCT_VERTEX Sphere_Shape::NormalizeVertex(PNCT_VERTEX Vertex)
{
	PNCT_VERTEX newvertex; // = (PNCT_VERTEX)0;
	D3DXVec3Normalize(&newvertex.p, &Vertex.p); // 정점이 원점을 중심으로 하는 단위 벡터가 된다.
	newvertex.n = newvertex.p;
	newvertex.c = Vertex.c;
	newvertex.t = Vertex.t;

	return newvertex;
}

void Sphere_Shape::TriAppend(PNCT_VERTEX V0, PNCT_VERTEX V1, PNCT_VERTEX V2, vector<PNCT_VERTEX>& TriStream, int iIndex)
{
	TriStream[iIndex + 0] = NormalizeVertex(V0);
	TriStream[iIndex + 1] = NormalizeVertex(V1);
	TriStream[iIndex + 2] = NormalizeVertex(V2);
}


HRESULT Sphere_Shape::CreateVertexData()
{
	Box_Shape::CreateVertexData();
	Box_Shape::CreateIndexData();

	vector<PNCT_VERTEX> vList;
	vList.resize(m_IndexList.size());
	m_vList.resize((m_IndexList.size() / 3) * 12);

	for (int iFace = 0; iFace < 12; iFace++) {
		int iCount = iFace * 3;
		vList[iCount + 0] = m_VertexList[m_IndexList[iCount + 0]];
		vList[iCount + 1] = m_VertexList[m_IndexList[iCount + 1]];
		vList[iCount + 2] = m_VertexList[m_IndexList[iCount + 2]];
	}

	int iIndex = 0;
	for (int iFace = 0; iFace < 12; iFace++) {
		PNCT_VERTEX input[3];
		input[0] = vList[iFace * 3 + 0];
		input[1] = vList[iFace * 3 + 1];
		input[2] = vList[iFace * 3 + 2];

		PNCT_VERTEX Center0, Center1, Center2;
		
		Center0.p = D3DXVECTOR3((input[0].p + input[1].p) / 2.0);
		Center0.n = (input[0].n + input[1].n) / 2.0;
		Center0.c = (input[0].c + input[1].c) / 2.0;
		Center0.t = (input[0].t + input[1].t) / 2.0;

		Center1.p = D3DXVECTOR3((input[1].p + input[2].p) / 2.0);
		Center1.n = (input[1].n + input[2].n) / 2.0;
		Center1.c = (input[1].c + input[2].c) / 2.0;
		Center1.t = (input[1].t + input[2].t) / 2.0;

		Center2.p = D3DXVECTOR3((input[0].p + input[2].p) / 2.0);
		Center2.n = (input[0].n + input[2].n) / 2.0;
		Center2.c = (input[0].c + input[2].c) / 2.0;
		Center2.t = (input[0].t + input[2].t) / 2.0;

		TriAppend(input[0], Center0,  Center2,  m_vList,  iIndex);   iIndex += 3;
		TriAppend(Center0,  input[1], Center1,  m_vList,  iIndex);   iIndex += 3;
		TriAppend(input[2], Center2,  Center1,  m_vList,  iIndex);   iIndex += 3;
		TriAppend(Center0,  Center1,  Center2,  m_vList,  iIndex);   iIndex += 3;
	}

	m_iNumVertex = (UINT)m_vList.size();
	m_iNumIndex = (UINT)m_vList.size();

	return S_OK;
}

HRESULT Sphere_Shape::CreateIndexData()
{
	return S_OK;
}
		
HRESULT Sphere_Shape::CreateVertexBuffer()
{
	m_iVertexSize = sizeof(PNCT_VERTEX);
	m_dxObj.m_pVertexBuffer = D3D::CreateVertexBuffer(m_iNumVertex, sizeof(PNCT_VERTEX), &m_vList.at(0));
	//m_iVertexSize = 56;
	//D3D::CreateVertexBuffer(m_iNumVertex, 56, &m_vList.at(0), m_dxObj.m_pVertexBuffer.GetAddressOf());
	return S_OK;
}

HRESULT Sphere_Shape::CreateIndexBuffer()
{
	return S_OK;
}
		
HRESULT Sphere_Shape::LoadVertexShader(T_STR  szName)
{
	m_dxObj.m_pVertexShader.Attach(D3D::LoadVertexShaderFile(szName.c_str(), m_dxObj.m_pVSBlob.GetAddressOf(), "VS_NoMatrix"));

	return S_OK;
}

HRESULT Sphere_Shape::LoadGeometryShader(T_STR  szName)
{
	return Shape_DX::LoadGeoShader(szName);
}


Sphere_Shape::~Sphere_Shape() { }
