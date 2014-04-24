//////////////////////////////////////////////////////
//
//	詳細		：立方体クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/24
//
//////////////////////////////////////////////////////
#include "Entity_Cube.h"
#include "ModelManager.h"
#include "DirectX.h" 
#include "Camera.h"
#include "GameEntityState.h"
#include "KeyManager.h"


#pragma region 静的メンバ変数
float C_Entity_Cube::DEFAULT_RADIUS = 10.0f;
#pragma endregion


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/24
用途		：メンバ変数の初期化
第１引数	：エンティティID
第２引数	：表示座標(default : (0, 0, 0) )
第３引数	：エンティティの大きさ(default : 1.0f)
返却値		：－

*************************************************************************/
C_Entity_Cube::C_Entity_Cube(DirectX::SimpleMath::Vector3 position, float scale)
: C_Game3DEntity(C_BaseEntity::GetNextID(), position, scale){
	m_entityType = eENTITY::ENTITY_CUBE;
	m_radius = DEFAULT_RADIUS * scale;

	// 頂点情報の設定
	POLYGON_LIST[0] = {
		// ポリゴンをなす頂点
		{ { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z } },
		0,					// 面番号
		{ 1, 2, 3, 4 }		// 隣接面番号
	};

	POLYGON_LIST[1] = {
		{ { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z } },
		1,
		{ 5, 2, 0, 4 }
	};

	POLYGON_LIST[2] = {
		{ {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z } },
		2,
		{ 1, 5, 3, 0 }
	};

	POLYGON_LIST[3] = {
		{ { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z } },
		3,
		{ 0, 2, 5, 4 }
	};

	POLYGON_LIST[4] = {
		{ { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z } },
		4,
		{ 1, 0, 3, 5 }
	};
	
	POLYGON_LIST[5] = {
		{ {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z } },
		5,
		{ 1, 4, 3, 2 }
	};
	// 一番最初の底面は０
	m_nowUnderPolygon = 0;

	// 状態管理クラスの作成
	m_pStateMachine = new C_StateMachine<C_Game3DEntity>(this);

	// エンティティIDが０ならば操作対象に設定する
	if (GetID() == 0){
		m_pStateMachine->SetCurrentState(C_GameEntity_Control::GetInstance());
	}
	else{
		// 違うなら待機状態
		m_pStateMachine->SetCurrentState(C_GameEntity_Wait::GetInstance());
	}
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
最終更新日	：2014/04/22
用途		：状態管理クラスの更新処理を呼び出す
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_Entity_Cube::Update(){
	// ワールド座標の再設定
	C_Game3DEntity::Update();

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

	C_ModelManager::GetInstance()->GetCommonModel(COMMONMODEL_CUBE)
		->Draw( C_DirectX::GetInstance()->GetDeviceContext(),
				*(C_DirectX::GetInstance()->GetCommonState()),
				m_world,
				C_BaseCamera::GetInstance()->GetViewMatrix(),
				C_BaseCamera::GetInstance()->GetProjectionMatrix() );
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/22
用途		：オブジェクトの操作を行う処理
第１引数	：－
返却値		：－

*************************************************************************/
void C_Entity_Cube::Control(){
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_RIGHT) == 1){

	}
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