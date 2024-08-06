#pragma once
#include "afxdialogex.h"


// CTileCreate 대화 상자

class CTileCreate : public CDialog
{
	DECLARE_DYNAMIC(CTileCreate)

public:
	CTileCreate(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTileCreate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TileCreate };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_iTileCountX;
	int m_iTileCountY;
	afx_msg void OnBnClickedOk();
};
