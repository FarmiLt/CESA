//////////////////////////////////////////////////////
//
//	�ڍ�		�F�v���C�V�[���N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "BaseScene.h"
#include "Game3DEntity.h" 


class C_ScenePlay : public C_BaseScene{
public:
	C_ScenePlay( IC_SceneChanger* changer );	// �R���X�g���N�^
	~C_ScenePlay();								// �f�X�g���N�^

	bool Initialize()	override;				// ����������
	bool Update()		override;				// �X�V����
	void Draw()			override;				// �`�揈��

private:
	C_Game3DEntity*	m_pEntity;
};

