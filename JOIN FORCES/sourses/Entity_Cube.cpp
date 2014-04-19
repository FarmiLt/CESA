//////////////////////////////////////////////////////
//
//	詳細		：立方体クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/15
//
//////////////////////////////////////////////////////
#include "Entity_Cube.h"
#include "ModelManager.h"
#include "DirectX.h" 
#include "Camera.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：メンバ変数の初期化
第１引数	：－
返却値		：－

*************************************************************************/
C_Entity_Cube::C_Entity_Cube(DirectX::SimpleMath::Vector3 position)
: C_Game3DEntity(C_BaseEntity::GetNextID(), position){
	m_entityType = eENTITY::ENTITY_CUBE;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：メンバ変数の解放
第１引数	：－
返却値		：－

*************************************************************************/
C_Entity_Cube::~C_Entity_Cube(){
	Macro::SAFE_DELETE(m_pStateMachine);
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：状態管理クラスの更新処理を呼び出す
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_Entity_Cube::Update(){
	m_pStateMachine->Update();

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：モデルを描画する
第１引数	：－
返却値		：－

*************************************************************************/
void C_Entity_Cube::Render(){
	// デバッグ用
	C_Game3DEntity::Render();

	C_ModelManager::GetInstance()->GetCommonModel(COMMONMODEL_BOX)
		->Draw( C_DirectX::GetInstance()->GetDeviceContext(),
				*(C_DirectX::GetInstance()->GetCommonState()),
				m_world,
				C_BaseCamera::GetInstance()->GetViewMatrix(),
				C_BaseCamera::GetInstance()->GetProjectionMatrix() );
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：オブジェクトの操作を行う処理
第１引数	：－
返却値		：－

*************************************************************************/
void C_Entity_Cube::Control(){

}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：メッセージを状態管理クラスで処理させる
第１引数	：－
返却値		：正常に処理→true, 処理されなかった→false

*************************************************************************/
bool C_Entity_Cube::HandleMessage(const S_Message& message){
	if (m_pStateMachine->HandleMessage(message)){
		return false;
	}
	return true;
}