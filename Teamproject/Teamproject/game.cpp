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
#include<stdio.h>
#include<string.h>
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "sound.h"
#include "input.h"
#include "joystick.h"
#include "game.h"
#include "scene2D.h"
#include "camera.h"
#include "light.h"
#include "sound.h"
#include "floor.h"
//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
//CLife * CGame::m_pLife = NULL;
bool CGame::m_bPlayerUse = true;
bool CGame::m_bIsStopUpdate = false;
bool CGame::m_bIsStopUpdateContinue = false;
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
	CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 500.0f));
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