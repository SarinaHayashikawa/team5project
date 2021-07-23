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

//=============================================================================
//クラス定義
//=============================================================================
class CPlayerControl
{
public:
	CPlayerControl(int nPriority = 3);
	~CPlayerControl();
	HRESULT	Init(void);												// 初期化処理関数
	void	Update(void);											// 更新処理関数
	CPlayer * GetPlayer(int nPlayer) { return m_pPlayer[nPlayer]; }	// プレイヤーゲッター関数
private:
	void RespawnControl(int nPlayer);		// プレイヤーのリスポーン
	void DamageHit(int nPlayer);			// 他のプレイヤーの当たった際のダメージ処理
	void PlayerHit(int nPlayer);			// プレイヤーのヒット処理
	void PlayerControl(int nPlayer);		// プレイヤー操作関数

	CPlayer*		m_pPlayer[MAX_PLAYER];		// プレイヤーポインタ
	int				m_nRespawn[MAX_PLAYER];		// プレイヤーのリスポーンカウント
	static D3DXVECTOR3 m_PlayerPos[MAX_PLAYER];	// プレイヤーの位置

};
#endif // !_BLOCK_H_

