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
#define PLAYER_SPEED (1.0f)			// �v���C���[�̃X�s�[�h(��ŕύX)
#define PLAYER_BOOST_SPEED (2.0f)	// �v���C���[�̃u�[�X�g�X�s�[�h(��ŕύX)
#define PlAYER_ROT_SPEED (10.0f)	// �v���C���[�̐U��������x(��ŕύX)
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	SetObjType(OBJTYPE_PLAYER);			// �I�u�W�F�N�g�^�C�v�ݒ�
	m_nLife		= 0;					// ���C�t�̏�����
	memset(m_Move, NULL, sizeof(m_Move));// �ړ��ʂ̏�����
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



	//�P�ʃx�N�g���擾
	D3DXVec3Normalize(&m_Move, &D3DXVECTOR3((float)pInputMouse->GetMousePos().x - SCREEN_WIDTH / 2, 0.0f, (float)-pInputMouse->GetMousePos().y + SCREEN_HEIGHT / 2));
	//�p�x����
	Rot();

	if (!pInputMouse->GetClick(0))
	{
		// �ړ��X�s�[�h
		m_Move *= PLAYER_SPEED;
	}
	else
	{
		//�u�[�X�g���̃X�s�[�h
		m_Move *= PLAYER_BOOST_SPEED;
	}

	// �ړ�����
	pos += m_Move;

	// �ʒu�ۑ�
	SetPos(pos);

}

//=============================================================================
// ���������֐�
//=============================================================================
void CPlayer::Rot(void)
{
	//�p�x�̈ړ���
	float fRotMove = 0.0f;
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�����擾
	D3DXVECTOR3 rot = GetRot();

	//���������p�x
	fRotMove = atan2f((pos.x - (m_Move.x + pos.x)), (pos.z - (m_Move.z + pos.z)));
	//�����̊p�x
	float fDiff = ((D3DXToRadian(180.0f) - (fRotMove*-1.0f)) - (D3DXToRadian(180.0f) - (rot.y*-1.0f)))*-1.0f;
	//��]�����̊m�F(���v����true:�����v���false)
	bool bRotation = fRotMove>rot.y ? !(fRotMove - rot.y > D3DXToRadian(180.0f)) : rot.y - fRotMove  > D3DXToRadian(180.0f);
	//�����̏C��
	fDiff = (fDiff + (bRotation ? D3DXToRadian(-360.0f) : D3DXToRadian(360.0f)));
	fDiff = (float)(fmod(fDiff, D3DXToRadian(360.0f)));
	//��������
	rot.y = rot.y - (fDiff*0.1f);
	//�p�x�����ɒB������C��
	if (D3DXToDegree(rot.y) >= 360.0f
		|| D3DXToDegree(rot.y) <= -360.0f)
	{
		rot.y = 0.0f;
	}

	// �����ۑ�
	SetRot(rot);

}

