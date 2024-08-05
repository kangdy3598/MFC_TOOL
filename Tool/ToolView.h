
// ToolView.h : CToolView 클래스의 인터페이스
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
class CToolDoc; // CScrollView로 상속받으면 가끔 멤버 함수 안 되는 오류가 있어서 해결하는 방법
class CToolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// 특성입니다.
public:
	CToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // ToolView.cpp의 디버그 버전
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

