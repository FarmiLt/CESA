//////////////////////////////////////////////////////
//
//	�ڍ�		�F�J�����N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/22
//
//////////////////////////////////////////////////////
#include "Camera.h"
#include "CameraState.h"


#pragma region	�ÓI�����o�ϐ�
const float C_BaseCamera::TURN_ANGLE = 0.2f;	// �J�����̉�]�p�x
#pragma endregion


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/21
�p�r		�F�����o�ϐ��̏�����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_BaseCamera::C_BaseCamera()
: m_cameraType(true)				// TODO: �J�����̏�Ԃ�ς���Ȃ炱��
, m_pOwner(nullptr)
, m_ownerBefPosition(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f))
, m_distance(200.0f)
, m_angleAxisX(45.0f)
, m_angleAxisY(90.0f)
{
	m_eyePosition =
		DirectX::SimpleMath::Vector3(m_distance * cosf(DirectX::XMConvertToRadians(m_angleAxisY)),
									 m_distance * sin(DirectX::XMConvertToRadians(m_angleAxisX)),
									 m_distance * sin(DirectX::XMConvertToRadians(m_angleAxisY)));
	m_targetPosition= DirectX::SimpleMath::Vector3::Vector3(0.0f, 0.0f, 0.0f);
	m_upVector		= DirectX::SimpleMath::Vector3::Vector3(0.0f, 1.0f, 0.0f);

	// �r���[�s����쐬����
	CreateViewMatrix();

	// �ˉe�s����쐬����
	CreateProjectionMatrix();

	// ��ԊǗ��N���X�𐶐�
	m_pStateMachine = new C_StateMachine<C_BaseCamera>(this);
	if (m_cameraType){
		m_pStateMachine->SetCurrentState(C_Camera_Following::GetInstance());
	}
	else{
		m_pStateMachine->SetCurrentState(C_Camera_Fixed::GetInstance());
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�����o�ϐ��̉��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_BaseCamera::~C_BaseCamera(){
	// ��ԊǗ��N���X�̉��
	Macro::SAFE_DELETE(m_pStateMachine);
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F��Ԃɉ������X�V�������s��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::Update(){
	m_pStateMachine->Update();

	// �r���[�s��Ǝˉe�s�����蒼��
	CreateViewMatrix();
	CreateProjectionMatrix();

#ifdef _DEBUG
	// TODO: �J�����̊p�x��\������

	//std::cout << "CAMERA XZ : " << m_angleAxisY << std::endl;
	//std::cout << "CAMERA Y : " << m_angleAxisX << std::endl;
#endif
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/21
�p�r		�F�Ώۂ𒆐S�ɉ��悤�ɃJ�����̍��W�𒲐�����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::AdjustCameraPosition(){
	// �J�����ʒu���Đݒ肷��
	m_eyePosition =
		DirectX::SimpleMath::Vector3(m_pOwner->GetPosition().x + m_distance * cosf(DirectX::XMConvertToRadians(m_angleAxisY)),
									 m_pOwner->GetPosition().y + m_distance * sin(DirectX::XMConvertToRadians(m_angleAxisX)),
									 m_pOwner->GetPosition().z + m_distance * sin(DirectX::XMConvertToRadians(m_angleAxisY)));

}



/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/21
�p�r		�F�r���[�s����쐬����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::CreateViewMatrix(){
	// �J�����̈ʒu�𒲐�����
	if ( m_pOwner )AdjustCameraPosition();

	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eyePosition, m_targetPosition, m_upVector);
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�ˉe�s����쐬����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::CreateProjectionMatrix(){
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(DirectX::XMConvertToRadians(45.0f), Macro::WINDOW_WIDTH / (float)Macro::WINDOW_HEIGHT, 0.1f, 1000.0f);
}



/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�J�����^�C�v�� ��_�����Ǐ] ��؂芷����
			�@(�؂芷����O�ɒǏ]�Ώۂ�ݒ肵�Ă�������)
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::ChangeCameraType(){
	m_cameraType = !m_cameraType;

	if (m_cameraType){
		// �Ǐ]�J�������[�h�ɐ؂芷��
		m_pStateMachine->ChangeState( C_Camera_Following::GetInstance() );
	}
	else{
		// �Œ�J�������[�h�ɐ؂芷��
		m_pStateMachine->ChangeState(C_Camera_Fixed::GetInstance());
	}
}



/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/21
�p�r		�F�J�����̒Ǐ]�Ώۂ�ݒ肷��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::SetOwner(C_Game3DEntity* pOwner){
	m_pOwner = pOwner;

	// �Ǐ]�Ώۂ̌��݂̍��W���擾���Ă���
	m_ownerBefPosition = m_pOwner->GetPosition();
}


#pragma region set�A�N�Z�T

/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/19
�p�r		�F�J�����ʒu�̎w��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::SetEyePosition(DirectX::SimpleMath::Vector3 position){
	m_eyePosition = position;

	// �r���[�s�����蒼��
	//CreateViewMatrix();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/21
�p�r		�F�J������Y���ɑ΂��ĉ�]������
��P����	�F�񂷕���(���v��聨true, �����v��聨false)
��Q����	�F��]�p�x(�x���@)
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::TurnCamera_AxisY(bool plus){
	if ( plus ) m_angleAxisY += TURN_ANGLE;
	else		m_angleAxisY -= TURN_ANGLE;

	// �R�U�O�x��]������O�x�ɖ߂�
	if (m_angleAxisY <= -360.0f || m_angleAxisY >= 360.0f){
		m_angleAxisY = 0.0f;
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/22
�p�r		�F�J������X���ɑ΂��ĉ�]������
��P����	�F�񂷕���(���v��聨true, �����v��聨false)
��Q����	�F��]�p�x(�x���@)
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::TurnCamera_AxisX(bool plus){
	if (plus){
		// �W�O�x�𒴂��Ȃ��悤�ɂ���
		if ( m_angleAxisX <= 80.0f ) m_angleAxisX += TURN_ANGLE;
	}
	else{
		// �P�O�x�������Ȃ��悤�ɂ���
		if ( m_angleAxisX >= 10.0f ) m_angleAxisX -= TURN_ANGLE;
	}
}

/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/21
�p�r		�F�J�����̃^�[�Q�b�g�𑀍�Ώۂɍ��킹��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::TargetFollowing(){
	// ���݂̒Ǐ]�Ώۂ̍��W��ێ�����
	DirectX::SimpleMath::Vector3 target = m_pOwner->GetPosition();
	// �P�t���[���O�ƌ��݂̒Ǐ]�Ώۂ̍��W����ێ�����
	DirectX::SimpleMath::Vector3 difPos;
	difPos = target - m_ownerBefPosition;

	// �^�[�Q�b�g�̍��W���v���C���[�ɂ���
	m_targetPosition = target;

	// �J�����̈ʒu��Ώۂ��ړ������������ړ�����
	m_eyePosition = m_eyePosition + difPos;

	// ���݂̍��W���N���X���ŕۊǂ���
	m_ownerBefPosition = target;
	
}

#pragma endregion


#pragma region get�A�N�Z�T

/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�r���[�s����擾(3D���f���̕`��ȂǂɎg�p)
��P����	�F�|
�ԋp�l		�F�r���[�s��

*************************************************************************/
DirectX::SimpleMath::Matrix C_BaseCamera::GetViewMatrix() const{
	return m_view;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�ˉe�s����擾(3D���f���̕`��ȂǂɎg�p)
��P����	�F�|
�ԋp�l		�F�ˉe�s��

*************************************************************************/
DirectX::SimpleMath::Matrix C_BaseCamera::GetProjectionMatrix() const{
	return m_projection;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/21
�p�r		�F�J�����̌����Ă�������Ɍ�����������������邽�߂Ɋp�x���擾����
��P����	�F�|
�ԋp�l		�FY���ɑ΂���p�x

*************************************************************************/
float C_BaseCamera::GetCameraAngleAxisY() const{
	return m_angleAxisY;
}

#pragma endregion