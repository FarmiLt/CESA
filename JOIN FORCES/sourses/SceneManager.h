//////////////////////////////////////////////////////
//
//	�ڍ�		�F�V�[���J�ڃN���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "SceneChanger.h"
#include "BaseScene.h"


class C_SceneManager : public IC_SceneChanger{
public:
	C_SceneManager( eSCENE firstScene );			// �R���X�g���N�^
	~C_SceneManager();								// �f�X�g���N�^

	bool Update();									// �X�V����
	void Draw();									// �`�揈��

	void SwapScene( eSCENE nextScene )	override;	// �V�[���؂�ւ�����

private:
	C_BaseScene*	m_pCurrentScene;				// ���݂̃V�[��
	eSCENE			m_nextScene;					// ���̃V�[�����
};