//=============================================================================
//
// ミニマップの処理 [map.cpp]
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
#include "map_manager.h"
#include "resource manager.h"
#include "map.h"
#include "locationpoint.h"
#include "game.h"
#include "player.h"
#include "player control.h"
#include "Fieldmanager.h"
#include "MapEdgeMask.h"
#include "MapEdgeOverlay.h"
#include "MapEdgeMaskOut.h"
#include "ebi.h"
#include "egg.h"
#include "ikura.h"
#include "salmon.h"
#include "tuna.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_LOCATION_VALUE (0.34f) //マップ表示の現在位置補正値
#define MAX_SUSHI_SPAWN (300)		//餌のスポーンまでの最大時間

//*****************************************************************************
// 静的メンバー変数初期化
//*****************************************************************************
int CMapManager::m_nProb[CFoodBase::TYPE_MAX] =
{
	20,				//ひとまずのデバック用の値
	20,
	20,
	20,
	20,
};
int CMapManager::m_nMaxProb = m_nProb[0] + m_nProb[1] + m_nProb[2] + m_nProb[3] + m_nProb[4];

//=============================================================================
// コンストラクタ
//=============================================================================
CMapManager::CMapManager(int nPriority) : CScene(nPriority)
{
	m_originPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMapEdgeMask	= nullptr;
	m_nSushiSpawn	= 0;	// 寿司のスポーンする時間の初期化
	m_SpawnCount	= 0;	// 寿司のスポーンカウントの初期化

}

//=============================================================================
// デストラクタ
//=============================================================================
CMapManager::~CMapManager()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CMapManager * CMapManager::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CMapManager *pMap = nullptr;

	pMap = new CMapManager;
	if (pMap != nullptr)
	{
		pMap->m_originPos = Pos;
		pMap->m_MapSize = Size;
		pMap->Init();
	}
	return pMap;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMapManager::Init(void)
{
	//ステージ生成
	CFieldManager::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), m_MapSize);
	//ステージ生成（現在のフィールド）
	m_pMapEdgeMask = CMapEdgeMask::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), m_MapSize);
	//ステージ生成（フィールド外側）
	CMapEdgeOverlay::Create(D3DXVECTOR3(0.0f, -49.0f, 0.0f), m_MapSize * 2.0f);
	//ミニマップ生成
	CMap::Create(m_originPos,D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f));
	//プレイヤー位置の生成
	m_pLocationPoint[0] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f),0);
	//プレイヤー位置の生成
	m_pLocationPoint[1] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 1);
	//プレイヤー位置の生成
	m_pLocationPoint[2] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 2);
	//プレイヤー位置の生成
	m_pLocationPoint[3] = CLocationPoint::Create(m_originPos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), 3);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMapManager::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMapManager::Update(void)
{
	//とりあえず収縮してるか確認する
	m_MapSize.x -= 2.0f;
	m_MapSize.y -= 2.0f;
	m_MapSize.z -= 2.0f;
	m_pMapEdgeMask->SetSize(m_MapSize);
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		//プレイヤーの位置取得
		D3DXVECTOR3 pos = CManager::GetPlayerControl()->GetPlayer(nCount)->GetPos();
		//プレイヤーの現在位置をセット
		m_pLocationPoint[nCount]->SetPos(D3DXVECTOR3(m_originPos.x + pos.x * MAP_LOCATION_VALUE, m_originPos.y - pos.z * MAP_LOCATION_VALUE, 0.0f));
	}

	//餌の生成処理
	SushiSpawn();
}
//=============================================================================
// 描画処理
//=============================================================================
void CMapManager::Draw(void)
{
	
}

//=============================================================================
// 寿司のランダム生成処理関数
//=============================================================================
void CMapManager::SushiSpawn(void)
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
