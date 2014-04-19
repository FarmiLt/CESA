//////////////////////////////////////////////////////
//
//	詳細		：画像統括管理クラスヘッダー(singleton)
//	作成者		：岸　将史
//	最終更新日	：2013/12/05
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "Enum_Image.h"		// シーン別画像列挙型
#include "Enum_Scene.h"		// シーン列挙型


class C_ImageManager : public C_Singleton<C_ImageManager>{
public:
	bool Initialize();						// 初期化処理
	bool LoadSceneImage(eSCENE nowScene);					// 各シーンで使う画像を読み込む

	ID3D11ShaderResourceView* GetCommonImage( eCOMMONIMAGE imageNumber );	// 共有画像の取得
	ID3D11ShaderResourceView* GetSceneImage( int imageNumber );				// シーン別画像の取得

private:
	friend C_Singleton<C_ImageManager>;		// フレンドに登録
	C_ImageManager();						// コンストラクタ
	~C_ImageManager();						// デストラクタ
	void ReleaseCommonImage();				// 共有する画像の解放
	void ReleaseSceneImage();				// シーン別画像の解放

	/*↓↓ 以下メンバ変数 ↓↓*/
	static const int			FOLDER_COMMONIMAGE_MAX	= 16;					// 全シーン共有の画像の保有上限
	static const int			FOLDER_SCENEIMAGE_MAX	= 256;					// 各シーンで使う画像の保有上限
	ID3D11ShaderResourceView*	m_pCommonImageFolder[FOLDER_COMMONIMAGE_MAX];	// 共有画像フォルダ
	ID3D11ShaderResourceView*	m_pSceneImageFolder[FOLDER_SCENEIMAGE_MAX];		// シーン毎で使う画像フォルダ
	
	/*† 画像リスト †*/
	static const LPCTSTR		m_lpCommonImageList[COMMONIMAGE_MAX];	// 共有する画像のリスト
	static const LPCTSTR		m_lpLogoImageList[LOGOIMAGE_MAX];		// ロゴ画面		で用いる画像のリスト
	static const LPCTSTR		m_lpTitleImageList[TITLEIMAGE_MAX];		// タイトル画面	で用いる画像のリスト
	static const LPCTSTR		m_lpPlayImageList[PLAYIMAGE_MAX];		// プレイ画面		で用いる画像のリスト

	
};