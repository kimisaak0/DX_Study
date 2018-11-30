#pragma once
#include "Shape_DX.h"

struct MapDesc
{
	int iNumColsVertice;      //타일의 가로 정점 개수 (2^n개 권장)
	int iNumRowsVertice;      //타일의 세로 정점 개수 (2^n개 권장)
	float fDistance;          //셀의 가로세로 길이 (셀은 정사각형으로 만든다.)	
	float fScaleHeight;       //정점의 높이값 (높이맵에서 사용할 것 미리 만들어 둠)

	T_STR szVSFilePath;       //쉐이더 파일 이름
	T_STR szPSFilePath;       //쉐이더 파일 이름
	T_STR szGSFilePath;       //쉐이더 파일 이름

	T_STR szTexFilePath;      //텍스쳐 파일 이름
};

class DefaultMap : public Shape_DX
{
	MapDesc m_MapDesc;

	int m_iNumRowsVertice;     //맵의 가로 정점 개수
	int m_iNumColsVertice;	   //맵의 세로 정점 개수
	int m_iNumVertice;		   //맵의 총 정점 개수

	int m_iNumRowsCell;		   //맵의 가로 셀 개수
	int m_iNumColsCell;		   //맵의 세로 셀 개수

	int m_iNumFace;			   //맵의 총 페이스 개수

	float m_fCellDistance;	   //맵에서 쓸 셀의 가로세로 길이 (desc의 값과의 비율을 이용해 스케일을 줄 수 있다.)

public:
	bool CreateMap(MapDesc TileDesc, UINT rowScale=1, UINT colScale=1, float tileScale=1);

	//어차피 가상함수지만 다른 종류의 맵에서 상속해서 쓸 수 있음을 표시하기 위해 virtual을 씀.
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
	DefaultMap();
	virtual ~DefaultMap();
};