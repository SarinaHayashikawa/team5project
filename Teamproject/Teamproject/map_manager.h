//=============================================================================
//
// ミニマップ管理 [map_manager.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_
//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "food base.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CLocationPoint;
class CMapEdgeMask;
class CFieldManager;

//*****************************************************************************
// ヘッダファイルのインクルード
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

	D3DXVECTOR3 m_originPos;						//マップの原点（ここを{0,0}とする）
	CLocationPoint * m_pLocationPoint[MAX_PLAYER];	//現在位置
	D3DXVECTOR3 m_MapSize;							//mapのサイズ
	CMapEdgeMask * m_pMapEdgeMask;					//マスクポインタ
	CFieldManager * m_pFieldManager;				//フィールドポインタ
	int m_nTimeFrame;								//現在時間
	int m_nShrinkCount;								//収縮した回数
	bool m_bShirnk;									//収縮中か
};
#endif // !_MAP_MANAGER_H_


