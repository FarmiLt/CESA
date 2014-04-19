//////////////////////////////////////////////////////
//
//	詳細		：カメラの状態クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/14
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "BaseState.h"
#include "Camera.h"


/***********************
/*†	追従状態	 †*/
/***********************/
class C_Camera_Following : public C_Singleton<C_Camera_Following>, public C_BaseState<C_BaseCamera>{
public:
	void Enter(C_BaseCamera* pOwner) override;		// 入り際処理
	void Execute(C_BaseCamera* pOwner) override;	// 実行処理
	void Exit(C_BaseCamera* pOwner) override;		// 出際処理

	bool OnMessage(C_BaseCamera* pOwner, const S_Message& message) override;	// メッセージ処理

private:
	friend C_Singleton<C_Camera_Following>;
	C_Camera_Following(){}		// コンストラクタ
	~C_Camera_Following(){}		// デストラクタ

};


/***********************
/*†	定点状態	 †*/
/***********************/
class C_Camera_Fixed : public C_Singleton<C_Camera_Fixed>, public C_BaseState<C_BaseCamera>{
public:
	void Enter(C_BaseCamera* pOwner) override;		// 入り際処理
	void Execute(C_BaseCamera* pOwner) override;	// 実行処理
	void Exit(C_BaseCamera* pOwner) override;		// 出際処理

	bool OnMessage(C_BaseCamera* pOwner, const S_Message& message) override;	// メッセージ処理

private:
	friend C_Singleton<C_Camera_Fixed>;
	C_Camera_Fixed(){}			// コンストラクタ
	~C_Camera_Fixed(){}			// デストラクタ
};