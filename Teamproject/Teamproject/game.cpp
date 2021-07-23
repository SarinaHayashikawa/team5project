//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : 
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "camera.h"
#include "scene.h"
#include "sound.h"
#include "joystick.h"
#include "game.h"
#include "sound.h"
#include "floor.h"
#include "player.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "tuna.h"
#include "salmon.h"
#include "player parts.h"
#include "renderer.h"
#include "player control.h"
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
//CLife * CGame::m_pLife = NULL;
bool CGame::m_bPlayerUse = true;
bool CGame::m_bIsStopUpdate = false;
bool CGame::m_bIsStopUpdateContinue = false;
CCamera* CGame::m_pCamera = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_pPlayerControl = nullptr;
	m_nGameCount	= 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ��������
//=============================================================================
CGame * CGame::Create(void)
{
	CGame *pGame;
	pGame = new CGame;
	if (pGame != nullptr)
	{
		pGame->Init();
	}
	return pGame;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init()
{
	//�I�u�W�F�N�g����
	CManager::CreateCamera();
	CManager::CreateLight();
	CFloor::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 500.0f));
	CEbi::Create(D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CEgg::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CSalmon::Create(D3DXVECTOR3(70.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CTuna::Create(D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CIkura::Create(D3DXVECTOR3(110.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	m_pPlayerControl = new CPlayerControl;
	m_pPlayerControl->Init();
	m_pCamera = CManager::GetCamera();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	//�T�E���h
	CSound * pSound = CManager::GetSound();
	//�L�[�{�[�h�̎擾
	CKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	m_pPlayerControl->Update();
	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		//�J�����Ƀv���C���[�̈ʒu��`����
		m_pCamera->SetPos(nPlayer, m_pPlayerControl->GetPlayer(nPlayer)->GetPos());
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
}


