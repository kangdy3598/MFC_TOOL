// MyFormView.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "MyFormView.h"

#include "MainFrm.h"
#include "ToolView.h"

// CMyFormView

IMPLEMENT_DYNCREATE(CMyFormView, CFormView)

CMyFormView::CMyFormView()
    : CFormView(IDD_MyFormView)
    // , m_bValue(false)
    , iTreeIndex(0)
    , m_pToolView(nullptr)
{

}

CMyFormView::~CMyFormView()
{
}

void CMyFormView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE1, m_tree);
}

BEGIN_MESSAGE_MAP(CMyFormView, CFormView)

    ON_BN_CLICKED(IDC_BUTTON1, &CMyFormView::OnBnClickedUnit)
    ON_BN_CLICKED(IDC_BUTTON2, &CMyFormView::OnBnClickedTile)
    ON_BN_CLICKED(IDC_BUTTON3, &CMyFormView::OnBnClickedSave)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMyFormView::OnTvnSelchangedTree)
    ON_NOTIFY(TVN_ITEMCHANGED, IDC_TREE1, &CMyFormView::OnTvnItemChangedTree)
    ON_BN_CLICKED(IDC_BUTTON7, &CMyFormView::OnBnClickedBuilding)
    ON_BN_CLICKED(IDC_BUTTON4, &CMyFormView::OnBnClickedPathFind)
END_MESSAGE_MAP()


// CMyFormView 진단

#ifdef _DEBUG
void CMyFormView::AssertValid() const
{
    CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyFormView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyFormView 메시지 처리기


void CMyFormView::Render(CPoint pt)
{

}

void CMyFormView::Set_ToolView()
{
    CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
    m_pToolView = pMainFrm->GetToolView();

    m_pToolView->Set_MyView(this);
}


void CMyFormView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    CFont		m_Font;
    m_Font.CreatePointFont(180, L"궁서");

    Set_ToolView();

    CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
    CToolView* pToolView = pMainFrm->GetToolView();
    pToolView->Set_MyView(this);


    root = m_tree.InsertItem((L"프로토스"), 0, 0, TVI_ROOT, TVI_LAST);
    unit = m_tree.InsertItem((L"유닛"), 0, 0, root, TVI_LAST);
    building = m_tree.InsertItem((L"건물"), 0, 0, root, TVI_LAST);

    SetTreeListOnEtc();
}

void CMyFormView::OnBnClickedUnit()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (nullptr == m_UnitTool.GetSafeHwnd())
        m_UnitTool.Create(IDD_UnitTool);

    m_UnitTool.ShowWindow(SW_SHOW);
}

void CMyFormView::OnBnClickedTile()
{

    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (nullptr == m_TileTool.GetSafeHwnd())
        m_TileTool.Create(IDD_TileTool);

    m_TileTool.ShowWindow(SW_SHOW);
}

void CMyFormView::OnBnClickedBuilding()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (nullptr == m_BuildingTool.GetSafeHwnd())
        m_BuildingTool.Create(IDD_BuildingTool);

    m_BuildingTool.ShowWindow(SW_SHOW);
}

void CMyFormView::OnBnClickedPathFind()
{
    if (nullptr == m_PathFind.GetSafeHwnd())
        m_PathFind.Create(IDD_PATHFIND);

    m_PathFind.ShowWindow(SW_SHOW);
}


void CMyFormView::OnBnClickedSave()
{
    CFileDialog		Dlg(FALSE,	// TRUE(불러오기), FALSE(다른 이름으로 저장)
        L"dat", // default 확장자명
        L"Tile.dat", // 대화 상자에 표시될 최초 파일명
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(일기 전용 체크박스 숨김 옵션), OFN_OVERWRITEPROMPT(중복 파일 저장 시, 경고 메시지 띄움 옵션)
        L"Data Files(*.dat)|*.dat||", // 콤보 박스에 출력될 문자열
        this);	// 부모 윈도우 주소

    TCHAR		szPath[MAX_PATH] = L"";

    GetCurrentDirectory(MAX_PATH, szPath);

    PathRemoveFileSpec(szPath);

    lstrcat(szPath, L"\\Data");

    // 대화 상자를 열었을 때 보이는 기본 경로
    Dlg.m_ofn.lpstrInitialDir = szPath;

    // DoModal : 대화 상자의 생성 여부를 판단
    if (IDOK == Dlg.DoModal())
    {
        // GetPathName : 선택된 경로를 반환, GetString : cstring 클래스 문자열을 원시 데이터 타입으로 변환하여 반환
        CString	str = Dlg.GetPathName().GetString();
        const TCHAR* pGetPath = str.GetString();

        HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
        CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

        CTerrain* pTerrain = pMainView->m_pTerrain;

        vector<TILE*>& vecTile = pTerrain->Get_VecTile();

        if (vecTile.empty())
            return;

        DWORD	dwByte(0);

        for (auto& pTile : vecTile)
            WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

        CloseHandle(hFile);
    }
}

void CMyFormView::SetTreeListOnProtoss()
{
    CString strTreeName;

    strName = m_UnitTool.Get_Name();

    strTreeName.Format(_T("%s"), strName);

    m_tree.InsertItem(strTreeName, 0, 0, unit, TVI_LAST);

    m_UnitTool.Set_Selected(false);
}

void CMyFormView::SetTreeListOnEtc()
{
    HTREEITEM root = m_tree.InsertItem((L"그 외"), 0, 0, TVI_ROOT, TVI_LAST);
    HTREEITEM mineral = m_tree.InsertItem((L"미네랄"), 0, 0, root, TVI_LAST);
    HTREEITEM gas = m_tree.InsertItem((L"가스"), 0, 0, root, TVI_LAST);
    HTREEITEM tile = m_tree.InsertItem((L"타일"), 0, 0, root, TVI_LAST);

    m_tree.InsertItem((L"1번타일"), 0, 0, tile, TVI_LAST);
    m_tree.InsertItem((L"2번타일"), 0, 0, tile, TVI_LAST);
    m_tree.InsertItem((L"3번타일"), 0, 0, tile, TVI_LAST);
}


void CMyFormView::Show_TreeUnitList()
{
    CString strTreeName;

    strName = m_UnitTool.Get_Name();

    strTreeName.Format(_T("%s"), strName);

    m_tree.InsertItem(strTreeName, 0, 0, unit, TVI_LAST);

    m_UnitTool.Set_Selected(false);
}

void CMyFormView::OnTvnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;

    HTREEITEM hSelected = m_tree.GetSelectedItem();
    HTREEITEM hParent = m_tree.GetParentItem(hSelected);

    CString ParentName = m_tree.GetItemText(hParent);
    CString SelectName = m_tree.GetItemText(hSelected);
    if (!lstrcmp(ParentName, L"유닛"))
    {
        m_pToolView->SetMouseState(MouseState::MS_UNIT);
        m_pToolView->m_pUnit->SetNowUnitName(SelectName);
        
    }
    else if (!lstrcmp(ParentName, L"건물"))
    {
        m_pToolView->SetMouseState(MouseState::MS_BUILDING);
        
        m_pToolView->m_pBuilding->SetNowBuildingName(SelectName);
    }
    else
    {
        m_pToolView->SetMouseState(MouseState::MS_NONE);
    }

    Invalidate(false);
}

void CMyFormView::OnTvnItemChangedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NMTVITEMCHANGE* pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;
}



