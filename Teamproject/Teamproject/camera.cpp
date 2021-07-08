//===================================================================
//
//	�J�������� [camera.cpp]
//	Author:�ѐ�ї���
//
//===================================================================

//======================================================
//�C���N���[�h�t�@�C��
//======================================================
#include "camera.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mouse.h"
#include "keyboard.h"
#include "scene.h"
#include "player.h"

//======================================================
// �}�N����`
//======================================================
#define SCRIPT_PASS				("Data/TEXT/camera.txt")
#define CAMERA_INTERPOLATION	(0.2f)					//�J������ԃX�s�[�h
#define MAX_SCREEN				(4)						//�ő��ʕ�����

#ifdef _DEBUG
#define CAMERA_SENSITIVITY (5)	// �}�E�X���x
#define CAMERA_SPEED (10.0f)	// �J�����X�s�[�h
#define CAMERA_ZOOM	(50.0f)		// �J�����Y�[����
#endif
//======================================================
// �ÓI�����o�ϐ��̏�����
//======================================================

//======================================================
//�R���X�g���N�^
//======================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	m_posR = m_posV + D3DXVECTOR3(0.0f, 0.0f, 500.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(45.0f, 180.0f, 0.0f);
	m_fDistance = 100.0f;
	m_bIsFollowPlayer = false;
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fInterpolation = 0.0f;

#ifdef _DEBUG
	m_fMoveRot = 0.0f;
	m_pos = m_posV;
	m_bDebug = false;
#endif

}
//======================================================
//�f�X�g���N�^
//======================================================
CCamera::~CCamera()
{
}

//======================================================
//����������
//======================================================
HRESULT CCamera::Init(void)
{
	//�J�����̏���(�ʒu�E���ӓ_�E�����)�ݒ�
	m_posV = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	m_posR = m_posV + D3DXVECTOR3(0.0f, 0.0f, 500.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//�J�����̌����ݒ�
	m_rot = D3DXVECTOR3(89.0f, 180.0f, 0.0f);

	//�}�l�[�W���[�ɃJ��������ۑ�
	CManager::BindCamera(this);
	return S_OK;
}

//======================================================
//�I������
//======================================================
void CCamera::Uninit(void)
{

}

//======================================================
//�X�V����
//======================================================
void CCamera::Update(void)
{
#ifdef _DEBUG
	//�L�[�{�[�h���͂̎擾
	CKeyboard* pInput = (CKeyboard*)CManager::GetInputKeyboard();
	//�v���C���[�̎擾

	//�f�o�b�N��Ԃ̐ؑ�
	if (pInput->GetKeyTrigger(DIK_Z))
	{
		if (m_bDebug == true)
		{
			m_bDebug = false;
		}
		else
		{
			m_bDebug = true;
		}
	}

	if (m_bDebug == true)
	{
		Move();
	}
	else
	{
		PlayerFlattery();
	}

	//�ړ��̌v�Z
	D3DXVECTOR3 RotateCenter = m_pos + D3DXVECTOR3(sinf(D3DXToRadian(m_rot.y - 90)),
		50,
		cosf(D3DXToRadian(-m_rot.y - 90)));

	//�J�����̈ړ�����
	m_posV = RotateCenter +
		D3DXVECTOR3(sinf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * m_fDistance,
			sinf(D3DXToRadian(m_rot.x)) * m_fDistance,
			cosf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * m_fDistance);

	//���ӓ_�̈ړ�����
	m_posR = RotateCenter;




#else
	//�ړ��̌v�Z
	D3DXVECTOR3 RotateCenter = m_pos + D3DXVECTOR3(sinf(D3DXToRadian(m_rot.y - 90)),
		50,
		cosf(D3DXToRadian(-m_rot.y - 90)));

	//�J�����̈ړ�����
	m_posV = RotateCenter +
		D3DXVECTOR3(sinf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * m_fDistance,
			sinf(D3DXToRadian(m_rot.x)) * m_fDistance,
			cosf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * m_fDistance);

	//���ӓ_�̈ړ�����
	m_posR = RotateCenter;

#endif

}

//======================================================
// �J�����ɂ��`��
//======================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();    
	
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//======================================================
// �J�����ɂ�镪���`��
//======================================================
void CCamera::SetCamera(D3DXVECTOR3 CameraPos, D3DXVECTOR3 LookPosition)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,&m_posV,&m_posR,&m_vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

}

