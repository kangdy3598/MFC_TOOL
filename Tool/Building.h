#pragma once

#include "Include.h"
#include "TileTool.h"

class CToolView;
class CMiniView;

class CBuilding
{
public:
	CBuilding();
	~CBuilding();

public:
	void		Set_ToolView(CToolView* pToolView) { m_ToolView = pToolView; }
	void		Check_Picking(CPoint _mousePosition, CTileTool* _CTileTool);

	vector<TILE*>& Get_VecTile() { return m_vecTile; }
public:
	HRESULT		Initialize();
	void		Update();
	void		Render();
	void		Release();

	void		MouseMove();
private:
	vector<TILE*>		m_vecTile;
	CToolView* m_ToolView;

	D3DXVECTOR3	vPos;
	D3DXVECTOR2 vSize;
	void		Set_Ratio(D3DXMATRIX* pOut, float fX, float fY);
};