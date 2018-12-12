#pragma once
#pragma comment(lib, "TLib.lib")

#include "zCore.h"

namespace Lypi
{
	class Sample : public zCore
	{
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