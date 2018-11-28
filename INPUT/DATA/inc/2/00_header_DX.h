#pragma once
#pragma warning(disable : 4005)

#define DIRECTINPUT_VERSION  0x0800

#pragma region //��� �� lib ����

//STL ���
#include <vector>
#include <map>
#include <list>
#include <set>

#include <bitset>
#include <algorithm>
#include <functional>

#include <math.h>

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

//���̴� ���
#pragma comment(lib, "d3dx11.lib")
#include "D3DX11.h"

#pragma comment(lib, "d3dcompiler.lib")
#include "D3Dcompiler.h"

//math
#pragma comment(lib, "d3dx10d.lib")
#include "D3DX10math.h"

//����ó���� ���� ���
#include <assert.h>

//�����ڵ� ó���� ���� �κ�
#include <string>
using std::string;

#include <tchar.h>

//comptr
#include <wrl.h>

//�������� �ڵ� ���
//#pragma comment (lib, "WindowsCodecs.lib")
//#include <wincodec.h>

#pragma endregion

#pragma region //namespace ���
using namespace std;
using namespace D2D1;
using namespace Microsoft;
using namespace WRL;
#pragma endregion

#pragma region //Ÿ�� ����
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

using C_STR = basic_string<char>;
using W_STR = basic_string<wchar_t>;
using T_STR = basic_string<TCHAR>;

using C_ITOR = basic_string<char>::iterator;
using W_ITOR = basic_string<wchar_t>::iterator;
using T_ITOR = basic_string<TCHAR>::iterator;

#pragma endregion

#pragma region //��ũ�� ����

#ifndef V
#define V(x)       { hr = (x); }
#endif

#ifndef V_FRETURN
#define V_FRETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; } }
#endif

#ifndef V_RF
#define V_RF(x){ hr = (x); if( hr != S_OK ) { return false; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)		       { if(x) { (x)->Release(); (x)=NULL; } }
#endif 

#define  ClinetRatio    ( ((float)g_rtClient.right) / ((float)g_rtClient.bottom) )

#pragma endregion

#pragma region //�ܺ� ���� ����

class wndC_DX;

//device_DX
extern ID3D11Device*              g_pD3dDevice;
extern ID3D11DeviceContext*       g_pD3dContext;
extern IDXGISwapChain*            g_pSwapChain;

//WndC_DX
extern HINSTANCE g_hInst;
extern HWND      g_hWnd;
extern RECT      g_rtWindow;
extern RECT      g_rtClient;
extern wndC_DX*  g_pWindow;

extern RECT checkW;
extern RECT checkC;

//Timer
extern float g_dSPF;

#pragma endregion

