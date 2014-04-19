#pragma once
#include "Singleton.h"


/*↓		使用しているマクロ			↓*/
//namespace Macro{
//	template<class T>
//	static const void SAFE_DELETE_ARRAY( T*& p ){
//		if ( p ){
//			delete[] p;
//			p = nullptr;
//		}
//	}
//};
/*↑		使用しているマクロ			↑*/


//////////////////////////////////////////////////////
//
//	詳細		：サウンド管理クラスヘッダー
//	用法		：使用する際は必ず
//				　xact3.h をインクルードしてください
//				　また、cppにて上のマクロを使用しております
//	参考サイト	：http://kocoon-memo.hateblo.jp/archive/category/XACT
//	作成者		：岸　将史
//	最終更新日	：2013/12/15
//
//////////////////////////////////////////////////////
class C_AudioManager : public C_Singleton<C_AudioManager>{
public:
	bool Initialize();						// 初期化処理
	bool Play();							// 再生

private:
	friend C_Singleton<C_AudioManager>;		// フレンド登録
	C_AudioManager();						// コンストラクタ
	~C_AudioManager();						// デストラクタ

	bool InitEngine();						// エンジンの初期化
	bool InitWaveBank();					// ウェーブバンクの初期化
	bool InitSoundBank();					// サウンドバンクの初期化

	IXACT3Engine*		m_pXACTEngine;		// サウンドを鳴らすエンジン
	IXACT3WaveBank*		m_pXACTWaveBank;	// ウェーブバンク(xwbファイルの格納庫)
	IXACT3SoundBank*	m_pXACTSoundBank;	// サウンドバンク(xsbファイルの格納庫)
	void*				m_pWBBuffer;		// ウェーブバンク作成に用いるバッファ領域
	void*				m_pSBBuffer;		// サウンドバンク作成に用いるバッファ領域
};