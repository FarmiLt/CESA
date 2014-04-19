//////////////////////////////////////////////////////
//
//	詳細		：システム管理クラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2014/04/18
//
//////////////////////////////////////////////////////
#include "SystemManager.h"
#include "Window.h"
#include "DirectX.h"			// DirectXの機能を使用するのに必要
#include "KeyManager.h"			// キーボード処理
#include "ImageManager.h"		// 画像を利用するのに必要
#include "ModelManager.h"		// モデルを利用するのに必要
//#include "AudioManager.h"		// サウンドを使用するのに必要
//#include "FpsTimer.h"			// フレームレート管理
#include "EffectManager.h"
#include "EntityManager.h"
#include "Camera.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/19
用途		：メンバ変数の初期化
第１引数	：－
返却値		：－

*************************************************************************/
C_SystemManager::C_SystemManager( HINSTANCE hInst, int nCmd )
	: m_pSceneManager( nullptr )
	, m_hInstance( hInst )
	, m_nCmdShow( nCmd ){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：終了処理の呼び出し
第１引数	：－
返却値		：－

*************************************************************************/
C_SystemManager::~C_SystemManager(){
	Finalize();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/12
用途		：ウィンドウの生成, DirectXの生成, 画像管理クラスの初期化
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_SystemManager::Initialize(){
	// ウィンドウを作成する
	if ( !C_Window::GetInstance()->Initialize( m_hInstance, m_nCmdShow ) ){
		return false;
	}

	// DirectXデバイス諸々を作成する
	if ( !C_DirectX::GetInstance()->Initialize( C_Window::GetInstance()->GetWindowHandle() ) ){
		return false;
	}

	// 画像クラスの初期化
	if ( !C_ImageManager::GetInstance()->Initialize() ){
		return false;
	}

	// モデルクラスの初期化
	if (!C_ModelManager::GetInstance()->Initialize()){
		return false;
	}

	// シーンマネージャの作成
	m_pSceneManager = new C_SceneManager( SCENE_PLAY );

	// サウンドの作成
	//if ( !C_AudioManager::GetInstance()->Initialize() ){
	//	return false;
	//}
	//C_AudioManager::GetInstance()->Play();

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/18
用途		：ゲームシーンの更新、描画
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
int C_SystemManager::GameRun(){
	// メッセージの初期化
	MSG msg = {0};

	// メインループ
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			// キー処理の更新
			C_KeyManager::GetInstance()->Update();

			// ゲームシーンの更新
			if ( !m_pSceneManager->Update() ) break;

			// カメラの更新
			C_BaseCamera::GetInstance()->Update();

			// エンティティの更新
			C_EntityManager::GetInstance()->Update();

			// エフェクトの更新
			C_EffectManager::GetInstance()->Update();

			// DirectXデバイス側で画面のクリアやスワップ処理を行う
			if ( !C_DirectX::GetInstance()->Update() ) break;

			// 時間を調整する
//			fps.Wait();

			//if ( !fps.CheckDrawSkip() ){
			
			// ゲームシーンの描画
			m_pSceneManager->Draw();

			// エンティティの更新
			C_EntityManager::GetInstance()->Render();

			// エフェクトの描画
			C_EffectManager::GetInstance()->Draw();
			
			//}

#ifdef _DEBUG
	//::system("cls");
	//std::cout << "------------ DEBUG MODE ------------" << std::endl;
	//std::cout << "調べたいデータは [#ifdef _DEBUG] 内にcoutで出すといい" << std::endl;

	
#endif
        }
    }
	return static_cast<int>( msg.wParam );
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/19
用途		：メンバ変数の解放
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
void C_SystemManager::Finalize(){
	Macro::SAFE_DELETE( m_pSceneManager );
}