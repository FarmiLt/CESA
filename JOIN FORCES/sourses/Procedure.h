//////////////////////////////////////////////////////
//
//	�ڍ�		�F�E�B���h�E�v���V�[�W���N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/03
//
//////////////////////////////////////////////////////
#pragma once

class C_WindowProc{
public:
	void					SetPointer( HWND hWnd );			// �|�C���^�̐ݒ�
	static LRESULT CALLBACK CallProcedure( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );	// �E�B���h�E�v���V�[�W���̌Ăяo��
	virtual LRESULT			MainProcedure( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );	// �E�B���h�E�v���V�[�W���i�{�́j

private:
};