//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : 
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
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
//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
//CLife * CGame::m_pLife = NULL;
bool CGame::m_bPlayerUse = true;
bool CGame::m_bIsStopUpdate = false;
bool CGame::m_bIsStopUpdateContinue = false;

CGame::CameraDivided CGame::m_pCameraDivided[4] =
{
	{ D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f) },
	{ D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f) },
	{ D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f) },
	{ D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f) },
};

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
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
	CFloor::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 500.0f));
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//CPlayerParts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	CEbi::Create(D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CEgg::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CSalmon::Create(D3DXVECTOR3(70.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CTuna::Create(D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CIkura::Create(D3DXVECTOR3(110.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));

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

	////ポーズ中,コンティニュー画面ではない時、UPDATE可能な時更新
	//if (m_bIsStopUpdate == false && m_bIsStopUpdateContinue == false && m_bIsStopUpdate == false)
	//{
	//		if (lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(7) || pInputKeyboard->GetKeyboardTrigger(DIK_P))//ポーズ
	//		{
	//			//更新を止める
	//			m_bIsStopUpdate = true;
	//		}
	//}

	m_nGameCount++;

	//if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))//スタート
	//{
	//	CManager::SetMode(CManager::MODE_TITLE);
	//	return;
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}