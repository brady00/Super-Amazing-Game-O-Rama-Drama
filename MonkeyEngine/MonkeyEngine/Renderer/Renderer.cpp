#include "Renderer.h"
#include "Managers/ConstantBufferManager.h"
#include "Managers/IndexBufferManager.h"
#include "Managers/InputLayoutManager.h"
#include "Managers/ShaderManager.h"
#include "Managers/VertexBufferManager.h"

namespace MERenderer
{
	ID3D11Device* Renderer::m_d3Device = nullptr;
	ID3D11DeviceContext* Renderer::m_d3DeviceContext = nullptr;
	IDXGISwapChain*	Renderer::m_d3SwapChain = nullptr;
	ID3D11RenderTargetView* Renderer::m_d3RenderTargetView = nullptr;
	ID3D11Texture2D* Renderer::m_d3RenderTarget = nullptr;
	ID3D11DepthStencilView* Renderer::m_d3DepthStencilState = nullptr;
	D3D11_VIEWPORT*	Renderer::m_d3ViewPort = nullptr;
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
	Renderer::Renderer() : m_pShaderManager(nullptr), m_pInputLayoutManager(nullptr), m_pVertexBufferManager(nullptr), m_pIndexBufferManager(nullptr), m_pConstantBufferManager(nullptr), m_pTransparentObjects(nullptr), m_pNonTranparentObjects(nullptr)
	{

	}


	Renderer::~Renderer()
	{

	}

	void Renderer::Initialize(HWND _window, UINT _ScreenWidth, UINT _ScreenHeight)
	{
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
		m_d3SwapChain->GetBuffer(0, __uuidof(m_d3RenderTarget), reinterpret_cast<void**>(&m_d3RenderTarget));
		m_d3Device->CreateRenderTargetView(m_d3RenderTarget, NULL, &m_d3RenderTargetView);
		m_d3SwapChain->GetDesc(&desc);
		m_d3ViewPort->Height = (FLOAT)desc.BufferDesc.Height;
		m_d3ViewPort->Width = (FLOAT)desc.BufferDesc.Width / 2;
		m_d3ViewPort->TopLeftX = 0;
		m_d3ViewPort->TopLeftY = 0;
		m_d3ViewPort->MinDepth = 0;
		m_d3ViewPort->MaxDepth = 1;
	}

	MEReturnValues::RETURNVALUE Renderer::Update()
	{
		return MEReturnValues::RENDERRETURN;
	}

	void Renderer::Shutdown()
	{

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