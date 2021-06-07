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
#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#define SCRIPT_PASS		"Data/TEXT/camera.txt"
#define CAMERA_INTERPOLATION 0.2f //カメラ補間スピード

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
	m_posR = D3DXVECTOR3(0, 0, 500);
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
	CPlayer* pPlayer = CManager::GetPlayer();

	//カメラ距離の変化を補完
	m_posV += (m_posVDest - m_posV) * m_fInterpolation;
	//カメラ距離の変化を補完
	m_posR += (m_posRDest - m_posR) * m_fInterpolation;

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