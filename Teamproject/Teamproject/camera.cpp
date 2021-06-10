//===================================================================
//
//	カメラ処理 [camera.cpp]
//	Author:林川紗梨夏
//
//===================================================================
//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
//======================================================
//インクルードファイル
//======================================================
#include "camera.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mouse.h"
#include "keyboard.h"

//======================================================
// マクロ定義
//======================================================
#define SCRIPT_PASS		"Data/TEXT/camera.txt"
#define CAMERA_INTERPOLATION 0.2f //カメラ補間スピード

#ifdef _DEBUG
#define CAMERA_SENSITIVITY (5)	// マウス感度
#define CAMERA_SPEED (10.0f)	// カメラスピード
#define CAMERA_ZOOM	(50.0f)		// カメラズーム量
#endif

//======================================================
//コンストラクタ
//======================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(20, 40, -100);
	m_posR = m_posV + D3DXVECTOR3(0, 0, 500);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(45.0f, 180.0f, 0.0f);
	m_fDistanceFromPlayer = CAMERA_DISTANCE_FROM_PLAYER;
	m_fDistanceFromPlayerDest = CAMERA_DISTANCE_FROM_PLAYER_STAND;
	m_fDistance = 0.0f;
	m_bIsFollowPlayer = false;
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fInterpolation = 0.0f;

#ifdef _DEBUG
	m_fMoveRot = 0.0f;
	m_pos = m_posV;
#endif

}
//======================================================
//デストラクタ
//======================================================
CCamera::~CCamera()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CCamera::Init(void)
{
	//カメラの初期(位置・注意点・上方向)設定
	m_posV = D3DXVECTOR3(20, 100, -200);
	m_posR = m_posV + D3DXVECTOR3(0, 0, 500);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//カメラの向き設定
	m_rot = D3DXVECTOR3(45.0f, 180.0f, 0.0f);
	//カメラのプレイヤーからの距離設定
	m_fDistanceFromPlayer = CAMERA_DISTANCE_FROM_PLAYER;
	m_fDistanceFromPlayerDest = CAMERA_DISTANCE_FROM_PLAYER;

	//マネージャーにカメラ情報を保存
	CManager::BindCamera(this);
	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CCamera::Uninit(void)
{

}

//======================================================
//更新処理
//======================================================
void CCamera::Update(void)
{
#ifdef _DEBUG
	Move();
	//移動の計算
	D3DXVECTOR3 RotateCenter = m_pos + D3DXVECTOR3(sinf(D3DXToRadian(m_rot.y - 90)),
		50,
		cosf(D3DXToRadian(-m_rot.y - 90)));

	//カメラの移動処理
	m_posV = RotateCenter +
		D3DXVECTOR3(sinf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * 1,
			sinf(D3DXToRadian(m_rot.x)) * 1,
			cosf(D3DXToRadian(-m_rot.y)) * cosf(D3DXToRadian(m_rot.x)) * 1);

	//注意点の移動処理
	m_posR = RotateCenter;

#else
	CPlayer* pPlayer = CManager::GetPlayer();

	//カメラ距離の変化を補完
	m_posV += (m_posVDest - m_posV) * m_fInterpolation;
	//カメラ距離の変化を補完
	m_posR += (m_posRDest - m_posR) * m_fInterpolation;

#endif

}

//======================================================
//カメラによる描画
//======================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();    //デバイスへのポインタ
																		 //ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_VIEW_RANGE);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//======================================================
//向き取得
//======================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

//======================================================
//向きのセット
//======================================================
void CCamera::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

void CCamera::SetCameraDistance(float fDistance)
{
	m_fDistanceFromPlayerDest = fDistance;
}

//======================================================
//カメラ情報のセット
//======================================================
void CCamera::SetCameraView(D3DXVECTOR3 posV, D3DXVECTOR3 posR, float fInterpolation)
{
	m_posVDest = posV;
	m_posRDest = posR;
	if (fInterpolation > 1.0f)
	{
		m_fInterpolation = 1.0f;//これ以上大きくなると変になるので制御
	}
	else
	{
		m_fInterpolation = fInterpolation;
	}
}

#ifdef _DEBUG
//=============================================================================
// 移動処理関数
//=============================================================================
void CCamera::Move(void)
{
	//キーボード入力の取得
	CKeyboard* pInput = (CKeyboard*)CManager::GetInputKeyboard();
	//マウス入力取得
	CMouse *pInputMouse = (CMouse*)CManager::GetInputMouse();
	//移動量
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//注視点までの距離
	D3DXVECTOR3 distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視点を動かす
	if (pInputMouse->GetClick(1))
	{
		//向き
		m_rot.x += (pInputMouse->GetMousePos().lY * (float)(0.01f * CAMERA_SENSITIVITY));
		m_rot.y -= (pInputMouse->GetMousePos().lX * (float)(0.01f * CAMERA_SENSITIVITY));
		
		//注視点の距離を変える
		if (pInputMouse->GetMousePos().lZ != 0)
		{
			//単位ベクトルに取得
			D3DXVec3Normalize(&distance, &(m_posR - m_posV));

			//ズームアウトの場合
			if (pInputMouse->GetMousePos().lZ<0)
			{
				distance *= -1;
			}
		}

		//移動
		if (pInput->GetKeyPress(DIK_W))
		{
			//移動方向指定
			m_fMoveRot = -90.0f;
			//移動時の向き設定
			m_fMoveRot += m_rot.y;
			//移動量処理
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
		}
		if (pInput->GetKeyPress(DIK_S))
		{
			//移動方向指定
			m_fMoveRot = 90.0f;
			//移動時の向き設定
			m_fMoveRot += m_rot.y;
			//移動量処理
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
		}

		if (pInput->GetKeyPress(DIK_A))
		{
			//移動方向指定
			m_fMoveRot = 0.0f;
			//移動時の向き設定
			m_fMoveRot += m_rot.y;
			//移動量処理
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
		}
		if (pInput->GetKeyPress(DIK_D))
		{
			//移動方向指定
			m_fMoveRot = 180.0f;
			//移動時の向き設定
			m_fMoveRot += m_rot.y;
			//移動量処理
			move += D3DXVECTOR3(cosf(D3DXToRadian(m_fMoveRot)), 0, sinf(D3DXToRadian(m_fMoveRot)));
		}

		//速度処理
		move *= CAMERA_SPEED;
		//ズームの感度
		distance *= CAMERA_ZOOM;

		//移動処理
		m_pos += move;
		//ズーム処理
		m_pos += distance;

	}

	//向きの限界値処理
	if ((m_rot.x) >= 89
		|| (m_rot.x) <= -89)
	{
		m_rot.x -= (pInputMouse->GetMousePos().lY * (float)(0.01f * CAMERA_SENSITIVITY));
	}
	if (m_rot.y<0)
	{
		m_rot.y += 360;
	}
	if (m_rot.y > 360)
	{
		m_rot.y -= 360;
	}



}
#endif
