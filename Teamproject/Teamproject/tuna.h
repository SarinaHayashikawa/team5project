//=============================================================================
//
// 寿司　マグロ[tuna.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _TUNA_H_
#define _TUNA_H_
//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "model.h"
#include "food base.h"

//=============================================================================
// クラス定義
//=============================================================================
class CTuna :public CFoodBase
{
public:
	CTuna();
	static CTuna * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	const int m_nTexture = 12;		// テクスチャ番号
};

#endif