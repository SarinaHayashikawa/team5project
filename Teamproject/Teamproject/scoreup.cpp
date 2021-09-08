//=============================================================================
//
// �A�C�e��[shield.h]
// Author : �V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scoreup.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScoreup::CScoreup()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CScoreup * CScoreup::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������[�m��
	CScoreup *pScoreup;
	pScoreup = new CScoreup;

	//Resource�̌Ăяo��
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(pScoreup->m_nScoreupModel);

	//NULL�`�F�b�N
	if (pScoreup != NULL)
	{
		pScoreup->SetPos(pos);			// �ʒu�ݒ�
		pScoreup->SetSize(size);		// �T�C�Y�ݒ�
		pScoreup->SetModelData(Model);	// ���f���ݒ�

		pScoreup->Init();				//����������
	}
	return pScoreup;
}

void CScoreup::ItemEffect(CPlayer* pPlayer)
{
	//�X�R�A�A�b�v�̏���

	//�X�R�A�̌���(�\��)

}


