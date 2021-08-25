//=============================================================================
//
// プレイヤー操作 [player control.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _PLAYER_CONTROL_H_
#define _PLAYER_CONTROL_H_

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "scene3d.h"
#include "model.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CPlayer;
class CScene;
class CScore;
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_NPC (MAX_PLAYER - 1)	// NPCの最大数（-1するのは1人はプレイヤーがいるため）

//=============================================================================
//クラス定義
//=============================================================================
class CPlayerControl : public CScene
{
public:
	CPlayerControl(int nPriority = 3);
	~CPlayerControl();
	static CPlayerControl *Create();	// 生成処理関数
	HRESULT	Init(void);					// 初期化処理関数
	void	Uninit(void);				// 終了処理関数
	void	Update(void);				// 更新処理関数
	void	Draw(void);					// 描画処理関数

	CPlayer * GetPlayer(int nPlayer) { return m_pPlayer[nPlayer]; }	// プレイヤーゲッター関数
private:

	void RespawnControl(int nPlayer);		// プレイヤーのリスポーン
	void DamageHit(int nPlayer);			// 他のプレイヤーの当たった際のダメージ処理
	void PlayerHit(int nPlayer);			// プレイヤーのヒット処理
	void PlayerControl(int nPlayer);		// プレイヤー操作関数
	
	void NpcControl(int nNpc);				// NPC操作関数
	void PlayerProcessCriteria(int nNpc);	// NPCとプレイヤーの関係処理
	void ItemProcessCriteria(int nNpc);		// NPCとアイテムの関係処理
	void SushiProcessCriteria(int nNpc);	// NPCと寿司の関係処理
	void NpcRandomProbability(int nNpc);	// 確率で向きをランダムに変更
	void NpcRandomControl(int nNpc);		// ランダム向き移動
	void TargetSwitching(int nNpc);			// ターゲット切替関数
	void NpcRandomCount(int nNpc);			// ランダム向き移動(長時間)
	void AvoidBarrier(int nNpc);			// バリアを避ける処理

	typedef struct
	{
		D3DXVECTOR3 m_TargetRot;				// 目的の向き
		int			m_nRandomCount;				// ランダム向き移動用のカウント
		int			m_nTargetCount;				// ターゲットの切り替えようのカウント
		bool		m_bRandomControl;			// ランダム移動状態かどうか
		CScene*		m_pTarget;					// 現在のターゲットシーン
		CScene*		m_pOldTarget;				// 記憶しているターゲットシーン
	}NPC_DATA;

	const int		m_nPlayerModel[MAX_PLAYER] = { 1,2,3,4 };		// プレイヤーモデル番号

	CPlayer*		m_pPlayer[MAX_PLAYER];				// プレイヤーポインタ
	int				m_nRespawn[MAX_PLAYER];				// プレイヤーのリスポーンカウント
	static D3DXVECTOR3 m_PlayerPos[MAX_PLAYER];	// プレイヤーの位置
	static D3DXVECTOR3 m_Score[MAX_PLAYER];		// スコアの位置
	CScore*			m_pScore[MAX_PLAYER];				// スコアポインタ
	int				m_nNumberPlayer;					// プレイヤーの人数
	NPC_DATA		m_NpcData[MAX_NPC];					// NPCの情報
};
#endif // !_PLAYER_CONTROL_H_

