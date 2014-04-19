//////////////////////////////////////////////////////
//
//	詳細		：オブジェクト生成クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/16
//
//////////////////////////////////////////////////////
#pragma once
#include "Entity_Cube.h"
#include "Entity_Sphere.h"
#include "Enum_Entity.h"


class C_EntityFactory{
public:
	// メソッド
		// オブジェクト生成処理
	static void Create(eENTITY object, DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
};