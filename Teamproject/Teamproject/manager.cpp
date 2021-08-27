//=============================================================================
//
// �Ǘ����� [manager.cpp]
// Author : �ѐ�ї���
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "sound.h"
#include "joystick.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "camera.h"
#include "light.h"
#include "resource manager.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CRenderer * CManager::m_pRenderer = nullptr;
CKeyboard * CManager::m_pKeyboard = nullptr;
CJoystick * CManager::m_pJoystick = nullptr;
CMouse * CManager::m_pMouse	= nullptr;
CSound * CManager::m_pSound = nullptr;
CGame * CManager::m_pGame = nullptr;
CResult * CManager::m_pResult = nullptr;
CTitle * CManager::m_pTitle = nullptr;
CSelect * CManager::m_pSelect = nullptr;
CCamera *CManager::m_pCamera = nullptr;
CLight *CManager::m_pLight = nullptr;
CManager::MODE CManager::m_mode = MODE_NONE;
CPlayer * CManager::m_pPlayer = nullptr;
CMapManager * CManager::m_pMapManager = nullptr;
HWND CManager::m_hWnd = nullptr;
CResource * CManager::m_pResource = nullptr;
CScore * CManager::m_apScore[MAX_PLAYER] = {};
CPlayerControl * CManager::m_pPlayerControl = nullptr;
int CManager::m_nPlayerNumber = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
	m_hWnd = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	//�����_���[�̐���
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;
	}
	//�����_���[�̏�����
	m_pRenderer->Init(hWnd, bWindow);

	//���͂̐���
	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CKeyboard;
	}
	//�L�[�{�[�h�̏�����
	m_pKeyboard->Init(hInsitance, hWnd);

	//���͂̐���
	if (m_pMouse == nullptr)
	{
		m_pMouse = new CMouse;
	}
	//�}�E�X�̏�����
	m_pMouse->Init(hInsitance, hWnd);

	//�W���C�X�e�B�b�N�̐���
	if (m_pJoystick == nullptr)
	{
		m_pJoystick = new CJoystick;
	}
	//�W���C�X�e�B�b�N�̏�����
	m_pJoystick->Init(hInsitance, hWnd);

	//�T�E���h�̐���
	if (m_pSound == nullptr)
	{
		m_pSound = new CSound;
	}
	//�T�E���h�̏�����
	m_pSound->Init(hWnd);

	//�J�[�\�������Ȃ�����
	//ShowCursor(FALSE);

	//�S�Ẵ��\�[�X�ǂݍ���
	if (m_pResource == nullptr)
	{
		m_pResource = new CResource;
	}
	m_pResource->Init();

	SetMode(MODE_GAME);

	m_hWnd = hWnd;
	return S_OK;
}

//=============================================================================	
// �I�������֐�
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	//�T�E���h�̒�~
	m_pSound->StopSound();

	//�T�E���h�̔j��
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//�W���C�X�e�B�b�N�̔j��
	if (m_pJoystick != nullptr)
	{
		m_pJoystick->Uninit();
		delete m_pJoystick;
		m_pJoystick = nullptr;
	}

	//�}�E�X�̔j��
	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	//�L�[�{�[�h�̔j��
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	//�J�����̏I��
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//�����_���[�̔j��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�S�Ẵ��\�[�X�j��
	if (m_pResource != nullptr)
	{
		m_pResource->Uninit();
		delete m_pResource;
		m_pResource = nullptr;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Update();
	}

	//�}�E�X�̍X�V
	if (m_pMouse != nullptr)
	{
		m_pMouse->Update();
	}

	//�W���C�X�e�B�b�N�̍X�V
	if (m_pJoystick != nullptr)
	{
		m_pJoystick->Update();
	}

	//�J�����̍X�V����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	//�`��̍X�V
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CManager::Draw(void)
{
	if (m_pCamera != nullptr)
	{
		// ���݂̃V�[���󋵂ŉ�ʕ���������
		// �Q�[���V�[���ȊO�̏ꍇ�������Ȃ�
		if (m_mode!= MODE_GAME)
		{
			m_pCamera->SetUpViewport();
			m_pCamera->SetCamera();
			m_pRenderer->Draw();
		}
		// �Q�[���V�[���̏ꍇ��������
		else
		{
			for (int nCamera = 0; nCamera<MAX_PLAYER; nCamera++)
			{
				m_pCamera->SetUpViewport(nCamera);
				m_pCamera->SetCamera(nCamera);
				m_pRenderer->Draw();
			}
		}
	}
}

//=============================================================================
// ���[�h�ݒ�֐�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_pPlayer = nullptr;
	//m_pMapManager = nullptr;
	CScene::ReleaseAll();

	//���[�h�̊��蓖��
	m_mode = mode;

	//���[�h�̐؂�ւ�
	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;
	case MODE_SELECT:
		//m_pSelect = CSelect::Create();
		break;
	case MODE_GAME:
		m_pGame = CGame::Create();
		break;
	case MODE_RESULT:
		m_pResult = CResult::Create();
		break;
	}
}

//=============================================================================
//  �J��������
//=============================================================================
void CManager::CreateCamera(void)
{
	// m_pCamera��NULL�̏ꍇ
	if (m_pCamera == nullptr)
	{
		// �������m��
		m_pCamera = new CCamera;

		// m_pCamera��NULL�łȂ��ꍇ
		if (m_pCamera != nullptr)
		{
			// ������
			m_pCamera->Init();
		}
	}
}

//=============================================================================
//  ���C�g����
//=============================================================================
void CManager::CreateLight(void)
{
	// m_pLight��NULL�̏ꍇ
	if (m_pLight == nullptr)
	{
		// �������m��
		m_pLight = new CLight;

		// m_pLight��NULL�łȂ��ꍇ
		if (m_pLight != nullptr)
		{
			// ������
			m_pLight->Init();
		}
	}
}
//=============================================================================
//  �J�������蓖��
//=============================================================================
void CManager::BindCamera(CCamera * pCamera)
{
	m_pCamera = pCamera;
}
//=============================================================================
//  �E�B���h�E���A�N�e�B�u���`�F�b�N
//=============================================================================
bool CManager::GetIsActiveWindow(void)
{
	bool bActive = false;
	if (GetForegroundWindow() == m_hWnd)
	{
		bActive = true;
	}
	else
	{
		bActive = false;
	}
	return bActive;
}
//=============================================================================
//  �X�R�A�|�C���^�Z�b�g
//=============================================================================
void CManager::SetScore(CScore * pScore, int nPlayer)
{
	m_apScore[nPlayer] = pScore;
}
//=============================================================================
//  �v���C���[�Ǘ��|�C���^�Z�b�g
//=============================================================================
void CManager::SetPlayerControl(CPlayerControl * pPlayerControl)
{
	m_pPlayerControl = pPlayerControl;
}

//=============================================================================
// �v���C���[�l���Z�b�^�[
//=============================================================================
void CManager::SetPlayerNumber(const int nNumber)
{
	m_nPlayerNumber = nNumber;
}
