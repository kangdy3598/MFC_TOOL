#pragma once
#include "afxdialogex.h"


// CBuilding 대화 상자

class CBuildingTool : public CDialog
{
	DECLARE_DYNAMIC(CBuildingTool)

public:
	CBuildingTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBuildingTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Building };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
