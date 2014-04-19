#pragma once
#include "Singleton.h"

/******************************
		�L�[�}�l�[�W��
******************************/
class C_KeyManager : public C_Singleton<C_KeyManager>{
	C_KeyManager();							// �R���X�g���N�^
	friend C_Singleton<C_KeyManager>;		// �t�����h�o�^

private:
	static const int KeyNum = 256;			// �L�[�̑���
	int m_KeyPressingCount[KeyNum];
	int m_KeyReleasingCount[KeyNum];
	
	bool IsAvailableCode(int keycode);		// keycode���L���ȃL�[�ԍ����ǂ���

public:
	bool Update();

	// �Q�b�^�[
	int GetPressingCount(int keycode);
	int GetReleasingCount(int keycode);


};