//////////////////////////////////////////////////////
//
//	�ڍ�		�F�V�[���J�ڃN���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "Enum_Scene.h"			// �V�[���񋓌^�w�b�_�[


class IC_SceneChanger{
public:
	virtual ~IC_SceneChanger() = 0;						// �f�X�g���N�^
	virtual void SwapScene( eSCENE nextScene ) = 0;		// �V�[���؂�ւ�����
};