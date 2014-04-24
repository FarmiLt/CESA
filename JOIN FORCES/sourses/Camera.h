//////////////////////////////////////////////////////
//
//	詳細		：カメラクラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2014/04/21
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "StateMachine.h"
#include "Game3DEntity.h"


class C_BaseCamera : public C_Singleton<C_BaseCamera>{
public:
	void Update();			// 更新処理

	// setアクセサ
	void SetEyePosition(DirectX::SimpleMath::Vector3 position);		// カメラ位置
	void ChangeCameraType();										// カメラタイプの切換
	void SetOwner(C_Game3DEntity* pOwner);							// カメラの追従対象の設定

	// ステートから呼び出すsetアクセサ
	void TargetFollowing();				// ターゲット座標の調整
	void CreateViewMatrix();			// ビュー行列の作成
	void CreateProjectionMatrix();		// 射影行列の作成
	void TurnCamera_AxisY(bool plus);	// Y軸に対するカメラの回転
	void TurnCamera_AxisX(bool plus);	// X軸に対するカメラの回転

	// getアクセサ
	DirectX::XMMATRIX GetViewMatrix() const;		// ビュー行列の取得
	DirectX::XMMATRIX GetProjectionMatrix() const;	// 射影行列の取得
	float			  GetCameraAngleAxisY() const;	// Y軸に対する角度を取得

private:
	// メソッド
	friend C_Singleton<C_BaseCamera>;		// フレンドに登録
	C_BaseCamera();							// コンストラクタ
	~C_BaseCamera();						// デストラクタ
	void AdjustCameraPosition();			// カメラ位置の調整
	
	/*↓↓ 以下メンバ変数 ↓↓*/
	static const float				TURN_ANGLE;			// カメラが１フレームで回転する角度
	C_StateMachine<C_BaseCamera>*	m_pStateMachine;	// 状態管理クラス
	C_Game3DEntity*					m_pOwner;			// 追従対象
	DirectX::SimpleMath::Vector3	m_eyePosition;		// カメラ位置
	DirectX::SimpleMath::Vector3	m_targetPosition;	// ターゲット座標
	DirectX::SimpleMath::Vector3	m_upVector;			// カメラ上部ベクトル
	DirectX::SimpleMath::Vector3	m_ownerBefPosition;	// 追従対象の１フレーム前座標
	DirectX::XMMATRIX				m_view;				// ビュー行列
	DirectX::XMMATRIX				m_projection;		// 射影行列
	bool							m_cameraType;		// カメラタイプ(default : false(定点カメラ))
	float							m_distance;			// カメラの距離
	float							m_angleAxisX;		// X軸に対する角度
	float							m_angleAxisY;		// Y軸に対する角度
};