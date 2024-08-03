// UnitImageBox.cpp: 구현 파일
//

#include "afxdialogex.h"
#include "stdafx.h"
#include "Tool.h"

#include "FilePath.h"
#include "UnitImageBox.h"
#include "UnitTool.h"
#include "MainFrm.h"


// CUnitImageBox 대화 상자

IMPLEMENT_DYNAMIC(CUnitImageBox, CDialog)

CUnitImageBox::CUnitImageBox(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_UNITIMAGEBOX, pParent)
{

}

CUnitImageBox::~CUnitImageBox()
{
}

void CUnitImageBox::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListBox);
    DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CUnitImageBox, CDialog)
    ON_WM_DROPFILES()
    ON_LBN_SELCHANGE(IDC_LIST1, &CUnitImageBox::OnListBoxSelChange)
END_MESSAGE_MAP()


// CUnitImageBox 메시지 처리기


BOOL CUnitImageBox::OnInitDialog()
{
    CDialog::OnInitDialog();

    UpdateData(TRUE);



    CString path, fileName;

    path = L"..\\Texture\\MultiTexture\\Unit\\Protoss\\Dragoon\\Stand\\";
    for (int i = 0; i < 8; ++i)
    {
        CImage* pPngImage = new CImage;

        fileName.Format(L"%d.png", i);
        pPngImage->Load(path + fileName);

        m_MapPngImg.insert({ fileName, pPngImage });
        m_ListBox.AddString(fileName);
    }



    UpdateData(FALSE);
    return TRUE;
}


void CUnitImageBox::OnListBoxSelChange()
{
    UpdateData(TRUE);

    CString		strFindImgName;

    int iIndex = m_ListBox.GetCurSel();

    if (LB_ERR == iIndex)
        return;

    m_ListBox.GetText(iIndex, strFindImgName);

    auto iter = m_MapPngImg.find(strFindImgName);

    if (iter == m_MapPngImg.end())
        return;

    m_Picture.SetBitmap(*(iter->second));
        
    ////
    CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
    CMyFormView* pMyForm = dynamic_cast<CMyFormView*>(
        pMainFrm->m_SecondSplitter.GetPane(1, 0));

    CUnitTool* pUnitTool = &pMyForm->m_UnitTool;

    pUnitTool->Set_PngImg(m_MapPngImg, iIndex);

    UpdateData(FALSE);
}


void CUnitImageBox::OnDropFiles(HDROP hDropInfo)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    UpdateData(TRUE);

    CDialog::OnDropFiles(hDropInfo);

    TCHAR	szFilePath[MAX_PATH] = L"";
    TCHAR	szFileName[MAX_STR] = L"";

    // DragQueryFile : 드롭된 파일의 정보를 얻어오는 함수
    // 두 번째 인자값이 0xffffffff(-1)인 경우 드롭된 파일의 개수를 반환

    int		iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

    for (int i = 0; i < iFileCnt; ++i)
    {
        DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

        CString strRelative = CFilePath::ConvertRelativePath(szFilePath);

        CString	strFileName = PathFindFileName(strRelative);

        lstrcpy(szFileName, strFileName.GetString());

        // PathRemoveExtension : 확장자명을 없애는 함수
        PathRemoveExtension(szFileName);

        strFileName = szFileName;

        auto iter = m_MapPngImg.find(strFileName);

        if (iter == m_MapPngImg.end())
        {
            CImage* pPngImage = new CImage;
            pPngImage->Load(strRelative);

            m_MapPngImg.insert({ strFileName, pPngImage });
            m_ListBox.AddString(szFileName);
        }
    }

    //Horizontal_Scroll();

    UpdateData(FALSE);
}
