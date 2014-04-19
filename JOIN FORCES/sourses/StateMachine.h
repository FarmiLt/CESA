//////////////////////////////////////////////////////
//
//	�ڍ�		�F��ԊǗ��N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/01/27
//
//////////////////////////////////////////////////////
#pragma once
#include "BaseState.h"
#include "Structure_Message.h"


template<class T>
class C_StateMachine{
public:
	C_StateMachine( T* pOwner );		// �R���X�g���N�^
	~C_StateMachine();					// �f�X�g���N�^

	bool Update();			// �X�V����
	void SetCurrentState( C_BaseState<T>* pFirstState );	// ���݂̏�Ԃ�ݒ�
	void SetGlobalState( C_BaseState<T>* pState );			// �펞���s��Ԃ�ݒ�
	void ChangeState( C_BaseState<T>* pNextState );			// ���݂̏�Ԃ�J�ڂ��鏈��

	bool HandleMessage( const S_Message& message );			// ���b�Z�[�W��M����

private:
	T*				m_pOwner;			// �I�[�i�[���
	C_BaseState<T>*	m_pCurrentState;	// ���݂̏��
	C_BaseState<T>*	m_pGlobalState;		// ��ɍs�����

};


//////////////////////////////////////////////////////
//
//	�ڍ�		�F��ԊǗ��N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/01/27
//
//////////////////////////////////////////////////////

/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F�����o�ϐ��̏�����
��P����	�F�I�[�i�[�̃A�h���X
�ԋp�l		�F�|

*************************************************************************/
template<class T> C_StateMachine<T>::C_StateMachine(T* pOwner)
: m_pOwner(pOwner)
, m_pCurrentState(nullptr)
, m_pGlobalState(nullptr){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F�|
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
template<class T> C_StateMachine<T>::~C_StateMachine(){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F�풓�����Ԃƌ��݂̏�Ԃɔ������������s��
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
template<class T> bool C_StateMachine<T>::Update(){
	if (m_pCurrentState){
		m_pCurrentState->Execute(m_pOwner);
	}
	if (m_pGlobalState){
		m_pGlobalState->Execute(m_pOwner);
	}

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F�����̌��݂̏�Ԃ�ݒ肷��
��P����	�F���݂̏�Ԃ̃A�h���X
�ԋp�l		�F�|

*************************************************************************/
template<class T> void C_StateMachine<T>::SetCurrentState(C_BaseState<T>* pFirstState){
	m_pCurrentState = pFirstState;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F�풓�����Ԃ�ݒ肷��
��P����	�F�풓�����Ԃ̃A�h���X
�ԋp�l		�F�|

*************************************************************************/
template<class T> void C_StateMachine<T>::SetGlobalState(C_BaseState<T>* pState){
	m_pGlobalState = pState;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F���݂̏�Ԃ��玟�̏�Ԃ֒u��������
��P����	�F���ɍ����ւ����Ԃ̃A�h���X
�ԋp�l		�F�|

*************************************************************************/
template<class T> void C_StateMachine<T>::ChangeState(C_BaseState<T>* pNextState){
	// �؂�ւ��钼�O�̏������s��
	if (m_pCurrentState) m_pCurrentState->Exit(m_pOwner);

	m_pCurrentState = pNextState;

	// �؂�ւ���ꂽ����̏������s��
	if (m_pCurrentState) m_pCurrentState->Enter(m_pOwner);
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F���b�Z�[�W�����݂̏�Ԃ������͏풓���Ă����Ԃɏ������Ă��炤
��P����	�F���b�Z�[�W
�ԋp�l		�F�������ꂽ��true, ����Ȃ�������false

*************************************************************************/
template<class T> bool C_StateMachine<T>::HandleMessage(const S_Message& message){
	if (m_pCurrentState->OnMessage(m_pOwner, message)){
		return true;
	}
	if (m_pGlobalState->OnMessage(m_pOwner, message)){
		return true;
	}

	return false;
}