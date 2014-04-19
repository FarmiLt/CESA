//////////////////////////////////////////////////////
//
//	�ڍ�		�F�����̃N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/15
//
//////////////////////////////////////////////////////
#include "Entity_Cube.h"
#include "ModelManager.h"
#include "DirectX.h" 
#include "Camera.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�����o�ϐ��̏�����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_Entity_Cube::C_Entity_Cube(DirectX::SimpleMath::Vector3 position)
: C_Game3DEntity(C_BaseEntity::GetNextID(), position){
	m_entityType = eENTITY::ENTITY_CUBE;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�����o�ϐ��̉��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_Entity_Cube::~C_Entity_Cube(){
	Macro::SAFE_DELETE(m_pStateMachine);
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F��ԊǗ��N���X�̍X�V�������Ăяo��
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_Entity_Cube::Update(){
	m_pStateMachine->Update();

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F���f����`�悷��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Cube::Render(){
	// �f�o�b�O�p
	C_Game3DEntity::Render();

	C_ModelManager::GetInstance()->GetCommonModel(COMMONMODEL_BOX)
		->Draw( C_DirectX::GetInstance()->GetDeviceContext(),
				*(C_DirectX::GetInstance()->GetCommonState()),
				m_world,
				C_BaseCamera::GetInstance()->GetViewMatrix(),
				C_BaseCamera::GetInstance()->GetProjectionMatrix() );
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�I�u�W�F�N�g�̑�����s������
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Cube::Control(){

}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F���b�Z�[�W����ԊǗ��N���X�ŏ���������
��P����	�F�|
�ԋp�l		�F����ɏ�����true, ��������Ȃ�������false

*************************************************************************/
bool C_Entity_Cube::HandleMessage(const S_Message& message){
	if (m_pStateMachine->HandleMessage(message)){
		return false;
	}
	return true;
}