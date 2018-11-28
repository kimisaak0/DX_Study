#include "01_enumCs_DX.h"

#ifndef SAFE_RELEASE
  #define SAFE_RELEASE(A)		       { if(A) { (A)->Release(); (A)=NULL; } }
#endif 

#ifndef SAFE_NEW
  #define SAFE_NEW(A, B)			   { if (!A) A = new B; }
#endif 

#ifndef SAFE_DEL
  #define SAFE_DEL(A)				   { if (A) delete A; (A)=NULL; }
#endif 

#ifndef SAFE_DELETE_ARRAY
  #define SAFE_DELETE_ARRAY(A)	       { if (A) delete [] A; (A)=NULL; }
#endif 

//----enumOutputC_DX

enumOutputC_DX::enumOutputC_DX() { }

//클래스에 아웃풋 객체를 세팅한다.
void enumOutputC_DX::Set(UINT iIndex, IDXGIOutput* pOutput)
{
	m_uOutput = iIndex;
	m_pOutput = pOutput;
	m_pOutput->GetDesc(&m_dioDesc);
}

//객체가 소멸할 떄 내부의 정보를 지워줌
enumOutputC_DX::~enumOutputC_DX()
{
	SAFE_RELEASE(m_pOutput);
	m_dimMode_Vector.clear();
}

//====

//----enumAdapterC_DX

enumAdapterC_DX::enumAdapterC_DX() { }

//클래스에 어댑터 정보를 세팅한다.
void enumAdapterC_DX::Set(UINT iIndex, IDXGIAdapter* pAdapter)
{
	m_uAdapterOrdinal = iIndex;
	m_pAdapter = pAdapter;
	pAdapter->GetDesc(&m_diaDesc);  //어댑터의 정보를 받아서 저장.
}

//객체가 소멸할 떄 내부의 정보를 지워줌
enumAdapterC_DX::~enumAdapterC_DX()
{
	enumDeviceC_DX* pDeviceInfo;
	for (int i = 0; i < m_edcInfo_vector.size(); i++) {
		pDeviceInfo = m_edcInfo_vector[i];
		SAFE_DEL(pDeviceInfo);
	}
	m_edcInfo_vector.clear();

	enumOutputC_DX* pOutputInfo;
	for (int i = 0; i < m_eocInfo_vector.size(); i++) {
		pOutputInfo = m_eocInfo_vector[i];
		SAFE_DEL(pOutputInfo);
	}
	m_eocInfo_vector.clear();

	SAFE_RELEASE(m_pAdapter);
}

//======

//-----enumeratoinC_DX

enumeratoinC_DX::enumeratoinC_DX() { }


HRESULT enumeratoinC_DX::Enumerate(IDXGIFactory* pFactory)
{
	HRESULT hr;
	if (pFactory == nullptr) {
		return E_FAIL;
	}

	ClearAdapterInfoList();

	for (int iIndex = 0; ; ++iIndex) {
		//어댑터 객체 생성
		IDXGIAdapter* pAdapter = nullptr;
		hr = pFactory->EnumAdapters(iIndex, &pAdapter);
		if (FAILED(hr)) { break; }

		//정보를 담을 클래스 객체 생성
		enumAdapterC_DX* pAdapterInfo = nullptr;
		SAFE_NEW(pAdapterInfo, enumAdapterC_DX);
		if (!pAdapterInfo) {
			return E_OUTOFMEMORY;
		}

		pAdapterInfo->Set(iIndex, pAdapter);

		hr = EnumerateDevices(pAdapterInfo);
		if (FAILED(hr)) {
			delete pAdapterInfo;
			continue;
		}

		hr = EnumerateOutputs(pAdapterInfo);
		if (FAILED(hr || pAdapterInfo->m_eocInfo_vector.size() <= 0)) {
			delete pAdapterInfo;
			continue;
		}

		m_eacInfo_vector.push_back(pAdapterInfo);
	}
	return S_OK;
}

