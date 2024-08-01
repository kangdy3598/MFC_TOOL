// MiniView.cpp: 구현 파일
//
#include "stdafx.h"
#include "Tool.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "MiniView.h"


// MiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView() : m_pTerrain()
{
}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// MiniView 그리기

void CMiniView::OnDraw(CDC* /*pDC*/)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	CDevice::Get_Instance()->Render_Begin();

	m_pTerrain->MiniRender();

	CDevice::Get_Instance()->Render_End(m_hWnd);

	//Invalidate(false);
}


// MiniView 진단

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// MiniView 메시지 처리기


void CMiniView::OnInitialUpdate()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CView::OnInitialUpdate();

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CToolView* pToolView = pMainFrm->GetToolView();

	pToolView->Set_MiniView(this);
	m_pTerrain = pToolView->m_pTerrain;
	
}
