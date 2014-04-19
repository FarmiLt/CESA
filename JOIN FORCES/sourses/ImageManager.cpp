//////////////////////////////////////////////////////
//
//	詳細		：画像管理クラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2013/12/19
//
//////////////////////////////////////////////////////
#include "ImageManager.h"
#include "DirectX.h"		// DirectXデバイス及びデバイスコンテキストの取得に必要


#pragma region 画像リスト
/**********************
	共有画像リスト
**********************/
const LPCTSTR C_ImageManager::m_lpCommonImageList[COMMONIMAGE_MAX] = {
	TEXT("interface/image/common/sample.png"),
};


/*************************
	 ロゴ用画像リスト 
*************************/
const LPCTSTR C_ImageManager::m_lpLogoImageList[LOGOIMAGE_MAX] = {
	TEXT("interface/image/logo/sample.png"),
};


/***************************
	タイトル画像リスト
***************************/
const LPCTSTR C_ImageManager::m_lpTitleImageList[TITLEIMAGE_MAX] = {
	TEXT("interface/image/title/sample.png"),
};


/*************************
	プレイ画像リスト 
*************************/
const LPCTSTR C_ImageManager::m_lpPlayImageList[PLAYIMAGE_MAX] = {
	TEXT("interface/image/play/sample.png"),
};

#pragma endregion


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/05
用途		：メンバ変数の初期化及び共有画像データの読み込み
第１引数	：－
返却値		：－

