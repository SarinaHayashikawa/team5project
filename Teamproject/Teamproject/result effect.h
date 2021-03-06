//=============================================================================
//
// リザルトエフェクト(寿司が降ってくる) [result effect.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _RESULT_EFFECT_H_
#define _RESULT_EFFECT_H_

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "scene.h"


//=============================================================================
// 前方宣言
//=============================================================================
class CSushiModel;

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_SUSHI_EFFECT (50)	//降ってくる寿司の画面内の最大数

//=============================================================================
//クラス定義
//=============================================================================
class CResultEffect : public CScene
{
public:
	CResultEffect(int nnPriority = 6);
	~CResultEffect();
	static CResultEffect *Create();	// 生成処理関数
	HRESULT	Init(void);				// 初期化処理関数
	void	Uninit(void);			// 終了処理関数
	void	Update(void);			// 更新処理関数
	void	Draw(void);				// 描画処理関数

private:
	void	RandomSpawn(void);	//寿司のランダム生成
	void	MoveSushi(void);	//寿司の移動処理
	void	Offscreen(void);	//寿司の画面外処理

	int				m_nSpawnCount;				// 寿司出現までのカウント
	CSushiModel *	m_pSushi[MAX_SUSHI_EFFECT];	// 寿司のポインタ
	int				m_nSushiCount;				// 寿司の数
};
#endif // !_RESULT_EFFECT_H_