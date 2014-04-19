//////////////////////////////////////////////////////
//
//	�ڍ�		�FDirectX�N���X���\�b�h
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/04
//
//////////////////////////////////////////////////////
#include "DirectX.h"


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F�����o�ϐ��̏�����
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_DirectX::C_DirectX()
{
	m_pD3DDevice			= nullptr;
	m_pDeviceContext		= nullptr;
	m_pSwapChain			= nullptr;
	m_pRenderTargetView	= nullptr;
	m_pDepthStencil		= nullptr;
	m_pDepthStencilView	= nullptr;
	m_pDXGIDevice		= nullptr;
	m_pDXGIAdapter		= nullptr;
	m_pDXGIFactory		= nullptr;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F�I���������Ăяo��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
C_DirectX::~C_DirectX()
{
	Finalize();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�FDirectX�f�o�C�X�̐����A���̎��ӂ̐ݒ�
��P����	�F���݂̃E�B���h�E�n���h��
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_DirectX::Initialize( HWND hWnd )
{
    RECT rc;
	// �N���C�A���g�̈�̃T�C�Y���擾����
    GetClientRect( hWnd, &rc );
    UINT width = rc.right - rc.left;			// �E�B���h�E��
    UINT height = rc.bottom - rc.top;			// �E�B���h�E����

    // DirectX�f�o�C�X�̍쐬( ��q )
	if ( !CreateDirectX11Device() ) return false;

	// �g�p�\�ȃ}���`�T���v�����擾
	// ( DirectX�f�o�C�X���g�p���邽�ߕK��DirectX�f�o�C�X�쐬��ɋL�q )
    DXGI_SAMPLE_DESC SampleDesc;
    for ( UINT i = 1; i <= 2; ++i ) {
        UINT Quality;
        if (SUCCEEDED(m_pD3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, i, &Quality))) {
            if (Quality > 0) {
                DXGI_SAMPLE_DESC Desc = { i, Quality - 1 };
                SampleDesc = Desc;
            }
        }
    }

	// DXGI �̏�����( ��q )
	if ( !InitDXGI() ) return false;

	// �X���b�v�`�F�C���̍쐬( ��q )
	// (�{���̓X���b�v�`�F�C����DXGI�̕��ނȂ񂾂��ǂ܂�������)
	if ( !CreateSwapChain( hWnd, SampleDesc, width, height ) ) return false;

	// �`��Ɋւ�����̏�����( ��q )
	if ( !InitRendering( SampleDesc, width, height ) ) return false;

	// DirectXTK �̏�����( ��q )
	InitDirectXTK();

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F����������Ăяo��
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_DirectX::Finalize()
{
	Cleanup();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F��ʂ̃��Z�b�g�ƃX���b�v���s��
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_DirectX::Update()
{
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@���X���b�v(����ւ�)����
	if ( FAILED( m_pSwapChain->Present( 0, 0 ) ) )
	{
		MessageBox( NULL, TEXT("�o�b�t�@�̃X���b�v�Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// ��ʂ̃N���A
	m_pDeviceContext->ClearRenderTargetView( m_pRenderTargetView, DirectX::Colors::Aquamarine );

	// �[�x�X�e���V���o�b�t�@�̃N���A
	m_pDeviceContext->ClearDepthStencilView( m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�FPC�̃X�y�b�N�ɍ�����DirectX�f�o�C�X�̐���
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_DirectX::CreateDirectX11Device()
{
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// �h���C�o�^�C�v
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,				// �n�[�h�E�F�A�h���C�o
        D3D_DRIVER_TYPE_WARP,					// �\�t�g�E�F�A���X�^���C�U
        D3D_DRIVER_TYPE_REFERENCE,				// ���t�@�����X���X�^���C�U
    };
    UINT numDriverTypes = ARRAYSIZE( driverTypes );

	// �@�\���x��
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,					// DirectX11.0 �̋@�\
        D3D_FEATURE_LEVEL_10_1,					// DirectX10.1
        D3D_FEATURE_LEVEL_10_0,					// DirectX10.0
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	// DirectX11�̃f�o�C�X���쐬
	for ( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes;  )
    {
        m_driverType = driverTypes[driverTypeIndex];
        if ( SUCCEEDED( D3D11CreateDevice( NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &m_pD3DDevice, &m_featureLevel, &m_pDeviceContext ) ) )
		{
			break;			// �쐬�ɐ��������甲����
		}
		else
		{
			// ����̈ʂ̃h���C�o�ōĒ���
			++driverTypeIndex;

			// �Ō�܂ō쐬�Ɏ��s������G���[��
			if ( driverTypeIndex == numDriverTypes )
			{
				MessageBox( NULL, TEXT("DirectX�f�o�C�X�̍쐬�Ɏ��s"), TEXT("ERROR"), MB_OK );
				return false;
			}
		}
    }

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�FDXGI�f�o�C�X, DXGI�A�_�v�^, DXGI�t�@�N�g���̎擾
��P����	�F�|
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_DirectX::InitDXGI()
{
	// �C���^�[�t�F�C�X�擾
	if ( FAILED( m_pD3DDevice->QueryInterface( __uuidof( IDXGIDevice1 ), ( LPVOID* )&m_pDXGIDevice ) ) )
	{
		MessageBox( NULL, TEXT("DXGI�f�o�C�X�̎擾�Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}
	// �A�_�v�^�[�擾
    if ( FAILED( m_pDXGIDevice->GetAdapter(&m_pDXGIAdapter) ) )
    {
		MessageBox( NULL, TEXT("DXGI�A�_�v�^�̎擾�Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}
	// �t�@�N�g���[�擾
	if ( FAILED( m_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (LPVOID*)&m_pDXGIFactory) ) )
    {
		MessageBox( NULL, TEXT("DXGI�t�@�N�g���̎擾�Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F�X���b�v�`�F�C����ݒ肵�A�쐬����
��P����	�F�E�B���h�E�n���h��
��Q����	�F�}���`�T���v���\����
��R����	�F�E�B���h�E��
��S����	�F�E�B���h�E����
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_DirectX::CreateSwapChain( HWND hWnd, DXGI_SAMPLE_DESC desc, UINT clientWidth, UINT clientHeight )
{
	// �X���b�v�`�F�C���̍\���̂�������
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
		// �ȉ��f�B�X�v���C�o�b�t�@�̐ݒ�
    sd.BufferCount = 1;											// ����
    sd.BufferDesc.Width = clientWidth;							// ��	(�E�B���h�E���ł���)
    sd.BufferDesc.Height = clientHeight;						// ����	(�E�B���h�E�����ł���)
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// �t�H�[�}�b�g
    sd.BufferDesc.RefreshRate.Numerator = 60;					// ���t���b�V�����[�g(���q)
    sd.BufferDesc.RefreshRate.Denominator = 1;					// ���t���b�V�����[�g(����)		(60Hz���ŉ�ʍX�V)
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;			// �g�p�ړI	(DXGI_USAGE_RENDER_TARGET_OUTPUT �̓����_�^�[�Q�b�g�Ƃ��Ďg�p)
    sd.OutputWindow = hWnd;										// �o�͂���E�B���h�E�n���h��
    sd.SampleDesc = desc;										// �}���`�T���v��
    sd.Windowed = TRUE;											// �E�B���h�E���[�h
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;					// �X���b�v�����ɂ�����I�v�V����
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;			// <-- �t���X�N���[������ʉ𑜓x��؂�ւ���
	
	// �X���b�v�`�F�C���̐���
	if( FAILED( m_pDXGIFactory->CreateSwapChain(m_pD3DDevice, &sd, &m_pSwapChain) ) )
	{
		MessageBox( NULL, TEXT("�X���b�v�`�F�C�������Ɏ��s"), TEXT("ERROR"), MB_OK );
        return false;
    }

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F�X���b�v�`�F�C����ݒ肵�A�쐬����
��P����	�F�}���`�T���v��
��Q����	�F�E�B���h�E��
��R����	�F�E�B���h�E����
�ԋp�l		�F����I����true, �ُ팟�m��false

*************************************************************************/
bool C_DirectX::InitRendering( DXGI_SAMPLE_DESC desc, UINT clientWidth, UINT clientHeight )
{
	
    ID3D11Texture2D* pBackBuffer = NULL;
	// �o�b�N�o�b�t�@�̎擾
    if ( FAILED( m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer ) ) )
	{
		MessageBox( NULL, TEXT("�o�b�N�o�b�t�@�̎擾�Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// �����_�[�^�[�Q�b�g�r���[�̍쐬
    if ( FAILED( m_pD3DDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pRenderTargetView ) ) )
    {
		MessageBox( NULL, TEXT("�����_�[�^�[�Q�b�g�r���[�쐬�Ɏ��s"), TEXT("ERROR"), MB_OK );
		pBackBuffer->Release();
		return false;
	}
	pBackBuffer->Release();		// �擾�����o�b�N�o�b�t�@�����

    // �[�x�X�e���V���p�e�N�X�`���̍\���̂�������
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory( &descDepth, sizeof(descDepth) );
    descDepth.Width = clientWidth;								// �e�N�X�`���̕�
    descDepth.Height = clientHeight;							// �e�N�X�`���̍���
    descDepth.MipLevels = 1;									// �~�b�v�}�b�v���x��
    descDepth.ArraySize = 1;									// �e�N�X�`���̔z��v�f��
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;			// �t�H�[�}�b�g
    descDepth.SampleDesc = desc;								// �}���`�T���v�����O
    descDepth.Usage = D3D11_USAGE_DEFAULT;						// �e�N�X�`���̓ǂݍ��݁A�������ݕ��@
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;				// �e�N�X�`����[�x�X�e���V���^�[�Q�b�g�Ƃ��ăo�C���h
    descDepth.CPUAccessFlags = 0;								// �b�o�t�A�N�Z�X�̎��
    descDepth.MiscFlags = 0;									// ���\�[�X�I�v�V���������ʂ���t���O
	
	// �[�x�X�e���V���p�e�N�X�`���𐶐�
    if ( FAILED( m_pD3DDevice->CreateTexture2D( &descDepth, NULL, &m_pDepthStencil ) ) )
    {
		MessageBox( NULL, TEXT("�[�x�X�e���V���e�N�X�`���쐬�Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

    // �[�x�X�e���V���r���[�̍\���̂̏�����
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory( &descDSV, sizeof(descDSV) );
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
    descDSV.Texture2D.MipSlice = 0;

	// �[�x�X�e���V���r���[�𐶐�
    if ( FAILED( m_pD3DDevice->CreateDepthStencilView( m_pDepthStencil, &descDSV, &m_pDepthStencilView ) ) )
    {
		MessageBox( NULL, TEXT("�[�x�X�e���V���r���[�쐬�Ɏ��s"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// �����_�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���f�o�C�X�R���e�L�X�g�ɐݒ�
    m_pDeviceContext->OMSetRenderTargets( 1, &m_pRenderTargetView, m_pDepthStencilView );

    // �r���[�|�[�g�̐ݒ�
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)clientWidth;
    vp.Height = (FLOAT)clientHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

	// �r���[�|�[�g���f�o�C�X�R���e�L�X�g�ɐݒ�
    m_pDeviceContext->RSSetViewports( 1, &vp );

	return true;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F�R�����X�e�[�g, �X�v���C�g�o�b�`, �X�v���C�g�t�H���g�̐���
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_DirectX::InitDirectXTK()
{
	m_pStates.reset( new DirectX::CommonStates( m_pD3DDevice ) );
	m_pSprite.reset( new DirectX::SpriteBatch( m_pDeviceContext ) );
	m_pFont.reset( new DirectX::SpriteFont( m_pD3DDevice, TEXT("interface/font/italic.spritefont") ) );
	
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F�e�����o�ϐ����m�ۂ������������������
��P����	�F�|
�ԋp�l		�F�|

*************************************************************************/
void C_DirectX::Cleanup()
{
	// DXGI�̉��
	if ( m_pDXGIFactory ) m_pDXGIFactory->Release();
	if ( m_pDXGIAdapter ) m_pDXGIAdapter->Release();
	if ( m_pDXGIDevice ) m_pDXGIDevice->Release();

	// �[�x�X�e���V���̉��
	if ( m_pDepthStencil ) m_pDepthStencil->Release();
	if ( m_pDepthStencilView ) m_pDepthStencilView->Release();

	// �`��ɌW���I�u�W�F�N�g�̉��
	if ( m_pRenderTargetView ) m_pRenderTargetView->Release();
	if ( m_pSwapChain ) m_pSwapChain->Release();
	if ( m_pDeviceContext ) m_pDeviceContext->Release();

	// DirectX�f�o�C�X�̉��
	if ( m_pD3DDevice ) m_pD3DDevice->Release();
}


/*������������������������������������������������������ �ȉ��Q�b�^�[ ��������������������������������������������������������*/


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�FDirect3D�f�o�C�X���擾����
��P����	�F�|
�ԋp�l		�FDirect3D�f�o�C�X�̃A�h���X���

*************************************************************************/
ID3D11Device* C_DirectX::GetD3DDevice(){
	return m_pD3DDevice;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F�f�o�C�X�R���e�X�g�̎擾
��P����	�F�|
�ԋp�l		�F�f�o�C�X�R���e�L�X�g�̃A�h���X���

*************************************************************************/
ID3D11DeviceContext* C_DirectX::GetDeviceContext(){
	return m_pDeviceContext;
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F�R�����X�e�C�c�̎擾
��P����	�F�|
�ԋp�l		�F�R�����X�e�[�g�̃A�h���X���

*************************************************************************/
DirectX::CommonStates* C_DirectX::GetCommonState(){
	return m_pStates.get();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F�X�v���C�g�o�b�`�̎擾
��P����	�F�|
�ԋp�l		�F�X�v���C�g�o�b�`�̃A�h���X���

*************************************************************************/
DirectX::SpriteBatch* C_DirectX::GetSpriteBatch(){
	return m_pSprite.get();
}


/*************************************************************************

�쐬��		�F�݁@���j
�ŏI�X�V��	�F2013/12/04
�p�r		�F�X�v���C�g�t�H���g�̎擾
��P����	�F�|
�ԋp�l		�F�X�v���C�g�t�H���g�̃A�h���X���

*************************************************************************/
DirectX::SpriteFont* C_DirectX::GetSpriteFont(){
	return m_pFont.get();
}


