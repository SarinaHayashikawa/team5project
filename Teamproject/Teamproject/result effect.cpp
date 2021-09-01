//=============================================================================
//
// ���U���g�G�t�F�N�g(���i���~���Ă���) [result effect.h]
// Author : �g�c�I�l
//
//=============================================================================
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "result effect.h"
#include "food base.h"
#include "floor.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include "effect sushi.h"

#include <time.h>

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResultEffect::CResultEffect(int nPriority)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		m_pSushi[nSushi] = nullptr;
	}
	
	m_nSushiCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResultEffect::~CResultEffect()
{
}

//=============================================================================
// ��������
//=============================================================================
CResultEffect * CResultEffect::Create()
{
	//�������m��
	CResultEffect* pResultEffect = nullptr;
	pResultEffect = new CResultEffect;

	//NULL�`�F�b�N
	if (pResultEffect != nullptr)
	{
		pResultEffect->Init();
	}

	return pResultEffect;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CResultEffect::Init(void)
{

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CResultEffect::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResultEffect::Update(void)
{
	//���i�̃����_����������
	RandomSpawn();
	//���i�̈ړ�����
	MoveSushi();
	//���i�̉�ʊO����
	Offscreen();

}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CResultEffect::Draw(void)
{

}

//=============================================================================
// ���i�̃����_�����������֐�
//=============================================================================
void CResultEffect::RandomSpawn(void)
{
	//�����_���֐��̏�����
	srand((unsigned int)time(NULL));
	//�����_���ɐ��l�擾
	int nRandom = (rand() % 10);

	//�擾�������l���P��艺�̏ꍇ
	if (nRandom<5)
	{
		//�����ʒu
		D3DXVECTOR3 pos;
		//�����_����X�ʒu��ݒ�
		float XPosRandom = (float)(rand() % SCREEN_WIDTH);
		pos = D3DXVECTOR3(XPosRandom, 0.0f - 30.0f, 0.0f);
		
		//�����_���ɂǂ̎��i���X�|�[�������邩���߂�
		int nSushiType = (rand() % (CEffectSushi::TYPE_MAX - 1));			//�����_���ɒl���擾
		
		for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
		{
			if (m_pSushi[nSushi] == NULL)
			{
				//���i�̃X�|�[������
				m_pSushi[nSushi] = CEffectSushi::Create(pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f), nSushiType);
				
				//���݂̎��i�̐����v���X
				m_nSushiCount += 1;
				
				return;
			}
		}
	}

}

//=============================================================================
// ���i�̈ړ�����
//=============================================================================
void CResultEffect::MoveSushi(void)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		if (m_pSushi[nSushi] != NULL)
		{
			//�ʒu�擾
			D3DXVECTOR3 pos = m_pSushi[nSushi]->GetPos();
			//�ʒu�̍X�V
			pos.y++;
			//�ʒu�Z�b�g
			m_pSushi[nSushi]->SetPos(pos);
		}
	}
}

//=============================================================================
// ���i�̉�ʊO�����֐�
//=============================================================================
void CResultEffect::Offscreen(void)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		if (m_pSushi[nSushi] != NULL)
		{
			//�ʒu�擾
			D3DXVECTOR3 pos = m_pSushi[nSushi]->GetPos();
			//��ʊO�ɏo�Ă��邩
			if (pos.y>SCREEN_HEIGHT + 20)
			{
				//��ʊO�ɂ��鎞�ɏ���
				m_pSushi[nSushi]->Uninit();
				m_pSushi[nSushi] = NULL;
				//�ő吔�����炷
				m_nSushiCount -= 1;
			}
		}
	}
}
