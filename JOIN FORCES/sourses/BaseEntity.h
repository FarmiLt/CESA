//////////////////////////////////////////////////////
//
//	詳細		：基盤実体クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/14
//
//////////////////////////////////////////////////////
#pragma once
#include "Structure_Message.h"


class C_BaseEntity{
public:
	C_BaseEntity(int id);		// コンストラクタ
	virtual ~C_BaseEntity();	// デストラクタ

	virtual bool HandleMessage( const S_Message& message ) = 0;	// メッセージの受信処理

	// getアクセサ
	int GetID() const;			// IDの取得
	static int GetNextID();		// 次に使用出来るIDの取得
	

private:
	// メンバ変数
	int			m_ID;			// ID情報
	static int	m_nextID;		// 次に利用可能なID情報 
	
};