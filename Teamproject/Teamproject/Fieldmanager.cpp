//=============================================================================
//
// フィールド管理 [fieldmanager.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "fieldmanager.h"
#include "resource manager.h"
#include "map.h"
#include "locationpoint.h"
#include "game.h"
#include "player.h"
#include "floor.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_SIZE (500.0f)		//マッぷサイズ
#define PLAYER_HIT_SIZE (5.0f)	//マッぷサイズ
#define MAX_SUSHI_SPAWN (300)	//餌のスポーンまでの最大時間

//*****************************************************************************
// 静的メンバー変数初期化
//*****************************************************************************
int CFieldManager::m_nProb[CFoodBase::TYPE_MAX] =
{
	20,				//ひとまずのデバック用の値
	20,
	20,
	20,
	20,
};
int CFieldManager::m_nMaxProb = m_nProb[0] + m_nProb[1] + m_nProb[2] + m_nProb[3] + m_nProb[4];

//=============================================================================
// コンストラクタ
//=============================================================================
CFieldManager::CFieldManager(int nPriority) : CScene(nPriority)
{
	m_nSushiSpawn = 0;	// 寿司のスポーンする時間の初期化
	m_SpawnCount = 0;	// 寿司のスポーンカウントの初期化
}

//=============================================================================
// デストラクタ
//=============================================================================
CFieldManager::~CFieldManager()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CFieldManager * CFieldManager::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CFieldManager *pMap = nullptr;

	pMap = new CFieldManager;
	if (pMap != nullptr)
	{
		pMap->m_size = Size;
		pMap->Init();
	}
	return pMap;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFieldManager::Init(void)
{
	//床生成
	CFloor::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(m_size.x, m_size.z, m_size.z));
	m_originsize = m_size;//マップ最大のサイズを格納しておく
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFieldManager::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CFieldManager::Update(void)
{
	//端当たり判定
	EdgeCollision();
	//餌の生成処理
	SushiSpawn();

}
//=============================================================================
// 描画処理
//=============================================================================
void CFieldManager::Draw(void)
{

}

//=============================================================================
// 端死亡処理
//=============================================================================
void CFieldManager::EdgeCollision(void)
{
	CScene* pTop[PRIORITY_MAX] = {};
	CScene* pNext = nullptr;
	D3DXVECTOR3 distance; //プレイヤーと敵の距離
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//リスト先頭取得
		pTop[nCount] = *(CScene::GetTop() + nCount);
	}

	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (pTop[nCount] != nullptr)
		{
			pNext = pTop[nCount];
			while (pNext != nullptr)
			{
				//pNext(CScene)をCEnemyにダウンキャスト
				CPlayer * pPlayer = dynamic_cast<CPlayer*> (pNext);
				if (pPlayer != nullptr)
				{
					distance = pPlayer->GetPos();//マップの原点が０、０なのでこのままプレイヤーの位置入れる

					//敵とプレイヤーの距離がそれぞれの半径の和より大きかったらマップからはみ出てる
					if (powf(distance.x, 2) + powf(distance.z, 2)
						>= pow(((m_size.x / 2) + PLAYER_HIT_SIZE), 2))
					{
						//死亡処理（マップ収縮２５％以下なら）
						//それ以外はリスポーン
						pPlayer->DamageHit();
					}
					
				}
				//次の対象を読み込む
				pNext = pNext->GetNext();
			}
		}
	}
}

//=============================================================================
// 端死亡処理
//=============================================================================
void CFieldManager::NowEdgeCollision(void)
{
}

//=============================================================================
// 寿司のランダム生成処理関数
//=============================================================================
void CFieldManager::SushiSpawn(void)
{
	//カウントダウン
	m_SpawnCount++;
	//カウントが一定に達したらランダムにスポーン
	if (m_SpawnCount>m_nSushiSpawn)
	{
		//エリアの半径
		int nRadius = 250;//(ココの数値を範囲制限の円の半径を取得)
		//中心値
		D3DXVECTOR3 centre = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//(ココの数値を範囲制限の円の中心を取得)

		//ランダム角度
		srand((unsigned int)time(NULL));			//ランダム関数の初期化
		float fAngle = (float)(rand() % 360 + 1);	//ランダムで角度を決める

													//ランダムな距離
		int nDistance = rand() % nRadius;			//ランダムな距離を取得

													//ランダムリスポーン位置
		D3DXVECTOR3 random = centre + D3DXVECTOR3((float)(nDistance*cos(fAngle)), 0.0f, (float)(nDistance*sin(fAngle)));

		//ランダムにどの寿司をスポーンさせるか決める
		int nSpawn = rand() % m_nMaxProb;			//ランダムに値を取得

		int nProd = 0;//確率用の変数

		//どの寿司がスポーンするか
		for (int nSushi = 0; nSushi < CFoodBase::TYPE_MAX; nSushi++)
		{
			//確率を足してく
			nProd += m_nProb[nSushi];
			//確率の確認
			if (nSpawn <= nProd)
			{
				//カウント初期化
				m_SpawnCount = 0;
				//ランダムに次のスポーン時間を決める
				m_nSushiSpawn = rand() % MAX_SUSHI_SPAWN;

				//寿司のスポーン生成
				switch (nSushi)
				{
				case CFoodBase::TYPE_EBI:
					CEbi::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_EGG:
					CEgg::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_IKURA:
					CIkura::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_SALMON:
					CSalmon::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				case CFoodBase::TYPE_TUNA:
					CTuna::Create(random, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
					break;
				}
				return;
			}
		}
	}
}
