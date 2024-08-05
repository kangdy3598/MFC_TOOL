#pragma once

#include "Include.h"
#include "TileTool.h"

class CToolView;
class CMiniView;

class CUnit
{
public:
	CUnit();
	~CUnit();

public:
	void		Set_ToolView(CToolView* pToolView) { m_ToolView = pToolView; }

	void		Set_Keys(wstring _strObjKey, wstring _strStateKey)
	{
		m_wstrObjKey = _strObjKey;
		m_wstrStateKey = _strStateKey;
	}


	vector<TILE*>& Get_VecTile() { return m_vecTile; }

public:
	HRESULT		Initialize();
	void		Update();
	void		Render();
	void		MiniRender();
	void		Release();

	void		MouseMove();


	D3DXVECTOR3 Get_Pos() { return vPos; }
	void Set_Pos(CPoint _Pos) { vPos.x = float(_Pos.x); vPos.y = float(_Pos.y); }


	wstring					m_wstrObjKey = L"";
	wstring					m_wstrStateKey = L"";


private:
	vector<TILE*>		m_vecTile;
	CToolView* m_ToolView;
	CMiniView* m_MiniView;




	D3DXVECTOR3	vPos;	
	D3DXVECTOR2 vSize;
	void		Set_Ratio(D3DXMATRIX* pOut, float fX, float fY);
};