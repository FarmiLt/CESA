//////////////////////////////////////////////////////
//
//	�ڍ�		�F�ՓˊǗ��N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2014/04/16
//
//////////////////////////////////////////////////////
#include "CollisionManager.h"
#include "Camera.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F���X�g���̑S�v�f���폜����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_CollisionManager::~C_CollisionManager(){
	m_pCubeList.clear();
	m_pSphereList.clear();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F���X�g���ɓo�^����Ă���G���e�B�e�B�̏Փ˔�����s��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_CollisionManager::Update(){
	// ����Ώۂ����Ȃ��Ȃ�ΏՓ˔�����s��Ȃ�
	if (m_pController == nullptr) return;

	std::list<C_Game3DEntity*>::iterator iterSphere = m_pSphereList.begin();
	std::list<C_Game3DEntity*>::iterator iterCube = m_pCubeList.begin();

	if (m_pController->IsType() == eENTITY::ENTITY_SPHERE){
		// �v���C���[�̏Փ˃t���O
		bool crashed = false;

		while (iterSphere != m_pSphereList.end()){
			// ���łɏՓ˂��Ă���ꍇ�͔���Ώۂɂ��Ȃ�
				// �Ȃ��Ȃ�A���ő���Ώۂ��؂芷���Ă��܂�����
			
				// �Փ˔���i���Ƌ��j
			if (Crash_Sphere2Sphere(m_pController, (*iterSphere))){
				crashed = true;

				// ���łɂԂ����Ă���ꍇ����ΏەύX�������s��Ȃ�
				if (!(*iterSphere)->IsCrashing()){
					// ���݂����Փ˒��ɂ���
					m_pController->Crashed(crashed);
					(*iterSphere)->Crashed(crashed);

					// ����Ώی��
					m_pController->ChangeControl();
					(*iterSphere)->ChangeControl();

					// ���X�g����ύX����
					m_pSphereList.push_back(m_pController);
					m_pController = (*iterSphere);
					// ���X�g����폜(���̎��_�ŃC�e���[�^�����ɗ����Ȃ��Ȃ�A�ł����Ȃ�)
					m_pSphereList.erase(iterSphere);

					// �J�����̑Ώۂ�؂芷����
					C_BaseCamera::GetInstance()->SetOwner(m_pController);

					// ���������烋�[�v�𔲂���
					return;
				}
			}
			else{
				(*iterSphere)->Crashed(false);
			}
			++iterSphere;
		}
		m_pController->Crashed(crashed);
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/16
�p�r		�F�G���e�B�e�B�����X�g�ɓo�^����
��P����	�F�G���e�B�e�B
�ԋp�l		�F�|

*************************************************************************/
void C_CollisionManager::RegisterEntity(C_Game3DEntity* object){
	// �����A����ΏۂȂ�΃��X�g�O�ɕێ�
	if (object->IsControlling()){
		m_pController = object;
	}
	else{
		// �I�u�W�F�N�g���Ń��X�g�Ǘ�����
		switch(object->IsType()){
			// ������
		case eENTITY::ENTITY_CUBE :
			m_pCubeList.push_back(object);
			break;

			// ����
		case eENTITY::ENTITY_SPHERE :
			m_pSphereList.push_back(object);
			break;

			// TODO: �}�`��ǉ�����Ȃ炱����

		default:
			MessageBox(NULL, TEXT("���̃I�u�W�F�N�g�̃��X�g�����݂��܂���"), TEXT("ERROR"), MB_OK);
			break;
		}
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2014/04/18
�p�r		�F���Ƌ��̏Փ˔���
��P����	�F����Ώ�
��Q����	�F����
�ԋp�l		�F�Փ˂��Ă��遨true, �Փ˂��Ă��Ȃ���false

*************************************************************************/
bool C_CollisionManager::Crash_Sphere2Sphere(C_Game3DEntity* pController, C_Game3DEntity* pSphere){
	// �Q�̃G���e�B�e�B�̋������o��
	DirectX::SimpleMath::Vector3 vec = pSphere->GetPosition() - pController->GetPosition();
	float distance = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		/*vec.Distance*/;

	// �Q�_�Ԃ̋��������݂��̔��a�𑫂����l��菬������Γ������Ă���
	if (distance <= ( pSphere->GetRadius() + pController->GetRadius() ) ){
		return true;
	}

	return false;
}