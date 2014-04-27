//////////////////////////////////////////////////////
//
//	�ڍ�		�F�����̃N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/25
//
//////////////////////////////////////////////////////
#include "Entity_Cube.h"
#include "ModelManager.h"
#include "DirectX.h" 
#include "Camera.h"
#include "GameEntityState.h"
#include "KeyManager.h"

#pragma region �ÓI�����o�ϐ�
const float C_Entity_Cube::DEFAULT_RADIUS = 10.0f;
const float C_Entity_Cube::ROTATION_SPEED = 0.5f;
#pragma endregion

/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/25
�p�r		�F�����o�ϐ��̏�����
��P����	�F�G���e�B�e�BID
��Q����	�F�\�����W(default : (0, 0, 0) )
��R����	�F�G���e�B�e�B�̑傫��(default : 1.0f)
�ԋp�l		�F�|

*************************************************************************/
C_Entity_Cube::C_Entity_Cube(DirectX::SimpleMath::Vector3 position, float scale)
: C_Game3DEntity(C_BaseEntity::GetNextID(), position, scale){
	// �G���e�B�e�B�^�C�v�𗧕��̂ɐݒ�
	m_entityType = eENTITY::ENTITY_CUBE;

	// ���a(��)�̐ݒ�
	m_radius = DEFAULT_RADIUS * scale;

	// �����̂̒��S�_����ӂ܂ł̍ŒZ�������Z�o
	m_distance = sqrt((DEFAULT_RADIUS * scale) * (DEFAULT_RADIUS * scale) 
					+ (DEFAULT_RADIUS * scale) * (DEFAULT_RADIUS * scale));


	// ���_���̐ݒ�
	m_vertices[0] = DirectX::SimpleMath::Vector3(-DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS * scale + m_position.y, -DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[1] = DirectX::SimpleMath::Vector3( DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS * scale + m_position.y, -DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[2] = DirectX::SimpleMath::Vector3( DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS * scale + m_position.y,  DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[3] = DirectX::SimpleMath::Vector3(-DEFAULT_RADIUS * scale + m_position.x, -DEFAULT_RADIUS * scale + m_position.y,  DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[4] = DirectX::SimpleMath::Vector3(-DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS * scale + m_position.y, -DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[5] = DirectX::SimpleMath::Vector3( DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS * scale + m_position.y, -DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[6] = DirectX::SimpleMath::Vector3( DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS * scale + m_position.y,  DEFAULT_RADIUS * scale + m_position.z);
	m_vertices[7] = DirectX::SimpleMath::Vector3(-DEFAULT_RADIUS * scale + m_position.x,  DEFAULT_RADIUS * scale + m_position.y,  DEFAULT_RADIUS * scale + m_position.z);

	// �ʂ̏���ݒ�
		// �`�����钸�_�̔ԍ�	(���̖ʂ����ɂ����Ƃ��A����A�E��A�E���A�����@�̏�)
		// �אږʂ̔ԍ�			(���A�E�A��O�A���@�̏�)
	m_polygonData[0] = { {0, 1, 2, 3}, {1, 2, 3, 4} };
	m_polygonData[1] = { {4, 5, 1, 0}, {5, 2, 0, 4} };
	m_polygonData[2] = { {1, 5, 6, 2}, {1, 5, 3, 0} };
	m_polygonData[3] = { {3, 2, 6, 7}, {0, 2, 5, 4} };
	m_polygonData[4] = { {4, 0, 3, 7}, {1, 0, 3, 5} };
	m_polygonData[5] = { {5, 4, 7, 6}, {1, 4, 3, 2} };

	// ��ԍŏ��̒�ʂ͂O
	m_nowPolygon = 0;

	// �ړ���Ԃ�����������
	m_moveState = eMOVE::MOVE_NONE;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/25
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
	// ���W����я�ԊǗ��N���X�̍X�V
	C_Game3DEntity::Update();



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
�ŏI�X�V��	�F2014/04/26
�p�r		�F�I�u�W�F�N�g�̑�����s������
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Cube::Control(){
	// �L�[�擾����(��q)
	if ( m_moveState == eMOVE::MOVE_NONE ){
		GetKey();
	}

	switch(m_moveState){
	case eMOVE::MOVE_UP :
		// ���ړ�����
		Move_Up();
		return;

	case eMOVE::MOVE_RIGHT :
		// �E�ړ�����
		Move_Right();
		return;

	case eMOVE::MOVE_DOWN :
		// ��O�ړ�����
		Move_Down();
		return;

	case eMOVE::MOVE_LEFT :
		// ���ړ�����
		Move_Left();
		return;
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


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/26
�p�r		�F�L�[�̎擾���s���A�ړ���Ԃ�؂芷���鏈��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Cube::GetKey(){
	if ( C_KeyManager::GetInstance()->GetPressingCount(VK_UP) == 1 ){
		m_moveState = eMOVE::MOVE_UP;
	}
	if ( C_KeyManager::GetInstance()->GetPressingCount(VK_RIGHT) == 1 ){
		m_moveState = eMOVE::MOVE_RIGHT;
	}
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_DOWN) == 1 ){
		m_moveState = eMOVE::MOVE_DOWN;
	}
	if (C_KeyManager::GetInstance()->GetPressingCount(VK_LEFT) == 1){
		m_moveState = eMOVE::MOVE_LEFT;
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/25
�p�r		�F���ւ̈ړ�����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Cube::Move_Up(){
	// ��]�p�x
	static float rotX = 0.0f;
	
	rotX -= ROTATION_SPEED;
	// 90�x����������ړ����~�߂�
	if ( rotX <= -90.0f ){
		rotX = -90.0f;
		m_moveState = eMOVE::MOVE_NONE;	
	}

	// �w���ɑ΂��ĉ�]������
	 DirectX::SimpleMath::Matrix rotXMatrix =
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f),
			DirectX::XMConvertToRadians(rotX)
		);

	// ���[���h�s��ɔ��f����
	m_world *= rotXMatrix;
	
#pragma region ���g�̍��W�ɂ����f�����鏈��
	DirectX::SimpleMath::Matrix matTransPos = DirectX::XMMatrixIdentity();

	// ���W�����_�ɖ߂�
	matTransPos *= 
		DirectX::SimpleMath::Matrix::CreateTranslation(-m_position);

	// �ړ����������߂�ۂ̊p�x��\�߃��W�A���ɕϊ�
	float rad = DirectX::XMConvertToRadians(45.0f - (rotX + ROTATION_SPEED));

	// ��]���Ă��镪���l�����ĉ�]�������킹��
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
			DirectX::SimpleMath::Vector3( 0, 
				m_distance * sinf(rad),
				m_distance * cosf(rad)
			)
		);
	// �w����]����
	matTransPos *= 
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f),
				DirectX::XMConvertToRadians(-ROTATION_SPEED)
			);

	// ���W�����_�ɖ߂�
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
			DirectX::SimpleMath::Vector3(0,
				-m_distance * sinf(rad),
				-m_distance * cosf(rad)
			)
		);
	// ���̍��W�ʒu�ɖ߂�
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_position = DirectX::SimpleMath::Vector3::Transform(m_position, matTransPos);

#pragma endregion

	// ��]�p�x��߂�
	if ( m_moveState == eMOVE::MOVE_NONE ){
		rotX = 0.0f;
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/25
�p�r		�F�E�����Ɉړ����鏈��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Cube::Move_Right(){
	static float rotZ = 0.0f;
	rotZ -= ROTATION_SPEED;
	// 90�x����������ړ����~�߂�
	if (rotZ <= -90.0f){
		rotZ = -90.0f;
		m_moveState = eMOVE::MOVE_NONE;
	}

	// �y���ɑ΂��ĉ�]������
	DirectX::SimpleMath::Matrix rotZMatrix =
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f),
		DirectX::XMConvertToRadians(rotZ)
		);

	// ���[���h�s��ɔ��f����
	m_world *= rotZMatrix;

#pragma region ���g�̍��W�ɂ����f�����鏈��
	DirectX::SimpleMath::Matrix matTransPos = DirectX::XMMatrixIdentity();

	// ���W�����_�ɖ߂�
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(-m_position);

	// �ړ����������߂�ۂ̊p�x��\�߃��W�A���ɕϊ�
	float rad = DirectX::XMConvertToRadians(135.0f + (rotZ + ROTATION_SPEED));

	// ��]���Ă��镪���l�����ĉ�]�������킹��
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(m_distance * cosf(rad),
		m_distance * sinf(rad),
		0
		)
		);
	// �y����]����
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f),
		DirectX::XMConvertToRadians(-ROTATION_SPEED)
		);
	// ���W�����_�ɖ߂�
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(-m_distance * cosf(rad),
		-m_distance * sinf(rad),
		0
		)
		);
	// ���̍��W�ʒu�ɖ߂�
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_position = DirectX::SimpleMath::Vector3::Transform(m_position, matTransPos);

#pragma endregion




	// ��]�p�x��߂�
	if ( m_moveState == eMOVE::MOVE_NONE ){
		rotZ = 0.0f;
	}

}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/25
�p�r		�F�����o�ϐ��̉��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Cube::Move_Down(){
	// ��]�p�x
	static float rotX = 0.0f;

	rotX += ROTATION_SPEED;
	// 90�x����������ړ����~�߂�
	if (rotX >= 90.0f){
		rotX = 90.0f;
		m_moveState = eMOVE::MOVE_NONE;
	}

	// �w���ɑ΂��ĉ�]������
	DirectX::SimpleMath::Matrix rotXMatrix =
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f),
		DirectX::XMConvertToRadians(rotX)
		);

	// ���[���h�s��ɔ��f����
	m_world *= rotXMatrix;

