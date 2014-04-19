#pragma once

#include <Windows.h>

class Timer
{
	// ���Z�b�g���Ă���̎���
	LARGE_INTEGER m_OffsetTime;

	// CPU���g���i�P�b������̃J�E���g���j
	LARGE_INTEGER m_CpuFrequency;

public:
	// �R���X�g���N�^
	Timer();

	// �f�X�g���N�^
	virtual ~Timer() {}

	// �^�C�}�[�̃��Z�b�g
	void Reset();

	// �^�C�}�[�̎擾
	DWORD Get();
};

// FPS�^�C�}�[�𐧌䂷��N���X
class FpsTimer : public Timer
{
	// FPS
	DWORD m_fps;

	// �P�t���[���ӂ�̑҂�����(ms)�~0x1000
	DWORD m_fpsWait;

	// �P�t���[���ӂ�̑҂����Ԃ̒[��������ێ����郏�[�N
	DWORD m_fpsWaitTT;

	// �O��`�悵������
	DWORD m_lastDraw;

	// true:�t���[���X�L�b�v���K�v
	bool m_drawSkipFlag;

	// �`�悵����
	DWORD m_drawCnt;

	// �`�悵�����Ԃ̗���ۑ��p���[�N
	DWORD m_drawTime[32];

public:
	// �R���X�g���N�^
	FpsTimer();

	// FPS�̐ݒ�
	DWORD SetFps(DWORD fps);

	// �ݒ肳��Ă���e�o�r�̎擾
	DWORD GetFps()
	{
		return m_fps;
	}

	// �E�G�C�g
	void Wait();

	// �`����X�L�b�v���ׂ����`�F�b�N����֐�
	bool CheckDrawSkip()
	{
		return m_drawSkipFlag;
	}

	// ���ۂ̂e�o�r�̎Z�o
	DWORD GetRealFps();

};

