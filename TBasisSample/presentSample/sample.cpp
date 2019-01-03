#include "sample.h"

namespace Lypi
{
	Sample::Sample(LPCTSTR LWndName) : zCore(LWndName)
	{

	}

	bool Sample::Init()
	{
		bg.LoadTexture(L"../../INPUT/DATA/image/desert.jpg");
		bg.Init();
		//T1.LoadTexture(L"../../INPUT/DATA/image/Koala.jpg");
		//T1.Init();

		m_Hero.CreateFullImgObj({ 0,0,100,100 }, L"../../INPUT/DATA/image/Koala.jpg");
		m_Hero.Init();
		return true;
	}

	bool Sample::Frame()
	{
		m_Hero.Frame();
		//T1.Frame();
		return true;
	}

	bool Sample::Render()
	{
		m_Hero.Render();
		bg.Render();
		//T1.Render();
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