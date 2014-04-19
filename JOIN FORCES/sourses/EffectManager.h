//////////////////////////////////////////////////////
//
//	�ڍ�		�F�G�t�F�N�g�Ǘ��N���X�w�b�_�[(singleton)
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/24
//
//////////////////////////////////////////////////////
#pragma once
#include <list>				// list���g�p����̂ɕK�v
#include <algorithm>		// �\�[�g���g�p����̂ɕK�v
#include "Singleton.h"
#include "BaseEffect.h"		// �G�t�F�N�g���Ǘ�����̂ɕK�v


class C_EffectManager : public C_Singleton<C_EffectManager>{
public:
	bool Update();					// �X�V����
	void Draw();					// �`�揈��

	bool EntryTask( C_EffectTask* task );		// �^�X�N�̒ǉ� 

private:
	friend C_Singleton<C_EffectManager>;		// �t�����h�o�^
	C_EffectManager();							// �R���X�g���N�^
	~C_EffectManager();							// �f�X�g���N�^

	std::list<C_EffectTask*>	m_effectList;	// �G�t�F�N�g���[�p���X�g
};