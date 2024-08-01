#include "stdafx.h"
#include "SingleTexture.h"
#include "Device.h"

CSingleTexture::CSingleTexture()
	: m_pTexInfo(nullptr)
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

HRESULT CSingleTexture::Insert_Texture(const TCHAR * pFilePath, 
	const TCHAR * pStateKey , 
	const int & iCnt)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	if (FAILED(D3DXGetImageInfoFromFile(pFilePath, &(m_pTexInfo->tImgInfo))))
	{
		Safe_Delete(m_pTexInfo);
		AfxMessageBox(L"D3DXGetImageInfoFromFile Failed");
		return E_FAIL;
	}

	// D3DPOOL_DEFAULT : ���� ������ �޸𸮿� ����, ���� �׷��� ī�� �޸𸮸� ����
	// D3DPOOL_MANAGED : �׷��� �޸𸮸� ��������� �̸� RAM�� ���
	// 
	// D3DPOOL_SYSTEMMEM : ���� �޸�(RAM)�� ����
	// D3DPOOL_SCRATCH : �ý��� �޸𸮿� ���������� DX ��ġ�� ���� �Ұ�

	if (FAILED(D3DXCreateTextureFromFileEx(CDevice::Get_Instance()->Get_Device(),
		pFilePath,
		m_pTexInfo->tImgInfo.Width,
		m_pTexInfo->tImgInfo.Height,
		m_pTexInfo->tImgInfo.MipLevels,
		0,	// D3DUSAGE_RENDERTARGET : ȭ�� ��¿� �ؽ�ó ���� �� �ɼ�
		m_pTexInfo->tImgInfo.Format,
		D3DPOOL_MANAGED, 
		D3DX_DEFAULT, // �̹��� ���͸� ���
		D3DX_DEFAULT, // MIP���� ���
		0,				// ������ ����, 0�� ������ ���� �÷�Ű ��ȿȭ
		nullptr,		// �̹��� ������� (m_pTexInfo->tImgInfo ������ �̹� �־��ְ� ����)
		nullptr,		// �ȷ�Ʈ �̹��� ������ �о���� ����ü �ּ�
		&(m_pTexInfo->pTexture))))
	{
		Safe_Delete(m_pTexInfo);
		AfxMessageBox(L"Single Texture Create Failed");
		return E_FAIL;
	}

	return S_OK;
}

void CSingleTexture::Release()
{
	Safe_Release(m_pTexInfo->pTexture);
	Safe_Delete(m_pTexInfo);
}
