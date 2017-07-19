#include "BlendStateManager.h"
#include "../Renderer.h"

namespace MonkeyEngine
{
	namespace MERenderer
	{
		BlendStateManager *BlendStateManager::m_pInstance = 0;

		BlendStateManager::BlendStateManager() : m_eCurrentState(BS_COUNT)
		{

		}


		BlendStateManager::~BlendStateManager()
		{

		}

		BlendStateManager *BlendStateManager::GetInstance()
		{
			if (!m_pInstance)
			{
				m_pInstance = new BlendStateManager;
				m_pInstance->CreateStates();
			}
			return m_pInstance;
		}

		void BlendStateManager::DeleteInstance()
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}

		bool BlendStateManager::ApplyState(BStates state)
		{
			if (state >= BS_COUNT)
				return false;

			Renderer::m_d3DeviceContext->OMSetBlendState(m_vBlendStates[state], 0, 0xffffffff);
			m_eCurrentState = state;
			return true;
		}

		void BlendStateManager::CreateStates()
		{
			D3D11_BLEND_DESC desc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
			desc.AlphaToCoverageEnable = FALSE;
			desc.IndependentBlendEnable = FALSE;
			desc.RenderTarget[0].BlendEnable = FALSE;
			desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
			desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
			desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			Renderer::m_d3Device->CreateBlendState(&desc, &m_vBlendStates[BS_Default].p);

			desc.RenderTarget[0].BlendEnable = TRUE;
			desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			Renderer::m_d3Device->CreateBlendState(&desc, &m_vBlendStates[BS_Alpha].p);

			desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
			desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
			Renderer::m_d3Device->CreateBlendState(&desc, &m_vBlendStates[BS_Additive].p);
		}
		CComPtr<ID3D11BlendState > BlendStateManager::GetState(BStates state)
		{
			return m_vBlendStates[state];
		}

		BlendStateManager::BStates BlendStateManager::GetCurrentState()
		{
			return m_eCurrentState;
		}
	}
}