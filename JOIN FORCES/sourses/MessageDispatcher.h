//////////////////////////////////////////////////////
//
//	�ڍ�		�F���b�Z�[�W�Ǘ��N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/01/27
//	���l		�F�x�����Ԃ��L�郁�b�Z�[�W�͂܂�������
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "BaseEntity.h"
#include "Structure_Message.h"


class C_MessageDispatcher : public C_Singleton<C_MessageDispatcher>{
public:
	void Dispatch( int delay, int senderID, int receiverID, int message, void* extra );	// ���b�Z�[�W�̍쐬����

private:
	friend C_Singleton<C_MessageDispatcher>;	// �t�����h�ɓo�^
	C_MessageDispatcher();						// �R���X�g���N�^
	~C_MessageDispatcher();						// �f�X�g���N�^

	void Send( C_BaseEntity* pSender, const S_Message& message );	// ���b�Z�[�W�̑��M����

};
