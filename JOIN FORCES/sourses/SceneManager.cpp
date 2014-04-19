//////////////////////////////////////////////////////
//
//	�ڍ�		�F�V�[���Ǘ��N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/17
//
//////////////////////////////////////////////////////
#include "SceneManager.h"
#include "Logo.h"
#include "Title.h"
#include "Play.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/17
�p�r		�F��ԏ��߂̃V�[���������̃V�[���Ƃ��Ċ��蓖�Ă�
��P����	�F��ԏ��߂ɕ\������V�[�����
�ԋp�l		�F�|

*************************************************************************/
C_SceneManager::C_SceneManager( eSCENE firstScene )
	: m_pCurrentScene( nullptr ){
	m_nextScene = firstScene;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/17
�p�r		�F�V�[���f�[�^�̉��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_SceneManager::~C_SceneManager(){
	Macro::SAFE_DELETE( m_pCurrentScene );
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/19
�p�r		�F���̃V�[����񂪓������炻�̃V�[���ɐ؂�ւ���
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_SceneManager::Update(){
	// ���̃V�[����񂪓����Ă���΃V�[�������
	if ( m_nextScene != SCENE_NONE ){

		// ���݂̃V�[�����������
		Macro::SAFE_DELETE( m_pCurrentScene );

		// �V�[�����쐬����
		switch( m_nextScene ){
		case SCENE_LOGO:
			m_pCurrentScene = new C_SceneLogo( this );
			break;

		case SCENE_TITLE:
			m_pCurrentScene = new C_SceneTitle( this );
			break;

		case SCENE_PLAY:
			m_pCurrentScene = new C_ScenePlay( this );
			break;

		default:
			MessageBox( NULL, TEXT("�������̃V�[�����Ăяo����܂���"), TEXT("ERROR"), MB_OK );
			return false;
		}
		// �V�[���̏�����
		if ( !m_pCurrentScene->Initialize() ){
			return false;
		}

		// ���̃V�[��������ɂ���
		m_nextScene = SCENE_NONE;
	}

	// �V�[���̍X�V
	if ( !m_pCurrentScene->Update() ){
		return false;
	}
	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/19
�p�r		�F���݂̃V�[���̕`�揈�����s��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_SceneManager::Draw(){
	m_pCurrentScene->Draw();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/17
�p�r		�F���̃V�[�����Ƀf�[�^������
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_SceneManager::SwapScene( eSCENE nextScene ){
	m_nextScene = nextScene;
}