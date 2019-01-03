#include "sample.h"

namespace Lypi
{
	Sample::Sample(LPCTSTR LWndName) : zCore(LWndName)
	{

	}

	bool Sample::Init()
	{
		bg.LoadTexture(L"../../INPUT/DATA/image/desert.jpg");
		T1.LoadTexture(L"../../INPUT/DATA/image/Koala.jpg");
		return true;
	}

	bool Sample::Frame()
	{
		T1.Frame();
		return true;
	}

	bool Sample::Render()
	{
		bg.Render();
		T1.Render();
		return true;
	}


	bool Sample::Release()
	{
		return true;
	}

	Sample::~Sample(void)
	{
	}
}