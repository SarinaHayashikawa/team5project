//=============================================================================
//
// アイテム[CItem.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "scene3d.h"
#include "model.h"

//=============================================================================
//クラス定義
//=============================================================================
class CItem : public CModel
{
public:

	// アイテムの種類
	typedef enum
	{
		ITEM_NONE = 0,		// 割り当てなし
		ITEM_SCOREUP,		// スコアアップ
		ITEM_SHIELD,		// シールド
		ITEM_MAX			// 種類の最大数
	}ITEM;

	CItem(int nPriority = 3);
	 ~CItem();
	void Update(void);
	void Collision(void);						// 当たり判定関数
	virtual void ItemEffect(ITEM type) = 0;		// アイテム効果関数
	void SetItem(ITEM item);					// アイテムの種類設定
	ITEM GetType(void) { return m_ItemType; };	// タイプゲッター
private:
	ITEM        m_ItemType;		//アイテムタイプ
};
#endif // !_ITEM_H_


