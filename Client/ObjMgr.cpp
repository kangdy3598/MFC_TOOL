#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "MyBuilding.h"
#include "MyUnit.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release(); 
}

void CObjMgr::Add_Object(ID eID, CObj * pObject)
{
	if (nullptr == pObject || END <= eID)
		return; 

	m_listObject[eID].emplace_back(pObject); 
}

void CObjMgr::Update()
{
	for (int i = 0 ; i < END; ++i)
	{
		for (auto iter = m_listObject[i].begin();
			       iter != m_listObject[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete(*iter);
				iter = m_listObject[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{
	for (int i = 0 ; i < END ; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->Late_Update();
	}
}

void CObjMgr::Render()
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->Render();
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			Safe_Delete(pObject); 

		m_listObject[i].clear();
	}
}

HRESULT CObjMgr::Load_Object(const TCHAR* _pBuildingPath)
{
	HANDLE hFile = CreateFile(_pBuildingPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte(0);

	while (true)
	{
		CObj* pMyBuilding = new CMyBuilding;

		D3DXVECTOR3 vPos{};
		D3DXVECTOR3 vSize{};

		ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
		ReadFile(hFile, vSize, sizeof(D3DXVECTOR3), &dwByte, nullptr);

		pMyBuilding->Set_Pos(vPos);
		pMyBuilding->Set_Size(vSize);

		if (0 == dwByte)
		{
			Safe_Delete(pMyBuilding);
			break;
		}

		m_listObject[BUILDING].push_back(pMyBuilding);
	}

	CloseHandle(hFile);

	return S_OK;
}

HRESULT CObjMgr::Load_Unit(const TCHAR* _pUnitPath)
{
	HANDLE hFile = CreateFile(_pUnitPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte(0);

	while (true)
	{
		CObj* pMyUnit = new CMyUnit;

		D3DXVECTOR3 vPos{};
		D3DXVECTOR3 vSize{};

		ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
		ReadFile(hFile, vSize, sizeof(D3DXVECTOR3), &dwByte, nullptr);

		pMyUnit->Set_Pos(vPos);
		pMyUnit->Set_Size(vSize);

		if (0 == dwByte)
		{
			Safe_Delete(pMyUnit);
			break;
		}

		m_listObject[UNIT].push_back(pMyUnit);
	}

	CloseHandle(hFile);

	return S_OK;
}
