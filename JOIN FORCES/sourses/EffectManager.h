//////////////////////////////////////////////////////
//
//	詳細		：エフェクト管理クラスヘッダー(singleton)
//	作成者		：岸　将史
//	最終更新日	：2013/12/24
//
//////////////////////////////////////////////////////
#pragma once
#include <list>				// listを使用するのに必要
#include <algorithm>		// ソートを使用するのに必要
#include "Singleton.h"
#include "BaseEffect.h"		// エフェクトを管理するのに必要


class C_EffectManager : public C_Singleton<C_EffectManager>{
public:
	bool Update();					// 更新処理
	void Draw();					// 描画処理

	bool EntryTask( C_EffectTask* task );		// タスクの追加 

private:
	friend C_Singleton<C_EffectManager>;		// フレンド登録
	C_EffectManager();							// コンストラクタ
	~C_EffectManager();							// デストラクタ

	std::list<C_EffectTask*>	m_effectList;	// エフェクト収納用リスト
};