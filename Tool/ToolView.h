
// ToolView.h : CToolView Ŭ������ �������̽�
//

#pragma once

#include "Device.h"
#include "TextureMgr.h"

#include "Terrain.h"
#include "Unit.h"
#include "Building.h"

#include "MiniView.h"
#include "MyFormView.h"

enum class MouseState
{
	MS_NONE,
	MS_TILE,
	MS_UNIT,
	MS_BUILDING,
};
class CToolDoc; // CScrollView�� ��ӹ����� ���� ��� �Լ� �� �Ǵ� ������ �־ �ذ��ϴ� ���
class CToolView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// Ư���Դϴ�.
public:
	CToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

public:
	void Set_MiniView(CMiniView* _pMiniView) { m_pMiniView = _pMiniView; }
	void Set_MyView(CMyFormView* _pMyView) { m_pMyFormView = _pMyView; }
	MouseState GetMouseState() { return eMouseState; }
	void SetMouseState(MouseState _mouseState) { eMouseState = _mouseState; }
public:
	CTerrain* m_pTerrain;
	//CUnit* m_pUnit;

	list<CUnit*>	m_listUnit;
	//list<CUnit*>::iterator m_iterListUnit;


	CBuilding* m_pBuilding;

	CMiniView* m_pMiniView;
	CMyFormView* m_pMyFormView;
	

public:
	MouseState eMouseState;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // ToolView.cpp�� ����� ����
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

