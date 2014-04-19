//////////////////////////////////////////////////////
//
//	�ڍ�		�F�G�t�F�N�g�N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/24
//
//////////////////////////////////////////////////////
#pragma once
#include "Object.h"


class C_EffectTask : public C_ObjectTask{
public:
	// �R���X�g���N�^
	C_EffectTask( float positionX, float positionY, float scalar = 0.0f, float angle = 0.0f, float priority = 0.5f );
	~C_EffectTask();	// �f�X�g���N�^

	bool Initialize()	override;		// ����������
	bool Update()		override;		// �X�V����
	void Draw()			override;		// �`�揈��

protected:
	int m_timer;		// �G�t�F�N�g�^�C�}�[

private:
};
