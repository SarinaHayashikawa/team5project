//=============================================================================
//
// �~�j�}�b�v�Ǘ� [map_manager.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CLocationPoint;
class CMapEdgeMask;
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************

class CMapManager : public CScene
{
public:
	CMapManager(int nPriority = 8);
	~CMapManager();

	static CMapManager *Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3 m_originPos;//�}�b�v�̌��_�i������{0,0}�Ƃ���j
	CLocationPoint * m_pLocationPoint[MAX_PLAYER];//���݈ʒu
	D3DXVECTOR3 m_MapSize; //map�̃T�C�Y
	CMapEdgeMask * m_pMapEdgeMask;//�}�X�N�|�C���^
};
#endif // !_MAP_MANAGER_H_


