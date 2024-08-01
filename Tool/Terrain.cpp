#include "stdafx.h"
#include "Terrain.h"

#include "Device.h"
#include "TextureMgr.h"
#include "ToolView.h"
#include "MiniView.h"



CTerrain::CTerrain()
	: m_ToolView()
	, m_MiniView()

{
	m_vecTile.reserve(TILEX * TILEY);
}


CTerrain::~CTerrain()
{
	Release();
}

void CTerrain::Check_Picking(CPoint _mousePosition, CTileTool* _CTileTool)
{
	float fA = (float)TILECY / (float)TILECX;

	float X = 0, Y = 0;
	for (auto pTile : m_vecTile)
	{
		// 1, 3
		if (pTile->vPos.x - TILECX / 2.f <= _mousePosition.x &&
			_mousePosition.x <= pTile->vPos.x)
		{
			X = fA * (_mousePosition.x - pTile->vPos.x);
			X += TILECY / 2.f;

			if (-X + pTile->vPos.y <= _mousePosition.y &&
				_mousePosition.y <= X + pTile->vPos.y)
			{
				pTile->SetDrawID(
					_CTileTool->m_iTileNum
				);
				return;
			}

		}
		
		// 2, 4
		else if (pTile->vPos.x <= _mousePosition.x &&
			_mousePosition.x <= pTile->vPos.x + TILECX / 2.f)
		{
			X = fA * (_mousePosition.x - pTile->vPos.x);
			X -= TILECY / 2;

			if (X + pTile->vPos.y <= _mousePosition.y &&
				_mousePosition.y <= -X + pTile->vPos.y)
			{
				pTile->SetDrawID(
					_CTileTool->m_iTileNum
				);
				return;
			}
		}
	}
}

HRESULT CTerrain::Initialize()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../Texture/Stage/Terrain/Tile/Tile%d.png",
		TEX_MULTI, L"Terrain", L"Tile", MAX_TILETYPE)))
	{
		AfxMessageBox(L"Tile Texture Failed");
		return E_FAIL;
	}

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			TILE*	pTile = new TILE;

			float	fX = (TILECX * j) + (i % 2) * (TILECX / 2.f);
			float	fY = (TILECY / 2.f) * i;

			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { (float)TILECX, (float)TILECY };
			pTile->byOption = 0;
			pTile->byDrawID = 3;

			m_vecTile.push_back(pTile);
		}
	}

	return S_OK;
}

void CTerrain::Update()
{
}

void CTerrain::Render(int _type)
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR	szBuf[MIN_STR] = L"";
	int		iIndex(0);

	for (auto pTile : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			pTile->vPos.x - m_ToolView->GetScrollPos(0),
			pTile->vPos.y - m_ToolView->GetScrollPos(1), 0.f);

		matWorld = matScale * matTrans;

		RECT	rc{};

		// GetClientRect : 클라이언트 영역에 해당하는 RECT 정보를 얻어오는 함수
		GetClientRect(m_ToolView->m_hWnd, &rc);

		float	fRatioX = WINCX / float(rc.right - rc.left);
		float	fRatioY = WINCY / float(rc.bottom - rc.top);

		if (_type == 1)
		{
			fRatioX = 300 / float(rc.right - rc.left);
			fRatioY = 300 / float(rc.bottom - rc.top);
		}
		Set_Ratio(&matWorld, fRatioX, fRatioY);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(
			L"Terrain", L"Tile", pTile->byDrawID);

		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr, // 출력할 이미지 영역의 RECT 주소, NULL인 경우 0, 0 기준으로 출력
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), // 출력할 이미지의 중심 좌표, VEC3주소, NULL 인 경우 0, 0이 중심 좌표
			nullptr, // 텍스처를 출력할 위치 좌표, VEC3주소, 스크린상 0, 0 좌표에 출력
			D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 0xffffffff를 넘겨주면 원본색 유지


		//////////////타일 인덱스 출력//////////////////

		
		//swprintf_s(szBuf, L"%f", pTile->vPos.y);

		//D3DXMATRIX	matTrans2;
		//D3DXMatrixTranslation(&matTrans2, pTile->vPos.x, pTile->vPos.y, 0.f);
		//CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matTrans2);

		//swprintf_s(szBuf, L"%d", iIndex);
		//CDevice::Get_Instance()->Get_Font()->DrawTextW(
		// CDevice::Get_Instance()->Get_Sprite(),
		// szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		//

		/*swprintf_s(szBuf, L"X : %f, Y : %f", Get_Mouse().x,
			Get_Mouse().y + GetScrollPos(g_hWnd, SB_VERT));

		D3DXMATRIX	matTrans2;
		D3DXMatrixTranslation(&matTrans2, 100.f, 100.f, 0.f);
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matTrans2);
		CDevice::Get_Instance()->Get_Font()->DrawTextW(
			CDevice::Get_Instance()->Get_Sprite(),
			szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));*/

			

		/*if (Check_Peeking(pTile->vPos.x, pTile->vPos.y))
			pTile->SetDrawID();*/

		++iIndex;
	}
	
}

void CTerrain::MiniRender()
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	int		iIndex(0);
	for (auto pTile : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,pTile->vPos.x,pTile->vPos.y, 0.f);

		matWorld = matScale * matTrans;

		RECT	rc{};

		GetClientRect(m_ToolView->m_hWnd, &rc);

		float	fRatioX = 300 / float(rc.right - rc.left);
		float	fRatioY = 300 / float(rc.bottom - rc.top);

		Set_Ratio(&matWorld, fRatioX, fRatioY);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(
			L"Terrain", L"Tile", pTile->byDrawID);

		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		++iIndex;
	}

}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	m_vecTile.clear();
}

void CTerrain::Set_Ratio(D3DXMATRIX* pOut, float fX, float fY)
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
