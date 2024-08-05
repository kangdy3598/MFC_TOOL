#include "stdafx.h"
#include "Unit.h"

#include "Device.h"
#include "TextureMgr.h"
#include "ToolView.h"
#include "MiniView.h"

CUnit::CUnit()
	: m_ToolView()
	, m_MiniView()

{
	m_vecUnit.reserve(TILEX * TILEY);
}


CUnit::~CUnit()
{
	Release();
}

HRESULT CUnit::Initialize()
{
	return S_OK;
}

void CUnit::Update()
{
	
}

void CUnit::Render()
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR	szBuf[MIN_STR] = L"";
	for (auto pTile : m_vecUnit)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			pTile->vPos.x - m_ToolView->GetScrollPos(0),
			pTile->vPos.y - m_ToolView->GetScrollPos(1), 0.f);

		matWorld = matScale * matTrans;

		RECT	rc{};

		// GetClientRect : Ŭ���̾�Ʈ ������ �ش��ϴ� RECT ������ ������ �Լ�
		GetClientRect(m_ToolView->m_hWnd, &rc);

		float	fRatioX = WINCX / float(rc.right - rc.left);
		float	fRatioY = WINCY / float(rc.bottom - rc.top);

		Set_Ratio(&matWorld, fRatioX, fRatioY);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

<<<<<<< HEAD
		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Unit", L"Dragoon", 8);
=======
		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(
			L"Unit", pTile->strKeyName, 0);
>>>>>>> origin/main
		//const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), 0);

		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr, // ����� �̹��� ������ RECT �ּ�, NULL�� ��� 0, 0 �������� ���
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), // ����� �̹����� �߽� ��ǥ, VEC3�ּ�, NULL �� ��� 0, 0�� �߽� ��ǥ
			nullptr, // �ؽ�ó�� ����� ��ġ ��ǥ, VEC3�ּ�, ��ũ���� 0, 0 ��ǥ�� ���
			D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ����, 0xffffffff�� �Ѱ��ָ� ������ ����
	}

}

void CUnit::MiniRender()
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	int		iIndex(0);
	for (auto pTile : m_vecUnit)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, 0.f);

		matWorld = matScale * matTrans;

		RECT	rc{};

		GetClientRect(m_ToolView->m_hWnd, &rc);

		float	fRatioX = 300 / float(rc.right - rc.left);
		float	fRatioY = 300 / float(rc.bottom - rc.top);

		Set_Ratio(&matWorld, fRatioX, fRatioY);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(
			L"Unit", L"Dragoon", 1);

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

void CUnit::PreviewRender()
{
	D3DXVECTOR3 pos = Get_Mouse();
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR	szBuf[MIN_STR] = L"";

	//for (auto pTile : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			pos.x,
			pos.y, 0.f);

		matWorld = matScale * matTrans;

		RECT	rc{};

		// GetClientRect : Ŭ���̾�Ʈ ������ �ش��ϴ� RECT ������ ������ �Լ�
		GetClientRect(m_ToolView->m_hWnd, &rc);

		float	fRatioX = WINCX / float(rc.right - rc.left);
		float	fRatioY = WINCY / float(rc.bottom - rc.top);

		Set_Ratio(&matWorld, fRatioX, fRatioY);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo =
			CTextureMgr::Get_Instance()->Get_Texture(
				L"Unit", m_strNowUnitName,
				0);

		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->Draw(
			pTexInfo->pTexture,
			nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr,
			D3DCOLOR_ARGB(128, 255, 255, 255));

	}
}

void CUnit::InstallUnit()
{
	D3DXVECTOR3 pos = Get_Mouse();
	//for (int i = 0; i < TILEY; ++i)
	{
		//for (int j = 0; j < TILEX; ++j)
		{
			UNITDATA* pUnit = new UNITDATA;

			const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(
				L"Unit", m_strNowUnitName);

			float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
			float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

			pUnit->vPos = { pos.x, pos.y, 0.f };
			pUnit->vSize = { fCenterX, fCenterY };
			pUnit->strKeyName = m_strNowUnitName;
			m_vecUnit.push_back(pUnit);
		}
	}
}

void CUnit::Release()
{
	for_each(m_vecUnit.begin(), m_vecUnit.end(), Safe_Delete<UNITDATA*>);
	m_vecUnit.clear();
}

void CUnit::MouseMove()
{
	D3DXVECTOR3 pt = Get_Mouse();
	pt.x -= vPos.x;
	pt.y -= vPos.y;

	D3DXVec3Normalize(&pt, &pt);

	vPos.x += pt.x * 10;
	vPos.y += pt.y * 10;
}

void CUnit::Set_Ratio(D3DXMATRIX* pOut, float fX, float fY)
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
