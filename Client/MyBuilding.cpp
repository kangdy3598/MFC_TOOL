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

    if (FAILED(Load_Building(L"../Data/Building.dat")))
    {
        return E_FAIL;
    }

	m_wstrObjKey = L"Building";
	m_wstrStateKey = L"Forge";


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

	for (auto pBuilding : m_vecBuilding)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			pBuilding->vPos.x + m_vScroll.x,
			pBuilding->vPos.y + m_vScroll.y, 0.f);

		matWorld = matScale * matTrans;

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		//const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Building", L"Forge", 0);
		//
		//float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		//float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;
		//
		//D3DXVECTOR3 center = D3DXVECTOR3(fCenterX, fCenterY, 0.f);
		//CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		//	nullptr, // 출력할 이미지 영역의 RECT 주소, NULL인 경우 0, 0 기준으로 출력
		//	&center, // 출력할 이미지의 중심 좌표, VEC3주소, NULL 인 경우 0, 0이 중심 좌표
		//	nullptr, // 텍스처를 출력할 위치 좌표, VEC3주소, 스크린상 0, 0 좌표에 출력
		//	D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 0xffffffff를 넘겨주면 원본색 유지

	}
}

void CMyBuilding::Release(void)
{
	for_each(m_vecBuilding.begin(), m_vecBuilding.end(), Safe_Delete<BUILDINGDATA*>);
	m_vecBuilding.clear();
}

HRESULT CMyBuilding::Load_Building(const TCHAR* _pBuildingPath)
{
	HANDLE hFile = CreateFile(_pBuildingPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte(0);

	BUILDINGDATA* pBuilding = nullptr;

	while (true)
	{
		pBuilding = new BUILDINGDATA;

		ReadFile(hFile, pBuilding, sizeof(BUILDINGDATA), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pBuilding);
			break;
		}

		m_vecBuilding.push_back(pBuilding);
	}

	CloseHandle(hFile);
    return S_OK;
}
