//////////////////////////////////////////////////////
//
//	詳細		：立方体クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/25
//
//////////////////////////////////////////////////////
#include "Entity_Cube.h"
#include "ModelManager.h"
#include "DirectX.h" 
#include "Camera.h"
#include "GameEntityState.h"
#include "KeyManager.h"

#pragma region 静的メンバ変数
const float C_Entity_Cube::DEFAULT_RADIUS = 10.0f;
const float C_Entity_Cube::ROTATION_SPEED = 0.5f;
#pragma endregion

/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/25
用途		：メンバ変数の初期化
第１引数	：エンティティID
第２引数	：表示座標(default : (0, 0, 0) )
第３引数	：エンティティの大きさ(default : 1.0f)
返却値		：－

*************************************************************************/
C_Entity_Cube::C_Entity_Cube(DirectX::SimpleMath::Vector3 position, float scale)
: C_Game3DEntity(C_BaseEntity::GetNextID(), position, scale){
	// エンティティタイプを立方体に設定
	m_entityType = eENTITY::ENTITY_CUBE;

	// 半径(仮)の設定
	m_radius = DEFAULT_RADIUS * scale;

	// 立方体の中心点から辺までの最短距離を算出
	m_distance = sqrt((DEFAULT_RADIUS * scale) * (DEFAULT_RADIUS * scale) 
					+ (DEFAULT_RADIUS * scale) * (DEFAULT_RADIUS * scale));


	// 頂点情報の設定
	m_vertices[0] = DirectX::SimpleMath::Vector3(-DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS * scale + m_position.y, -DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[1] = DirectX::SimpleMath::Vector3( DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS * scale + m_position.y, -DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[2] = DirectX::SimpleMath::Vector3( DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS * scale + m_position.y,  DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[3] = DirectX::SimpleMath::Vector3(-DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS * scale + m_position.y,  DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[4] = DirectX::SimpleMath::Vector3(-DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS * scale + m_position.y, -DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[5] = DirectX::SimpleMath::Vector3( DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS * scale + m_position.y, -DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[6] = DirectX::SimpleMath::Vector3( DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS * scale + m_position.y,  DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[7] = DirectX::SimpleMath::Vector3(-DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS * scale + m_position.y,  DEFAULT_RADIUS * scale + m_position.z);

	// 面の情報を設定
		// 形成する頂点の番号	(その面を下にしたとき、左上、右上、右下、左下　の順)
		// 隣接面の番号			(奥、右、手前、左　の順)
	m_polygonData[0] = { {0, 1, 2, 3}, {1, 2, 3, 4} };
	m_polygonData[1] = { {4, 5, 1, 0}, {5, 2, 0, 4} };
	m_polygonData[2] = { {1, 5, 6, 2}, {1, 5, 3, 0} };
	m_polygonData[3] = { {3, 2, 6, 7}, {0, 2, 5, 4} };
	m_polygonData[4] = { {4, 0, 3, 7}, {1, 0, 3, 5} };
	m_polygonData[5] = { {5, 4, 7, 6}, {1, 4, 3, 2} };

	// 一番最初の底面は０
	m_nowPolygon = 0;

	// 移動状態を初期化する
	m_moveState = eMOVE::MOVE_NONE;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/25
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
	// 座標および状態管理クラスの更新
	C_Game3DEntity::Update();



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
最終更新日	：2014/04/26
用途		：オブジェクトの操作を行う処理
第１引数	：－
返却値		：－

*************************************************************************/
void C_Entity_Cube::Control(){
	// キー取得する(後述)
	if ( m_moveState == eMOVE::MOVE_NONE ){
		GetKey();
	}

	switch(m_moveState){
	case eMOVE::MOVE_UP :
		// 奥移動処理
		Move_Up();
		return;

	case eMOVE::MOVE_RIGHT :
		// 右移動処理
		Move_Right();
		return;

	case eMOVE::MOVE_DOWN :
		// 手前移動処理
		Move_Down();
		return;

	case eMOVE::MOVE_LEFT :
		// 左移動処理
		Move_Left();
		return;
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


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/26
用途		：キーの取得を行い、移動状態を切り換える処理
第１引数	：－
返却値		：－

*************************************************************************/
void C_Entity_Cube::GetKey(){
	if ( C_KeyManager::GetInstance()->GetPressingCount(VK_UP) == 1 ){
		m_moveState = eMOVE::MOVE_UP;
	}
	if ( C_KeyManager::GetInstance()->GetPressingCount(VK_RIGHT) == 1 ){
		m_moveState = eMOVE::MOVE_RIGHT;
	}
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_DOWN) == 1 ){
		m_moveState = eMOVE::MOVE_DOWN;
	}
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_LEFT) == 1){
		m_moveState = eMOVE::MOVE_LEFT;
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/25
用途		：奥への移動処理
第１引数	：－
返却値		：－

*************************************************************************/
void C_Entity_Cube::Move_Up(){
	// 回転角度
	static float rotX = 0.0f;
	
	rotX -= ROTATION_SPEED;
	// 90度分動いたら移動を止める
	if ( rotX <= -90.0f ){
		rotX = -90.0f;
		m_moveState = eMOVE::MOVE_NONE;	
	}

	// Ｘ軸に対して回転させる
	 DirectX::SimpleMath::Matrix rotXMatrix =
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f),
			DirectX::XMConvertToRadians(rotX)
		);

	// ワールド行列に反映する
	m_world *= rotXMatrix;
	
#pragma region 自身の座標にも反映させる処理
	DirectX::SimpleMath::Matrix matTransPos = DirectX::XMMatrixIdentity();

	// 座標を原点に戻す
	matTransPos *= 
		DirectX::SimpleMath::Matrix::CreateTranslation(-m_position);

	// 移動差分を求める際の角度を予めラジアンに変換
	float rad = DirectX::XMConvertToRadians(45.0f - (rotX + ROTATION_SPEED));

	// 回転している分を考慮して回転軸を合わせる
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
			DirectX::SimpleMath::Vector3( 0, 
				m_distance * sinf(rad),
				m_distance * cosf(rad)
			)
		);
	// Ｘ軸回転処理
	matTransPos *= 
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f),
				DirectX::XMConvertToRadians(-ROTATION_SPEED)
			);

	// 座標を原点に戻す
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
			DirectX::SimpleMath::Vector3(0,
				-m_distance * sinf(rad),
				-m_distance * cosf(rad)
			)
		);
	// 元の座標位置に戻す
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_position = DirectX::SimpleMath::Vector3::Transform(m_position, matTransPos);

#pragma endregion

	// 回転角度を戻す
	if ( m_moveState == eMOVE::MOVE_NONE ){
		rotX = 0.0f;
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/25
用途		：右方向に移動する処理
第１引数	：－
返却値		：－

*************************************************************************/
void C_Entity_Cube::Move_Right(){
	static float rotZ = 0.0f;
	rotZ -= ROTATION_SPEED;
	// 90度分動いたら移動を止める
	if (rotZ <= -90.0f){
		rotZ = -90.0f;
		m_moveState = eMOVE::MOVE_NONE;
	}

	// Ｚ軸に対して回転させる
	DirectX::SimpleMath::Matrix rotZMatrix =
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f),
		DirectX::XMConvertToRadians(rotZ)
		);

	// ワールド行列に反映する
	m_world *= rotZMatrix;

#pragma region 自身の座標にも反映させる処理
	DirectX::SimpleMath::Matrix matTransPos = DirectX::XMMatrixIdentity();

	// 座標を原点に戻す
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(-m_position);

	// 移動差分を求める際の角度を予めラジアンに変換
	float rad = DirectX::XMConvertToRadians(135.0f + (rotZ + ROTATION_SPEED));

	// 回転している分を考慮して回転軸を合わせる
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(m_distance * cosf(rad),
		m_distance * sinf(rad),
		0
		)
		);
	// Ｚ軸回転処理
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f),
		DirectX::XMConvertToRadians(-ROTATION_SPEED)
		);
	// 座標を原点に戻す
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(-m_distance * cosf(rad),
		-m_distance * sinf(rad),
		0
		)
		);
	// 元の座標位置に戻す
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_position = DirectX::SimpleMath::Vector3::Transform(m_position, matTransPos);

