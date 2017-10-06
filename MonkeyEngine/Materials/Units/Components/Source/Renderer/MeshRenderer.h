#pragma once
#include "CompRenderer.h"
#include "../Transform/Transform.h"
namespace MonkeyEngine
{
	using namespace MERenderer;
	namespace MEObject
	{
		class MeshRenderer : public CompRenderer
		{
		private:

		public:
			MeshRenderer() { m_sName = "MeshRenderer"; };
			~MeshRenderer() {};

			virtual void Draw(ID3D11DeviceContext* d3DeviceContext);
			virtual bool Load(MERenderer::BlendStateManager::BStates* m_BlendState,
				MERenderer::RasterizerStateManager::RasterStates* m_RasterState,
				MERenderer::DepthStencilStateManager::DSStates* m_DSState,
				MERenderer::VERTEX* m_vVerticies,
				unsigned int* m_uiNumVerticies,
				unsigned int* m_vIndicies,
				unsigned int* m_uiNumIndicies,
				unsigned int* m_uiStartIndexLocation,
				int* m_iBaseVertexLocation,
				std::string* m_sVertexFileName,
				MERenderer::VertexFormat* m_eVertexFormat,
				Material* _Material,
				Skeleton _Skeleton);
		};
	}
}