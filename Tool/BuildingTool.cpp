// BuildingTool.cpp: 구현 파일
//
#include "stdafx.h"
#include "BuildingTool.h"

#include "Tool.h"
#include "afxdialogex.h"

#include "Device.h"
#include "FilePath.h"
#include "TextureMgr.h"
#include "MainFrm.h"
#include "MyFormView.h"


// CBuilding 대화 상자

IMPLEMENT_DYNAMIC(CBuildingTool, CDialog)

CBuildingTool::CBuildingTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_BuildingTool, pParent)
	, m_strName(_T(""))
	, m_iHP(0)
	, m_iShield(0)
	, m_iAttack(0)
{

}

CBuildingTool::~CBuildingTool()
{
}

void CBuildingTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_iHP);
	DDX_Text(pDX, IDC_EDIT3, m_iShield);
	DDX_Text(pDX, IDC_EDIT5, m_iAttack);

	DDX_Control(pDX, IDC_RADIO1, m_radioBuildingRace[0]);
	DDX_Control(pDX, IDC_RADIO2, m_radioBuildingRace[1]);
	DDX_Control(pDX, IDC_RADIO3, m_radioBuildingRace[2]);

	DDX_Control(pDX, IDC_CHECK1, m_checkAttackType[0]);
	DDX_Control(pDX, IDC_CHECK2, m_checkAttackType[1]);

	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Text(pDX, IDC_EDIT4, m_strSearchName);
	DDX_Control(pDX, IDC_EDIT4, m_searchName);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
}


BEGIN_MESSAGE_MAP(CBuildingTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CBuildingTool::OnBnClickedCreate)
	ON_BN_CLICKED(IDC_BUTTON4, &CBuildingTool::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BUTTON5, &CBuildingTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON1, &CBuildingTool::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BUTTON3, &CBuildingTool::OnBnClickedShowAll)
	ON_LBN_SELCHANGE(IDC_LIST1, &CBuildingTool::OnLbnSelchange)
	ON_BN_CLICKED(IDC_BUTTON6, &CBuildingTool::OnBnClickedChangeImage)
END_MESSAGE_MAP()


// CBuilding 메시지 처리기


BOOL CBuildingTool::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_radioBuildingRace[1].SetCheck(true);
	OnDataLoad();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBuildingTool::OnBnClickedCreate()
{
	UpdateData(TRUE);

	BUILDINGDATA* pBuilding = new BUILDINGDATA;

	pBuilding->strName = m_strName;
	m_strName = L"";

	pBuilding->iHP = m_iHP;
	m_iHP = 0;

	pBuilding->iShield = m_iShield;
	m_iShield = 0;

	pBuilding->iAttack = m_iAttack;
	m_iAttack = 0;

	//byBuildingRace
	for (int i = 0; i < 3; ++i)
	{
		if (m_radioBuildingRace[i].GetCheck())
		{
			pBuilding->byBuildRace = i;
			break;
		}
	}
	m_radioBuildingRace[1].SetCheck(true);

	//btAttackType
	pBuilding->byAttackType = 0x00;

	if (m_checkAttackType[0].GetCheck())
		pBuilding->byAttackType |= ATTACK_GROUND;

	if (m_checkAttackType[1].GetCheck())
		pBuilding->byAttackType |= ATTACK_SKY;

	pBuilding->byAttackType = 0x00;
	// image

	pBuilding->strImgPath = m_strFullPath;
	pBuilding->strKeyName = m_strKeyName;

	m_ListBox.AddString(pBuilding->strName);

	m_mapBuildingData.insert({ pBuilding->strName, pBuilding });

	m_picture.SetBitmap(nullptr);
	UpdateData(FALSE);
}

