//////////////////////////////////////////////////////
//
//	詳細		：基盤状態クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/01/21
//
//////////////////////////////////////////////////////
#pragma once
#include "Structure_Message.h"


template<class T>
class C_BaseState{
public:
	virtual ~C_BaseState(){}			// デストラクタ

	virtual void Enter( T* pOwner ) = 0;		// 入り際の処理
	virtual void Execute( T* pOwner ) = 0;		// 実行処理
	virtual void Exit( T* pOwner ) = 0;			// 出際の処理

	virtual bool OnMessage( T* pOwner, const S_Message& message ) = 0;	// メッセージ処理

private:
};
