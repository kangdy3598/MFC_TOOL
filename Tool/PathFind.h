﻿#pragma once
#include "afxdialogex.h"
#include "Include.h"


// CPathFind 대화 상자

class CPathFind : public CDialog
{
	DECLARE_DYNAMIC(CPathFind)

public:
	CPathFind(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPathFind();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATHFIND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSaveData();
	afx_msg void OnLoadData();
	afx_msg void OnListBox();

public:
	CListBox m_ListBox;
	list<IMGPATH*>		m_PathInfoList;

	afx_msg void OnDestroy();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
