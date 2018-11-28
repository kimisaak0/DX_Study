#pragma once
#include "11_Shapes_DX.h"

class Dir_Line : public Line_Shape
{
public:
	HRESULT CreateVertexData();
	HRESULT CreateIndexData();
	
	HRESULT LoadGeometryShader(T_STR  szName);

	bool Render();

public:
	Dir_Line();
	virtual ~Dir_Line();
};

//구를 만드는 부분에서 문제가 있음.
class Sphere_Shape : public Box_Shape
{
	vector<PNCT_VERTEX>  m_vList;

public:
	PNCT_VERTEX NormalizeVertex(PNCT_VERTEX Vertex);
	void TriAppend(PNCT_VERTEX V0, PNCT_VERTEX V1, PNCT_VERTEX V2, vector<PNCT_VERTEX>& TriStream, int iIndex);

	HRESULT CreateVertexData();
	HRESULT CreateIndexData();
	
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	
	HRESULT LoadVertexShader(T_STR  szName);
	HRESULT LoadGeometryShader(T_STR  szName);

public:
	Sphere_Shape();
	virtual ~Sphere_Shape();
};