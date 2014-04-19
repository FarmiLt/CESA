//////////////////////////////////////////////////////
//
//	詳細		：ベース例外処理クラス
//				　全ての例外処理の親クラス
//	作成者		：岸　将史
//	最終更新日	：2013/12/05
//
//////////////////////////////////////////////////////
#pragma once


class C_BaseException{
public:
	virtual unsigned GetErrorCode();		// エラーコードの取得

protected:
	C_BaseException( unsigned errorCode );	// コンストラクタ
	virtual ~C_BaseException();				// デストラクタ

private:
	int		m_errorCode;		// ♪エラーコード 
};