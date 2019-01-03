#pragma once
#define DIRECTINPUT_VERSION 0x0800
#define _CRT_SECURE_NO_WARNINGS    
#pragma warning( disable:4005) //매크로 재정의 에러 띄우지 않기.

//#define _DISABLE_EXTENDED_ALIGNED_STORAGE //메모리 자동 정렬 사용 안함?

#pragma region //헤더 파일 및 라이브러리 파일 추가

#include <Windows.h>

#include <tchar.h>
#include <time.h>
#include <cassert>

#include <memory> //스마트 포인터 사용
#include <wrl.h> //Windows Runtime C++ Template Library //ComPtr사용

//timeGetTime()
#include <mmsystem.h>
#pragma comment		(lib, "winmm.lib" )

//stl헤더
#include <set>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <iterator>

//dx (순서 주의)
#include "d3dx11.h"  
#include "D3D11.h" 
#include "dxgi.h"
#include "D3Dcompiler.h"
#include "D2D1.h"
#include "D2D1Helper.h"
#include "DWrite.h"
#include "dinput.h"


//라이브러리 포함
#pragma comment (lib, "D3D11.lib")

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx10d.lib" )	
#pragma comment( lib, "d3dx11d.lib" )	
#else
#pragma comment( lib, "d3dx10.lib" )
#pragma comment( lib, "d3dx11.lib" )
#endif

#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "D3Dcompiler.lib")
#pragma comment (lib, "D2D1.lib")
#pragma comment (lib, "DWrite.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")

#pragma endregion

#pragma region //namespace 사용
using namespace std;
using namespace Microsoft::WRL;
using namespace D2D1;
#pragma endregion

namespace Lypi
{
#pragma region	//문자열 타입정의
	typedef basic_string<TCHAR>     T_STR;
	typedef basic_string<wchar_t>   W_STR;
	typedef basic_string<char>      C_STR;
	typedef vector<T_STR>		    T_STR_VECTOR;
#pragma endregion

#pragma region	//매크로
#define str(x) L#x
#define randf(x) (((float)x)*rand()/(float)RAND_MAX) //0~x사이의 랜덤한 실수값을 반환
#define randstep(fMin,fMax) (fMin+randf(fMax-fmin))  //min에서 max까지의 랜덤할 실수값을 반환
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;  //x값이 min보다 작으면 min으로, max보다 크면 max로 고정시킴.

#define SAFE_NEW(A, B)              { if (!A) A = new B; }                    //A가 널포인트이면 A에 B를 동적할당한다.
#define SAFE_DEL(A)                 { if (A) delete A; (A)=nullptr; }         //A가 널포인트가 아니면 A의 메모리를 해제하고, Nullptr로 설정한다.
#define SAFE_NEW_ARRAY(A, B, C)	    { if (!A && C>0) A = new B[C]; }          //A가 널포인트가 아니고 C가 1이상이면 A에 B를 C개의 배열로 동적할당한다.
#define SAFE_DELETE_ARRAY(A)		{ if (A) delete[] A; (A)=nullptr; }       //A가 널포인트가 아니면 A에 할당된 배열 메모리를 해제하고, nullptr로 설정한다.
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }   //A가 널포인터가 아니면 A를 릴리즈하고 nullptr로 설정한다.

#define V(x)                        { hr = (x); }
#define V_FRETURN(x)                { hr = (x); if( FAILED(hr) ) { return hr; } }


//디버그 메시지 출력용
#define	DEBUGMSG(lpText)\
	{\
		TCHAR szBuffer[256];\
		_stprintf_s(szBuffer, _T("[File: %s][Line: %d]\n[Note : %s]"), _CRT_WIDE(__FILE__), __LINE__, lpText);	\
		MessageBox(NULL, szBuffer, _T("ERROR"), MB_ICONERROR);}



#if defined(DEBUG) | defined(_DEBUG) 
#define H_RETURN(x){ if (FAILED(x)){\
		LPWSTR output;\
		WCHAR buffer[256]={0,};\
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_ALLOCATE_BUFFER,\
		NULL,x,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&output,0,NULL);\
		wsprintf(buffer,L"File=%s\nLine=%s", str(__FILE__),str(__LINE__));\
		MessageBox(NULL, buffer,output,MB_OK); return hr;}\
	}

#define H(x){ if (FAILED(x)){\
		LPWSTR output;\
		WCHAR buffer[256]={0,};\
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_ALLOCATE_BUFFER,\
		NULL,x,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&output,0,NULL);\
		wsprintf(buffer,L"File=%s\nLine=%s", str(__FILE__),str(__LINE__));\
		MessageBox(NULL, buffer,output,MB_OK);}\
	}

#else
#define H_RETURN(x) (x)
#define H(x) (x)
#endif

#pragma endregion

