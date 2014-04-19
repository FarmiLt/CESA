//////////////////////////////////////////////////////
//
//	詳細		：ウィンドウクラスヘッダー(singleton)
//	作成者		：岸　将史
//	最終更新日	：2013/12/03
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "Procedure.h"


class C_Window : public C_Singleton<C_Window>{
public:
	bool Initialize( HINSTANCE hInst, int nCmdShow );	// 初期化処理
	bool InitWindow( HINSTANCE hInst, int nCmdShow );	// ウィンドウの作成

	/*† ゲッター †*/
	HWND GetWindowHandle() const;		// ウィンドウハンドル

private:
	friend C_Singleton<C_Window>;		// フレンド登録
	C_Window();							// コンストラクタ
	~C_Window();						// デストラクタ

	static const TCHAR* APP_NAME;		// ♪アプリケーション名
	static const TCHAR* WINDOW_TITLE;	// ♪ウィンドウタイトル
	C_WindowProc*		m_pProcedure;	// ♪ウィンドウプロシージャ
	HWND				m_hWnd;			// ♪ウィンドウハンドル

};