*************************************************************************/
C_ImageManager::C_ImageManager(){
	// 共有画像フォルダの初期化
	for ( int i = 0; i < FOLDER_COMMONIMAGE_MAX; ++i ){
		m_pCommonImageFolder[i] = nullptr;
	}

	// シーン用フォルダの初期化
	for ( int i = 0; i < FOLDER_SCENEIMAGE_MAX; ++i ){
		m_pSceneImageFolder[i] = nullptr;
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/19
用途		：画像を解放する
第１引数	：－
返却値		：－

*************************************************************************/
C_ImageManager::~C_ImageManager(){
	// 共有画像フォルダの解放
	ReleaseCommonImage();

	// シーン用画像フォルダの解放
	ReleaseSceneImage();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/19
用途		：全シーンで使用する共有画像を読み込む
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_ImageManager::Initialize(){
	HRESULT isSucceeded = E_FAIL;

	// 枚数分のみ読み込み処理を行う
	for ( int i = 0; i < COMMONIMAGE_MAX; ++i ){
		if ( m_pCommonImageFolder == nullptr ){
			isSucceeded = DirectX::CreateWICTextureFromFile( C_DirectX::GetInstance()->GetD3DDevice(),
															C_DirectX::GetInstance()->GetDeviceContext(),
															m_lpCommonImageList[i],
															nullptr,
															&m_pCommonImageFolder[i] );
			// 一枚でも読み込みに失敗したら報告する
			if ( isSucceeded == E_FAIL ){
				MessageBox( NULL, TEXT("共有画像の読み込みに失敗しました"), TEXT("ERROR"), MB_OK );
				return false;
			}
		}
	}
	
	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/19
用途		：前のシーンの画像を破棄し、
			　現在のシーン用画像フォルダを一括で読み込む
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_ImageManager::LoadSceneImage(eSCENE nowScene){
	LPCTSTR sceneImages[FOLDER_SCENEIMAGE_MAX];	// シーンの画像リストを保持する
	int		imageMax;							// シーン別の画像枚数
	HRESULT isSucceeded = E_FAIL;				// 画像読み込み成功フラグ
	
	// 前のシーンの画像データを解放する
	ReleaseSceneImage();

	// 現在のシーン情報を基に画像リストを選択する
	switch( nowScene ){
	case SCENE_LOGO:
		imageMax = LOGOIMAGE_MAX;

		// 画像リストの配列数が保持上限を超えている場合エラーを返す
		if ( imageMax >= FOLDER_SCENEIMAGE_MAX ){
			MessageBox( NULL, TEXT("シーン用画像が画像保持上限を超えています。画像枚数を減らすか、保有上限を変更してください"), TEXT("ERROR"), MB_OK );
			return false;
		}

		// リストのデータをコピーする
		for ( int i = 0; i < imageMax; ++i ){
			sceneImages[i] = m_lpLogoImageList[i];
		}
		break;

	case SCENE_TITLE:
		imageMax = TITLEIMAGE_MAX;
		
		// 画像リストの配列数が保持上限を超えている場合エラーを返す
		if ( imageMax >= FOLDER_SCENEIMAGE_MAX ){
			MessageBox( NULL, TEXT("シーン用画像が画像保持上限を超えています。画像枚数を減らすか、保有上限を変更してください"), TEXT("ERROR"), MB_OK );
			return false;
		}

		// リストのデータをコピーする
		for ( int i = 0; i < imageMax; ++i ){
			sceneImages[i] = m_lpTitleImageList[i];
		}
		break;

	case SCENE_PLAY:
		imageMax = PLAYIMAGE_MAX;
		
		// 画像リストの配列数が保持上限を超えている場合エラーを返す
		if ( imageMax >= FOLDER_SCENEIMAGE_MAX ){
			MessageBox( NULL, TEXT("シーン用画像が画像保持上限を超えています。画像枚数を減らすか、保有上限を変更してください"), TEXT("ERROR"), MB_OK );
			return false;
		}

		// リストのデータをコピーする
		for ( int i = 0; i < imageMax; ++i ){
			sceneImages[i] = m_lpPlayImageList[i];
		}
		break;

	default:
		imageMax = 0;
		break;
	}

	// 画像を読み込む
	for ( int i = 0; i < imageMax; ++i ){
		isSucceeded = DirectX::CreateWICTextureFromFile(	C_DirectX::GetInstance()->GetD3DDevice(),
															C_DirectX::GetInstance()->GetDeviceContext(),
															sceneImages[i],
															nullptr,
															&m_pSceneImageFolder[i] );
		// 一枚でも読み込みに失敗したら報告する
		if ( isSucceeded == E_FAIL ){
			MessageBox( NULL, TEXT("シーン画像の読み込みに失敗しました"), TEXT("ERROR"), MB_OK );
			return false;
		}
	}

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/05
用途		：共有画像フォルダを一括解放する
第１引数	：－
返却値		：－

*************************************************************************/
void C_ImageManager::ReleaseCommonImage(){
	for ( int i = 0; i < FOLDER_COMMONIMAGE_MAX; ++i ){
		if ( m_pCommonImageFolder[i] != nullptr ) m_pCommonImageFolder[i]->Release();
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/05
用途		：シーン用画像フォルダを一括解放する
第１引数	：－
返却値		：－

*************************************************************************/
void C_ImageManager::ReleaseSceneImage(){
	for( int i = 0; i < FOLDER_SCENEIMAGE_MAX; ++i ){
		if ( m_pSceneImageFolder[i] != nullptr ) m_pSceneImageFolder[i]->Release();
	}
}


/*††††††††††††††††††††††††††† 以下ゲッター ††††††††††††††††††††††††††††*/


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/19
用途		：共有の画像データを取得する
第１引数	：呼び出す共有画像データの配列番号
返却値		：共有画像データのアドレス情報

*************************************************************************/
ID3D11ShaderResourceView* C_ImageManager::GetCommonImage( eCOMMONIMAGE imageNumber ){
	// 指定された配列番号が配列外の場合エラーを返す
	if ( imageNumber >= FOLDER_COMMONIMAGE_MAX ){
		MessageBox( NULL, TEXT("指定された番号は配列外です"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	// 指定された配列番号にモデルデータが無い場合エラーを返す
	if ( m_pCommonImageFolder[imageNumber] == nullptr ){
		MessageBox( NULL, TEXT("読み込まれていない共有画像が呼び出されようとしました"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}
	return m_pCommonImageFolder[imageNumber];
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/19
用途		：シーン別の画像データを取得する
第１引数	：呼び出すシーン画像データの配列番号
返却値		：シーン画像データのアドレス情報

*************************************************************************/
ID3D11ShaderResourceView* C_ImageManager::GetSceneImage( int imageNumber ){
	// 指定された配列番号が配列外の場合エラーを返す
	if ( imageNumber >= FOLDER_SCENEIMAGE_MAX ){
		MessageBox( NULL, TEXT("指定された番号は配列外です"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	// 指定された配列番号にモデルデータが無い場合エラーを返す
	if ( m_pSceneImageFolder[imageNumber] == nullptr ){
		MessageBox( NULL, TEXT("読み込まれていないシーン画像が呼び出されようとしました"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}
	return m_pSceneImageFolder[imageNumber];
}