#pragma region //외부변수 정의
	class winL;

	//device_DX
	extern ID3D11Device*             g_pD3dDevice;
	extern ID3D11DeviceContext*      g_pD3dContext;
	extern IDXGISwapChain*           g_pSwapChain;
	extern ID3D11RenderTargetView*   g_pRenderTagetView;	
	extern ID3D11DepthStencilView*   g_pDepthStencilView;  
	extern D3D11_VIEWPORT            g_d3dViewPort;		   

	//WndC_DX
	extern HINSTANCE    g_hInst;      //윈도우의 인스턴스 핸들값
	extern HWND         g_hWnd;       //생성된 윈도우의 핸들값
	extern RECT         g_rtWindow;   //윈도우 영역
	extern RECT         g_rtClient;   //클라이언트 영역 (작업영역)
	extern winL*        g_pWindow;    //현재 생성된 윈도우에 대한 포인터

	extern float        g_dSPF;       //SPF

	extern UINT    g_uPrimType;    //토폴로지 타입
	extern UINT    g_uCullMode;    //컬링모드
	extern UINT    g_uFillMode;    //와이어 프레임만 렌더링

#pragma endregion 

#pragma region	//템플릿

	template <class T>
	void Swap(T* a, T* b)
	{
		T Temp;
		Temp = *a;
		*a = *b;
		*b = Temp;
	};

	template <typename TContainer>
	void stl_clear(TContainer& cnt)
	{
		typename TContainer::iterator iter;
		for (iter = cnt.begin(); iter != cnt.end(); iter++) {
			delete *iter;
		}
		cnt.clear();
	};

	template<typename TContainer>
	void stl_wipe(TContainer& container)
	{
		typename TContainer::iterator iter;
		for (iter = container.begin(); iter != container.end(); ++iter)
		{
			delete *iter;
		}
		container.clear();
	}

	template<typename T>
	void stl_wipe_vector(vector<T>& rVector)
	{
		vector<T> emptyData;
		rVector.swap(emptyData);
	}

	template <typename TCnt>
	void stl_clear_vector(vector<TCnt>& vTCnt)
	{
		vector<TCnt> emptyData;
		vTCnt.swap(emptyData);
	};

#pragma region classTemplate
	//객체를 STL::map으로 관리하기 위한 클래스 템플릿.
	template <class Child>
	class TemplateMap
	{
	public:
		typedef unordered_map <int, Child*>     TMap;
		typedef typename TMap::iterator  TMapIter;

		TMap       TM;
		TMapIter   TI;

		int        m_iCurIndex;

	public:													
		virtual int  Count();								// 전체 객체 갯수 리턴
		
		virtual int  GetID(Child* pChild);					// 객체 포인터로 객체의 인덱스를 리턴.
		virtual int  GetID(const TCHAR* szName);			// 객체 이름으로 객체의 인덱스를 리턴.
		virtual Child* const  GetPtr(int iIndex);			// 객체 인덱스로 객체 포인터를 리턴.
		virtual Child* const  GetPtr(const TCHAR* szName);  // 객체 이름으로 객체 포인터를 리턴.

		virtual bool Delete(int iIndex);					// 인덱스에 해당하는 객체 삭제.
		virtual bool Delete(Child* pChild);					// 객체 포인터에 해당하는 객체 삭제.

	public:
		TemplateMap();
		virtual ~TemplateMap();
	};

	template <class Child>
	TemplateMap<Child>::TemplateMap()
	{
		m_iCurIndex = 0;
		TM.clear();
	}

	
	template <class Child>
	int TemplateMap<Child>::Count()
	{
		return (int)TM.size();
	}

	template <class Child>
	int TemplateMap<Child>::GetID(Child* pChild)
	{
		int iIndex = -1;
		for (TMapIter iter = TM.begin(); iter != TM.end(); iter++) {
			Child *pPoint = (Child*)(*iter).second;
			if (pChild == pPoint) {
				iIndex = (*iter).first;
				break;
			}
		}
		return iIndex;
	}

	template <class Child>
	int TemplateMap<Child>::GetID(const TCHAR* szName)
	{
		int iIndex = -1;
		for (TMapIter iter = TM.begin(); iter != TM.end(); iter++) {
			Child *pPoint = (Child*)(*iter).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szName)) {
				iIndex = (*iter).first;
				break;
			}
		}
		return iIndex;
	}

	template <class Child>
	Child* const TemplateMap<Child>::GetPtr(int iIndex)
	{
		TMapIter iter = TM.find(iIndex);
		if (iter == TM.end()) {
			return nullptr;
		}
		Child* pPoint = (*iter).second;
		return pPoint;
	}

	template <class Child>
	Child* const TemplateMap<Child>::GetPtr(const TCHAR* szName)
	{
		for (TMapIter iter = TM.begin(); iter != TM.end(); iter++) {
			Child *pPoint = (Child*)(*iter).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szName)) {
				return pPoint;
			}
		}
		return nullptr;
	}

	template <class Child>
	bool TemplateMap<Child>::Delete(int iIndex)
	{
		Child* const pChild = GetPtr(iIndex);
		if (pChild) {
			pChild->Release();
			TM.erase(iIndex);
		}
		return true;
	}

	template <class Child>
	bool TemplateMap<Child>::Delete(Child* pChild)
	{
		if (pChild) {
			pChild->Release();
			TM.erase(GetID(pChild));
		}
		return true;
	}

	template <class Child>
	TemplateMap<Child>::~TemplateMap()
	{
		Release();
	}
#pragma endregion

#pragma endregion

}