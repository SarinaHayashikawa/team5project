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
#include "joystick.h"
#include "player parts.h"
#include "ebi parts.h"
#include "egg parts.h"
#include "ikura parts.h"
#include "salmon parts.h"
#include "tuna parts.h"
#include "food base.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED		(1.0f)	// �v���C���[�̃X�s�[�h(��ŕύX)
#define PLAYER_BOOST_SPEED	(2.0f)	// �v���C���[�̃u�[�X�g�X�s�[�h(��ŕύX)
#define PLAYER_ROT_SPEED	(10.0f)	// �v���C���[�̐U��������x(��ŕύX)
#define PLAYER_REPEL		(15.0f)	// �v���C���[���͂�����鋗��
#define PLAYER_REPEL_FRAME	(10.0f)	// �v���C���[�̂͂����ꂽ�ۂ̃t���[��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	SetObjType(OBJTYPE_PLAYER);								// �I�u�W�F�N�g�^�C�v�ݒ�
	m_nLife		= 0;										// ���C�t�̏�����
	m_nRepelFrameCount = 0;									// �͂����ꂽ�ۂ̃t���[���l�̏�����
	m_nDeathFrameCount = 0;									// ���S���̃J�E���g�t���[���l�@�̏�����
	m_fDashCoutn = 0;										// �����l�̏�����
	m_nParts	= 0;										// �p�[�c���̏�����
	m_PlayerStats = PLAYER_STATS_NORMAL;					// �v���C���[�X�e�[�^�X�̏�����
	m_DashSwitch = false;									// �_�b�V���ؑւ̏�����
	m_RotMove	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̈ړ��ʂ̏�����
	m_RepelMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �͂����ꂽ�ۂ̈ړ��ʂ̏�����
	memset(m_pParts, NULL, sizeof(m_pParts[MAX_PARTS]));	// �p�[�c�|�C���^�̏�����
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
// �X�V�����֐�
//=============================================================================
void CPlayer::Update(void)
{
	//�L�[�{�[�h���͂̎擾
	CKeyboard* pInput = (CKeyboard*)CManager::GetInputKeyboard();

	switch (m_PlayerStats)
	{
	case PLAYER_STATS_NORMAL:
		//�ړ�����
		Move();
		//�p�x����
		Rot();
		break;
	case PLAYER_STATS_REPEL:
		RepelMove();
		break;
	case PLAYER_STATS_DEATH:
		Death();
		break;
	default:
		break;
	}
	

}

//=============================================================================
// �p�[�c�ǉ��i�H�ו���H�ׂ���̒ǉ��p�[�c�j�����֐�
//=============================================================================
void CPlayer::AddParts(CFoodBase::FOOD_TYPE FoodType)
{
	//�p�[�c���Ȃ���
	if (m_nParts == 0)
	{	
		//�ʒu�擾
		D3DXVECTOR3 pos = GetPos();
		//�����擾
		D3DXVECTOR3 rot = GetRot();
		//��������
		switch (FoodType)
		{
		case CFoodBase::TYPE_EBI:
			m_pParts[m_nParts] = CEbiParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
			break;
		case CFoodBase::TYPE_EGG:
			m_pParts[m_nParts] = CEggParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
			break;
		case CFoodBase::TYPE_IKURA:
			m_pParts[m_nParts] = CIkuraParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
			break;
		case CFoodBase::TYPE_SALMON:
			m_pParts[m_nParts] = CSalmonParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
			break;
		case CFoodBase::TYPE_TUNA:
			m_pParts[m_nParts] = CTunaParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
			break;
		}
	}
	//�p�[�c���P�ł����鎞
	else if (m_nParts>0 && m_nParts<MAX_PARTS)
	{
		//�ʒu�擾
		D3DXVECTOR3 PartsPos = m_pParts[m_nParts - 1]->GetPos();
		//�����擾
		D3DXVECTOR3 PartsRot = m_pParts[m_nParts - 1]->GetRot();
		//��������
		switch (FoodType)
		{
		case CFoodBase::TYPE_EBI:
			m_pParts[m_nParts] = CEbiParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
			break;
		case CFoodBase::TYPE_EGG:
			m_pParts[m_nParts] = CEggParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
			break;
		case CFoodBase::TYPE_IKURA:		
			m_pParts[m_nParts] = CIkuraParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
			break;
		case CFoodBase::TYPE_SALMON:
			m_pParts[m_nParts] = CSalmonParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
			break;
		case CFoodBase::TYPE_TUNA:
			m_pParts[m_nParts] = CTunaParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
			break;
		}


	}

	//�p�[�c���𑝂₷
	m_nParts++;
}

//=============================================================================
// �R���g���[���[���쏈���֐�
//=============================================================================
void CPlayer::RotControl(D3DXVECTOR3 Control)
{
	//�X�e�B�b�N�ɐG��Ă��邩�̊m�F�iControl�̂��Ƃ����ǂ����0.0f�̏ꍇ�G��Ă��Ȃ��j
	bool TouchStick = Control.x == 0.0f&&Control.y == 0.0f ? true : false;
	
	//�X�e�B�b�N�ɐG��Ă���ꍇ�̏���
	if(TouchStick!= true)
	{
		//�P�ʃx�N�g���擾
		D3DXVec3Normalize(&m_RotMove, &D3DXVECTOR3(Control.x, 0.0f, Control.y));
	}
}

//=============================================================================
// �_�b�V����ԂɈڍs
//=============================================================================
void CPlayer::Dash(bool bDash)
{
	m_DashSwitch = bDash;
}

