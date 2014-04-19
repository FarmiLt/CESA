//////////////////////////////////////////////////////
//
//	�ڍ�		�F��Վ��̃N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/14
//
//////////////////////////////////////////////////////
#pragma once
#include "Structure_Message.h"


class C_BaseEntity{
public:
	C_BaseEntity(int id);		// �R���X�g���N�^
	virtual ~C_BaseEntity();	// �f�X�g���N�^

	virtual bool HandleMessage( const S_Message& message ) = 0;	// ���b�Z�[�W�̎�M����

	// get�A�N�Z�T
	int GetID() const;			// ID�̎擾
	static int GetNextID();		// ���Ɏg�p�o����ID�̎擾
	

private:
	// �����o�ϐ�
	int			m_ID;			// ID���
	static int	m_nextID;		// ���ɗ��p�\��ID��� 
	
};