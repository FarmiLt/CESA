//////////////////////////////////////////////////////
//
//	�ڍ�		�F��Տ�ԃN���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/01/21
//
//////////////////////////////////////////////////////
#pragma once
#include "Structure_Message.h"


template<class T>
class C_BaseState{
public:
	virtual ~C_BaseState(){}			// �f�X�g���N�^

	virtual void Enter( T* pOwner ) = 0;		// ����ۂ̏���
	virtual void Execute( T* pOwner ) = 0;		// ���s����
	virtual void Exit( T* pOwner ) = 0;			// �o�ۂ̏���

	virtual bool OnMessage( T* pOwner, const S_Message& message ) = 0;	// ���b�Z�[�W����

private:
};
