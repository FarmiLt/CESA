//////////////////////////////////////////////////////
//
//	�ڍ�		�F�x�[�X��O�����N���X
//				�@�S�Ă̗�O�����̐e�N���X
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/05
//
//////////////////////////////////////////////////////
#pragma once


class C_BaseException{
public:
	virtual unsigned GetErrorCode();		// �G���[�R�[�h�̎擾

protected:
	C_BaseException( unsigned errorCode );	// �R���X�g���N�^
	virtual ~C_BaseException();				// �f�X�g���N�^

private:
	int		m_errorCode;		// ��G���[�R�[�h 
};