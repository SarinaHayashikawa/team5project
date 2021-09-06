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
#include "Fieldmanager.h"
#include "MapEdgeMask.h"
#include "MapEdgeOverlay.h"
#include "MapEdgeMaskOut.h"
#include "timer.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_LOCATION_VALUE (0.34f) //�}�b�v�\���̌��݈ʒu�␳�l
#define MAP_SHRINK_TIME (10)//���̕b�������ɏk��ł�
#define MAP_SHIRINK_SIZE (2.0f)//�k�ރX�s�[�h
#define MAP_SHIRINK_TIME_VALUE (60) //1�k���ŏk�ޗʁi�t���[���j
#define MAP_LAST_SIZE (50.0f) //�Ō�̃}�b�v�T�C�Y

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapManager::CMapManager(int nPriority) : CScene(nPriority)
{
    m_originPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_pMapEdgeMask	= nullptr;
	m_pFieldManager = nullptr;
	m_nShrinkCount = 1;
	m_bShirnk = false;
	m_nTimeFrame = 0;
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
CMapManager * CMapManager::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
    CMapManager *pMap = nullptr;

    pMap = new CMapManager;
    if (pMap != nullptr)
    {
        pMap->m_originPos = Pos;
        pMap->m_MapSize = Size;
        pMap->Init();
    }
    return pMap;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMapManager::Init(void)
{
    //�X�e�[�W����
    m_pFieldManager = CFieldManager::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), m_MapSize);
    //�X�e�[�W�����i���݂̃t�B�[���h�j
    m_pMapEdgeMask = CMapEdgeMask::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), m_MapSize);
    //�X�e�[�W�����i�t�B�[���h�O���j
    CMapEdgeOverlay::Create(D3DXVECTOR3(0.0f, -49.0f, 0.0f), m_MapSize * 2.0f);
    //�~�j�}�b�v����
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

	//���k���Ԃ����������ׂ�
	if (m_nTimeFrame == (MAP_SHRINK_TIME * m_nShrinkCount) * 30 && m_bShirnk == false)
	{
		m_bShirnk = true;
	}
	if (m_bShirnk == true && m_nTimeFrame <= (MAP_SHRINK_TIME * m_nShrinkCount) * 30 + MAP_SHIRINK_TIME_VALUE)
	{
		if (m_MapSize.x > MAP_LAST_SIZE)//�ŏ��T�C�Y�ɂȂ�܂ŏk�܂���
		{
			//�X�e�[�W���k
			m_MapSize.x -= MAP_SHIRINK_SIZE;
			m_MapSize.y -= MAP_SHIRINK_SIZE;
			m_MapSize.z -= MAP_SHIRINK_SIZE;
		}
	}
	else if(m_bShirnk == true && m_nTimeFrame > (MAP_SHRINK_TIME * m_nShrinkCount) * 30 + MAP_SHIRINK_TIME_VALUE)
	{
		m_nShrinkCount++;
		m_bShirnk = false;
	}

    //�T�C�Y�Z�b�g
    m_pMapEdgeMask->SetSize(m_MapSize);
    m_pFieldManager->SetSize(m_MapSize);
    for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
    {
        //�v���C���[�̈ʒu�擾
        D3DXVECTOR3 pos = CManager::GetPlayerControl()->GetPlayer(nCount)->GetPos();
        //�v���C���[�̌��݈ʒu���Z�b�g
        m_pLocationPoint[nCount]->SetPos(D3DXVECTOR3(m_originPos.x + pos.x * MAP_LOCATION_VALUE, m_originPos.y - pos.z * MAP_LOCATION_VALUE, 0.0f));
    }
	m_nTimeFrame++;
}
//=============================================================================
// �`�揈��
//=============================================================================
void CMapManager::Draw(void)
{
    
}

