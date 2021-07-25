//=============================================================================
//
// �A�C�e��[CItem.h]
// Author : �V����s
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
// �w�b�_�[�t�@�C��
//=============================================================================
#include "scene3d.h"
#include "model.h"

//=============================================================================
//�N���X��`
//=============================================================================
class CItem : public CModel
{
public:

	// �A�C�e���̎��
	typedef enum
	{
		ITEM_NONE = 0,		// ���蓖�ĂȂ�
		ITEM_SCOREUP,			// �X�R�A�A�b�v
		ITEM_SHIELD,		// �V�[���h
		ITEM_MAX			// ��ނ̍ő吔
	}ITEM;

	CItem(int nPriority = 3);
	~CItem();

	void			Update(void);
	void			Collision(void);					// �����蔻��֐�
	void			ItemEffect(ITEM type);					//�A�C�e�����ʊ֐�
	void			SetItem(ITEM item);				// �A�C�e���̎�ސݒ�
	ITEM GetType(void) { return m_ItemType; };
private:

	ITEM        m_ItemType;
};
#endif // !_ITEM_H_


