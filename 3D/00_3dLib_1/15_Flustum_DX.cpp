#include "15_Flustum_DX.h"

FlustumPlane::FlustumPlane()
{
	x = y = z = d = 0.0f;
}

void FlustumPlane::Create(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	D3DXVECTOR3 vEdge1 = v1 - v0;
	D3DXVECTOR3 vEdge2 = v2 - v0;
	D3DXVECTOR3 vNormal;
	D3DXVec3Cross(&vNormal, &vEdge1, &vEdge2);
	D3DXVec3Normalize(&vNormal, &vNormal);
	x = vNormal.x;
	y = vNormal.y;
	z = vNormal.z;
	d = -(v0.x*x + v0.y*y + v0.z*z);
}

void FlustumPlane::Create(D3DXVECTOR3 v0, D3DXVECTOR3 vNormal)
{
	D3DXVec3Normalize(&vNormal, &vNormal);
	x = vNormal.x;
	y = vNormal.y;
	z = vNormal.z;
	d = -(v0.x*x + v0.y*y + v0.z*z);
}

FlustumPlane::~FlustumPlane() { }

Flustum_DX::Flustum_DX()
{
	D3DXMatrixIdentity(&m_mWorld);
	D3DXMatrixIdentity(&m_mWorld);
	D3DXMatrixIdentity(&m_mWorld);
}

void Flustum_DX::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	if (pWorld != nullptr) {
		m_mWorld = *pWorld;
	}

	if (pView != nullptr) {
		m_mView = *pView;
	}

	if (pProj != nullptr) {
		m_mProj = *pProj;
	}
}

bool Flustum_DX::CreateFlustum()
{
	D3DXMATRIX matInvViewProj; // (m_mView * m_mProj)의 역행렬
	D3DXMatrixMultiply(&matInvViewProj, &m_mView, &m_mProj);
	D3DXMatrixInverse(&matInvViewProj, nullptr, &matInvViewProj);

	// near  far
	// 0 1	 4 5
	// 3 2	 7 6

	//near side
	m_vVertex[0] = { -1.f,  1.f, 0.f };
	m_vVertex[1] = {  1.f,  1.f, 0.f };
	m_vVertex[2] = {  1.f, -1.f, 0.f };
	m_vVertex[3] = { -1.f, -1.f, 0.f };

	//far side
	m_vVertex[4] = { -1.f,  1.f, 1.f };
	m_vVertex[5] = {  1.f,  1.f, 1.f };
	m_vVertex[6] = {  1.f, -1.f, 1.f };
	m_vVertex[7] = { -1.f, -1.f, 1.f };

	for (int i = 0; i < 8; i++) {
		D3DXVec3TransformCoord(&m_vVertex[i], &m_vVertex[i], &matInvViewProj);
	}

	// near 0 far 1 up 2 right 3 down 4 left 5
	m_Plane[0].Create(m_vVertex[0], m_vVertex[1], m_vVertex[2]);
	m_Plane[1].Create(m_vVertex[6], m_vVertex[5], m_vVertex[4]);
	m_Plane[2].Create(m_vVertex[4], m_vVertex[5], m_vVertex[1]);
	m_Plane[3].Create(m_vVertex[1], m_vVertex[5], m_vVertex[6]);
	m_Plane[4].Create(m_vVertex[3], m_vVertex[2], m_vVertex[6]);
	m_Plane[5].Create(m_vVertex[4], m_vVertex[0], m_vVertex[3]);
	
	return true;
}

bool Flustum_DX::ClassifyPoint(D3DXVECTOR3 v)
{
	for (int i = 0; i < 6; i++) {
		//평면과 한 점의 거리 ...?
		float fD = m_Plane[i].x * v.x + m_Plane[i].y * v.y + m_Plane[i].z * v.z + m_Plane[i].d;
		if (fD > 0.0f) {
			return false;
		}
	}
	return true;
}

bool Flustum_DX::ClassifySphere(D3DXVECTOR3 v, float fRadius)
{
	for (int i = 0; i < 6; i++) {
		//평면과 한 점의 거리 ...?
		float fD = m_Plane[i].x * v.x + m_Plane[i].y * v.y + m_Plane[i].z * v.z + m_Plane[i].d;
		if (fD > fRadius) {
			return false;
		}
	}
	return true;
}

Flustum_DX::~Flustum_DX() { }