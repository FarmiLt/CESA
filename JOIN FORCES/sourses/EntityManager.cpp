//////////////////////////////////////////////////////
//
//	詳細		：実体管理クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/16
//
//////////////////////////////////////////////////////
#include "EntityManager.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：コンテナ内を空にする
第１引数	：－
返却値		：－

*************************************************************************/
C_EntityManager::~C_EntityManager(){
	// イテレータの作成
	std::map<int, C_Game3DEntity*>::iterator iter = m_entityMap.begin();

	while( iter != m_entityMap.end() ){
		// エンティティを削除する
		Macro::SAFE_DELETE(iter->second);
		// リストから削除する
		iter = m_entityMap.erase( iter );
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/17
用途		：登録されているエンティティの更新
第１引数	：－
返却値		：－

*************************************************************************/
void C_EntityManager::Update(){
	// イテレータの作成
	std::map<int, C_Game3DEntity*>::iterator iter = m_entityMap.begin();

	while (iter != m_entityMap.end()){
		// もし、死亡フラグが立っている場合削除する
		if (iter->second->IsDead()){
			// エンティティを削除する
			Macro::SAFE_DELETE(iter->second);

			// リストから削除する
			iter = m_entityMap.erase(iter);
		}
		else{
			// 更新処理を行う
			iter->second->Update();
			++iter;
		}
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/17
用途		：登録されているエンティティの描画
第１引数	：－
返却値		：－

*************************************************************************/
void C_EntityManager::Render(){
	// イテレータの作成
	std::map<int, C_Game3DEntity*>::iterator iter = m_entityMap.begin();

	// 描画
	while (iter != m_entityMap.end()){
		iter->second->Render();
		++iter;
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：実体の情報をコンテナ内に登録する
第１引数	：実体のアドレス
返却値		：－

*************************************************************************/
void C_EntityManager::RegisterEntity( C_Game3DEntity* pEntity ){
	m_entityMap.insert( std::pair<int, C_Game3DEntity*>( pEntity->GetID(), pEntity ) );
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：IDを基にそのIDを持つ実体のアドレスを取得する
第１引数	：実体のID情報
返却値		：実体のアドレス

*************************************************************************/
C_BaseEntity* C_EntityManager::GetEntity( int id ){
	// イテレータの作成
	std::map<int, C_Game3DEntity*>::iterator iter = m_entityMap.find( id );

	// 引数をキーとする要素が有るならその値を返す
	if ( iter != m_entityMap.end() ){
		return iter->second;
	}
	else{
		return nullptr;
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：IDを基にそのIDを持つ実体のアドレスをコンテナから削除する
第１引数	：実体のID情報
返却値		：－

*************************************************************************/
void C_EntityManager::DeleteEntity( int id ){
	// イテレータの作成
	std::map<int, C_Game3DEntity*>::iterator iter = m_entityMap.find( id );

	if ( iter != m_entityMap.end() ){
		// エンティティを削除する
		Macro::SAFE_DELETE(iter->second);

		// リストから削除する
		iter = m_entityMap.erase( iter );
	}
}