//=============================================================================
//
// �v���C���[�p�[�c [player parts.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _PLAYER_PARTS_H_
#define _PLAYER_PARTS_H_

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "scene3d.h"
#include "billboard.h"

//=============================================================================
//�N���X��`
//=============================================================================
class CPlayerParts : public CBillboard
{
public:
	CPlayerParts(int nPriority = 3);
	~CPlayerParts();
	static CPlayerParts* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, CScene3d* pParent);
	void Update(void);
	void SetParent(CScene3d* pParent);	// �e�f�[�^�Z�b�^�[

private: 
	void Tracking(void);		// �ǔ�����
	void Rot(void);				// ��������

	CScene3d* 	m_pParent;		// �e�p�[�c�̃|�C���^
	D3DXVECTOR3 m_Move;			// �ړ���
	const int	m_nModel = 1;	// �e�N�X�`���ԍ�
};
#endif // !_BLOCK_H_


