//////////////////////////////////////////////////////
//
//	詳細		：ゲームで利用する3D実体クラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2014/04/17
//
//////////////////////////////////////////////////////
#include "Game3DEntity.h"
#include "GameEntityState.h"
#include "Camera.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/17
用途		：メンバ変数の初期化
第１引数	：－
返却値		：－

*************************************************************************/
C_Game3DEntity::C_Game3DEntity(int id, DirectX::SimpleMath::Vector3 position)
: C_BaseEntity(id)
, m_radius(0.0f)
, m_position(position)
, m_deadFlag(false)
, m_crashing(false){

	// ワールド行列を作成
	m_world = DirectX::XMMatrixIdentity();
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);


	// 状態管理クラスを作成
	m_pStateMachine = new C_StateMachine<C_Game3DEntity>(this);

	// もし、エンティティIDが０ならば操作対象にする
	if (GetID() == 0){
		m_pStateMachine->SetCurrentState(C_GameEntity_Control::GetInstance());
		m_controlling = true;
		// カメラの追従対象に設定
		C_BaseCamera::GetInstance()->SetOwner(this);
	}
	else{
		m_pStateMachine->SetCurrentState(C_GameEntity_Wait::GetInstance());
		m_controlling = false;
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：メンバ変数の解放
第１引数	：－
返却値		：－

*************************************************************************/
C_Game3DEntity::~C_Game3DEntity(){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/18
用途		：ワールド座標の変換を行う
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_Game3DEntity::Update(){
	// 行列の初期化
	m_world = DirectX::XMMatrixIdentity();

	// 表示座標に合わせる
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	return true;
}



/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/17
用途		：デバッグ用のデータをコンソール画面に描画
第１引数	：－
返却値		：－

*************************************************************************/
void C_Game3DEntity::Render(){
#ifdef _DEBUG
	std::cout << "EntityID : " << GetID() << std::endl
		<< "POSITION_X : " << m_position.x << std::endl
		<< "POSITION_Y : " << m_position.y << std::endl
		<< "POSITION_Z : " << m_position.z << std::endl;
#endif
}

/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：ここではメッセージを処理しない
第１引数	：メッセージ内容
返却値		：正常に処理された→true, 処理されなかった→false

*************************************************************************/
bool C_Game3DEntity::HandleMessage(const S_Message& message){
	return false;
}


#pragma region setアクセサ


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：死亡フラグを立てる
第１引数	：－
返却値		：－

*************************************************************************/
void C_Game3DEntity::Kill(){
	m_deadFlag = true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：操作状態の切り換え
第１引数	：－
返却値		：－

*************************************************************************/
void C_Game3DEntity::ChangeControl(){
	m_controlling = !m_controlling;

	if (m_controlling){
		m_pStateMachine->ChangeState(C_GameEntity_Control::GetInstance());
	}
	else{
		m_pStateMachine->ChangeState(C_GameEntity_Wait::GetInstance());
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/17
用途		：衝突フラグを切り換える
第１引数	：－
返却値		：－

*************************************************************************/
void C_Game3DEntity::Crashed(bool isCrashed){
	m_crashing = isCrashed;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/18
用途		：表示する座標を変更する
第１引数	：新しい座標
返却値		：－

*************************************************************************/
void C_Game3DEntity::SetPosition(DirectX::SimpleMath::Vector3 position){
	m_position = position;
}


#pragma endregion


#pragma region getアクセサ


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/13
用途		：死亡状況を取得する
第１引数	：－
返却値		：死んでいる→false, 生きている→true

*************************************************************************/
bool C_Game3DEntity::IsDead() const{
	return m_deadFlag;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：操作中かどうかを取得する
第１引数	：－
返却値		：操作中じゃない→false, 操作中→true

*************************************************************************/
bool C_Game3DEntity::IsControlling() const{
	return m_controlling;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/17
用途		：衝突中かどうかを取得する(CollisionManagerで使用)
第１引数	：－
返却値		：衝突していない→false, 衝突中→true

*************************************************************************/
bool C_Game3DEntity::IsCrashing() const{
	return m_crashing;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/13
用途		：自身の座標を取得する
第１引数	：－
返却値		：表示座標情報

*************************************************************************/
DirectX::SimpleMath::Vector3 C_Game3DEntity::GetPosition() const{
	return m_position;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/18
用途		：自身の半径を取得する
第１引数	：－
返却値		：半径

*************************************************************************/
float C_Game3DEntity::GetRadius() const{
	return m_radius;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/18
用途		：自身の図形タイプを取得する
第１引数	：－
返却値		：図形タイプ

*************************************************************************/
eENTITY C_Game3DEntity::IsType() const{
	return m_entityType;
}


#pragma endregion