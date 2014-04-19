//////////////////////////////////////////////////////
//
//	詳細		：ロゴシーンクラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "BaseScene.h"


class C_SceneLogo : public C_BaseScene{
public:
	C_SceneLogo( IC_SceneChanger* changer );	// コンストラクタ
	~C_SceneLogo()		override;				// デストラクタ

	bool Initialize()	override;				// 初期化処理
	bool Update()		override;				// 更新処理
	void Draw()			override;				// 描画処理

private:
	
};

