
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
    // ǥ�� �μ� ����Դϴ�.
    ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)

<<<<<<< HEAD
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
=======
    ON_WM_DESTROY()
    ON_WM_LBUTTONDOWN()
>>>>>>> origin/main
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView() 
	: m_pTerrain(nullptr)
	, eMouseState(MouseState::MS_NONE)
{
    // TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
}

void CToolView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    //SetScrollSizes ��ũ�� ���� ����� �����ϴ� �Լ�
    //MM_TEXT: �ȼ� ������ ũ�⸦ ����

    SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY / 2));

    // AfxGetMainWnd : ������ ���� �����츦 ��ȯ�ϴ� ���� �Լ�
    CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

    RECT	rcWnd{};

    // GetWindowRect : ���� �������� Rect ������ ������ �Լ�
    pMainFrm->GetWindowRect(&rcWnd);

    // ������ �Ű� ���� ������ ��Ʈ�� �����ϴ� �Լ�
    SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

    // rcWnd.right -> â�� ���� ����
    // rcWnd.bottom -> â�� ���� ����
    RECT	rcMainView{};

    // GetClientRect : ���� view â�� RECT ������ ������ �Լ�
    GetClientRect(&rcMainView);

    float fRowFrm = float(rcWnd.right - rcMainView.right);
    float fColFrm = float(rcWnd.bottom - rcMainView.bottom);

    // SetWindowPos : �Ű� ������� ���Ӱ� �������� ��ġ�� ũ�⸦ �����ϴ� �Լ�

    //SetWindowPos(��ġ�� �������� Z������ ���� ������, X��ǥ, Y��ǥ, ���� ũ��, ���� ũ��, ��ġ�� �������� ũ�� �� ��ġ ���� �ɼ�)
    //nullptr : ���� ���� ����
    //SWP_NOZORDER : ���� ���� ���� ����

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

    //m_pUnit = new CUnit;
    //if (FAILED(m_pUnit->Initialize()))
    //{
    //	return;
    //}
    //m_pUnit->Set_ToolView(this);

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

<<<<<<< HEAD
	if (eMouseState == MouseState::MS_BUILDING)
		m_pBuilding->PreviewRender();
=======

    //m_pUnit->Render();

    for (auto& iter : m_listUnit)
    {
        (*iter).Render();
    }

>>>>>>> origin/main

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
    //Safe_Delete(m_pUnit);
    Safe_Delete(m_pBuilding);

    CTextureMgr::Get_Instance()->Destroy_Instance();
    CDevice::Get_Instance()->Destroy_Instance();
}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
<<<<<<< HEAD
	CScrollView::OnLButtonDown(nFlags, point);

	if (eMouseState == MouseState::MS_NONE)
		return;

	if (eMouseState == MouseState::MS_BUILDING)
	{
		m_pBuilding->InstallBuilding();
		m_pMiniView->OnDraw(nullptr);
		Invalidate(FALSE);
		return;
	}
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyFormView* pMyForm = dynamic_cast<CMyFormView*>(
		pMainFrm->m_SecondSplitter.GetPane(1, 0));
=======
    CScrollView::OnLButtonDown(nFlags, point);
    ////
    CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
    CMyFormView* pMyForm = dynamic_cast<CMyFormView*>(
        pMainFrm->m_SecondSplitter.GetPane(1, 0));
>>>>>>> origin/main

    CTileTool* pTileTool = &pMyForm->m_TileTool;

    CUnitTool* pUnitTool = &pMyForm->m_UnitTool;
    m_listUnit.push_back(pUnitTool->Create_Unit(point + GetScrollPosition(), pUnitTool->Get_Index()));


    for (auto& iter : m_listUnit)
    {
        if (FAILED((*iter).Initialize()))
            return;
        (*iter).Set_ToolView(this);
        (*iter).Set_Keys(pUnitTool->Get_ObjKey(), pUnitTool->Get_StateKey());
    }


    m_pTerrain->Check_Picking(point + GetScrollPosition(), pTileTool);

<<<<<<< HEAD
	m_pTerrain->Check_Picking(point + GetScrollPosition(), pTileTool);
	m_pMiniView->OnDraw(nullptr);
	
	Invalidate();
=======




    m_pMiniView->OnDraw(nullptr);


    Invalidate();
>>>>>>> origin/main
}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
<<<<<<< HEAD
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
=======
    CScrollView::OnMouseMove(nFlags, point);
    AfxMessageBox(L"mouse move");
}
>>>>>>> origin/main

	//if (eMouseState == MouseState::MS_NONE)
	//	return;

	CScrollView::OnMouseMove(nFlags, point);

	
	Invalidate(FALSE);
}

#pragma region ����
BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
    //  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

    return CScrollView::PreCreateWindow(cs);
}
BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // �⺻���� �غ�
    return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
    return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


#pragma endregion ����


void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);

	switch (nChar)
	{
	case VK_ESCAPE:
		eMouseState = MouseState::MS_NONE;
		break;
	}


}
