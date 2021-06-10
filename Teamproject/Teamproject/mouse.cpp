//=============================================================================
//
//	マウス入力処理[mouse.cpp]
//	Author:吉田 悠人
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "mouse.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CMouse::CMouse()
{
	//座標の初期化
#ifdef  MOUSE_POS_TYPE
	m_aMousePos.lX = (LONG)0.0f;
	m_aMousePos.lY = (LONG)0.0f;

#else 
	posMouse.x = 0.0f;
	posMouse.y = 0.0f;
#endif
	memset(m_aClickState.rgbButtons, 0, sizeof(m_aClickState.rgbButtons));
	memset(m_aClickTrigger.rgbButtons, 0, sizeof(m_aClickTrigger.rgbButtons));
	memset(m_aClickRelease.rgbButtons, 0, sizeof(m_aClickRelease.rgbButtons));


}

//=============================================================================
//デストラクタ
//=============================================================================
CMouse::~CMouse()
{
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//座標の初期化
#ifdef  MOUSE_POS_TYPE
	m_aMousePos.lX = (LONG)0.0f;
	m_aMousePos.lY = (LONG)0.0f;
#else 
	hPointerpos = hWnd;
	posMouse.x = 0.0f;
	posMouse.y = 0.0f;
#endif

	//入力デバイス（マウス）の作成
	if (FAILED(m_pDinput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	/*データフォーマットを設定*/
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	/*協調モードを設定（フォアグラウンド＆非排他モード*/
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))))
	{
		return E_FAIL;
	}
	// 軸モードを設定（相対値モードに設定）
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;
	//diprop.dwData       = DIPROPAXISMODE_ABS; // 絶対値モードの場合

	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	/*マウスへのアクセス権を会得（入力制御開始）*/
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
//更新処理
//=============================================================================
void CMouse::Update(void)
{


#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE ClickState;
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &ClickState)))
	{
		for (int nCntClick = 0; nCntClick < NUM_CLICK_MAX; nCntClick++)
		{
			//クリック処理
			m_aClickState.rgbButtons[nCntClick] = ClickState.rgbButtons[nCntClick];
			//クリックトリガー処理
			m_aClickTrigger.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&ClickState.rgbButtons[nCntClick];
			//クリックリリース処理
			m_aClickRelease.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&~ClickState.rgbButtons[nCntClick];
		}
		//マウスの移動量取得（IXとIYの移動量）
		m_aMousePos = ClickState;
	}

	else
	{
		m_pDevice->Acquire();
	}
#else 
	DIMOUSESTATE ClickState;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &ClickState)))
	{
		for (int nCntClick = 0; nCntClick < NUM_CLICK_MAX; nCntClick++)
		{
			//クリックトリガー処理
			m_aClickTrigger.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&ClickState.rgbButtons[nCntClick];
			//クリックリリース処理
			m_aClickRelease.rgbButtons[nCntClick] = (m_aClickState.rgbButtons[nCntClick] ^ ClickState.rgbButtons[nCntClick])&~ClickState.rgbButtons[nCntClick];
			//クリック処理
			m_aClickState.rgbButtons[nCntClick] = ClickState.rgbButtons[nCntClick];

		}
	}

	else
	{
		m_pDevice->Acquire();
	}
	////スクリーン座標取得
	GetCursorPos(&posMouse);
	ScreenToClient(hPointerpos, &posMouse);

#endif

}

//=============================================================================
// 位置処理
//=============================================================================
#ifdef  MOUSE_POS_TYPE
DIMOUSESTATE CMouse::GetMousePos(void)
{
	return m_aMousePos;
}
#else 
POINT CInputMouse::GetMousePos(void)
{
	return posMouse;
}
#endif

//=============================================================================
// クリック処理
//=============================================================================
bool CMouse::GetClick(int nClick)
{
	return (m_aClickState.rgbButtons[nClick] & 0x80) ? true : false;
}

bool CMouse::GetClickTrigger(int nClick)
{
	return (m_aClickTrigger.rgbButtons[nClick] & 0x80) ? true : false;
}

bool CMouse::GetClickRelease(int nClick)
{
	return (m_aClickRelease.rgbButtons[nClick] & 0x80) ? true : false;
}
