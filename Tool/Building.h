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

	vector<BUILDINGDATA*>& Get_VecBuilding() { return m_vecBuilding; }

public:
	HRESULT		Initialize();
	void		Update();
	void		Render();
	void		MiniRender();
	void		PreviewRender();
	void		InstallBuilding();
	void		Release();

	void SetNowBuildingName(CString _buildingName)
	{
		m_strNowBuildingName =  _buildingName;
	}
private:
	vector<BUILDINGDATA*>		m_vecBuilding;
	CToolView* m_ToolView;
	CString m_strNowBuildingName;

	void		Set_Ratio(D3DXMATRIX* pOut, float fX, float fY);
};