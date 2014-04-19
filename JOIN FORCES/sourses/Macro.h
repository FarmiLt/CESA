//////////////////////////////////////////////////////
//
//	詳細		：マクロ管理ヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/16
//
//////////////////////////////////////////////////////
#pragma once


// マクロだと分かり易くするための名前空間
namespace Macro{
	static const int WINDOW_WIDTH	= 640;		// ウィンドウ幅
	static const int WINDOW_HEIGHT	= 480;		// ウィンドウ高さ

	// ポインタの安全解放
	template<class T>
	static const void SAFE_DELETE( T*& p ){ if ( p ) delete p; p = nullptr; }

	template<class T>
	static const void SAFE_DELETE_ARRAY( T*& p ){ if ( p ) delete[] p; p = nullptr; }
}