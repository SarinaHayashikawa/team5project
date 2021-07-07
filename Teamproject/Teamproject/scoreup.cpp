//=============================================================================
//
// アイテム[shield.h]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scoreup.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScoreup::CScoreup()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CScoreup * CScoreup::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ITEM type)
{
	//メモリー確保
	CScoreup *pScoreup;
	pScoreup = new CScoreup;

	//Resourceの呼び出し
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(pScoreup->m_nModel);

	//NULLチェック
	if (pScoreup != NULL)
	{
		pScoreup->SetPos(pos);			// 位置設定
		pScoreup->SetSize(size);		// サイズ設定
		pScoreup->SetItem(type);		// アイテムタイプ(スコアアップ)固定
		pScoreup->SetModelData(Model);	// テクスチャ設定

		pScoreup->Init();				//初期化処理
	}
	return pScoreup;
}


