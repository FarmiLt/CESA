//////////////////////////////////////////////////////
//
//	�ڍ�		�FDirectX�N���X�w�b�_�[
//	�쐬��		�F�݁@���j
//	�ŏI�X�V��	�F2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"


class C_DirectX : public C_Singleton<C_DirectX>
{
public:
	bool Initialize( HWND hWnd );							// ����������
	void Finalize();										// �I������
	bool Update();											// �X�V����

	/* �Q�b�^�[ */
	ID3D11Device*			GetD3DDevice();					// Direct3D�f�o�C�X
	ID3D11DeviceContext*	GetDeviceContext();				// �f�o�C�X�R���e�L�X�g
	DirectX::CommonStates*	GetCommonState();				// �R�����X�e�C�c�̎擾
	DirectX::SpriteBatch*	GetSpriteBatch();				// �X�v���C�g�̎擾
	DirectX::SpriteFont*	GetSpriteFont();				// �X�v���C�g�t�H���g�̎擾

private:
	friend C_Singleton<C_DirectX>;							// �t�����h�o�^
	C_DirectX();											// �R���X�g���N�^
	~C_DirectX();											// �f�X�g���N�^

	bool CreateDirectX11Device();							// DirectX11�f�o�C�X�̍쐬
	bool InitDXGI();										// DXGI�̏���������
	// �X���b�v�`�F�C���̍쐬
	bool CreateSwapChain( HWND hWnd, DXGI_SAMPLE_DESC desc, UINT clientWidth, UINT clientHeight );	
	// �`��Ɋւ��鏉��������
	bool InitRendering( DXGI_SAMPLE_DESC desc, UINT clientWidth, UINT clientHeight );				
	void InitDirectXTK();									// Tool Kit�ŃT�|�[�g����Ă�����̏�����
	void Cleanup();											// �������

	/*���� �ȉ������o�ϐ� ����*/
	std::unique_ptr<DirectX::CommonStates>	m_pStates;			// �R�����X�e�C�c
	std::unique_ptr<DirectX::SpriteBatch>	m_pSprite;			// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteFont>	m_pFont;			// �X�v���C�g�t�H���g

	ID3D11Device*			m_pD3DDevice;					// Direct3D�f�o�C�X
	ID3D11DeviceContext*	m_pDeviceContext;				// �f�o�C�X�R���e�L�X�g
	IDXGISwapChain*			m_pSwapChain;					// �X���b�v�`�F�C��
	ID3D11RenderTargetView*	m_pRenderTargetView;			// �����_�[�^�[�Q�b�g
	ID3D11Texture2D*		m_pDepthStencil;				// �[�x�X�e���V��
	ID3D11DepthStencilView*	m_pDepthStencilView;			// �[�x�X�e���V���r���[
	IDXGIDevice1*			m_pDXGIDevice;					// DXGI �I�u�W�F�N�g
	IDXGIAdapter*			m_pDXGIAdapter;					// DXGI �A�_�v�^
	IDXGIFactory*			m_pDXGIFactory;					// DXGI �t�@�N�g��

	D3D_DRIVER_TYPE			m_driverType;					// Direct3D�h���C�o�^�C�v
	D3D_FEATURE_LEVEL		m_featureLevel;					// �t�B�[�`���[���x��

};