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
#include "player parts.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED (1.0f)			// プレイヤーのスピード(後で変更)
#define PLAYER_BOOST_SPEED (2.0f)	// プレイヤーのブーストスピード(後で変更)
#define PlAYER_ROT_SPEED (10.0f)	// プレイヤーの振り向き速度(後で変更)

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	SetObjType(OBJTYPE_PLAYER);				// オブジェクトタイプ設定
	m_nLife		= 0;						// ライフの初期化
	m_nParts	= 0;						// パーツ数の初期化
	memset(m_pParts, NULL, sizeof(m_pParts[MAX_PARTS]));	// パーツポインタの初期化
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
// 更新処理関数
//=============================================================================
void CPlayer::Update(void)
{
	//キーボード入力の取得
	CKeyboard* pInput = (CKeyboard*)CManager::GetInputKeyboard();
	if (pInput->GetKeyTrigger(DIK_X))
	{
		AddParts();
	}
	//移動処理
	Move();
	//角度処理
	Rot();

}

//=============================================================================
// パーツ追加（食べ物を食べた後の追加パーツ）処理関数
//=============================================================================
void CPlayer::AddParts(void)
{
	//パーツがない時
	if (m_nParts == 0)
	{	
		//位置取得
		D3DXVECTOR3 pos = GetPos();
		//向き取得
		D3DXVECTOR3 rot = GetRot();

		//生成処理
		m_pParts[m_nParts] = CPlayerParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
	}
	//パーツが１つでもある時
	else if (m_nParts>0 && m_nParts<MAX_PARTS)
	{
		//位置取得
		D3DXVECTOR3 PartsPos = m_pParts[m_nParts - 1]->GetPos();
		//向き取得
		D3DXVECTOR3 PartsRot = m_pParts[m_nParts - 1]->GetRot();

		//生成処理
		m_pParts[m_nParts] = CPlayerParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);

	}

	//パーツ数を増やす
	m_nParts++;
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
	
	//移動処理
	move = D3DXVECTOR3((float)(cos(rot.y + D3DXToRadian(90.0f))), 0.0f, (float)(sin(rot.y - D3DXToRadian(90.0f))));

	if (!pInputMouse->GetClick(0))
	{
		// 移動スピード
		move *= PLAYER_SPEED;
	}
	else
	{
		//ブースト時のスピード
		move *= PLAYER_BOOST_SPEED;
	}

	// 移動処理
	pos += move;

	// 位置保存
	SetPos(pos);

}

//=============================================================================
// 向き処理関数
//=============================================================================
void CPlayer::Rot(void)
{
	//マウス入力取得
	CMouse *pInputMouse = (CMouse*)CManager::GetInputMouse();
	//角度の移動量
	float fRotMove = 0.0f;
	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//向き取得
	D3DXVECTOR3 rot = GetRot();
	//向きの移動量
	D3DXVECTOR3 RotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//単位ベクトル取得
	D3DXVec3Normalize(&RotMove, &D3DXVECTOR3((float)pInputMouse->GetMousePos().x - SCREEN_WIDTH / 2, 0.0f, (float)-pInputMouse->GetMousePos().y + SCREEN_HEIGHT / 2));
	//向きたい角度
	fRotMove = atan2f((pos.x - (RotMove.x + pos.x)), (pos.z - (RotMove.z + pos.z)));
	//差分の角度
	float fDiff = ((D3DXToRadian(180.0f) - (fRotMove*-1.0f)) - (D3DXToRadian(180.0f) - (rot.y*-1.0f)))*-1.0f;
	//回転方向の確認(時計周りtrue:反時計回りfalse)
	bool bRotation = fRotMove>rot.y ? !(fRotMove - rot.y > D3DXToRadian(180.0f)) : rot.y - fRotMove  > D3DXToRadian(180.0f);
	//向きの修正
	fDiff = (fDiff + (bRotation ? D3DXToRadian(-360.0f) : D3DXToRadian(360.0f)));
	fDiff = (float)(fmod(fDiff, D3DXToRadian(360.0f)));
	//向き処理
	rot.y = rot.y - (fDiff*(0.04f));
	//角度が一定に達したら修正
	if (D3DXToDegree(rot.y) >= 360.0f
		|| D3DXToDegree(rot.y) <= -360.0f)
	{
		rot.y = 0.0f;
	}

	// 向き保存
	SetRot(rot);

}

