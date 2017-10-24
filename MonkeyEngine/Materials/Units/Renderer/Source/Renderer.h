#pragma once
#include <vector>
#include <Windows.h>
#pragma warning(disable: 4793)
#include <DirectXMath.h>
#include <d3d11.h>
#include "Behaviour\Camera.h"
#pragma comment(lib, "d3d11.lib")
namespace MonkeyEngine
{
	namespace MERenderer
	{
#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }
		class Skybox;
		class RenderSet;
		class Canvas;
		class ShaderManager;
		class InputLayoutManager;
		class VertexBufferManager;
		class IndexBufferManager;
		class ConstantBufferManager;
		class Object;
		class RenderContext;
		class DefferedRenderTarget;
		using namespace DirectX;

		class __declspec(dllexport) Renderer
		{
		private:
			//static Skybox* m_pSkybox;
			static RenderSet* m_pNonTranparentObjects;
			static RenderSet* m_pTransparentObjects;
			//std::vector<Canvas*> m_vCanvases;
			static std::vector<MEObject::Camera*> m_vCameras;
			static unsigned int m_ActiveCamera;
			static Camera* m_DebugCamera;
			XMFLOAT4X4 m_DebugCameraViewMatrix;
			DefferedRenderTarget* m_pDeferredRenderTarget;
			__int64	m_dPrevFrame = 0;
			float m_fFPS = 0.0f;
			static ID3D11Device* m_d3Device;
			static ID3D11DeviceContext* m_d3DeviceContext;
			static IDXGISwapChain* m_d3SwapChain;
			static ID3D11RenderTargetView* m_d3BackBufferTargetView;
			static ID3D11Texture2D* m_d3DepthBuffer;
			static ID3D11DepthStencilView* m_d3DepthStencilView;
			static D3D11_VIEWPORT m_d3ViewPort;
			static IDXGIOutput* m_d3Output;
			static UINT m_uiScreenHeight;
			static UINT m_uiScreenWidth;
			static UINT m_uiScreenXPositionOffset;
			static UINT m_uiScreenYPositionOffset;
			static bool m_bFullScreen;
		public:
			Renderer();
			~Renderer();
			void Initialize(HWND _window, UINT _ScreenWidth, UINT _ScreenHeight);
			void Resize(UINT _ScreenWidth, UINT _ScreenHeight);
			void Update();
			void Shutdown();
			static ID3D11Device* GetDevice();
			static ID3D11DeviceContext* GetDeviceContext();
			static IDXGISwapChain* GetSwapChain();
			static ID3D11RenderTargetView* GetBackBufferTargetView();
			static ID3D11Texture2D* GetDepthBuffer();
			static ID3D11DepthStencilView* GetDepthStencilView();
			static D3D11_VIEWPORT GetViewPort();
			static IDXGIOutput* GetOutput();
			static UINT GetScreenHeight();
			static UINT GetScreenWidth();
			static UINT GetScreenXPositionOffset();
			static UINT GetScreenYPositionOffset();
			static bool GetFullScreen();
			static RenderContext* AddNewTransparentContext(RenderContext*& _context);
			static RenderContext* AddNewnonTransparentContext(RenderContext*& _context);
			static std::vector<Camera*>& GetCameras();
			static void SetActiveCamera(unsigned int index);
			static void SetDebugCamera(Camera* cam);
		};
	}
}
