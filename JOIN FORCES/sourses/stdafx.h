///////////////////////////////////////////////
//
//	詳細		：プリコンパイル済みヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/03
//
///////////////////////////////////////////////
#pragma once


/*************************************************************************

ライブラリ追加

*************************************************************************/
#pragma comment( lib, "d3d11.lib" )
#pragma comment(lib,"DirectXTK.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"Xinput9_1_0.lib")		// XBOX360コントローラの処理に必要


/*************************************************************************

ヘッダーのインクルード

*************************************************************************/
#include <windows.h>
#include <list>			// 衝突判定クラスで使用
#include <map>			// エンティティ管理クラスで使用
#include <iostream>		// デバッグ用

// DirectXヘッダー
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <xact3.h>					// XACT3 に必要なヘッダー
#include <XInput.h>					// InputManager に必要なヘッダー


// DirectXTKヘッダー
#include <CommonStates.h>
#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Model.h>



// 自作ヘッダー
#include "Macro.h"