#include "stdafx.h"
#include "Building.h"

#include "Device.h"
#include "TextureMgr.h"
#include "ToolView.h"

CBuilding::CBuilding()
	: m_ToolView()
	, m_strNowBuildingName(L"")

{
	m_vecBuilding.reserve(TILEX * TILEY);
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
		TEX_MULTI, L"Building", L"GateWay", MAX_TILETYPE)))
	{
		AfxMessageBox(L"Building Texture Failed");
		return E_FAIL;
	}


	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../Texture/MultiTexture/Build/Protoss/Forge/0.png",
		TEX_MULTI, L"Building", L"Forge", MAX_TILETYPE)))
	{
		AfxMessageBox(L"Building Texture Failed");
		return E_FAIL;
	}
	return S_OK;
}

void CBuilding::Update()
{

}

// m_vecBuilding�� �ִ� �ǹ�(�ʿ� ��ġ �Ϸ�� �ǹ�)�� �׸�
void CBuilding::Render()
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR	szBuf[MIN_STR] = L"";

	for (auto pBuilding : m_vecBuilding)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			pBuilding->vPos.x,
			pBuilding->vPos.y, 0.f);

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
				L"Building", pBuilding->strKeyName,
				0);

		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		HRESULT result = CDevice::Get_Instance()->Get_Sprite()->Draw(
			pTexInfo->pTexture,
			nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));

	}

}

void CBuilding::MiniRender()
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR	szBuf[MIN_STR] = L"";

	for (auto pBuilding : m_vecBuilding)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			pBuilding->vPos.x,
			pBuilding->vPos.y, 0.f);

		matWorld = matScale * matTrans;

		RECT	rc{};

		// GetClientRect : Ŭ���̾�Ʈ ������ �ش��ϴ� RECT ������ ������ �Լ�
		GetClientRect(m_ToolView->m_hWnd, &rc);

		float	fRatioX = 300 / float(rc.right - rc.left);
		float	fRatioY = 300 / float(rc.bottom - rc.top);

		Set_Ratio(&matWorld, fRatioX, fRatioY);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo =
			CTextureMgr::Get_Instance()->Get_Texture(
				L"Building", pBuilding->strKeyName,
				0);

		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		HRESULT result = CDevice::Get_Instance()->Get_Sprite()->Draw(
			pTexInfo->pTexture,
			nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

// m_vecBuilding�� ���� ���� ���콺 Ŀ�� ��ġ�� �ǹ��� �׸�
// ��ġ �Ϸ�� �ǹ��� ���� ���� ���ؼ� �������ϰ� ���̰� �ϸ� ������
void CBuilding::PreviewRender()
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
				L"Building", m_strNowBuildingName,
				0);

		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		HRESULT result = CDevice::Get_Instance()->Get_Sprite()->Draw(
			pTexInfo->pTexture,
			nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr,
			D3DCOLOR_ARGB(128, 255, 255, 255));

	}
}

// CToolView::OnLButtonDown()�� ���� ȣ��
// ���� ���콺 ��ġ�� m_vecBuilding�� �ǹ� ������ �ְ� Invalidate() ȣ��
// Invalidate() ȣ�� -> OnDraw() ȣ�� -> CBuilding::Render() ȣ��

void CBuilding::InstallBuilding()
{
	D3DXVECTOR3 pos = Get_Mouse();
	//for (int i = 0; i < TILEY; ++i)
	{
		//for (int j = 0; j < TILEX; ++j)
		{
			BUILDINGDATA* pBuilding = new BUILDINGDATA;

			const TEXINFO* pTexInfo =
				CTextureMgr::Get_Instance()->Get_Texture(
					L"Building", m_strNowBuildingName,
					0);
			float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
			float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

			pBuilding->vPos = { pos.x, pos.y, 0.f };
			pBuilding->vSize = { fCenterX, fCenterY };
			pBuilding->strKeyName = m_strNowBuildingName;
			m_vecBuilding.push_back(pBuilding);
		}
	}
}

void CBuilding::Release()
{
	for_each(m_vecBuilding.begin(), m_vecBuilding.end(), Safe_Delete<BUILDINGDATA*>);
	m_vecBuilding.clear();
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
