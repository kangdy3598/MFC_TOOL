#pragma once
#include "afxdialogex.h"


// CUnitTool 대화 상자
#include "Include.h"
class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UnitTool };
#endif

public:
	CString m_strName;
	int m_iHP;
	int m_iAttack;

	CButton m_radioUnitType[2];
	CButton m_checkAttackType[2];

	CString m_strSearchName;
	CEdit m_searchName;

	CListBox m_ListBox;
	map<CString, UNITDATA*>		m_mapUnitData;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedCreate();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedShowAll();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnListBoxSelChange();
};
