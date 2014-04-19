//////////////////////////////////////////////////////
//
//	�ڍ�		�F�V�X�e���Ǘ��N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/03
//
//////////////////////////////////////////////////////
#pragma once
#include "DirectX.h"
#include "SceneManager.h"		// �V�[�����쐬����̂ɕK�v
//#include "FpsTimer.h"

class C_SystemManager{
public:
	C_SystemManager(HINSTANCE hInst, int nCmd );	// �R���X�g���N�^
	~C_SystemManager();								// �f�X�g���N�^

	bool Initialize();								// ����������
	int GameRun();									// ���C�����[�v����

private:
	void Finalize();								// �I������

	/*���� �ȉ������o�ϐ� ����*/
	//FpsTimer		fps;
	C_SceneManager* m_pSceneManager;				// �V�[���Ǘ��N���X�f�[�^
	HINSTANCE		m_hInstance;					// �C���X�^���X�n���h��
	int				m_nCmdShow;						// �R�}���h
};
