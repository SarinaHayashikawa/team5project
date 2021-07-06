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
#include "scene.h"
#include "sound.h"
#include "joystick.h"
#include "game.h"
#include "sound.h"
#include "floor.h"
#include "player.h"
#include "ebi.h"
#include "score.h"
#include "map_manager.h"
#include "map.h"
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
//CLife * CGame::m_pLife = NULL;
bool CGame::m_bPlayerUse = true;
bool CGame::m_bIsStopUpdate = false;
bool CGame::m_bIsStopUpdateContinue = false;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_nGameCount = 0;
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
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	CEbi::Create(D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	
	//�v���C���[�����ɐ���
	CManager::SetScore(CScore::Create(D3DXVECTOR3(180.0f, 50.0f, 0.0f), SCORE_SIZE),  0);
	CManager::SetScore(CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 80.0f, 50.0f, 0.0f), SCORE_SIZE), 1);
	CManager::SetScore(CScore::Create(D3DXVECTOR3(180.0f, SCREEN_HEIGHT/2 + 50.0f, 0.0f), SCORE_SIZE), 2);
	CManager::SetScore(CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 80.0f, SCREEN_HEIGHT / 2 + 50.0f, 0.0f), SCORE_SIZE), 3);
	//�~�j�}�b�v����
	CMapManager::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
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

	////�|�[�Y��,�R���e�B�j���[��ʂł͂Ȃ����AUPDATE�\�Ȏ��X�V
	//if (m_bIsStopUpdate == false && m_bIsStopUpdateContinue == false && m_bIsStopUpdate == false)
	//{
	//		if (lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(7) || pInputKeyboard->GetKeyboardTrigger(DIK_P))//�|�[�Y
	//		{
	//			//�X�V���~�߂�
	//			m_bIsStopUpdate = true;
	//		}
	//}

	m_nGameCount++;

	//if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))//�X�^�[�g
	//{
	//	CManager::SetMode(CManager::MODE_TITLE);
	//	return;
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}