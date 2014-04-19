//////////////////////////////////////////////////////
//
//	�ڍ�		�F���C���֐�
//	�⑫		�F�E�B���h�E�͕K���E�B���h�E�̕���{�^������
//				�@���邱�ƁB
//				�@�f�o�b�O�̒�~�A�R�}���h�v�����v�g���̂�
//				�@����ƃR�}���h�v�����v�g�����c��܂��B
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/17
//
//////////////////////////////////////////////////////
#include "SystemManager.h"

#pragma warning (disable : 4996)


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/17
�p�r		�F�V�X�e���}�l�[�W���̐����A�������A
��P����	�F�|
�ԋp�l		�F����I�� �� 0 �A�ُ�I�� �� -1

*************************************************************************/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPInst, LPSTR lpCmd, int nCmdShow ){
	
#ifdef _DEBUG
	// �������[���[�N���o�̂��߂̐ݒ�
	::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	// �R���\�[����ʂ̕\��
	//::AllocConsole();
	//freopen("CONIN$", "r", stdin);
	//freopen("CONOUT$", "w", stdout);

	//std::cout << "------------ DEBUG MODE ------------" << std::endl;
	//std::cout << "���ׂ����f�[�^�� [#ifdef _DEBUG] ����cout�ŏo���Ƃ���" << std::endl;
#endif

	// �V�X�e���}�l�[�W���̃I�u�W�F�N�g�𐶐�����
	C_SystemManager systemManager( hInstance, nCmdShow );

	// �V�X�e���}�l�[�W���̏�����
	if ( !systemManager.Initialize() ){
		// �G���[��
		MessageBox( NULL, TEXT("�V�X�e���}�l�[�W���̏������Ɏ��s���܂���"), TEXT("ERROR"), MB_OK );
		return -1;
	}

	// �V�X�e���}�l�[�W���̍X�V
	systemManager.GameRun();

#ifdef _DEBUG
	// �R���\�[����ʂ̍폜
	//::FreeConsole();
#endif

	return 0;
}