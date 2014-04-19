//////////////////////////////////////////////////////
//
//	詳細		：システム管理クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/03
//
//////////////////////////////////////////////////////
#pragma once
#include "DirectX.h"
#include "SceneManager.h"		// シーンを作成するのに必要
//#include "FpsTimer.h"

class C_SystemManager{
public:
	C_SystemManager(HINSTANCE hInst, int nCmd );	// コンストラクタ
	~C_SystemManager();								// デストラクタ

	bool Initialize();								// 初期化処理
	int GameRun();									// メインループ処理

private:
	void Finalize();								// 終了処理

	/*↓↓ 以下メンバ変数 ↓↓*/
	//FpsTimer		fps;
	C_SceneManager* m_pSceneManager;				// シーン管理クラスデータ
	HINSTANCE		m_hInstance;					// インスタンスハンドル
	int				m_nCmdShow;						// コマンド
};
