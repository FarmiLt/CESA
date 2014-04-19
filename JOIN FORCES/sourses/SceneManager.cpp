//////////////////////////////////////////////////////
//
//	詳細		：シーン管理クラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2013/12/17
//
//////////////////////////////////////////////////////
#include "SceneManager.h"
#include "Logo.h"
#include "Title.h"
#include "Play.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/17
用途		：一番初めのシーン情報を次のシーンとして割り当てる
第１引数	：一番初めに表示するシーン情報
返却値		：－

*************************************************************************/
C_SceneManager::C_SceneManager( eSCENE firstScene )
	: m_pCurrentScene( nullptr ){
	m_nextScene = firstScene;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/17
用途		：シーンデータの解放
第１引数	：－
返却値		：－

*************************************************************************/
C_SceneManager::~C_SceneManager(){
	Macro::SAFE_DELETE( m_pCurrentScene );
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/19
用途		：次のシーン情報が入ったらそのシーンに切り替える
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_SceneManager::Update(){
	// 次のシーン情報が入っていればシーンを作る
	if ( m_nextScene != SCENE_NONE ){

		// 現在のシーンを解放する
		Macro::SAFE_DELETE( m_pCurrentScene );

		// シーンを作成する
		switch( m_nextScene ){
		case SCENE_LOGO:
			m_pCurrentScene = new C_SceneLogo( this );
			break;

		case SCENE_TITLE:
			m_pCurrentScene = new C_SceneTitle( this );
			break;

		case SCENE_PLAY:
			m_pCurrentScene = new C_ScenePlay( this );
			break;

		default:
			MessageBox( NULL, TEXT("未解決のシーンが呼び出されました"), TEXT("ERROR"), MB_OK );
			return false;
		}
		// シーンの初期化
		if ( !m_pCurrentScene->Initialize() ){
			return false;
		}

		// 次のシーン情報を空にする
		m_nextScene = SCENE_NONE;
	}

	// シーンの更新
	if ( !m_pCurrentScene->Update() ){
		return false;
	}
	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/19
用途		：現在のシーンの描画処理を行う
第１引数	：－
返却値		：－

*************************************************************************/
void C_SceneManager::Draw(){
	m_pCurrentScene->Draw();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/17
用途		：次のシーン情報にデータを入れる
第１引数	：－
返却値		：－

*************************************************************************/
void C_SceneManager::SwapScene( eSCENE nextScene ){
	m_nextScene = nextScene;
}