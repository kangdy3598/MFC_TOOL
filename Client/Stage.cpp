#include "stdafx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "MyTerrain.h"
#include "MyBuilding.h"
#include "MyUnit.h"


CStage::CStage()
{
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../Texture/Stage/Terrain/Tile/Tile%d.png", 
		TEX_MULTI, L"Terrain", L"Tile", 36)))
	{
		ERR_MSG(L"Tile Img Insert Failed");
		return E_FAIL;
	}	

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/MultiTexture/Unit/Protoss/Dragoon/Attack3/%d.png",
		TEX_MULTI, L"Unit", L"Dragoon", 8)))
	{
		ERR_MSG(L"Player Img Insert Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/MultiTexture/Build/Protoss/Gateway/%d.png",
		TEX_MULTI, L"Building", L"Gateway", 1)))
	{
		ERR_MSG(L"Player Img Insert Failed");
		return E_FAIL;
	}

	CObj*	pObj = new CMyTerrain;

	if (nullptr == pObj)
		return E_FAIL;


	pObj->Initialize();
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::TERRAIN, pObj);


	// building
	//CObj* pObj2 = new CMyBuilding;
	
	//if (nullptr == pObj2)
	//	return E_FAIL;

	// pObj2->Initialize();
	// CObjMgr::Get_Instance()->Add_Object(CObjMgr::BUILDING, pObj2);

	CObjMgr::Get_Instance()->Load_Object(L"../Data/BuildingPos.dat");



	//// 플레이어
	//CObj* pObj3 = new CMyUnit;

	//if (nullptr == pObj3)
	//	return E_FAIL;

	//pObj3->Initialize();
	//CObjMgr::Get_Instance()->Add_Object(CObjMgr::UNIT, pObj3);
	CObjMgr::Get_Instance()->Load_Unit(L"../Data/UnitPos.dat");
	
	return S_OK;
}

void CStage::Update_Scene()
{
	CObjMgr::Get_Instance()->Update();
}

void CStage::Late_Update_Scene()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render_Scene()
{
	CObjMgr::Get_Instance()->Render();
}

void CStage::Release_Scene()
{
}
