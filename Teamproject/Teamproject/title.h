//=============================================================================
//
// �^�C�g������ [title.h]
// Author : �ѐ�ї���
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"
//=============================================================================
//�N���X
//=============================================================================
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();
	static CTitle *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:

};
#endif