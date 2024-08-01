// TileTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"

#include "TextureMgr.h"
#include "TileTool.h"
#include "FilePath.h"

// CTileTool 대화 상자

IMPLEMENT_DYNAMIC(CTileTool, CDialog)

CTileTool::CTileTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TileTool, pParent), m_iTileNum(0)
{
}

CTileTool::~CTileTool()
{
}

void CTileTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
}


BEGIN_MESSAGE_MAP(CTileTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CTileTool::OnListBoxSelChange)

END_MESSAGE_MAP()


// CTileTool 메시지 처리기


void CTileTool::OnDropFiles(HDROP hDropInfo)
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

void CTileTool::OnListBoxSelChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString		strFindName;

	int	iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	m_ListBox.GetText(iIndex, strFindName);

	auto iter = m_MapPngImg.find(strFindName);

	if (iter == m_MapPngImg.end())
		return;

	m_picture.SetBitmap(*(iter->second));

	int i(0);

	for (; i < strFindName.GetLength(); ++i)
	{
		// isdigit : 매개 변수로 전달받은 글자가 단일 문자인지 아니면 숫자 형태의 문자인지 구별하는 함수
		// 숫자 형태의 문자로 판명될 경우 0이 아닌 값을 리턴

		if (0 != isdigit(strFindName[i]))
			break;
	}
	// Delete(index, count) : 인덱스 위치로부터 카운트만큼 문자를 모두 삭제하는 함수
	strFindName.Delete(0, i);

	// _tstoi : 유니코드 문자열을 정수형으로 변환하는 함수
	m_iTileNum = _tstoi(strFindName);

	UpdateData(FALSE);
}

BOOL CTileTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateData(TRUE);
	
	//for (auto& MyPair : m_MapPngImg)
	//	delete MyPair.second;

	//m_MapPngImg.clear();

	//m_ListBox.ResetContent();

	CString path, fileName;
	path = L"..\\Texture\\Stage\\Terrain\\Tile\\";
	for (int i = 0; i < 36; i++)
	{
		CImage* pPngImage = new CImage;
		
		fileName.Format(L"Tile%d.png", i);
		pPngImage->Load(path + fileName);

		m_MapPngImg.insert( {fileName, pPngImage } );
		m_ListBox.AddString(fileName);
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


