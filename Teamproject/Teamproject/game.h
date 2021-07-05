//=============================================================================
//
// ゲームシーン処理 [game.h]
// Author : 林川紗梨夏
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"

//*****************************************************************************
// 前方宣言
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
//マネージャークラス
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
	int    m_nGameCount;//ゲームカウント

	typedef struct 	//分割カメラ
	{
		D3DXVECTOR3 Pos;			// 位置
		D3DXVECTOR3 LookPosition;	// 注視点
	}CameraDivided;
	static CameraDivided m_pCameraDivided[4];//分割カメラの情報

	static bool m_bPlayerUse;//プレイヤーが使われているか
	static bool m_bIsStopUpdate;//アップデート停止しているか
	static bool m_bIsStopUpdateContinue;//コンティニュー発生しているか
};
#endif