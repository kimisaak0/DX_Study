#pragma once
#pragma comment(lib, "TLib.lib")

#include "zCore.h"

#include "BGTexture.h"
#include "Texture.h"
#include "Object.h"

namespace Lypi
{

	struct SimpleVertex
	{
		float x, y, z;
		float u, v;
	};

	class Sample : public zCore
	{
		
		BGTexture bg;
		Texture T1;

		Object_DX  m_Hero;

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
