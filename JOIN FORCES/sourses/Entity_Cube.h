//////////////////////////////////////////////////////
//
//	詳細		：立方体クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/25
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
		int verticesNumber[4];		// ポリゴンを形成している頂点データ
		int neighborPolygon[4];		// 隣接するポリゴン番号
	};

	// 移動列挙型
	enum eMOVE{
		MOVE_UP,		// 奥
		MOVE_RIGHT,		// 右
		MOVE_DOWN,		// 手前
		MOVE_LEFT,		// 左
		MOVE_NONE,		// 移動なし
	};

	// メソッド
	void GetKey();			// キー取得処理
	void Move_Up();			// 奥移動
	void Move_Right();		// 右移動
	void Move_Down();		// 手前移動
	void Move_Left();		// 左移動
	
	// setアクセサ
	void SetVertices(DirectX::SimpleMath::Matrix matrix);		// 頂点情報の書き換え

	// メンバ変数
	static const int				POLYGON_MAX = 6;			// 面の数(立方体なので当然６枚)
	static const int				VERTEX_MAX = 8;				// 頂点個数(立方体なので当然８つ)
	static const float				DEFAULT_RADIUS;				// 標準の半径
	static const float				ROTATION_SPEED;				// 移動時の回転速度
	DirectX::SimpleMath::Vector3	m_vertices[VERTEX_MAX];		// 頂点情報
	int								m_nowPolygon;				// 現在の底面
	float							m_distance;					// 中心点と辺の距離
	S_Polygon						m_polygonData[POLYGON_MAX];	// 面の情報
	eMOVE							m_moveState;				// 現在の移動状態
};