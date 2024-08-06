#include "stdafx.h"
#include "MyBuilding.h"
#include "Device.h"
#include "TextureMgr.h"

CMyBuilding::CMyBuilding()
{
}

CMyBuilding::~CMyBuilding()
{
    Release();
}

HRESULT CMyBuilding::Initialize(void)
{
    m_vecBuilding.reserve(TILEX * TILEY);

    //if (FAILED(Load_Building(L"../Data/BuildingPos.dat")))
    //{
    //    return E_FAIL;
    //}

    return S_OK;
}

int CMyBuilding::Update(void)
{
    return 0;
}

void CMyBuilding::Late_Update(void)
{
}

void CMyBuilding::Render(void)
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR	szBuf[MIN_STR] = L"";
	int		iIndex(0);

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y, 0.f);

	matWorld = matScale * matTrans;

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Building", L"Gateway", 0);

	float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	D3DXVECTOR3 center = D3DXVECTOR3(fCenterX, fCenterY, 0.f);
	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr, // ����� �̹��� ������ RECT �ּ�, NULL�� ��� 0, 0 �������� ���
		&center, // ����� �̹����� �߽� ��ǥ, VEC3�ּ�, NULL �� ��� 0, 0�� �߽� ��ǥ
		nullptr, // �ؽ�ó�� ����� ��ġ ��ǥ, VEC3�ּ�, ��ũ���� 0, 0 ��ǥ�� ���
		D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ����, 0xffffffff�� �Ѱ��ָ� ������ ����
}

void CMyBuilding::Release(void)
{
	for_each(m_vecBuilding.begin(), m_vecBuilding.end(), Safe_Delete<BUILDINGDATA*>);
	m_vecBuilding.clear();
}
