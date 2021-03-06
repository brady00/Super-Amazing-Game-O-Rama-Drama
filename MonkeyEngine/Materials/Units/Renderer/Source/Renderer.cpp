#include "Renderer.h"
#include "RenderSet\RenderSet.h"
#include "Managers\ConstantBufferManager.h"
#include "Containers\DefferedRenderTarget.h"
#include "RenderSet\RenderContext.h"
#include "CriticalRegion.h"
#include "Managers\ShaderManager.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		ID3D11Device* Renderer::m_d3Device = nullptr;
		ID3D11DeviceContext* Renderer::m_d3DeviceContext;
		IDXGISwapChain*	Renderer::m_d3SwapChain = nullptr;
		ID3D11RenderTargetView* Renderer::m_d3BackBufferTargetView = nullptr;
		ID3D11Texture2D* Renderer::m_d3DepthBuffer = nullptr;
		ID3D11DepthStencilView* Renderer::m_d3DepthStencilView = nullptr;
		D3D11_VIEWPORT	Renderer::m_d3ViewPort;
		IDXGIOutput* Renderer::m_d3Output = nullptr;
		//Skybox* Renderer::m_pSkybox = nullptr;
		RenderSet* Renderer::m_pTransparentObjects = nullptr;
		RenderSet* Renderer::m_pNonTranparentObjects = nullptr;
		UINT Renderer::m_uiScreenHeight = 0;
		UINT Renderer::m_uiScreenWidth = 0;
		UINT Renderer::m_uiScreenXPositionOffset = 0;
		UINT Renderer::m_uiScreenYPositionOffset = 0;
		std::vector<Camera*> Renderer::m_vCameras;
		unsigned int Renderer::m_ActiveCamera = 0;
		Camera* Renderer::m_DebugCamera = nullptr;
#ifdef _DEBUG
		bool Renderer::m_bFullScreen = false;
#else
		bool Renderer::m_bFullScreen = true;

