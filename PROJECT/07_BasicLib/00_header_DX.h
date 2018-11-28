#pragma once
#pragma warning(disable : 4005)

#define DIRECTINPUT_VERSION  0x0800

//STL ���
#include <vector>
#include <map>
#include <list>
#include <set>

#include <bitset>
#include <algorithm>
#include <functional>

#include <math.h>


#pragma region //��� �� lib ����

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

//���̴��� ��밡
#pragma comment(lib, "d3dx11.lib")
#include "D3DX11.h"

#pragma comment(lib, "d3dcompiler.lib")
#include "D3Dcompiler.h"

//math
#include "D3DX10math.h"

//����ó���� ���� ���
#include <assert.h>

//�����ڵ� ó���� ���� �κ�
#include <string>
using std::string;

#include <tchar.h>



//�������� �ڵ� ���
//#pragma comment (lib, "WindowsCodecs.lib")
//#include <wincodec.h>


using namespace std;
using namespace D2D1;

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

//core
extern float g_dSPF;

#pragma endregion

#pragma region //������ ����
enum direction
{
	d_NO = 0,
	d_LEFT = 1,
	d_TOP = 2,
	d_RIGHT = 3,
	d_BOTTOM = 4,
};

enum push
{
	p_FREE = 0,
	p_DOWN = 1,
	p_HOLD = 2,
	p_UP = 3,
};

#pragma endregion

#pragma region //����ü ����
struct PCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;

	PCT_VERTEX() {}

	PCT_VERTEX(D3DXVECTOR3 vp, D3DXVECTOR4 vc, D3DXVECTOR2 vt)
	{
		p = vp;
		c = vc;
		t = vt;
	}

	bool operator==  (const PCT_VERTEX& Vertex)
	{
		if (p == Vertex.p && c == Vertex.c && t == Vertex.t) {
			return true;
		}
		else {
			return false;
		}
	}
};

struct uWH
{
	UINT width;
	UINT Height;
};

struct uPOINT
{
	UINT x;
	UINT y;

	uPOINT& operator= (const POINT& pt) {
		x = pt.x;
		y = pt.y;

		return *this;
	}
};

struct fLTRB
{
	float left;
	float top;
	float right;
	float bottom;
};

struct iXYWH
{
	LONG ltx;
	LONG lty;
	UINT width;
	UINT height;
};

struct iLTRB
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;

	iLTRB& operator= (const iXYWH& _xywh) {
		left = _xywh.ltx;
		top = _xywh.lty;
		right = _xywh.ltx + _xywh.width;
		bottom = _xywh.lty + _xywh.height;

		return *this;
	}
};

struct circle
{
	POINT pCenter;
	double dRadius;
};

struct ClsInfo
{
	bool bDoCls;
	direction drClsSrc;
	direction drClsDest;
	POINT ptInLength;
};

struct MouseInfo
{
	POINT xy;

	push left;
	push right;
	push middle;
};

#pragma endregion

#define  stpX(x)	((x) / ((float)g_rtClient.right))
#define  stpY(y)    -((y) / ((float)g_rtClient.bottom))