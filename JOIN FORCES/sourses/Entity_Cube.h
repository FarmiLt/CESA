//////////////////////////////////////////////////////
//
//	詳細		：立方体クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/15
//
//////////////////////////////////////////////////////
#pragma once
#include "Game3DEntity.h"


class C_Entity_Cube : public C_Game3DEntity{
public:
	C_Entity_Cube(DirectX::SimpleMath::Vector3 position);	// コンストラクタ
	~C_Entity_Cube();										// デストラクタ

	bool HandleMessage(const S_Message& message) override;	// メッセージ処理

	bool Update() override;		// 更新処理
	void Render() override;		// 描画処理
	void Control() override;	// 操作処理

private:
};