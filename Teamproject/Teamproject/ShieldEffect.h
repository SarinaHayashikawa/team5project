//=============================================================================
//
// 制限時間の処理 [timer.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _SHIELDEFFECT_
#define _SHIELDEFFECT_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "billboard.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"

//================================================
// 前方宣言
//================================================


//=============================================================================
//マクロ定義
//=============================================================================


class CShieldEffect :public CBillboard
{
public:
	CShieldEffect(int nPriority = 4);
	~CShieldEffect();

	static CShieldEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR Col);
	void Update(void);




private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		//テクスチャーのポインター
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3					m_Pos;			//位置
	D3DXVECTOR3					m_Size;			//大きさ
	int							m_Alpha;		//透明度
	bool						m_bUse;			//使うか使わないか
	const int					m_nTexture = 40;// テクスチャ番号

};


#endif