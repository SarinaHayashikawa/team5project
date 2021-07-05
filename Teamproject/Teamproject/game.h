//=============================================================================
//
// �Q�[���V�[������ [game.h]
// Author : �ѐ�ї���
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"

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
	CScene2D * GetScene(void) { return m_pScene; };
	CGame * GetManager(void) { return this; };

	static bool GetIsStopUpdate(void) { return m_bIsStopUpdate; };
	static void SetIsStopUpdate(bool bIsStopUpdate) { m_bIsStopUpdate = bIsStopUpdate; };
	static bool GetIsStopUpdateContinue(void) { return m_bIsStopUpdateContinue; };
	static void SetIsStopUpdateContinue(bool bIsStopUpdateContinue) { m_bIsStopUpdateContinue = bIsStopUpdateContinue; };
private:
	CScene2D * m_pScene;
	int    m_nGameCount;//�Q�[���J�E���g

	typedef struct 	//�����J����
	{
		D3DXVECTOR3 Pos;			// �ʒu
		D3DXVECTOR3 LookPosition;	// �����_
	}CameraDivided;
	static CameraDivided m_pCameraDivided[4];//�����J�����̏��

	static bool m_bPlayerUse;//�v���C���[���g���Ă��邩
	static bool m_bIsStopUpdate;//�A�b�v�f�[�g��~���Ă��邩
	static bool m_bIsStopUpdateContinue;//�R���e�B�j���[�������Ă��邩
};
#endif