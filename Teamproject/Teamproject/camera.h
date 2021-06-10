//=====================================================================
//
//	カメラ処理 [camera.h]
//	Author  林川紗梨夏
//
//=====================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//======================================================
//マクロ定義
//======================================================
#define CAMERA_VIEW_RANGE (10000.0f)
#define CAMERA_DISTANCE_FROM_PLAYER (100.0f)
#define CAMERA_DISTANCE_FROM_PLAYER_STAND (200.0f)
#define PLAYER_CAMERA_HEIGHT (20.0f) //プレイヤーの高さ

//======================================================
//クラス定義
//======================================================
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetRot(void);
	void SetRot(D3DXVECTOR3 rot);
	void SetCameraDistance(float fDistance);
	//static void LoadScriptCamera(void);

#ifdef _DEBUG
	void		Move(void);			// 移動処理
#endif
private:

	void SetCameraView(D3DXVECTOR3 posV, D3DXVECTOR3 posR, float fInterpolation);

	D3DXVECTOR3 m_posV;            // カメラの座標
	D3DXVECTOR3 m_posR;            // 注視点の座標
	D3DXVECTOR3 m_vecU;            // カメラの上方向
	D3DXMATRIX m_mtxProjection;    // プロジェクションマトリックス
	D3DXMATRIX m_mtxView;          // ビューマトリックス
	D3DXVECTOR3 m_RotateCenter;    // カメラの回転中心座標
	float m_fDistance;             // 視点-注意点の距離
	float m_fDistanceFromPlayer;
	float m_fDistanceFromPlayerDest;
	D3DXVECTOR3 m_rot;				   
	D3DXVECTOR3 m_posVDest;         // カメラの座標(差)
	D3DXVECTOR3 m_posRDest;         // 注視点の座標(差)
	bool m_bIsFollowPlayer;			// プレイヤーに追従するか
	float m_fInterpolation;			// カメラ補間スピード

#ifdef _DEBUG						   
	float m_fMoveRot;				// 移動する向き
	D3DXVECTOR3 m_pos;				// 位置
#endif

};

#endif
