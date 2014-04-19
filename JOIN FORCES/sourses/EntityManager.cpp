//////////////////////////////////////////////////////
//
//	�ڍ�		�F���̊Ǘ��N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/16
//
//////////////////////////////////////////////////////
#include "EntityManager.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F�R���e�i������ɂ���
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_EntityManager::~C_EntityManager(){
	// �C�e���[�^�̍쐬
	std::map<int, C_Game3DEntity*>::iterator iter = m_entityMap.begin();

	while( iter != m_entityMap.end() ){
		// �G���e�B�e�B���폜����
		Macro::SAFE_DELETE(iter->second);
		// ���X�g����폜����
		iter = m_entityMap.erase( iter );
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/17
�p�r		�F�o�^����Ă���G���e�B�e�B�̍X�V
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_EntityManager::Update(){
	// �C�e���[�^�̍쐬
	std::map<int, C_Game3DEntity*>::iterator iter = m_entityMap.begin();

	while (iter != m_entityMap.end()){
		// �����A���S�t���O�������Ă���ꍇ�폜����
		if (iter->second->IsDead()){
			// �G���e�B�e�B���폜����
			Macro::SAFE_DELETE(iter->second);

			// ���X�g����폜����
			iter = m_entityMap.erase(iter);
		}
		else{
			// �X�V�������s��
			iter->second->Update();
			++iter;
		}
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/17
�p�r		�F�o�^����Ă���G���e�B�e�B�̕`��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_EntityManager::Render(){
	// �C�e���[�^�̍쐬
	std::map<int, C_Game3DEntity*>::iterator iter = m_entityMap.begin();

	// �`��
	while (iter != m_entityMap.end()){
		iter->second->Render();
		++iter;
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�F���̂̏����R���e�i���ɓo�^����
��P����	�F���̂̃A�h���X
�ԋp�l		�F�|

*************************************************************************/
void C_EntityManager::RegisterEntity( C_Game3DEntity* pEntity ){
	m_entityMap.insert( std::pair<int, C_Game3DEntity*>( pEntity->GetID(), pEntity ) );
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/01/27
�p�r		�FID����ɂ���ID�������̂̃A�h���X���擾����
��P����	�F���̂�ID���
�ԋp�l		�F���̂̃A�h���X

*************************************************************************/
C_BaseEntity* C_EntityManager::GetEntity( int id ){
	// �C�e���[�^�̍쐬
	std::map<int, C_Game3DEntity*>::iterator iter = m_entityMap.find( id );

	// �������L�[�Ƃ���v�f���L��Ȃ炻�̒l��Ԃ�
	if ( iter != m_entityMap.end() ){
		return iter->second;
	}
	else{
		return nullptr;
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�FID����ɂ���ID�������̂̃A�h���X���R���e�i����폜����
��P����	�F���̂�ID���
�ԋp�l		�F�|

*************************************************************************/
void C_EntityManager::DeleteEntity( int id ){
	// �C�e���[�^�̍쐬
	std::map<int, C_Game3DEntity*>::iterator iter = m_entityMap.find( id );

	if ( iter != m_entityMap.end() ){
		// �G���e�B�e�B���폜����
		Macro::SAFE_DELETE(iter->second);

		// ���X�g����폜����
		iter = m_entityMap.erase( iter );
	}
}