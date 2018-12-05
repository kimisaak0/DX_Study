#pragma once
#include "Shape_DX.h"

struct MapDesc
{
	int iNumColsVertice;      //Ÿ���� ���� ���� ���� (2^n�� ����)
	int iNumRowsVertice;      //Ÿ���� ���� ���� ���� (2^n�� ����)
	float fDistance;          //���� ���μ��� ���� (���� ���簢������ �����.)	
	float fScaleHeight;       //������ ���̰� (���̸ʿ��� ����� �� �̸� ����� ��)

	T_STR szVSFilePath;       //���̴� ���� �̸�
	T_STR szPSFilePath;       //���̴� ���� �̸�
	T_STR szGSFilePath;       //���̴� ���� �̸�

	T_STR szTexFilePath;      //�ؽ��� ���� �̸�
};

class heightMap : public Shape_DX
{
public:
	int m_iNumRowsVertice;     //���� ���� ���� ����
	int m_iNumColsVertice;	   //���� ���� ���� ����

	int m_iNumVertice;		   //���� �� ���� ����

protected:
	MapDesc m_MapDesc;

	int m_iNumRowsCell;		   //���� ���� �� ����
	int m_iNumColsCell;		   //���� ���� �� ����

	int m_iNumFace;			   //���� �� ���̽� ����

	float m_fCellDistance;	   //�ʿ��� �� ���� ���μ��� ���� (desc�� ������ ������ �̿��� �������� �� �� �ִ�.)

	vector<float> m_fHeightList; //���̸ʿ��� ���� ���� ���� ����
	float m_fScaleHeight;

public:
	bool CreateMap(MapDesc TileDesc);
	bool CreateHeightMap(T_STR HeightMapPath);

	//������ �����Լ����� �ٸ� ������ �ʿ��� ����ؼ� �� �� ������ ǥ���ϱ� ���� virtual�� ��.
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;

	D3DXVECTOR2 GetTextureOfVertex(float fU, float fV);
	D3DXVECTOR3 GetNomalOfVertex(int iIndex);
	D3DXVECTOR4 GetColorOfVertex(int iIndex);
	float GetHeightOfVertex(int iIndex);

	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	heightMap();
	virtual ~heightMap();
};