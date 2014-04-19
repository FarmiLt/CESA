//////////////////////////////////////////////////////
//
//	�ڍ�		�F�摜�Ǘ��N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/19
//
//////////////////////////////////////////////////////
#include "ImageManager.h"
#include "DirectX.h"		// DirectX�f�o�C�X�y�уf�o�C�X�R���e�L�X�g�̎擾�ɕK�v


#pragma region �摜���X�g
/**********************
	���L�摜���X�g
**********************/
const LPCTSTR C_ImageManager::m_lpCommonImageList[COMMONIMAGE_MAX] = {
	TEXT("interface/image/common/sample.png"),
};


/*************************
	 ���S�p�摜���X�g 
*************************/
const LPCTSTR C_ImageManager::m_lpLogoImageList[LOGOIMAGE_MAX] = {
	TEXT("interface/image/logo/sample.png"),
};


/***************************
	�^�C�g���摜���X�g
***************************/
const LPCTSTR C_ImageManager::m_lpTitleImageList[TITLEIMAGE_MAX] = {
	TEXT("interface/image/title/sample.png"),
};


/*************************
	�v���C�摜���X�g 
*************************/
const LPCTSTR C_ImageManager::m_lpPlayImageList[PLAYIMAGE_MAX] = {
	TEXT("interface/image/play/sample.png"),
};

