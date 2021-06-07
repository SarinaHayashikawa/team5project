//===================================================================
//
//	�J�������� [camera.cpp]
//	Author:�ѐ�ї���
//
//===================================================================
//*****************************************************************************
// �x������
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
//======================================================
//�C���N���[�h�t�@�C��
//======================================================
#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#define SCRIPT_PASS		"Data/TEXT/camera.txt"
#define CAMERA_INTERPOLATION 0.2f //�J������ԃX�s�[�h

//======================================================
//�R���X�g���N�^
//======================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(20, 40, -100);
	m_posR = m_posV + D3DXVECTOR3(0, 0, 500);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(45.0f, 180.0f, 0.0f);
	m_fDistanceFromPlayer = CAMERA_DISTANCE_FROM_PLAYER;
	m_fDistanceFromPlayerDest = CAMERA_DISTANCE_FROM_PLAYER_STAND;
	m_fDistance = 0.0f;
	m_bIsFollowPlayer = false;
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fInterpolation = 0.0f;
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
	m_posV = D3DXVECTOR3(20, 100, -200);
	m_posR = D3DXVECTOR3(0, 0, 500);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//�J�����̌����ݒ�
	m_rot = D3DXVECTOR3(45.0f, 180.0f, 0.0f);
	//�J�����̃v���C���[����̋����ݒ�
	m_fDistanceFromPlayer = CAMERA_DISTANCE_FROM_PLAYER;
	m_fDistanceFromPlayerDest = CAMERA_DISTANCE_FROM_PLAYER;

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
	CPlayer* pPlayer = CManager::GetPlayer();

	//�J���������̕ω���⊮
	m_posV += (m_posVDest - m_posV) * m_fInterpolation;
	//�J���������̕ω���⊮
	m_posR += (m_posRDest - m_posR) * m_fInterpolation;

}
//======================================================
//�J�����ɂ��`��
//======================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();    //�f�o�C�X�ւ̃|�C���^
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

void CCamera::SetCameraDistance(float fDistance)
{
	m_fDistanceFromPlayerDest = fDistance;
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