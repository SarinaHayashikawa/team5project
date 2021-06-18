//=============================================================================
//
// ビルボード [billboard.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "model.h"
#include "scene3d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CBillboard :public CScene3d
{
public:
	CBillboard();
	virtual ~CBillboard();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetColor(D3DXCOLOR col);					// カラーセッター
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// テクスチャ設定

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;		// 行列計算用
	D3DXCOLOR				m_col;			// カラー

};

#endif