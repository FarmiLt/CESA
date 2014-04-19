//////////////////////////////////////////////////////
//
//	詳細		：オブジェクト生成クラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2014/04/18
//
//////////////////////////////////////////////////////
#include "EntityFactory.h"
#include "EntityManager.h"
#include "CollisionManager.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/18
用途		：インスタンスを生成して
			　エンティティ管理クラスと衝突管理クラスに登録する
第１引数	：オブジェクトの種類
第２引数	：表示座標
返却値		：－

*************************************************************************/
void C_EntityFactory::Create(eENTITY objectType, DirectX::SimpleMath::Vector3 position){
	C_Game3DEntity* entity;

	switch (objectType){
		// 立方体
	case eENTITY::ENTITY_CUBE :
		entity = new C_Entity_Cube(position);
		break;

		// 球体
	case eENTITY::ENTITY_SPHERE :
		entity = new C_Entity_Sphere(position);
		break;

		// TODO: 図形を追加するならここに

	default:
		MessageBox(NULL, TEXT("そのオブジェクト情報はファクトリに登録されていません (C_EntityFactory::Create)"), TEXT("ERROR"), MB_OK);
		return;
	}

	// エンティティ管理クラスに登録
	C_EntityManager::GetInstance()->RegisterEntity(entity);

	// 衝突管理クラスに登録
	C_CollisionManager::GetInstance()->RegisterEntity(entity);
}