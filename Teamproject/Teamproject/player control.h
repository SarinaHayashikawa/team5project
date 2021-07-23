//=============================================================================
//
// �v���C���[���� [player control.h]
// Author : �g�c�I�l
//
//=============================================================================
#ifndef _PLAYER_CONTROL_H_
#define _PLAYER_CONTROL_H_

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "scene3d.h"
#include "model.h"
//=============================================================================
// �O���錾
//=============================================================================
class CPlayer;

//=============================================================================
//�N���X��`
//=============================================================================
class CPlayerControl
{
public:
	CPlayerControl(int nPriority = 3);
	~CPlayerControl();
	HRESULT	Init(void);												// �����������֐�
	void	Update(void);											// �X�V�����֐�
	CPlayer * GetPlayer(int nPlayer) { return m_pPlayer[nPlayer]; }	// �v���C���[�Q�b�^�[�֐�
private:
	void RespawnControl(int nPlayer);		// �v���C���[�̃��X�|�[��
	void DamageHit(int nPlayer);			// ���̃v���C���[�̓��������ۂ̃_���[�W����
	void PlayerHit(int nPlayer);			// �v���C���[�̃q�b�g����
	void PlayerControl(int nPlayer);		// �v���C���[����֐�

	CPlayer*		m_pPlayer[MAX_PLAYER];		// �v���C���[�|�C���^
	int				m_nRespawn[MAX_PLAYER];		// �v���C���[�̃��X�|�[���J�E���g
	static D3DXVECTOR3 m_PlayerPos[MAX_PLAYER];	// �v���C���[�̈ʒu

};
#endif // !_BLOCK_H_

