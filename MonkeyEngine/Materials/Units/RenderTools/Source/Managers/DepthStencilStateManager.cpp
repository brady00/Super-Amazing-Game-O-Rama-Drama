#include "DepthStencilStateManager.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{

		DepthStencilStateManager::DepthStencilStateManager() : m_eCurrentState(DSS_COUNT)
		{

		}


		DepthStencilStateManager::~DepthStencilStateManager()
		{
			for (unsigned int i = 0; i < DSS_COUNT; i++)
			{
				if (m_vDepthStates[i])
				{
					m_vDepthStates[i]->Release();
					m_vDepthStates[i] = 0;
				}
			}
		}

		DepthStencilStateManager* DepthStencilStateManager::GetInstance()
		{
			static DepthStencilStateManager	m_pInstance;
			return &m_pInstance;
		}

		bool DepthStencilStateManager::ApplyState(DSStates state, ID3D11DeviceContext* d3DeviceContext)
		{
			if (state >= DSS_COUNT)
				return false;

			d3DeviceContext->OMSetDepthStencilState(m_vDepthStates[state], m_vStencilRefs[state]);
			m_eCurrentState = state;
			return true;
		}

		void DepthStencilStateManager::CreateStates(ID3D11Device* d3Device)
		{
			D3D11_DEPTH_STENCIL_DESC dssDesc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());
			dssDesc.DepthEnable = FALSE;
			d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_NoDepth]);
			m_vStencilRefs[DSS_NoDepth] = 0;
			dssDesc.DepthEnable = TRUE;
			d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_Default]);
			m_vStencilRefs[DSS_Default] = 0;
			dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_LessEqual]);
			m_vStencilRefs[DSS_LessEqual] = 0;
			dssDesc.DepthFunc = D3D11_COMPARISON_GREATER;
			dssDesc.StencilEnable = TRUE;
			dssDesc.FrontFace.StencilPassOp = dssDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
			dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
			d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_DeferredLight1]);
			m_vStencilRefs[DSS_DeferredLight1] = 0x1;
			dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			dssDesc.FrontFace.StencilFunc = dssDesc.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;
			dssDesc.FrontFace.StencilPassOp = dssDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
			d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_DeferredLight2]);
			m_vStencilRefs[DSS_DeferredLight2] = 0x1;
			dssDesc.FrontFace.StencilPassOp = dssDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			dssDesc.DepthEnable = FALSE;
			d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_LightOutsideFinal]);
			m_vStencilRefs[DSS_LightOutsideFinal] = 0x2;
			d3Device->CreateDepthStencilState(&dssDesc, &m_vDepthStates[DSS_LightInsideFinal]);
			m_vStencilRefs[DSS_LightInsideFinal] = 0x1;

		}

		DepthStencilStateManager::DSStates DepthStencilStateManager::GetCurrentState()
		{
			return m_eCurrentState;
		}
	}
}