//////////////////////////////////////////////////////
//
//	詳細		：球体クラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2014/04/16
//
//////////////////////////////////////////////////////
#include "Entity_Sphere.h"
#include "ModelManager.h"
#include "Camera.h"
#include "DirectX.h"
#include "KeyManager.h"


#pragma region 静的メンバ変数
float C_Entity_Sphere::DEFAULT_RADIUS = 10.0f;
#pragma endregion


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/22
用途		：メンバ変数の初期化
第１引数	：エンティティID
第２引数	：表示座標(default : (0, 0, 0) )
第３引数	：エンティティの大きさ(default : 1.0f)
返却値		：－

*************************************************************************/
C_Entity_Sphere::C_Entity_Sphere(DirectX::SimpleMath::Vector3 position, float scale)
: C_Game3DEntity(C_BaseEntity::GetNextID(), position, scale)
, m_velocity(0.3f){
	m_entityType = eENTITY::ENTITY_SPHERE;
	
	// 半径の設定
	m_radius = DEFAULT_RADIUS * scale;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：メンバ変数の解放
第１引数	：－
返却値		：－

*************************************************************************/
C_Entity_Sphere::~C_Entity_Sphere(){
	Macro::SAFE_DELETE(m_pStateMachine);
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/18
用途		：状態に沿って更新処理を行う
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_Entity_Sphere::Update(){
	C_Game3DEntity::Update();
	m_pStateMachine->Update();
	
	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：描画処理
第１引数	：－
返却値		：－

*************************************************************************/
void C_Entity_Sphere::Render(){
	// デバッグ用
	C_Game3DEntity::Render();

	C_ModelManager::GetInstance()->GetCommonModel(COMMONMODEL_SPHERE)
		->Draw(	C_DirectX::GetInstance()->GetDeviceContext(),
				*(C_DirectX::GetInstance()->GetCommonState()),
				m_world,
				C_BaseCamera::GetInstance()->GetViewMatrix(),
				C_BaseCamera::GetInstance()->GetProjectionMatrix());
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/21
用途		：入力によってエンティティを操作する
第１引数	：－
返却値		：－

*************************************************************************/
void C_Entity_Sphere::Control(){
	// カメラの角度を取得
	float angle = C_BaseCamera::GetInstance()->GetCameraAngleAxisY();

	// 右へ移動
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_RIGHT) >= 1){	
		DirectX::SimpleMath::Vector3 pos(GetPosition().x + m_velocity * cosf(DirectX::XMConvertToRadians(angle - 90.0f)),
										 GetPosition().y,
										 GetPosition().z + m_velocity * sinf(DirectX::XMConvertToRadians(angle - 90.0f)));
		SetPosition(pos);
	}

	// 左へ移動
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_LEFT) >= 1){
		DirectX::SimpleMath::Vector3 pos(GetPosition().x + m_velocity * cosf(DirectX::XMConvertToRadians(angle + 90.0f)),
										 GetPosition().y,
										 GetPosition().z + m_velocity * sinf(DirectX::XMConvertToRadians(angle + 90.0f)));
		SetPosition(pos);
	}

	// 奥へ移動
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_UP) >= 1){
		DirectX::SimpleMath::Vector3 pos(GetPosition().x + m_velocity * cosf(DirectX::XMConvertToRadians(angle + 180.0f)),
										 GetPosition().y,
										 GetPosition().z + m_velocity * sinf(DirectX::XMConvertToRadians(angle + 180.0f)));
		SetPosition(pos);
	}

	// 手前に移動
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_DOWN) >= 1){
		DirectX::SimpleMath::Vector3 pos(GetPosition().x + m_velocity * cosf(DirectX::XMConvertToRadians(angle)),
										 GetPosition().y, 
										 GetPosition().z + m_velocity * sinf(DirectX::XMConvertToRadians(angle)));
		SetPosition(pos);
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：メッセージを状態クラスに投げる
第１引数	：メッセージ情報
返却値		：処理された→true, 処理されなかった→false

*************************************************************************/
bool C_Entity_Sphere::HandleMessage(const S_Message& message){
	return false; 
}