HRESULT enumeratoinC_DX::EnumerateDevices(enumAdapterC_DX* pAdapterInfo)
{
	HRESULT hr;

	D3D_DRIVER_TYPE dxDriverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	const D3D_FEATURE_LEVEL dxFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(dxFeatureLevels);
	const UINT devTypeArrayCount = sizeof(dxDriverTypes) / sizeof(dxDriverTypes[0]);

	for (UINT uDeviceType = 0; uDeviceType < devTypeArrayCount; uDeviceType++) {
		enumDeviceC_DX* pDeviceInfo = 0;
		SAFE_NEW(pDeviceInfo, enumDeviceC_DX);
		if (pDeviceInfo == nullptr) {	return E_OUTOFMEMORY; }

		pDeviceInfo->m_uAdapterOdinal = pAdapterInfo->m_uAdapterOrdinal;
		pDeviceInfo->dtDeviceType = dxDriverTypes[uDeviceType];

		ID3D11Device* pd3dDevice = nullptr;
		ID3D11DeviceContext* pImmediateContext = nullptr;
		IDXGIAdapter* pAdapter = nullptr;

		D3D_DRIVER_TYPE ddt = dxDriverTypes[uDeviceType];
		if (dxDriverTypes[uDeviceType] == D3D_DRIVER_TYPE_HARDWARE)
		{
			pAdapter = pAdapterInfo->m_pAdapter;
			ddt = D3D_DRIVER_TYPE_UNKNOWN;
		}

		D3D_FEATURE_LEVEL getFL;

		hr = D3D11CreateDevice(pAdapter, ddt, (HMODULE)0, NULL, dxFeatureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &pd3dDevice, &getFL, &pImmediateContext);
		if (FAILED(hr)) {
			delete pDeviceInfo;
			continue;
		}

		D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS ho;
		pd3dDevice->CheckFeatureSupport(D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS, &ho, sizeof(ho));

		SAFE_RELEASE(pd3dDevice);
		SAFE_RELEASE(pImmediateContext);
		
		pAdapterInfo->m_edcInfo_vector.push_back(pDeviceInfo);

	}

	return S_OK;
}

HRESULT enumeratoinC_DX::EnumerateDisplayModes(enumOutputC_DX* pOutputinfo)
{
	HRESULT hr = S_OK;
	DXGI_FORMAT allowedAdapterFormatArray[] =
	{
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT_R16G16_FLOAT,
		DXGI_FORMAT_R10G10B10A2_UNORM,
	};

	int allowedAdapterFormatArrayCount = sizeof(allowedAdapterFormatArray) / sizeof(allowedAdapterFormatArray[0]);

	for (int f = 0; f < allowedAdapterFormatArrayCount; ++f) {
		UINT NumModes = 0;
		hr = pOutputinfo->m_pOutput->GetDisplayModeList(allowedAdapterFormatArray[f], DXGI_ENUM_MODES_SCALING, &NumModes, 0);
		DXGI_MODE_DESC* pDesc = new DXGI_MODE_DESC[NumModes];

		assert(pDesc);

		if (!pDesc) { return E_OUTOFMEMORY; }

		hr = pOutputinfo->m_pOutput->GetDisplayModeList(allowedAdapterFormatArray[f], DXGI_ENUM_MODES_SCALING, &NumModes, pDesc);

		if (DXGI_ERROR_NOT_FOUND == hr) {
			SAFE_DELETE_ARRAY(pDesc);
			NumModes = 0;
			break;
		}

		if (SUCCEEDED(hr)) {
			for (UINT m = 0; m < NumModes; m++) {
				if (pDesc[m].Width >= 800 && pDesc[m].Height >= 600) {
					pOutputinfo->m_dimMode_Vector.push_back(pDesc[m]);
				}
			}
		}
		SAFE_DELETE_ARRAY(pDesc);
	}
	return hr;
}

HRESULT enumeratoinC_DX::EnumerateOutputs(enumAdapterC_DX* pAdapterInfo)
{
	HRESULT hr;
	IDXGIOutput* pOutput;

	for (int iOutput = 0; ; ++iOutput) {
		pOutput = nullptr;
		hr = pAdapterInfo->m_pAdapter->EnumOutputs(iOutput, &pOutput);
		
		if (DXGI_ERROR_NOT_FOUND == hr) {
			return S_OK;
		}
		else if(FAILED(hr)) {
			return hr; //something bad happened;
		}
		else { //success
			enumOutputC_DX* pOutputInfo = new enumOutputC_DX;
			if (!pOutputInfo) {
				SAFE_RELEASE(pOutput);
				return E_OUTOFMEMORY;
			}
			pOutputInfo->Set(iOutput, pOutput);

			EnumerateDisplayModes(pOutputInfo);
			if (pOutputInfo->m_dimMode_Vector.size() <= 0) {
				//if this output has no valid display mode, do not save it.
				delete pOutputInfo;
				continue;
			}
			pAdapterInfo->m_eocInfo_vector.push_back(pOutputInfo);
		}
	}
}

void enumeratoinC_DX::ClearAdapterInfoList()
{
	enumAdapterC_DX* pAdaterInfo;

	for (int i = 0; i < m_eacInfo_vector.size(); i++) {
		pAdaterInfo = m_eacInfo_vector[i];
		SAFE_DEL(pAdaterInfo);
	}

	m_eacInfo_vector.clear();
}

enumeratoinC_DX::~enumeratoinC_DX()
{

}

//=====