﻿#pragma once



// CMyFormView 폼 보기

#include "UnitTool.h"
#include "TileTool.h"
#include "PathFind.h"
#include "BuildingTool.h"

class CMainFrame;
class CToolView;
class CMyFormView : public CFormView
{
	DECLARE_DYNCREATE(CMyFormView)

protected:
	CMyFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MyFormView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	
	afx_msg void OnBnClickedUnit();
	afx_msg void OnBnClickedTile();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedBuilding();
	afx_msg void OnBnClickedPathFind();

	afx_msg void OnTvnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvnItemChangedTree(NMHDR* pNMHDR, LRESULT* pResult);

	void SetTreeListOnProtoss();
	void SetTreeListOnEtc();
	void Render(CPoint pt);


	void Show_TreeUnitList();
	void Set_ToolView();

public:
	CUnitTool m_UnitTool;
	CTileTool m_TileTool;
	CPathFind m_PathFind;
	CBuildingTool m_BuildingTool;
	CToolView* m_pToolView;

	CTreeCtrl m_tree;

	int iTreeIndex;
	CString	strName;


	HTREEITEM root;
	HTREEITEM unit;
	HTREEITEM building;


	
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedSaveUnit();
};


