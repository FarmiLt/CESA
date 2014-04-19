//////////////////////////////////////////////////////
//
//	詳細		：実体管理クラスヘッダー
//	補足		：基本的にエンティティを削除するのは
//				　このクラス内で行うこと！
//				　また、作成したエンティティは
//				　必ずこのクラスに登録すること！
//	作成者		：岸　将史
//	最終更新日	：2014/04/16
//
//////////////////////////////////////////////////////
#pragma once
#include "Game3DEntity.h"
#include "Singleton.h"


class C_EntityManager : public C_Singleton<C_EntityManager>{
public:
	
	void Update();									// 更新処理
	void Render();									// 描画処理
	void RegisterEntity( C_Game3DEntity* pEntity );	// 実体の登録

	// アクセサ
	C_BaseEntity* GetEntity( int id );				// 実体アドレスの取得

private:
	friend C_Singleton<C_EntityManager>;			// フレンドに登録
	C_EntityManager(){}								// コンストラクタ
	~C_EntityManager();								// デストラクタ

	void DeleteEntity( int id );					// 実体の削除

	// メンバ変数
	std::map<int, C_Game3DEntity*>	m_entityMap;	// 実体情報管理コンテナ
};