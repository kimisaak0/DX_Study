#pragma once
#define DIRECTINPUT_VERSION 0x0800
#define _CRT_SECURE_NO_WARNINGS    
//#pragma warning( disable:4005) //매크로 재정의 에러 띄우지 않기.

//#define _DISABLE_EXTENDED_ALIGNED_STORAGE //메모리 자동 정렬 사용 안함?

#include <Windows.h>

#include <wrl.h> //Windows Runtime C++ Template Library //ComPtr사용

#include <tchar.h>
#include <time.h>
#include <cassert>

#include <memory> //스마트 포인터 사용

//stl헤더
#include <set>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>

//dx (순서 주의)
#include "D3D11_4.h" // 
#include "d3dx11.h"  
#include "dxgi1_6.h"
#include "D3Dcompiler.h"
#include "D2D1.h"
#include "D2D1Helper.h"
#include "DWrite.h"

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


using namespace std;
using namespace Microsoft::WRL;
using namespace D2D1;

//문자열 타입정의
typedef basic_string<TCHAR>     T_STR;
typedef basic_string<wchar_t>   W_STR;
typedef basic_string<char>      C_STR;
typedef vector<T_STR>		    T_STR_VECTOR;

//매크로
#define randf(x) (((float)x)*rand()/(float)RAND_MAX) //0~x사이의 랜덤한 실수값을 반환
#define randstep(fMin,fMax) (fMin+randf(fMax-fmin))  //min에서 max까지의 랜덤할 실수값을 반환
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;  //x값이 min보다 작으면 min으로, max보다 크면 max로 고정시킴.

#define SAFE_NEW(A, B)              { if (!A) A = new B; }                    //A가 널포인트이면 A에 B를 동적할당한다.
#define SAFE_DEL(A)                 { if (A) delete A; (A)=nullptr; }         //A가 널포인트가 아니면 A의 메모리를 해제하고, Nullptr로 설정한다.
#define SAFE_NEW_ARRAY(A, B, C)	    { if (!A && C>0) A = new B[C]; }          //A가 널포인트가 아니고 C가 1이상이면 A에 B를 C개의 배열로 동적할당한다.
#define SAFE_DELETE_ARRAY(A)		{ if (A) delete[] A; (A)=nullptr; }       //A가 널포인트가 아니면 A에 할당된 배열 메모리를 해제하고, nullptr로 설정한다.
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }   //A가 널포인터가 아니면 A를 릴리즈하고 nullptr로 설정한다.

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

