//////////////////////////////////////////////////////
//
//	詳細		：サウンド管理クラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2013/12/16
//
//////////////////////////////////////////////////////
#include "AudioManager.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/16
用途		：メンバ変数の初期化
第１引数	：－
返却値		：－

*************************************************************************/
C_AudioManager::C_AudioManager()
	: m_pXACTEngine( nullptr )
	, m_pXACTWaveBank( nullptr )
	, m_pXACTSoundBank( nullptr )
	, m_pWBBuffer( nullptr )
	, m_pSBBuffer( nullptr ){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/16
用途		：メンバ変数の解放
第１引数	：－
返却値		：－

*************************************************************************/
C_AudioManager::~C_AudioManager(){
	// サウンドバンクの解放
	if ( m_pXACTSoundBank ){
		m_pXACTSoundBank->Destroy();
		m_pXACTSoundBank = nullptr;
	}
	Macro::SAFE_DELETE_ARRAY( m_pSBBuffer );

	// ウェーブバンクの解放
	if ( m_pXACTWaveBank ){
		m_pXACTWaveBank->Destroy();
		m_pXACTWaveBank = nullptr;
	}
	UnmapViewOfFile( m_pWBBuffer );

	// エンジンの解放
	if ( m_pXACTEngine ){
		m_pXACTEngine->ShutDown();
		m_pXACTEngine->Release();
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/16
用途		：エンジン、ウェーブバンク、サウンドバンクの初期化を行う
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_AudioManager::Initialize(){
	// エンジンの初期化(後述)
	if ( !InitEngine() ) return false;

	// ウェーブバンクの初期化(後述)
	if ( !InitWaveBank() ) return false;

	// サウンドバンクの初期化(後述)
	if ( !InitSoundBank() ) return false;

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/16
用途		：キューを基に音を再生する
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_AudioManager::Play(){
	XACTINDEX index = m_pXACTSoundBank->GetCueIndex("asayake");
	// キューの
	m_pXACTSoundBank->Play(	index,		// キューのインデックス
							0,			// 再生フラグ(ツール側で作ったフェード処理等を使用するかどうか)
							0,			// 再生開始位置
							NULL);		// キューのポインタ

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/16
用途		：エンジンを初期化し、xgsファイルを読み込む
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_AudioManager::InitEngine(){
	// COM を使用するためにCOMライブラリを初期化する
	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	// エンジンの初期化
	if ( FAILED( XACT3CreateEngine( NULL, &m_pXACTEngine ) ) ){
		// エラー報告
		MessageBox( NULL, TEXT("XACTエンジンの初期化に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	void*	pBuffer;
	DWORD	dwFileSize;				// xgsファイルサイズ
	bool	isSucceeded = false;	// 作成成功フラグ

	// ファイルの生成
	HANDLE hFile = CreateFile(	TEXT("interface/bgm.xgs"),						// ファイル名
								GENERIC_READ,									// ファイルへのアクセスタイプ
								FILE_SHARE_READ,								// ファイルの共有方法の指定
								NULL,											// SECURITY_ATTRIBUTES 構造体へのポインタ
								OPEN_EXISTING,									// ファイルの存在に対し如何動作させるか
								0,												// ファイルの属性やフラグを指定
								NULL );											// テンプレートファイルの指定
	if ( hFile == INVALID_HANDLE_VALUE ){
		// エラー報告
		MessageBox( NULL, TEXT("ファイルの生成に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// xgsファイルのサイズを取得する
	dwFileSize = GetFileSize( hFile, NULL );

	if ( dwFileSize != INVALID_FILE_SIZE ){
		pBuffer = CoTaskMemAlloc( dwFileSize );

		if ( pBuffer ){
			DWORD byteRead;

			// ファイルを読み込む
			if ( ReadFile( hFile, pBuffer, dwFileSize, &byteRead, NULL ) != NULL ){
				// 成功フラグを立てる
				isSucceeded = true;
			}
		}
	}
	// ファイルを閉じる
	CloseHandle( hFile );

	if ( !isSucceeded ){
		// エラー報告
		MessageBox( NULL, TEXT("xgsファイルの読み込みに失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}
	
	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/16
用途		：ウェーブバンクを初期化し、ウェーブバンクを作成する
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_AudioManager::InitWaveBank(){
	DWORD	dwFileSize = 0;			// xwbファイルサイズ
	HANDLE	hMapFile;				// マップファイルのハンドル
	bool	isSucceeded = false;	// 成功フラグ
	
	// xwbファイルの読み込み
	HANDLE hFile = CreateFile(	TEXT("interface/BGM_Title.xwb"),
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								0,
								NULL );
	if (  hFile == INVALID_HANDLE_VALUE ){
		// エラー報告
		MessageBox( NULL, TEXT("xwbファイルの読み込みに失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// ファイルサイズの取得
	dwFileSize = GetFileSize( hFile, NULL );
	if ( dwFileSize == INVALID_FILE_SIZE ){
		// エラー報告
		MessageBox( NULL, TEXT("xwbファイルサイズ取得に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// ファイルマップオブジェクトの生成
	hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
	// ファイルビューをマップ
	m_pWBBuffer = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
	
	// ウェーブバンクの作成
	if ( m_pWBBuffer ){
		if ( SUCCEEDED( m_pXACTEngine->CreateInMemoryWaveBank( m_pWBBuffer, dwFileSize, 0, 0, &m_pXACTWaveBank ) ) ){
			isSucceeded = true;
		}
	}

	// ファイルを閉じる
	CloseHandle( hMapFile );
	CloseHandle( hFile );

	if ( !isSucceeded ){
		// エラー報告
		MessageBox( NULL, TEXT("ウェーブバンクの生成に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/16
用途		：サウンドバンクを初期化し、サウンドバンクを作成する
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_AudioManager::InitSoundBank(){
	DWORD	dwFileSize;				// xsbファイルサイズ
	DWORD	dwByteRead;
	bool	isSucceeded = false;	// 成功フラグ

	// xsbファイルの読み込み
	HANDLE hFile = CreateFile(	TEXT("interface/BGM_Title.xsb"),
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								0, 
								NULL );
	if ( hFile == INVALID_HANDLE_VALUE ){
		// エラー報告
		MessageBox( NULL, TEXT("xsbファイルの読み込みに失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// ファイルサイズの取得
	dwFileSize = GetFileSize( hFile, NULL );
	if ( dwFileSize == INVALID_FILE_SIZE ){
		// エラー報告
		MessageBox( NULL, TEXT("xsbファイルサイズの取得に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	m_pSBBuffer = new BYTE[dwFileSize];
	if ( m_pSBBuffer == nullptr ){
		// エラー報告
		MessageBox( NULL, TEXT("バッファ領域の確保に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	dwByteRead = 0;
	ReadFile( hFile, m_pSBBuffer, dwFileSize, &dwByteRead, NULL );
	
	// サウンドバンクの生成
	if ( SUCCEEDED( m_pXACTEngine->CreateSoundBank( m_pSBBuffer, dwFileSize, 0, 0, &m_pXACTSoundBank ) ) ){
		isSucceeded = true;
	}

	if ( !isSucceeded ){
		// エラー報告
		MessageBox( NULL, TEXT("サウンドバンクの生成"), TEXT("ERROR"), MB_OK );
		return false;
	}

	return true;
}