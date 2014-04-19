#include "KeyManager.h"

////////////////////////
/*�� �R���X�g���N�^ ��*/
////////////////////////
C_KeyManager::C_KeyManager(){
	memset( m_KeyPressingCount, 0, sizeof(m_KeyPressingCount) );
	memset( m_KeyReleasingCount, 0, sizeof(m_KeyReleasingCount) );
}


////////////////
/*���X�V������*/
////////////////
bool C_KeyManager::Update(){
	BYTE nowKeyStatus[KeyNum];

	GetKeyboardState( nowKeyStatus );	// ���݂̃L�[���͏�Ԃ��擾

	for(int i = 0; i < KeyNum; ++i){
		// �����L�[��������Ă���Ȃ��
		if((nowKeyStatus[i] & 0x80) != 0){
			// ������J�E���^���O���傫���Ȃ�O�ɂ���
			if(m_KeyReleasingCount[i] > 0){
				m_KeyReleasingCount[i] = 0;
			}
			// ������J�E���^�𑝂₷
			++m_KeyPressingCount[i];
		}
		// �L�[��������Ă��Ȃ��Ȃ��
		else{
			// ������J�E���^���O���傫���Ȃ�O�ɂ���
			if(m_KeyPressingCount[i] > 0){
				m_KeyPressingCount[i] = 0;
			}
			// ������J�E���^�𑝂₷
			++m_KeyReleasingCount[i];
		}
	}
	return true;
}


//////////////////////////////////
/*�� ������J�E���^���擾���� ��*/
//////////////////////////////////
int C_KeyManager::GetPressingCount(int keycode){
	if(! IsAvailableCode(keycode) ){
		return -1;
	}
	return m_KeyPressingCount[keycode];
}


//////////////////////////////////
/*�� ������J�E���^���擾���� ��*/
//////////////////////////////////
int C_KeyManager::GetReleasingCount(int keycode){
	if(! IsAvailableCode(keycode)){
		return -1;
	}
	return m_KeyReleasingCount[keycode];
}


/////////////////////////////////////////
/*�� keycode���L���Ȓl���`�F�b�N���� ��*/
/////////////////////////////////////////
bool C_KeyManager::IsAvailableCode(int keycode){
	if(! ( keycode >= 0 && keycode < KeyNum )){
		return false;
	}
	return true;
}