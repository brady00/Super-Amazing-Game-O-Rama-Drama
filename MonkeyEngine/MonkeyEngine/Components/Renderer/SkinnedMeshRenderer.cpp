#include "SkinnedMeshRenderer.h"
namespace MonkeyEngine
{
	namespace MEObject
	{
		void SkinnedMeshRenderer::Draw()
		{
			cbPerSkinnedObject temp = ConstantBufferManager::GetInstance()->GetPerSkinnedObjectCBuffer().GetBufferValue();
			temp.World = GetTransform()->GetMatrix();
			memcpy(temp.BoneMatricies, &m_CurrentSkeleton[0], m_CurrentSkeleton.size() * sizeof(XMFLOAT4X4));
			ConstantBufferManager::GetInstance()->GetPerSkinnedObjectCBuffer().Update(&temp, sizeof(temp));
			ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetPerSkinnedObjectCBuffer().GetConstantBuffer();
			Renderer::m_d3DeviceContext->VSSetConstantBuffers(temp.REGISTER_SLOT, 1, &buf);
			if (!m_vIndicies)
			{
				Renderer::m_d3DeviceContext->Draw(*m_uiNumVerticies, *m_iBaseVertexLocation);
			}
			else
			{
				Renderer::m_d3DeviceContext->DrawIndexed(*m_uiNumIndicies, *m_uiStartIndexLocation, *m_iBaseVertexLocation);
			}
		}

		bool SkinnedMeshRenderer::Load(MERenderer::BlendStateManager::BStates* _BlendState,
			MERenderer::RasterizerStateManager::RasterStates* _RasterState,
			MERenderer::DepthStencilStateManager::DSStates* _DSState,
			MERenderer::VERTEX* _vVerticies,
			unsigned int* _uiNumVerticies,
			unsigned int* _vIndicies,
			unsigned int* _uiNumIndicies,
			unsigned int* _uiStartIndexLocation,
			int* _iBaseVertexLocation,
			std::string* _sVertexFileName,
			MERenderer::VertexFormat* _eVertexFormat,
			Material* _Material,
			std::vector<XMFLOAT4X4> _CurrentSkeleton)
		{
			m_BlendState = _BlendState;
			m_RasterState = _RasterState;
			m_DSState = _DSState;
			m_vVerticies = _vVerticies;
			m_uiNumVerticies = _uiNumVerticies;
			m_vIndicies = _vIndicies;
			m_uiNumIndicies = _uiNumIndicies;
			m_uiStartIndexLocation = _uiStartIndexLocation;
			m_iBaseVertexLocation = _iBaseVertexLocation;
			m_sVertexFileName = _sVertexFileName;
			m_eVertexFormat = _eVertexFormat;
			m_Material = _Material;
			m_CurrentSkeleton = _CurrentSkeleton;
			return true;
		}
	}
}