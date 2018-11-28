#include "13b_ActorDX.h"

ActorDX::ActorDX()
{
}

bool ActorDX::Init()
{
	return true;
}

bool ActorDX::Frame(float fGameTimer, float fFps)
{
	return true;
}

bool ActorDX::PreRender(ID3D11DeviceContext* pContext)
{
	m_dxObj.PreRender(pContext);
	return true;
}

bool ActorDX::Render(ID3D11DeviceContext* pContext)
{
	m_dxObj.Render(pContext);
	return true;
}

bool ActorDX::PostRender(ID3D11DeviceContext* pContext)
{
	m_dxObj.PostRender(pContext);
	return true;
}

bool ActorDX::Release()
{
	m_dxObj.Release();
	return true;
}


ActorDX::~ActorDX()
{
}