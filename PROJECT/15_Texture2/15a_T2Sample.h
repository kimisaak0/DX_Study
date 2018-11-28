#pragma once
#include "15_Texture2.h"

struct SimpleVertex
{
	float x, y, z;
	float u, v;
};

class T2Sample : public coreC_DX
{
public:
	Texture2 m_dxObj;

public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
};