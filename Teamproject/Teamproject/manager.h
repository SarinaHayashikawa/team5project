//=============================================================================
//
// �Ǘ� [manager.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER (4)
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CKeyboard;
class CJoystick;
class CScene2d;
class CSound;
class CCamera;
class CLight;
class CMode;
class CGame;
class CPlayer;
class CMouse;
class CMapManager;
class CTitle;
class CSelect;
class CResource;
class CScore;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,
		MODE_SELECT,
		MODE_GAME,
		MODE_TUTORIAL,
		MODE_RESULT,
		MODE_RANKING,
		MODE_END
	}MODE;
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; };
	static CRenderer * GetRenderer(void) { return m_pRenderer; };
	static CKeyboard * GetInputKeyboard(void) { return m_pKeyboard; };
	static CMouse * GetInputMouse(void) { return m_pMouse; };
	static CJoystick * GetInputJoystick(void) { return m_pJoystick; };
	static CSound * GetSound(void) { return m_pSound; };
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; };
	static CScore * GetScore(int nPlayer) { return m_apScore[nPlayer]; };
	static void SetScore(CScore * pScore, int nPlayer);
	static void CreateCamera(void);
	static void CreateLight(void);
	static void CManager::BindCamera(CCamera* pCamera);
	static bool GetIsActiveWindow(void);
	static CResource* GetResource(void) { return m_pResource; };			//���\�[�X�Q�b�^�[
private:
	static CRenderer * m_pRenderer;
	static CKeyboard * m_pKeyboard;
	static CJoystick * m_pJoystick;
	static CMouse * m_pMouse;
	static CSound * m_pSound;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CPlayer * m_pPlayer;
	static MODE m_mode;
	static CGame * m_pGame;
	static CTitle * m_pTitle;
	static CSelect * m_pSelect;
	static CMapManager * m_pMapManager;
	static HWND m_hWnd;
	static CResource* m_pResource;		//���\�[�X�|�C���^
	static CScore * m_apScore[MAX_PLAYER];//�v���C���[�X�R�A
};
#endif