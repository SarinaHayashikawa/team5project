//=============================================================================
//
// ミニマップの処理 [map.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"
class CMap : public CScene2d
{
public:
	CMap(int nPriority = 8);
	~CMap();

	static CMap *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int                     m_nPatternAnim;	//アニメーションパターン
	int                     m_nCountAnim;	//アニメーションパターン
	int                     m_nTexture = 21;//テクスチャ番号
};
#endif // !_MAP_H_


