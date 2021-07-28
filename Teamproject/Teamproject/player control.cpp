//=============================================================================
//
//	プレイヤー操作 [player control.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "player control.h"
#include "player.h"
#include "joystick.h"
#include "manager.h"
#include "player parts.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SIZE			(7.0f)	// プレイヤーの当たり判定のサイズ
#define PLAYER_DEATH		(30*3)	// プレイヤーが死亡時間
//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
D3DXVECTOR3 CPlayerControl::m_PlayerPos[MAX_PLAYER] = 
{
	D3DXVECTOR3(-50.0f, 0.0f, 0.0f),
	D3DXVECTOR3(50.0f, 0.0f, 0.0f),
	D3DXVECTOR3(-50.0f, 0.0f, -50.0f),
	D3DXVECTOR3(50.0f, 0.0f, -50.0f)
};

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayerControl::CPlayerControl(int nPriority)
{
	for (int nPlayer = 0; nPlayer<MAX_PLAYER; nPlayer++)
	{
		m_pPlayer[nPlayer] = nullptr;
		m_nRespawn[nPlayer] = 0;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayerControl::~CPlayerControl()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CPlayerControl * CPlayerControl::Create()
{
	//メモリ確保
	CPlayerControl *pPlayerControl = nullptr;
	pPlayerControl = new CPlayerControl;

	if (pPlayerControl != nullptr)
	{
		pPlayerControl->Init();
	}
	return pPlayerControl;

}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPlayerControl::Init(void)
{
	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		m_pPlayer[nPlayer] = CPlayer::Create(m_PlayerPos[nPlayer], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPlayerControl::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPlayerControl::Update(void)
{
	for (int nPlayer = 0; nPlayer<MAX_PLAYER; nPlayer++)
	{
		//NULLチェック
		if (m_pPlayer[nPlayer] != nullptr)
		{
			//プレイヤー一人ひとりの操作管理
			PlayerControl(nPlayer);
			//プレイヤー同士の当たり判定
			PlayerHit(nPlayer);
			//プレイヤーのダメージ判定
			DamageHit(nPlayer);
			//リスポーン処理
			RespawnControl(nPlayer);
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPlayerControl::Draw(void)
{
}

//=============================================================================
// プレイヤーのリスポーン処理関数
//=============================================================================
void CPlayerControl::RespawnControl(int nPlayer)
{
	if (m_pPlayer[nPlayer]->GetStats()== CPlayer::PLAYER_STATS_DEATH)
	{
		//リスポーンカウント
		m_nRespawn[nPlayer]++;

		//リスポーンカウントが一定に達したら
		if (m_nRespawn[nPlayer] >= PLAYER_DEATH)
		{
			//リスポーン処理
			m_pPlayer[nPlayer]->Respawn(m_PlayerPos[nPlayer]);
			//リスポーンカウントの初期化
			m_nRespawn[nPlayer] = 0;
		}
	}
}

//=============================================================================
// 他のプレイヤーの当たった際のダメージ処理
//=============================================================================
void CPlayerControl::DamageHit(int nPlayer)
{
	//NULLチェック
	if (m_pPlayer[nPlayer] != nullptr)
	{
		for (int nPlayerCount = 0; nPlayerCount < MAX_PLAYER; nPlayerCount++)
		{
			if (m_pPlayer[nPlayerCount] != nullptr
				&& nPlayer != nPlayerCount)
			{
				//プレイヤーの位置
				D3DXVECTOR3 PlayerPos = m_pPlayer[nPlayer]->GetPos();
				//あてられたプレイヤーのパーツ数
				int nPlayerParts = m_pPlayer[nPlayerCount]->GetPartsCount();

				for (int nPartsCount = 0; nPartsCount<nPlayerParts; nPartsCount++)
				{
					//パーツの位置
					D3DXVECTOR3 PartsPos = m_pPlayer[nPlayerCount]->GetParts(nPartsCount)->GetPos();

					//プレイヤーとパーツの距離を計算
					float RangeX = PlayerPos.x - PartsPos.x;
					float RangeZ = PlayerPos.z - PartsPos.z;
					float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

					//範囲に入っているか
					if (Range <= PLAYER_SIZE + PLAYER_SIZE)
					{
						//プレイヤーの処理
						m_pPlayer[nPlayer]->DamageHit();
						return;
					}
				}

			}
		}
	}
}

//=============================================================================
//プレイヤーの同士のヒット処理関数
//=============================================================================
void CPlayerControl::PlayerHit(int nPlayer)
{
	//NULLチェック
	if (m_pPlayer[nPlayer] != nullptr)
	{
		//一度処理をした部分を省くために+1
		int nPlayerCount = nPlayer + 1;
		//プレイヤー同士の処理
		for (nPlayerCount; nPlayerCount < MAX_PLAYER; nPlayerCount++)
		{
			//プレイヤーのポインタのNULLチェック
			if (m_pPlayer[nPlayerCount] != nullptr)
			{
				//相手プレイヤーの状態チェック
				if (m_pPlayer[nPlayerCount]->GetStats()== CPlayer::PLAYER_STATS_NORMAL)
				{
					//プレイヤーの位置
					D3DXVECTOR3 PlayerPos = m_pPlayer[nPlayer]->GetPos();
					//あてられたプレイヤーの位置
					D3DXVECTOR3 HitPlayerPos = m_pPlayer[nPlayerCount]->GetPos();
					//プレイヤー同士の距離を計算
					float RangeX = PlayerPos.x - HitPlayerPos.x;
					float RangeZ = PlayerPos.z - HitPlayerPos.z;
					float Range = (float)(sqrt(RangeX * RangeX + RangeZ * RangeZ));

					//プレイヤーが近くにいるか
					if (Range <= PLAYER_SIZE + PLAYER_SIZE)
					{
						//プレイヤー同士の判定
						m_pPlayer[nPlayer]->Repel(m_pPlayer[nPlayerCount]);
						m_pPlayer[nPlayerCount]->Repel(m_pPlayer[nPlayer]);
						return;
					}
				}
			}
		}
	}
}

//=============================================================================
// プレイヤー操作処理関数
//=============================================================================
void CPlayerControl::PlayerControl(int nPlayer)
{
	// コントローラーの取得
	CJoystick* pJoystick = CManager::GetInputJoystick();
	//入力先
	D3DXVECTOR3 Joystic = D3DXVECTOR3((float)pJoystick->GetJoyStick(nPlayer).lX, (float)-pJoystick->GetJoyStick(nPlayer).lY, 0.0f);
	// プレイヤーの操作 
	m_pPlayer[nPlayer]->RotControl(Joystic);
	//プレイヤーの加速操作
	if (pJoystick->GetJoystickPress(JS_A, nPlayer))
	{
		m_pPlayer[nPlayer]->Dash(true);
	}
	else
	{
		m_pPlayer[nPlayer]->Dash(false);
	}

}
