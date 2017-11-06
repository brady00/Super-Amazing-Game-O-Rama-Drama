#pragma once
#include "MemoryOverloads.h"
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
			//in: HWND
			//	The Window to Render too
			//in: UINT
			//	The Width of the Screen
			//in: UINT
			//	The Height of the Screen
			//out: void
			//desc: Gets the D3D Vertex Buffer used for drawing
			void Initialize(HWND _window, UINT _ScreenWidth, UINT _ScreenHeight);
			//in: HWND
			//	The Window to Render too
			//in: UINT
			//	The Width of the Screen
			//in: UINT
			//	The Height of the Screen
			//out: void
			//desc: Gets the D3D Vertex Buffer used for drawing
			void Resize(UINT _ScreenWidth, UINT _ScreenHeight);
			//in: void
			//out: void
			//desc: Renders all objects to the Screen
			void Update();
			//in: void
			//out: void
			//desc: Cleans up all D3D Memory
			void Shutdown();
			//in: void
			//out: void
			//desc: Clears all rendersets to refresh the Objects that are rendering
			static void Reset();
			//in: void
			//out: ID3D11Device*
			//	The Current Renderer's Device
			//desc: Gets the Current Renderer's Device
			static ID3D11Device* GetDevice();
			//in: void
			//out: ID3D11DeviceContext*
			//	The Current Renderer's DeviceContext
			//desc: Gets the Current Renderer's DeviceContext
			static ID3D11DeviceContext* GetDeviceContext();
			//in: void
			//out: ID3D11SwapChain*
			//	The Current Renderer's SwapChain
			//desc: Gets the Current Renderer's SwapChain
			static IDXGISwapChain* GetSwapChain();
			//in: void
			//out: ID3D11RenderTargetView*
			//	The Current Renderer's BackBufferTargetView
			//desc: Gets the Current Renderer's BackBufferTargetView
			static ID3D11RenderTargetView* GetBackBufferTargetView();
			//in: void
			//out: ID3D11Texture2D*
			//	The Current Renderer's DepthBuffer
			//desc: Gets the Current Renderer's DepthBuffer
			static ID3D11Texture2D* GetDepthBuffer();
			//in: void
			//out: ID3D11DepthStencilView*
			//	The Current Renderer's DepthStencilView
			//desc: Gets the Current Renderer's DepthStencilView
			static ID3D11DepthStencilView* GetDepthStencilView();
			//in: void
			//out: D3D11_VIEWPORT
			//	The Current Renderer's Viewport
			//desc: Gets the Current Renderer's Viewport
			static D3D11_VIEWPORT GetViewPort();
			//in: void
			//out: IDXGIOutput*
			//	The Current Renderer's Output
			//desc: Gets the Current Renderer's Output
			static IDXGIOutput* GetOutput();
			//in: void
			//out: UINT
			//	The Screen Height
			//desc: Gets the Current Screen Height
			static UINT GetScreenHeight();
			//in: void
			//out: UINT
			//	The Screen Width
			//desc: Gets the Current Screen Width
			static UINT GetScreenWidth();
			//in: void
			//out: UINT
			//	The x offset of the Window
			//desc: Gets the x offset of the Window
			static UINT GetScreenXPositionOffset();
			//in: void
			//out: UINT
			//	The y offset of the Window
			//desc: Gets the y offset of the Window
			static UINT GetScreenYPositionOffset();
			//in: void
			//out: bool
			//	Whether fullscreen or not
			//desc: Gets whether fullscreen or not
			static bool GetFullScreen();
			//in: RenderContext*&
			//	The RenderContext to add to the Transparent Objects list
			//out: RenderContext*
			//	If the RenderContext that was added
			//desc: If the RenderContext is already in the list that RenderContext will be returned
			//	otherwise the RenderContext passed will be returned
			static RenderContext* AddNewTransparentContext(RenderContext*& _context);
			//in: RenderContext*&
			//	The RenderContext to add to the Non-Transparent Objects list
			//out: RenderContext*
			//	If the RenderContext that was added
			//desc: If the RenderContext is already in the list that RenderContext will be returned
			//	otherwise the RenderContext passed will be returned
			static RenderContext* AddNewnonTransparentContext(RenderContext*& _context);
			//in: void
			//out: vector<Camera*>&
			//	The list of Cameras in the Scene
			//desc: Gets the list of Cameras in the Scene
			static std::vector<Camera*>& GetCameras();
			//in: unsigned int
			//	Index of the new Active Camera
			//out: void
			//desc: Sets the index for the Active Camera
			static void SetActiveCamera(unsigned int index);
			//in: Camera*
			//	The DebugCamera
			//out: void
			//desc: Sets the Debug Camera for the Renderer to use
			static void SetDebugCamera(Camera* cam);
		};
	}
}
