//////////////////////////////////////////////////////
//
//	詳細		：オブジェクトクラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/20
//
//////////////////////////////////////////////////////
#pragma once


class C_ObjectTask{
public:
	// コンストラクタ
	C_ObjectTask( float positionX, float positionY, float scalar = 0.0f, float angle = 0.0f, float priority = 0.5f );
	virtual ~C_ObjectTask();			// デストラクタ

	virtual bool Initialize()	= 0;	// 初期化処理
	virtual bool Update()		= 0;	// 更新処理
	virtual void Draw()			= 0;	// 描画処理

	void	Suicide();					// 自殺処理

	/*↓↓ 以下ゲッター ↓↓*/
	float	GetPositionX() const;		// X座標の取得
	float	GetPositionY() const;		// Y座標の取得
	float	GetImageWidth() const;		// 画像幅の取得
	float	GetImageHeight() const;		// 画像高さの取得
	bool	IsDead() const;				// 死んでいるかどうかを取得

protected:
	/*↓↓ 以下メンバ変数 ↓↓*/
	float	m_positionX;		// 座標X
	float	m_positionY;		// 座標Y
	float	m_speedX;			// 移動速度X
	float	m_speedY;			// 移動速度Y
	float	m_imageWidth;		// 画像幅
	float	m_imageHeight;		// 画像高さ
	float	m_priority;			// 優先度
	bool	m_deadFlag;			// 死亡フラグ

private:
};