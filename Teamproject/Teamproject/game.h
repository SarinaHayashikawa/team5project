//=============================================================================
//
// �Q�[���V�[������ [game.h]
// Author : �ѐ�ї���
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include "camera.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CInput;
class CKeyboard;
class CJoystick;
class CRenderer;
class CScene2D;
class CTitle;
class CEnemy;
class CSound;
class CCamera;
class CLight;
class CPlayer;
class CScore;
class CPlayerControl;
class CTimer;
//=============================================================================
//�}�l�[�W���[�N���X
//=============================================================================
class CGame : public CScene
{
public:
	CGame();
	~CGame();
	static CGame *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void GameOut(void);

	CScene2D * GetScene(void) { return m_pScene; };
	CGame * GetManager(void) { return this; };

	static bool GetIsStopUpdate(void) { return m_bIsStopUpdate; };
	static void SetIsStopUpdate(bool bIsStopUpdate) { m_bIsStopUpdate = bIsStopUpdate; };
	static bool GetIsStopUpdateContinue(void) { return m_bIsStopUpdateContinue; };
	static void SetIsStopUpdateContinue(bool bIsStopUpdateContinue) { m_bIsStopUpdateContinue = bIsStopUpdateContinue; };
	static CTimer * GetTimer(void) { return m_pTimer; };
private:
	CScene2D*	m_pScene;				//�V�[���|�C���^
	int			m_nGameCount;			//�Q�[���J�E���g
	CPlayerControl* m_pPlayerControl;	//�v���C���[�R���g���[���|�C���^
	static CCamera*	m_pCamera;			//�J�����|�C���^
	static CTimer*		m_pTimer;
	static D3DXVECTOR3 m_Score[MAX_PLAYER];		// �X�R�A�̈ʒu

	static bool		m_bPlayerUse;				//�v���C���[���g���Ă��邩
	static bool		m_bIsStopUpdate;			//�A�b�v�f�[�g��~���Ă��邩
	static bool		m_bIsStopUpdateContinue;	//�R���e�B�j���[�������Ă��邩
};
#endif