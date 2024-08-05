#include "stdafx.h"
#include "FilePath.h"


CFilePath::CFilePath()
{
}


CFilePath::~CFilePath()
{
}

CString CFilePath::ConvertRelativePath(CString strFullPath)
{
	TCHAR	szRelativePath[MAX_PATH] = L"";
	TCHAR	szDirPath[MAX_PATH] = L"";

	// GetCurrentDirectory : 현재 프로젝트가 있는 절대 경로를 얻어오는 함수

	GetCurrentDirectory(MAX_PATH, szDirPath);

	// PathRelativePathTo : szDirPath 에서 strFullPath 가는 상대 경로를 구해서 szRelativePath에 저장
	// 단, 같은 드라이블 안에서만 변경이 가능

	PathRelativePathTo(szRelativePath,
		szDirPath, FILE_ATTRIBUTE_DIRECTORY,
		strFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelativePath);
}

void CFilePath::DirInfoExtraction(const wstring& wstrPath, list<IMGPATH*>& rPathInfoList)
{
	CFileFind			Find;

	wstring		wstrFilePath = wstrPath + L"\\*.*";

	// FindFile : 주어진 경로에 파일의 유무를 판단하는 함수, 파일이 없으면 false, 있으면 true

	BOOL		bContinue = Find.FindFile(wstrFilePath.c_str());

	while (bContinue)
	{
		// FindNextFile : 동일 경로 안에서 다음 파일을 찾음. 더이상 찾을게 없거나 마지막 파일인 경우 0을 리턴
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		else if (Find.IsDirectory())
		{
			DirInfoExtraction(wstring(Find.GetFilePath()), rPathInfoList);
		}

		else
		{
			if (Find.IsSystem())
				continue;


			IMGPATH* pImgPath = new IMGPATH;
			TCHAR		szPathBuf[MAX_STR] = L"";

			lstrcpy(szPathBuf, Find.GetFilePath().GetString());
			//szPathBuf = 0x005adce0 L"D:\\유준환\\148기\\Frame148\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack0.png"

			PathRemoveFileSpec(szPathBuf);
			// szPathBuf = 0x005adce0 L"D:\\유준환\\148기\\Frame148\\Texture\\Stage\\Effect\\BossMultiAttack"

			pImgPath->iCount = DirFileCount(szPathBuf);

			// GetFileTitle : 파일 이름만 얻어오는 함수
			wstring			wstrTextureName = Find.GetFileTitle().GetString();
			//wstrTextureName = L"BossMultiAttack0"

			// substr(시작, 끝) : 시작에서 끝까지 해당하는 문자열을 얻어옴
			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + L"%d.png";

			// PathCombine :경로를 결합하는 함수
			PathCombine(szPathBuf, szPathBuf, wstrTextureName.c_str());
			//szPathBuf = 0x00efe038 L"D:\\유준환\\148기\\Frame148\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack%d.png"

			pImgPath->wstrPath = ConvertRelativePath(szPathBuf);
			// pImgPath->wstrPath = L"..\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack%d.png"

			PathRemoveFileSpec(szPathBuf);
			// pImgPath->wstrPath = L"..\\Texture\\Stage\\Effect\\BossMultiAttack

			// PathFindFileName : 파일 이름을 찾거나 가장 마지막 폴더 이름을 찾아냄
			pImgPath->wstrStateKey = PathFindFileName(szPathBuf);

			PathRemoveFileSpec(szPathBuf);

			pImgPath->wstrObjKey = PathFindFileName(szPathBuf);

			rPathInfoList.push_back(pImgPath);

			bContinue = 0;
		}
	}
}

int CFilePath::DirFileCount(const wstring& wstrPath)
{
	CFileFind			Find;

	wstring		wstrFilePath = wstrPath + L"\\*.*";

	BOOL		bContinue = Find.FindFile(wstrFilePath.c_str());

	int iFileCnt(0);

	while (bContinue)
	{

		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		if (Find.IsSystem())
			continue;

		++iFileCnt;
	}
	return iFileCnt;
}
