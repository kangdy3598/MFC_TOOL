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
	LPDIRECT3DTEXTURE9		pTexture;   // �� ��ü

	D3DXIMAGE_INFO			tImgInfo;	// ����ü

}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;			// Ÿ���� ���� ��ǥ
	D3DXVECTOR2 vSize;			// Ÿ���� ����, ���� ������

	BYTE		byOption;		// 0, 1��(��ֹ�)
	BYTE		byDrawID;		// �� �� Ÿ�� �̹���

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
	//int			iIndex = 0;			// ���� Ÿ�� �ε��� ����
	//int			iParentIdx = 0;		// ���� Ÿ�� �ε��� ����

}TILE;

typedef	struct tagUnitData
{
#ifndef _AFX
	wstring	strName;
	wstring	strPathName;
	
#else
	CString	strName;
	CString	strPathName;
	
#endif


	int		iHP;
	int		iAttack;

	BYTE	byUnitType;		// byJobIndex;
	BYTE	byAttackType;	// byItem;

}UNITDATA;

typedef	struct tagBuildingData
{
#ifndef _AFX
	wstring	strName;
	wstring strImgPath;
	wString strKeyName;
#else
	CString	strName;
	CString strImgPath;
	CString strKeyName;
#endif

	D3DXVECTOR3	vPos;			// ���� ��ǥ
	D3DXVECTOR2 vSize;			// ����, ���� ������

	int		iHP;
	int		iShield;
	int		iAttack;

	BYTE	byBuildRace;		// byJobIndex;
	BYTE	byAttackType;	// byItem;

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
	float		fFrame; // �������� ���� ���� ����
	float		fMax;	// �ִ� �̹����� ������ ��

}FRAME;


static D3DXVECTOR3		Get_Mouse()
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3((float)Pt.x, (float)Pt.y, 0.f);
}