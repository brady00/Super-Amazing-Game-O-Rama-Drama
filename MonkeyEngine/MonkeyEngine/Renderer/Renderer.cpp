#include "Renderer.h"
#include "RenderSet\RenderSet.h"
#include "Managers\ConstantBufferManager.h"
#include "Containers\DefferedRenderTarget.h"
#include "../Utils/MemoryManager.h"
#include "RenderSet\RenderContext.h"
#include "../Engine Base/Game Engine/MountainDew.h"
#include "DebugCamera\DebugCamera.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		ID3D11Device* Renderer::m_d3Device = nullptr;
		ID3D11DeviceContext* Renderer::m_d3DeviceContext = nullptr;
		IDXGISwapChain*	Renderer::m_d3SwapChain = nullptr;
		ID3D11RenderTargetView* Renderer::m_d3BackBufferTargetView = nullptr;
		ID3D11Texture2D* Renderer::m_d3DepthBuffer = nullptr;
		ID3D11DepthStencilView* Renderer::m_d3DepthStencilView = nullptr;
		D3D11_VIEWPORT	Renderer::m_d3ViewPort;
		IDXGIOutput* Renderer::m_d3Output = nullptr;
		RenderSet* Renderer::m_pTransparentObjects = nullptr;
		RenderSet* Renderer::m_pNonTranparentObjects = nullptr;
		UINT Renderer::m_uiScreenHeight = 0;
		UINT Renderer::m_uiScreenWidth = 0;
		UINT Renderer::m_uiScreenXPositionOffset = 0;
		UINT Renderer::m_uiScreenYPositionOffset = 0;
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

			m_pDeferredRenderTarget = new DefferedRenderTarget;
			m_pDeferredRenderTarget->Initialize(m_d3Device, _ScreenHeight, _ScreenWidth);
		}

		void Renderer::Resize(UINT _ScreenWidth, UINT _ScreenHeight)
		{
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

			// Projection Matrix
			MountainDew::GetInstance()->m_pScene->GetDebugCamera()->Resize(0.1f, 999999.9f, 90.0f, (float)_ScreenHeight, (float)_ScreenWidth);

			// Render Target
			m_pDeferredRenderTarget->Initialize(m_d3Device, _ScreenHeight, _ScreenWidth);
		}

		void Renderer::Update()
		{
			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);
			float DeltaTime = (float)(double(li.QuadPart - m_dPrevFrame) / 10000.0);
			m_dPrevFrame = li.QuadPart;
			if (false)
				m_fFPS = 1.0f / DeltaTime;
			m_d3DeviceContext->RSSetViewports(1, &m_d3ViewPort);
			m_d3DeviceContext->ClearDepthStencilView(m_d3DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
			m_pDeferredRenderTarget->SetAsRenderTarget(m_d3DepthStencilView, m_d3DeviceContext);
			m_pNonTranparentObjects->Draw();
			m_pTransparentObjects->Draw();
			//draw lights
			//set backbuffer
			float color[] = { 0,0,1,1 };
			m_d3DeviceContext->ClearDepthStencilView(m_d3DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
			m_d3DeviceContext->OMSetRenderTargets(1, &m_d3BackBufferTargetView, m_d3DepthStencilView);
			m_d3DeviceContext->ClearRenderTargetView(m_d3BackBufferTargetView, color);

			//draw quad
			m_pDeferredRenderTarget->Update();
			m_d3SwapChain->Present(0, 0);
		}

		void Renderer::Shutdown()
		{
			delete m_pNonTranparentObjects;
			delete m_pTransparentObjects;
			m_pDeferredRenderTarget->Shutdown();
			delete m_pDeferredRenderTarget;
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

	}
}