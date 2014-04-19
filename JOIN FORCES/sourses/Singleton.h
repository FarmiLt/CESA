//////////////////////////////////////////////////////
//
//	詳細		：シングルトンクラスヘッダー
//  			　シングルトンクラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2013/12/03
//
//////////////////////////////////////////////////////
#pragma once


template<class _T>
class C_Singleton{
public:
	static _T* GetInstance();								// 唯一のインスタンスの生成

protected:
	C_Singleton();											// コンストラクタ
	virtual ~C_Singleton();									// デストラクタ

private:
	C_Singleton( const C_Singleton& object );				// コピーコンストラクタ
	C_Singleton& operator = ( const C_Singleton& object );	// 代入演算子のオーバーロード
};


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：インスタンスを生成する
第１引数	：−
返却値		：唯一のインスタンスのアドレス

*************************************************************************/
template<class _T>
_T* C_Singleton<_T>::GetInstance(){ 
	static _T instance;
	return &instance; 
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：−
第１引数	：−
返却値		：−

*************************************************************************/
template<class _T>
C_Singleton<_T>::C_Singleton(){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：−
第１引数	：−
返却値		：−

*************************************************************************/
template<class _T>
C_Singleton<_T>::~C_Singleton(){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：−
第１引数	：このクラスインスタンス(参照)
返却値		：−

*************************************************************************/
template<class _T>
C_Singleton<_T>::C_Singleton( const C_Singleton<_T>& object ){
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/03
用途		：−
第１引数	：このクラスインスタンス(参照)
返却値		：このクラスインスタンス(参照)

*************************************************************************/
template<class _T>
C_Singleton<_T>& C_Singleton<_T>::operator = ( const C_Singleton<_T>& object ){
}