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
class CPlayerControl : public CScene
{
public:
	CPlayerControl(int nPriority = 3);
	~CPlayerControl();
	static CPlayerControl *Create();	// ���������֐�
	HRESULT	Init(void);					// �����������֐�
	void	Uninit(void);				// �I�������֐�
	void	Update(void);				// �X�V�����֐�
	void	Draw(void);					// �`�揈���֐�

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

