#pragma once
#pragma warning(disable : 4005)



//DX11�� ������ �ʿ���
#pragma comment (lib, "D3D11.lib")
#include "D3D11.h"

//DXGIFactory�� ����µ� ����.
#pragma comment (lib, "DXGI.lib")
#include "DXGI.h"

//���̷�Ʈ 2D���
#pragma comment (lib, "d2d1.lib")
#include "D2D1.h"
#include "D2D1Helper.h"

//���̷�Ʈ ����Ʈ ���
#pragma comment (lib, "dwrite.lib")
#include "DWrite.h"

//���̷�Ʈ ��ǲ ���.
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#include "dinput.h"


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



//�������� �ڵ� ���
//#pragma comment (lib, "WindowsCodecs.lib")
//#include <wincodec.h>

//STL ���
#include <vector>
#include <map>
#include <list>
#include <set>

#include <bitset>
#include <algorithm>
#include <functional>

#include <math.h>

using namespace std;
using namespace D2D1;

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

//DX �޼ҵ� ȣ�⿡ ���� ��ȯ�� ó�� ��ũ��

#ifndef V
#define V(x)       { hr = (x); }
#endif

#ifndef V_FRETURN
  #define V_FRETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; } }
#endif


//////////////////////////////////////////////
// ��ü �� �迭 �Ҵ�� ���� �� �Ҹ� ��ũ��
//////////////////////////////////////////////
#ifndef SAFE_ZERO
#define SAFE_ZERO(A)				   { A = 0; }
#endif

#ifndef SAFE_NEW
#define SAFE_NEW(A, B)			   { if (!A) A = new B; }
#endif 

#ifndef SAFE_DEL
#define SAFE_DEL(A)				   { if (A) delete A; (A)=NULL; }
#endif 

#ifndef SAFE_NEW_ARRAY
#define SAFE_NEW_ARRAY(A, B, C)	   { if (!A && C) A = new B[C]; }
#endif 

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(A)	       { if (A) delete [] A; (A)=NULL; }
#endif 

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(A)		       { if(A) { (A)->Release(); (A)=NULL; } }
#endif 

#ifndef SAFE_NEW_CLEAR
#define SAFE_NEW_CLEAR( A, B )      { if (!A) A = new B; if(A) memset( A, 0, sizeof(B) ); };
#endif 

#ifndef SAFE_NEW_ARRAY_CLEAR
#define NEW_ARRAY_CLEAR( A, B, C )  { if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
#endif


//--------�ܺ� ���� ���� ����----------//



//WndC_DX
extern HINSTANCE g_hInst;
extern HWND      g_hWnd;           //������ �������� �ڵ鰪 (DC�� �޾ƿ� �� �����)
extern RECT      g_rtWindow;       //������ ������ ��ü���� ũ��
extern RECT      g_rtClient;       //������ ������ �۾����� ũ��
extern UINT      g_uClientWidth;
extern UINT      g_uClientHeight;


//Ÿ�̸ӿ���
extern double g_GameTimer;