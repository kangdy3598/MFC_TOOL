#pragma once
#include "Include.h"
class CAstarManager
{
    DECLARE_SINGLETON(CAstarManager)

private:
    CAstarManager();
    ~CAstarManager();

public:
	list<TILE*>& GetBestList() { return m_BestList; }
public:
	void		Start_Astar(const D3DXVECTOR3& vStart, const D3DXVECTOR3& vGoal);
	void		Release();
private:
	bool		MakeRoute(int iStartIdx, int iGoalIdx);
	void		MakeBestList(int iStartIdx, int iGoalIdx);

	int			GetTileIndex(const D3DXVECTOR3& vPos);
	bool		Picking(const D3DXVECTOR3& vPos, const int& iIndex);

private:
	bool		CheckClose(int iIndex);
	bool		CheckOpen(int iIndex);

private:
	list<int>		m_CloseList;
	list<int>		m_OpenList;

	list<TILE*>		m_BestList;
	int				m_iStartIdx;
};

