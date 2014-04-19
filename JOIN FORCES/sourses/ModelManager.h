//////////////////////////////////////////////////////
//
//	�ڍ�		�F���f���Ǘ��N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "Enum_Model.h"		// �V�[���ʃ��f���񋓌^
#include "Enum_Scene.h"		// �V�[���񋓌^


class C_ModelManager : public C_Singleton<C_ModelManager>{
public:
	bool			Initialize();								// ����������
	bool			LoadSceneModel(eSCENE nowScene);			// ���f���̓ǂݍ���
	DirectX::Model*	GetCommonModel(eCOMMONMODEL modelNumber);	// ���L���f���̎擾
	DirectX::Model*	GetSceneModel( int modelnumber );			// �V�[���ʃ��f���̎擾

private:
	friend C_Singleton<C_ModelManager>;							// �t�����h�o�^
	C_ModelManager();											// �R���X�g���N�^
	~C_ModelManager();											// �f�X�g���N�^
	void ReleaseCommonModel();									// ���L���f���f�[�^�̉��
	void ReleaseSceneModel();									// ���f���f�[�^�̉��


	/*���� �ȉ������o�ϐ� ����*/
	std::unique_ptr<DirectX::EffectFactory> m_pEffectFactory;			// �G�t�F�N�g�t�@�N�g��

	static const int	FOLDER_COMMONMODEL_MAX = 128;					// �e�V�[�����L�̃��f���f�[�^�ő�ێ���
	static const int	FOLDER_SCENEMODEL_MAX = 128;					// �V�[���ʃ��f���f�[�^�ő�ۑ���
	
	std::unique_ptr<DirectX::Model>		m_pCommonModelFolder[FOLDER_COMMONMODEL_MAX];	// ���L���f���f�[�^
	std::unique_ptr<DirectX::Model>		m_pSceneModelFolder[FOLDER_SCENEMODEL_MAX];		// �V�[���ʃ��f���f�[�^

	// ���f���𗘗p����ۂɃR�����g�������Ă�������
	/*�� ���f�����X�g ��*/
	static const LPCTSTR m_lpCommonModels[COMMONMODEL_MAX];	// ���L�g�p���f�����X�g
	//static const LPCTSTR m_lpLogoModels[LOGOMODEL_MAX];		// ���S�V�[���p���f�����X�g
	//static const LPCTSTR m_lpTitleModels[TITLEMODEL_MAX];		// �^�C�g���V�[���p���f�����X�g
	//static const LPCTSTR m_lpPlayModels[PLAYMODEL_MAX];		// �v���C�V�[���p���f�����X�g
};