#pragma once
#include "../Utils/ReturnValues.h"
#include <vector>
#include <Windows.h>
#include <DirectXMath.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
namespace MERenderer
{
#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }
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
	class DebugCamera;
	using namespace DirectX;
	class Renderer
	{
	private:
		RenderSet* m_pNonTranparentObjects;
		RenderSet* m_pTransparentObjects;
		std::vector<Canvas*> m_vCanvases;
		std::vector<Camera*> m_vCameras;
		unsigned int m_uiActiveCamera;
		//debug Object
		RenderContext* m_pRenderContext;
		DebugCamera* m_pDebugCamera;
	public:
		Renderer();
		~Renderer();
		void Initialize(HWND _window, UINT _ScreenWidth, UINT _ScreenHeight);
		MEReturnValues::RETURNVALUE Update();
		void Shutdown();
		bool Register(Object* _Object);
		bool UnRegister(Object* _Object);
		static ID3D11Device* m_d3Device;
		static ID3D11DeviceContext* m_d3DeviceContext;
		static IDXGISwapChain* m_d3SwapChain;
		static ID3D11RenderTargetView* m_d3RenderTargetView;
		static ID3D11Texture2D* m_d3DepthBuffer;
		static ID3D11Texture2D* m_d3RenderTarget;
		static ID3D11DepthStencilView* m_d3DepthStencilView;
		static D3D11_VIEWPORT m_d3ViewPort;
		static IDXGIOutput* m_d3Output;
		static UINT m_uiScreenHeight;
		static UINT m_uiScreenWidth;
		static UINT m_uiScreenXPositionOffset;
		static UINT m_uiScreenYPositionOffset;
		static bool m_bFullScreen;
	};
}

