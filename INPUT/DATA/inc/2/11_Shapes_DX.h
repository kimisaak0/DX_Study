#pragma once
#include "10_Shape_DX.h"

class Line_Shape : public Shape_DX
{
public:
	HRESULT CreateVertexData() override;
	HRESULT CreateIndexData() override;

	HRESULT LoadPixelShader(T_STR  szName) override;
	HRESULT LoadGeoShader(T_STR  szName) override;

	bool Draw(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor = D3DXVECTOR4(1, 0, 0, 1));

public:
	Line_Shape();
	virtual ~Line_Shape();
};

class Plane_Shape : public Shape_DX
{
public:
	HRESULT CreateVertexData() override;
	HRESULT CreateIndexData() override;

	HRESULT LoadGeoShader(T_STR  szName) override;

public:
	Plane_Shape();
	virtual ~Plane_Shape();
};

class Box_Shape : public Shape_DX
{
public:
	HRESULT CreateVertexData() override;
	HRESULT CreateIndexData() override;

	HRESULT LoadGeoShader(T_STR szName) override;

public:
	Box_Shape();
	virtual ~Box_Shape();
};
