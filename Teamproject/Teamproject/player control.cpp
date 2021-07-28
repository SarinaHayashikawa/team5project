//=============================================================================
//
//	�v���C���[���� [player control.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player control.h"
#include "player.h"
#include "joystick.h"
#include "manager.h"
#include "player parts.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SIZE			(7.0f)	// �v���C���[�̓����蔻��̃T�C�Y
#define PLAYER_DEATH		(30*3)	// �v���C���[�����S����
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
D3DXVECTOR3 CPlayerControl::m_PlayerPos[MAX_PLAYER] = 
{
	D3DXVECTOR3(-50.0f, 0.0f, 0.0f),
	D3DXVECTOR3(50.0f, 0.0f, 0.0f),
	D3DXVECTOR3(-50.0f, 0.0f, -50.0f),
	D3DXVECTOR3(50.0f, 0.0f, -50.0f)
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayerControl::CPlayerControl(int nPriority)
{
	for (int nPlayer = 0; nPlayer<MAX_PLAYER; nPlayer++)
	{
		m_pPlayer[nPlayer] = nullptr;
		m_nRespawn[nPlayer] = 0;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayerControl::~CPlayerControl()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CPlayerControl * CPlayerControl::Create()
{
	//�������m��
	CPlayerControl *pPlayerControl = nullptr;
	pPlayerControl = new CPlayerControl;

	if (pPlayerControl != nullptr)
	{
		pPlayerControl->Init();
	}
	return pPlayerControl;

}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPlayerControl::Init(void)
{
	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		m_pPlayer[nPlayer] = CPlayer::Create(m_PlayerPos[nPlayer], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPlayerControl::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayerControl::Update(void)
{
	for (int nPlayer = 0; nPlayer<MAX_PLAYER; nPlayer++)
	{
		//NULL�`�F�b�N
		if (m_pPlayer[nPlayer] != nullptr)
		{
			//�v���C���[��l�ЂƂ�̑���Ǘ�
			PlayerControl(nPlayer);
			//�v���C���[���m�̓����蔻��
			PlayerHit(nPlayer);
			//�v���C���[�̃_���[�W����
			DamageHit(nPlayer);
			//���X�|�[������
			RespawnControl(nPlayer);
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPlayerControl::Draw(void)
{
}

//=============================================================================
// �v���C���[�̃��X�|�[�������֐�
//=============================================================================
void CPlayerControl::RespawnControl(int nPlayer)
{
	if (m_pPlayer[nPlayer]->GetStats()== CPlayer::PLAYER_STATS_DEATH)
	{
		//���X�|�[���J�E���g
		m_nRespawn[nPlayer]++;

		//���X�|�[���J�E���g�����ɒB������
		if (m_nRespawn[nPlayer] >= PLAYER_DEATH)
		{
			//���X�|�[������
			m_pPlayer[nPlayer]->Respawn(m_PlayerPos[nPlayer]);
			//���X�|�[���J�E���g�̏�����
			m_nRespawn[nPlayer] = 0;
		}
	}
}

//=============================================================================
// ���̃v���C���[�̓��������ۂ̃_���[�W����
//=============================================================================
void CPlayerControl::DamageHit(int nPlayer)
{
	//NULL�`�F�b�N
	if (m_pPlayer[nPlayer] != nullptr)
	{
		for (int nPlayerCount = 0; nPlayerCount < MAX_PLAYER; nPlayerCount++)
		{
			if (m_pPlayer[nPlayerCount] != nullptr
				&& nPlayer != nPlayerCount)
			{
				//�v���C���[�̈ʒu
				D3DXVECTOR3 PlayerPos = m_pPlayer[nPlayer]->GetPos();
				//���Ă�ꂽ�v���C���[�̃p�[�c��
				int nPlayerParts = m_pPlayer[nPlayerCount]->GetPartsCount();

				for (int nPartsCount = 0; nPartsCount<nPlayerParts; nPartsCount++)
				{
					//�p�[�c�̈ʒu
					D3DXVECTOR3 PartsPos = m_pPlayer[nPlayerCount]->GetParts(nPartsCount)->GetPos();

					//�v���C���[�ƃp�[�c�̋������v�Z
					float RangeX = PlayerPos.x - PartsPos.x;
					float RangeZ = PlayerPos.z - PartsPos.z;
					float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

					//�͈͂ɓ����Ă��邩
					if (Range <= PLAYER_SIZE + PLAYER_SIZE)
					{
						//�v���C���[�̏���
						m_pPlayer[nPlayer]->DamageHit();
						return;
					}
				}

			}
		}
	}
}

//=============================================================================
//�v���C���[�̓��m�̃q�b�g�����֐�
//=============================================================================
void CPlayerControl::PlayerHit(int nPlayer)
{
	//NULL�`�F�b�N
	if (m_pPlayer[nPlayer] != nullptr)
	{
		//��x�����������������Ȃ����߂�+1
		int nPlayerCount = nPlayer + 1;
		//�v���C���[���m�̏���
		for (nPlayerCount; nPlayerCount < MAX_PLAYER; nPlayerCount++)
		{
			//�v���C���[�̃|�C���^��NULL�`�F�b�N
			if (m_pPlayer[nPlayerCount] != nullptr)
			{
				//����v���C���[�̏�ԃ`�F�b�N
				if (m_pPlayer[nPlayerCount]->GetStats()== CPlayer::PLAYER_STATS_NORMAL)
				{
					//�v���C���[�̈ʒu
					D3DXVECTOR3 PlayerPos = m_pPlayer[nPlayer]->GetPos();
					//���Ă�ꂽ�v���C���[�̈ʒu
					D3DXVECTOR3 HitPlayerPos = m_pPlayer[nPlayerCount]->GetPos();
					//�v���C���[���m�̋������v�Z
					float RangeX = PlayerPos.x - HitPlayerPos.x;
					float RangeZ = PlayerPos.z - HitPlayerPos.z;
					float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

					//�v���C���[���߂��ɂ��邩
					if (Range <= PLAYER_SIZE + PLAYER_SIZE)
					{
						//�v���C���[���m�̔���
						m_pPlayer[nPlayer]->Repel(m_pPlayer[nPlayerCount]);
						m_pPlayer[nPlayerCount]->Repel(m_pPlayer[nPlayer]);
						return;
					}
				}
			}
		}
	}
}

//=============================================================================
// �v���C���[���쏈���֐�
//=============================================================================
void CPlayerControl::PlayerControl(int nPlayer)
{
	// �R���g���[���[�̎擾
	CJoystick* pJoystick = CManager::GetInputJoystick();
	//���͐�
	D3DXVECTOR3 Joystic = D3DXVECTOR3((float)pJoystick->GetJoyStick(nPlayer).lX, (float)-pJoystick->GetJoyStick(nPlayer).lY, 0.0f);
	// �v���C���[�̑��� 
	m_pPlayer[nPlayer]->RotControl(Joystic);
	//�v���C���[�̉�������
	if (pJoystick->GetJoystickPress(JS_A, nPlayer))
	{
		m_pPlayer[nPlayer]->Dash(true);
	}
	else
	{
		m_pPlayer[nPlayer]->Dash(false);
	}

}
