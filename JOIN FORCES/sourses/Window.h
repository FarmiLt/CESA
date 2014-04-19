//////////////////////////////////////////////////////
//
//	�ڍ�		�F�E�B���h�E�N���X�w�b�_�[(singleton)
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/03
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "Procedure.h"


class C_Window : public C_Singleton<C_Window>{
public:
	bool Initialize( HINSTANCE hInst, int nCmdShow );	// ����������
	bool InitWindow( HINSTANCE hInst, int nCmdShow );	// �E�B���h�E�̍쐬

	/*�� �Q�b�^�[ ��*/
	HWND GetWindowHandle() const;		// �E�B���h�E�n���h��

private:
	friend C_Singleton<C_Window>;		// �t�����h�o�^
	C_Window();							// �R���X�g���N�^
	~C_Window();						// �f�X�g���N�^

	static const TCHAR* APP_NAME;		// ��A�v���P�[�V������
	static const TCHAR* WINDOW_TITLE;	// ��E�B���h�E�^�C�g��
	C_WindowProc*		m_pProcedure;	// ��E�B���h�E�v���V�[�W��
	HWND				m_hWnd;			// ��E�B���h�E�n���h��

};