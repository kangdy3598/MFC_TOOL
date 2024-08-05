#pragma once

#include "Include.h"
class CTimeManager
{

    DECLARE_SINGLETON(CTimeManager);

private:
    CTimeManager();
    ~CTimeManager();

public:
	float			Get_TimeDelta() { return m_fTimeDelta; }

public:
	void			Initialize();
	void			Update();

private:
	LARGE_INTEGER			m_CurTime;
	LARGE_INTEGER			m_OldTime;
	LARGE_INTEGER			m_OriginTime;
	LARGE_INTEGER			m_CpuTick;

	float					m_fTimeDelta;
};

