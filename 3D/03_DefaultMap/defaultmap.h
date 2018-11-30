#pragma once
#include "Shape_DX.h"

struct MapDesc
{
	int iNumColsVertice;      //Ÿ���� ���� ���� ���� (2^n�� ����)
	int iNumRowsVertice;      //Ÿ���� ���� ���� ���� (2^n�� ����)
	float fDistance;          //���� ���μ��� ���� (���� ���簢������ �����.)	

	float fScaleHeight;       //������ ���̰� (���̸ʿ��� ����� �� �̸� ����� ��)
	T_STR szTextrueFile;      //�ؽ��� ���� �̸�
	T_STR szShaderFile;       //���̴� ���� �̸�
};

class DefaultMap : public Shape_DX
{
	MapDesc m_MapDesc;

	int m_iNumRowsVertice;     //���� ���� ���� ����
	int m_iNumColsVertice;	   //���� ���� ���� ����
	int m_iNumVertice;		   //���� �� ���� ����

	int m_iNumRowsCell;		   //���� ���� �� ����
	int m_iNumColsCell;		   //���� ���� �� ����

	int m_iNumFace;			   //���� �� ���̽� ����

	float m_fCellDistance;	   //�ʿ��� �� ���� ���μ��� ���� (desc�� ������ ������ �̿��� �������� �� �� �ִ�.)

public:
	bool CreateMap(MapDesc TileDesc, int rowScale=1, int colScale=1, float tileScale=1);
	bool load(MapDesc TileDesc);

	//������ �����Լ����� �ٸ� ������ �ʿ��� ����ؼ� �� �� ������ ǥ���ϱ� ���� virtual�� ��.
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
	D3DXVECTOR2 GetTextureOfVertex(float fU, float fV);
	D3DXVECTOR3 GetNomalOfVertex(int iIndex);
	D3DXVECTOR4 GetColorOfVertex(int iIndex);

	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	DefaultMap();
	virtual ~DefaultMap();
};