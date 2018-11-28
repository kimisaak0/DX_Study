#pragma once
#pragma warning(disable : 4005)

////DX����
#pragma comment (lib, "d3d11.lib")
#include <d3d11.h>

//DXGIFactory�� ����µ� ����.
#pragma comment (lib, "dxgi.lib")
#include <dxgi.h> 

//����ó���� ���� ���
#include <assert.h>

//�����ڵ� ó���� ���� �κ�
#include <string>
using std::string;

#include <tchar.h>
using C_STR = std::basic_string<char>;
using W_STR = std::basic_string<wchar_t>;
using T_STR = std::basic_string<TCHAR>;

using T_ITOR = std::basic_string<TCHAR>::iterator;


//STL ���
#include <vector>
#include <map>
#include <list>
#include <set>

#include <bitset>
#include <algorithm>
#include <functional>
using namespace std;


//Ÿ�� ����
using T_STR_VECTOR = vector<basic_string<TCHAR>>;
using C_STR_VECTOR = vector<string>;

using DWORD_VECTOR = vector<DWORD>;
using DWORD_VECTOR_ITOR = vector<DWORD>::iterator;

using T_STR_LIST = list<basic_string<TCHAR>>;
using CHAR_STRING = string;

using DWORD_LIST = list<DWORD>;
using DWORD_LIST_ITOR = list<DWORD>::iterator;

using HANDLE_LIST = list<HANDLE>;
using HANDLE_LIST_ITOR = list<HANDLE>::iterator;


//��ũ�� ����
#ifndef _EMPTY
  #define _EMPTY                       { return true; }
#endif				            
#ifndef _FURE		            
  #define _FURE                        = 0;
#endif

#ifndef V_FRETURN
  #define V_FRETURN(x)                 { hr = (x); if( FAILED(hr) ) { return hr; } }
#endif

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


//--------�ܺ� ���� ���� ����----------//
//WndC_DX
extern HINSTANCE g_hInst;
extern HWND      g_hWnd;      //������ �������� �ڵ鰪 (DC�� �޾ƿ� �� �����)
extern RECT      g_rtWindow;  //������ ������ ��ü���� ũ��
extern RECT      g_rtClient;  //������ ������ �۾����� ũ��
extern UINT      g_uClientWidth;
extern UINT      g_uClientHegiht;

