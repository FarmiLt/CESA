//////////////////////////////////////////////////////
//
//	詳細		：基盤実体クラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2014/01/27
//
//////////////////////////////////////////////////////
#include "MessageDispatcher.h"
#include "EntityManager.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：−
第１引数	：−
返却値		：−

*************************************************************************/
C_MessageDispatcher::C_MessageDispatcher(){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：−
第１引数	：−
返却値		：−

*************************************************************************/
C_MessageDispatcher::~C_MessageDispatcher(){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：−
第１引数	：遅延時間
第２引数	：送信元のID
第３引数	：送信先のID
第４引数	：メッセージ内容
第５引数	：備考
返却値		：−

*************************************************************************/
void C_MessageDispatcher::Dispatch( int delay, int senderID, int receiverID, int message, void* extra ){
	// 実体管理クラスから送信先のアドレスを取得する
	C_BaseEntity* pReceiver = C_EntityManager::GetInstance()->GetEntity( receiverID );

	// メッセージの作成
	S_Message l_message = { delay, senderID, receiverID, message, extra };

	// 遅延時間が設けられていないならば即座に送信する
	if ( delay <= 0 ){
		Send( pReceiver, l_message );
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：送信先にメッセージを転送する
第１引数	：送信先のアドレス
第２引数	：メッセージ概要
返却値		：−

*************************************************************************/
void C_MessageDispatcher::Send( C_BaseEntity* pReceiver, const S_Message& message ){
	pReceiver->HandleMessage( message );
}