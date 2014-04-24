//////////////////////////////////////////////////////
//
//	�ڍ�		�F�J�����N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/21
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "StateMachine.h"
#include "Game3DEntity.h"


class C_BaseCamera : public C_Singleton<C_BaseCamera>{
public:
	void Update();			// �X�V����

	// set�A�N�Z�T
	void SetEyePosition(DirectX::SimpleMath::Vector3 position);		// �J�����ʒu
	void ChangeCameraType();										// �J�����^�C�v�̐؊�
	void SetOwner(C_Game3DEntity* pOwner);							// �J�����̒Ǐ]�Ώۂ̐ݒ�

	// �X�e�[�g����Ăяo��set�A�N�Z�T
	void TargetFollowing();				// �^�[�Q�b�g���W�̒���
	void CreateViewMatrix();			// �r���[�s��̍쐬
	void CreateProjectionMatrix();		// �ˉe�s��̍쐬
	void TurnCamera_AxisY(bool plus);	// Y���ɑ΂���J�����̉�]
	void TurnCamera_AxisX(bool plus);	// X���ɑ΂���J�����̉�]

	// get�A�N�Z�T
	DirectX::XMMATRIX GetViewMatrix() const;		// �r���[�s��̎擾
	DirectX::XMMATRIX GetProjectionMatrix() const;	// �ˉe�s��̎擾
	float			  GetCameraAngleAxisY() const;	// Y���ɑ΂���p�x���擾

private:
	// ���\�b�h
	friend C_Singleton<C_BaseCamera>;		// �t�����h�ɓo�^
	C_BaseCamera();							// �R���X�g���N�^
	~C_BaseCamera();						// �f�X�g���N�^
	void AdjustCameraPosition();			// �J�����ʒu�̒���
	
	/*���� �ȉ������o�ϐ� ����*/
	static const float				TURN_ANGLE;			// �J�������P�t���[���ŉ�]����p�x
	C_StateMachine<C_BaseCamera>*	m_pStateMachine;	// ��ԊǗ��N���X
	C_Game3DEntity*					m_pOwner;			// �Ǐ]�Ώ�
	DirectX::SimpleMath::Vector3	m_eyePosition;		// �J�����ʒu
	DirectX::SimpleMath::Vector3	m_targetPosition;	// �^�[�Q�b�g���W
	DirectX::SimpleMath::Vector3	m_upVector;			// �J�����㕔�x�N�g��
	DirectX::SimpleMath::Vector3	m_ownerBefPosition;	// �Ǐ]�Ώۂ̂P�t���[���O���W
	DirectX::XMMATRIX				m_view;				// �r���[�s��
	DirectX::XMMATRIX				m_projection;		// �ˉe�s��
	bool							m_cameraType;		// �J�����^�C�v(default : false(��_�J����))
	float							m_distance;			// �J�����̋���
	float							m_angleAxisX;		// X���ɑ΂���p�x
	float							m_angleAxisY;		// Y���ɑ΂���p�x
};