//////////////////////////////////////////////////////
//
//	詳細		：プレイシーンクラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/16
//
//////////////////////////////////////////////////////
#include "Play.h"
#include "Camera.h"
#include "Entity_Cube.h"
#include "DirectX.h"
#include "ModelManager.h" 
#include "CollisionManager.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/17
用途		：シーン切り替え用のアドレスを保管する
第１引数	：シーン切り替え用アドレス
返却値		：－

*************************************************************************/
C_ScenePlay::C_ScenePlay( IC_SceneChanger* changer )
	: C_BaseScene( changer )
	, m_pEntity(nullptr){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/17
用途		：メンバ変数の解放
第１引数	：－
返却値		：－

*************************************************************************/
C_ScenePlay::~C_ScenePlay(){
	Macro::SAFE_DELETE(m_pEntity);
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：シーンに必要なデータの作成
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_ScenePlay::Initialize(){
	// エンティティの生成
	C_EntityFactory::Create(eENTITY::ENTITY_SPHERE, DirectX::SimpleMath::Vector3(10.0f, 10.0f, 0.0f));
	C_EntityFactory::Create(eENTITY::ENTITY_SPHERE, DirectX::SimpleMath::Vector3(-50.0f, 10.0f, 30.0f), 2.0f);
	C_EntityFactory::Create(eENTITY::ENTITY_CUBE, DirectX::SimpleMath::Vector3(100.0f, 10.0f, 50.0f));
	//m_pEntity = new C_Entity_Sphere(DirectX::SimpleMath::Vector3(0.0f, 10.0f, 0.0f) );

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：シーンを更新する
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_ScenePlay::Update(){
	// 衝突判定を行う
	C_CollisionManager::GetInstance()->Update();
	
	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：シーンで利用するテクスチャ及びモデルを描画する
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
void C_ScenePlay::Draw(){
	DirectX::XMMATRIX f_world = DirectX::XMMatrixIdentity();

	C_ModelManager::GetInstance()->GetCommonModel(COMMONMODEL_FLOOR)
		->Draw(C_DirectX::GetInstance()->GetDeviceContext(),
		*(C_DirectX::GetInstance()->GetCommonState()),
		f_world,
		C_BaseCamera::GetInstance()->GetViewMatrix(),
		C_BaseCamera::GetInstance()->GetProjectionMatrix());

}