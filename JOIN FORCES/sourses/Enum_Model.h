//////////////////////////////////////////////////////
//
//	詳細		：シーン用モデル列挙型ヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/05
//
//////////////////////////////////////////////////////
#pragma once


/*********************使うときに必ず読んでください************************
																		  
作成者		：岸　将史													 
最終更新日	：2013/12/17												
用法		：使いたい画像をそのシーンの画像列挙型に					  
			　「〇〇MODEL_◆◆」というように記述する					
			  ( ○にはシーンを、◆にはその画像が何かを明記する )		  
																		  
			  注：明記する際は必ず「〇〇MODEL_MAX」より上に書く事！		 
																		  
			  その後、													  
			  ここの列挙型に追加した順番で			←†††重要†††	 
			  ModelManager.cpp のリストに画像パスを記述する				 
																		  
*************************************************************************/


/*************************
/*† 共有モデル列挙型 †*/
/************************/
enum eCOMMONMODEL{
	// 記入例
//	COMMONMODEL_EXAMPLE,
	
	COMMONMODEL_BOX,
	COMMONMODEL_FLOOR,
	COMMONMODEL_CUBE,
	COMMONMODEL_SPHERE,

	// ここよりも↑に記述する事。MAXの下に書くとエライ事になります。
	COMMONMODEL_MAX,
};


/*******************************
/*† ロゴ画面用モデル列挙型 †*/
/******************************/
enum eLOGOMODEL{
	// 記入例
//	LOGOMODEL_EXAMPLE,
	LOGOMODEL_BACK,

	// ここよりも↑に記述する事。MAXの下に書くとエライ事になります。
	LOGOMODEL_MAX,
};


/**********************************/
/*† タイトル画面用モデル列挙型 †*/
/**********************************/
enum eTITLEMODEL{
	// 記入例
//	TITLEMODEL_EXAMPLE,
	TITLEMODEL_BACK,

	// ここよりも↑に記述する事。MAXの下に書くとエライ事になります。
	TITLEMODEL_MAX,
};


/********************************/
/*† プレイ画面用モデル列挙型 †*/
/********************************/
enum ePLAYMODEL{
	// 記入例
//	PLAYMODEL_EXAMPLE,
	PLAYMODEL_BACK,

	// ここよりも↑に記述する事。MAXの下に書くとエライ事になります。
	PLAYMODEL_MAX,
};