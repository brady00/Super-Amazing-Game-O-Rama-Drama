#pragma once
#include <vector>
#include <Windows.h>
#include <DirectXMath.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Utilities.lib")

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
		class Camera;
		class RenderContext;
		class DefferedRenderTarget;
		using namespace DirectX;

		class Renderer
		{
		private:
			//static Skybox* m_pSkybox;
			static RenderSet* m_pNonTranparentObjects;
			static RenderSet* m_pTransparentObjects;
			//std::vector<Canvas*> m_vCanvases;
			//std::vector<Camera*> m_vCameras;
			XMFLOAT4X4 m_DebugCameraViewMatrix;
			unsigned int m_uiActiveCamera;
			DefferedRenderTarget* m_pDeferredRenderTarget;
			__int64	m_dPrevFrame = 0;
			float m_fFPS = 0.0f;
		public:
			Renderer();
			~Renderer();
			void Initialize(HWND _window, UINT _ScreenWidth, UINT _ScreenHeight);
			void Resize(UINT _ScreenWidth, UINT _ScreenHeight);
			void Update();
			void Shutdown();
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
			static RenderContext* AddNewTransparentContext(RenderContext*& _context);
			static RenderContext* AddNewnonTransparentContext(RenderContext*& _context);
		};
	}
}
