//=============================================================================
//
// アイテム　シールド [scoreup.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _SCOREUP_H_
#define _SCOREUP_H_
//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "Item.h"
#include "model.h"

//=============================================================================
// クラス定義
//=============================================================================
class CScoreup :public CItem
{
public:
	CScoreup();

	static CScoreup * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ITEM type);
	void ItemEffect(ITEM type);		//アイテム効果関数

private:
	const int	m_nModel = 2;	// モデル番号	
};

#endif