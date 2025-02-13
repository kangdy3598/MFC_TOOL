#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vSize;

	D3DXMATRIX		matWorld;

}INFO;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // 컴 객체

	D3DXIMAGE_INFO			tImgInfo;	// 구조체

}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;			// 타일의 중점 좌표
	D3DXVECTOR2 vSize;			// 타일의 가로, 세로 사이즈

	BYTE		byOption;		// 0, 1번(장애물)
	BYTE		byDrawID;		// 몇 번 타일 이미지

public:
	void SetDrawID()
	{
		byDrawID++;
		if (byDrawID == MAX_TILETYPE)
			byDrawID = 0;
	}
	void SetDrawID(int _ID)
	{
		if (_ID >= MAX_TILETYPE)
			return;
		byDrawID = _ID;
	}

	int			iIndex = 0;			// 현재 타일 인덱스 정보
	int			iParentIdx = 0;		// 이전 타일 인덱스 정보

}TILE;



typedef struct tagUnit
{
	D3DXVECTOR3	vPos;
	D3DXVECTOR3 vSize;

	BYTE		byUnitType;
	BYTE		byAttackType;

public:
	void SetUnitType()
	{
		byUnitType++;
	}
	void SetUnitType(int _UnitType)
	{
		byUnitType = _UnitType;
	}


}UNITCLASS;






typedef	struct tagUnitData
{
//#ifndef _AFX
//	wstring	strName;
//	wstring	strPathName;
//	
//#else
//	CString	strName;
//	CString	strPathName;
//	
//#endif
//
//
//	int		iHP;
//	int		iAttack;
//
//	BYTE	byUnitType;		// byJobIndex;
//	BYTE	byAttackType;	// byItem;

#ifndef _AFX
	wstring	strName;
	wstring strImgPath;
	wstring strKeyName;
#else
	CString	strName;
	CString strImgPath;
	CString strKeyName;
#endif

	D3DXVECTOR3	vPos;			// 중점 좌표
	D3DXVECTOR2 vSize;			// 가로, 세로 사이즈

	int		iHP;
	int		iShield;
	int		iAttack;

	BYTE	byUnitRace;		// byJobIndex;
	BYTE	byAttackType;	// byItem;

}UNITDATA;

typedef	struct tagBuildingData
{
#ifndef _AFX
	wstring	strName;
	wstring strImgPath;
	wstring strKeyName;
#else
	CString	strName;
	CString strImgPath;
	CString strKeyName;
#endif

	D3DXVECTOR3	vPos;			// 중점 좌표
	D3DXVECTOR2 vSize;			// 가로, 세로 사이즈

	int		iHP;
	int		iShield;
	int		iAttack;

	BYTE	byBuildRace;		// byJobIndex;
	BYTE	byAttackType;		// byItem;

}BUILDINGDATA;

typedef struct tagTexturePath
{
	wstring		wstrObjKey		= L"";
	wstring		wstrStateKey	= L"";
	wstring		wstrPath		= L"";
	int			iCount			= 0;

}IMGPATH;

typedef	struct tagFrame
{
	float		fFrame; // 프레임을 세기 위한 변수
	float		fMax;	// 최대 이미지의 프레임 수

}FRAME;


static D3DXVECTOR3		Get_Mouse()
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3((float)Pt.x, (float)Pt.y, 0.f);
}