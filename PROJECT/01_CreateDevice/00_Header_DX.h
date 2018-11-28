#pragma once
#pragma warning(disable : 4005)

//DX11 사용
#pragma comment (lib, "d3d11.lib")
#include <d3d11.h> // d3dx11에서 호출함.

//DXGIFactory를 만들기 위해서 필요함
#pragma comment (lib, "dxgi.lib")  
#include <DXGI.h> 

//에러처리를 위한 헤더
#include <assert.h>

//유니코드 처리를 위한 부분
#include <string>
using std::string;

#include <tchar.h>
using C_STR = std::basic_string<char>;
using W_STR = std::basic_string<wchar_t> ;
using T_STR = std::basic_string<TCHAR> ;

//매크로 정리
#ifndef _EMPTY
  #define _EMPTY             { return true; }
#endif

#ifndef _FURE
  #define _FURE              = 0;
#endif

#ifndef V_FRETURN
  #define V_FRETURN(x)       { hr = (x); if( FAILED(hr) ) { return hr; } }
#endif

#ifndef SAFE_RELEASE
  #define SAFE_RELEASE(A)	 { if(A) { (A)->Release(); (A)=NULL; } }
#endif 

//--------외부 변수 정의 영역----------//
//deviceC_DX


//WndC_DX
extern HINSTANCE g_hInst;
extern HWND      g_hWnd;      //생성된 윈도우의 핸들값 (DC를 받아올 때 사용함)
extern RECT      g_rtWindow;  //생성된 윈도우 전체영역 크기
extern RECT      g_rtClient;  //생성된 윈도우 작업영역 크기
extern UINT      g_uClientWidth;
extern UINT      g_uClientHegiht;

