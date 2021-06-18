//=============================================================================
//
// �r���{�[�h [billboard.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "model.h"
#include "scene3d.h"

//=============================================================================
// �N���X��`
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

	void SetColor(D3DXCOLOR col);					// �J���[�Z�b�^�[
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// �e�N�X�`���ݒ�

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;		// �s��v�Z�p
	D3DXCOLOR				m_col;			// �J���[

};

#endif