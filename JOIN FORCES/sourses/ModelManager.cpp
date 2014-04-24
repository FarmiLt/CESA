//////////////////////////////////////////////////////
//
//	詳細		：モデル管理クラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2013/12/19
//
//////////////////////////////////////////////////////
#include "ModelManager.h"
#include "DirectX.h"			// DXGIファクトリの取得に必要


#pragma region 静的メンバ変数
/**********************
　 共有モデルリスト
**********************/ 
const LPCTSTR C_ModelManager::m_lpCommonModels[] = {
	
	TEXT("interface/model/sample.cmo"),
	TEXT("interface/model/floor.cmo"),
	TEXT("interface/model/cube.cmo"),
	TEXT("interface/model/peach.cmo"),

};
#pragma endregion


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/18
用途		：モデルデータの初期化
第１引数	：－
返却値		：－

*************************************************************************/
C_ModelManager::C_ModelManager(){
	// エフェクトファクトリの作成
	m_pEffectFactory.reset( new DirectX::EffectFactory( C_DirectX::GetInstance()->GetD3DDevice() ) );

	for ( int i = 0; i < FOLDER_COMMONMODEL_MAX; ++i ){
		m_pCommonModelFolder[i].reset();
	}

	for ( int i = 0; i < FOLDER_SCENEMODEL_MAX; ++i ){
		m_pSceneModelFolder[i].reset();
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/18
用途		：共有モデルデータとシーン別モデルデータの解放
第１引数	：－
返却値		：－

*************************************************************************/
C_ModelManager::~C_ModelManager(){
	ReleaseCommonModel();
	ReleaseSceneModel();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/18
用途		：共有モデルデータの読み込み
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_ModelManager::Initialize(){
	for ( int i = 0; i < COMMONMODEL_MAX; ++i ){
		m_pCommonModelFolder[i] = DirectX::Model::CreateFromCMO( C_DirectX::GetInstance()->GetD3DDevice(),
																 m_lpCommonModels[i],
																 *m_pEffectFactory);
	}

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/18
用途		：シーンモデルデータの読み込み
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_ModelManager::LoadSceneModel( eSCENE nowScene ){
	TCHAR*	sceneModels[FOLDER_SCENEMODEL_MAX];	// シーンのモデルリストを保持する
	int		modelMax;							// シーン別のモデル数

	// 前のシーンでのモデルデータを解放する
	ReleaseSceneModel();

	// 現在のシーンに合わせて読み込むモデルリストを選択する
	switch( nowScene ){
	case SCENE_LOGO:
		modelMax = LOGOMODEL_MAX;
		break;

	case SCENE_TITLE:
		modelMax = TITLEMODEL_MAX;
		break;

	case SCENE_PLAY:
		modelMax = PLAYMODEL_MAX;
		break;

	default:
		modelMax = 0;
		break;

	}

	// モデルリストを基にモデルを作成する
	for ( int i = 0; i < modelMax; ++i ){
		
	}

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/18
用途		：どのシーンでも共有モデルデータを解放する
第１引数	：－
返却値		：－

*************************************************************************/
void C_ModelManager::ReleaseCommonModel(){
	for( int i = 0; i < COMMONMODEL_MAX; ++i ){
		m_pCommonModelFolder[i].reset();
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/18
用途		：シーン別モデルデータが入っている場合解放する
第１引数	：－
返却値		：－

*************************************************************************/
void C_ModelManager::ReleaseSceneModel(){
	for ( int i = 0; i < FOLDER_SCENEMODEL_MAX; ++i ){
		m_pSceneModelFolder[i].reset();
	}
}


/*††††††††††††††††††††††††††† 以下ゲッター ††††††††††††††††††††††††††††*/


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/19
用途		：共有のモデルデータを取得する
第１引数	：呼び出す共有モデルデータの配列番号
返却値		：共有モデルデータのアドレス情報

*************************************************************************/
DirectX::Model* C_ModelManager::GetCommonModel( eCOMMONMODEL modelNumber ){
	// 指定された配列番号が配列外の場合エラーを返す
	if ( modelNumber >= FOLDER_COMMONMODEL_MAX ){
		MessageBox( NULL, TEXT("指定された番号は配列外です"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	// 指定された配列番号にモデルデータが無い場合エラーを返す
	if ( m_pCommonModelFolder[modelNumber] == nullptr ){
		MessageBox( NULL, TEXT("作成されていない共有モデルが呼び出されようとしました"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	return m_pCommonModelFolder[modelNumber].get();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/19
用途		：シーン別のモデルデータを取得する
第１引数	：呼び出すシーン別モデルデータの配列番号
返却値		：シーン別モデルデータのアドレス情報

*************************************************************************/
DirectX::Model* C_ModelManager::GetSceneModel( int modelNumber ){
	// 指定された配列番号が配列外の場合エラーを返す
	if ( modelNumber >= FOLDER_SCENEMODEL_MAX ){
		MessageBox( NULL, TEXT("指定された番号は配列外です"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	// 指定された配列番号にモデルデータが無い場合エラーを返す
	if ( m_pSceneModelFolder[modelNumber] == nullptr ){
		MessageBox( NULL, TEXT("作成されていないシーンモデルが呼び出されようとしました"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	return m_pSceneModelFolder[modelNumber].get();
}