#pragma region ���g�̍��W�ɂ����f�����鏈��
	DirectX::SimpleMath::Matrix matTransPos = DirectX::XMMatrixIdentity();

	// ���W�����_�ɖ߂�
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(-m_position);

	// �ړ����������߂�ۂ̊p�x��\�߃��W�A���ɕϊ�
	float rad = DirectX::XMConvertToRadians(135.0f - (rotX - ROTATION_SPEED));

	// ��]���Ă��镪���l�����ĉ�]�������킹��
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(0,
		m_distance * sinf(rad),
		m_distance * cosf(rad)
		)
		);
	// �w����]����
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f),
		DirectX::XMConvertToRadians(ROTATION_SPEED)
		);

	// �ړ����������߂�ۂ̊p�x��\�߃��W�A���ɕϊ�
	//rad = DirectX::XMConvertToRadians(45.0f + (rotX + ROTATION_SPEED));

	// ���W�����_�ɖ߂�
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(0,
		-m_distance * sinf(rad),
		-m_distance * cosf(rad)
		)
		);
	// ���̍��W�ʒu�ɖ߂�
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_position = DirectX::SimpleMath::Vector3::Transform(m_position, matTransPos);

#pragma endregion



	// ��]�p�x��߂�
	if (m_moveState == eMOVE::MOVE_NONE){
		rotX = 0.0f;
	}

}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/25
�p�r		�F�����o�ϐ��̉��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Cube::Move_Left(){
	static float rotZ = 0.0f;
	rotZ += ROTATION_SPEED;
	// 90�x����������ړ����~�߂�
	if (rotZ >= 90.0f){
		rotZ = 90.0f;
		m_moveState = eMOVE::MOVE_NONE;
	}

	// �y���ɑ΂��ĉ�]������
	DirectX::SimpleMath::Matrix rotZMatrix =
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f),
		DirectX::XMConvertToRadians(rotZ)
		);

	// ���[���h�s��ɔ��f����
	m_world *= rotZMatrix;


