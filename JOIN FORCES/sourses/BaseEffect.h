//////////////////////////////////////////////////////
//
//	詳細		：エフェクトクラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/24
//
//////////////////////////////////////////////////////
#pragma once
#include "Object.h"


class C_EffectTask : public C_ObjectTask{
public:
	// コンストラクタ
	C_EffectTask( float positionX, float positionY, float scalar = 0.0f, float angle = 0.0f, float priority = 0.5f );
	~C_EffectTask();	// デストラクタ

	bool Initialize()	override;		// 初期化処理
	bool Update()		override;		// 更新処理
	void Draw()			override;		// 描画処理

protected:
	int m_timer;		// エフェクトタイマー

private:
};
