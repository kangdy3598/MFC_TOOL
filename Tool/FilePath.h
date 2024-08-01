#pragma once

#include "Include.h"

class CFilePath
{
public:
	CFilePath();
	~CFilePath();

public:
	static CString	ConvertRelativePath(CString strFullPath);
};

