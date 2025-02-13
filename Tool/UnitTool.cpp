﻿// UnitTool.cpp: 구현 파일
//

#include "stdafx.h"

#include "Tool.h"
#include "afxdialogex.h"
#include "UnitTool.h"

#include "MainFrm.h"
#include "FilePath.h"

#include "MyFormView.h"
    
#include "PathFind.h"


// CUnitTool 대화 상자

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_UnitTool, pParent)
    , m_iAttack(0)
    , m_iHP(0)
    , m_strSearchName(_T(""))
    , m_bSelected(false)
    , m_stateNameKey(_T(""))
{

}

CUnitTool::~CUnitTool()
{
}

CUnit* CUnitTool::Create_Unit(CPoint _pos, int _iUnitIndex)
{
    CUnit* pUnit = new CUnit;

    _pos.x = LONG(Get_Mouse().x);
    _pos.y = LONG(Get_Mouse().y);

    _iUnitIndex = iIndex;

    pUnit->Set_Pos(_pos);

    return pUnit;
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, m_strName);
    DDX_Text(pDX, IDC_EDIT2, m_iHP);
    DDX_Text(pDX, IDC_EDIT3, m_iAttack);

    DDX_Control(pDX, IDC_RADIO1, m_radioUnitType[0]);
    DDX_Control(pDX, IDC_RADIO2, m_radioUnitType[1]);
    DDX_Control(pDX, IDC_CHECK1, m_checkAttackType[0]);
    DDX_Control(pDX, IDC_CHECK2, m_checkAttackType[1]);
    DDX_Control(pDX, IDC_LIST1, m_ListBox);
    DDX_Text(pDX, IDC_EDIT4, m_strSearchName);
    DDX_Control(pDX, IDC_EDIT4, m_searchName);

    DDX_Control(pDX, IDC_PICTURE, m_Picture);
    DDX_Text(pDX, IDC_EDIT5, m_stateNameKey);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
    ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnBnClickedCreate)
    ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnBnClickedDelete)
    ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedSearch)
    ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnBnClickedShowAll)
    ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnBnClickedSave)
    ON_BN_CLICKED(IDC_BUTTON6, &CUnitTool::OnBnClickedLoad)
    ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnListBoxSelChange)
    ON_BN_CLICKED(IDOK, &CUnitTool::OnBnClickedOk)
END_MESSAGE_MAP()


// CUnitTool 메시지 처리기


void CUnitTool::OnBnClickedCreate()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    UpdateData(TRUE);

    UNITDATA* pUnit = new UNITDATA;

    pUnit->strName = m_strName;
    pUnit->iHP = m_iHP;
    pUnit->iAttack = m_iAttack;

    //byUnitType
    for (int i = 0; i < 2; ++i)
    {
        if (m_radioUnitType[i].GetCheck())
        {
            pUnit->byUnitRace = i;
            break;
        }
    }

    //btAttackType
    pUnit->byAttackType = 0x00;

    if (m_checkAttackType[0].GetCheck())
        pUnit->byAttackType |= ATTACK_GROUND;

    if (m_checkAttackType[1].GetCheck())
        pUnit->byAttackType |= ATTACK_SKY;

    CFileDialog		Dlg(TRUE,	// TRUE(불러오기), FALSE(다른 이름으로 저장)
        L"png", // default 확장자명
        L"*.png", // 대화 상자에 표시될 최초 파일명
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(일기 전용 체크박스 숨김 옵션), OFN_OVERWRITEPROMPT(중복 파일 저장 시, 경고 메시지 띄움 옵션)
        L"이미지 파일(*.jpg, *.png)|*jpg;*.jpeg;*png||", // 콤보 박스에 출력될 문자열
        this);	// 부모 윈도우 주소

    TCHAR		szPath[MAX_PATH] = L"";
    TCHAR	szFileName[MAX_STR] = L"";

    GetCurrentDirectory(MAX_PATH, szPath);
    PathRemoveFileSpec(szPath);

    lstrcat(szPath, L"..\\Texture\\MultiTexture\\Unit\\Protoss\\");

    Dlg.m_ofn.lpstrInitialDir = szPath;

    if (IDOK == Dlg.DoModal())
    {
        CString	str = Dlg.GetPathName().GetString();
        const TCHAR* pGetPath = str.GetString();

        HANDLE hFile = CreateFile(pGetPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        //m_wstrStateKey = wstring(m_stateNameKey);

        CloseHandle(hFile); // 파일 스트림 닫고 경로를 저장한 변수를 Load할 것!!

        CString	strFileName = PathFindFileName(str);
        lstrcpy(szFileName, strFileName.GetString());
        PathRemoveExtension(szFileName);

        strFileName = szFileName;

        auto iter = m_MapPngUnitImg.find(strFileName);

        if (iter == m_MapPngUnitImg.end())
        {
            CImage* pImage = new CImage;
            pImage->Load(str);

            m_MapPngUnitImg.insert({ m_strName, pImage });
            //m_Picture.SetBitmap((HBITMAP)*pImage);
            CTextureMgr::Get_Instance()->Insert_Texture(str, TEX_MULTI,
                L"Unit", pUnit->strName, 1);
            
        }
    }

    m_ListBox.AddString(pUnit->strName);
    m_mapUnitData.insert({ pUnit->strName,pUnit });

    UpdateData(FALSE);
}

