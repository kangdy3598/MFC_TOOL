#pragma once
#include "afxdialogex.h"


// CTileTool 대화 상자

class CTileTool : public CDialog
{
	DECLARE_DYNAMIC(CTileTool)

public:
	CTileTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTileTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TileTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);

	map<CString, CImage*>		m_MapPngImg;
	CListBox m_ListBox;
	CStatic m_picture;

	afx_msg void OnListBoxSelChange();
	
	int m_iTileNum;
	virtual BOOL OnInitDialog();
	
};
