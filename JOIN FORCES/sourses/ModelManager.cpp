//////////////////////////////////////////////////////
//
//	�ڍ�		�F���f���Ǘ��N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/19
//
//////////////////////////////////////////////////////
#include "ModelManager.h"
#include "DirectX.h"			// DXGI�t�@�N�g���̎擾�ɕK�v


#pragma region �ÓI�����o�ϐ�
/**********************
�@ ���L���f�����X�g
**********************/ 
const LPCTSTR C_ModelManager::m_lpCommonModels[] = {
	
	TEXT("interface/model/sample.cmo"),
	TEXT("interface/model/floor.cmo"),
	TEXT("interface/model/cube.cmo"),
	TEXT("interface/model/peach.cmo"),

};
#pragma endregion


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/18
�p�r		�F���f���f�[�^�̏�����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_ModelManager::C_ModelManager(){
	// �G�t�F�N�g�t�@�N�g���̍쐬
	m_pEffectFactory.reset( new DirectX::EffectFactory( C_DirectX::GetInstance()->GetD3DDevice() ) );

	for ( int i = 0; i < FOLDER_COMMONMODEL_MAX; ++i ){
		m_pCommonModelFolder[i].reset();
	}

	for ( int i = 0; i < FOLDER_SCENEMODEL_MAX; ++i ){
		m_pSceneModelFolder[i].reset();
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/18
�p�r		�F���L���f���f�[�^�ƃV�[���ʃ��f���f�[�^�̉��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_ModelManager::~C_ModelManager(){
	ReleaseCommonModel();
	ReleaseSceneModel();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/18
�p�r		�F���L���f���f�[�^�̓ǂݍ���
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_ModelManager::Initialize(){
	for ( int i = 0; i < COMMONMODEL_MAX; ++i ){
		m_pCommonModelFolder[i] = DirectX::Model::CreateFromCMO( C_DirectX::GetInstance()->GetD3DDevice(),
																 m_lpCommonModels[i],
																 *m_pEffectFactory);
	}

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/18
�p�r		�F�V�[�����f���f�[�^�̓ǂݍ���
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_ModelManager::LoadSceneModel( eSCENE nowScene ){
	TCHAR*	sceneModels[FOLDER_SCENEMODEL_MAX];	// �V�[���̃��f�����X�g��ێ�����
	int		modelMax;							// �V�[���ʂ̃��f����

	// �O�̃V�[���ł̃��f���f�[�^���������
	ReleaseSceneModel();

	// ���݂̃V�[���ɍ��킹�ēǂݍ��ރ��f�����X�g��I������
	switch( nowScene ){
	case SCENE_LOGO:
		modelMax = LOGOMODEL_MAX;
		break;

	case SCENE_TITLE:
		modelMax = TITLEMODEL_MAX;
		break;

	case SCENE_PLAY:
		modelMax = PLAYMODEL_MAX;
		break;

	default:
		modelMax = 0;
		break;

	}

	// ���f�����X�g����Ƀ��f�����쐬����
	for ( int i = 0; i < modelMax; ++i ){
		
	}

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/18
�p�r		�F�ǂ̃V�[���ł����L���f���f�[�^���������
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_ModelManager::ReleaseCommonModel(){
	for( int i = 0; i < COMMONMODEL_MAX; ++i ){
		m_pCommonModelFolder[i].reset();
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/18
�p�r		�F�V�[���ʃ��f���f�[�^�������Ă���ꍇ�������
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_ModelManager::ReleaseSceneModel(){
	for ( int i = 0; i < FOLDER_SCENEMODEL_MAX; ++i ){
		m_pSceneModelFolder[i].reset();
	}
}


/*������������������������������������������������������ �ȉ��Q�b�^�[ ��������������������������������������������������������*/


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/19
�p�r		�F���L�̃��f���f�[�^���擾����
��P����	�F�Ăяo�����L���f���f�[�^�̔z��ԍ�
�ԋp�l		�F���L���f���f�[�^�̃A�h���X���

*************************************************************************/
DirectX::Model* C_ModelManager::GetCommonModel( eCOMMONMODEL modelNumber ){
	// �w�肳�ꂽ�z��ԍ����z��O�̏ꍇ�G���[��Ԃ�
	if ( modelNumber >= FOLDER_COMMONMODEL_MAX ){
		MessageBox( NULL, TEXT("�w�肳�ꂽ�ԍ��͔z��O�ł�"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	// �w�肳�ꂽ�z��ԍ��Ƀ��f���f�[�^�������ꍇ�G���[��Ԃ�
	if ( m_pCommonModelFolder[modelNumber] == nullptr ){
		MessageBox( NULL, TEXT("�쐬����Ă��Ȃ����L���f�����Ăяo����悤�Ƃ��܂���"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	return m_pCommonModelFolder[modelNumber].get();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/19
�p�r		�F�V�[���ʂ̃��f���f�[�^���擾����
��P����	�F�Ăяo���V�[���ʃ��f���f�[�^�̔z��ԍ�
�ԋp�l		�F�V�[���ʃ��f���f�[�^�̃A�h���X���

*************************************************************************/
DirectX::Model* C_ModelManager::GetSceneModel( int modelNumber ){
	// �w�肳�ꂽ�z��ԍ����z��O�̏ꍇ�G���[��Ԃ�
	if ( modelNumber >= FOLDER_SCENEMODEL_MAX ){
		MessageBox( NULL, TEXT("�w�肳�ꂽ�ԍ��͔z��O�ł�"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	// �w�肳�ꂽ�z��ԍ��Ƀ��f���f�[�^�������ꍇ�G���[��Ԃ�
	if ( m_pSceneModelFolder[modelNumber] == nullptr ){
		MessageBox( NULL, TEXT("�쐬����Ă��Ȃ��V�[�����f�����Ăяo����悤�Ƃ��܂���"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	return m_pSceneModelFolder[modelNumber].get();
}