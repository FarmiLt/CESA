//////////////////////////////////////////////////////
//
//	詳細		：ウィンドウクラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2013/12/03
//
//////////////////////////////////////////////////////
#include "Window.h"


#pragma region 静的メンバ変数
const TCHAR* C_Window::APP_NAME		= TEXT("自作ウィンドウちゃん");
const TCHAR* C_Window::WINDOW_TITLE	= TEXT("NOTITLE");
#pragma endregion


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：メンバ変数の初期化
第１引数	：－
返却値		：－

*************************************************************************/
C_Window::C_Window() 
	: m_pProcedure( nullptr ), m_hWnd( nullptr ){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：プロシージャを解放する
第１引数	：－
返却値		：－

*************************************************************************/
C_Window::~C_Window(){
	Macro::SAFE_DELETE( m_pProcedure );
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：ウィンドウの生成
第１引数	：インスタンスハンドル
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_Window::Initialize( HINSTANCE hInstance, int nCmdShow ){
	// 多重起動防止のミューテックスハンドル
	HANDLE hMutex = nullptr;

	// ミューテックスを生成
	hMutex = CreateMutex( NULL, TRUE, TEXT("DUAL LAUNCH") );

	// 既にこのウィンドウが存在しているならエラー報告
	if ( GetLastError() == ERROR_ALREADY_EXISTS ){
		MessageBox( NULL, TEXT("既に起動されています"), TEXT("DUAL LAUNCH"), MB_OK );
		return false;
	}
	
	// ウィンドウクラス構造体のオブジェクトを作成
	WNDCLASSEX windowClass;		
	
	// オブジェクトの初期化
	windowClass.cbSize			= sizeof( WNDCLASSEX );
	windowClass.style			= CS_VREDRAW | CS_HREDRAW;
	windowClass.lpfnWndProc		= C_WindowProc::CallProcedure;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= hInstance;
	windowClass.hIcon			= LoadIcon( hInstance, (LPCTSTR)NULL );
	windowClass.hCursor			= LoadCursor( NULL, IDC_ARROW );
	windowClass.hbrBackground	= (HBRUSH)( COLOR_WINDOW + 1 );
	windowClass.lpszMenuName	= NULL;
	windowClass.lpszClassName	= APP_NAME;
	windowClass.hIconSm			= LoadIcon( windowClass.hInstance, (LPCTSTR)NULL );
	// ウィンドウクラスの登録
	if ( !RegisterClassEx( &windowClass ) ){
		MessageBox( NULL, TEXT("ウィンドウクラスの登録に失敗しました"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// ウィンドウプロシージャの生成
	if ( m_pProcedure == nullptr ) m_pProcedure = new C_WindowProc;

	// ウィンドウの生成
	if ( !InitWindow( hInstance, nCmdShow ) ){
		MessageBox( NULL, TEXT("Window.cpp(94)"), TEXT("ERROR"), MB_OK );
		return false;
	}
	//if ( !InitWindow( hInstance, nCmdShow ) ){
	//	MessageBox( NULL, TEXT("Window.cpp(94)"), TEXT("ERROR"), MB_OK );
	//	return false;
	//}
	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：ウィンドウハンドルを渡す
第１引数	：－
返却値		：ウィンドウハンドル

*************************************************************************/
HWND C_Window::GetWindowHandle() const{
	return m_hWnd;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/13
用途		：ウィンドウの生成
第１引数	：－
返却値		：正常終了[true], 異常検知[false]

*************************************************************************/
bool C_Window::InitWindow( HINSTANCE hInst, int nCmdShow ){
	// クライアント領域を640 * 480に保つ
    RECT rc = { 0, 0, Macro::WINDOW_WIDTH, Macro::WINDOW_HEIGHT };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

	// ウインドウの作成
    m_hWnd = CreateWindow(	APP_NAME,			// アプリケーション名
							WINDOW_TITLE,			// ウィンドウタイトル
							WS_OVERLAPPEDWINDOW,	// ウィンドウのスタイル
							CW_USEDEFAULT,			// ウィンドウの横方向位置
							CW_USEDEFAULT,			// ウィンドウの縦方向位置
							rc.right - rc.left,		// 画面幅
							rc.bottom - rc.top,		// 画面高さ
							NULL,					// 親ウィンドウのハンドル
							NULL,					// 子ウィンドウのハンドル
							hInst,					// ウィンドウのインスタンスハンドル
							(LPVOID)m_pProcedure );	// プロシージャのポインタ

	// ウィンドウ作成に失敗したらfalseを返す
    if( m_hWnd == nullptr ){
		MessageBox( NULL, TEXT("ウィンドウの作成に失敗しました"), TEXT("ERROR"), MB_OK );
        return false;
	}

	// ウィンドウの表示状態の設定
    ShowWindow( m_hWnd, nCmdShow );

	return true;
}