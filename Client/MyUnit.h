#pragma once
#include "Obj.h"
class CMyUnit : public CObj
{
public:
	CMyUnit();
	virtual ~CMyUnit();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

private:
	void		Move_Astar();
};

