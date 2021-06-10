//=============================================================================
//
// プレイヤー [player.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene3d.h"

//=============================================================================
//クラス定義
//=============================================================================
class Cplayer : public 
{
public:
	Cplayer(int nPriority = 3);
	~Cplayer();

	static HRESULT	Load(void);
	static void		Unload(void);
	static Cplayer* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);

	HRESULT			Init(void);
	void			Uninit(void);
	void			Update(void);
	void			Draw(void);

private:

};
#endif // !_BLOCK_H_


