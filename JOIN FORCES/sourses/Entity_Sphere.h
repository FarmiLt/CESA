//////////////////////////////////////////////////////
//
//	詳細		：球体クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/16
//
//////////////////////////////////////////////////////
#pragma once
#include "Game3DEntity.h"


class C_Entity_Sphere : public C_Game3DEntity{
public:
	C_Entity_Sphere(DirectX::SimpleMath::Vector3 position, float scale);	// コンストラクタ
	~C_Entity_Sphere();										// デストラクタ

	bool Update()	override;		// 更新処理
	void Render()	override;		// 描画処理
	void Control()	override;		// 操作処理

	bool HandleMessage(const S_Message& message) override;	// メッセージ受信処理

private:
	static float	DEFAULT_RADIUS;		// 標準の半径
	float			m_velocity;			// 速度
	
};