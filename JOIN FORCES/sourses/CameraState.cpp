//////////////////////////////////////////////////////
//
//	�ڍ�		�F�J������ԃN���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/14
//
//////////////////////////////////////////////////////
#include "CameraState.h"
#include "KeyManager.h"


#pragma region �Ǐ]�J�������


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�|
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Camera_Following::Enter(C_BaseCamera* pOwner){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�L�����N�^�Ǐ]�������s��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Camera_Following::Execute(C_BaseCamera* pOwner){
	// �L�[�����ŉ�]����悤�ɂ���
	if (C_KeyManager::GetInstance()->GetPressingCount('Z') >= 1){
		pOwner->TurnCamera_AxisY(false);
	}
	if (C_KeyManager::GetInstance()->GetPressingCount('X') >= 1){
		pOwner->TurnCamera_AxisY(true);
	}
	if (C_KeyManager::GetInstance()->GetPressingCount('A') >= 1){
		pOwner->TurnCamera_AxisX(false);
	}
	if (C_KeyManager::GetInstance()->GetPressingCount('S') >= 1){
		pOwner->TurnCamera_AxisX(true);
	}

	// �^�[�Q�b�g�Ǐ]�������Ăяo��
	pOwner->TargetFollowing();

	// �r���[�s��̍쐬
	pOwner->CreateViewMatrix();

	// �ˉe�s��̍쐬
	pOwner->CreateProjectionMatrix();
	
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14  
�p�r		�F�|
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Camera_Following::Exit(C_BaseCamera* pOwner){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�L�����N�^�Ǐ]�������s��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
bool C_Camera_Following::OnMessage(C_BaseCamera* pOwner, const S_Message& message){
	return true;
}

#pragma endregion


#pragma region ��_�J�������


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�|
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Camera_Fixed::Enter(C_BaseCamera* pOwner){
}



/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�|
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Camera_Fixed::Execute(C_BaseCamera* pOwner){
}



/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�|
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_Camera_Fixed::Exit(C_BaseCamera* pOwner){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/14
�p�r		�F�L�����N�^�Ǐ]�������s��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
bool C_Camera_Fixed::OnMessage(C_BaseCamera* pOwner, const S_Message& message){
	return true;
}

#pragma endregion