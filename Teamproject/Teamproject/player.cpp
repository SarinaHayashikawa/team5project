//=============================================================================
//
//	プレイヤー[player.cpp]
//	Author:吉田悠人
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "player.h"
#include "resource manager.h"
#include "keyboard.h"
#include "mouse.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED (2.0f)	//プレイヤーのスピード

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	SetObjType(OBJTYPE_PLAYER);
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size)
{
	//メモリ確保
	CPlayer* pPlayer = NULL;
	pPlayer = new CPlayer;
	//リソース確保
	CResource* pResource = CManager::GetResource();
	MODELDATA Model = pResource->ModelLoad(pPlayer->m_nModel);

	//NULLチェック
	if (pPlayer != NULL)
	{
		//位置設定
		pPlayer->SetPos(Pos);
		//向き設定
		pPlayer->SetRot(Rot);
		//カラー設定
		pPlayer->SetSize(Size);
		//モデルデータ設定
		pPlayer->SetModelData(Model);
		//初期化処理
		pPlayer->Init();
	}

	return pPlayer;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPlayer::Init(void)
{

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPlayer::Uninit(void)
{
	
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPlayer::Update(void)
{
	Move();
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CPlayer::Move(void)
{
	//キーボード入力の取得
	CKeyboard* pInput = (CKeyboard*)CManager::GetInputKeyboard();
	//マウス入力取得
	CMouse *pInputMouse = (CMouse*)CManager::GetInputMouse();

	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//移動量
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//移動（デバック）
	if (pInput->GetKeyPress(DIK_W))
	{
		move += D3DXVECTOR3(0.0f,0.0f,1.0f);
	}
	if(pInput->GetKeyPress(DIK_S))
	{
		move += D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}
	if (pInput->GetKeyPress(DIK_A))
	{
		move += D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	}
	if (pInput->GetKeyPress(DIK_D))
	{
		move += D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	}

	//移動（マウス）
	if (pInputMouse->GetClick(0))
	{
		//単位ベクトルに取得
		D3DXVec3Normalize(&move, &D3DXVECTOR3((float)pInputMouse->GetMousePos().x - SCREEN_WIDTH/2, 0.0f, (float)-pInputMouse->GetMousePos().y + SCREEN_HEIGHT/2));
	}



	// 移動スピード
	move *= PLAYER_SPEED;

	// 移動処理
	pos += move;

	// 位置保存
	SetPos(pos);
}

