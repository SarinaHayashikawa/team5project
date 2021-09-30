//=============================================================================
//
// リザルト処理 [result.cpp]
// Author:
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "result.h"
#include "winner player.h"
#include "manager.h"
#include "camera.h"
#include "score.h"
#include "winner.h"
#include "classifier.h"
#include "player number.h"
#include "result effect.h"
#include "sound.h"
//=============================================================================
// 静的メンバ変数初期化
//=============================================================================
CCamera* CResult::m_pCamera = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
	m_pScore = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CResult * CResult::Create(void)
{
	CResult *pResult;
	pResult = new CResult;
	if (pResult != nullptr)
	{
		pResult->Init();
	}
	return pResult;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
	//カメラ生成
	CManager::CreateCamera();
	//カメラ設定
	m_pCamera = CManager::GetCamera();
	//カメラ位置設定
	m_pCamera->SetPos(0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//ライト設定
	CManager::CreateLight();

	//勝者モデルの表示
	CWinnerPlayer::Create(D3DXVECTOR3(0.0f, 80.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1);

	//勝利UI
	CWinner::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 6, 0.0f), D3DXVECTOR3(900.0f, 260.0f, 0.0f));
	
	//プレイヤーUI
	CPlayerNumber::Create(D3DXVECTOR3((SCREEN_WIDTH / 3), (SCREEN_HEIGHT / 2.5f), 0.0f), D3DXVECTOR3(110.0f, 110.0f, 0.0f),0);

	//スコア
	ScoreCreate(D3DXVECTOR3((SCREEN_WIDTH / 2) + 200 , (SCREEN_HEIGHT / 2.5f), 0.0f), D3DXVECTOR3(70.0f, 110.0f, 0.0f));

	//皿を上から降らす
	CResultEffect::Create();


	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::LABEL_BGM_RESULT);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	CSound *pSound = CManager::GetSound();
	pSound->StopSound(CSound::LABEL_BGM_RESULT);

}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::ScoreCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//スコア生成
	m_pScore = CScore::Create(pos, size);
	//m_pScore->SetScore();

	//スコア助数詞生成処理
	CClassifier::Create(D3DXVECTOR3(pos.x + (size.x*1.2f), pos.y, pos.z), D3DXVECTOR3(size.x * 2, size.y, size.z));
}
