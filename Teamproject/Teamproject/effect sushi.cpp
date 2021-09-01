//=============================================================================
//
// �G�t�F�N�g�p���i���� [effect sushi.h]
// Author : �g�c�I�l
//
//=============================================================================

//=============================================================================
// �w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "effect sushi.h"
#include "resource manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffectSushi::CEffectSushi(int nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffectSushi::~CEffectSushi()
{
}

//=============================================================================
// ��������
//=============================================================================
CEffectSushi * CEffectSushi::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size, int nType)
{
	//�������m��
	CEffectSushi *pEffectSushi = nullptr;
	pEffectSushi = new CEffectSushi;

	//���\�[�X�m��(���\�[�X�}�l�[�W���[����Ăяo��)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 		Texture = pResource->TextureLoad(pEffectSushi->m_nEffectSushiTexture[nType]);
	

	//NULL�`�F�b�N
	if (pEffectSushi != nullptr)
	{
		pEffectSushi->BindTexture(Texture);
		pEffectSushi->SetPos(Pos);
		pEffectSushi->SetSize(Size);
		pEffectSushi->Init();
	}

	return pEffectSushi;
}

