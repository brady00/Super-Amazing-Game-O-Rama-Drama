#include "MeshRenderer.h"
#include "Managers/ConstantBufferManager.h"
#include "Transform/Transform.h"
#include "Behaviour/Animation.h"
namespace MonkeyEngine
{
	namespace MEObject
	{
		REGISTER_CLASS("MeshRenderer", MeshRenderer)
		void MeshRenderer::Draw(ID3D11DeviceContext* d3DeviceContext)
		{
			cbPerObject temp = ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().GetBufferValue();
			temp.world = GetTransform()->GetMatrix();
			ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().Update(&temp, sizeof(temp), d3DeviceContext);
			ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().GetConstantBuffer();
			d3DeviceContext->VSSetConstantBuffers(temp.REGISTER_SLOT, 1, &buf);
			if (!m_vIndicies)
				d3DeviceContext->Draw(*m_uiNumVerticies, *m_iBaseVertexLocation);
			else
				d3DeviceContext->DrawIndexed(*m_uiNumIndicies, *m_uiStartIndexLocation, *m_iBaseVertexLocation);
		}

		bool MeshRenderer::Load(MERenderer::BlendStateManager::BStates* _BlendState,
			MERenderer::RasterizerStateManager::RasterStates* _RasterState,
			MERenderer::DepthStencilStateManager::DSStates* _DSState,
			void* _vVerticies,
			unsigned int* _uiNumVerticies,
			unsigned int* _vIndicies,
			unsigned int* _uiNumIndicies,
			unsigned int* _uiStartIndexLocation,
			int* _iBaseVertexLocation,
			std::string* _sVertexFileName,
			MERenderer::VertexFormat* _eVertexFormat,
			Material* _Material,
			Skeleton _Skelton)
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
			return true;
		}
	}
}