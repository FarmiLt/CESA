//////////////////////////////////////////////////////
//
//	詳細		：基本シーンクラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2013/12/17
//
//////////////////////////////////////////////////////
#include "BaseScene.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/17
用途		：シーン切り替え用のアドレスを保管する
第１引数	：シーン切り替え用アドレス
返却値		：−

*************************************************************************/
C_BaseScene::C_BaseScene( IC_SceneChanger* changer ){
	m_pChanger = changer;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/17
用途		：−
第１引数	：−
返却値		：−

*************************************************************************/
C_BaseScene::~C_BaseScene(){
}