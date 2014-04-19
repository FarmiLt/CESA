//////////////////////////////////////////////////////
//
//	詳細		：状態管理クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/01/27
//
//////////////////////////////////////////////////////
#pragma once
#include "BaseState.h"
#include "Structure_Message.h"


template<class T>
class C_StateMachine{
public:
	C_StateMachine( T* pOwner );		// コンストラクタ
	~C_StateMachine();					// デストラクタ

	bool Update();			// 更新処理
	void SetCurrentState( C_BaseState<T>* pFirstState );	// 現在の状態を設定
	void SetGlobalState( C_BaseState<T>* pState );			// 常時実行状態を設定
	void ChangeState( C_BaseState<T>* pNextState );			// 現在の状態を遷移する処理

	bool HandleMessage( const S_Message& message );			// メッセージ受信処理

private:
	T*				m_pOwner;			// オーナー情報
	C_BaseState<T>*	m_pCurrentState;	// 現在の状態
	C_BaseState<T>*	m_pGlobalState;		// 常に行う状態

};


//////////////////////////////////////////////////////
//
//	詳細		：状態管理クラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2014/01/27
//
//////////////////////////////////////////////////////

/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：メンバ変数の初期化
第１引数	：オーナーのアドレス
返却値		：－

*************************************************************************/
template<class T> C_StateMachine<T>::C_StateMachine(T* pOwner)
: m_pOwner(pOwner)
, m_pCurrentState(nullptr)
, m_pGlobalState(nullptr){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：－
第１引数	：－
返却値		：－

*************************************************************************/
template<class T> C_StateMachine<T>::~C_StateMachine(){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：常駐する状態と現在の状態に伴った処理を行う
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
template<class T> bool C_StateMachine<T>::Update(){
	if (m_pCurrentState){
		m_pCurrentState->Execute(m_pOwner);
	}
	if (m_pGlobalState){
		m_pGlobalState->Execute(m_pOwner);
	}

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：初期の現在の状態を設定する
第１引数	：現在の状態のアドレス
返却値		：－

*************************************************************************/
template<class T> void C_StateMachine<T>::SetCurrentState(C_BaseState<T>* pFirstState){
	m_pCurrentState = pFirstState;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：常駐する状態を設定する
第１引数	：常駐する状態のアドレス
返却値		：－

*************************************************************************/
template<class T> void C_StateMachine<T>::SetGlobalState(C_BaseState<T>* pState){
	m_pGlobalState = pState;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：現在の状態から次の状態へ置き換える
第１引数	：次に差し替える状態のアドレス
返却値		：－

*************************************************************************/
template<class T> void C_StateMachine<T>::ChangeState(C_BaseState<T>* pNextState){
	// 切り替える直前の処理を行う
	if (m_pCurrentState) m_pCurrentState->Exit(m_pOwner);

	m_pCurrentState = pNextState;

	// 切り替えられた直後の処理を行う
	if (m_pCurrentState) m_pCurrentState->Enter(m_pOwner);
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/01/27
用途		：メッセージを現在の状態もしくは常駐している状態に処理してもらう
第１引数	：メッセージ
返却値		：処理された→true, されなかった→false

*************************************************************************/
template<class T> bool C_StateMachine<T>::HandleMessage(const S_Message& message){
	if (m_pCurrentState->OnMessage(m_pOwner, message)){
		return true;
	}
	if (m_pGlobalState->OnMessage(m_pOwner, message)){
		return true;
	}

	return false;
}