#pragma endregion




	// 回転角度を戻す
	if ( m_moveState == eMOVE::MOVE_NONE ){
		rotZ = 0.0f;
	}

}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/25
用途		：メンバ変数の解放
第１引数	：－
返却値		：－

*************************************************************************/
void C_Entity_Cube::Move_Down(){
	// 回転角度
	static float rotX = 0.0f;

	rotX += ROTATION_SPEED;
	// 90度分動いたら移動を止める
	if (rotX >= 90.0f){
		rotX = 90.0f;
		m_moveState = eMOVE::MOVE_NONE;
	}

	// Ｘ軸に対して回転させる
	DirectX::SimpleMath::Matrix rotXMatrix =
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f),
		DirectX::XMConvertToRadians(rotX)
		);

	// ワールド行列に反映する
	m_world *= rotXMatrix;

#pragma region 自身の座標にも反映させる処理
	DirectX::SimpleMath::Matrix matTransPos = DirectX::XMMatrixIdentity();

	// 座標を原点に戻す
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(-m_position);

	// 移動差分を求める際の角度を予めラジアンに変換
	float rad = DirectX::XMConvertToRadians(135.0f - (rotX - ROTATION_SPEED));

	// 回転している分を考慮して回転軸を合わせる
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(0,
		m_distance * sinf(rad),
		m_distance * cosf(rad)
		)
		);
	// Ｘ軸回転処理
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f),
		DirectX::XMConvertToRadians(ROTATION_SPEED)
		);

	// 移動差分を求める際の角度を予めラジアンに変換
	//rad = DirectX::XMConvertToRadians(45.0f + (rotX + ROTATION_SPEED));

	// 座標を原点に戻す
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(0,
		-m_distance * sinf(rad),
		-m_distance * cosf(rad)
		)
		);
	// 元の座標位置に戻す
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_position = DirectX::SimpleMath::Vector3::Transform(m_position, matTransPos);

