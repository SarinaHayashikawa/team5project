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
#include "joystick.h"
#include "player parts.h"
#include "ebi parts.h"
#include "egg parts.h"
#include "ikura parts.h"
#include "salmon parts.h"
#include "tuna parts.h"
#include "food base.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED		(1.0f)	// プレイヤーのスピード(後で変更)
#define PLAYER_BOOST_SPEED	(2.0f)	// プレイヤーのブーストスピード(後で変更)
#define PLAYER_ROT_SPEED	(10.0f)	// プレイヤーの振り向き速度(後で変更)
#define PLAYER_REPEL		(15.0f)	// プレイヤーがはじかれる距離
#define PLAYER_REPEL_FRAME	(10.0f)	// プレイヤーのはじかれた際のフレーム
//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	SetObjType(OBJTYPE_PLAYER);								// オブジェクトタイプ設定
	m_nLife		= 0;										// ライフの初期化
	m_nRepelFrameCount = 0;									// はじかれた際のフレーム値の初期化
	m_nDeathFrameCount = 0;									// 死亡時のカウントフレーム値　の初期化
	m_fDashCoutn = 0;										// 加速値の初期化
	m_nParts	= 0;										// パーツ数の初期化
	m_PlayerStats = PLAYER_STATS_NORMAL;					// プレイヤーステータスの初期化
	m_DashSwitch = false;									// ダッシュ切替の初期化
	m_RotMove	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの移動量の初期化
	m_RepelMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// はじかれた際の移動量の初期化
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

	switch (m_PlayerStats)
	{
	case PLAYER_STATS_NORMAL:
		//移動処理
		Move();
		//角度処理
		Rot();
		break;
	case PLAYER_STATS_REPEL:
		RepelMove();
		break;
	case PLAYER_STATS_DEATH:
		Death();
		break;
	default:
		break;
	}
	

}

//=============================================================================
// パーツ追加（食べ物を食べた後の追加パーツ）処理関数
//=============================================================================
void CPlayer::AddParts(CFoodBase::FOOD_TYPE FoodType)
{
	//パーツがない時
	if (m_nParts == 0)
	{	
		//位置取得
		D3DXVECTOR3 pos = GetPos();
		//向き取得
		D3DXVECTOR3 rot = GetRot();
		//生成処理
		switch (FoodType)
		{
		case CFoodBase::TYPE_EBI:
			m_pParts[m_nParts] = CEbiParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
			break;
		case CFoodBase::TYPE_EGG:
			m_pParts[m_nParts] = CEggParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
			break;
		case CFoodBase::TYPE_IKURA:
			m_pParts[m_nParts] = CIkuraParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
			break;
		case CFoodBase::TYPE_SALMON:
			m_pParts[m_nParts] = CSalmonParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
			break;
		case CFoodBase::TYPE_TUNA:
			m_pParts[m_nParts] = CTunaParts::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), this);
			break;
		}
	}
	//パーツが１つでもある時
	else if (m_nParts>0 && m_nParts<MAX_PARTS)
	{
		//位置取得
		D3DXVECTOR3 PartsPos = m_pParts[m_nParts - 1]->GetPos();
		//向き取得
		D3DXVECTOR3 PartsRot = m_pParts[m_nParts - 1]->GetRot();
		//生成処理
		switch (FoodType)
		{
		case CFoodBase::TYPE_EBI:
			m_pParts[m_nParts] = CEbiParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
			break;
		case CFoodBase::TYPE_EGG:
			m_pParts[m_nParts] = CEggParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
			break;
		case CFoodBase::TYPE_IKURA:		
			m_pParts[m_nParts] = CIkuraParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
			break;
		case CFoodBase::TYPE_SALMON:
			m_pParts[m_nParts] = CSalmonParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
			break;
		case CFoodBase::TYPE_TUNA:
			m_pParts[m_nParts] = CTunaParts::Create(m_pParts[m_nParts - 1]->GetPos(), PartsRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_pParts[m_nParts - 1]);
			break;
		}


	}

	//パーツ数を増やす
	m_nParts++;
}

//=============================================================================
// コントローラー操作処理関数
//=============================================================================
void CPlayer::RotControl(D3DXVECTOR3 Control)
{
	//スティックに触れているかの確認（Controlのｘとｙがどちらも0.0fの場合触れていない）
	bool TouchStick = Control.x == 0.0f&&Control.y == 0.0f ? true : false;
	
	//スティックに触れている場合の処理
	if(TouchStick!= true)
	{
		//単位ベクトル取得
		D3DXVec3Normalize(&m_RotMove, &D3DXVECTOR3(Control.x, 0.0f, Control.y));
	}
}

