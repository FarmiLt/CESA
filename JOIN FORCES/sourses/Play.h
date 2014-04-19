//////////////////////////////////////////////////////
//
//	詳細		：プレイシーンクラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "BaseScene.h"
#include "Game3DEntity.h" 


class C_ScenePlay : public C_BaseScene{
public:
	C_ScenePlay( IC_SceneChanger* changer );	// コンストラクタ
	~C_ScenePlay();								// デストラクタ

	bool Initialize()	override;				// 初期化処理
	bool Update()		override;				// 更新処理
	void Draw()			override;				// 描画処理

private:
	C_Game3DEntity*	m_pEntity;
};

