//////////////////////////////////////////////////////
//
//	�ڍ�		�F�J�����N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/18
//
//////////////////////////////////////////////////////
#include "Camera.h"
#include "CameraState.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�����o�ϐ��̏�����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_BaseCamera::C_BaseCamera()
: m_cameraType(true)				// TODO: �J�����̏�Ԃ�ς���Ȃ炱��
, m_pOwner(nullptr)
, m_distance(DirectX::SimpleMath::Vector3(0.0f, 30.0f, 50.0f)){
	m_eyePosition	= m_distance;
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
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�r���[�s����쐬����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::CreateViewMatrix(){
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
�ŏI�X�V��	�F2014/04/14
�p�r		�F�J�����̒Ǐ]�Ώۂ�ݒ肷��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::SetOwner(C_Game3DEntity* pOwner){
	m_pOwner = pOwner;
}


#pragma region set�A�N�Z�T

/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�J�����ʒu�̎w��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::SetEyePosition(DirectX::SimpleMath::Vector3 position){
	m_eyePosition = position;

	// �r���[�s�����蒼��
	CreateViewMatrix();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�J��������]������
��P����	�F�J��������]�����鎲
��Q����	�F��]�p�x(�x���@)
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::TurnCamera(eTURNCAMERA axis, float angle){
	// �J���������_�Ɉړ�������

	// �J��������]������
	switch (axis){
	case eTURNCAMERA::X :
		break;

	case eTURNCAMERA::Y :
		break;

	case eTURNCAMERA::Z :
		break;
	}

	// �J���������̈ʒu�ɖ߂�


	// �r���[�s�����蒼��
	CreateViewMatrix();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/18
�p�r		�F�J�����̃^�[�Q�b�g�𑀍�Ώۂɍ��킹��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_BaseCamera::TargetFollowing(){
	// �^�[�Q�b�g�̍��W���v���C���[�ɂ���
	m_targetPosition = m_pOwner->GetPosition();

	// �v���C���[�ɑ΂��ē���
	m_eyePosition = m_pOwner->GetPosition() + m_distance;
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
DirectX::XMMATRIX C_BaseCamera::GetViewMatrix() const{
	return m_view;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�ˉe�s����擾(3D���f���̕`��ȂǂɎg�p)
��P����	�F�|
�ԋp�l		�F�ˉe�s��

*************************************************************************/
DirectX::XMMATRIX C_BaseCamera::GetProjectionMatrix() const{
	return m_projection;
}


#pragma endregion