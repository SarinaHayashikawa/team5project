//=============================================================================
//
// 床の処理 [floor.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "polygon3d.h"
#include "floor.h"

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CFloor::m_apTexture[TYPE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CFloor::CFloor(int nPriority) : CPolygon3d(nPriority)
{
	m_nPatternAnim = 0;
	m_nCountAnim = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFloor::~CFloor()
{

}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CFloor::Load(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FLOOR, &m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CFloor::Unload(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CFloor * CFloor::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CFloor *pFloor;

	pFloor = new CFloor;
	if (pFloor != NULL)
	{
		pFloor->SetPos(Pos);
		pFloor->SetSize(Size);
		pFloor->Init();
	}

	return pFloor;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFloor::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	CPolygon3d::Init();

	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);

	SetRot(D3DXVECTOR3(D3DXToRadian(-90.0f), D3DXToRadian(0.0f), D3DXToRadian(90.0f)));
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFloor::Uninit(void)
{
	CPolygon3d::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CFloor::Update(void)
{
	CPolygon3d::Update();
	//テクスチャセット
	D3DXVECTOR2 Tex[NUM_VERTEX];
	Tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	Tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	Tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	Tex[3] = D3DXVECTOR2(1.0f, 1.0f);
	SetTexture(Tex);
}

//=============================================================================
// 描画処理
//=============================================================================
void CFloor::Draw(void)
{
	CPolygon3d::Draw();
}