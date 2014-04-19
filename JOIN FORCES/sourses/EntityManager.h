//////////////////////////////////////////////////////
//
//	�ڍ�		�F���̊Ǘ��N���X�w�b�_�[
//	�⑫		�F��{�I�ɃG���e�B�e�B���폜����̂�
//				�@���̃N���X���ōs�����ƁI
//				�@�܂��A�쐬�����G���e�B�e�B��
//				�@�K�����̃N���X�ɓo�^���邱�ƁI
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/16
//
//////////////////////////////////////////////////////
#pragma once
#include "Game3DEntity.h"
#include "Singleton.h"


class C_EntityManager : public C_Singleton<C_EntityManager>{
public:
	
	void Update();									// �X�V����
	void Render();									// �`�揈��
	void RegisterEntity( C_Game3DEntity* pEntity );	// ���̂̓o�^

	// �A�N�Z�T
	C_BaseEntity* GetEntity( int id );				// ���̃A�h���X�̎擾

private:
	friend C_Singleton<C_EntityManager>;			// �t�����h�ɓo�^
	C_EntityManager(){}								// �R���X�g���N�^
	~C_EntityManager();								// �f�X�g���N�^

	void DeleteEntity( int id );					// ���̂̍폜

	// �����o�ϐ�
	std::map<int, C_Game3DEntity*>	m_entityMap;	// ���̏��Ǘ��R���e�i
};