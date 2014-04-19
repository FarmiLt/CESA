#pragma once
#include "Singleton.h"

/******************************
		キーマネージャ
******************************/
class C_KeyManager : public C_Singleton<C_KeyManager>{
	C_KeyManager();							// コンストラクタ
	friend C_Singleton<C_KeyManager>;		// フレンド登録

private:
	static const int KeyNum = 256;			// キーの総数
	int m_KeyPressingCount[KeyNum];
	int m_KeyReleasingCount[KeyNum];
	
	bool IsAvailableCode(int keycode);		// keycodeが有効なキー番号かどうか

public:
	bool Update();

	// ゲッター
	int GetPressingCount(int keycode);
	int GetReleasingCount(int keycode);


};