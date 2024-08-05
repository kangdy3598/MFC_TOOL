#include "stdafx.h"
#include "MyUnit.h"
#include "Device.h"
#include "TextureMgr.h"
#include "AstarManager.h"
#include "TimeManager.h"

CMyUnit::CMyUnit()
{
}

CMyUnit::~CMyUnit()
{
    Release();
}

HRESULT CMyUnit::Initialize(void)
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	//m_wstrObjKey = L"Unit";
	//m_wstrStateKey = L"Dragoon";

	m_wstrObjKey = L"Unit";
	m_wstrStateKey = L"Dragoon";

	m_tFrame = { 0.f, 11.f };

	return S_OK;
}

int CMyUnit::Update(void)
{
	D3DXMATRIX	matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	Move_Astar();


	return 0;
}

void CMyUnit::Late_Update(void)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		CAstarManager::Get_Instance()->Start_Astar(m_tInfo.vPos, ::Get_Mouse() - CObj::m_vScroll);
	}

	CObj::Move_Frame();
}

void CMyUnit::Render(void)
{
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	//const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(),
	//	m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);


	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Unit", L"Dragoon", 1);

	float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	D3DXVECTOR3 center = D3DXVECTOR3(fCenterX, fCenterY, 0.f);
	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&center,
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMyUnit::Release(void)
{
}

void CMyUnit::Move_Astar()
{
	list<TILE*>& BestList = CAstarManager::Get_Instance()->GetBestList();

	if (!BestList.empty())
	{
		D3DXVECTOR3	vDir = BestList.front()->vPos - m_tInfo.vPos;

		float	fDistance = D3DXVec3Length(&vDir);

		D3DXVec3Normalize(&vDir, &vDir);

		m_tInfo.vPos += vDir * 300.f * CTimeManager::Get_Instance()->Get_TimeDelta();

		if (3.f >= fDistance)
			BestList.pop_front();
	}
}
