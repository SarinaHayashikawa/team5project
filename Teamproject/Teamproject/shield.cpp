//=============================================================================
//
// アイテム[shield.h]
// Author : 齋藤大行
//
//=============================================================================
//=============================================================================
//インクルードファイル

//=============================================================================
#include "shield.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CShield::CShield()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CShield * CShield::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ITEM type)
{
	//メモリー確保
	CShield *pShield;
	pShield = new CShield;

	//Resourceの呼び出し
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(pShield->m_nModel);

	//NULLチェック
	if (pShield != NULL)
	{
		pShield->SetPos(pos);			// 位置設定
		pShield->SetSize(size);			// サイズ設定
		pShield->SetItem(type);			// アイテムタイプ(シールド)固定
		pShield->SetModelData(Model);	// モデル設定

		pShield->Init();				//初期化処理
	}
	return pShield;
}


