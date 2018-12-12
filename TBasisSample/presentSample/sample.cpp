#include "sample.h"

namespace Lypi
{
	Sample::Sample(LPCTSTR LWndName) : zCore(LWndName) { }

	bool Sample::Init()
	{
		return true;
	}
	bool Sample::Frame()
	{
		return true;
	}

	bool Sample::Render()
	{
		return true;
	}

	bool Sample::Release()
	{
		return true;
	}


	Sample::~Sample() { }

}