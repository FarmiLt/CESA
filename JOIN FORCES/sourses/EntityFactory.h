//////////////////////////////////////////////////////
//
//	�ڍ�		�F�I�u�W�F�N�g�����N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/16
//
//////////////////////////////////////////////////////
#pragma once
#include "Entity_Cube.h"
#include "Entity_Sphere.h"
#include "Enum_Entity.h"


class C_EntityFactory{
public:
	// ���\�b�h
		// �I�u�W�F�N�g��������
	static void Create(eENTITY object, DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
};