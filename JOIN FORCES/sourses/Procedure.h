//////////////////////////////////////////////////////
//
//	詳細		：ウィンドウプロシージャクラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/03
//
//////////////////////////////////////////////////////
#pragma once

class C_WindowProc{
public:
	void					SetPointer( HWND hWnd );			// ポインタの設定
	static LRESULT CALLBACK CallProcedure( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );	// ウィンドウプロシージャの呼び出し
	virtual LRESULT			MainProcedure( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );	// ウィンドウプロシージャ（本体）

private:
};