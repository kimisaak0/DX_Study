#include "sample.h"

namespace Lypi
{
	Sample::Sample(LPCTSTR LWndName) : zCore(LWndName)
	{

	}

	bool Sample::Init()
	{
		m_dxobj.CreateFullImgObj({ 0,0,1500,750 }, L"../../INPUT/DATA/image/skybox_front.JPG");

		return true;
	}

	bool Sample::Frame()
	{
		return true;
	}

	bool Sample::Render()
	{
		m_dxobj.Render();
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