//////////////////////////////////////////////////////
//
//	�ڍ�		�F��{�V�[���N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "SceneChanger.h"
#include "EntityFactory.h"


class C_BaseScene{
public:
	C_BaseScene( IC_SceneChanger* changer );	// �R���X�g���N�^
	virtual ~C_BaseScene() = 0;					// �f�X�g���N�^

	virtual bool Initialize() = 0;				// ����������
	virtual bool Update() = 0;					// �X�V����
	virtual void Draw() = 0;					// �`�揈��

private:
	IC_SceneChanger* m_pChanger;				// �V�[���Ǘ��N���X�ɃA�N�Z�X���邽�߂̃|�C���^
};