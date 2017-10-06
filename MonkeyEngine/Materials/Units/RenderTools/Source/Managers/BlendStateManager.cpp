#include "BlendStateManager.h"

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
			for (unsigned int i = 0; i < BS_COUNT; i++)
			{
				if (m_vBlendStates[i])
				{
					m_vBlendStates[i]->Release();
					m_vBlendStates[i] = 0;
				}
			}
		}

		BlendStateManager *BlendStateManager::GetInstance()
		{
			if (!m_pInstance)
				m_pInstance = new BlendStateManager;
			return m_pInstance;
		}

		void BlendStateManager::DeleteInstance()
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}

		bool BlendStateManager::ApplyState(BStates state, ID3D11DeviceContext* d3DeviceContext)
		{
			if (state >= BS_COUNT)
				return false;

			d3DeviceContext->OMSetBlendState(m_vBlendStates[state], 0, 0xffffffff);
			m_eCurrentState = state;
			return true;
		}

		void BlendStateManager::CreateStates(ID3D11Device* d3Device)
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
			d3Device->CreateBlendState(&desc, &m_vBlendStates[BS_Default]);

			desc.RenderTarget[0].BlendEnable = TRUE;
			desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			d3Device->CreateBlendState(&desc, &m_vBlendStates[BS_Alpha]);

			desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
			desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
			d3Device->CreateBlendState(&desc, &m_vBlendStates[BS_Additive]);
		}
		ID3D11BlendState* BlendStateManager::GetState(BStates state)
		{
			return m_vBlendStates[state];
		}

		BlendStateManager::BStates BlendStateManager::GetCurrentState()
		{
			return m_eCurrentState;
		}
	}
}