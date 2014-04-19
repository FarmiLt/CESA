//////////////////////////////////////////////////////
//
//	�ڍ�		�F�Q�[���G���e�B�e�B��ԃN���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/14
//
//////////////////////////////////////////////////////
#pragma once
#include "BaseState.h"
#include "Singleton.h"
#include "Game3DEntity.h"


/***********************
/*��	�҂����	 ��*/
/***********************/
class C_GameEntity_Wait : public C_Singleton<C_GameEntity_Wait>, public C_BaseState<C_Game3DEntity>{
public:
	void Enter(C_Game3DEntity* pOwner) override;	// ����ۏ���
	void Execute(C_Game3DEntity* pOwner) override;	// ���s����
	void Exit(C_Game3DEntity* pOwner) override;		// �o�ۏ���

	bool OnMessage(C_Game3DEntity* pOwner, const S_Message& message) override;	// ���b�Z�[�W����

private:
	friend C_Singleton<C_GameEntity_Wait>;
	C_GameEntity_Wait(){}		// �R���X�g���N�^
	~C_GameEntity_Wait(){}		// �f�X�g���N�^
};


/***********************************
/*��	�R���g���[���\���	 ��*/
/***********************************/
class C_GameEntity_Control : public C_Singleton<C_GameEntity_Control>, public C_BaseState<C_Game3DEntity>{
public:
	void Enter(C_Game3DEntity* pOwner) override;	// ����ۏ���
	void Execute(C_Game3DEntity* pOwner) override;	// ���s����
	void Exit(C_Game3DEntity* pOwner) override;		// �o�ۏ���

	bool OnMessage(C_Game3DEntity* pOwner, const S_Message& message) override;	// ���b�Z�[�W����

private:
	friend C_Singleton<C_GameEntity_Control>;
	C_GameEntity_Control(){}		// �R���X�g���N�^
	~C_GameEntity_Control(){}		// �f�X�g���N�^
};