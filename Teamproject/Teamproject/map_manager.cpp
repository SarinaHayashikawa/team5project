//=============================================================================
//
// �~�j�}�b�v�̏��� [map.cpp]
// Author : �ѐ�ї���
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "map_manager.h"
#include "resource manager.h"
#include "map.h"
#include "locationpoint.h"
#include "game.h"
#include "player.h"
#include "player control.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_LOCATION_VALUE (0.55f) //�}�b�v�\���̌��݈ʒu�␳�l
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapManager::CMapManager(int nPriority) : CScene(nPriority)
{
	m_originPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapManager::~CMapManager()
{

}

//=============================================================================
// ��������
//=============================================================================
CMapManager * CMapManager::Create(D3DXVECTOR3 Pos)
{
	CMapManager *pMap = nullptr;

	pMap = new CMapManager;
	if (pMap != nullptr)
	{
		pMap->m_originPos = Pos;
		pMap->Init();
	}
	return pMap;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMapManager::Init(void)
{
	//�}�b�v����
	CMap::Create(m_originPos,D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f));
	//�v���C���[�ʒu�̐���
	m_pLocationPoint[0] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f),0);
	//�v���C���[�ʒu�̐���
	m_pLocationPoint[1] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 1);
	//�v���C���[�ʒu�̐���
	m_pLocationPoint[2] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 2);
	//�v���C���[�ʒu�̐���
	m_pLocationPoint[3] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMapManager::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMapManager::Update(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		//�v���C���[�̈ʒu�擾
		D3DXVECTOR3 pos = CManager::GetPlayerControl()->GetPlayer(nCount)->GetPos();
		//�v���C���[�̌��݈ʒu���Z�b�g
		m_pLocationPoint[nCount]->SetPos(D3DXVECTOR3(m_originPos.x + pos.x * MAP_LOCATION_VALUE, m_originPos.y - pos.z * MAP_LOCATION_VALUE, 0.0f));
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CMapManager::Draw(void)
{
	
}
