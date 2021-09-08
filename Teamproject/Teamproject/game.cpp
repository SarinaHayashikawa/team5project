//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author:
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "manager.h"
#include "camera.h"
#include "scene.h"
#include "sound.h"
#include "joystick.h"
#include "game.h"
#include "sound.h"
#include "floor.h"
#include "player.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "tuna.h"
#include "salmon.h"
#include "player parts.h"
#include "renderer.h"
#include "player control.h"
#include "score.h"
#include "map_manager.h"
#include "map.h"
#include "Shield.h"
#include "scoreup.h"
#include "Fieldmanager.h"
#include "timer.h"
#include "manager.h"
#include "keyboard.h"
#include "ShieldEffect.h"
#include "timerBg.h"

//=============================================================================
// 静的メンバ変数初期化
//=============================================================================
bool CGame::m_bPlayerUse = true;
bool CGame::m_bIsStopUpdate = false;
bool CGame::m_bIsStopUpdateContinue = false;
CCamera* CGame::m_pCamera = nullptr;
CTimer* CGame::m_pTimer = nullptr;
D3DXVECTOR3 CGame::m_Score[MAX_PLAYER] =
{
	D3DXVECTOR3(150.0f, 30.0f, 0.0f),
	D3DXVECTOR3(1250.0f, 30.0f, 0.0f),
	D3DXVECTOR3(150.0f, 385.0f, -50.0f),
	D3DXVECTOR3(1250.0f, 385.0f, -50.0f)

};

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	m_pMapManager = nullptr;
	m_pPlayerControl = nullptr;
	m_nGameCount	= 0;
	m_nGameCount = 0;

}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CGame * CGame::Create(void)
{
	CGame *pGame;
	pGame = new CGame;
	if (pGame != nullptr)
	{
		pGame->Init();
	}
	return pGame;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init()
{
	//オブジェクト生成
	CManager::CreateCamera();
	CManager::CreateLight();

	//デバックのためのアイテム生成
	CEbi::Create(D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CEgg::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CSalmon::Create(D3DXVECTOR3(70.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CTuna::Create(D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CIkura::Create(D3DXVECTOR3(110.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CShield::Create(D3DXVECTOR3(-55.0f, 0.0f, -80.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	CScoreup::Create(D3DXVECTOR3(-60.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	
	
	//スコア生成
	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		CManager::SetScore(CScore::Create(m_Score[nPlayer], D3DXVECTOR3(30.0f, 60.0f, 0.0f)), nPlayer);
	}
	
	//カメラ設定
	m_pCamera = CManager::GetCamera();
	
	//全てのプレイヤーの管理(プレイヤー4人の生成処理とプレイヤー関係のマネージャー)	
	CManager::SetPlayerControl(CPlayerControl::Create());//情報ほしいのでマネージャーにセットしてほしいです
	
	//マップ作成（ここでミニマップ、管理処理も生成する）
	m_pMapManager = CMapManager::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f));

	//タイム生成
	CtimerBg::Create(TIMER_POSBG, TIMERBG_SIZE, D3DCOLOR_RGBA(255, 255, 255, 255));
	m_pTimer = CTimer::Create(TIMER_POS, TIMER_SIZE, MOOD1_MINUTES, MOOD1_SECONDS);

	//サウンド処理
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::LABEL_BGM_GAME);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	//サウンドストップ
	CSound *pSound = CManager::GetSound();
	pSound->StopSound();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	//サウンド
	CSound * pSound = CManager::GetSound();
	//キーボードの取得
	CKeyboard * pInputKeyboard = CManager::GetInputKeyboard();

	//カメラにプレイヤーの位置を伝える
	for (int nPlayer = 0; nPlayer < MAX_PLAYER; nPlayer++)
	{
		m_pCamera->SetPos(nPlayer, CManager::GetPlayerControl()->GetPlayer(nPlayer)->GetPos());
	}
	//ステージサイズセット
	CManager::GetPlayerControl()->SetMapSize(m_pMapManager->GetMapSize());
	//制限時間を過ぎた際の処理
	GameOut();

	//デバック
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		CManager::SetMode(CManager::MODE_RESULT);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// ゲーム終了時の処理
//=============================================================================
void CGame::GameOut(void)
{
	//制限時間が来たら
	if (m_pTimer->GetTimeUp() == true)
	{
		//画面遷移
		CManager::SetMode(CManager::MODE_RESULT);
	}
}
