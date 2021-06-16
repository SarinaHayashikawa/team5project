//=============================================================================
//
// タイトル処理 [title.h]
// Author : 林川紗梨夏
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"
//=============================================================================
//クラス
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