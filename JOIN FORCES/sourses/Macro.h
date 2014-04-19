//////////////////////////////////////////////////////
//
//	�ڍ�		�F�}�N���Ǘ��w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/16
//
//////////////////////////////////////////////////////
#pragma once


// �}�N�����ƕ�����Ղ����邽�߂̖��O���
namespace Macro{
	static const int WINDOW_WIDTH	= 640;		// �E�B���h�E��
	static const int WINDOW_HEIGHT	= 480;		// �E�B���h�E����

	// �|�C���^�̈��S���
	template<class T>
	static const void SAFE_DELETE( T*& p ){ if ( p ) delete p; p = nullptr; }

	template<class T>
	static const void SAFE_DELETE_ARRAY( T*& p ){ if ( p ) delete[] p; p = nullptr; }
}