//=============================================================================
//
// リザルトエフェクト(寿司が降ってくる) [result effect.h]
// Author : 吉田悠人
//
//=============================================================================
//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "result effect.h"
#include "food base.h"
#include "floor.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include "effect sushi.h"
#include <time.h>

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_SPAWN_COUNT (60*1)	//寿司生成のカウント

//=============================================================================
// コンストラクタ
//=============================================================================
CResultEffect::CResultEffect(int nPriority):CScene(nPriority)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		m_pSushi[nSushi] = nullptr;
	}
	m_nSpawnCount = 0;
	m_nSushiCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResultEffect::~CResultEffect()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CResultEffect * CResultEffect::Create()
{
	//メモリ確保
	CResultEffect* pResultEffect = nullptr;
	pResultEffect = new CResultEffect;

	//NULLチェック
	if (pResultEffect != nullptr)
	{
		pResultEffect->Init();
	}

	return pResultEffect;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CResultEffect::Init(void)
{

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CResultEffect::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CResultEffect::Update(void)
{
	//寿司のランダム生成処理
	RandomSpawn();
	//寿司の移動処理
	MoveSushi();
	//寿司の画面外処理
	Offscreen();

}

//=============================================================================
// 描画処理関数
//=============================================================================
void CResultEffect::Draw(void)
{

}

//=============================================================================
// 寿司のランダム生成処理関数
//=============================================================================
void CResultEffect::RandomSpawn(void)
{
	//カウントアップ
	m_nSpawnCount++;
	//取得した数値が１より下の場合
	if (m_nSpawnCount>MAX_SPAWN_COUNT)
	{
		//生成位置
		D3DXVECTOR3 pos;
		//ランダムでX位置を設定
		float XPosRandom = (float)(rand() % SCREEN_WIDTH);
		pos = D3DXVECTOR3(XPosRandom, 0.0f - 30.0f, 0.0f);
		
		//ランダムにどの寿司をスポーンさせるか決める
		int nSushiType = (rand() % (CEffectSushi::TYPE_MAX - 1));			//ランダムに値を取得
		
		for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
		{
			if (m_pSushi[nSushi] == NULL)
			{

				//寿司のスポーン生成
				m_pSushi[nSushi] = CEffectSushi::Create(pos, D3DXVECTOR3(100.0f, 100.0f, 0.0f), nSushiType);
				
				//現在の寿司の数をプラス
				m_nSushiCount += 1;

				//数値の初期化
				m_nSpawnCount = 0;
				return;
			}
		}
	}

}

//=============================================================================
// 寿司の移動処理
//=============================================================================
void CResultEffect::MoveSushi(void)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		if (m_pSushi[nSushi] != NULL)
		{
			//位置取得
			D3DXVECTOR3 pos = m_pSushi[nSushi]->GetPos();
			//位置の更新
			pos.y++;
			//位置セット
			m_pSushi[nSushi]->SetPos(pos);
		}
	}
}

//=============================================================================
// 寿司の画面外処理関数
//=============================================================================
void CResultEffect::Offscreen(void)
{
	for (int nSushi = 0; nSushi < MAX_SUSHI_EFFECT; nSushi++)
	{
		if (m_pSushi[nSushi] != NULL)
		{
			//位置取得
			D3DXVECTOR3 pos = m_pSushi[nSushi]->GetPos();
			//画面外に出ているか
			if (pos.y>SCREEN_HEIGHT + 40)
			{
				//画面外にいる時に消去
				m_pSushi[nSushi]->Uninit();
				m_pSushi[nSushi] = NULL;
				//最大数を減らす
				m_nSushiCount -= 1;
			}
		}
	}
}
