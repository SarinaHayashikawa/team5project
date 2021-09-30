//=============================================================================
//
// ���U���g���� [result.cpp]
// Author:
//
//=============================================================================
//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "result.h"
#include "winner player.h"
#include "manager.h"
#include "camera.h"
#include "score.h"
#include "winner.h"
#include "classifier.h"
#include "player number.h"
#include "result effect.h"
#include "sound.h"
//=============================================================================
// �ÓI�����o�ϐ�������
//=============================================================================
CCamera* CResult::m_pCamera = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	m_pScore = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// ��������
//=============================================================================
CResult * CResult::Create(void)
{
	CResult *pResult;
	pResult = new CResult;
	if (pResult != nullptr)
	{
		pResult->Init();
	}
	return pResult;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(void)
{
	//�J��������
	CManager::CreateCamera();
	//�J�����ݒ�
	m_pCamera = CManager::GetCamera();
	//�J�����ʒu�ݒ�
	m_pCamera->SetPos(0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//���C�g�ݒ�
	CManager::CreateLight();

	//���҃��f���̕\��
	CWinnerPlayer::Create(D3DXVECTOR3(0.0f, 80.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1);

	//����UI
	CWinner::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 6, 0.0f), D3DXVECTOR3(900.0f, 260.0f, 0.0f));
	
	//�v���C���[UI
	CPlayerNumber::Create(D3DXVECTOR3((SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2.5f), 0.0f), D3DXVECTOR3(110.0f, 110.0f, 0.0f),0);

	//�X�R�A
	ScoreCreate(D3DXVECTOR3((SCREEN_WIDTH / 2) + 200 , (SCREEN_HEIGHT / 2.5f), 0.0f), D3DXVECTOR3(70.0f, 110.0f, 0.0f));

	//�M���ォ��~�炷
	CResultEffect::Create();


	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::LABEL_BGM_RESULT);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	CSound *pSound = CManager::GetSound();
	pSound->StopSound(CSound::LABEL_BGM_RESULT);

}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::ScoreCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�X�R�A����
	m_pScore = CScore::Create(pos, size);
	//m_pScore->SetScore();

	//�X�R�A��������������
	CClassifier::Create(D3DXVECTOR3(pos.x + (size.x*1.2f), pos.y, pos.z), D3DXVECTOR3(size.x * 2, size.y, size.z));
}
