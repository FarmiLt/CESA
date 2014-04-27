//////////////////////////////////////////////////////
//
//	�ڍ�		�F�����̃N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/25
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
		int verticesNumber[4];		// �|���S�����`�����Ă��钸�_�f�[�^
		int neighborPolygon[4];		// �אڂ���|���S���ԍ�
	};

	// �ړ��񋓌^
	enum eMOVE{
		MOVE_UP,		// ��
		MOVE_RIGHT,		// �E
		MOVE_DOWN,		// ��O
		MOVE_LEFT,		// ��
		MOVE_NONE,		// �ړ��Ȃ�
	};

	// ���\�b�h
	void GetKey();			// �L�[�擾����
	void Move_Up();			// ���ړ�
	void Move_Right();		// �E�ړ�
	void Move_Down();		// ��O�ړ�
	void Move_Left();		// ���ړ�
	
	// set�A�N�Z�T
	void SetVertices(DirectX::SimpleMath::Matrix matrix);		// ���_���̏�������

	// �����o�ϐ�
	static const int				POLYGON_MAX = 6;			// �ʂ̐�(�����̂Ȃ̂œ��R�U��)
	static const int				VERTEX_MAX = 8;				// ���_��(�����̂Ȃ̂œ��R�W��)
	static const float				DEFAULT_RADIUS;				// �W���̔��a
	static const float				ROTATION_SPEED;				// �ړ����̉�]���x
	DirectX::SimpleMath::Vector3	m_vertices[VERTEX_MAX];		// ���_���
	int								m_nowPolygon;				// ���݂̒��
	float							m_distance;					// ���S�_�ƕӂ̋���
	S_Polygon						m_polygonData[POLYGON_MAX];	// �ʂ̏��
	eMOVE							m_moveState;				// ���݂̈ړ����
};