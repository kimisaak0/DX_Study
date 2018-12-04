#pragma once
#define DIRECTINPUT_VERSION 0x0800
#define _CRT_SECURE_NO_WARNINGS    
//#pragma warning( disable:4005) //��ũ�� ������ ���� ����� �ʱ�.

//#define _DISABLE_EXTENDED_ALIGNED_STORAGE //�޸� �ڵ� ���� ��� ����?

#include <Windows.h>

#include <wrl.h> //Windows Runtime C++ Template Library //ComPtr���

#include <tchar.h>
#include <time.h>
#include <cassert>

#include <memory> //����Ʈ ������ ���

//stl���
#include <set>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>

//dx (���� ����)
#include "D3D11_4.h" // 
#include "d3dx11.h"  
#include "dxgi1_6.h"
#include "D3Dcompiler.h"
#include "D2D1.h"
#include "D2D1Helper.h"
#include "DWrite.h"

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


using namespace std;
using namespace Microsoft::WRL;
using namespace D2D1;

//���ڿ� Ÿ������
typedef basic_string<TCHAR>     T_STR;
typedef basic_string<wchar_t>   W_STR;
typedef basic_string<char>      C_STR;
typedef vector<T_STR>		    T_STR_VECTOR;

//��ũ��
#define randf(x) (((float)x)*rand()/(float)RAND_MAX) //0~x������ ������ �Ǽ����� ��ȯ
#define randstep(fMin,fMax) (fMin+randf(fMax-fmin))  //min���� max������ ������ �Ǽ����� ��ȯ
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;  //x���� min���� ������ min����, max���� ũ�� max�� ������Ŵ.

#define SAFE_NEW(A, B)              { if (!A) A = new B; }                    //A�� ������Ʈ�̸� A�� B�� �����Ҵ��Ѵ�.
#define SAFE_DEL(A)                 { if (A) delete A; (A)=nullptr; }         //A�� ������Ʈ�� �ƴϸ� A�� �޸𸮸� �����ϰ�, Nullptr�� �����Ѵ�.
#define SAFE_NEW_ARRAY(A, B, C)	    { if (!A && C>0) A = new B[C]; }          //A�� ������Ʈ�� �ƴϰ� C�� 1�̻��̸� A�� B�� C���� �迭�� �����Ҵ��Ѵ�.
#define SAFE_DELETE_ARRAY(A)		{ if (A) delete[] A; (A)=nullptr; }       //A�� ������Ʈ�� �ƴϸ� A�� �Ҵ�� �迭 �޸𸮸� �����ϰ�, nullptr�� �����Ѵ�.
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }   //A�� �������Ͱ� �ƴϸ� A�� �������ϰ� nullptr�� �����Ѵ�.

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
		wsprintf(buffer,L"File=%s\nLine=%s", xstr(__FILE__),xstr(__LINE__));\
		MessageBox(NULL, buffer,output,MB_OK); return hr;}\
	}

#define H(x){ if (FAILED(x)){\
		LPWSTR output;\
		WCHAR buffer[256]={0,};\
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_ALLOCATE_BUFFER,\
		NULL,x,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&output,0,NULL);\
		wsprintf(buffer,L"File=%s\nLine=%s", xstr(__FILE__),xstr(__LINE__));\
		MessageBox(NULL, buffer,output,MB_OK);}\
	}

#else
#define H_RETURN(x) (x)
#define H(x) (x)
#endif

