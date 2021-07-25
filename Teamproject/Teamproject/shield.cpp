//=============================================================================
//
// �A�C�e��[shield.h]
// Author : �V����s
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��

//=============================================================================
#include "shield.h"
#include "resource manager.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShield::CShield()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CShield * CShield::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ITEM type)
{
	//�������[�m��
	CShield *pShield;
	pShield = new CShield;

	//Resource�̌Ăяo��
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(pShield->m_nModel);

	//NULL�`�F�b�N
	if (pShield != NULL)
	{
		pShield->SetPos(pos);			// �ʒu�ݒ�
		pShield->SetSize(size);			// �T�C�Y�ݒ�
		pShield->SetItem(type);			// �A�C�e���^�C�v(�V�[���h)�Œ�
		pShield->SetModelData(Model);	// ���f���ݒ�

		pShield->Init();				//����������
	}
	return pShield;
}

