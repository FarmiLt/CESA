//////////////////////////////////////////////////////
//
//	�ڍ�		�F�^�C�g���V�[���N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "BaseScene.h"


class C_SceneTitle : public C_BaseScene{
public:
	C_SceneTitle( IC_SceneChanger* changer );	// �R���X�g���N�^
	~C_SceneTitle();								// �f�X�g���N�^

	bool Initialize()	override;				// ����������
	bool Update()		override;				// �X�V����
	void Draw()			override;				// �`�揈��

private:
};

