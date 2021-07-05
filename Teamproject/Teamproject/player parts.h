//=============================================================================
//
// プレイヤーパーツ [player parts.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _PLAYER_PARTS_H_
#define _PLAYER_PARTS_H_

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "scene3d.h"
#include "billboard.h"

//=============================================================================
//クラス定義
//=============================================================================
class CPlayerParts : public CBillboard
{
public:
	CPlayerParts(int nPriority = 3);
	~CPlayerParts();
	static CPlayerParts* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d* pParent);
	void Update(void);
	void SetParent(CScene3d* pParent);	// 親データセッター

private: 
	void Tracking(void);		// 追尾処理
	void Rot(void);				// 向き処理

	CScene3d* 	m_pParent;		// 親パーツのポインタ
	D3DXVECTOR3 m_Move;			// 移動量
	const int	m_nModel = 1;	// テクスチャ番号
};
#endif // !_BLOCK_H_


