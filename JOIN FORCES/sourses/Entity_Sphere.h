//////////////////////////////////////////////////////
//
//	�ڍ�		�F���̃N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/16
//
//////////////////////////////////////////////////////
#pragma once
#include "Game3DEntity.h"


class C_Entity_Sphere : public C_Game3DEntity{
public:
	C_Entity_Sphere(DirectX::SimpleMath::Vector3 position);	// �R���X�g���N�^
	~C_Entity_Sphere();										// �f�X�g���N�^

	bool Update() override;		// �X�V����
	void Render() override;		// �`�揈��
	void Control() override;	// ���쏈��

	bool HandleMessage(const S_Message& message) override;	// ���b�Z�[�W��M����

private:

};