#pragma once
#include <d3d11.h>
namespace MERenderer
{
#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }
	class DefferedRenderTarget
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

		void Initialize(ID3D11Device* _Device, UINT _ScreenHeight, UINT _ScreenWidth);
		void Update();
		void Shutdown();

		void SetAsRenderTarget(ID3D11DepthStencilView* _StencilView, ID3D11DeviceContext* _DeviceContext);
	};
}

