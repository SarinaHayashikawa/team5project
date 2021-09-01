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
	CShieldEffect(int nPriority = 4);
	~CShieldEffect();

	static CShieldEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR Col);
	void Update(void);




private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		//�e�N�X�`���[�̃|�C���^�[
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_Pos;			//�ʒu
	D3DXVECTOR3					m_Size;			//�傫��
	int							m_Alpha;		//�����x
	bool						m_bUse;			//�g�����g��Ȃ���
	const int					m_nTexture = 40;// �e�N�X�`���ԍ�

};


#endif