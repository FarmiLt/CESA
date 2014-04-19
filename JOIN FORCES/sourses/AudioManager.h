#pragma once
#include "Singleton.h"


/*��		�g�p���Ă���}�N��			��*/
//namespace Macro{
//	template<class T>
//	static const void SAFE_DELETE_ARRAY( T*& p ){
//		if ( p ){
//			delete[] p;
//			p = nullptr;
//		}
//	}
//};
/*��		�g�p���Ă���}�N��			��*/


//////////////////////////////////////////////////////
//
//	�ڍ�		�F�T�E���h�Ǘ��N���X�w�b�_�[
//	�p�@		�F�g�p����ۂ͕K��
//				�@xact3.h ���C���N���[�h���Ă�������
//				�@�܂��Acpp�ɂď�̃}�N�����g�p���Ă���܂�
//	�Q�l�T�C�g	�Fhttp://kocoon-memo.hateblo.jp/archive/category/XACT
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/15
//
//////////////////////////////////////////////////////
class C_AudioManager : public C_Singleton<C_AudioManager>{
public:
	bool Initialize();						// ����������
	bool Play();							// �Đ�

private:
	friend C_Singleton<C_AudioManager>;		// �t�����h�o�^
	C_AudioManager();						// �R���X�g���N�^
	~C_AudioManager();						// �f�X�g���N�^

	bool InitEngine();						// �G���W���̏�����
	bool InitWaveBank();					// �E�F�[�u�o���N�̏�����
	bool InitSoundBank();					// �T�E���h�o���N�̏�����

	IXACT3Engine*		m_pXACTEngine;		// �T�E���h��炷�G���W��
	IXACT3WaveBank*		m_pXACTWaveBank;	// �E�F�[�u�o���N(xwb�t�@�C���̊i�[��)
	IXACT3SoundBank*	m_pXACTSoundBank;	// �T�E���h�o���N(xsb�t�@�C���̊i�[��)
	void*				m_pWBBuffer;		// �E�F�[�u�o���N�쐬�ɗp����o�b�t�@�̈�
	void*				m_pSBBuffer;		// �T�E���h�o���N�쐬�ɗp����o�b�t�@�̈�
};