void CBuildingTool::OnBnClickedDelete()
{
	UpdateData(TRUE);

	int	iIndex = m_ListBox.GetCurSel();
	if (LB_ERR == iIndex)
		return;

	CString		strFindName;
	m_ListBox.GetText(iIndex, strFindName);

	auto iter = m_mapBuildingData.find(strFindName);
	if (iter == m_mapBuildingData.end())
		return;

	m_ListBox.DeleteString(iIndex);

	Safe_Delete(iter->second);
	m_mapBuildingData.erase(iter);

	UpdateData(FALSE);
}

void CBuildingTool::OnBnClickedSave()
{
	CFileDialog Dlg(FALSE,	
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | 
		OFN_OVERWRITEPROMPT, 
		L"Data File(*.dat) | *.dat||",
		this); 

	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (Dlg.DoModal())
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
		for (auto& rPair : m_mapBuildingData)
		{
			dwStringSize = sizeof(wchar_t) * (rPair.second->strName.GetLength() + 1);
			WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, rPair.second->strName.GetString(), dwStringSize, &dwByte, nullptr);
			
			WriteFile(hFile, &rPair.second->iHP, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->iAttack, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->iShield, sizeof(int), &dwByte, nullptr);

			WriteFile(hFile, &rPair.second->byBuildRace, sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->byAttackType, sizeof(BYTE), &dwByte, nullptr);

			dwStringSize = sizeof(wchar_t) * (rPair.second->strImgPath.GetLength() + 1);
			WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, rPair.second->strImgPath.GetString(), dwStringSize, &dwByte, nullptr);

			dwStringSize = sizeof(wchar_t) * (rPair.second->strKeyName.GetLength() + 1);
			WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, rPair.second->strKeyName.GetString(), dwStringSize, &dwByte, nullptr);

		}
		CloseHandle(hFile);
	}
}

void CBuildingTool::OnBnClickedSearch()
{
	UpdateData(TRUE);

	if (m_strSearchName == "")
		return;

	auto iter = m_mapBuildingData.find(m_strSearchName);
	if (iter == m_mapBuildingData.end())
		return;

	m_ListBox.ResetContent();

	m_ListBox.AddString(m_strSearchName);

	UpdateData(FALSE);
}

void CBuildingTool::OnBnClickedShowAll()
{
	m_ListBox.ResetContent();
	for (auto iter : m_mapBuildingData)
	{
		m_ListBox.AddString(iter.first);
	}
}

void CBuildingTool::OnLbnSelchange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString		strFindName;

	int	iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	m_ListBox.GetText(iIndex, strFindName);

	auto iter = m_mapBuildingData.find(strFindName);

	if (iter == m_mapBuildingData.end())
		return;

	m_tSelectBuildingData = (*iter).second;

	m_strName = m_tSelectBuildingData->strName;
	m_iHP = m_tSelectBuildingData->iHP;
	m_iShield = m_tSelectBuildingData->iShield;
	m_iAttack = m_tSelectBuildingData->iAttack;

	for (int i = 0; i < 2; i++)
		m_radioBuildingRace[i].SetCheck(false);

	m_radioBuildingRace[m_tSelectBuildingData->byBuildRace].SetCheck(true);

	for (int i = 0; i < 2; i++)
	{
		m_checkAttackType[i].SetCheck(
			(m_tSelectBuildingData->byAttackType & (1 << i)) != 0
		);
	}
	
	CImage* pImage = new CImage;
	pImage->Load(m_tSelectBuildingData->strImgPath);

	m_picture.SetBitmap((HBITMAP)*pImage);

	UpdateData(FALSE);
}

