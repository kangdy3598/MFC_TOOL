#include "stdafx.h"
#include "Building.h"

#include "Device.h"
#include "TextureMgr.h"
#include "ToolView.h"

CBuilding::CBuilding()
	: m_ToolView()

{
	m_vecTile.reserve(TILEX * TILEY);
}


CBuilding::~CBuilding()
{
	Release();
}

void CBuilding::Check_Picking(CPoint _mousePosition, CTileTool* _CTileTool)
{

}

HRESULT CBuilding::Initialize()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../Texture/MultiTexture/Build/Protoss/GateWay/0.png",
		TEX_MULTI, L"Building", L"Building", MAX_TILETYPE)))
	{
		AfxMessageBox(L"Building Texture Failed");
		return E_FAIL;
	}

	vPos.x = 200;
	vPos.y = 200;
	return S_OK;
}

void CBuilding::Update()
{

}

void CBuilding::Render()
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR	szBuf[MIN_STR] = L"";

	//for (auto pTile : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			vPos.x - m_ToolView->GetScrollPos(0),
			vPos.y - m_ToolView->GetScrollPos(1), 0.f);

		matWorld = matScale * matTrans;

		RECT	rc{};

		// GetClientRect : 클라이언트 영역에 해당하는 RECT 정보를 얻어오는 함수
		GetClientRect(m_ToolView->m_hWnd, &rc);

		float	fRatioX = WINCX / float(rc.right - rc.left);
		float	fRatioY = WINCY / float(rc.bottom - rc.top);

		Set_Ratio(&matWorld, fRatioX, fRatioY);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo =
			CTextureMgr::Get_Instance()->Get_Texture(L"Building", L"Building", 0);

		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, 
			D3DCOLOR_ARGB(255, 255, 255, 255));

	}

}

void CBuilding::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	m_vecTile.clear();
}

void CBuilding::MouseMove()
{
	D3DXVECTOR3 pt = Get_Mouse();
	vPos.x = pt.x;
	vPos.y += pt.y;
	
}

void CBuilding::Set_Ratio(D3DXMATRIX* pOut, float fX, float fY)
{
	pOut->_11 *= fX;
	pOut->_21 *= fX;
	pOut->_31 *= fX;
	pOut->_41 *= fX;

	pOut->_12 *= fY;
	pOut->_22 *= fY;
	pOut->_32 *= fY;
	pOut->_42 *= fY;
}
