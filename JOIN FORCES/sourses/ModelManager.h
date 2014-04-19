//////////////////////////////////////////////////////
//
//	詳細		：モデル管理クラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "Enum_Model.h"		// シーン別モデル列挙型
#include "Enum_Scene.h"		// シーン列挙型


class C_ModelManager : public C_Singleton<C_ModelManager>{
public:
	bool			Initialize();								// 初期化処理
	bool			LoadSceneModel(eSCENE nowScene);			// モデルの読み込み
	DirectX::Model*	GetCommonModel(eCOMMONMODEL modelNumber);	// 共有モデルの取得
	DirectX::Model*	GetSceneModel( int modelnumber );			// シーン別モデルの取得

private:
	friend C_Singleton<C_ModelManager>;							// フレンド登録
	C_ModelManager();											// コンストラクタ
	~C_ModelManager();											// デストラクタ
	void ReleaseCommonModel();									// 共有モデルデータの解放
	void ReleaseSceneModel();									// モデルデータの解放


	/*↓↓ 以下メンバ変数 ↓↓*/
	std::unique_ptr<DirectX::EffectFactory> m_pEffectFactory;			// エフェクトファクトリ

	static const int	FOLDER_COMMONMODEL_MAX = 128;					// 各シーン共有のモデルデータ最大保持数
	static const int	FOLDER_SCENEMODEL_MAX = 128;					// シーン別モデルデータ最大保存数
	
	std::unique_ptr<DirectX::Model>		m_pCommonModelFolder[FOLDER_COMMONMODEL_MAX];	// 共有モデルデータ
	std::unique_ptr<DirectX::Model>		m_pSceneModelFolder[FOLDER_SCENEMODEL_MAX];		// シーン別モデルデータ

	// モデルを利用する際にコメント解除してください
	/*† モデルリスト †*/
	static const LPCTSTR m_lpCommonModels[COMMONMODEL_MAX];	// 共有使用モデルリスト
	//static const LPCTSTR m_lpLogoModels[LOGOMODEL_MAX];		// ロゴシーン用モデルリスト
	//static const LPCTSTR m_lpTitleModels[TITLEMODEL_MAX];		// タイトルシーン用モデルリスト
	//static const LPCTSTR m_lpPlayModels[PLAYMODEL_MAX];		// プレイシーン用モデルリスト
};