void CBuildingTool::OnDataLoad()
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
		for (auto& MyPair : m_mapBuildingData)
			delete MyPair.second;

		m_mapBuildingData.clear();

		// ResetContent : 리스트 박스 목록 초기화
		m_ListBox.ResetContent();

		CString	str = Dlg.GetPathName().GetString();

		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte(0);
		DWORD	dwStrByte(0);
		BUILDINGDATA tData{};

		CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
		CToolView* pToolView = pMainFrm->GetToolView();

		HTREEITEM building = pToolView->Get_MyView()->building;
		while (true)
		{
			//ReadFile(hFile, &(tData.vSize), sizeof(int), &dwByte, nullptr);

			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			TCHAR* pName = new TCHAR[dwStrByte / 2];
			ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);
			if (0 == dwByte) { delete[]pName; break; }

			//////////////////////////////////////////////////////////////////
			ReadFile(hFile, &(tData.iHP), sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &(tData.iAttack), sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &(tData.iShield), sizeof(int), &dwByte, nullptr);

			ReadFile(hFile, &(tData.byBuildRace), sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &(tData.byAttackType), sizeof(BYTE), &dwByte, nullptr);

			//////////////////////////////////////////////////////////////////
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			TCHAR* pPath = new TCHAR[dwStrByte / 2];
			ReadFile(hFile, pPath, dwStrByte, &dwByte, nullptr);
			if (0 == dwByte) { delete[]pPath; break; }

			//////////////////////////////////////////////////////////////////
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			TCHAR* pKey = new TCHAR[dwStrByte / 2];
			ReadFile(hFile, pKey, dwStrByte, &dwByte, nullptr);
			if (0 == dwByte) { delete[]pKey; break; }

			BUILDINGDATA* pBuilding = new BUILDINGDATA;

			pBuilding->strName = pName;
			delete[]pName;

			pBuilding->strImgPath = pPath;
			delete[]pPath;

			pBuilding->strKeyName = pKey;
			delete[]pKey;

			pBuilding->iHP = tData.iHP;
			pBuilding->iAttack = tData.iAttack;
			pBuilding->iShield = tData.iShield;
			pBuilding->byBuildRace = tData.byBuildRace;
			pBuilding->byAttackType = tData.byAttackType;

			m_mapBuildingData.insert({ pBuilding->strName, pBuilding });

			m_ListBox.AddString(pBuilding->strName);

			if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
				pBuilding->strImgPath, TEX_MULTI, L"Building",
				pBuilding->strKeyName, MAX_TILETYPE)))
			{
				AfxMessageBox(L"Building Texture Failed");
				return;
			}

			pToolView->Get_MyView()->m_tree.InsertItem(
				pBuilding->strName, 0, 0, building, TVI_LAST);
		}
		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}

void CBuildingTool::OnBnClickedChangeImage()
{
	UpdateData(TRUE);
	CFileDialog		Dlg(TRUE,	// TRUE(불러오기), FALSE(다른 이름으로 저장)
		L"png", // default 확장자명
		L"*.png", // 대화 상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(일기 전용 체크박스 숨김 옵션), OFN_OVERWRITEPROMPT(중복 파일 저장 시, 경고 메시지 띄움 옵션)
		L"이미지 파일(*.jpg, *.png)|*jpg;*.jpeg;*png||", // 콤보 박스에 출력될 문자열
		this);	// 부모 윈도우 주소
	
	TCHAR		szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath); // D:\유준환\148기\Frame148\Tool
	PathRemoveFileSpec(szPath); // D:\유준환\148기\Frame148\

	lstrcat(szPath, L"\\Texture\\MultiTexture\\Build\\Protoss\\");
	
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CString	str = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();
		
		HANDLE hFile = CreateFile(pGetPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		
		CloseHandle(hFile); // 파일 스트림 닫고 경로를 저장한 변수를 Load할 것!!

		CImage* pImage = new CImage;
		pImage->Load(str);
		
		m_picture.SetBitmap((HBITMAP)*pImage);

		m_strFullPath = str; // "C:\\ ~~~ Gateway\\0.png"

		str.Replace(szPath, L"");	// "Gateway\\0.png"	
		str.Replace(L"\\" + Dlg.GetFileName(), L""); // Gateway
		m_strKeyName = str;

		if (m_tSelectBuildingData)
		{
			m_tSelectBuildingData->strImgPath = m_strFullPath;
			m_tSelectBuildingData->strKeyName = m_strKeyName;
		}

	}

	UpdateData(FALSE);
}
