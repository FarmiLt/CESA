//////////////////////////////////////////////////////
//
//	�ڍ�		�F�摜�����Ǘ��N���X�w�b�_�[(singleton)
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/05
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "Enum_Image.h"		// �V�[���ʉ摜�񋓌^
#include "Enum_Scene.h"		// �V�[���񋓌^


class C_ImageManager : public C_Singleton<C_ImageManager>{
public:
	bool Initialize();						// ����������
	bool LoadSceneImage(eSCENE nowScene);					// �e�V�[���Ŏg���摜��ǂݍ���

	ID3D11ShaderResourceView* GetCommonImage( eCOMMONIMAGE imageNumber );	// ���L�摜�̎擾
	ID3D11ShaderResourceView* GetSceneImage( int imageNumber );				// �V�[���ʉ摜�̎擾

private:
	friend C_Singleton<C_ImageManager>;		// �t�����h�ɓo�^
	C_ImageManager();						// �R���X�g���N�^
	~C_ImageManager();						// �f�X�g���N�^
	void ReleaseCommonImage();				// ���L����摜�̉��
	void ReleaseSceneImage();				// �V�[���ʉ摜�̉��

	/*���� �ȉ������o�ϐ� ����*/
	static const int			FOLDER_COMMONIMAGE_MAX	= 16;					// �S�V�[�����L�̉摜�ۗ̕L���
	static const int			FOLDER_SCENEIMAGE_MAX	= 256;					// �e�V�[���Ŏg���摜�ۗ̕L���
	ID3D11ShaderResourceView*	m_pCommonImageFolder[FOLDER_COMMONIMAGE_MAX];	// ���L�摜�t�H���_
	ID3D11ShaderResourceView*	m_pSceneImageFolder[FOLDER_SCENEIMAGE_MAX];		// �V�[�����Ŏg���摜�t�H���_
	
	/*�� �摜���X�g ��*/
	static const LPCTSTR		m_lpCommonImageList[COMMONIMAGE_MAX];	// ���L����摜�̃��X�g
	static const LPCTSTR		m_lpLogoImageList[LOGOIMAGE_MAX];		// ���S���		�ŗp����摜�̃��X�g
	static const LPCTSTR		m_lpTitleImageList[TITLEIMAGE_MAX];		// �^�C�g�����	�ŗp����摜�̃��X�g
	static const LPCTSTR		m_lpPlayImageList[PLAYIMAGE_MAX];		// �v���C���		�ŗp����摜�̃��X�g

	
};