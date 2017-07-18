#include "DepthStencilStateManager.h"
#include "../Renderer.h"
namespace MERenderer
{
	DepthStencilStateManager *DepthStencilStateManager::m_pInstance = 0;

	DepthStencilStateManager::DepthStencilStateManager() : m_eCurrentState(DSS_COUNT)
	{

	}


	DepthStencilStateManager::~DepthStencilStateManager()
	{
	}

	DepthStencilStateManager* DepthStencilStateManager::GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new DepthStencilStateManager;
			m_pInstance->CreateStates();
		}
		return m_pInstance;
	}

	void DepthStencilStateManager::DeleteInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	bool DepthStencilStateManager::ApplyState(DSStates state)
	{
		if (state >= DSS_COUNT)
			return false;

		Renderer::m_d3DeviceContext->OMSetDepthStencilState(m_vDepthStates[state], m_vStencilRefs[state]);
		m_eCurrentState = state;
		return true;
	}

	void DepthStencilStateManager::CreateStates()
	{
		D3D11_DEPTH_STENCIL_DESC dssDesc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());
		dssDesc.DepthEnable = FALSE;
		Renderer::m_d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_NoDepth].p);
		m_vStencilRefs[DSS_NoDepth] = 0;
		dssDesc.DepthEnable = TRUE;
		Renderer::m_d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_Default].p);
		m_vStencilRefs[DSS_Default] = 0;
		dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		Renderer::m_d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_LessEqual].p);
		m_vStencilRefs[DSS_LessEqual] = 0;
		dssDesc.DepthFunc = D3D11_COMPARISON_GREATER;
		dssDesc.StencilEnable = TRUE;
		dssDesc.FrontFace.StencilPassOp = dssDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		Renderer::m_d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_DeferredLight1].p);
		m_vStencilRefs[DSS_DeferredLight1] = 0x1;
		dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dssDesc.FrontFace.StencilFunc = dssDesc.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;
		dssDesc.FrontFace.StencilPassOp = dssDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
		Renderer::m_d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_DeferredLight2].p);
		m_vStencilRefs[DSS_DeferredLight2] = 0x1;
		dssDesc.FrontFace.StencilPassOp = dssDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dssDesc.DepthEnable = FALSE;
		Renderer::m_d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_LightOutsideFinal].p);
		m_vStencilRefs[DSS_LightOutsideFinal] = 0x2;
		Renderer::m_d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_LightInsideFinal].p);
		m_vStencilRefs[DSS_LightInsideFinal] = 0x1;

	}

	DepthStencilStateManager::DSStates DepthStencilStateManager::GetCurrentState()
	{
		return m_eCurrentState;
	}
}