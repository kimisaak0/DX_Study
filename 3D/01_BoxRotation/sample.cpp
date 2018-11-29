#include "sample.h"

Sample::Sample(LPCTSTR LWndName) : coreC_DX(LWndName) { }

bool Sample::Init()
{
	SetMainCamera(1);

	m_ObjLine.Create  (L"../../INPUT/DATA/shader/vs.hlsl", L"../../INPUT/DATA/shader/ps.hlsl", L"../../INPUT/DATA/shader/gs.hlsl", L"NULL");
	m_ObjPlane.Create (L"../../INPUT/DATA/shader/vs.hlsl", L"../../INPUT/DATA/shader/ps.hlsl", L"../../INPUT/DATA/shader/gs.hlsl", L"../../INPUT/DATA/image/box_uv_check.png");
	m_ObjBox.Create   (L"../../INPUT/DATA/shader/vs.hlsl", L"../../INPUT/DATA/shader/ps.hlsl", L"../../INPUT/DATA/shader/gs.hlsl", L"../../INPUT/DATA/image/box_uv_check.png");
	m_ObjSphere.Create(L"../../INPUT/DATA/shader/vs.hlsl", L"../../INPUT/DATA/shader/ps.hlsl", L"../../INPUT/DATA/shader/gs.hlsl", L"../../INPUT/DATA/image/box_uv_check.png");

	return true;
}
bool Sample::Frame()
{
	m_ObjLine.Frame();
	m_ObjPlane.Frame();
	m_ObjBox.Frame();
	m_ObjSphere.Frame();

	return true;
}

bool Sample::Render()
{
	D3DXMATRIX matWorld, matRot;

	//면 출력
	D3DXMatrixTranslation(&matWorld, 3.0f, 0, 0);
	D3DXMatrixRotationY(&matRot, m_GameTimer.getGameTime());
	matWorld = matWorld * matRot;
	m_ObjPlane.SetMatrix(&matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_ObjPlane.Render();

	//구 출력
	D3DXMatrixTranslation(&matWorld, -3.0f, 0, 0);
	m_ObjSphere.SetMatrix(&matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_ObjSphere.Render();

	//박스 출력
	m_ObjBox.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_ObjBox.Render();

	//박스와 면의 연결선 출력
	m_ObjLine.Draw(m_ObjBox.m_vPosition, m_ObjPlane.m_vPosition, { 1.0f, 1.0f, 0.0f, 1.0f });


	//면 방향벡터 출력
	D3DXVECTOR3 vDir;
	m_ObjLine.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	vDir = m_ObjPlane.m_vLook * 10.0f;
	m_ObjLine.Draw(m_ObjPlane.m_vPosition, m_ObjPlane.m_vPosition + vDir, { 1.0f, 0.0f, 0.0f, 1.0f });

	vDir = m_ObjPlane.m_vUp * 10.0f;
	m_ObjLine.Draw(m_ObjPlane.m_vPosition, m_ObjPlane.m_vPosition + vDir, { 0.0f, 1.0f, 0.0f, 1.0f });

	vDir = m_ObjPlane.m_vSide * 10.0f;
	m_ObjLine.Draw(m_ObjPlane.m_vPosition, m_ObjPlane.m_vPosition + vDir, { 0.0f, 0.0f, 1.0f, 1.0f });


	return true;
}

bool Sample::Release()
{
	m_ObjLine.Release();
	m_ObjSphere.Release();
	m_ObjPlane.Release();
	m_ObjBox.Release();

	return true;
}


Sample::~Sample() { }