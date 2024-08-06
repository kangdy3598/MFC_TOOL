// TileCreate.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "TileCreate.h"

#include "MainFrm.h"
#include "ToolView.h"

// CTileCreate 대화 상자

IMPLEMENT_DYNAMIC(CTileCreate, CDialog)

CTileCreate::CTileCreate(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TileCreate, pParent)
	, m_iTileCountX(0)
	, m_iTileCountY(0)
{

}

CTileCreate::~CTileCreate()
{
}

void CTileCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_iTileCountX);
	DDX_Text(pDX, IDC_EDIT1, m_iTileCountY);
}


BEGIN_MESSAGE_MAP(CTileCreate, CDialog)
	ON_BN_CLICKED(IDOK, &CTileCreate::OnBnClickedOk)
END_MESSAGE_MAP()


// CTileCreate 메시지 처리기

void CTileCreate::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CToolView* m_pToolView = pMainFrm->GetToolView();

	m_pToolView->InitTerrain();
}
