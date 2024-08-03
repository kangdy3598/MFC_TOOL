#pragma once
#include "afxdialogex.h"


// CUnitImageBox 대화 상자


class CUnitImageBox : public CDialog
{
	DECLARE_DYNAMIC(CUnitImageBox)

public:
	CUnitImageBox(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUnitImageBox();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITIMAGEBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	CStatic m_Picture;
	map<CString, CImage*>		m_MapPngImg;




public:
	virtual BOOL OnInitDialog();
	afx_msg void OnListBoxSelChange();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
