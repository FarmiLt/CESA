#include "KeyManager.h"

////////////////////////
/*† コンストラクタ †*/
////////////////////////
C_KeyManager::C_KeyManager(){
	memset( m_KeyPressingCount, 0, sizeof(m_KeyPressingCount) );
	memset( m_KeyReleasingCount, 0, sizeof(m_KeyReleasingCount) );
}


////////////////
/*†更新処理†*/
////////////////
bool C_KeyManager::Update(){
	BYTE nowKeyStatus[KeyNum];

	GetKeyboardState( nowKeyStatus );	// 現在のキー入力状態を取得

	for(int i = 0; i < KeyNum; ++i){
		// もしキーが押されているならば
		if((nowKeyStatus[i] & 0x80) != 0){
			// 離されカウンタが０より大きいなら０にする
			if(m_KeyReleasingCount[i] > 0){
				m_KeyReleasingCount[i] = 0;
			}
			// 押されカウンタを増やす
			++m_KeyPressingCount[i];
		}
		// キーが押されていないならば
		else{
			// 押されカウンタが０より大きいなら０にする
			if(m_KeyPressingCount[i] > 0){
				m_KeyPressingCount[i] = 0;
			}
			// 離されカウンタを増やす
			++m_KeyReleasingCount[i];
		}
	}
	return true;
}


//////////////////////////////////
/*† 押されカウンタを取得する †*/
//////////////////////////////////
int C_KeyManager::GetPressingCount(int keycode){
	if(! IsAvailableCode(keycode) ){
		return -1;
	}
	return m_KeyPressingCount[keycode];
}


//////////////////////////////////
/*† 離されカウンタを取得する †*/
//////////////////////////////////
int C_KeyManager::GetReleasingCount(int keycode){
	if(! IsAvailableCode(keycode)){
		return -1;
	}
	return m_KeyReleasingCount[keycode];
}


/////////////////////////////////////////
/*† keycodeが有効な値かチェックする †*/
/////////////////////////////////////////
bool C_KeyManager::IsAvailableCode(int keycode){
	if(! ( keycode >= 0 && keycode < KeyNum )){
		return false;
	}
	return true;
}