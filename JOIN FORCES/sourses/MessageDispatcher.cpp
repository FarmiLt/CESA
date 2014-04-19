//////////////////////////////////////////////////////
//
//	�ڍ�		�F��Վ��̃N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/01/27
//
//////////////////////////////////////////////////////
#include "MessageDispatcher.h"
#include "EntityManager.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F�|
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_MessageDispatcher::C_MessageDispatcher(){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F�|
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_MessageDispatcher::~C_MessageDispatcher(){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F�|
��P����	�F�x������
��Q����	�F���M����ID
��R����	�F���M���ID
��S����	�F���b�Z�[�W���e
��T����	�F���l
�ԋp�l		�F�|

*************************************************************************/
void C_MessageDispatcher::Dispatch( int delay, int senderID, int receiverID, int message, void* extra ){
	// ���̊Ǘ��N���X���瑗�M��̃A�h���X���擾����
	C_BaseEntity* pReceiver = C_EntityManager::GetInstance()->GetEntity( receiverID );

	// ���b�Z�[�W�̍쐬
	S_Message l_message = { delay, senderID, receiverID, message, extra };

	// �x�����Ԃ��݂����Ă��Ȃ��Ȃ�Α����ɑ��M����
	if ( delay <= 0 ){
		Send( pReceiver, l_message );
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F���M��Ƀ��b�Z�[�W��]������
��P����	�F���M��̃A�h���X
��Q����	�F���b�Z�[�W�T�v
�ԋp�l		�F�|

*************************************************************************/
void C_MessageDispatcher::Send( C_BaseEntity* pReceiver, const S_Message& message ){
	pReceiver->HandleMessage( message );
}