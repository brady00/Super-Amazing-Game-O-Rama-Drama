#include "RasterizerStateManager.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{

		RasterizerStateManager::RasterizerStateManager()
		{
			m_eCurrentState = RS_COUNT;
		}


		RasterizerStateManager::~RasterizerStateManager()
		{
			for (unsigned int i = 0; i < RS_COUNT; i++)
			{
				if (m_vRasterStates[i])
				{
					m_vRasterStates[i]->Release();
					m_vRasterStates[i] = 0;
				}
			}
		}

		RasterizerStateManager* RasterizerStateManager::GetInstance()
		{
			static RasterizerStateManager m_pInstance;
			return &m_pInstance;
		}

		bool RasterizerStateManager::ApplyState(RasterStates state, ID3D11DeviceContext* d3DeviceContext)
		{
			if (state >= RS_COUNT)
				return false;

			d3DeviceContext->RSSetState(m_vRasterStates[state]);
			m_eCurrentState = state;
			return true;
		}

		void RasterizerStateManager::CreateStates(ID3D11Device* d3Device)
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
			d3Device->CreateRasterizerState(&desc, &m_vRasterStates[RS_Default]);
			desc.FillMode = D3D11_FILL_WIREFRAME;
			d3Device->CreateRasterizerState(&desc, &m_vRasterStates[RS_LINE]);
			desc.FillMode = D3D11_FILL_SOLID;
			desc.FrontCounterClockwise = TRUE;
			d3Device->CreateRasterizerState(&desc, &m_vRasterStates[RS_CCW]);
			desc.CullMode = D3D11_CULL_NONE;
			d3Device->CreateRasterizerState(&desc, &m_vRasterStates[RS_NOCULL]);
		}

		RasterizerStateManager::RasterStates RasterizerStateManager::GetCurrentState()
		{
			return m_eCurrentState;
		}
	}
}
