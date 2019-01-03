#pragma once
#pragma comment(lib, "TLib.lib")

#include "zCore.h"

#include "BGTexture.h"
#include "Texture.h"
#include "Object.h"

namespace Lypi
{
	class Sample : public zCore
	{
		
		BGTexture bg;
		Texture T1;

		Object  m_Hero;

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
