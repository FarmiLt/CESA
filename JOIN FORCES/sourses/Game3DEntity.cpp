//////////////////////////////////////////////////////
//
//	�ڍ�		�F�Q�[���ŗ��p����3D���̃N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/22
//
//////////////////////////////////////////////////////
#include "Game3DEntity.h"
#include "GameEntityState.h"
#include "Camera.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/22
�p�r		�F�����o�ϐ��̏�����
��P����	�F�G���e�B�e�BID
��Q����	�F�\�����W(default : (0, 0, 0) )
��R����	�F�G���e�B�e�B�̑傫��(default : 1.0f)
�ԋp�l		�F�|

*************************************************************************/
C_Game3DEntity::C_Game3DEntity(int id, DirectX::SimpleMath::Vector3 position, float scale)
: C_BaseEntity(id)
, m_radius(0.0f)
, m_position(position)
, m_scale(scale)
, m_deadFlag(false)
, m_crashing(false){

	// ���[���h�s����쐬
	m_world = DirectX::XMMatrixIdentity();
	m_world *= DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	

	// ��ԊǗ��N���X���쐬
	m_pStateMachine = new C_StateMachine<C_Game3DEntity>(this);

	// �����A�G���e�B�e�BID���O�Ȃ�Α���Ώۂɂ���
	if (GetID() == 0){
		m_pStateMachine->SetCurrentState(C_GameEntity_Control::GetInstance());
		m_controlling = true;
		// �J�����̒Ǐ]�Ώۂɐݒ�
		C_BaseCamera::GetInstance()->SetOwner(this);
	}
	else{
		m_pStateMachine->SetCurrentState(C_GameEntity_Wait::GetInstance());
		m_controlling = false;
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�����o�ϐ��̉��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_Game3DEntity::~C_Game3DEntity(){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/25
�p�r		�F���[���h�s��̒���
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
bool C_Game3DEntity::Update(){
	m_world = DirectX::XMMatrixIdentity();
	m_world *= DirectX::SimpleMath::Matrix::CreateScale(m_scale);

	// ��Ԃɉ������������s��
	m_pStateMachine->Update();

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/17
�p�r		�F�f�o�b�O�p�̃f�[�^���R���\�[����ʂɕ`��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Game3DEntity::Render(){
#ifdef _DEBUG
	// ���W��\������

	std::cout << "EntityID : " << GetID() << std::endl
		<< "POSITION_X : " << m_position.x << std::endl
		<< "POSITION_Y : " << m_position.y << std::endl
		<< "POSITION_Z : " << m_position.z << std::endl;
#endif
}

/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�����ł̓��b�Z�[�W���������Ȃ�
��P����	�F���b�Z�[�W���e
�ԋp�l		�F����ɏ������ꂽ��true, ��������Ȃ�������false

*************************************************************************/
bool C_Game3DEntity::HandleMessage(const S_Message& message){
	return false;
}


#pragma region set�A�N�Z�T


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F���S�t���O�𗧂Ă�
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Game3DEntity::Kill(){
	m_deadFlag = true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F�����Ԃ̐؂芷��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Game3DEntity::ChangeControl(){
	m_controlling = !m_controlling;

	if (m_controlling){
		m_pStateMachine->ChangeState(C_GameEntity_Control::GetInstance());
	}
	else{
		m_pStateMachine->ChangeState(C_GameEntity_Wait::GetInstance());
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/17
�p�r		�F�Փ˃t���O��؂芷����
��P����	�F�Փ˂��Ă��邩�ǂ���
�ԋp�l		�F�|

*************************************************************************/
void C_Game3DEntity::Crashed(bool isCrashed){
	m_crashing = isCrashed;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/18
�p�r		�F�\��������W��ύX����
��P����	�F�V�������W
�ԋp�l		�F�|

*************************************************************************/
void C_Game3DEntity::SetPosition(DirectX::SimpleMath::Vector3 position){
	m_position = position;
}


#pragma endregion


#pragma region get�A�N�Z�T


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/13
�p�r		�F���S�󋵂��擾����
��P����	�F�|
�ԋp�l		�F����ł��遨false, �����Ă��遨true

*************************************************************************/
bool C_Game3DEntity::IsDead() const{
	return m_deadFlag;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F���쒆���ǂ������擾����
��P����	�F�|
�ԋp�l		�F���쒆����Ȃ���false, ���쒆��true

*************************************************************************/
bool C_Game3DEntity::IsControlling() const{
	return m_controlling;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/17
�p�r		�F�Փ˒����ǂ������擾����(CollisionManager�Ŏg�p)
��P����	�F�|
�ԋp�l		�F�Փ˂��Ă��Ȃ���false, �Փ˒���true

*************************************************************************/
bool C_Game3DEntity::IsCrashing() const{
	return m_crashing;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/13
�p�r		�F���g�̍��W���擾����
��P����	�F�|
�ԋp�l		�F�\�����W���

*************************************************************************/
DirectX::SimpleMath::Vector3 C_Game3DEntity::GetPosition() const{
	return m_position;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/18
�p�r		�F���g�̔��a���擾����
��P����	�F�|
�ԋp�l		�F���a

*************************************************************************/
float C_Game3DEntity::GetRadius() const{
	return m_radius;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/18
�p�r		�F���g�̐}�`�^�C�v���擾����
��P����	�F�|
�ԋp�l		�F�}�`�^�C�v

*************************************************************************/
eENTITY C_Game3DEntity::IsType() const{
	return m_entityType;
}


#pragma endregion