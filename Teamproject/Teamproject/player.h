//=============================================================================
//
// プレイヤー [player.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "scene3d.h"
#include "model.h"
#include "food base.h"
//=============================================================================
// 前方宣言
//=============================================================================
class CPlayerParts;
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PARTS (20)	//最大パーツ数

//=============================================================================
//クラス定義
//=============================================================================
class CPlayer : public CModel
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer();
	typedef enum	//プレイヤーの状態
	{
		PLAYER_STATS_NONE = 0,	// NULL
		PLAYER_STATS_NORMAL,	// 通常状態
		PLAYER_STATS_REPEL,		// はじかれ状態
		PLAYER_STATS_DEATH		// 死
	}PLAYER_STATS;

	static CPlayer* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size);	//生成処理

	void			Update(void);
	void			AddParts(CFoodBase::FOOD_TYPE FoodType);		// パーツ追加（食べ物を食べた後の追加パーツ）処理関数
	void			RotControl(D3DXVECTOR3 Control);				// コントローラーでの操作
	void			Dash(bool bDash);								// ダッシュ状態に移行
	void			DamageHit(void);								// プレイヤーがダメージを受けるモノにぶつかった際の処理
	void			Repel(CScene3d* Player);						// はじかれる処理
	void			Respawn(D3DXVECTOR3 RespawnPos);				// リスポーン処理

	CPlayerParts*	GetParts(int nParts) { return m_pParts[nParts]; }	// パーツゲッター
	int				GetPartsCount(void) { return m_nParts; }			// パーツ数ゲッター
	PLAYER_STATS	GetStats(void) { return m_PlayerStats; }			// プレイヤー状態ゲッター
private:

	void			Death(void);			// 死亡処理
	void			Move(void);				// 移動処理
	void			Rot(void);				// 向き処理
	void			RepelMove(void);		// はじかれ移動処理

	const int		m_nModel = 1;			// モデル番号
	PLAYER_STATS	m_PlayerStats;			// プレイヤーステータス
	int				m_nLife;				// ライフ
	int				m_nRepelFrameCount;		// はじかれた際の移動時のフレーム
	int				m_nDeathFrameCount;		// 死亡した際のフレーム
	float			m_fDashCoutn;			// 加速値
	D3DXVECTOR3		m_RotMove;				// 向きの移動量
	D3DXVECTOR3		m_RepelMove;			// はじかれ移動量
	bool			m_bInvincible;			// 無敵状態のスイッチ
	bool			m_bDashSwitch;			// 加速切替スイッチ
	int				m_nParts;				// パーツ数
	CPlayerParts*	m_pParts[MAX_PARTS];	// パーツポインタ
};
#endif // !_PLAYER_H_


