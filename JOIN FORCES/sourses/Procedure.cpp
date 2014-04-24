///////////////////////////////////////////////
//
//	�ڍ�		�FDirectX�N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/17
//
///////////////////////////////////////////////
#include "Procedure.h"
#include "Window.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/03
�p�r		�F���g�̃|�C���^���v���p�e�B���X�g�ɐݒ肷��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_WindowProc::SetPointer( HWND hWnd ){
	SetWindowLong( hWnd, GWL_USERDATA, (LONG)this );
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/03
�p�r		�F�E�B���h�E�v���V�[�W���ւ̒���
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
LRESULT CALLBACK C_WindowProc::CallProcedure( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ){
	// �v���p�e�B���X�g���玩�g�̃|�C���^���擾����
	C_WindowProc* thisptr = (C_WindowProc*)GetWindowLong( hWnd, GWL_USERDATA );

	// ���g�̃|�C���^���擾�o���Ȃ������ꍇ
	if( !thisptr ){

		// ���ꂪ�E�B���h�E����������鎞��������
		if( uMsg == WM_CREATE ){

			thisptr = (C_WindowProc*)( (LPCREATESTRUCT)lParam )->lpCreateParams;
		}

		// �������g�̃|�C���^���擾�o������v���p�e�B���X�g�ɃZ�b�g����
		if( thisptr ){
			thisptr->SetPointer( hWnd );
		}
	}
	
	if ( thisptr ){
		// �v���V�[�W���Ƀ��b�Z�[�W�𑗂�
		LRESULT lResult = thisptr->MainProcedure( hWnd, uMsg, wParam, lParam );
		return lResult;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/21
�p�r		�F�E�B���h�E�v���V�[�W��
��P����	�F�|
�ԋp�l		�F

*************************************************************************/
LRESULT C_WindowProc::MainProcedure( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ){
	// ���b�Z�[�W�ɉ��������������s����
	switch( uMsg ){
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE){
			if (MessageBox(NULL, TEXT("�I�����܂����H"), TEXT("�I���m�F"), MB_YESNO) == IDYES){
				SendMessage(C_Window::GetInstance()->GetWindowHandle(), WM_DESTROY, 0, 0);
				return 0;
			}
		}

	default:
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
}