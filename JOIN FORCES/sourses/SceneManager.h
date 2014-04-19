//////////////////////////////////////////////////////
//
//	詳細		：シーン遷移クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "SceneChanger.h"
#include "BaseScene.h"


class C_SceneManager : public IC_SceneChanger{
public:
	C_SceneManager( eSCENE firstScene );			// コンストラクタ
	~C_SceneManager();								// デストラクタ

	bool Update();									// 更新処理
	void Draw();									// 描画処理

	void SwapScene( eSCENE nextScene )	override;	// シーン切り替え処理

private:
	C_BaseScene*	m_pCurrentScene;				// 現在のシーン
	eSCENE			m_nextScene;					// 次のシーン情報
};