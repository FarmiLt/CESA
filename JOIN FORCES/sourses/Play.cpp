//////////////////////////////////////////////////////
//
//	�ڍ�		�F�v���C�V�[���N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/16
//
//////////////////////////////////////////////////////
#include "Play.h"
#include "Camera.h"
#include "Entity_Cube.h"
#include "DirectX.h"
#include "ModelManager.h" 
#include "CollisionManager.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/17
�p�r		�F�V�[���؂�ւ��p�̃A�h���X��ۊǂ���
��P����	�F�V�[���؂�ւ��p�A�h���X
�ԋp�l		�F�|

*************************************************************************/
C_ScenePlay::C_ScenePlay( IC_SceneChanger* changer )
	: C_BaseScene( changer )
	, m_pEntity(nullptr){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/17
�p�r		�F�����o�ϐ��̉��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_ScenePlay::~C_ScenePlay(){
	Macro::SAFE_DELETE(m_pEntity);
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F�V�[���ɕK�v�ȃf�[�^�̍쐬
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_ScenePlay::Initialize(){
	// �G���e�B�e�B�̐���
	C_EntityFactory::Create(eENTITY::ENTITY_SPHERE, DirectX::SimpleMath::Vector3(10.0f, 10.0f, 0.0f));
	C_EntityFactory::Create(eENTITY::ENTITY_SPHERE, DirectX::SimpleMath::Vector3(-50.0f, 10.0f, 30.0f), 2.0f);
	C_EntityFactory::Create(eENTITY::ENTITY_CUBE, DirectX::SimpleMath::Vector3(100.0f, 10.0f, 50.0f));
	//m_pEntity = new C_Entity_Sphere(DirectX::SimpleMath::Vector3(0.0f, 10.0f, 0.0f) );

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F�V�[�����X�V����
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_ScenePlay::Update(){
	// �Փ˔�����s��
	C_CollisionManager::GetInstance()->Update();
	
	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F�V�[���ŗ��p����e�N�X�`���y�у��f����`�悷��
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
void C_ScenePlay::Draw(){
	DirectX::XMMATRIX f_world = DirectX::XMMatrixIdentity();

	C_ModelManager::GetInstance()->GetCommonModel(COMMONMODEL_FLOOR)
		->Draw(C_DirectX::GetInstance()->GetDeviceContext(),
		*(C_DirectX::GetInstance()->GetCommonState()),
		f_world,
		C_BaseCamera::GetInstance()->GetViewMatrix(),
		C_BaseCamera::GetInstance()->GetProjectionMatrix());

}