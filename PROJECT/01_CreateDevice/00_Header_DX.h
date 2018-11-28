#pragma once
#pragma warning(disable : 4005)

//DX11 ���
#pragma comment (lib, "d3d11.lib")
#include <d3d11.h> // d3dx11���� ȣ����.

//DXGIFactory�� ����� ���ؼ� �ʿ���
#pragma comment (lib, "dxgi.lib")  
#include <DXGI.h> 

//����ó���� ���� ���
#include <assert.h>

//�����ڵ� ó���� ���� �κ�
#include <string>
using std::string;

#include <tchar.h>
using C_STR = std::basic_string<char>;
using W_STR = std::basic_string<wchar_t> ;
using T_STR = std::basic_string<TCHAR> ;

//��ũ�� ����
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

//--------�ܺ� ���� ���� ����----------//
//deviceC_DX


//WndC_DX
extern HINSTANCE g_hInst;
extern HWND      g_hWnd;      //������ �������� �ڵ鰪 (DC�� �޾ƿ� �� �����)
extern RECT      g_rtWindow;  //������ ������ ��ü���� ũ��
extern RECT      g_rtClient;  //������ ������ �۾����� ũ��
extern UINT      g_uClientWidth;
extern UINT      g_uClientHegiht;