void CUnitTool::OnBnClickedDelete()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    UpdateData(TRUE);

    CString		strFindName;

    // GetCurSel :리스트 박스 목록 중, 선택된 셀의 인덱스를 반환
    /* int	*/ iIndex = m_ListBox.GetCurSel();

    if (LB_ERR == iIndex)
        return;

    // GetText : index에 해당하는 리스트 박스 문자열을 얻어옴
    m_ListBox.GetText(iIndex, strFindName);

    auto iter = m_mapUnitData.find(strFindName);

    if (iter == m_mapUnitData.end())
        return;

    m_ListBox.DeleteString(iIndex);

    Safe_Delete(iter->second);
    m_mapUnitData.erase(iter);

    UpdateData(FALSE);
}

void CUnitTool::OnBnClickedSearch()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    UpdateData(TRUE);

    if (m_strSearchName == "")
        return;

    auto iter = m_mapUnitData.find(m_strSearchName);

    if (iter == m_mapUnitData.end())
        return;

    m_ListBox.ResetContent();

    m_ListBox.AddString(m_strSearchName);

    UpdateData(FALSE);
}

void CUnitTool::OnBnClickedShowAll()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_ListBox.ResetContent();
    for (auto iter : m_mapUnitData)
    {
        m_ListBox.AddString(iter.first);
    }
}

void CUnitTool::OnBnClickedSave()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CFileDialog Dlg(FALSE,		// 불러오기(true) , 다름이름으로저장(false)
        L"dat",
        L"*.dat",
        OFN_HIDEREADONLY | // 읽기 전용 체크박스 숨김
        OFN_OVERWRITEPROMPT, // 중복 저장 경고 
        L"Data File(*.dat) | *.dat||", // 콤보 박스에 출력될 문자열
        this); // 부모 윈도우 주소

    TCHAR szPath[MAX_PATH] = L"";

    // 프로젝트 파일까지의 경로를 받아오는 함수
    GetCurrentDirectory(MAX_PATH, szPath);

    // 전체 경로중 파일 이름만 잘라내는 함수
    PathRemoveFileSpec(szPath);

    lstrcat(szPath, L"\\Data");

    Dlg.m_ofn.lpstrInitialDir = szPath;

    if (Dlg.DoModal()) // 창이 프로세스를 점유하는 방식 : 모달 / 아닌거 : 모달리스
    {
        CString wstrFilePath = Dlg.GetPathName();
        HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (INVALID_HANDLE_VALUE == hFile)
        {
            ERR_MSG(L"파일 개방 실패.");
            return;
        }
        DWORD dwByte = 0;
        DWORD dwStringSize = 0;
        for (auto& rPair : m_mapUnitData)
        {
            dwStringSize = sizeof(wchar_t) * (rPair.second->strName.GetLength() + 1);
            WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
            WriteFile(hFile, rPair.second->strName.GetString(), dwStringSize, &dwByte, nullptr);
            WriteFile(hFile, &rPair.second->iHP, sizeof(int), &dwByte, nullptr);
            WriteFile(hFile, &rPair.second->iAttack, sizeof(int), &dwByte, nullptr);
            WriteFile(hFile, &rPair.second->byUnitRace, sizeof(BYTE), &dwByte, nullptr);
            WriteFile(hFile, &rPair.second->byAttackType, sizeof(BYTE), &dwByte, nullptr);
        }
        CloseHandle(hFile);
    }
}

