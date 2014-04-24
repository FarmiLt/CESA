//////////////////////////////////////////////////////
//
//	�ڍ�		�F���̃N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/16
//
//////////////////////////////////////////////////////
#include "Entity_Sphere.h"
#include "ModelManager.h"
#include "Camera.h"
#include "DirectX.h"
#include "KeyManager.h"


#pragma region �ÓI�����o�ϐ�
float C_Entity_Sphere::DEFAULT_RADIUS = 10.0f;
#pragma endregion


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/22
�p�r		�F�����o�ϐ��̏�����
��P����	�F�G���e�B�e�BID
��Q����	�F�\�����W(default : (0, 0, 0) )
��R����	�F�G���e�B�e�B�̑傫��(default : 1.0f)
�ԋp�l		�F�|

*************************************************************************/
C_Entity_Sphere::C_Entity_Sphere(DirectX::SimpleMath::Vector3 position, float scale)
: C_Game3DEntity(C_BaseEntity::GetNextID(), position, scale)
, m_velocity(0.3f){
	m_entityType = eENTITY::ENTITY_SPHERE;
	
	// ���a�̐ݒ�
	m_radius = DEFAULT_RADIUS * scale;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F�����o�ϐ��̉��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_Entity_Sphere::~C_Entity_Sphere(){
	Macro::SAFE_DELETE(m_pStateMachine);
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/18
�p�r		�F��Ԃɉ����čX�V�������s��
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_Entity_Sphere::Update(){
	C_Game3DEntity::Update();
	m_pStateMachine->Update();
	
	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F�`�揈��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Sphere::Render(){
	// �f�o�b�O�p
	C_Game3DEntity::Render();

	C_ModelManager::GetInstance()->GetCommonModel(COMMONMODEL_SPHERE)
		->Draw(	C_DirectX::GetInstance()->GetDeviceContext(),
				*(C_DirectX::GetInstance()->GetCommonState()),
				m_world,
				C_BaseCamera::GetInstance()->GetViewMatrix(),
				C_BaseCamera::GetInstance()->GetProjectionMatrix());
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/21
�p�r		�F���͂ɂ���ăG���e�B�e�B�𑀍삷��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Sphere::Control(){
	// �J�����̊p�x���擾
	float angle = C_BaseCamera::GetInstance()->GetCameraAngleAxisY();

	// �E�ֈړ�
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_RIGHT) >= 1){	
		DirectX::SimpleMath::Vector3 pos(GetPosition().x + m_velocity * cosf(DirectX::XMConvertToRadians(angle - 90.0f)),
										 GetPosition().y,
										 GetPosition().z + m_velocity * sinf(DirectX::XMConvertToRadians(angle - 90.0f)));
		SetPosition(pos);
	}

	// ���ֈړ�
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_LEFT) >= 1){
		DirectX::SimpleMath::Vector3 pos(GetPosition().x + m_velocity * cosf(DirectX::XMConvertToRadians(angle + 90.0f)),
										 GetPosition().y,
										 GetPosition().z + m_velocity * sinf(DirectX::XMConvertToRadians(angle + 90.0f)));
		SetPosition(pos);
	}

	// ���ֈړ�
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_UP) >= 1){
		DirectX::SimpleMath::Vector3 pos(GetPosition().x + m_velocity * cosf(DirectX::XMConvertToRadians(angle + 180.0f)),
										 GetPosition().y,
										 GetPosition().z + m_velocity * sinf(DirectX::XMConvertToRadians(angle + 180.0f)));
		SetPosition(pos);
	}

	// ��O�Ɉړ�
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_DOWN) >= 1){
		DirectX::SimpleMath::Vector3 pos(GetPosition().x + m_velocity * cosf(DirectX::XMConvertToRadians(angle)),
										 GetPosition().y, 
										 GetPosition().z + m_velocity * sinf(DirectX::XMConvertToRadians(angle)));
		SetPosition(pos);
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F���b�Z�[�W����ԃN���X�ɓ�����
��P����	�F���b�Z�[�W���
�ԋp�l		�F�������ꂽ��true, ��������Ȃ�������false

*************************************************************************/
bool C_Entity_Sphere::HandleMessage(const S_Message& message){
	return false; 
}