//=============================================================================
//
//	�v���C���[[player.cpp]
//	Author:�g�c�I�l
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"
#include "resource manager.h"
#include "keyboard.h"
#include "mouse.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED (2.0f)			//�v���C���[�̃X�s�[�h(��ŕύX)
#define PlAYER_ROT_SPEED (10.0f)	//�v���C���[�̐U��������x(��ŕύX)
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	SetObjType(OBJTYPE_PLAYER);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size)
{
	//�������m��
	CPlayer* pPlayer = NULL;
	pPlayer = new CPlayer;
	//���\�[�X�m��
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(pPlayer->m_nModel);

	//NULL�`�F�b�N
	if (pPlayer != NULL)
	{
		//�ʒu�ݒ�
		pPlayer->SetPos(Pos);
		//�����ݒ�
		pPlayer->SetRot(Rot);
		//�J���[�ݒ�
		pPlayer->SetSize(Size);
		//���f���f�[�^�ݒ�
		pPlayer->SetModelData(Model);
		//����������
		pPlayer->Init();
	}

	return pPlayer;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPlayer::Init(void)
{

	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPlayer::Uninit(void)
{
	
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayer::Update(void)
{
	Move();
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CPlayer::Move(void)
{
	//�L�[�{�[�h���͂̎擾
	CKeyboard* pInput = (CKeyboard*)CManager::GetInputKeyboard();
	//�}�E�X���͎擾
	CMouse *pInputMouse = (CMouse*)CManager::GetInputMouse();

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�����擾
	D3DXVECTOR3 rot = GetRot();
	//�ړ���
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�ړ��i�f�o�b�N�j
	if (pInput->GetKeyPress(DIK_W))
	{
		move += D3DXVECTOR3(0.0f,0.0f,1.0f);
	}
	if(pInput->GetKeyPress(DIK_S))
	{
		move += D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}
	if (pInput->GetKeyPress(DIK_A))
	{
		move += D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	}
	if (pInput->GetKeyPress(DIK_D))
	{
		move += D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	}

	//�ړ��i�}�E�X�j
	if (pInputMouse->GetClick(0))
	{
		float fRotMove=0.0f;

		//�P�ʃx�N�g���擾
		D3DXVec3Normalize(&move, &D3DXVECTOR3((float)pInputMouse->GetMousePos().x - SCREEN_WIDTH/2, 0.0f, (float)-pInputMouse->GetMousePos().y + SCREEN_HEIGHT/2));
		
		//���������p�x
		fRotMove = atan2f((pos.x - (move.x + pos.x)), (pos.z - (move.z + pos.z)));
		//�����̊p�x
		float fDiff = ((D3DXToRadian(180.0f) - (fRotMove*-1.0f)) - (D3DXToRadian(180.0f) - (rot.y*-1.0f)))*-1.0f;
		//��]�����̊m�F(���v����true:�����v���false)
		bool bRotation = fRotMove>rot.y ? !(fRotMove - rot.y > D3DXToRadian(180.0f)): rot.y - fRotMove  > D3DXToRadian(180.0f);
		//�����̏C��
		fDiff = (fDiff + (bRotation ? D3DXToRadian(-360.0f) : D3DXToRadian (360.0f)));
		fDiff = fmod(fDiff, D3DXToRadian(360.0f));
		//��������
		rot.y = rot.y - (fDiff*0.1f);
		//�p�x�����ɒB������C��
		if (D3DXToDegree(rot.y) >= 360.0f
			|| D3DXToDegree(rot.y) <= -360.0f)
		{
			rot.y = 0.0f;
		}

	}


	// �ړ��X�s�[�h
	move *= PLAYER_SPEED;

	// �ړ�����
	pos += move;

	// �ʒu�ۑ�
	SetPos(pos);
	// �����ۑ�
	SetRot(rot);

}

//=============================================================================
// ���������֐�
//=============================================================================
void CPlayer::Rot(void)
{
	

}

//=============================================================================
// ���������֐�
//=============================================================================
void CPlayer::Boost(void)
{
}

