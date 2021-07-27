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
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAP_LOCATION_VALUE (0.55f) //マップ表示の現在位置補正値
//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CMapManager::CMapManager(int nPriority) : CScene(nPriority)
{
	m_originPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
CMapManager * CMapManager::Create(D3DXVECTOR3 Pos)
{
	CMapManager *pMap = nullptr;

	pMap = new CMapManager;
	if (pMap != nullptr)
	{
		pMap->m_originPos = Pos;
		pMap->Init();
	}
	return pMap;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMapManager::Init(void)
{
	//マップ生成
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
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		//プレイヤーの位置取得
		D3DXVECTOR3 pos = CManager::GetPlayerControl()->GetPlayer(nCount)->GetPos();
		//プレイヤーの現在位置をセット
		m_pLocationPoint[nCount]->SetPos(D3DXVECTOR3(m_originPos.x + pos.x * MAP_LOCATION_VALUE, m_originPos.y - pos.z * MAP_LOCATION_VALUE, 0.0f));
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CMapManager::Draw(void)
{
	
}
