#pragma once
#include "afxdialogex.h"


// CBuilding 대화 상자
#include "Include.h"
class CBuildingTool : public CDialog
{
	DECLARE_DYNAMIC(CBuildingTool)

public:
	CBuildingTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBuildingTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BuildingTool };
#endif
public:
	CString m_strName;
	int m_iHP;
	int m_iShield;
	int m_iAttack;

	CButton m_radioBuildingRace[3];
	CButton m_checkAttackType[2];
	CStatic m_picture;

	CString m_strSearchName;
	CEdit m_searchName;

	CListBox m_ListBox;
	map<CString, BUILDINGDATA*>		m_mapBuildingData;
	BUILDINGDATA* m_tSelectBuildingData;

	CString m_strFullPath;
	CString m_strNameKey;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCreate();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedShowAll();
	afx_msg void OnLbnSelchange();
	afx_msg void OnBnClickedChangeImage();

public:
	void OnDataLoad();
	
	
};
