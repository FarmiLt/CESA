//////////////////////////////////////////////////////
//
//	�ڍ�		�F�G�t�F�N�g�Ǘ��N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/17
//
//////////////////////////////////////////////////////
#include "EffectManager.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/24
�p�r		�F�|
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_EffectManager::C_EffectManager(){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/24
�p�r		�F�z����̃G�t�F�N�g��S�폜����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_EffectManager::~C_EffectManager(){
	std::list<C_EffectTask*>::iterator iter;

	for ( iter = m_effectList.begin(); iter != m_effectList.end(); ){
		delete (*iter);
		iter = m_effectList.erase( iter );
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/17
�p�r		�Flist�������ԂɃA�N�Z�X�����S�t���O�������Ă�����폜����
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_EffectManager::Update(){
	// �A�N�Z�X���邽�߂̃C�e���[�^���쐬
	std::list<C_EffectTask*>::iterator iter;

	for (iter = m_effectList.begin(); iter != m_effectList.end(); ){
		// ����ł�����f�[�^������
		if ( (*iter)->IsDead() ) {
			Macro::SAFE_DELETE (*iter);
			iter = m_effectList.erase( iter );
		}
		else {
			// �G�t�F�N�g���X�V����
			(*iter)->Update();
			++iter;
		}
	}

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/24
�p�r		�Flist���̃G�t�F�N�g�̕`����s��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_EffectManager::Draw(){
	// �z��ɃA�N�Z�X����ׂ̃C�e���[�^
	std::list<C_EffectTask*>::iterator iter;

	for ( iter = m_effectList.begin(); iter != m_effectList.end(); ){
		(*iter)->Draw();
		++iter;
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/24
�p�r		�F�z��ɃG�t�F�N�g��o�^����
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_EffectManager::EntryTask( C_EffectTask* task ){

	m_effectList.push_back( task );

	return true;
}