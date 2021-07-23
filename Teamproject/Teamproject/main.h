//=============================================================================
//
// メイン処理 [main.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <Windows.h>
#include <dinput.h>
#include "d3dx9.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define SCREEN_WIDTH	(1920)
//#define SCREEN_HEIGHT	(1080)
#define SCREEN_WIDTH	(1280)	//画面の横幅
#define SCREEN_HEIGHT	(720)	//画面の立幅
#define MAX_PLAYER		(4)		//プレイヤーの最大数


#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"ws2_32.lib")

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	float		rhw; //座標変換用紙係数
	D3DCOLOR	col; //頂点カラー
	D3DXVECTOR2	tex; //テクスチャ
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR	col;	//頂点カラー
	D3DXVECTOR2	tex;	//テクスチャ
}VERTEX_3D;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#ifdef _DEBUG
int GetFPS(void);
#endif
#endif