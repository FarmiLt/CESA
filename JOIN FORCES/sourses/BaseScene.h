//////////////////////////////////////////////////////
//
//	詳細		：基本シーンクラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "SceneChanger.h"
#include "EntityFactory.h"


class C_BaseScene{
public:
	C_BaseScene( IC_SceneChanger* changer );	// コンストラクタ
	virtual ~C_BaseScene() = 0;					// デストラクタ

	virtual bool Initialize() = 0;				// 初期化処理
	virtual bool Update() = 0;					// 更新処理
	virtual void Draw() = 0;					// 描画処理

private:
	IC_SceneChanger* m_pChanger;				// シーン管理クラスにアクセスするためのポインタ
};