//////////////////////////////////////////////////////
//
//	�ڍ�		�F�����̃N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/24
//
//////////////////////////////////////////////////////
#include "Entity_Cube.h"
#include "ModelManager.h"
#include "DirectX.h" 
#include "Camera.h"
#include "GameEntityState.h"
#include "KeyManager.h"


#pragma region �ÓI�����o�ϐ�
float C_Entity_Cube::DEFAULT_RADIUS = 10.0f;
#pragma endregion


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/24
�p�r		�F�����o�ϐ��̏�����
��P����	�F�G���e�B�e�BID
��Q����	�F�\�����W(default : (0, 0, 0) )
��R����	�F�G���e�B�e�B�̑傫��(default : 1.0f)
�ԋp�l		�F�|

*************************************************************************/
C_Entity_Cube::C_Entity_Cube(DirectX::SimpleMath::Vector3 position, float scale)
: C_Game3DEntity(C_BaseEntity::GetNextID(), position, scale){
	m_entityType = eENTITY::ENTITY_CUBE;
	m_radius = DEFAULT_RADIUS * scale;

	// ���_���̐ݒ�
	POLYGON_LIST[0] = {
		// �|���S�����Ȃ����_
		{ { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z } },
		0,					// �ʔԍ�
		{ 1, 2, 3, 4 }		// �אږʔԍ�
	};

	POLYGON_LIST[1] = {
		{ { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z } },
		1,
		{ 5, 2, 0, 4 }
	};

	POLYGON_LIST[2] = {
		{ {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z } },
		2,
		{ 1, 5, 3, 0 }
	};

	POLYGON_LIST[3] = {
		{ { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z } },
		3,
		{ 0, 2, 5, 4 }
	};

	POLYGON_LIST[4] = {
		{ { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z } },
		4,
		{ 1, 0, 3, 5 }
	};
	
	POLYGON_LIST[5] = {
		{ {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y, -DEFAULT_RADIUS * scale + m_position.z },
		  { -DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z },
		  {  DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS + m_position.y,  DEFAULT_RADIUS * scale + m_position.z } },
		5,
		{ 1, 4, 3, 2 }
	};
	// ��ԍŏ��̒�ʂ͂O
	m_nowUnderPolygon = 0;

	// ��ԊǗ��N���X�̍쐬
	m_pStateMachine = new C_StateMachine<C_Game3DEntity>(this);

	// �G���e�B�e�BID���O�Ȃ�Α���Ώۂɐݒ肷��
	if (GetID() == 0){
		m_pStateMachine->SetCurrentState(C_GameEntity_Control::GetInstance());
	}
	else{
		// �Ⴄ�Ȃ�ҋ@���
		m_pStateMachine->SetCurrentState(C_GameEntity_Wait::GetInstance());
	}
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
�ŏI�X�V��	�F2014/04/22
�p�r		�F��ԊǗ��N���X�̍X�V�������Ăяo��
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_Entity_Cube::Update(){
	// ���[���h���W�̍Đݒ�
	C_Game3DEntity::Update();

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

	C_ModelManager::GetInstance()->GetCommonModel(COMMONMODEL_CUBE)
		->Draw( C_DirectX::GetInstance()->GetDeviceContext(),
				*(C_DirectX::GetInstance()->GetCommonState()),
				m_world,
				C_BaseCamera::GetInstance()->GetViewMatrix(),
				C_BaseCamera::GetInstance()->GetProjectionMatrix() );
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/22
�p�r		�F�I�u�W�F�N�g�̑�����s������
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Cube::Control(){
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_RIGHT) == 1){

	}
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