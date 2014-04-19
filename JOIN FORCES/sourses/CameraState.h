//////////////////////////////////////////////////////
//
//	�ڍ�		�F�J�����̏�ԃN���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/14
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "BaseState.h"
#include "Camera.h"


/***********************
/*��	�Ǐ]���	 ��*/
/***********************/
class C_Camera_Following : public C_Singleton<C_Camera_Following>, public C_BaseState<C_BaseCamera>{
public:
	void Enter(C_BaseCamera* pOwner) override;		// ����ۏ���
	void Execute(C_BaseCamera* pOwner) override;	// ���s����
	void Exit(C_BaseCamera* pOwner) override;		// �o�ۏ���

	bool OnMessage(C_BaseCamera* pOwner, const S_Message& message) override;	// ���b�Z�[�W����

private:
	friend C_Singleton<C_Camera_Following>;
	C_Camera_Following(){}		// �R���X�g���N�^
	~C_Camera_Following(){}		// �f�X�g���N�^

};


/***********************
/*��	��_���	 ��*/
/***********************/
class C_Camera_Fixed : public C_Singleton<C_Camera_Fixed>, public C_BaseState<C_BaseCamera>{
public:
	void Enter(C_BaseCamera* pOwner) override;		// ����ۏ���
	void Execute(C_BaseCamera* pOwner) override;	// ���s����
	void Exit(C_BaseCamera* pOwner) override;		// �o�ۏ���

	bool OnMessage(C_BaseCamera* pOwner, const S_Message& message) override;	// ���b�Z�[�W����

private:
	friend C_Singleton<C_Camera_Fixed>;
	C_Camera_Fixed(){}			// �R���X�g���N�^
	~C_Camera_Fixed(){}			// �f�X�g���N�^
};