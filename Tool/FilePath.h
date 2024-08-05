#pragma once

#include "Include.h"

class CFilePath
{
public:
	CFilePath();
	~CFilePath();

public:
	static CString	ConvertRelativePath(CString strFullPath);


	static void		DirInfoExtraction(const wstring& wstrPath,
		list<IMGPATH*>& rPathInfoList);

	static int		DirFileCount(const wstring& wstrPath);
};

