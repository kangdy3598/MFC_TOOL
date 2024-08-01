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

	// GetCurrentDirectory : ���� ������Ʈ�� �ִ� ���� ��θ� ������ �Լ�

	GetCurrentDirectory(MAX_PATH, szDirPath);

	// PathRelativePathTo : szDirPath ���� strFullPath ���� ��� ��θ� ���ؼ� szRelativePath�� ����
	// ��, ���� ����̺� �ȿ����� ������ ����

	PathRelativePathTo(szRelativePath,
		szDirPath, FILE_ATTRIBUTE_DIRECTORY,
		strFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelativePath);
}