#endif
		Renderer::Renderer()
		{

		}


		Renderer::~Renderer()
		{

		}

		void Renderer::Initialize(HWND _window, UINT _ScreenWidth, UINT _ScreenHeight)
		{
			m_uiScreenHeight = _ScreenHeight;
			m_uiScreenWidth = _ScreenWidth;
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
			CriticalRegion::Enter(m_d3DeviceContext);
			D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, flags, NULL, NULL, D3D11_SDK_VERSION, &desc, &m_d3SwapChain, &m_d3Device, NULL, &m_d3DeviceContext);
			m_d3SwapChain->GetBuffer(0, __uuidof(BackBuffer), reinterpret_cast<void**>(&BackBuffer));
			m_d3Device->CreateRenderTargetView(BackBuffer, NULL, &m_d3BackBufferTargetView);
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
			CriticalRegion::Exit(m_d3DeviceContext);

			m_pSceneTarget = new DefferedRenderTarget;
			m_pSceneTarget->Initialize(m_d3Device, m_d3DeviceContext, _ScreenHeight, _ScreenWidth);
			BlendStateManager::GetInstance()->CreateStates(m_d3Device);
			ConstantBufferManager::GetInstance()->CreateBuffers(m_d3Device);
			DepthStencilStateManager::GetInstance()->CreateStates(m_d3Device);
			InputLayoutManager::GetInstance()->CreateLayouts(m_d3Device);
			RasterizerStateManager::GetInstance()->CreateStates(m_d3Device);
			ShaderManager::GetInstance()->CreateShaders(m_d3Device);
		}

		void Renderer::Resize(UINT _ScreenWidth, UINT _ScreenHeight)
		{
			m_uiScreenHeight = _ScreenHeight;
			m_uiScreenWidth = _ScreenWidth;
			// Back Buffer
			if (m_d3BackBufferTargetView != nullptr)
				m_d3BackBufferTargetView->Release();

			m_d3SwapChain->ResizeBuffers(1, _ScreenWidth, _ScreenHeight, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
			ID3D11Resource* resource;
			m_d3SwapChain->GetBuffer(0, __uuidof(resource), (void**)(&resource));
			m_d3Device->CreateRenderTargetView(resource, NULL, &m_d3BackBufferTargetView);
			resource->Release();

			// Viewport
			ZeroMemory(&m_d3ViewPort, sizeof(D3D11_VIEWPORT));
			m_d3ViewPort.Width = (FLOAT)_ScreenWidth;
			m_d3ViewPort.Height = (FLOAT)_ScreenHeight;
			m_d3ViewPort.TopLeftX = 0.0f;
			m_d3ViewPort.TopLeftY = 0.0f;
			m_d3ViewPort.MinDepth = 0.0f;
			m_d3ViewPort.MaxDepth = 1.0f;

			// Depth Buffer
			if (m_d3DepthBuffer != nullptr)
				m_d3DepthBuffer->Release();

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

			// Render Target
			m_pSceneTarget->ResizeBuffers(m_d3Device, _ScreenHeight, _ScreenWidth);
		}

		void Renderer::Update()
		{
			float color[4] = { 0,0,0,0 };
			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);
			float DeltaTime = (float)(double(li.QuadPart - m_dPrevFrame) / 10000.0);
			m_dPrevFrame = li.QuadPart;
			if (false)
				m_fFPS = 1.0f / DeltaTime;
			CriticalRegion::Enter(m_d3DeviceContext);
			m_d3DeviceContext->RSSetViewports(1, &m_d3ViewPort);
			m_pSceneTarget->SetAsRenderTarget(GetDepthStencilView(), GetDeviceContext());
			m_pSceneTarget->Clear(GetDeviceContext(), color);
			m_d3DeviceContext->ClearDepthStencilView(m_d3DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
			m_pNonTranparentObjects->Draw(m_d3DeviceContext);
			m_pTransparentObjects->Draw(m_d3DeviceContext);
			//draw lights
			//draw skybox
			if (RenderState::GetRenderState() == RenderState::EDITOR_RENDERING)
				m_DebugCamera->GetSkybox()->Draw(m_d3DeviceContext);
			else
			{
				m_vCameras[m_ActiveCamera]->Draw(m_d3DeviceContext);
				m_vCameras[m_ActiveCamera]->GetSkybox()->Draw(m_d3DeviceContext);
			}
			//draw lights			//set backbuffer
			CriticalRegion::Enter(m_d3DeviceContext);
			m_d3DeviceContext->ClearDepthStencilView(m_d3DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
			m_d3DeviceContext->OMSetRenderTargets(1, &m_d3BackBufferTargetView, m_d3DepthStencilView);
			m_d3DeviceContext->ClearRenderTargetView(m_d3BackBufferTargetView, color);
			CriticalRegion::Exit(m_d3DeviceContext);

			//draw quad
			m_pSceneTarget->Update(m_d3DeviceContext);
			m_d3SwapChain->Present(0, 0);
		}

		void Renderer::Reset()
		{
			m_pNonTranparentObjects->Clear();
			m_pTransparentObjects->Clear();
		}

		void Renderer::Shutdown()
		{
			//delete m_pSkybox;
			delete m_pNonTranparentObjects;
			delete m_pTransparentObjects;
			m_pSceneTarget->Shutdown();
			delete m_pSceneTarget;
			ReleaseCOM(m_d3Device);
			ReleaseCOM(m_d3DeviceContext);
			ReleaseCOM(m_d3SwapChain);
			ReleaseCOM(m_d3DepthBuffer);
			ReleaseCOM(m_d3BackBufferTargetView);
			ReleaseCOM(m_d3DepthStencilView);
			ReleaseCOM(m_d3Output);
		}

		RenderContext* Renderer::AddNewTransparentContext(RenderContext*& _context)
		{
			RenderContext* temp = (RenderContext*)m_pTransparentObjects->getHead();
			while (temp->GetNext())
			{
				if (temp->m_BlendState == _context->m_BlendState &&
					temp->m_DSState == _context->m_DSState &&
					temp->m_RasterState == _context->m_RasterState &&
					temp->m_VertexFormat == _context->m_VertexFormat)
				{
					delete _context;
					_context = nullptr;
					return temp;
				}
				temp = (RenderContext*)temp->GetNext();
			}
			if (temp->m_BlendState == _context->m_BlendState &&
				temp->m_DSState == _context->m_DSState &&
				temp->m_RasterState == _context->m_RasterState &&
				temp->m_VertexFormat == _context->m_VertexFormat)
			{
				delete _context;
				_context = nullptr;
				return temp;
			}
			temp->SetNext(_context);
			return _context;
		}

		RenderContext* Renderer::AddNewnonTransparentContext(RenderContext*& _context)
		{
			RenderContext* temp = (RenderContext*)m_pNonTranparentObjects->getHead();
			if (!temp)
			{
				m_pNonTranparentObjects->AddNode(_context);
				return _context;
			}
			while (temp->GetNext())
			{
				if (temp->m_BlendState == _context->m_BlendState &&
					temp->m_DSState == _context->m_DSState &&
					temp->m_RasterState == _context->m_RasterState &&
					temp->m_VertexFormat == _context->m_VertexFormat)
				{
					delete _context;
					_context = nullptr;
					return temp;
				}
				temp = (RenderContext*)temp->GetNext();
			}
			if (temp->m_BlendState == _context->m_BlendState &&
				temp->m_DSState == _context->m_DSState &&
				temp->m_RasterState == _context->m_RasterState &&
				temp->m_VertexFormat == _context->m_VertexFormat)
			{
				delete _context;
				_context = nullptr;
				return temp;
			}
			m_pNonTranparentObjects->AddNode(_context);
			return _context;
		}

		ID3D11Device* Renderer::GetDevice()
		{
			return m_d3Device;
		}

		ID3D11DeviceContext* Renderer::GetDeviceContext()
		{
			return m_d3DeviceContext;
		}

		IDXGISwapChain*	Renderer::GetSwapChain()
		{
			return m_d3SwapChain;
		}

		ID3D11RenderTargetView* Renderer::GetBackBufferTargetView()
		{
			return m_d3BackBufferTargetView;
		}

		ID3D11Texture2D* Renderer::GetDepthBuffer()
		{
			return m_d3DepthBuffer;
		}

		ID3D11DepthStencilView* Renderer::GetDepthStencilView()
		{
			return m_d3DepthStencilView;
		}

		D3D11_VIEWPORT Renderer::GetViewPort()
		{
			return m_d3ViewPort;
		}

		IDXGIOutput* Renderer::GetOutput()
		{
			return m_d3Output;
		}

		UINT Renderer::GetScreenHeight()
		{
			return m_uiScreenHeight;
		}

		UINT Renderer::GetScreenWidth()
		{
			return m_uiScreenWidth;
		}

		UINT Renderer::GetScreenXPositionOffset()
		{
			return m_uiScreenXPositionOffset;
		}

		UINT Renderer::GetScreenYPositionOffset()
		{
			return m_uiScreenYPositionOffset;
		}

		bool Renderer::GetFullScreen()
		{
			return m_bFullScreen;
		}

		std::vector<Camera*>& Renderer::GetCameras()
		{
			return m_vCameras;
		}

		void Renderer::SetActiveCamera(unsigned int index)
		{
			m_ActiveCamera = index;
		}

		void Renderer::SetDebugCamera(Camera* cam)
		{
			m_DebugCamera = cam;
		}

	}
}