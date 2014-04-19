//////////////////////////////////////////////////////
//
//	詳細		：DirectXクラスヘッダー
//	作成者		：岸　将史
//	最終更新日	：2013/12/17
//
//////////////////////////////////////////////////////
#pragma once
#include "Singleton.h"


class C_DirectX : public C_Singleton<C_DirectX>
{
public:
	bool Initialize( HWND hWnd );							// 初期化処理
	void Finalize();										// 終了処理
	bool Update();											// 更新処理

	/* ゲッター */
	ID3D11Device*			GetD3DDevice();					// Direct3Dデバイス
	ID3D11DeviceContext*	GetDeviceContext();				// デバイスコンテキスト
	DirectX::CommonStates*	GetCommonState();				// コモンステイツの取得
	DirectX::SpriteBatch*	GetSpriteBatch();				// スプライトの取得
	DirectX::SpriteFont*	GetSpriteFont();				// スプライトフォントの取得

private:
	friend C_Singleton<C_DirectX>;							// フレンド登録
	C_DirectX();											// コンストラクタ
	~C_DirectX();											// デストラクタ

	bool CreateDirectX11Device();							// DirectX11デバイスの作成
	bool InitDXGI();										// DXGIの初期化処理
	// スワップチェインの作成
	bool CreateSwapChain( HWND hWnd, DXGI_SAMPLE_DESC desc, UINT clientWidth, UINT clientHeight );	
	// 描画に関する初期化処理
	bool InitRendering( DXGI_SAMPLE_DESC desc, UINT clientWidth, UINT clientHeight );				
	void InitDirectXTK();									// Tool Kitでサポートされている情報の初期化
	void Cleanup();											// 解放処理

	/*↓↓ 以下メンバ変数 ↓↓*/
	std::unique_ptr<DirectX::CommonStates>	m_pStates;			// コモンステイツ
	std::unique_ptr<DirectX::SpriteBatch>	m_pSprite;			// スプライトバッチ
	std::unique_ptr<DirectX::SpriteFont>	m_pFont;			// スプライトフォント

	ID3D11Device*			m_pD3DDevice;					// Direct3Dデバイス
	ID3D11DeviceContext*	m_pDeviceContext;				// デバイスコンテキスト
	IDXGISwapChain*			m_pSwapChain;					// スワップチェイン
	ID3D11RenderTargetView*	m_pRenderTargetView;			// レンダーターゲット
	ID3D11Texture2D*		m_pDepthStencil;				// 深度ステンシル
	ID3D11DepthStencilView*	m_pDepthStencilView;			// 深度ステンシルビュー
	IDXGIDevice1*			m_pDXGIDevice;					// DXGI オブジェクト
	IDXGIAdapter*			m_pDXGIAdapter;					// DXGI アダプタ
	IDXGIFactory*			m_pDXGIFactory;					// DXGI ファクトリ

	D3D_DRIVER_TYPE			m_driverType;					// Direct3Dドライバタイプ
	D3D_FEATURE_LEVEL		m_featureLevel;					// フィーチャーレベル

};