#pragma once
#pragma comment(lib, "TLib.lib")

#include "zCore.h"

#include "BGTexture.h"
#include "Texture1.h"

namespace Lypi
{
	class Sample : public zCore
	{
		
		BGTexture bg;
		Texture1 T1;

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
