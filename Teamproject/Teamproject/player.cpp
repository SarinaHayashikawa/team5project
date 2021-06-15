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
#define PLAYER_SPEED (2.0f)			//プレイヤーのスピード(後で変更)
#define PlAYER_ROT_SPEED (10.0f)	//プレイヤーの振り向き速度(後で変更)
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
	//向き取得
	D3DXVECTOR3 rot = GetRot();
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
		float fRotMove=0.0f;

		//単位ベクトル取得
		D3DXVec3Normalize(&move, &D3DXVECTOR3((float)pInputMouse->GetMousePos().x - SCREEN_WIDTH/2, 0.0f, (float)-pInputMouse->GetMousePos().y + SCREEN_HEIGHT/2));
		
		//向きたい角度
		fRotMove = atan2f((pos.x - (move.x + pos.x)), (pos.z - (move.z + pos.z)));
		//差分の角度
		float fDiff = ((D3DXToRadian(180.0f) - (fRotMove*-1.0f)) - (D3DXToRadian(180.0f) - (rot.y*-1.0f)))*-1.0f;
		//回転方向の確認(時計周りtrue:反時計回りfalse)
		bool bRotation = fRotMove>rot.y ? !(fRotMove - rot.y > D3DXToRadian(180.0f)): rot.y - fRotMove  > D3DXToRadian(180.0f);
		//向きの修正
		fDiff = (fDiff + (bRotation ? D3DXToRadian(-360.0f) : D3DXToRadian (360.0f)));
		fDiff = fmod(fDiff, D3DXToRadian(360.0f));
		//向き処理
		rot.y = rot.y - (fDiff*0.1f);
		//角度が一定に達したら修正
		if (D3DXToDegree(rot.y) >= 360.0f
			|| D3DXToDegree(rot.y) <= -360.0f)
		{
			rot.y = 0.0f;
		}

	}


	// 移動スピード
	move *= PLAYER_SPEED;

	// 移動処理
	pos += move;

	// 位置保存
	SetPos(pos);
	// 向き保存
	SetRot(rot);

}

//=============================================================================
// 向き処理関数
//=============================================================================
void CPlayer::Rot(void)
{
	

}

//=============================================================================
// 加速処理関数
//=============================================================================
void CPlayer::Boost(void)
{
}

