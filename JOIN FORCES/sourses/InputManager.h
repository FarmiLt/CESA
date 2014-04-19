//////////////////////////////////////////////////////
//
//	�ڍ�		�F���͏����N���X�w�b�_�[
//				�@���̃N���X�ł͎��XBOX360�R���g���[��
//				�@�ł̏������s���܂�
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/14
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"


class C_InputManager : public C_Singleton<C_InputManager>{
public:
	void Update();		// �X�V����

	// get�A�N�Z�T
	bool	IsConnecting() const;					// �R���g���[�����q�����Ă��邩
	int		GetPressingCount(int button) const;		// �R���g���[���̃{�^���������Ԃ��擾

private:
	friend C_Singleton<C_InputManager>;	// �t�����h�ɓo�^
	C_InputManager();					// �R���X�g���N�^
	~C_InputManager();					// �f�X�g���N�^

	// �����o�ϐ�
	XINPUT_STATE 

};