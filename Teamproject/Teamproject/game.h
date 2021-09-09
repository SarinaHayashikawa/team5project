//=============================================================================
//
// ゲームシーン処理 [game.h]
// Author : 林川紗梨夏
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include "camera.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CInput;
class CScene2D;
class CCamera;
class CScore;
class CPlayerControl;
class CTimer;
class CMapManager;
//=============================================================================
//マネージャークラス
//=============================================================================
class CGame : public CScene
{
public:

	typedef enum	//ゲームの状態(範囲縮小やプレイヤーリスポーンの管理用)
	{
		STATS_1 = 0,	//初期状態
		STATS_2,
		STATS_3,
		STATS_4,
		STATS_5,		//ここでプレイヤーリスポーン不可
	}GAME_STATS;


	CGame();
	~CGame();
	static CGame *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void GameOut(void);		// ゲーム終了時の処理

	CScene2D * GetScene(void) { return m_pScene; };
	CGame * GetManager(void) { return this; };

	static bool GetIsStopUpdate(void) { return m_bIsStopUpdate; };
	static void SetIsStopUpdate(bool bIsStopUpdate) { m_bIsStopUpdate = bIsStopUpdate; };
	static bool GetIsStopUpdateContinue(void) { return m_bIsStopUpdateContinue; };
	static void SetIsStopUpdateContinue(bool bIsStopUpdateContinue) { m_bIsStopUpdateContinue = bIsStopUpdateContinue; };
	static CTimer * GetTimer(void) { return m_pTimer; };
private:
	CScene2D*		m_pScene;				// シーンポインタ
	int				m_nGameCount;			// ゲームカウント
	CPlayerControl* m_pPlayerControl;		// プレイヤーコントロールポインタ
	CMapManager *	m_pMapManager;			// マップマネージャーポインタ
	GAME_STATS		GameStats;				// ゲームの進行状況
	static CCamera*	m_pCamera;				// カメラポインタ
	static CTimer*	m_pTimer;				// タイムポインタ
	static D3DXVECTOR3 m_Score[MAX_PLAYER];	// スコアの位置

	static bool		m_bPlayerUse;			// プレイヤーが使われているか
	static bool		m_bIsStopUpdate;		// アップデート停止しているか
	static bool		m_bIsStopUpdateContinue;// コンティニュー発生しているか
};
#endif