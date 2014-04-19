//////////////////////////////////////////////////////
//
//	詳細		：メッセージ管理クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/01/27
//	備考		：遅延時間が有るメッセージはまだ未実装
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "BaseEntity.h"
#include "Structure_Message.h"


class C_MessageDispatcher : public C_Singleton<C_MessageDispatcher>{
public:
	void Dispatch( int delay, int senderID, int receiverID, int message, void* extra );	// メッセージの作成処理

private:
	friend C_Singleton<C_MessageDispatcher>;	// フレンドに登録
	C_MessageDispatcher();						// コンストラクタ
	~C_MessageDispatcher();						// デストラクタ

	void Send( C_BaseEntity* pSender, const S_Message& message );	// メッセージの送信処理

};
