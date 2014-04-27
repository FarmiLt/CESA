//////////////////////////////////////////////////////
//
//	詳細		：カメラクラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2014/04/22
//
//////////////////////////////////////////////////////
#include "Camera.h"
#include "CameraState.h"


#pragma region	静的メンバ変数
const float C_BaseCamera::TURN_ANGLE = 0.2f;	// カメラの回転角度
#pragma endregion


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/21
用途		：メンバ変数の初期化
第１引数	：－
返却値		：－

*************************************************************************/
C_BaseCamera::C_BaseCamera()
: m_cameraType(true)				// TODO: カメラの状態を変えるならここ
, m_pOwner(nullptr)
, m_ownerBefPosition(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f))
, m_distance(200.0f)
, m_angleAxisX(45.0f)
, m_angleAxisY(90.0f)
{
	m_eyePosition =
		DirectX::SimpleMath::Vector3(m_distance * cosf(DirectX::XMConvertToRadians(m_angleAxisY)),
									 m_distance * sin(DirectX::XMConvertToRadians(m_angleAxisX)),
									 m_distance * sin(DirectX::XMConvertToRadians(m_angleAxisY)));
	m_targetPosition= DirectX::SimpleMath::Vector3::Vector3(0.0f, 0.0f, 0.0f);
	m_upVector		= DirectX::SimpleMath::Vector3::Vector3(0.0f, 1.0f, 0.0f);

	// ビュー行列を作成する
	CreateViewMatrix();

	// 射影行列を作成する
	CreateProjectionMatrix();

	// 状態管理クラスを生成
	m_pStateMachine = new C_StateMachine<C_BaseCamera>(this);
	if (m_cameraType){
		m_pStateMachine->SetCurrentState(C_Camera_Following::GetInstance());
	}
	else{
		m_pStateMachine->SetCurrentState(C_Camera_Fixed::GetInstance());
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：メンバ変数の解放
第１引数	：－
返却値		：－

*************************************************************************/
C_BaseCamera::~C_BaseCamera(){
	// 状態管理クラスの解放
	Macro::SAFE_DELETE(m_pStateMachine);
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：状態に沿った更新処理を行う
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::Update(){
	m_pStateMachine->Update();

	// ビュー行列と射影行列を作り直す
	CreateViewMatrix();
	CreateProjectionMatrix();

#ifdef _DEBUG
	// TODO: カメラの角度を表示する

	//std::cout << "CAMERA XZ : " << m_angleAxisY << std::endl;
	//std::cout << "CAMERA Y : " << m_angleAxisX << std::endl;
#endif
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/21
用途		：対象を中心に回るようにカメラの座標を調整する
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::AdjustCameraPosition(){
	// カメラ位置を再設定する
	m_eyePosition =
		DirectX::SimpleMath::Vector3(m_pOwner->GetPosition().x + m_distance * cosf(DirectX::XMConvertToRadians(m_angleAxisY)),
									 m_pOwner->GetPosition().y + m_distance * sin(DirectX::XMConvertToRadians(m_angleAxisX)),
									 m_pOwner->GetPosition().z + m_distance * sin(DirectX::XMConvertToRadians(m_angleAxisY)));

}



/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/21
用途		：ビュー行列を作成する
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::CreateViewMatrix(){
	// カメラの位置を調整する
	if ( m_pOwner )AdjustCameraPosition();

	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eyePosition, m_targetPosition, m_upVector);
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：射影行列を作成する
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::CreateProjectionMatrix(){
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(DirectX::XMConvertToRadians(45.0f), Macro::WINDOW_WIDTH / (float)Macro::WINDOW_HEIGHT, 0.1f, 1000.0f);
}



/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：カメラタイプを 定点←→追従 を切り換える
			　(切り換える前に追従対象を設定しておくこと)
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::ChangeCameraType(){
	m_cameraType = !m_cameraType;

	if (m_cameraType){
		// 追従カメラモードに切り換え
		m_pStateMachine->ChangeState( C_Camera_Following::GetInstance() );
	}
	else{
		// 固定カメラモードに切り換え
		m_pStateMachine->ChangeState(C_Camera_Fixed::GetInstance());
	}
}



/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/21
用途		：カメラの追従対象を設定する
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::SetOwner(C_Game3DEntity* pOwner){
	m_pOwner = pOwner;

	// 追従対象の現在の座標を取得しておく
	m_ownerBefPosition = m_pOwner->GetPosition();
}


#pragma region setアクセサ

/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/19
用途		：カメラ位置の指定
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::SetEyePosition(DirectX::SimpleMath::Vector3 position){
	m_eyePosition = position;

	// ビュー行列を作り直す
	//CreateViewMatrix();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/21
用途		：カメラをY軸に対して回転させる
第１引数	：回す方向(時計回り→true, 反時計回り→false)
第２引数	：回転角度(度数法)
返却値		：－

*************************************************************************/
void C_BaseCamera::TurnCamera_AxisY(bool plus){
	if ( plus ) m_angleAxisY += TURN_ANGLE;
	else		m_angleAxisY -= TURN_ANGLE;

	// ３６０度回転したら０度に戻す
	if (m_angleAxisY <= -360.0f || m_angleAxisY >= 360.0f){
		m_angleAxisY = 0.0f;
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/22
用途		：カメラをX軸に対して回転させる
第１引数	：回す方向(時計回り→true, 反時計回り→false)
第２引数	：回転角度(度数法)
返却値		：－

*************************************************************************/
void C_BaseCamera::TurnCamera_AxisX(bool plus){
	if (plus){
		// ８０度を超えないようにする
		if ( m_angleAxisX <= 80.0f ) m_angleAxisX += TURN_ANGLE;
	}
	else{
		// １０度を下回らないようにする
		if ( m_angleAxisX >= 10.0f ) m_angleAxisX -= TURN_ANGLE;
	}
}

/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/21
用途		：カメラのターゲットを操作対象に合わせる
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::TargetFollowing(){
	// 現在の追従対象の座標を保持する
	DirectX::SimpleMath::Vector3 target = m_pOwner->GetPosition();
	// １フレーム前と現在の追従対象の座標差を保持する
	DirectX::SimpleMath::Vector3 difPos;
	difPos = target - m_ownerBefPosition;

	// ターゲットの座標をプレイヤーにする
	m_targetPosition = target;

	// カメラの位置を対象が移動した分だけ移動する
	m_eyePosition = m_eyePosition + difPos;

	// 現在の座標をクラス内で保管する
	m_ownerBefPosition = target;
	
}

#pragma endregion


#pragma region getアクセサ

/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：ビュー行列を取得(3Dモデルの描画などに使用)
第１引数	：－
返却値		：ビュー行列

*************************************************************************/
DirectX::SimpleMath::Matrix C_BaseCamera::GetViewMatrix() const{
	return m_view;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：射影行列を取得(3Dモデルの描画などに使用)
第１引数	：－
返却値		：射影行列

*************************************************************************/
DirectX::SimpleMath::Matrix C_BaseCamera::GetProjectionMatrix() const{
	return m_projection;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/21
用途		：カメラの向いている方向に見合った操作をさせるために角度を取得する
第１引数	：－
返却値		：Y軸に対する角度

*************************************************************************/
float C_BaseCamera::GetCameraAngleAxisY() const{
	return m_angleAxisY;
}

#pragma endregion