//======================================================
// �r���[�|�[�g�ݒ�
//======================================================
bool CCamera::SetUpViewport(int screen_id)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �r���[�|�[�g�p�����[�^
	D3DVIEWPORT9 view_port;

	//��ʂ̃T�C�Y
	if (MAX_SCREEN >= 2)
	{
		m_WidowSize.Width = SCREEN_WIDTH / 2.0f;
	}

	if (MAX_SCREEN >= 3)
	{
		m_WidowSize.Height = SCREEN_HEIGHT / 2.0f;
	}

	//��ʂ̈ʒu
	D3DXVECTOR2 offset[] = 
	{
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH / 2.0f, 0.0f),
		D3DXVECTOR2(0.0f, SCREEN_HEIGHT / 2.0f),
		D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f),
	};

	// �r���[�|�[�g�̍�����W
	view_port.X = offset[screen_id].x;
	view_port.Y = offset[screen_id].y;

	// �r���[�|�[�g�̕�
	view_port.Width = m_WidowSize.Width;
	// �r���[�|�[�g�̍���
	view_port.Height = m_WidowSize.Height;
	// �r���[�|�[�g�[�x�ݒ�
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// �r���[�|�[�g�ݒ�
	if (FAILED(pDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

//======================================================
//�����擾
//======================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

//======================================================
//�����̃Z�b�g
//======================================================
void CCamera::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}


//======================================================
// �v���C���[�Ǐ]����
//======================================================
void CCamera::PlayerFlattery(void)
{
	//�V�[���擾�p
	CScene* pTop[PRIORITY_MAX] = {};
	//���`�F�b�N����V�[���̃|�C���^
	CScene* pNext = NULL;

	//top�̃A�h���X���擾
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	//�I�u�W�F�N�g�T��
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			//���̕`��D��x�̃I�u�W�F�N�g���Ȃ��Ȃ�܂Ń��[�v
			while (pNext != NULL)
			{
				if (pNext->GetObjType() == CScene::OBJTYPE_PLAYER)
				{
					
					m_pos = ((CPlayer*)pNext)->GetPos();
					return;
				}
				//���̃I�u�W�F�N�g�̃|�C���^���X�V
				pNext = pNext->GetNext();
			}
		}
	}
}

//======================================================
//�J�������̃Z�b�g
//======================================================
void CCamera::SetCameraView(D3DXVECTOR3 posV, D3DXVECTOR3 posR, float fInterpolation)
{
	m_posVDest = posV;
	m_posRDest = posR;
	if (fInterpolation > 1.0f)
	{
		m_fInterpolation = 1.0f;//����ȏ�傫���Ȃ�ƕςɂȂ�̂Ő���
	}
	else
	{
		m_fInterpolation = fInterpolation;
	}
}

#ifdef _DEBUG
//=============================================================================
// �ړ������֐�
//=============================================================================
void CCamera::Move(void)
{
	//�L�[�{�[�h���͂̎擾
	CKeyboard* pInput = (CKeyboard*)CManager::GetInputKeyboard();
	//�}�E�X���͎擾
	CMouse *pInputMouse = (CMouse*)CManager::GetInputMouse();
	//�ړ���
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�����_�܂ł̋���
	D3DXVECTOR3 distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�𓮂���
	if (m_bDebug == true)
	{
		//����
		m_rot.x += (pInputMouse->GetMouseMove().lY * (float)(0.01f * CAMERA_SENSITIVITY));
		m_rot.y -= (pInputMouse->GetMouseMove().lX * (float)(0.01f * CAMERA_SENSITIVITY));
		
		//�����_�̋�����ς���
		if (pInputMouse->GetMouseMove().lZ != 0)
		{
			//�P�ʃx�N�g���Ɏ擾
			D3DXVec3Normalize(&distance, &(m_posR - m_posV));

			//�Y�[���A�E�g�̏ꍇ
			if (pInputMouse->GetMouseMove().lZ<0)
			{
				distance *= -1;
			}
		}

		//�ړ�
		if (pInput->GetKeyPress(DIK_W))
		{
			//�ړ������w��
			m_fMoveRot = -90.0f;
			//�ړ����̌����ݒ�
			m_fMoveRot += m_rot.y;
			//�ړ��ʏ���
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
		}

		if (pInput->GetKeyPress(DIK_S))
		{
			//�ړ������w��
			m_fMoveRot = 90.0f;
			//�ړ����̌����ݒ�
			m_fMoveRot += m_rot.y;
			//�ړ��ʏ���
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
		}

		if (pInput->GetKeyPress(DIK_A))
		{
			//�ړ������w��
			m_fMoveRot = 0.0f;
			//�ړ����̌����ݒ�
			m_fMoveRot += m_rot.y;
			//�ړ��ʏ���
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
		}

		if (pInput->GetKeyPress(DIK_D))
		{
			//�ړ������w��
			m_fMoveRot = 180.0f;
			//�ړ����̌����ݒ�
			m_fMoveRot += m_rot.y;
			//�ړ��ʏ���
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
		}

		//���x����
		move *= CAMERA_SPEED;
		//�Y�[���̊��x
		distance *= CAMERA_ZOOM;

		//�ړ�����
		m_pos += move;
		//�Y�[������
		m_pos += distance;

	}

	//�����̌��E�l����
	if ((m_rot.x) >= 89
		|| (m_rot.x) <= -89)
	{
		m_rot.x -= (pInputMouse->GetMouseMove().lY * (float)(0.01f * CAMERA_SENSITIVITY));
	}
	if (m_rot.y<0)
	{
		m_rot.y += 360;
	}
	if (m_rot.y > 360)
	{
		m_rot.y -= 360;
	}

}
#endif
