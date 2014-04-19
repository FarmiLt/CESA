//////////////////////////////////////////////////////
//
//	詳細		：メイン関数
//	補足		：ウィンドウは必ずウィンドウの閉じるボタンから
//				　閉じること。
//				　デバッグの停止、コマンドプロンプト自体を
//				　閉じるとコマンドプロンプトだけ残ります。
//	作成者		：岸　将史
//	最終更新日	：2014/04/17
//
//////////////////////////////////////////////////////
#include "SystemManager.h"

#pragma warning (disable : 4996)


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/17
用途		：システムマネージャの生成、初期化、
第１引数	：－
返却値		：正常終了 → 0 、異常終了 → -1

*************************************************************************/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPInst, LPSTR lpCmd, int nCmdShow ){
	
#ifdef _DEBUG
	// メモリーリーク検出のための設定
	::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	// コンソール画面の表示
	//::AllocConsole();
	//freopen("CONIN$", "r", stdin);
	//freopen("CONOUT$", "w", stdout);

	//std::cout << "------------ DEBUG MODE ------------" << std::endl;
	//std::cout << "調べたいデータは [#ifdef _DEBUG] 内にcoutで出すといい" << std::endl;
#endif

	// システムマネージャのオブジェクトを生成する
	C_SystemManager systemManager( hInstance, nCmdShow );

	// システムマネージャの初期化
	if ( !systemManager.Initialize() ){
		// エラー報告
		MessageBox( NULL, TEXT("システムマネージャの初期化に失敗しました"), TEXT("ERROR"), MB_OK );
		return -1;
	}

	// システムマネージャの更新
	systemManager.GameRun();

#ifdef _DEBUG
	// コンソール画面の削除
	//::FreeConsole();
#endif

	return 0;
}