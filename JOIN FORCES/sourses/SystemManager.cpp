//////////////////////////////////////////////////////
//
//	�ڍ�		�F�V�X�e���Ǘ��N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/18
//
//////////////////////////////////////////////////////
#include "SystemManager.h"
#include "Window.h"
#include "DirectX.h"			// DirectX�̋@�\���g�p����̂ɕK�v
#include "KeyManager.h"			// �L�[�{�[�h����
#include "ImageManager.h"		// �摜�𗘗p����̂ɕK�v
#include "ModelManager.h"		// ���f���𗘗p����̂ɕK�v
//#include "AudioManager.h"		// �T�E���h���g�p����̂ɕK�v
//#include "FpsTimer.h"			// �t���[�����[�g�Ǘ�
#include "EffectManager.h"
#include "EntityManager.h"
#include "Camera.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/19
�p�r		�F�����o�ϐ��̏�����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_SystemManager::C_SystemManager( HINSTANCE hInst, int nCmd )
	: m_pSceneManager( nullptr )
	, m_hInstance( hInst )
	, m_nCmdShow( nCmd ){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/03
�p�r		�F�I�������̌Ăяo��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_SystemManager::~C_SystemManager(){
	Finalize();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/12
�p�r		�F�E�B���h�E�̐���, DirectX�̐���, �摜�Ǘ��N���X�̏�����
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_SystemManager::Initialize(){
	// �E�B���h�E���쐬����
	if ( !C_Window::GetInstance()->Initialize( m_hInstance, m_nCmdShow ) ){
		return false;
	}

	// DirectX�f�o�C�X���X���쐬����
	if ( !C_DirectX::GetInstance()->Initialize( C_Window::GetInstance()->GetWindowHandle() ) ){
		return false;
	}

	// �摜�N���X�̏�����
	if ( !C_ImageManager::GetInstance()->Initialize() ){
		return false;
	}

	// ���f���N���X�̏�����
	if (!C_ModelManager::GetInstance()->Initialize()){
		return false;
	}

	// �V�[���}�l�[�W���̍쐬
	m_pSceneManager = new C_SceneManager( SCENE_PLAY );

	// �T�E���h�̍쐬
	//if ( !C_AudioManager::GetInstance()->Initialize() ){
	//	return false;
	//}
	//C_AudioManager::GetInstance()->Play();

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/18
�p�r		�F�Q�[���V�[���̍X�V�A�`��
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
int C_SystemManager::GameRun(){
	// ���b�Z�[�W�̏�����
	MSG msg = {0};

	// ���C�����[�v
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			// �L�[�����̍X�V
			C_KeyManager::GetInstance()->Update();

			// �Q�[���V�[���̍X�V
			if ( !m_pSceneManager->Update() ) break;

			// �J�����̍X�V
			C_BaseCamera::GetInstance()->Update();

			// �G���e�B�e�B�̍X�V
			C_EntityManager::GetInstance()->Update();

			// �G�t�F�N�g�̍X�V
			C_EffectManager::GetInstance()->Update();

			// DirectX�f�o�C�X���ŉ�ʂ̃N���A��X���b�v�������s��
			if ( !C_DirectX::GetInstance()->Update() ) break;

			// ���Ԃ𒲐�����
//			fps.Wait();

			//if ( !fps.CheckDrawSkip() ){
			
			// �Q�[���V�[���̕`��
			m_pSceneManager->Draw();

			// �G���e�B�e�B�̍X�V
			C_EntityManager::GetInstance()->Render();

			// �G�t�F�N�g�̕`��
			C_EffectManager::GetInstance()->Draw();
			
			//}

#ifdef _DEBUG
	//::system("cls");
	//std::cout << "------------ DEBUG MODE ------------" << std::endl;
	//std::cout << "���ׂ����f�[�^�� [#ifdef _DEBUG] ����cout�ŏo���Ƃ���" << std::endl;

	
#endif
        }
    }
	return static_cast<int>( msg.wParam );
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/19
�p�r		�F�����o�ϐ��̉��
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
void C_SystemManager::Finalize(){
	Macro::SAFE_DELETE( m_pSceneManager );
}