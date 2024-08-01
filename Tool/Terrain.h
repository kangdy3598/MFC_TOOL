#pragma once

#include "Include.h"
#include "TileTool.h"

class CToolView;
class CMiniView;

class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	void		Set_ToolView(CToolView* pToolView) { m_ToolView = pToolView; }
	void		Check_Picking(CPoint _mousePosition, CTileTool* _CTileTool);

	vector<TILE*>& Get_VecTile() { return m_vecTile; }
public:
	HRESULT		Initialize();
	void		Update();
	void		Render(int _type = 0);
	void		MiniRender();
	void		Release();

private:
	vector<TILE*>		m_vecTile;
	CToolView* m_ToolView;
	CMiniView* m_MiniView;

	void		Set_Ratio(D3DXMATRIX* pOut, float fX, float fY);
};