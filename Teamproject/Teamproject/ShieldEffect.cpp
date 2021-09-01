//=============================================================================
//
// 制限時間の処理 [item.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
// ヘッダーファイル
//=============================================================================
#include "ShieldEffect.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "resource manager.h"
#include "player.h"
#include "player control.h"
//=============================================================================
// マクロ定義
//=============================================================================



//=============================================================================
//静的メンバー変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CShieldEffect::m_pTexture = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CShieldEffect::CShieldEffect(int nPriority)
{
	m_pVtxBuff = NULL;
	m_Alpha = 0;
	m_bUse = true;
}


//=============================================================================
// デストラクタ
//=============================================================================
CShieldEffect::~CShieldEffect()
{
}

CShieldEffect * CShieldEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR Col)
{
	CShieldEffect *pShieldEffect = NULL;

	pShieldEffect = new CShieldEffect;

	CResource* pResource = CManager::GetResource();
	LPDIRECT3DTEXTURE9 Texture = pResource->TextureLoad(pShieldEffect->m_nTexture);

	if (pShieldEffect != NULL)
	{
		pShieldEffect->SetObjType(CScene::OBJTYPE_NONE);
		pShieldEffect->SetPos(pos);
		pShieldEffect->SetSize(size);
		pShieldEffect->SetColor(Col);
		pShieldEffect->BindTexture(Texture);
		pShieldEffect->Init();
	}


	return pShieldEffect;
}



void CShieldEffect::Update(void)
{

	//位置取得
	D3DXVECTOR3 pos = GetPos();


	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		//プレイヤーの位置取得
		D3DXVECTOR3 PlayerPos = CManager::GetPlayerControl()->GetPlayer(nCount)->GetPos();
		//プレイヤーの現在位置をセット
		pos = PlayerPos;
	}
	

	SetPos(pos);

}
