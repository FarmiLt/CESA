//////////////////////////////////////////////////////
//
//	�ڍ�		�F�I�u�W�F�N�g�����N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/18
//
//////////////////////////////////////////////////////
#include "EntityFactory.h"
#include "EntityManager.h"
#include "CollisionManager.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/18
�p�r		�F�C���X�^���X�𐶐�����
			�@�G���e�B�e�B�Ǘ��N���X�ƏՓˊǗ��N���X�ɓo�^����
��P����	�F�I�u�W�F�N�g�̎��
��Q����	�F�\�����W
�ԋp�l		�F�|

*************************************************************************/
void C_EntityFactory::Create(eENTITY objectType, DirectX::SimpleMath::Vector3 position){
	C_Game3DEntity* entity;

	switch (objectType){
		// ������
	case eENTITY::ENTITY_CUBE :
		entity = new C_Entity_Cube(position);
		break;

		// ����
	case eENTITY::ENTITY_SPHERE :
		entity = new C_Entity_Sphere(position);
		break;

		// TODO: �}�`��ǉ�����Ȃ炱����

	default:
		MessageBox(NULL, TEXT("���̃I�u�W�F�N�g���̓t�@�N�g���ɓo�^����Ă��܂��� (C_EntityFactory::Create)"), TEXT("ERROR"), MB_OK);
		return;
	}

	// �G���e�B�e�B�Ǘ��N���X�ɓo�^
	C_EntityManager::GetInstance()->RegisterEntity(entity);

	// �ՓˊǗ��N���X�ɓo�^
	C_CollisionManager::GetInstance()->RegisterEntity(entity);
}