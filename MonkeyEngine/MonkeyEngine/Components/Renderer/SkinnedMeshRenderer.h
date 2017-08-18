#pragma once
#include "MeshRenderer.h"
namespace MonkeyEngine
{
	namespace MEObject
	{
		class SkinnedMeshRenderer : public MeshRenderer
		{
		private:
			Skeleton m_CurrentSkeleton;
		public:
			SkinnedMeshRenderer() : MeshRenderer() {};
			~SkinnedMeshRenderer() {};

			void Draw();
			bool Load(MERenderer::BlendStateManager::BStates* m_BlendState,
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