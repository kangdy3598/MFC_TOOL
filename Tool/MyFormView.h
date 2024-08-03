#pragma once



// CMyFormView 폼 보기
#include "UnitTool.h"
#include "TileTool.h"
#include "BuildingTool.h"

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

	void SetTreeListOnProtoss();
	void SetTreeListOnEtc();



public:
	CUnitTool m_UnitTool;
	CTileTool m_TileTool;
	CBuildingTool m_BuildingTool;

	CTreeCtrl m_tree;

	int iTreeIndex;


	afx_msg void OnTvnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvnItemChangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedBuilding();


	HTREEITEM root;
	HTREEITEM unit;
	HTREEITEM building;




};


