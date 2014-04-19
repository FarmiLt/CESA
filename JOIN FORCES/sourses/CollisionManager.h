//////////////////////////////////////////////////////
//
//	�ڍ�		�F�ՓˊǗ��N���X
//	�⑫		�F���̃N���X�ɓo�^����Ă���G���e�B�e�B��
//				�@�w��΂�delete���Ȃ��ł��������I�x
//				�@( �G���e�B�e�B�Ǘ��N���X������Ă���܂� )
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/18
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "Game3DEntity.h"


class C_CollisionManager : public C_Singleton<C_CollisionManager>{
public:
	void Update();									// �X�V����
	void RegisterEntity(C_Game3DEntity* pObject);	// �G���e�B�e�B�̒ǉ�

private:
	friend C_Singleton<C_CollisionManager>;			// �t�����h�ɓo�^
	C_CollisionManager(){}							// �R���X�g���N�^
	~C_CollisionManager();							// �f�X�g���N�^

	// �Փ˔��菔�X
	bool Crash_Sphere2Sphere(C_Game3DEntity* pController, C_Game3DEntity* pSphere);	// ���Ƌ�
	bool Crash_Cube2Cube(C_Game3DEntity* pController, C_Game3DEntity* pSphere);		// �����̂Ɨ�����

	// �����o�ϐ�
	C_Game3DEntity*				m_pController;		// ����G���e�B�e�B
	std::list<C_Game3DEntity*>	m_pCubeList;		// �����̂̃��X�g
	std::list<C_Game3DEntity*>	m_pSphereList;		// ���̂̃��X�g

	// TODO: �}�`��ǉ�����ꍇ�͂�����փ��X�g��ǉ�
};