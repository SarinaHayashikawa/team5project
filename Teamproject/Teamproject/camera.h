//=====================================================================
//
//	�J�������� [camera.h]
//	Author  �ѐ�ї���
//
//=====================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//======================================================
//�}�N����`
//======================================================
#define CAMERA_VIEW_RANGE (10000.0f)
#define CAMERA_DISTANCE_FROM_PLAYER (100.0f)
#define CAMERA_DISTANCE_FROM_PLAYER_STAND (200.0f)
#define PLAYER_CAMERA_HEIGHT (20.0f) //�v���C���[�̍���

//======================================================
//�N���X��`
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
	void		Move(void);			// �ړ�����
#endif
private:

	void SetCameraView(D3DXVECTOR3 posV, D3DXVECTOR3 posR, float fInterpolation);

	D3DXVECTOR3 m_posV;            // �J�����̍��W
	D3DXVECTOR3 m_posR;            // �����_�̍��W
	D3DXVECTOR3 m_vecU;            // �J�����̏����
	D3DXMATRIX m_mtxProjection;    // �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;          // �r���[�}�g���b�N�X
	D3DXVECTOR3 m_RotateCenter;    // �J�����̉�]���S���W
	float m_fDistance;             // ���_-���ӓ_�̋���
	float m_fDistanceFromPlayer;
	float m_fDistanceFromPlayerDest;
	D3DXVECTOR3 m_rot;				   
	D3DXVECTOR3 m_posVDest;         // �J�����̍��W(��)
	D3DXVECTOR3 m_posRDest;         // �����_�̍��W(��)
	bool m_bIsFollowPlayer;			// �v���C���[�ɒǏ]���邩
	float m_fInterpolation;			// �J������ԃX�s�[�h

#ifdef _DEBUG						   
	float m_fMoveRot;				// �ړ��������
	D3DXVECTOR3 m_pos;				// �ʒu
#endif

};

#endif