#pragma region ���g�̍��W�ɂ����f�����鏈��
	DirectX::SimpleMath::Matrix matTransPos = DirectX::XMMatrixIdentity();

	// ���W�����_�ɖ߂�
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(-m_position);

	// �ړ����������߂�ۂ̊p�x��\�߃��W�A���ɕϊ�
	float rad = DirectX::XMConvertToRadians(45.0f + (rotZ - ROTATION_SPEED));

	// ��]���Ă��镪���l�����ĉ�]�������킹��
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(m_distance * cosf(rad),
		m_distance * sinf(rad),
		0
		)
		);
	// �y����]����
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f),
		DirectX::XMConvertToRadians(ROTATION_SPEED)
		);
	// ���W�����_�ɖ߂�
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(-m_distance * cosf(rad),
		-m_distance * sinf(rad),
		0
		)
		);
	// ���̍��W�ʒu�ɖ߂�
	matTransPos *=
		DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_position = DirectX::SimpleMath::Vector3::Transform(m_position, matTransPos);

#pragma endregion



	// ��]�p�x��߂�
	if (m_moveState == eMOVE::MOVE_NONE){
		rotZ = 0.0f;
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/25
�p�r		�F�ێ����Ă��钸�_�����ړ��ɍ��킹�Ē������Ȃ���
��P����	�F���W�𒲐����邽�߂̍s��
�ԋp�l		�F�|

*************************************************************************/
void C_Entity_Cube::SetVertices(DirectX::SimpleMath::Matrix matrix){
	for(int i = 0; i < VERTEX_MAX; ++i){
		m_vertices[i] = DirectX::SimpleMath::Vector3::Transform(m_vertices[i], matrix);
	}
}