//=============================================================================
// �v���C���[���_���[�W���󂯂郂�m�ɂԂ������ۂ̏����֐�
//=============================================================================
void CPlayer::DamageHit(void)
{
	if (m_PlayerStats != PLAYER_STATS_DEATH)
	{
		m_PlayerStats = PLAYER_STATS_DEATH;
	}
}

//=============================================================================
// �͂�����鏈���֐�
//=============================================================================
void CPlayer::Repel(CScene3d* Player)
{
	if (m_PlayerStats != PLAYER_STATS_REPEL)
	{
		//���݈ʒu
		D3DXVECTOR3 pos = GetPos();
		//����̈ʒu
		D3DXVECTOR3 PlayerPos = Player->GetPos();
		//������������
		D3DXVECTOR3 HItPint = D3DXVECTOR3(0.0f, atan2f((PlayerPos.x - pos.x), (PlayerPos.z - pos.z)), 0.0f);;
		//�@���x�N�g���̌v�Z
		D3DXVECTOR3 Normal = PlayerPos - pos;
		//�ړ�����
		D3DXVECTOR3 move = D3DXVECTOR3((float)(cos(HItPint.y + D3DXToRadian(90.0f))), 0.0f, (float)(sin(HItPint.y - D3DXToRadian(90.0f))));
		//�ړ���
		D3DXVec3Normalize(&Normal, &Normal);
		//�ړ��ʂ̌v�Z
		D3DXVec3Normalize(&m_RepelMove, &(move - 2.0f * D3DXVec3Dot(&move, &Normal) * Normal));
		m_RepelMove = (-m_RepelMove*PLAYER_REPEL) + pos;
		//�����l�̏�����
		m_fDashCoutn = 0.0f;
		//��ԕω�
		m_PlayerStats = PLAYER_STATS_REPEL;

	}
}

//=============================================================================
// ���X�|�[������
//=============================================================================
void CPlayer::Respawn(D3DXVECTOR3 RespawnPos)
{
	//���X�|�[���ʒu
	SetPos(RespawnPos);
	//�X�e�[�^�X�ݒ�
	m_PlayerStats = PLAYER_STATS_NORMAL;
	//���S�����ۂ̃J�E���g������
	m_nDeathFrameCount = 0;
	//�A���t�@�l��������
	SetAlphaValue(1.0f);
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CPlayer::Death(void)
{
	//�J�E���g
	m_nDeathFrameCount++;
	if (m_nDeathFrameCount % 3)
	{
		SetAlphaValue(1.0f);
	}
	else
	{
		SetAlphaValue(0.0f);
	}
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
	// �R���g���[���[�̎擾
	CJoystick* pJoystick = CManager::GetInputJoystick();

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�����擾
	D3DXVECTOR3 rot = GetRot();
	//�ړ���
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�ړ�����
	move = D3DXVECTOR3((float)(cos(rot.y + D3DXToRadian(90.0f))), 0.0f, (float)(sin(rot.y - D3DXToRadian(90.0f))));

	if (!m_DashSwitch)
	{
		if (m_fDashCoutn <= PLAYER_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn + 0.1f;
		}
		else if(m_fDashCoutn > PLAYER_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn - 0.1f;

		}
	}
	else
	{
		if (m_fDashCoutn <= PLAYER_BOOST_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn + 0.1f;
		}
		else if (m_fDashCoutn > PLAYER_BOOST_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn - 0.1f;
		}
	}
	//�X�s�[�h���v�Z
	move *= m_fDashCoutn;
	// �ړ�����
	pos += move;

	// �ʒu�ۑ�
	SetPos(pos);

}

//=============================================================================
// ���������֐�
//=============================================================================
void CPlayer::Rot(void)
{
	//�}�E�X���͎擾
	CMouse *pInputMouse = (CMouse*)CManager::GetInputMouse();
	//�p�x�̈ړ���
	float fRotMove = 0.0f;
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�����擾
	D3DXVECTOR3 rot = GetRot();
	//���������p�x
	fRotMove = atan2f((pos.x - (m_RotMove.x + pos.x)), (pos.z - (m_RotMove.z + pos.z)));
	//�����̊p�x
	float fDiff = ((D3DXToRadian(180.0f) - (fRotMove*-1.0f)) - (D3DXToRadian(180.0f) - (rot.y*-1.0f)))*-1.0f;
	//��]�����̊m�F(���v����true:�����v���false)
	bool bRotation = fRotMove>rot.y ? !(fRotMove - rot.y > D3DXToRadian(180.0f)) : rot.y - fRotMove  > D3DXToRadian(180.0f);
	//�����̏C��
	fDiff = (fDiff + (bRotation ? D3DXToRadian(-360.0f) : D3DXToRadian(360.0f)));
	fDiff = (float)(fmod(fDiff, D3DXToRadian(360.0f)));
	//��������
	rot.y = rot.y - (fDiff*(0.04f));
	//�p�x�����ɒB������C��
	if (D3DXToDegree(rot.y) >= 360.0f
		|| D3DXToDegree(rot.y) <= -360.0f)
	{
		rot.y = 0.0f;
	}
	// �����ۑ�
	SetRot(rot);
}


//=============================================================================
// �͂����ꂽ�ۂ̈ړ������֐�
//=============================================================================
void CPlayer::RepelMove(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�ړ�����
	pos = pos + (m_RepelMove - pos)/(PLAYER_REPEL_FRAME - m_nRepelFrameCount);
	//�ʒu�Z�b�g
	SetPos(pos);
	//�t���[�����Z
	m_nRepelFrameCount++;

	if (m_nRepelFrameCount>= PLAYER_REPEL_FRAME)
	{
		//�J�E���g������
		m_nRepelFrameCount = 0;
		//�X�e�[�^�X��ύX
		m_PlayerStats = PLAYER_STATS_NORMAL;
	}
}

