#pragma once
#include "Obj.h"
class CMyBuilding : public CObj
{
public:
    CMyBuilding();
    virtual ~CMyBuilding();
public:
    HRESULT Initialize(void) override;
    int Update(void) override;
    void Late_Update(void) override;
    void Render(void) override;
    void Release(void) override;

private:
    HRESULT     Load_Building(const TCHAR* _pBuildingPath);

private:
    vector<BUILDINGDATA*>		m_vecBuilding;

};

