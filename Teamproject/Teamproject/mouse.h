//=============================================================================
//
//	�}�E�X���͏���[mouse.h]
//	Author:�g�c�I�l
//
//=============================================================================

#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "input.h"
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define NUM_CLICK_MAX (3)						//�L�[�̍ő吔
#define MOUSE_POS_TYPE							//�}�E�X�̈ړ��ʂ̏����ϊ�

//=============================================================================
// �N���X
//=============================================================================
class CMouse :public CInput
{
public:
	CMouse();
	~CMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Update(void);
	bool GetClick(int nClick);
	bool GetClickTrigger(int nClick);
	bool GetClickRelease(int nClick);

#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE GetMousePos(void);
#else 
	POINT		GetMousePos(void);
#endif

private:
	DIMOUSESTATE m_aClickState;			//�}�E�X�̓��͏�񃏁[�N
	DIMOUSESTATE m_aClickTrigger;		//�}�E�X�̃g���K�[���
	DIMOUSESTATE m_aClickRelease;		//�}�E�X�̃����[�X���

#ifdef  MOUSE_POS_TYPE
	DIMOUSESTATE m_aMousePos;			//�}�E�X�̈ړ���
#else 
	POINT posMouse;						//�}�E�X�̍��W
	HWND hPointerpos;					//�E�B���h�E�̃}�E�X�|�C���^�[�̍��W
#endif

};


#endif