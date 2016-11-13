#include "RasterizerStateManager.h"
#include "../Renderer.h"
namespace MERenderer
{
	RasterizerStateManager *RasterizerStateManager::m_pInstance = 0;

	RasterizerStateManager::RasterizerStateManager()
	{
		m_eCurrentState = RS_COUNT;
	}


	RasterizerStateManager::~RasterizerStateManager()
	{
	}

	RasterizerStateManager &RasterizerStateManager::GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new RasterizerStateManager;
			m_pInstance->CreateStates();
		}
		return *m_pInstance;
	}

	void RasterizerStateManager::DeleteInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	bool RasterizerStateManager::ApplyState(RasterStates state)
	{
		if (state >= RS_COUNT)
			return false;

		Renderer::m_d3DeviceContext->RSSetState(m_vRasterStates[state]);
		m_eCurrentState = state;
		return true;
	}

	void RasterizerStateManager::CreateStates()
	{
		D3D11_RASTERIZER_DESC desc;

		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_BACK;
		desc.FrontCounterClockwise = FALSE;
		desc.DepthBias = 0;
		desc.SlopeScaledDepthBias = 0.0f;
		desc.DepthBiasClamp = 0.0f;
		desc.DepthClipEnable = TRUE;
		desc.ScissorEnable = FALSE;
		desc.MultisampleEnable = FALSE;
		desc.AntialiasedLineEnable = FALSE;
		Renderer::m_d3Device->CreateRasterizerState(&desc, &m_vRasterStates[RS_Default].p);

		desc.FillMode = D3D11_FILL_WIREFRAME;
		Renderer::m_d3Device->CreateRasterizerState(&desc, &m_vRasterStates[RS_LINE].p);
		desc.FillMode = D3D11_FILL_SOLID;

		desc.FrontCounterClockwise = TRUE;
		Renderer::m_d3Device->CreateRasterizerState(&desc, &m_vRasterStates[RS_CCW].p);

		desc.CullMode = D3D11_CULL_NONE;
		Renderer::m_d3Device->CreateRasterizerState(&desc, &m_vRasterStates[RS_NOCULL].p);

	}
}
