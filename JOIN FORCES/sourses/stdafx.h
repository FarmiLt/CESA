///////////////////////////////////////////////
//
//	�ڍ�		�F�v���R���p�C���ς݃w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/03
//
///////////////////////////////////////////////
#pragma once


/*************************************************************************

���C�u�����ǉ�

*************************************************************************/
#pragma comment( lib, "d3d11.lib" )
#pragma comment(lib,"DirectXTK.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"Xinput9_1_0.lib")		// XBOX360�R���g���[���̏����ɕK�v


/*************************************************************************

�w�b�_�[�̃C���N���[�h

*************************************************************************/
#include <windows.h>
#include <list>			// �Փ˔���N���X�Ŏg�p
#include <map>			// �G���e�B�e�B�Ǘ��N���X�Ŏg�p
#include <iostream>		// �f�o�b�O�p

// DirectX�w�b�_�[
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <xact3.h>					// XACT3 �ɕK�v�ȃw�b�_�[
#include <XInput.h>					// InputManager �ɕK�v�ȃw�b�_�[


// DirectXTK�w�b�_�[
#include <CommonStates.h>
#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Model.h>



// ����w�b�_�[
#include "Macro.h"