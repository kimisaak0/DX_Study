#pragma once
#include "00_Header_DX.h"

//�ƿ�ǲ ��ġ : �������� ����� 
//---�� �ƿ�ǲ ��ġ�� ���� ������ �����ϴ� Ŭ���� 
class enumOutputC_DX
{
public:
	UINT                     m_uOutput; //�ε���
	IDXGIOutput*             m_pOutput; //�޾ƿ� �ƿ�ǲ ��ü�� ������ �ּ�
	DXGI_OUTPUT_DESC         m_dioDesc; //�ƿ�ǲ ��ü�� ������ ������ ����ü
	vector<DXGI_MODE_DESC>   m_dimMode_Vector; //�ƿ�ǲ ��ü�� �����ϴ� ���÷��� ������ ������ �迭

public:
	void Set(UINT iIndex, IDXGIOutput* pOutput); //Ŭ������ �ƿ�ǲ ��ü�� �����Ѵ�.

public:
	enumOutputC_DX();
	virtual ~enumOutputC_DX();
};


//����̽� ��ġ : �׷��� ī��� ����� ������ ������ ������ �� �ִ� ��� ����̽�.
//---������ ����̽� ��ġ�� ���� ������ �����ϴ� Ŭ����
class enumDeviceC_DX
{
public:
	UINT                      m_uAdapterOdinal; //�ε���
	D3D_DRIVER_TYPE           dtDeviceType;     //����̽��� ������ ����̹� Ÿ��
	//vector<enumOutputC_DX*>   m_eocInfo_Vector; //�ƿ�ǲ ���� ����Ʈ�ε�.. ���ó�� ����?

};

//---��ǻ�Ϳ� ������ �����(�׷���ī��)��ü�� ����.
class enumAdapterC_DX
{
public:
	UINT    m_uAdapterOrdinal;                 //�ε���
	IDXGIAdapter* m_pAdapter;                  //������ ����͸� ������ �ּ�
	DXGI_ADAPTER_DESC m_diaDesc;               //������� ������ �����ϴ� ����ü
	vector<enumOutputC_DX*> m_eocInfo_vector;  //����Ϳ� ���� �������� ����.
	vector<enumDeviceC_DX*> m_edcInfo_vector;  //� ����̹��� ����̽��� �����ߴ����� ���� ����

public:
	void Set(UINT iIndex, IDXGIAdapter* pAdapter);  //Ŭ������ ����� ������ �����Ѵ�.

public:
	enumAdapterC_DX();
	virtual ~enumAdapterC_DX();
};

//-----
class enumeratoinC_DX
{
protected:
	HRESULT EnumerateDevices(enumAdapterC_DX* pAdapterInfo);	// 4���� ����̽� Ÿ�Կ� ���� ���� ���θ� Ȯ���ؼ� ���Ϳ� �����Ѵ�.
	HRESULT EnumerateOutputs(enumAdapterC_DX* pAdapterInfo);	// �˻��� ����� �������̽��� ���� �׷��� ī�忡 ������ ��� �ƿ�ǲ ��⸦ ���Ϳ� �����Ѵ�.
	HRESULT EnumerateDisplayModes(enumOutputC_DX* pOutputinfo); // ������ ������ ����Ͽ� ���÷��� ��带 �����ϰ� �ػ󵵰� 800*600�̻��� ��ϸ� �����Ͽ� ���Ϳ� �����Ѵ�.

public:
	vector<enumAdapterC_DX*> m_eacInfo_vector;

public:
	HRESULT Enumerate(IDXGIFactory* pFactory);					// EnumAdapters�� ���� ���ŵ� ����͸� ������� ����̽� ���� ���ο� �� �����ġ�� �ػ� ����� ������.
	
	void ClearAdapterInfoList();

public:
	enumeratoinC_DX();
	virtual ~enumeratoinC_DX();
};
