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
#include "timer.h"
//=============================================================================
// 静的メンバ変数初期化
//=============================================================================
bool CGame::m_bPlayerUse = true;
bool CGame::m_bIsStopUpdate = false;
bool CGame::m_bIsStopUpdateContinue = false;
CCamera* CGame::m_pCamera = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
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

	//ステージ生成
	CFloor::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 500.0f));
	
	//デバックのためのアイテム
	CEbi::Create(D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CEgg::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CSalmon::Create(D3DXVECTOR3(70.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CTuna::Create(D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CIkura::Create(D3DXVECTOR3(110.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CShield::Create(D3DXVECTOR3(-50.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CItem::ITEM_SHIELD);
	CScoreup::Create(D3DXVECTOR3(-60.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CItem::ITEM_SCOREUP);
	CTimer::Create(TIMER_POS, TIMER_SIZE, START_MINUTES, START_SECONDS);


	//カメラ設定
	m_pCamera = CManager::GetCamera();
	
	//全てのプレイヤーの管理(プレイヤー4人の生成処理とプレイヤー関係のマネージャー)	
	//m_pPlayerControl = CPlayerControl::Create();
	CManager::SetPlayerControl(CPlayerControl::Create());//情報ほしいのでマネージャーにセットしてほしいです
	
	//ミニマップ生成
	CMapManager::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{

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
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
}