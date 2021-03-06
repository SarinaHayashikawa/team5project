//=============================================================================
//
// リスポーンカウントUI処理 [respawn count.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _RESPAWN_CONTROL_H_
#define _RESPAWN_CONTROL_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "scene2d.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_NUMBER (2)	//最大桁数
//=============================================================================
// 前方宣言
//=============================================================================
class CNumber;
//=============================================================================
// クラス定義
//=============================================================================
class CRespawnCount : public CScene
{
public:

	CRespawnCount(int nPriority = 7);
	~CRespawnCount();

	static CRespawnCount * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetControl(int nControl);

private:
	CNumber*		m_pNumber[MAX_NUMBER];	//数値の最大数
	D3DXVECTOR3		m_Pos;
	D3DXVECTOR3		m_Size;
	int				m_nControl; //カウントの数値
};
#endif 
