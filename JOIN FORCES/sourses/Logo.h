//////////////////////////////////////////////////////
//
//	�ڍ�		�F���S�V�[���N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "BaseScene.h"


class C_SceneLogo : public C_BaseScene{
public:
	C_SceneLogo( IC_SceneChanger* changer );	// �R���X�g���N�^
	~C_SceneLogo()		override;				// �f�X�g���N�^

	bool Initialize()	override;				// ����������
	bool Update()		override;				// �X�V����
	void Draw()			override;				// �`�揈��

private:
	
};

