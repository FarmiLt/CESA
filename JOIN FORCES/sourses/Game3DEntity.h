//////////////////////////////////////////////////////
//
//	詳細		：ゲームで利用する3D実体クラス
//	作成者		：岸　将史
//	最終更新日	：2014/04/16
//
//////////////////////////////////////////////////////
#pragma once
#include "BaseEntity.h"
#include "StateMachine.h"
#include "Enum_Entity.h"


class C_Game3DEntity : public C_BaseEntity{
public:
	C_Game3DEntity(int id, DirectX::SimpleMath::Vector3 position);	// コンストラクタ
	~C_Game3DEntity();												// デストラクタ

	virtual bool Update();			// 更新処理
	virtual void Render();			// 描画処理
	virtual void Control() = 0;		// 操作処理

	bool HandleMessage(const S_Message& message) override;			// メッセージ取得処理

	// setアクセサ
	void Kill();					// 実体を殺す処理
	void ChangeControl();			// 操作状態の切り換え
	void Crashed(bool isCrashed);	// 衝突フラグ切り換え

	// getアクセサ
	bool IsDead() const;								// 生存状況の確認
	bool IsControlling() const;							// 操作中かどうかの確認
	bool IsCrashing() const;							// 衝突中かどうかの確認
	eENTITY IsType() const;								// タイプの取得
	DirectX::SimpleMath::Vector3 GetPosition() const;	// 座標の取得
	float GetRadius() const;							// 半径取得

protected:
	// setアクセサ
	void SetPosition(DirectX::SimpleMath::Vector3 position);	// 座標の移動

	// メンバ変数
	DirectX::SimpleMath::Matrix		m_world;			// ワールド行列
	C_StateMachine<C_Game3DEntity>* m_pStateMachine;	// 状態管理クラス
	float							m_radius;			// 半径
	eENTITY							m_entityType;		// タイプ

private:
	// メンバ変数
	bool							m_deadFlag;			// 死亡フラグ(default : false)
	bool							m_controlling;		// 操作中フラグ(default: false)
	bool							m_crashing;			// 衝突中フラグ(衝突している限りフラグは立ちっぱなしになる)
	DirectX::SimpleMath::Vector3	m_position;			// 表示座標

};