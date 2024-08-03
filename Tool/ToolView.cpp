
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


HWND	g_hWnd;

// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)

	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView() : m_pTerrain(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
}

void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	//SetScrollSizes 스크롤 바의 사이즈를 지정하는 함수
	//MM_TEXT: 픽셀 단위로 크기를 조정

	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY / 2));
	
	// AfxGetMainWnd : 현재의 메인 윈도우를 반환하는 전역 함수
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();
	
	RECT	rcWnd{};

	// GetWindowRect : 현재 윈도우의 Rect 정보를 얻어오는 함수
	pMainFrm->GetWindowRect(&rcWnd);

	// 지정한 매개 변수 값으로 렉트를 설정하는 함수
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	// rcWnd.right -> 창의 가로 길이
	// rcWnd.bottom -> 창의 세로 길이
	RECT	rcMainView{};

	// GetClientRect : 현재 view 창의 RECT 정보를 얻어오는 함수
	GetClientRect(&rcMainView);

	float fRowFrm = float(rcWnd.right - rcMainView.right);
	float fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	// SetWindowPos : 매개 변수대로 새롭게 윈도우의 위치와 크기를 조정하는 함수

	//SetWindowPos(배치할 윈도우의 Z순서에 대한 포인터, X좌표, Y좌표, 가로 크기, 세로 크기, 배치할 윈도우의 크기 및 위치 지정 옵션)
	//nullptr : 순서 변경 안함
	//SWP_NOZORDER : 현재 정렬 순서 유지

	pMainFrm->SetWindowPos(nullptr, 
		0, 0,
		int(WINCX + fRowFrm), 
		int(WINCY + fColFrm), 
		SWP_NOZORDER);
		
	pMainFrm->SetToolView(this);
	g_hWnd = m_hWnd;

	if (FAILED(CDevice::Get_Instance()->Init_Device()))
	{
		AfxMessageBox(L"Init_Device Failed");
		return;
	}

	/*if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Cube.png", TEX_SINGLE, L"Cube")))
	{
		AfxMessageBox(L"Cube Texture Failed");
		return;
	}*/

	m_pTerrain = new CTerrain;
	if (FAILED(m_pTerrain->Initialize()))
	{
		return;
	}

	m_pTerrain->Set_ToolView(this);

	m_pUnit = new CUnit;
	if (FAILED(m_pUnit->Initialize()))
	{
		return;
	}
	m_pUnit->Set_ToolView(this);

	m_pBuilding = new CBuilding;
	if (FAILED(m_pBuilding->Initialize()))
	{
		return;
	}
	m_pBuilding->Set_ToolView(this);
}

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDevice::Get_Instance()->Render_Begin();

	m_pTerrain->Render();
	m_pUnit->Render();
	m_pBuilding->Render();

	//m_pMiniView->OnDraw(nullptr);
	/*TCHAR	szBuf[MIN_STR] = L"";

	CDevice::Get_Instance()->Get_Font()->DrawTextW(
		CDevice::Get_Instance()->Get_Sprite(),
		szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	swprintf_s(szBuf, L"X : %f, Y : %f", Get_Mouse().x,
		Get_Mouse().y + GetScrollPosition().y);

	D3DXMATRIX	matTrans2;
	D3DXMatrixTranslation(&matTrans2, 100.f, 100.f, 0.f);
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matTrans2);
	CDevice::Get_Instance()->Get_Font()->DrawTextW(
		CDevice::Get_Instance()->Get_Sprite(),
		szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));*/

	CDevice::Get_Instance()->Render_End();	
}
void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();

	Safe_Delete(m_pTerrain);

	CTextureMgr::Get_Instance()->Destroy_Instance();
	CDevice::Get_Instance()->Destroy_Instance();
}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);
	////
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyFormView* pMyForm = dynamic_cast<CMyFormView*>(
		pMainFrm->m_SecondSplitter.GetPane(1, 0));

	CTileTool* pTileTool = &pMyForm->m_TileTool;





	m_pTerrain->Check_Picking(point + GetScrollPosition(), pTileTool);
	m_pMiniView->OnDraw(nullptr);
	

	Invalidate();
}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	CScrollView::OnMouseMove(nFlags, point);
	AfxMessageBox(L"mouse move");
}


#pragma region 생략
BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}
BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


#pragma endregion 생략






