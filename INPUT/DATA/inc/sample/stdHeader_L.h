#pragma once
#define DIRECTINPUT_VERSION 0x0800
#define _CRT_SECURE_NO_WARNINGS    
#pragma warning( disable:4005) //��ũ�� ������ ���� ����� �ʱ�.

//#define _DISABLE_EXTENDED_ALIGNED_STORAGE //�޸� �ڵ� ���� ��� ����?

#pragma region //��� ���� �� ���̺귯�� ���� �߰�

#include <Windows.h>

#include <tchar.h>
#include <time.h>
#include <cassert>

#include <memory> //����Ʈ ������ ���
#include <wrl.h> //Windows Runtime C++ Template Library //ComPtr���

//timeGetTime()
#include <mmsystem.h>
#pragma comment		(lib, "winmm.lib" )

//stl���
#include <set>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <iterator>

//dx (���� ����)
#include "d3dx11.h"  
#include "D3D11.h" 
#include "dxgi.h"
#include "D3Dcompiler.h"
#include "D2D1.h"
#include "D2D1Helper.h"
#include "DWrite.h"
#include "dinput.h"


//���̺귯�� ����
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

#pragma region //namespace ���
using namespace std;
using namespace Microsoft::WRL;
using namespace D2D1;
#pragma endregion

namespace Lypi
{
#pragma region	//���ڿ� Ÿ������
	typedef basic_string<TCHAR>     T_STR;
	typedef basic_string<wchar_t>   W_STR;
	typedef basic_string<char>      C_STR;
	typedef vector<T_STR>		    T_STR_VECTOR;
#pragma endregion

#pragma region	//��ũ��
#define str(x) L#x
#define randf(x) (((float)x)*rand()/(float)RAND_MAX) //0~x������ ������ �Ǽ����� ��ȯ
#define randstep(fMin,fMax) (fMin+randf(fMax-fmin))  //min���� max������ ������ �Ǽ����� ��ȯ
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;  //x���� min���� ������ min����, max���� ũ�� max�� ������Ŵ.

#define SAFE_NEW(A, B)              { if (!A) A = new B; }                    //A�� ������Ʈ�̸� A�� B�� �����Ҵ��Ѵ�.
#define SAFE_DEL(A)                 { if (A) delete A; (A)=nullptr; }         //A�� ������Ʈ�� �ƴϸ� A�� �޸𸮸� �����ϰ�, Nullptr�� �����Ѵ�.
#define SAFE_NEW_ARRAY(A, B, C)	    { if (!A && C>0) A = new B[C]; }          //A�� ������Ʈ�� �ƴϰ� C�� 1�̻��̸� A�� B�� C���� �迭�� �����Ҵ��Ѵ�.
#define SAFE_DELETE_ARRAY(A)		{ if (A) delete[] A; (A)=nullptr; }       //A�� ������Ʈ�� �ƴϸ� A�� �Ҵ�� �迭 �޸𸮸� �����ϰ�, nullptr�� �����Ѵ�.
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }   //A�� �������Ͱ� �ƴϸ� A�� �������ϰ� nullptr�� �����Ѵ�.

#define V(x)                        { hr = (x); }
#define V_FRETURN(x)                { hr = (x); if( FAILED(hr) ) { return hr; } }


//����� �޽��� ��¿�
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

#pragma region //�ܺκ��� ����
	class winL;

	//device_DX
	extern ID3D11Device*             g_pD3dDevice;
	extern ID3D11DeviceContext*      g_pD3dContext;
	extern IDXGISwapChain*           g_pSwapChain;
	extern ID3D11RenderTargetView*   g_pRenderTagetView;	
	extern ID3D11DepthStencilView*   g_pDepthStencilView;  
	extern D3D11_VIEWPORT            g_d3dViewPort;		   

	//WndC_DX
	extern HINSTANCE    g_hInst;      //�������� �ν��Ͻ� �ڵ鰪
	extern HWND         g_hWnd;       //������ �������� �ڵ鰪
	extern RECT         g_rtWindow;   //������ ����
	extern RECT         g_rtClient;   //Ŭ���̾�Ʈ ���� (�۾�����)
	extern winL*        g_pWindow;    //���� ������ �����쿡 ���� ������

	extern float        g_dSPF;       //SPF

	extern UINT    g_uPrimType;    //�������� Ÿ��
	extern UINT    g_uCullMode;    //�ø����
	extern UINT    g_uFillMode;    //���̾� �����Ӹ� ������

#pragma endregion 

#pragma region	//���ø�

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
	//��ü�� STL::map���� �����ϱ� ���� Ŭ���� ���ø�.
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
		virtual int  Count();								// ��ü ��ü ���� ����
		
		virtual int  GetID(Child* pChild);					// ��ü �����ͷ� ��ü�� �ε����� ����.
		virtual int  GetID(const TCHAR* szName);			// ��ü �̸����� ��ü�� �ε����� ����.
		virtual Child* const  GetPtr(int iIndex);			// ��ü �ε����� ��ü �����͸� ����.
		virtual Child* const  GetPtr(const TCHAR* szName);  // ��ü �̸����� ��ü �����͸� ����.

		virtual bool Delete(int iIndex);					// �ε����� �ش��ϴ� ��ü ����.
		virtual bool Delete(Child* pChild);					// ��ü �����Ϳ� �ش��ϴ� ��ü ����.

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