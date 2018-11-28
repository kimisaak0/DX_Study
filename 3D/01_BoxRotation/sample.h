#pragma once
#pragma comment(lib, "lib_1.lib")

#include "03_coreC_DX.h"

class Sample : public coreC_DX
{
	Box_Shape      m_ObjBox;
	Plane_Shape    m_ObjPlane;
	Line_Shape     m_ObjLine;
	Box_Shape      m_ObjSphere;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	Sample(LPCTSTR LWndName);
	virtual ~Sample();
};				   