#pragma endregion



	// 回転角度を戻す
	if (m_moveState == eMOVE::MOVE_NONE){
		rotX = 0.0f;
	}

}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/25
用途		：メンバ変数の解放
第１引数	：－
返却値		：－

*************************************************************************/
void C_Entity_Cube::Move_Left(){
	static float rotZ = 0.0f;
	rotZ += ROTATION_SPEED;
	// 90度分動いたら移動を止める
	if (rotZ >= 90.0f){
		rotZ = 90.0f;
		m_moveState = eMOVE::MOVE_NONE;
	}

	// Ｚ軸に対して回転させる
	DirectX::SimpleMath::Matrix rotZMatrix =
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f),
		DirectX::XMConvertToRadians(rotZ)
		);

	// ワールド行列に反映する
	m_world *= rotZMatrix;


#pragma region 自身の座標にも反映させる処理
	DirectX::SimpleMath::Matrix matTransPos = DirectX::XMMatrixIdentity();

	// 座標を原点に戻す
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(-m_position);

	// 移動差分を求める際の角度を予めラジアンに変換
	float rad = DirectX::XMConvertToRadians(45.0f + (rotZ - ROTATION_SPEED));

	// 回転している分を考慮して回転軸を合わせる
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(m_distance * cosf(rad),
		m_distance * sinf(rad),
		0
		)
		);
	// Ｚ軸回転処理
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f),
		DirectX::XMConvertToRadians(ROTATION_SPEED)
		);
	// 座標を原点に戻す
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(-m_distance * cosf(rad),
		-m_distance * sinf(rad),
		0
		)
		);
	// 元の座標位置に戻す
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_position = DirectX::SimpleMath::Vector3::Transform(m_position, matTransPos);

#pragma endregion



	// 回転角度を戻す
	if (m_moveState == eMOVE::MOVE_NONE){
		rotZ = 0.0f;
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/25
用途		：保持している頂点情報を移動に合わせて調整しなおす
第１引数	：座標を調整するための行列
返却値		：－

*************************************************************************/
void C_Entity_Cube::SetVertices(DirectX::SimpleMath::Matrix matrix){
	for(int i = 0; i < VERTEX_MAX; ++i){
		m_vertices[i] = DirectX::SimpleMath::Vector3::Transform(m_vertices[i], matrix);
	}
}