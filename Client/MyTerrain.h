#pragma once
#include "Obj.h"
class CMyTerrain :	public CObj
{
public:
	CMyTerrain();
	virtual ~CMyTerrain();

public:
	vector<TILE*>& GetVecTile() { return m_vecTile; }
	vector<list<TILE*>>& GetVecAdj() { return m_vecAdj; }

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

private:
	HRESULT		Load_Tile(const TCHAR* pTilePath);

	HRESULT		Ready_Adj();

private:
	vector<TILE*>		m_vecTile;

	vector<list<TILE*>>	m_vecAdj;
};
	
