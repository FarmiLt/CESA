//////////////////////////////////////////////////////
//
//	�ڍ�		�F�I�u�W�F�N�g�N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/20
//
//////////////////////////////////////////////////////
#pragma once


class C_ObjectTask{
public:
	// �R���X�g���N�^
	C_ObjectTask( float positionX, float positionY, float scalar = 0.0f, float angle = 0.0f, float priority = 0.5f );
	virtual ~C_ObjectTask();			// �f�X�g���N�^

	virtual bool Initialize()	= 0;	// ����������
	virtual bool Update()		= 0;	// �X�V����
	virtual void Draw()			= 0;	// �`�揈��

	void	Suicide();					// ���E����

	/*���� �ȉ��Q�b�^�[ ����*/
	float	GetPositionX() const;		// X���W�̎擾
	float	GetPositionY() const;		// Y���W�̎擾
	float	GetImageWidth() const;		// �摜���̎擾
	float	GetImageHeight() const;		// �摜�����̎擾
	bool	IsDead() const;				// ����ł��邩�ǂ������擾

protected:
	/*���� �ȉ������o�ϐ� ����*/
	float	m_positionX;		// ���WX
	float	m_positionY;		// ���WY
	float	m_speedX;			// �ړ����xX
	float	m_speedY;			// �ړ����xY
	float	m_imageWidth;		// �摜��
	float	m_imageHeight;		// �摜����
	float	m_priority;			// �D��x
	bool	m_deadFlag;			// ���S�t���O

private:
};