#pragma endregion


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/05
�p�r		�F�����o�ϐ��̏������y�ы��L�摜�f�[�^�̓ǂݍ���
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_ImageManager::C_ImageManager(){
	// ���L�摜�t�H���_�̏�����
	for ( int i = 0; i < FOLDER_COMMONIMAGE_MAX; ++i ){
		m_pCommonImageFolder[i] = nullptr;
	}

	// �V�[���p�t�H���_�̏�����
	for ( int i = 0; i < FOLDER_SCENEIMAGE_MAX; ++i ){
		m_pSceneImageFolder[i] = nullptr;
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/19
�p�r		�F�摜���������
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_ImageManager::~C_ImageManager(){
	// ���L�摜�t�H���_�̉��
	ReleaseCommonImage();

	// �V�[���p�摜�t�H���_�̉��
	ReleaseSceneImage();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/19
�p�r		�F�S�V�[���Ŏg�p���鋤�L�摜��ǂݍ���
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_ImageManager::Initialize(){
	HRESULT isSucceeded = E_FAIL;

	// �������̂ݓǂݍ��ݏ������s��
	for ( int i = 0; i < COMMONIMAGE_MAX; ++i ){
		if ( m_pCommonImageFolder == nullptr ){
			isSucceeded = DirectX::CreateWICTextureFromFile( C_DirectX::GetInstance()->GetD3DDevice(),
															C_DirectX::GetInstance()->GetDeviceContext(),
															m_lpCommonImageList[i],
															nullptr,
															&m_pCommonImageFolder[i] );
			// �ꖇ�ł��ǂݍ��݂Ɏ��s������񍐂���
			if ( isSucceeded == E_FAIL ){
				MessageBox( NULL, TEXT("���L�摜�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("ERROR"), MB_OK );
				return false;
			}
		}
	}
	
	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/19
�p�r		�F�O�̃V�[���̉摜��j�����A
			�@���݂̃V�[���p�摜�t�H���_���ꊇ�œǂݍ���
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_ImageManager::LoadSceneImage(eSCENE nowScene){
	LPCTSTR sceneImages[FOLDER_SCENEIMAGE_MAX];	// �V�[���̉摜���X�g��ێ�����
	int		imageMax;							// �V�[���ʂ̉摜����
	HRESULT isSucceeded = E_FAIL;				// �摜�ǂݍ��ݐ����t���O
	
	// �O�̃V�[���̉摜�f�[�^���������
	ReleaseSceneImage();

	// ���݂̃V�[��������ɉ摜���X�g��I������
	switch( nowScene ){
	case SCENE_LOGO:
		imageMax = LOGOIMAGE_MAX;

		// �摜���X�g�̔z�񐔂��ێ�����𒴂��Ă���ꍇ�G���[��Ԃ�
		if ( imageMax >= FOLDER_SCENEIMAGE_MAX ){
			MessageBox( NULL, TEXT("�V�[���p�摜���摜�ێ�����𒴂��Ă��܂��B�摜���������炷���A�ۗL�����ύX���Ă�������"), TEXT("ERROR"), MB_OK );
			return false;
		}

		// ���X�g�̃f�[�^���R�s�[����
		for ( int i = 0; i < imageMax; ++i ){
			sceneImages[i] = m_lpLogoImageList[i];
		}
		break;

	case SCENE_TITLE:
		imageMax = TITLEIMAGE_MAX;
		
		// �摜���X�g�̔z�񐔂��ێ�����𒴂��Ă���ꍇ�G���[��Ԃ�
		if ( imageMax >= FOLDER_SCENEIMAGE_MAX ){
			MessageBox( NULL, TEXT("�V�[���p�摜���摜�ێ�����𒴂��Ă��܂��B�摜���������炷���A�ۗL�����ύX���Ă�������"), TEXT("ERROR"), MB_OK );
			return false;
		}

		// ���X�g�̃f�[�^���R�s�[����
		for ( int i = 0; i < imageMax; ++i ){
			sceneImages[i] = m_lpTitleImageList[i];
		}
		break;

	case SCENE_PLAY:
		imageMax = PLAYIMAGE_MAX;
		
		// �摜���X�g�̔z�񐔂��ێ�����𒴂��Ă���ꍇ�G���[��Ԃ�
		if ( imageMax >= FOLDER_SCENEIMAGE_MAX ){
			MessageBox( NULL, TEXT("�V�[���p�摜���摜�ێ�����𒴂��Ă��܂��B�摜���������炷���A�ۗL�����ύX���Ă�������"), TEXT("ERROR"), MB_OK );
			return false;
		}

		// ���X�g�̃f�[�^���R�s�[����
		for ( int i = 0; i < imageMax; ++i ){
			sceneImages[i] = m_lpPlayImageList[i];
		}
		break;

	default:
		imageMax = 0;
		break;
	}

	// �摜��ǂݍ���
	for ( int i = 0; i < imageMax; ++i ){
		isSucceeded = DirectX::CreateWICTextureFromFile(	C_DirectX::GetInstance()->GetD3DDevice(),
															C_DirectX::GetInstance()->GetDeviceContext(),
															sceneImages[i],
															nullptr,
															&m_pSceneImageFolder[i] );
		// �ꖇ�ł��ǂݍ��݂Ɏ��s������񍐂���
		if ( isSucceeded == E_FAIL ){
			MessageBox( NULL, TEXT("�V�[���摜�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("ERROR"), MB_OK );
			return false;
		}
	}

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/05
�p�r		�F���L�摜�t�H���_���ꊇ�������
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_ImageManager::ReleaseCommonImage(){
	for ( int i = 0; i < FOLDER_COMMONIMAGE_MAX; ++i ){
		if ( m_pCommonImageFolder[i] != nullptr ) m_pCommonImageFolder[i]->Release();
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/05
�p�r		�F�V�[���p�摜�t�H���_���ꊇ�������
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_ImageManager::ReleaseSceneImage(){
	for( int i = 0; i < FOLDER_SCENEIMAGE_MAX; ++i ){
		if ( m_pSceneImageFolder[i] != nullptr ) m_pSceneImageFolder[i]->Release();
	}
}


/*������������������������������������������������������ �ȉ��Q�b�^�[ ��������������������������������������������������������*/


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/19
�p�r		�F���L�̉摜�f�[�^���擾����
��P����	�F�Ăяo�����L�摜�f�[�^�̔z��ԍ�
�ԋp�l		�F���L�摜�f�[�^�̃A�h���X���

*************************************************************************/
ID3D11ShaderResourceView* C_ImageManager::GetCommonImage( eCOMMONIMAGE imageNumber ){
	// �w�肳�ꂽ�z��ԍ����z��O�̏ꍇ�G���[��Ԃ�
	if ( imageNumber >= FOLDER_COMMONIMAGE_MAX ){
		MessageBox( NULL, TEXT("�w�肳�ꂽ�ԍ��͔z��O�ł�"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	// �w�肳�ꂽ�z��ԍ��Ƀ��f���f�[�^�������ꍇ�G���[��Ԃ�
	if ( m_pCommonImageFolder[imageNumber] == nullptr ){
		MessageBox( NULL, TEXT("�ǂݍ��܂�Ă��Ȃ����L�摜���Ăяo����悤�Ƃ��܂���"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}
	return m_pCommonImageFolder[imageNumber];
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/19
�p�r		�F�V�[���ʂ̉摜�f�[�^���擾����
��P����	�F�Ăяo���V�[���摜�f�[�^�̔z��ԍ�
�ԋp�l		�F�V�[���摜�f�[�^�̃A�h���X���

*************************************************************************/
ID3D11ShaderResourceView* C_ImageManager::GetSceneImage( int imageNumber ){
	// �w�肳�ꂽ�z��ԍ����z��O�̏ꍇ�G���[��Ԃ�
	if ( imageNumber >= FOLDER_SCENEIMAGE_MAX ){
		MessageBox( NULL, TEXT("�w�肳�ꂽ�ԍ��͔z��O�ł�"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}

	// �w�肳�ꂽ�z��ԍ��Ƀ��f���f�[�^�������ꍇ�G���[��Ԃ�
	if ( m_pSceneImageFolder[imageNumber] == nullptr ){
		MessageBox( NULL, TEXT("�ǂݍ��܂�Ă��Ȃ��V�[���摜���Ăяo����悤�Ƃ��܂���"), TEXT("ERROR"), MB_OK );
		return nullptr;
	}
	return m_pSceneImageFolder[imageNumber];
}