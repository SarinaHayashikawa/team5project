//=============================================================================
//
// エフェクト用寿司処理 [effect sushi.h]
// Author : 吉田悠人
//
//=============================================================================

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "effect sushi.h"
#include "resource manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CEffectSushi::CEffectSushi(int nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffectSushi::~CEffectSushi()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CEffectSushi * CEffectSushi::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size, int nType)
{
	//メモリ確保
	CEffectSushi *pEffectSushi = nullptr;
	pEffectSushi = new CEffectSushi;

	//リソース確保(リソースマネージャーから呼び出す)
	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 		Texture = pResource->TextureLoad(pEffectSushi->m_nEffectSushiTexture[nType]);
	

	//NULLチェック
	if (pEffectSushi != nullptr)
	{
		pEffectSushi->BindTexture(Texture);
		pEffectSushi->SetPos(Pos);
		pEffectSushi->SetSize(Size);
		pEffectSushi->Init();
	}

	return pEffectSushi;
}

