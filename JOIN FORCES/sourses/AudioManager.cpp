//////////////////////////////////////////////////////
//
//	�ڍ�		�F�T�E���h�Ǘ��N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/16
//
//////////////////////////////////////////////////////
#include "AudioManager.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/16
�p�r		�F�����o�ϐ��̏�����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_AudioManager::C_AudioManager()
	: m_pXACTEngine( nullptr )
	, m_pXACTWaveBank( nullptr )
	, m_pXACTSoundBank( nullptr )
	, m_pWBBuffer( nullptr )
	, m_pSBBuffer( nullptr ){
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/16
�p�r		�F�����o�ϐ��̉��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_AudioManager::~C_AudioManager(){
	// �T�E���h�o���N�̉��
	if ( m_pXACTSoundBank ){
		m_pXACTSoundBank->Destroy();
		m_pXACTSoundBank = nullptr;
	}
	Macro::SAFE_DELETE_ARRAY( m_pSBBuffer );

	// �E�F�[�u�o���N�̉��
	if ( m_pXACTWaveBank ){
		m_pXACTWaveBank->Destroy();
		m_pXACTWaveBank = nullptr;
	}
	UnmapViewOfFile( m_pWBBuffer );

	// �G���W���̉��
	if ( m_pXACTEngine ){
		m_pXACTEngine->ShutDown();
		m_pXACTEngine->Release();
	}
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/16
�p�r		�F�G���W���A�E�F�[�u�o���N�A�T�E���h�o���N�̏��������s��
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_AudioManager::Initialize(){
	// �G���W���̏�����(��q)
	if ( !InitEngine() ) return false;

	// �E�F�[�u�o���N�̏�����(��q)
	if ( !InitWaveBank() ) return false;

	// �T�E���h�o���N�̏�����(��q)
	if ( !InitSoundBank() ) return false;

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/16
�p�r		�F�L���[����ɉ����Đ�����
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_AudioManager::Play(){
	XACTINDEX index = m_pXACTSoundBank->GetCueIndex("asayake");
	// �L���[��
	m_pXACTSoundBank->Play(	index,		// �L���[�̃C���f�b�N�X
							0,			// �Đ��t���O(�c�[�����ō�����t�F�[�h���������g�p���邩�ǂ���)
							0,			// �Đ��J�n�ʒu
							NULL);		// �L���[�̃|�C���^

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/16
�p�r		�F�G���W�������������Axgs�t�@�C����ǂݍ���
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_AudioManager::InitEngine(){
	// COM ���g�p���邽�߂�COM���C�u����������������
	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	// �G���W���̏�����
	if ( FAILED( XACT3CreateEngine( NULL, &m_pXACTEngine ) ) ){
		// �G���[��
		MessageBox( NULL, TEXT("XACT�G���W���̏������Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	void*	pBuffer;
	DWORD	dwFileSize;				// xgs�t�@�C���T�C�Y
	bool	isSucceeded = false;	// �쐬�����t���O

	// �t�@�C���̐���
	HANDLE hFile = CreateFile(	TEXT("interface/bgm.xgs"),						// �t�@�C����
								GENERIC_READ,									// �t�@�C���ւ̃A�N�Z�X�^�C�v
								FILE_SHARE_READ,								// �t�@�C���̋��L���@�̎w��
								NULL,											// SECURITY_ATTRIBUTES �\���̂ւ̃|�C���^
								OPEN_EXISTING,									// �t�@�C���̑��݂ɑ΂��@�����삳���邩
								0,												// �t�@�C���̑�����t���O���w��
								NULL );											// �e���v���[�g�t�@�C���̎w��
	if ( hFile == INVALID_HANDLE_VALUE ){
		// �G���[��
		MessageBox( NULL, TEXT("�t�@�C���̐����Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// xgs�t�@�C���̃T�C�Y���擾����
	dwFileSize = GetFileSize( hFile, NULL );

	if ( dwFileSize != INVALID_FILE_SIZE ){
		pBuffer = CoTaskMemAlloc( dwFileSize );

		if ( pBuffer ){
			DWORD byteRead;

			// �t�@�C����ǂݍ���
			if ( ReadFile( hFile, pBuffer, dwFileSize, &byteRead, NULL ) != NULL ){
				// �����t���O�𗧂Ă�
				isSucceeded = true;
			}
		}
	}
	// �t�@�C�������
	CloseHandle( hFile );

	if ( !isSucceeded ){
		// �G���[��
		MessageBox( NULL, TEXT("xgs�t�@�C���̓ǂݍ��݂Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}
	
	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/16
�p�r		�F�E�F�[�u�o���N�����������A�E�F�[�u�o���N���쐬����
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_AudioManager::InitWaveBank(){
	DWORD	dwFileSize = 0;			// xwb�t�@�C���T�C�Y
	HANDLE	hMapFile;				// �}�b�v�t�@�C���̃n���h��
	bool	isSucceeded = false;	// �����t���O
	
	// xwb�t�@�C���̓ǂݍ���
	HANDLE hFile = CreateFile(	TEXT("interface/BGM_Title.xwb"),
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								0,
								NULL );
	if (  hFile == INVALID_HANDLE_VALUE ){
		// �G���[��
		MessageBox( NULL, TEXT("xwb�t�@�C���̓ǂݍ��݂Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// �t�@�C���T�C�Y�̎擾
	dwFileSize = GetFileSize( hFile, NULL );
	if ( dwFileSize == INVALID_FILE_SIZE ){
		// �G���[��
		MessageBox( NULL, TEXT("xwb�t�@�C���T�C�Y�擾�Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// �t�@�C���}�b�v�I�u�W�F�N�g�̐���
	hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
	// �t�@�C���r���[���}�b�v
	m_pWBBuffer = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
	
	// �E�F�[�u�o���N�̍쐬
	if ( m_pWBBuffer ){
		if ( SUCCEEDED( m_pXACTEngine->CreateInMemoryWaveBank( m_pWBBuffer, dwFileSize, 0, 0, &m_pXACTWaveBank ) ) ){
			isSucceeded = true;
		}
	}

	// �t�@�C�������
	CloseHandle( hMapFile );
	CloseHandle( hFile );

	if ( !isSucceeded ){
		// �G���[��
		MessageBox( NULL, TEXT("�E�F�[�u�o���N�̐����Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/16
�p�r		�F�T�E���h�o���N�����������A�T�E���h�o���N���쐬����
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_AudioManager::InitSoundBank(){
	DWORD	dwFileSize;				// xsb�t�@�C���T�C�Y
	DWORD	dwByteRead;
	bool	isSucceeded = false;	// �����t���O

	// xsb�t�@�C���̓ǂݍ���
	HANDLE hFile = CreateFile(	TEXT("interface/BGM_Title.xsb"),
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								0, 
								NULL );
	if ( hFile == INVALID_HANDLE_VALUE ){
		// �G���[��
		MessageBox( NULL, TEXT("xsb�t�@�C���̓ǂݍ��݂Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// �t�@�C���T�C�Y�̎擾
	dwFileSize = GetFileSize( hFile, NULL );
	if ( dwFileSize == INVALID_FILE_SIZE ){
		// �G���[��
		MessageBox( NULL, TEXT("xsb�t�@�C���T�C�Y�̎擾�Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	m_pSBBuffer = new BYTE[dwFileSize];
	if ( m_pSBBuffer == nullptr ){
		// �G���[��
		MessageBox( NULL, TEXT("�o�b�t�@�̈�̊m�ۂɎ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	dwByteRead = 0;
	ReadFile( hFile, m_pSBBuffer, dwFileSize, &dwByteRead, NULL );
	
	// �T�E���h�o���N�̐���
	if ( SUCCEEDED( m_pXACTEngine->CreateSoundBank( m_pSBBuffer, dwFileSize, 0, 0, &m_pXACTSoundBank ) ) ){
		isSucceeded = true;
	}

	if ( !isSucceeded ){
		// �G���[��
		MessageBox( NULL, TEXT("�T�E���h�o���N�̐���"), TEXT("ERROR"), MB_OK );
		return false;
	}

	return true;
}