void CUnitTool::OnBnClickedLoad()
{
    UpdateData(TRUE);
    CFileDialog		Dlg(TRUE,	// TRUE(불러오기), FALSE(다른 이름으로 저장)
        L"dat", // default 확장자명
        L"*.dat", // 대화 상자에 표시될 최초 파일명
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(일기 전용 체크박스 숨김 옵션), OFN_OVERWRITEPROMPT(중복 파일 저장 시, 경고 메시지 띄움 옵션)
        L"Data Files(*.dat)|*.dat||", // 콤보 박스에 출력될 문자열
        this);	// 부모 윈도우 주소


    TCHAR		szPath[MAX_PATH] = L"";

    GetCurrentDirectory(MAX_PATH, szPath);

    PathRemoveFileSpec(szPath);

    lstrcat(szPath, L"\\Data");

    Dlg.m_ofn.lpstrInitialDir = szPath;

    if (IDOK == Dlg.DoModal())
    {
        for (auto& MyPair : m_mapUnitData)
            delete MyPair.second;

        m_mapUnitData.clear();

        // ResetContent : 리스트 박스 목록 초기화
        m_ListBox.ResetContent();

        CString	str = Dlg.GetPathName().GetString();

        const TCHAR* pGetPath = str.GetString();

        HANDLE hFile = CreateFile(pGetPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        DWORD	dwByte(0);
        DWORD	dwStrByte(0);
        UNITDATA tData{};

        while (true)
        {
            ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

            TCHAR* pName = new TCHAR[dwStrByte / 2];
            ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);

            ReadFile(hFile, &(tData.iHP), sizeof(int), &dwByte, nullptr);
            ReadFile(hFile, &(tData.iAttack), sizeof(int), &dwByte, nullptr);
            ReadFile(hFile, &(tData.byUnitRace), sizeof(BYTE), &dwByte, nullptr);
            ReadFile(hFile, &(tData.byAttackType), sizeof(BYTE), &dwByte, nullptr);

            if (0 == dwByte)
            {
                delete[]pName;
                break;
            }

            UNITDATA* pUnit = new UNITDATA;

            pUnit->strName = pName;
            delete[]pName;

            pUnit->iHP = tData.iHP;
            pUnit->iAttack = tData.iAttack;
            pUnit->byUnitRace = tData.byUnitRace;
            pUnit->byAttackType = tData.byAttackType;

            m_mapUnitData.insert({ pUnit->strName, pUnit });

            m_ListBox.AddString(pUnit->strName);
        }

        CloseHandle(hFile);
    }

    UpdateData(FALSE);
}



void CUnitTool::OnListBoxSelChange()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    UpdateData(TRUE);
    CString		strFindName;

    /*int */ iIndex = m_ListBox.GetCurSel();

    if (LB_ERR == iIndex)
        return;

    m_ListBox.GetText(iIndex, strFindName);

    auto iter = m_mapUnitData.find(strFindName);

    if (iter == m_mapUnitData.end())
        return;

    m_strName = iter->second->strName;
    m_iHP = iter->second->iHP;
    m_iAttack = iter->second->iAttack;

    for (int i = 0; i < 2; ++i)
    {
        m_radioUnitType[i].SetCheck(FALSE);
        m_checkAttackType[i].SetCheck(FALSE);
    }

    if (iter->second->byAttackType & ATTACK_GROUND)
        m_checkAttackType[0].SetCheck(TRUE);

    if (iter->second->byAttackType & ATTACK_SKY)
        m_checkAttackType[1].SetCheck(TRUE);


    //m_radioUnitType[iter->second->byUnitType].SetCheck(TRUE);

    //----------------------------------------------------------------

    m_ListBox.GetText(iIndex, strFindName);

    auto iterImage = m_MapPngUnitImg.find(strFindName);

    if (iterImage == m_MapPngUnitImg.end())
        return;

    m_Picture.SetBitmap(*(iterImage->second));

    UpdateData(FALSE);
}



void CUnitTool::OnBnClickedOk()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CDialog::OnOK();

    m_bSelected = true;


    CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
    CToolView* pToolView = pMainFrm->GetToolView();
    HTREEITEM unit = pToolView->Get_MyView()->unit;

    for (auto iter : m_mapUnitData)
    {
        pToolView->Get_MyView()->m_tree.InsertItem(iter.first, 0, 0, unit, TVI_LAST);
    }
}

