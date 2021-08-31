//=============================================================================
//
// フィールド管理 [fieldmanager.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _FIELD_MANAGER_H_
#define _FIELD_MANAGER_H_

#include "food base.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CLocationPoint;
//*****************************************************************************
// ヘッダファイルのインクルード
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
	void SushiSpawn(void);				// 寿司のランダム生成処理関数

	void EdgeCollision(void);
	void NowEdgeCollision(void);
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_originsize;
	int		m_nSushiSpawn;						// 寿司のスポーンする時間
	int		m_SpawnCount;						// 寿司のスポーンカウント
	static int m_nProb[CFoodBase::TYPE_MAX];	// どの寿司が出てくるかの確率
	static int m_nMaxProb;						// 最大確率

};
#endif // !_MAP_MANAGER_H_


