#include "sample.h"

namespace Lypi
{
	Sample::Sample(LPCTSTR LWndName) : zCore(LWndName)
	{

	}

	bool Sample::Init()
	{

		PC_VERTEX vertices[] =
		{
			{ float3(-0.0f, +0.7f, 0.5f), float4(1.f,1.f,1.f,1.f) },
			{ float3(+0.5f, -0.2f, 0.5f), float4(1.f,1.f,1.f,1.f) },
			{ float3(-0.5f, -0.2f, 0.5f), float4(1.f,1.f,1.f,1.f) },
		};

		PC_VERTEX vertices2[] =
		{
			{ float3(-1.0f, -1.0f, 0.5f), float4(1.f,1.f,1.f,1.f) },
			{ float3(-0.5f, -0.5f, 0.5f), float4(1.f,1.f,1.f,1.f) },
			{ float3(-0.5f, -1.0f, 0.5f), float4(1.f,1.f,1.f,1.f) },
		};

		DWORD indices[] =
		{
			0,1,2,
			//0,2,3,
		};

		m_sShape.Init(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
		m_sShape2.Init(vertices2, sizeof(vertices2) / sizeof(vertices2[0]), indices, sizeof(indices) / sizeof(indices[0]));

		return true;
	}

	bool Sample::Frame()
	{
		m_sShape.Frame();
		m_sShape2.Frame();

		return true;
	}

	bool Sample::Render()
	{
		m_sShape.Render();
		m_sShape2.Render();
	
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