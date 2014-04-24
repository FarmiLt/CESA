///////////////////////////////////////////////
//
//	詳細		：DirectXクラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/17
//
///////////////////////////////////////////////
#include "Procedure.h"
#include "Window.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：自身のポインタをプロパティリストに設定する
第１引数	：－
返却値		：－

*************************************************************************/
void C_WindowProc::SetPointer( HWND hWnd ){
	SetWindowLong( hWnd, GWL_USERDATA, (LONG)this );
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：ウィンドウプロシージャへの仲介
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
LRESULT CALLBACK C_WindowProc::CallProcedure( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ){
	// プロパティリストから自身のポインタを取得する
	C_WindowProc* thisptr = (C_WindowProc*)GetWindowLong( hWnd, GWL_USERDATA );

	// 自身のポインタが取得出来なかった場合
	if( !thisptr ){

		// それがウィンドウが生成される時だったら
		if( uMsg == WM_CREATE ){

			thisptr = (C_WindowProc*)( (LPCREATESTRUCT)lParam )->lpCreateParams;
		}

		// 無事自身のポインタが取得出来たらプロパティリストにセットする
		if( thisptr ){
			thisptr->SetPointer( hWnd );
		}
	}
	
	if ( thisptr ){
		// プロシージャにメッセージを送る
		LRESULT lResult = thisptr->MainProcedure( hWnd, uMsg, wParam, lParam );
		return lResult;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/21
用途		：ウィンドウプロシージャ
第１引数	：－
返却値		：

*************************************************************************/
LRESULT C_WindowProc::MainProcedure( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ){
	// メッセージに沿った処理を実行する
	switch( uMsg ){
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE){
			if (MessageBox(NULL, TEXT("終了しますか？"), TEXT("終了確認"), MB_YESNO) == IDYES){
				SendMessage(C_Window::GetInstance()->GetWindowHandle(), WM_DESTROY, 0, 0);
				return 0;
			}
		}

	default:
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
}