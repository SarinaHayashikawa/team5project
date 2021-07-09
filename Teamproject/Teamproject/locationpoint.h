//=============================================================================
//
// �v���C���[���݈ʒu�̏��� [locationpoint.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _LOCATION_POINT_H_
#define _LOCATION_POINT_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"
class CLocationPoint : public CScene2d
{
public:
	CLocationPoint(int nPriority = 8);
	~CLocationPoint();

	static CLocationPoint *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int                     m_nPatternAnim; //�A�j���[�V�����p�^�[��
	int                     m_nCountAnim; //�A�j���[�V�����p�^�[��
	int                     m_nTexture = 22;//�e�N�X�`���ԍ�
};
#endif // !_LOCATION_POINT_H_


