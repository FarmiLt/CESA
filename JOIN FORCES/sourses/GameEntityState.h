//////////////////////////////////////////////////////
//
//	詳細		：ゲームエンティティ状態クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/14
//
//////////////////////////////////////////////////////
#pragma once
#include "BaseState.h"
#include "Singleton.h"
#include "Game3DEntity.h"


/***********************
/*†	待ち状態	 †*/
/***********************/
class C_GameEntity_Wait : public C_Singleton<C_GameEntity_Wait>, public C_BaseState<C_Game3DEntity>{
public:
	void Enter(C_Game3DEntity* pOwner) override;	// 入り際処理
	void Execute(C_Game3DEntity* pOwner) override;	// 実行処理
	void Exit(C_Game3DEntity* pOwner) override;		// 出際処理

	bool OnMessage(C_Game3DEntity* pOwner, const S_Message& message) override;	// メッセージ処理

private:
	friend C_Singleton<C_GameEntity_Wait>;
	C_GameEntity_Wait(){}		// コンストラクタ
	~C_GameEntity_Wait(){}		// デストラクタ
};


/***********************************
/*†	コントロール可能状態	 †*/
/***********************************/
class C_GameEntity_Control : public C_Singleton<C_GameEntity_Control>, public C_BaseState<C_Game3DEntity>{
public:
	void Enter(C_Game3DEntity* pOwner) override;	// 入り際処理
	void Execute(C_Game3DEntity* pOwner) override;	// 実行処理
	void Exit(C_Game3DEntity* pOwner) override;		// 出際処理

	bool OnMessage(C_Game3DEntity* pOwner, const S_Message& message) override;	// メッセージ処理

private:
	friend C_Singleton<C_GameEntity_Control>;
	C_GameEntity_Control(){}		// コンストラクタ
	~C_GameEntity_Control(){}		// デストラクタ
};