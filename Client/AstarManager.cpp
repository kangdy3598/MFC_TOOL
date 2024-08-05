#include "stdafx.h"
#include "AstarManager.h"
#include "ObjMgr.h"
#include "MyTerrain.h"

IMPLEMENT_SINGLETON(CAstarManager)

CAstarManager::CAstarManager() : m_iStartIdx(0)
{
}

CAstarManager::~CAstarManager()
{
    Release();
}

void CAstarManager::Start_Astar(const D3DXVECTOR3& vStart, 
	const D3DXVECTOR3& vGoal)
{
	Release();

	CObj* pMyTerrain = CObjMgr::Get_Instance()->Get_Terrain();
	vector<TILE*>& vecTile = dynamic_cast<CMyTerrain*>(pMyTerrain)->GetVecTile();

	m_iStartIdx = GetTileIndex(vStart);

	int iGoalIdx = GetTileIndex(vGoal);

	if (0 > m_iStartIdx || 0 > iGoalIdx || vecTile.size() <= (size_t)m_iStartIdx || vecTile.size() <= (size_t)iGoalIdx)
		return;

	if (m_iStartIdx == iGoalIdx)
		return;

	if (0 != vecTile[iGoalIdx]->byOption)
		return;

	if (true == MakeRoute(m_iStartIdx, iGoalIdx))
		MakeBestList(m_iStartIdx, iGoalIdx);
}

void CAstarManager::Release()
{
	m_CloseList.clear();
	m_OpenList.clear();

	m_BestList.clear();
}

bool CAstarManager::MakeRoute(int iStartIdx, int iGoalIdx)
{
	CObj* pMyTerrain = CObjMgr::Get_Instance()->Get_Terrain();

	vector<TILE*>& vecTile = dynamic_cast<CMyTerrain*>(pMyTerrain)->GetVecTile();
	vector<list<TILE*>>& vecAdj = dynamic_cast<CMyTerrain*>(pMyTerrain)->GetVecAdj();

	if (!m_OpenList.empty())
		m_OpenList.pop_front();

	m_CloseList.push_back(iStartIdx);

	for (auto& pTile : vecAdj[iStartIdx])
	{
		if (iGoalIdx == pTile->iIndex)
		{
			pTile->iParentIdx = iStartIdx;
			return true;
		}

		if (false == CheckOpen(pTile->iIndex) &&
			false == CheckClose(pTile->iIndex))
		{
			pTile->iParentIdx = iStartIdx;
			m_OpenList.push_back(pTile->iIndex);
		}
	}

	if (m_OpenList.empty())
		return false;

	int	iStarIdx = m_iStartIdx;

	m_OpenList.sort([&vecTile, &iGoalIdx, &iStarIdx](int Dst, int Src)->bool
		{
			D3DXVECTOR3	vPCost1 = vecTile[iStarIdx]->vPos - vecTile[Dst]->vPos;
			D3DXVECTOR3	vPCost2 = vecTile[iStarIdx]->vPos - vecTile[Src]->vPos;

			D3DXVECTOR3	vGCost1 = vecTile[iGoalIdx]->vPos - vecTile[Dst]->vPos;
			D3DXVECTOR3	vGCost2 = vecTile[iGoalIdx]->vPos - vecTile[Src]->vPos;

			float	fCost1 = D3DXVec3Length(&vPCost1) + D3DXVec3Length(&vGCost1);
			float	fCost2 = D3DXVec3Length(&vPCost2) + D3DXVec3Length(&vGCost2);

			return fCost1 < fCost2;
		});

	return MakeRoute(m_OpenList.front(), iGoalIdx);
}

void CAstarManager::MakeBestList(int iStartIdx, int iGoalIdx)
{
	CObj* pMyTerrain = CObjMgr::Get_Instance()->Get_Terrain();

	vector<TILE*>& vecTile = dynamic_cast<CMyTerrain*>(pMyTerrain)->GetVecTile();

	m_BestList.push_front(vecTile[iGoalIdx]);

	int	iRouteIdx = vecTile[iGoalIdx]->iParentIdx;

	while (true)
	{
		if (iStartIdx == iRouteIdx)
			break;

		m_BestList.push_front(vecTile[iRouteIdx]);

		iRouteIdx = vecTile[iRouteIdx]->iParentIdx;
	}
}

int CAstarManager::GetTileIndex(const D3DXVECTOR3& vPos)
{
	CObj* pMyTerrain = CObjMgr::Get_Instance()->Get_Terrain();
	vector<TILE*>& vecTile = dynamic_cast<CMyTerrain*>(pMyTerrain)->GetVecTile();

	for (size_t index = 0; index < vecTile.size(); ++index)
	{
		if (Picking(vPos, index))
			return index;
	}

	return -1;
}

bool CAstarManager::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
{
	CObj* pMyTerrain = CObjMgr::Get_Instance()->Get_Terrain();
	vector<TILE*>& vecTile = dynamic_cast<CMyTerrain*>(pMyTerrain)->GetVecTile();

	// 12, 3, 6, 9
	D3DXVECTOR3	vPoint[4]
	{
		{ vecTile[iIndex]->vPos.x, vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
		{ vecTile[iIndex]->vPos.x + (TILECX / 2.f), vecTile[iIndex]->vPos.y, 0.f },
		{ vecTile[iIndex]->vPos.x, vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
		{ vecTile[iIndex]->vPos.x - (TILECX / 2.f), vecTile[iIndex]->vPos.y, 0.f },
	};

	// ¹æÇâ º¤ÅÍ
	D3DXVECTOR3	vDir[4]
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	// (x,y) -> (-y, x)
	D3DXVECTOR3	vNormal[4]
	{
		{ -vDir[0].y, vDir[0].x, 0.f },
		{ -vDir[1].y, vDir[1].x, 0.f },
		{ -vDir[2].y, vDir[2].x, 0.f },
		{ -vDir[3].y, vDir[3].x, 0.f }
	};

	D3DXVECTOR3		vMouseDir[4]
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		if (0.f < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;
}

bool CAstarManager::CheckClose(int iIndex)
{
	for (int& iCloseIdx : m_CloseList)
	{
		if (iIndex == iCloseIdx)
			return true;
	}

	return false;
}

bool CAstarManager::CheckOpen(int iIndex)
{
	for (int& iOpenIdx : m_OpenList)
	{
		if (iIndex == iOpenIdx)
			return true;
	}

	return false;
}
