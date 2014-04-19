//////////////////////////////////////////////////////
//
//	詳細		：DirectXクラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2013/12/04
//
//////////////////////////////////////////////////////
#include "DirectX.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：メンバ変数の初期化
第１引数	：－
返却値		：－

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

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：終了処理を呼び出す
第１引数	：－
返却値		：－

*************************************************************************/
C_DirectX::~C_DirectX()
{
	Finalize();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：DirectXデバイスの生成、その周辺の設定
第１引数	：現在のウィンドウハンドル
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_DirectX::Initialize( HWND hWnd )
{
    RECT rc;
	// クライアント領域のサイズを取得する
    GetClientRect( hWnd, &rc );
    UINT width = rc.right - rc.left;			// ウィンドウ幅
    UINT height = rc.bottom - rc.top;			// ウィンドウ高さ

    // DirectXデバイスの作成( 後述 )
	if ( !CreateDirectX11Device() ) return false;

	// 使用可能なマルチサンプルを取得
	// ( DirectXデバイスを使用するため必ずDirectXデバイス作成後に記述 )
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

	// DXGI の初期化( 後述 )
	if ( !InitDXGI() ) return false;

	// スワップチェインの作成( 後述 )
	// (本当はスワップチェインもDXGIの部類なんだけどまぁいいか)
	if ( !CreateSwapChain( hWnd, SampleDesc, width, height ) ) return false;

	// 描画に関する情報の初期化( 後述 )
	if ( !InitRendering( SampleDesc, width, height ) ) return false;

	// DirectXTK の初期化( 後述 )
	InitDirectXTK();

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：解放処理を呼び出す
第１引数	：－
返却値		：－

*************************************************************************/
void C_DirectX::Finalize()
{
	Cleanup();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：画面のリセットとスワップを行う
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_DirectX::Update()
{
	// バックバッファとフロントバッファをスワップ(入れ替え)する
	if ( FAILED( m_pSwapChain->Present( 0, 0 ) ) )
	{
		MessageBox( NULL, TEXT("バッファのスワップに失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// 画面のクリア
	m_pDeviceContext->ClearRenderTargetView( m_pRenderTargetView, DirectX::Colors::Aquamarine );

	// 深度ステンシルバッファのクリア
	m_pDeviceContext->ClearDepthStencilView( m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：PCのスペックに合ったDirectXデバイスの生成
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_DirectX::CreateDirectX11Device()
{
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// ドライバタイプ
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,				// ハードウェアドライバ
        D3D_DRIVER_TYPE_WARP,					// ソフトウェアラスタライザ
        D3D_DRIVER_TYPE_REFERENCE,				// リファレンスラスタライザ
    };
    UINT numDriverTypes = ARRAYSIZE( driverTypes );

	// 機能レベル
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,					// DirectX11.0 の機能
        D3D_FEATURE_LEVEL_10_1,					// DirectX10.1
        D3D_FEATURE_LEVEL_10_0,					// DirectX10.0
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	// DirectX11のデバイスを作成
	for ( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes;  )
    {
        m_driverType = driverTypes[driverTypeIndex];
        if ( SUCCEEDED( D3D11CreateDevice( NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &m_pD3DDevice, &m_featureLevel, &m_pDeviceContext ) ) )
		{
			break;			// 作成に成功したら抜ける
		}
		else
		{
			// 一つ下の位のドライバで再挑戦
			++driverTypeIndex;

			// 最後まで作成に失敗したらエラー報告
			if ( driverTypeIndex == numDriverTypes )
			{
				MessageBox( NULL, TEXT("DirectXデバイスの作成に失敗"), TEXT("ERROR"), MB_OK );
				return false;
			}
		}
    }

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：DXGIデバイス, DXGIアダプタ, DXGIファクトリの取得
第１引数	：－
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_DirectX::InitDXGI()
{
	// インターフェイス取得
	if ( FAILED( m_pD3DDevice->QueryInterface( __uuidof( IDXGIDevice1 ), ( LPVOID* )&m_pDXGIDevice ) ) )
	{
		MessageBox( NULL, TEXT("DXGIデバイスの取得に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}
	// アダプター取得
    if ( FAILED( m_pDXGIDevice->GetAdapter(&m_pDXGIAdapter) ) )
    {
		MessageBox( NULL, TEXT("DXGIアダプタの取得に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}
	// ファクトリー取得
	if ( FAILED( m_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (LPVOID*)&m_pDXGIFactory) ) )
    {
		MessageBox( NULL, TEXT("DXGIファクトリの取得に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：スワップチェインを設定し、作成する
第１引数	：ウィンドウハンドル
第２引数	：マルチサンプル構造体
第３引数	：ウィンドウ幅
第４引数	：ウィンドウ高さ
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_DirectX::CreateSwapChain( HWND hWnd, DXGI_SAMPLE_DESC desc, UINT clientWidth, UINT clientHeight )
{
	// スワップチェインの構造体を初期化
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
		// 以下ディスプレイバッファの設定
    sd.BufferCount = 1;											// 枚数
    sd.BufferDesc.Width = clientWidth;							// 幅	(ウィンドウ幅でおｋ)
    sd.BufferDesc.Height = clientHeight;						// 高さ	(ウィンドウ高さでおｋ)
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// フォーマット
    sd.BufferDesc.RefreshRate.Numerator = 60;					// リフレッシュレート(分子)
    sd.BufferDesc.RefreshRate.Denominator = 1;					// リフレッシュレート(分母)		(60Hz毎で画面更新)
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;			// 使用目的	(DXGI_USAGE_RENDER_TARGET_OUTPUT はレンダターゲットとして使用)
    sd.OutputWindow = hWnd;										// 出力するウィンドウハンドル
    sd.SampleDesc = desc;										// マルチサンプル
    sd.Windowed = TRUE;											// ウィンドウモード
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;					// スワップ処理におけるオプション
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;			// <-- フルスクリーン時画面解像度を切り替える
	
	// スワップチェインの生成
	if( FAILED( m_pDXGIFactory->CreateSwapChain(m_pD3DDevice, &sd, &m_pSwapChain) ) )
	{
		MessageBox( NULL, TEXT("スワップチェイン生成に失敗"), TEXT("ERROR"), MB_OK );
        return false;
    }

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：スワップチェインを設定し、作成する
第１引数	：マルチサンプル
第２引数	：ウィンドウ幅
第３引数	：ウィンドウ高さ
返却値		：正常終了→true, 異常検知→false

*************************************************************************/
bool C_DirectX::InitRendering( DXGI_SAMPLE_DESC desc, UINT clientWidth, UINT clientHeight )
{
	
    ID3D11Texture2D* pBackBuffer = NULL;
	// バックバッファの取得
    if ( FAILED( m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer ) ) )
	{
		MessageBox( NULL, TEXT("バックバッファの取得に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// レンダーターゲットビューの作成
    if ( FAILED( m_pD3DDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pRenderTargetView ) ) )
    {
		MessageBox( NULL, TEXT("レンダーターゲットビュー作成に失敗"), TEXT("ERROR"), MB_OK );
		pBackBuffer->Release();
		return false;
	}
	pBackBuffer->Release();		// 取得したバックバッファを解放

    // 深度ステンシル用テクスチャの構造体を初期化
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory( &descDepth, sizeof(descDepth) );
    descDepth.Width = clientWidth;								// テクスチャの幅
    descDepth.Height = clientHeight;							// テクスチャの高さ
    descDepth.MipLevels = 1;									// ミップマップレベル
    descDepth.ArraySize = 1;									// テクスチャの配列要素数
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;			// フォーマット
    descDepth.SampleDesc = desc;								// マルチサンプリング
    descDepth.Usage = D3D11_USAGE_DEFAULT;						// テクスチャの読み込み、書き込み方法
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;				// テクスチャを深度ステンシルターゲットとしてバインド
    descDepth.CPUAccessFlags = 0;								// ＣＰＵアクセスの種類
    descDepth.MiscFlags = 0;									// リソースオプションを識別するフラグ
	
	// 深度ステンシル用テクスチャを生成
    if ( FAILED( m_pD3DDevice->CreateTexture2D( &descDepth, NULL, &m_pDepthStencil ) ) )
    {
		MessageBox( NULL, TEXT("深度ステンシルテクスチャ作成に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

    // 深度ステンシルビューの構造体の初期化
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory( &descDSV, sizeof(descDSV) );
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
    descDSV.Texture2D.MipSlice = 0;

	// 深度ステンシルビューを生成
    if ( FAILED( m_pD3DDevice->CreateDepthStencilView( m_pDepthStencil, &descDSV, &m_pDepthStencilView ) ) )
    {
		MessageBox( NULL, TEXT("深度ステンシルビュー作成に失敗"), TEXT("ERROR"), MB_OK );
		return false;
	}

	// レンダターゲットビューと深度ステンシルビューをデバイスコンテキストに設定
    m_pDeviceContext->OMSetRenderTargets( 1, &m_pRenderTargetView, m_pDepthStencilView );

    // ビューポートの設定
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)clientWidth;
    vp.Height = (FLOAT)clientHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

	// ビューポートをデバイスコンテキストに設定
    m_pDeviceContext->RSSetViewports( 1, &vp );

	return true;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：コモンステート, スプライトバッチ, スプライトフォントの生成
第１引数	：－
返却値		：－

*************************************************************************/
void C_DirectX::InitDirectXTK()
{
	m_pStates.reset( new DirectX::CommonStates( m_pD3DDevice ) );
	m_pSprite.reset( new DirectX::SpriteBatch( m_pDeviceContext ) );
	m_pFont.reset( new DirectX::SpriteFont( m_pD3DDevice, TEXT("interface/font/italic.spritefont") ) );
	
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：各メンバ変数が確保したメモリを解放する
第１引数	：－
返却値		：－

*************************************************************************/
void C_DirectX::Cleanup()
{
	// DXGIの解放
	if ( m_pDXGIFactory ) m_pDXGIFactory->Release();
	if ( m_pDXGIAdapter ) m_pDXGIAdapter->Release();
	if ( m_pDXGIDevice ) m_pDXGIDevice->Release();

	// 深度ステンシルの解放
	if ( m_pDepthStencil ) m_pDepthStencil->Release();
	if ( m_pDepthStencilView ) m_pDepthStencilView->Release();

	// 描画に係わるオブジェクトの解放
	if ( m_pRenderTargetView ) m_pRenderTargetView->Release();
	if ( m_pSwapChain ) m_pSwapChain->Release();
	if ( m_pDeviceContext ) m_pDeviceContext->Release();

	// DirectXデバイスの解放
	if ( m_pD3DDevice ) m_pD3DDevice->Release();
}


/*††††††††††††††††††††††††††† 以下ゲッター ††††††††††††††††††††††††††††*/


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：Direct3Dデバイスを取得する
第１引数	：－
返却値		：Direct3Dデバイスのアドレス情報

*************************************************************************/
ID3D11Device* C_DirectX::GetD3DDevice(){
	return m_pD3DDevice;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：デバイスコンテストの取得
第１引数	：－
返却値		：デバイスコンテキストのアドレス情報

*************************************************************************/
ID3D11DeviceContext* C_DirectX::GetDeviceContext(){
	return m_pDeviceContext;
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：コモンステイツの取得
第１引数	：－
返却値		：コモンステートのアドレス情報

*************************************************************************/
DirectX::CommonStates* C_DirectX::GetCommonState(){
	return m_pStates.get();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：スプライトバッチの取得
第１引数	：－
返却値		：スプライトバッチのアドレス情報

*************************************************************************/
DirectX::SpriteBatch* C_DirectX::GetSpriteBatch(){
	return m_pSprite.get();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2013/12/04
用途		：スプライトフォントの取得
第１引数	：－
返却値		：スプライトフォントのアドレス情報

*************************************************************************/
DirectX::SpriteFont* C_DirectX::GetSpriteFont(){
	return m_pFont.get();
}


