//////////////////////////////////////////////////////
//
//	�ڍ�		�F�Q�[���ŗ��p����3D���̃N���X
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/16
//
//////////////////////////////////////////////////////
#pragma once
#include "BaseEntity.h"
#include "StateMachine.h"
#include "Enum_Entity.h"


class C_Game3DEntity : public C_BaseEntity{
public:
	C_Game3DEntity(int id, DirectX::SimpleMath::Vector3 position);	// �R���X�g���N�^
	~C_Game3DEntity();												// �f�X�g���N�^

	virtual bool Update();			// �X�V����
	virtual void Render();			// �`�揈��
	virtual void Control() = 0;		// ���쏈��

	bool HandleMessage(const S_Message& message) override;			// ���b�Z�[�W�擾����

	// set�A�N�Z�T
	void Kill();					// ���̂��E������
	void ChangeControl();			// �����Ԃ̐؂芷��
	void Crashed(bool isCrashed);	// �Փ˃t���O�؂芷��

	// get�A�N�Z�T
	bool IsDead() const;								// �����󋵂̊m�F
	bool IsControlling() const;							// ���쒆���ǂ����̊m�F
	bool IsCrashing() const;							// �Փ˒����ǂ����̊m�F
	eENTITY IsType() const;								// �^�C�v�̎擾
	DirectX::SimpleMath::Vector3 GetPosition() const;	// ���W�̎擾
	float GetRadius() const;							// ���a�擾

protected:
	// set�A�N�Z�T
	void SetPosition(DirectX::SimpleMath::Vector3 position);	// ���W�̈ړ�

	// �����o�ϐ�
	DirectX::SimpleMath::Matrix		m_world;			// ���[���h�s��
	C_StateMachine<C_Game3DEntity>* m_pStateMachine;	// ��ԊǗ��N���X
	float							m_radius;			// ���a
	eENTITY							m_entityType;		// �^�C�v

private:
	// �����o�ϐ�
	bool							m_deadFlag;			// ���S�t���O(default : false)
	bool							m_controlling;		// ���쒆�t���O(default: false)
	bool							m_crashing;			// �Փ˒��t���O(�Փ˂��Ă������t���O�͗������ςȂ��ɂȂ�)
	DirectX::SimpleMath::Vector3	m_position;			// �\�����W

};