//=============================================================================
//
// �������Ԃ̏��� [timer.h]
// Author : �V����s
//
//=============================================================================
#ifndef _SHIELDEFFECT_
#define _SHIELDEFFECT_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "billboard.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"

//================================================
// �O���錾
//================================================


//=============================================================================
//�}�N����`
//=============================================================================


class CShieldEffect :public CBillboard
{
public:
	CShieldEffect(int nPriority = 5);
	~CShieldEffect();

	static CShieldEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR Col, CPlayer* pPlayer);
	void Update(void);




private:
	CPlayer *					m_pPlayer;
	
	int							m_Alpha;		//�����x
	bool						m_bUse;			//�g�����g��Ȃ���
	const int					m_nTexture = 40;// �e�N�X�`���ԍ�
	

};


#endif