//=============================================================================
//
// �t�B�[���h�Ǘ� [fieldmanager.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _FIELD_MANAGER_H_
#define _FIELD_MANAGER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************

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
	void EdgeCollision(void);
	void NowEdgeCollision(void);
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_originsize;
};
#endif // !_MAP_MANAGER_H_

