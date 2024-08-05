// PathFind.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "PathFind.h"
#include "FilePath.h"

#include "TextureMgr.h"


// CPathFind 대화 상자

IMPLEMENT_DYNAMIC(CPathFind, CDialog)

CPathFind::CPathFind(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_PATHFIND, pParent)
{

}

CPathFind::~CPathFind()
{
}

void CPathFind::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(CPathFind, CDialog)
    ON_BN_CLICKED(IDC_BUTTON1, &CPathFind::OnSaveData)
    ON_BN_CLICKED(IDC_BUTTON2, &CPathFind::OnLoadData)
    ON_LBN_SELCHANGE(IDC_LIST1, &CPathFind::OnListBox)
    ON_WM_DESTROY()
    ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CPathFind 메시지 처리기


void CPathFind::OnSaveData()
{
    wofstream		fout;
    fout.open(L"../Data/ImgPath.txt", ios::out);

    if (!fout.fail())
    {
        for (auto& pImgPath : m_PathInfoList)
        {
            fout << pImgPath->wstrObjKey << L"|" << pImgPath->wstrStateKey << L"|" << pImgPath->iCount << L"|" << pImgPath->wstrPath << endl;
        }

        fout.close();
    }

    WinExec("notepad.exe ../Data/ImgPath.txt", SW_SHOW);
}


void CPathFind::OnLoadData()
{

    UpdateData(TRUE);

    wifstream	fin;
    fin.open(L"../Data/ImgPath.txt", ios::in);

    if (!fin.fail())
    {
        TCHAR		szObjKey[MAX_STR] = L"";
        TCHAR		szStateKey[MAX_STR] = L"";
        TCHAR		szCount[MAX_STR] = L"";
        TCHAR		szPath[MAX_PATH] = L"";


        wstring		wstrCombined = L"";

        m_ListBox.ResetContent();

        while (true)
        {
            fin.getline(szObjKey, MAX_STR, '|');
            fin.getline(szStateKey, MAX_STR, '|');
            fin.getline(szCount, MAX_STR, '|');
            fin.getline(szPath, MAX_PATH);

            if (fin.eof())
                break;

            wstrCombined = wstring(szObjKey) + L"|" + szStateKey + L"|" + szCount + L"|" + szPath;

            CTextureMgr::Get_Instance()->Insert_Texture(szPath, TEX_MULTI, szObjKey, szStateKey, _wtoi(szCount));

            m_ListBox.AddString(wstrCombined.c_str());

        }
        fin.close();
    }

    WinExec("notepad.exe ../Data/ImgPath.txt", SW_SHOW);
    UpdateData(FALSE);

}




void CPathFind::OnListBox()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPathFind::OnDestroy()
{
    CDialog::OnDestroy();

    for_each(m_PathInfoList.begin(), m_PathInfoList.end(), CDeleteObj());
    m_PathInfoList.clear();
}


void CPathFind::OnDropFiles(HDROP hDropInfo)
{
    UpdateData(TRUE);

    CDialog::OnDropFiles(hDropInfo);

    TCHAR	szFilePath[MAX_PATH] = L"";

    int		iFileCnt = DragQueryFile(hDropInfo, -1, nullptr, 0);

    for (int i = 0; i < iFileCnt; ++i)
    {
        DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

        CFilePath::DirInfoExtraction(szFilePath, m_PathInfoList);
    }

    m_ListBox.ResetContent();

    wstring	wstrCombined = L"";
    TCHAR	szBuf[MAX_STR] = L"";

    for (auto& pImgPath : m_PathInfoList)
    {
        // _itow_s : 정수를 유니코드 문자열로 전환
        //	숫자 10은 10진수 형태로 변환하는 것을 의미
        _itow_s(pImgPath->iCount, szBuf, 10);

        wstrCombined = pImgPath->wstrObjKey + L"|" + pImgPath->wstrStateKey + L"|" + szBuf + L"|" + pImgPath->wstrPath;

        m_ListBox.AddString(wstrCombined.c_str());
    }


    UpdateData(FALSE);
}
