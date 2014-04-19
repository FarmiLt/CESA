//////////////////////////////////////////////////////
//
//	詳細		：入力処理クラスヘッダー
//				　このクラスでは主にXBOX360コントローラ
//				　での処理を行います
//	作成者		：岸　将史
//	最終更新日	：2014/04/14
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"


class C_InputManager : public C_Singleton<C_InputManager>{
public:
	void Update();		// 更新処理

	// getアクセサ
	bool	IsConnecting() const;					// コントローラが繋がっているか
	int		GetPressingCount(int button) const;		// コントローラのボタン押され状態を取得

private:
	friend C_Singleton<C_InputManager>;	// フレンドに登録
	C_InputManager();					// コンストラクタ
	~C_InputManager();					// デストラクタ

	// メンバ変数
	XINPUT_STATE 

};