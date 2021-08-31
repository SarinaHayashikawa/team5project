//=============================================================================
//
// �t�B�[���h�Ǘ� [fieldmanager.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _FIELD_MANAGER_H_
#define _FIELD_MANAGER_H_

#include "food base.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CLocationPoint;
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************

class CFieldManager : public CScene
{
public:
	CFieldManager(int nPriority = 8);
	~CFieldManager();

	static CFieldManager *Create(D3DXVECTOR3 Pos,D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void SushiSpawn(void);				// ���i�̃����_�����������֐�

	void EdgeCollision(void);
	void NowEdgeCollision(void);
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_originsize;
	int		m_nSushiSpawn;						// ���i�̃X�|�[�����鎞��
	int		m_SpawnCount;						// ���i�̃X�|�[���J�E���g
	static int m_nProb[CFoodBase::TYPE_MAX];	// �ǂ̎��i���o�Ă��邩�̊m��
	static int m_nMaxProb;						// �ő�m��

};
#endif // !_MAP_MANAGER_H_


