//=============================================================================
//
// シールドエフェクトの処理 [ShieldEffect.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _SHIELD_EFFECT_H_
#define _SHIELD_EFFECT_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "billboard.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CPlayer;

//=============================================================================
// クラス定義
//=============================================================================
class CShieldEffect :public CBillboard
{
public:
	CShieldEffect(int nPriority = 5);
	~CShieldEffect();

	static CShieldEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR Col, CPlayer* pPlayer);
	void Update(void);

private:
	CPlayer * m_pPlayer;		// プレイヤーのポインタ
	const int m_nTexture = 40;	// テクスチャ番号

};


#endif