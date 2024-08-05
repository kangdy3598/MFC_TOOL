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

void CFilePath::DirInfoExtraction(const wstring& wstrPath, list<IMGPATH*>& rPathInfoList)
{
	CFileFind			Find;

	wstring		wstrFilePath = wstrPath + L"\\*.*";

	// FindFile : �־��� ��ο� ������ ������ �Ǵ��ϴ� �Լ�, ������ ������ false, ������ true

	BOOL		bContinue = Find.FindFile(wstrFilePath.c_str());

	while (bContinue)
	{
		// FindNextFile : ���� ��� �ȿ��� ���� ������ ã��. ���̻� ã���� ���ų� ������ ������ ��� 0�� ����
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
			//szPathBuf = 0x005adce0 L"D:\\����ȯ\\148��\\Frame148\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack0.png"

			PathRemoveFileSpec(szPathBuf);
			// szPathBuf = 0x005adce0 L"D:\\����ȯ\\148��\\Frame148\\Texture\\Stage\\Effect\\BossMultiAttack"

			pImgPath->iCount = DirFileCount(szPathBuf);

			// GetFileTitle : ���� �̸��� ������ �Լ�
			wstring			wstrTextureName = Find.GetFileTitle().GetString();
			//wstrTextureName = L"BossMultiAttack0"

			// substr(����, ��) : ���ۿ��� ������ �ش��ϴ� ���ڿ��� ����
			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + L"%d.png";

			// PathCombine :��θ� �����ϴ� �Լ�
			PathCombine(szPathBuf, szPathBuf, wstrTextureName.c_str());
			//szPathBuf = 0x00efe038 L"D:\\����ȯ\\148��\\Frame148\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack%d.png"

			pImgPath->wstrPath = ConvertRelativePath(szPathBuf);
			// pImgPath->wstrPath = L"..\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack%d.png"

			PathRemoveFileSpec(szPathBuf);
			// pImgPath->wstrPath = L"..\\Texture\\Stage\\Effect\\BossMultiAttack

			// PathFindFileName : ���� �̸��� ã�ų� ���� ������ ���� �̸��� ã�Ƴ�
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
