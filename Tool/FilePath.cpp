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
