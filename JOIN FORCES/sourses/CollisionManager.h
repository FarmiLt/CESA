//////////////////////////////////////////////////////
//
//	詳細		：衝突管理クラス
//	補足		：このクラスに登録されているエンティティは
//				　『絶対にdeleteしないでください！』
//				　( エンティティ管理クラスがやってくれます )
//	作成者		：岸　将史
//	最終更新日	：2014/04/18
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "Game3DEntity.h"


class C_CollisionManager : public C_Singleton<C_CollisionManager>{
public:
	void Update();									// 更新処理
	void RegisterEntity(C_Game3DEntity* pObject);	// エンティティの追加

private:
	friend C_Singleton<C_CollisionManager>;			// フレンドに登録
	C_CollisionManager(){}							// コンストラクタ
	~C_CollisionManager();							// デストラクタ

	// 衝突判定諸々
	bool Crash_Sphere2Sphere(C_Game3DEntity* pController, C_Game3DEntity* pSphere);	// 球と球
	bool Crash_Cube2Cube(C_Game3DEntity* pController, C_Game3DEntity* pSphere);		// 立方体と立方体

	// メンバ変数
	C_Game3DEntity*				m_pController;		// 操作エンティティ
	std::list<C_Game3DEntity*>	m_pCubeList;		// 立方体のリスト
	std::list<C_Game3DEntity*>	m_pSphereList;		// 球体のリスト

	// TODO: 図形を追加する場合はこちらへリストを追加
};