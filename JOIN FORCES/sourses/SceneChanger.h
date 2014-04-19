//////////////////////////////////////////////////////
//
//	詳細		：シーン遷移クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "Enum_Scene.h"			// シーン列挙型ヘッダー


class IC_SceneChanger{
public:
	virtual ~IC_SceneChanger() = 0;						// デストラクタ
	virtual void SwapScene( eSCENE nextScene ) = 0;		// シーン切り替え処理
};