//////////////////////////////////////////////////////
//
//	詳細		：立方体クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/24
//
//////////////////////////////////////////////////////
#pragma once
#include "Game3DEntity.h"


class C_Entity_Cube : public C_Game3DEntity{
public:
	C_Entity_Cube(DirectX::SimpleMath::Vector3 position, float scale);	// コンストラクタ
	~C_Entity_Cube();										// デストラクタ

	bool HandleMessage(const S_Message& message) override;	// メッセージ処理

	bool Update()	override;		// 更新処理
	void Render()	override;		// 描画処理
	void Control()	override;		// 操作処理

private:
	// ポリゴン情報構造体
	struct S_Polygon{
		DirectX::SimpleMath::Vector3 vertices[4];	// 面をなす頂点座標
		int	number;									// 自身の面番号
		int neighbor[4];							// 隣り合う面番号
	};

	// メンバ変数
	int								m_nowUnderPolygon;	// 現在の底面
	static const int				VERTEX_MAX = 8;		// 頂点個数(立方体なので当然８つ)
	static float					DEFAULT_RADIUS;		// 標準の半径
	S_Polygon						POLYGON_LIST[6];	// ポリゴン情報リスト
	DirectX::SimpleMath::Vector3	m_vertices[8];		// 頂点情報
};