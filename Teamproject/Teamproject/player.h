//=============================================================================
//
// プレイヤー [player.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "scene3d.h"
#include "model.h"

//=============================================================================
//クラス定義
//=============================================================================
class CPlayer : public CModel
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer();

	static CPlayer* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size);

	HRESULT			Init(void);
	void			Uninit(void);
	void			Update(void);

	void			Move(void);	// 移動処理
	void			Rot(void);	// 向き処理
	void			Boost(void);// 加速処理

private:
	const int	m_nModel = 1;	// モデル番号
	int			m_nLife;		// ライフ

};
#endif // !_BLOCK_H_


