#pragma once
#include "afxdialogex.h"


// CUnitTool 대화 상자
#include "Include.h"

#include "UnitImageBox.h"

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
	CStatic m_Picture;


	int m_iHP;
	int m_iAttack;

	CButton m_radioUnitType[2];
	CButton m_checkAttackType[2];

	CString m_strSearchName;
	CEdit m_searchName;

	CListBox m_ListBox;

	map<CString, UNITDATA*>		m_mapUnitData;
	map<CString, UNITDATA*>		Get_UnitData() { return m_mapUnitData; }




	map<CString, CImage*>		m_MapPngUnitImg;
	void Set_PngImg(map<CString, CImage*> _pngImage, int _iIndex) { m_MapPngUnitImg = _pngImage; m_iIndex = _iIndex; }

	


public:
	CUnitImageBox		m_UnitImageWnd;
	CString				m_ImgName;
	int					m_iIndex;
	bool				m_bSelected;


	void Set_UnitAdd(bool _bUnitAdded) { m_bSelected = _bUnitAdded; }
	bool Get_UnitAdd() { return m_bSelected; }


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
