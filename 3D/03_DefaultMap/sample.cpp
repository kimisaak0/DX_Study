#include "sample.h"

Sample::Sample(LPCTSTR LWndName) : coreC_DX(LWndName) { }

bool Sample::Init()
{
	D3DXMatrixIdentity(&m_World);
	m_World._43 = 10;

	SetMainCamera(1);
	m_pMainCamera->SetViewMatrix({ 0.0f, 10.0f, -10.0f }, { 0.0f, 0.0f, 0.0f });

	m_ObjBox.Create(L"../../INPUT/DATA/shader/vs.hlsl", L"../../INPUT/DATA/shader/ps.hlsl", L"../../INPUT/DATA/shader/gs.hlsl", L"../../INPUT/DATA/image/lightmap.bmp");
	m_ObjSphere.Create(L"../../INPUT/DATA/shader/vs.hlsl", L"../../INPUT/DATA/shader/ps.hlsl", L"../../INPUT/DATA/shader/gs.hlsl", L"../../INPUT/DATA/image/lightmap.bmp");

	m_ObjBox.ChangePSFunction(L"../../INPUT/DATA/shader/ps.hlsl", "PS");
	m_ObjSphere.ChangePSFunction(L"../../INPUT/DATA/shader/ps.hlsl", "PS");

	return true;
}
bool Sample::Frame()
{
	m_ObjBox.Frame();
	m_ObjSphere.Frame();

	return true;
}

bool Sample::Render()
{
	D3DXMATRIX matWorld;

	//박스 출력
	D3DXVECTOR3 vPos;
	vPos.x = m_World._41;
	vPos.y = m_World._42;
	vPos.z = m_World._43;

	m_World = m_pMainCamera->m_matWorld;

	m_World._41 = vPos.x;
	m_World._42 = vPos.y;
	m_World._43 = vPos.z;

	if (m_pMainCamera->ClassifySphere(vPos, 1.44f)) {
		m_ObjBox.SetMatrix(&m_World, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		m_ObjBox.Render();
	}

	//구 출력
	D3DXMatrixTranslation(&matWorld, -3.0f, 0, 0);
	m_ObjSphere.SetMatrix(&matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_ObjSphere.Render();

	return true;
}

bool Sample::Release()
{
	m_ObjSphere.Release();
	m_ObjBox.Release();

	return true;
}


Sample::~Sample() { }