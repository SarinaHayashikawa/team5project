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
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_LOCATION_VALUE (0.34f) //�}�b�v�\���̌��݈ʒu�␳�l
#define MAX_SUSHI_SPAWN (300)		//�a�̃X�|�[���܂ł̍ő厞��

//*****************************************************************************
// �ÓI�����o�[�ϐ�������
//*****************************************************************************
int CMapManager::m_nProb[CFoodBase::TYPE_MAX] =
{
	20,				//�ЂƂ܂��̃f�o�b�N�p�̒l
	20,
	20,
	20,
	20,
};
int CMapManager::m_nMaxProb = m_nProb[0] + m_nProb[1] + m_nProb[2] + m_nProb[3] + m_nProb[4];

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapManager::CMapManager(int nPriority) : CScene(nPriority)
{
	m_originPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMapEdgeMask	= nullptr;
	m_nSushiSpawn	= 0;	// ���i�̃X�|�[�����鎞�Ԃ̏�����
	m_SpawnCount	= 0;	// ���i�̃X�|�[���J�E���g�̏�����

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
	CFieldManager::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), m_MapSize);
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
	//�Ƃ肠�������k���Ă邩�m�F����
	m_MapSize.x -= 2.0f;
	m_MapSize.y -= 2.0f;
	m_MapSize.z -= 2.0f;
	m_pMapEdgeMask->SetSize(m_MapSize);
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		//�v���C���[�̈ʒu�擾
		D3DXVECTOR3 pos = CManager::GetPlayerControl()->GetPlayer(nCount)->GetPos();
		//�v���C���[�̌��݈ʒu���Z�b�g
		m_pLocationPoint[nCount]->SetPos(D3DXVECTOR3(m_originPos.x + pos.x * MAP_LOCATION_VALUE, m_originPos.y - pos.z * MAP_LOCATION_VALUE, 0.0f));
	}

	//�a�̐�������
	SushiSpawn();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CMapManager::Draw(void)
{
	
}

//=============================================================================
// ���i�̃����_�����������֐�
//=============================================================================
void CMapManager::SushiSpawn(void)
{
	//�J�E���g�_�E��
	m_SpawnCount++;
	//�J�E���g�����ɒB�����烉���_���ɃX�|�[��
	if (m_SpawnCount>m_nSushiSpawn)
	{
		//�G���A�̔��a
		int nRadius = 250;//(�R�R�̐��l��͈͐����̉~�̔��a���擾)
		 //���S�l
		D3DXVECTOR3 centre = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//(�R�R�̐��l��͈͐����̉~�̒��S���擾)

		//�����_���p�x
		srand((unsigned int)time(NULL));			//�����_���֐��̏�����
		float fAngle = (float)(rand() % 360 + 1);	//�����_���Ŋp�x�����߂�

		//�����_���ȋ���
		int nDistance = rand() % nRadius;			//�����_���ȋ������擾

		//�����_�����X�|�[���ʒu
		D3DXVECTOR3 random = centre + D3DXVECTOR3((float)(nDistance*cos(fAngle)), 0.0f, (float)(nDistance*sin(fAngle)));

		//�����_���ɂǂ̎��i���X�|�[�������邩���߂�
		int nSpawn = rand() % m_nMaxProb;			//�����_���ɒl���擾

		int nProd = 0;//�m���p�̕ϐ�

		//�ǂ̎��i���X�|�[�����邩
		for (int nSushi = 0; nSushi < CFoodBase::TYPE_MAX; nSushi++)
		{
			//�m���𑫂��Ă�
			nProd += m_nProb[nSushi];
			//�m���̊m�F
			if (nSpawn <= nProd)
			{
				//�J�E���g������
				m_SpawnCount = 0;
				//�����_���Ɏ��̃X�|�[�����Ԃ����߂�
				m_nSushiSpawn = rand() % MAX_SUSHI_SPAWN;

				//���i�̃X�|�[������
				switch (nSushi)
				{
				case CFoodBase::TYPE_EBI:
					CEbi::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_EGG:
					CEgg::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_IKURA:
					CIkura::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_SALMON:
					CSalmon::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_TUNA:
					CTuna::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				}
				return;
			}
		}
	}
}
