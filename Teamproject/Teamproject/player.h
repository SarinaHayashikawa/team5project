//=============================================================================
//
// �v���C���[ [player.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene3d.h"

//=============================================================================
//�N���X��`
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


