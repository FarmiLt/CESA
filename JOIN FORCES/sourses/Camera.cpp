//////////////////////////////////////////////////////
//
//	詳細		：カメラクラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2014/04/18
//
//////////////////////////////////////////////////////
#include "Camera.h"
#include "CameraState.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：メンバ変数の初期化
第１引数	：－
返却値		：－

*************************************************************************/
C_BaseCamera::C_BaseCamera()
: m_cameraType(true)				// TODO: カメラの状態を変えるならここ
, m_pOwner(nullptr)
, m_distance(DirectX::SimpleMath::Vector3(0.0f, 30.0f, 50.0f)){
	m_eyePosition	= m_distance;
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
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：ビュー行列を作成する
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::CreateViewMatrix(){
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
最終更新日	：2014/04/14
用途		：カメラの追従対象を設定する
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::SetOwner(C_Game3DEntity* pOwner){
	m_pOwner = pOwner;
}


#pragma region setアクセサ

/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：カメラ位置の指定
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::SetEyePosition(DirectX::SimpleMath::Vector3 position){
	m_eyePosition = position;

	// ビュー行列を作り直す
	CreateViewMatrix();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：カメラを回転させる
第１引数	：カメラを回転させる軸
第２引数	：回転角度(度数法)
返却値		：－

*************************************************************************/
void C_BaseCamera::TurnCamera(eTURNCAMERA axis, float angle){
	// カメラを原点に移動させる

	// カメラを回転させる
	switch (axis){
	case eTURNCAMERA::X :
		break;

	case eTURNCAMERA::Y :
		break;

	case eTURNCAMERA::Z :
		break;
	}

	// カメラを元の位置に戻す


	// ビュー行列を作り直す
	CreateViewMatrix();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/18
用途		：カメラのターゲットを操作対象に合わせる
第１引数	：－
返却値		：－

*************************************************************************/
void C_BaseCamera::TargetFollowing(){
	// ターゲットの座標をプレイヤーにする
	m_targetPosition = m_pOwner->GetPosition();

	// プレイヤーに対して動く
	m_eyePosition = m_pOwner->GetPosition() + m_distance;
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
DirectX::XMMATRIX C_BaseCamera::GetViewMatrix() const{
	return m_view;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/14
用途		：射影行列を取得(3Dモデルの描画などに使用)
第１引数	：－
返却値		：射影行列

*************************************************************************/
DirectX::XMMATRIX C_BaseCamera::GetProjectionMatrix() const{
	return m_projection;
}


#pragma endregion