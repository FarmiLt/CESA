//////////////////////////////////////////////////////
//
//	�ڍ�		�F�����̃N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/24
//
//////////////////////////////////////////////////////
#pragma once
#include "Game3DEntity.h"


class C_Entity_Cube : public C_Game3DEntity{
public:
	C_Entity_Cube(DirectX::SimpleMath::Vector3 position, float scale);	// �R���X�g���N�^
	~C_Entity_Cube();										// �f�X�g���N�^

	bool HandleMessage(const S_Message& message) override;	// ���b�Z�[�W����

	bool Update()	override;		// �X�V����
	void Render()	override;		// �`�揈��
	void Control()	override;		// ���쏈��

private:
	// �|���S�����\����
	struct S_Polygon{
		DirectX::SimpleMath::Vector3 vertices[4];	// �ʂ��Ȃ����_���W
		int	number;									// ���g�̖ʔԍ�
		int neighbor[4];							// �ׂ荇���ʔԍ�
	};

	// �����o�ϐ�
	int								m_nowUnderPolygon;	// ���݂̒��
	static const int				VERTEX_MAX = 8;		// ���_��(�����̂Ȃ̂œ��R�W��)
	static float					DEFAULT_RADIUS;		// �W���̔��a
	S_Polygon						POLYGON_LIST[6];	// �|���S����񃊃X�g
	DirectX::SimpleMath::Vector3	m_vertices[8];		// ���_���
};