//////////////////////////////////////////////////////
//
//	�ڍ�		�F�����̃N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/15
//
//////////////////////////////////////////////////////
#pragma once
#include "Game3DEntity.h"


class C_Entity_Cube : public C_Game3DEntity{
public:
	C_Entity_Cube(DirectX::SimpleMath::Vector3 position);	// �R���X�g���N�^
	~C_Entity_Cube();										// �f�X�g���N�^

	bool HandleMessage(const S_Message& message) override;	// ���b�Z�[�W����

	bool Update() override;		// �X�V����
	void Render() override;		// �`�揈��
	void Control() override;	// ���쏈��

private:
};