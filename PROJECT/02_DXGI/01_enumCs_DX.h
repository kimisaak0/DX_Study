#pragma once
#include "00_Header_DX.h"

//아웃풋 장치 : 물리적인 모니터 
//---각 아웃풋 장치에 대한 정보를 저장하는 클래스 
class enumOutputC_DX
{
public:
	UINT                     m_uOutput; //인덱스
	IDXGIOutput*             m_pOutput; //받아온 아웃풋 객체를 저장할 주소
	DXGI_OUTPUT_DESC         m_dioDesc; //아웃풋 객체의 정보를 저장할 구조체
	vector<DXGI_MODE_DESC>   m_dimMode_Vector; //아웃풋 객체가 지원하는 디스플레이 모드들을 저장할 배열

public:
	void Set(UINT iIndex, IDXGIOutput* pOutput); //클래스에 아웃풋 객체를 세팅한다.

public:
	enumOutputC_DX();
	virtual ~enumOutputC_DX();
};


//디바이스 장치 : 그래픽 카드와 모니터 정보를 가지고 생성할 수 있는 출력 디바이스.
//---생성된 디바이스 장치에 대한 정보를 저장하는 클래스
class enumDeviceC_DX
{
public:
	UINT                      m_uAdapterOdinal; //인덱스
	D3D_DRIVER_TYPE           dtDeviceType;     //디바이스를 생성한 드라이버 타입
	//vector<enumOutputC_DX*>   m_eocInfo_Vector; //아웃풋 정보 리스트인데.. 사용처가 없다?

};

//---컴퓨터에 장착된 어댑터(그래픽카드)객체를 생성.
class enumAdapterC_DX
{
public:
	UINT    m_uAdapterOrdinal;                 //인덱스
	IDXGIAdapter* m_pAdapter;                  //생성된 어댑터를 저장할 주소
	DXGI_ADAPTER_DESC m_diaDesc;               //어댑터의 정보를 저장하는 구조체
	vector<enumOutputC_DX*> m_eocInfo_vector;  //모니터에 대한 정보들을 저장.
	vector<enumDeviceC_DX*> m_edcInfo_vector;  //어떤 드라이버로 디바이스를 생성했는지에 대한 정보

public:
	void Set(UINT iIndex, IDXGIAdapter* pAdapter);  //클래스에 어댑터 정보를 세팅한다.

public:
	enumAdapterC_DX();
	virtual ~enumAdapterC_DX();
};

//-----
class enumeratoinC_DX
{
protected:
	HRESULT EnumerateDevices(enumAdapterC_DX* pAdapterInfo);	// 4가지 디바이스 타입에 대한 지원 여부를 확인해서 벡터에 저장한다.
	HRESULT EnumerateOutputs(enumAdapterC_DX* pAdapterInfo);	// 검색된 어댑터 인터페이스를 통해 그래픽 카드에 부착된 모든 아웃풋 기기를 벡터에 저장한다.
	HRESULT EnumerateDisplayModes(enumOutputC_DX* pOutputinfo); // 지정된 포맷을 사용하여 디스플레이 모드를 열거하고 해상도가 800*600이상인 목록만 발췌하여 벡터에 저장한다.

public:
	vector<enumAdapterC_DX*> m_eacInfo_vector;

public:
	HRESULT Enumerate(IDXGIFactory* pFactory);					// EnumAdapters를 통해 열거된 어댑터를 대상으로 디바이스 지원 여부와 각 출력장치의 해상도 목록을 저장함.
	
	void ClearAdapterInfoList();

public:
	enumeratoinC_DX();
	virtual ~enumeratoinC_DX();
};