//=============================================================================
// ダッシュ状態に移行
//=============================================================================
void CPlayer::Dash(bool bDash)
{
	m_DashSwitch = bDash;
}

//=============================================================================
// プレイヤーがダメージを受けるモノにぶつかった際の処理関数
//=============================================================================
void CPlayer::DamageHit(void)
{
	if (m_PlayerStats != PLAYER_STATS_DEATH)
	{
		m_PlayerStats = PLAYER_STATS_DEATH;
	}
}

//=============================================================================
// はじかれる処理関数
//=============================================================================
void CPlayer::Repel(CScene3d* Player)
{
	if (m_PlayerStats != PLAYER_STATS_REPEL)
	{
		//現在位置
		D3DXVECTOR3 pos = GetPos();
		//相手の位置
		D3DXVECTOR3 PlayerPos = Player->GetPos();
		//当たった方向
		D3DXVECTOR3 HItPint = D3DXVECTOR3(0.0f, atan2f((PlayerPos.x - pos.x), (PlayerPos.z - pos.z)), 0.0f);;
		//法線ベクトルの計算
		D3DXVECTOR3 Normal = PlayerPos - pos;
		//移動処理
		D3DXVECTOR3 move = D3DXVECTOR3((float)(cos(HItPint.y + D3DXToRadian(90.0f))), 0.0f, (float)(sin(HItPint.y - D3DXToRadian(90.0f))));
		//移動量
		D3DXVec3Normalize(&Normal, &Normal);
		//移動量の計算
		D3DXVec3Normalize(&m_RepelMove, &(move - 2.0f * D3DXVec3Dot(&move, &Normal) * Normal));
		m_RepelMove = (-m_RepelMove*PLAYER_REPEL) + pos;
		//加速値の初期化
		m_fDashCoutn = 0.0f;
		//状態変化
		m_PlayerStats = PLAYER_STATS_REPEL;

	}
}

//=============================================================================
// リスポーン処理
//=============================================================================
void CPlayer::Respawn(D3DXVECTOR3 RespawnPos)
{
	//リスポーン位置
	SetPos(RespawnPos);
	//ステータス設定
	m_PlayerStats = PLAYER_STATS_NORMAL;
	//死亡した際のカウント初期化
	m_nDeathFrameCount = 0;
	//アルファ値を初期化
	SetAlphaValue(1.0f);
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CPlayer::Death(void)
{
	//カウント
	m_nDeathFrameCount++;
	if (m_nDeathFrameCount % 3)
	{
		SetAlphaValue(1.0f);
	}
	else
	{
		SetAlphaValue(0.0f);
	}
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
	// コントローラーの取得
	CJoystick* pJoystick = CManager::GetInputJoystick();

	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//向き取得
	D3DXVECTOR3 rot = GetRot();
	//移動量
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//移動処理
	move = D3DXVECTOR3((float)(cos(rot.y + D3DXToRadian(90.0f))), 0.0f, (float)(sin(rot.y - D3DXToRadian(90.0f))));

	if (!m_DashSwitch)
	{
		if (m_fDashCoutn <= PLAYER_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn + 0.1f;
		}
		else if(m_fDashCoutn > PLAYER_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn - 0.1f;

		}
	}
	else
	{
		if (m_fDashCoutn <= PLAYER_BOOST_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn + 0.1f;
		}
		else if (m_fDashCoutn > PLAYER_BOOST_SPEED)
		{
			m_fDashCoutn = m_fDashCoutn - 0.1f;
		}
	}
	//スピードを計算
	move *= m_fDashCoutn;
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
	//向きたい角度
	fRotMove = atan2f((pos.x - (m_RotMove.x + pos.x)), (pos.z - (m_RotMove.z + pos.z)));
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


//=============================================================================
// はじかれた際の移動処理関数
//=============================================================================
void CPlayer::RepelMove(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//移動処理
	pos = pos + (m_RepelMove - pos)/(PLAYER_REPEL_FRAME - m_nRepelFrameCount);
	//位置セット
	SetPos(pos);
	//フレーム加算
	m_nRepelFrameCount++;

	if (m_nRepelFrameCount>= PLAYER_REPEL_FRAME)
	{
		//カウント初期化
		m_nRepelFrameCount = 0;
		//ステータスを変更
		m_PlayerStats = PLAYER_STATS_NORMAL;
	}
}

