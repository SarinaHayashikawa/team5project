//=============================================================================
//
// �v���C���[ [player.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "scene3d.h"
#include "model.h"

//=============================================================================
//�N���X��`
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

	void			Move(void);	// �ړ�����
	void			Rot(void);	// ��������
	void			Boost(void);// ��������

private:
	const int	m_nModel = 1;	// ���f���ԍ�
	int			m_nLife;		// ���C�t

};
#endif // !_BLOCK_H_


