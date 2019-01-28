#pragma once
#pragma comment(lib, "TLib.lib")

#include "zCore.h"

#include "pOBJ.h"

namespace Lypi
{
	class Sample : public zCore
	{
		Object_DX  m_dxobj;

	public:
		bool Init();
		bool Frame();
		bool Render();
		bool Release();

	public:
		Sample(LPCTSTR LWndName);
		virtual ~Sample();
	};
}
