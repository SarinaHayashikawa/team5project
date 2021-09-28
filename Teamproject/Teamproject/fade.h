#pragma once
//=============================================================================
//
// フェード処理 [fade.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_FADE	(3)
#define FADE_RATE (0.03f)

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// フェードクラス
//*****************************************************************************
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,									// 何もない状態
		FADE_IN,										// フェードイン処理
		FADE_OUT,										// フェードアウト処理
		FADE_MAX
	}FADE;
	CFade();											// コンストラクタ
	~CFade();											// デストラクタ
	static CFade *Create(void);				// 作成処理
	HRESULT Init(void);						// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
	void SetFade(CManager::MODE mode);					// フェード設定

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;									// 位置
	CManager::MODE m_mode;								// モード
	D3DXCOLOR m_color;									// カラー
	FADE m_fade;										// フェード
};

#endif