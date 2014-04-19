//////////////////////////////////////////////////////
//
//	�ڍ�		�F�E�B���h�E�N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/03
//
//////////////////////////////////////////////////////
#include "Window.h"


#pragma region �ÓI�����o�ϐ�
const TCHAR* C_Window::APP_NAME		= TEXT("����E�B���h�E�����");
const TCHAR* C_Window::WINDOW_TITLE	= TEXT("NOTITLE");
#pragma endregion


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/03
�p�r		�F�����o�ϐ��̏�����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_Window::C_Window() 
	: m_pProcedure( nullptr ), m_hWnd( nullptr ){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/03
�p�r		�F�v���V�[�W�����������
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_Window::~C_Window(){
	Macro::SAFE_DELETE( m_pProcedure );
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/03
�p�r		�F�E�B���h�E�̐���
��P����	�F�C���X�^���X�n���h��
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_Window::Initialize( HINSTANCE hInstance, int nCmdShow ){
	// ���d�N���h�~�̃~���[�e�b�N�X�n���h��
	HANDLE hMutex = nullptr;

	// �~���[�e�b�N�X�𐶐�
	hMutex = CreateMutex( NULL, TRUE, TEXT("DUAL LAUNCH") );

	// ���ɂ��̃E�B���h�E�����݂��Ă���Ȃ�G���[��
	if ( GetLastError() == ERROR_ALREADY_EXISTS ){
		MessageBox( NULL, TEXT("���ɋN������Ă��܂�"), TEXT("DUAL LAUNCH"), MB_OK );
		return false;
	}
	
	// �E�B���h�E�N���X�\���̂̃I�u�W�F�N�g���쐬
	WNDCLASSEX windowClass;		
	
	// �I�u�W�F�N�g�̏�����
	windowClass.cbSize			= sizeof( WNDCLASSEX );
	windowClass.style			= CS_VREDRAW | CS_HREDRAW;
	windowClass.lpfnWndProc		= C_WindowProc::CallProcedure;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= hInstance;
	windowClass.hIcon			= LoadIcon( hInstance, (LPCTSTR)NULL );
	windowClass.hCursor			= LoadCursor( NULL, IDC_ARROW );
	windowClass.hbrBackground	= (HBRUSH)( COLOR_WINDOW + 1 );
	windowClass.lpszMenuName	= NULL;
	windowClass.lpszClassName	= APP_NAME;
	windowClass.hIconSm			= LoadIcon( windowClass.hInstance, (LPCTSTR)NULL );
	// �E�B���h�E�N���X�̓o�^
	if ( !RegisterClassEx( &windowClass ) ){
		MessageBox( NULL, TEXT("�E�B���h�E�N���X�̓o�^�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// �E�B���h�E�v���V�[�W���̐���
	if ( m_pProcedure == nullptr ) m_pProcedure = new C_WindowProc;

	// �E�B���h�E�̐���
	if ( !InitWindow( hInstance, nCmdShow ) ){
		MessageBox( NULL, TEXT("Window.cpp(94)"), TEXT("ERROR"), MB_OK );
		return false;
	}
	//if ( !InitWindow( hInstance, nCmdShow ) ){
	//	MessageBox( NULL, TEXT("Window.cpp(94)"), TEXT("ERROR"), MB_OK );
	//	return false;
	//}
	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/03
�p�r		�F�E�B���h�E�n���h����n��
��P����	�F�|
�ԋp�l		�F�E�B���h�E�n���h��

*************************************************************************/
HWND C_Window::GetWindowHandle() const{
	return m_hWnd;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/13
�p�r		�F�E�B���h�E�̐���
��P����	�F�|
�ԋp�l		�F����I��[true], �ُ팟�m[false]

*************************************************************************/
bool C_Window::InitWindow( HINSTANCE hInst, int nCmdShow ){
	// �N���C�A���g�̈��640 * 480�ɕۂ�
    RECT rc = { 0, 0, Macro::WINDOW_WIDTH, Macro::WINDOW_HEIGHT };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

	// �E�C���h�E�̍쐬
    m_hWnd = CreateWindow(	APP_NAME,			// �A�v���P�[�V������
							WINDOW_TITLE,			// �E�B���h�E�^�C�g��
							WS_OVERLAPPEDWINDOW,	// �E�B���h�E�̃X�^�C��
							CW_USEDEFAULT,			// �E�B���h�E�̉������ʒu
							CW_USEDEFAULT,			// �E�B���h�E�̏c�����ʒu
							rc.right - rc.left,		// ��ʕ�
							rc.bottom - rc.top,		// ��ʍ���
							NULL,					// �e�E�B���h�E�̃n���h��
							NULL,					// �q�E�B���h�E�̃n���h��
							hInst,					// �E�B���h�E�̃C���X�^���X�n���h��
							(LPVOID)m_pProcedure );	// �v���V�[�W���̃|�C���^

	// �E�B���h�E�쐬�Ɏ��s������false��Ԃ�
    if( m_hWnd == nullptr ){
		MessageBox( NULL, TEXT("�E�B���h�E�̍쐬�Ɏ��s���܂���"), TEXT("ERROR"), MB_OK );
        return false;
	}

	// �E�B���h�E�̕\����Ԃ̐ݒ�
    ShowWindow( m_hWnd, nCmdShow );

	return true;
}