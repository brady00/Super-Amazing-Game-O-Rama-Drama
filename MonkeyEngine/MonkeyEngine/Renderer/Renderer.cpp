#include "Renderer.h"
#include "RenderSet\RenderSet.h"
#include "RenderSet\RenderContext.h"
#include "RenderSet\RenderMesh.h"
#include "RenderSet\RenderTexture.h"
#include "Managers\ConstantBufferManager.h"
#include "DebugCamera\DebugCamera.h"

namespace MERenderer
{
	ID3D11Device* Renderer::m_d3Device = nullptr;
	ID3D11DeviceContext* Renderer::m_d3DeviceContext = nullptr;
	IDXGISwapChain*	Renderer::m_d3SwapChain = nullptr;
	ID3D11RenderTargetView* Renderer::m_d3RenderTargetView = nullptr;
	ID3D11Texture2D* Renderer::m_d3RenderTarget = nullptr;
	ID3D11Texture2D* Renderer::m_d3DepthBuffer = nullptr;
	ID3D11DepthStencilView* Renderer::m_d3DepthStencilView = nullptr;
	D3D11_VIEWPORT	Renderer::m_d3ViewPort;
	IDXGIOutput* Renderer::m_d3Output = nullptr;
	UINT Renderer::m_uiScreenHeight = 0;
	UINT Renderer::m_uiScreenWidth = 0;
	UINT Renderer::m_uiScreenXPositionOffset = 0;
	UINT Renderer::m_uiScreenYPositionOffset = 0;
#ifdef _DEBUG
	bool Renderer::m_bFullScreen = false;
#else
	bool Renderer::m_bFullScreen = true;

#endif
	Renderer::Renderer() : m_pTransparentObjects(nullptr), m_pNonTranparentObjects(nullptr)
	{

	}


	Renderer::~Renderer()
	{

	}

	void Renderer::Initialize(HWND _window, UINT _ScreenWidth, UINT _ScreenHeight)
	{
		ID3D11Texture2D* BackBuffer;
		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BufferCount = 1;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		desc.BufferDesc.RefreshRate = { 1, 60 };
		desc.BufferDesc.Height = _ScreenHeight;
		desc.BufferDesc.Width = _ScreenWidth;
		desc.SampleDesc.Count = 1;
		desc.OutputWindow = _window;
		desc.Windowed = !m_bFullScreen;
#ifdef _DEBUG
		UINT flags = D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_DEBUG;
#else
		UINT flags = NULL;
#endif
		D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, flags, NULL, NULL, D3D11_SDK_VERSION, &desc, &m_d3SwapChain, &m_d3Device, NULL, &m_d3DeviceContext);
		m_d3SwapChain->GetBuffer(0, __uuidof(BackBuffer), reinterpret_cast<void**>(&BackBuffer));
		m_d3Device->CreateRenderTargetView(BackBuffer, NULL, &m_d3RenderTargetView);
		BackBuffer->Release();
		BackBuffer = nullptr;
		m_d3SwapChain->GetDesc(&desc);
		m_d3ViewPort.Height = (FLOAT)desc.BufferDesc.Height;
		m_d3ViewPort.Width = (FLOAT)desc.BufferDesc.Width;
		m_d3ViewPort.TopLeftX = 0.0f;
		m_d3ViewPort.TopLeftY = 0.0f;
		m_d3ViewPort.MinDepth = 0.0f;
		m_d3ViewPort.MaxDepth = 1.0f;
		m_pNonTranparentObjects = new RenderSet;
		m_pTransparentObjects = new RenderSet;
		m_pRenderContext = new RenderContext;
		ConstantBufferManager::GetInstance()->CreateBuffers();

		D3D11_TEXTURE2D_DESC depthBufferDesc;
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthBufferDesc.Width = _ScreenWidth;
		depthBufferDesc.Height = _ScreenHeight;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.MipLevels = 1;
		m_d3Device->CreateTexture2D(&depthBufferDesc, 0, &m_d3DepthBuffer);

		D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;
		ZeroMemory(&depthViewDesc, sizeof(depthViewDesc));
		depthViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthViewDesc.Texture2D.MipSlice = 0;
		m_d3Device->CreateDepthStencilView(m_d3DepthBuffer, &depthViewDesc, &m_d3DepthStencilView);

		//test code
		m_pRenderContext->Load(VertexFormat::eVERTEX_POSNORMTEX, BlendStateManager::BS_Alpha, RasterizerStateManager::RS_NOCULL, DepthStencilStateManager::DSS_Default);
		RenderMesh* tempMesh = m_pRenderContext->AddMesh("Assets/testObj.obj", VertexFormat::eVERTEX_POSNORMTEX);
		RenderTexture* tempTex = tempMesh->AddTexture("Assets/images.png");
		tempTex->AddShape(nullptr, nullptr);
		m_pDebugCamera = new DebugCamera;
		m_pDebugCamera->Initialize(XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), 0.1f, 999999.9f, 90.0f, (float)_ScreenHeight, (float)_ScreenWidth);
	}

	MEReturnValues::RETURNVALUE Renderer::Update()
	{
		float color[] = { 0,0,1,1 };
		m_d3DeviceContext->RSSetViewports(1, &m_d3ViewPort);
		m_d3DeviceContext->OMSetRenderTargets(1, &m_d3RenderTargetView, m_d3DepthStencilView);
		m_d3DeviceContext->ClearRenderTargetView(m_d3RenderTargetView, color);
		m_d3DeviceContext->ClearDepthStencilView(m_d3DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		m_pDebugCamera->Update();
		m_pNonTranparentObjects->Draw();
		m_pTransparentObjects->Draw();
		m_pRenderContext->Draw();
		m_d3SwapChain->Present(0, 0);
		return MEReturnValues::RENDERRETURN;
	}

	void Renderer::Shutdown()
	{
		delete m_pRenderContext;
		delete m_pNonTranparentObjects;
		delete m_pTransparentObjects;
		ReleaseCOM(m_d3Device);
		ReleaseCOM(m_d3DeviceContext);
		ReleaseCOM(m_d3SwapChain);
		ReleaseCOM(m_d3DepthBuffer);
		ReleaseCOM(m_d3RenderTargetView);
		ReleaseCOM(m_d3RenderTarget);
		ReleaseCOM(m_d3DepthStencilView);
		ReleaseCOM(m_d3Output);
	}

	bool Renderer::Register(Object* _Object)
	{
		return true;
	}

	bool Renderer::UnRegister(Object* _Object)
	{
		return true;
	}
}