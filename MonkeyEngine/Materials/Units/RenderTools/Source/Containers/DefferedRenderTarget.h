#pragma once
#include "RenderToolsDLL.h"
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }
		class RENDERTOOLS_EXPORT DefferedRenderTarget
		{
		private:
			ID3D11Texture2D* m_d3GbufferTarget[2];
			ID3D11RenderTargetView* m_d3GBufferTargetView[2];
			ID3D11ShaderResourceView* m_d3GBufferShaderView[2];
			const unsigned int m_uiBufferCount = 2;
			UINT m_uiStartVert;
			ID3D11SamplerState*			m_d3SamplerState;
		public:
			DefferedRenderTarget();
			~DefferedRenderTarget();
			//in: ID3D11Device*
			//	The current Renderer's Device
			//in: ID3D11DeviceContext*
			//	The current Renderer's DeviceContext
			//in: UINT
			//	The Width of the Screen
			//in: UINT
			//	The Height of the Screen
			//out: void
			//desc: Creates the necessasry D3D Objects to render to a texture
			void Initialize(ID3D11Device* _Device, ID3D11DeviceContext* d3DeviceContext, UINT _ScreenHeight, UINT _ScreenWidth);
			//in: void
			//out: void
			//desc: Draws the 2D texture to the screen
			void Update(ID3D11DeviceContext* d3DeviceContext);
			//in: void
			//out: void
			//desc: Cleans up all D3D memory
			void Shutdown();
			//in: ID3D11Device*
			//	The current Renderer's Device
			//in: UINT
			//	The Width of the Screen
			//in: UINT
			//	The Height of the Screen
			//out: void
			//desc: Reinitalizes with the new ScreenHeight and ScreenWidth
			void ResizeBuffers(ID3D11Device* _Device, UINT _ScreenHeight, UINT _ScreenWidth);
			//in: ID3D11DepthStencilView*
			//	The current Renderer's DepthStencilView
			//in: ID3D11DeviceContext*
			//	The Width of the Screen
			//out: void
			//desc: Sets the D3D Objects to make this the RenderTarget of the Graphics Pipeline
			void SetAsRenderTarget(ID3D11DepthStencilView* _StencilView, ID3D11DeviceContext* _DeviceContext);
		};
	}
}
