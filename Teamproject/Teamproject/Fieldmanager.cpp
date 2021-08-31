//=============================================================================
//
// �t�B�[���h�Ǘ� [fieldmanager.cpp]
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
#include "fieldmanager.h"
#include "resource manager.h"
#include "map.h"
#include "locationpoint.h"
#include "game.h"
#include "player.h"
#include "floor.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_SIZE (500.0f)		//�}�b�ՃT�C�Y
#define PLAYER_HIT_SIZE (5.0f)	//�}�b�ՃT�C�Y
#define MAX_SUSHI_SPAWN (300)	//�a�̃X�|�[���܂ł̍ő厞��

//*****************************************************************************
// �ÓI�����o�[�ϐ�������
//*****************************************************************************
int CFieldManager::m_nProb[CFoodBase::TYPE_MAX] =
{
	20,				//�ЂƂ܂��̃f�o�b�N�p�̒l
	20,
	20,
	20,
	20,
};
int CFieldManager::m_nMaxProb = m_nProb[0] + m_nProb[1] + m_nProb[2] + m_nProb[3] + m_nProb[4];

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFieldManager::CFieldManager(int nPriority) : CScene(nPriority)
{
	m_nSushiSpawn = 0;	// ���i�̃X�|�[�����鎞�Ԃ̏�����
	m_SpawnCount = 0;	// ���i�̃X�|�[���J�E���g�̏�����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFieldManager::~CFieldManager()
{

}

//=============================================================================
// ��������
//=============================================================================
CFieldManager * CFieldManager::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CFieldManager *pMap = nullptr;

	pMap = new CFieldManager;
	if (pMap != nullptr)
	{
		pMap->m_size = Size;
		pMap->Init();
	}
	return pMap;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFieldManager::Init(void)
{
	//������
	CFloor::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(m_size.x, m_size.z, m_size.z));
	m_originsize = m_size;//�}�b�v�ő�̃T�C�Y���i�[���Ă���
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFieldManager::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFieldManager::Update(void)
{
	//�[�����蔻��
	EdgeCollision();
	//�a�̐�������
	SushiSpawn();

}
//=============================================================================
// �`�揈��
//=============================================================================
void CFieldManager::Draw(void)
{

}

//=============================================================================
// �[���S����
//=============================================================================
void CFieldManager::EdgeCollision(void)
{
	CScene* pTop[PRIORITY_MAX] = {};
	CScene* pNext = nullptr;
	D3DXVECTOR3 distance; //�v���C���[�ƓG�̋���
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//���X�g�擪�擾
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != nullptr)
		{
			pNext = pTop[nCount];
			while (pNext != nullptr)
			{
				//pNext(CScene)��CEnemy�Ƀ_�E���L���X�g
				CPlayer * pPlayer = dynamic_cast<CPlayer*> (pNext);
				if (pPlayer != nullptr)
				{
					distance = pPlayer->GetPos();//�}�b�v�̌��_���O�A�O�Ȃ̂ł��̂܂܃v���C���[�̈ʒu�����

					//�G�ƃv���C���[�̋��������ꂼ��̔��a�̘a���傫��������}�b�v����͂ݏo�Ă�
					if (powf(distance.x, 2) + powf(distance.z, 2)
						>= pow(((m_size.x / 2) + PLAYER_HIT_SIZE), 2))
					{
						//���S�����i�}�b�v���k�Q�T���ȉ��Ȃ�j
						//����ȊO�̓��X�|�[��
						pPlayer->DamageHit();
					}
					
				}
				//���̑Ώۂ�ǂݍ���
				pNext = pNext->GetNext();
			}
		}
	}
}

//=============================================================================
// �[���S����
//=============================================================================
void CFieldManager::NowEdgeCollision(void)
{
}

//=============================================================================
// ���i�̃����_�����������֐�
//=============================================================================
void CFieldManager::SushiSpawn(void)
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
