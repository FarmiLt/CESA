//////////////////////////////////////////////////////
//
//	詳細		：オブジェクトの列挙型
//	補足		：列挙型にオブジェクトを追加する際は
//				　同時に以下のことをしてください
//				　
//				  C_EntityFactory::Create のswitch文に
//				  新しく追加したオブジェクトを追加する
//
//	作成者		：岸　将史
//	最終更新日	：2014/04/16
//
//////////////////////////////////////////////////////
#pragma once


enum class eENTITY{
	ENTITY_CUBE,	// 立方体
	ENTITY_SPHERE,	// 球体
};