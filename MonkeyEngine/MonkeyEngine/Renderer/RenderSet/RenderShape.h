#pragma once
#include "RenderNode.h"
#include <DirectXMath.h>
#include "../../Renderer/Managers/InputLayoutManager.h"
#include "../../Renderer/Managers/BlendStateManager.h"
#include "../../Renderer/Managers/RasterizerStateManager.h"
#include "../../Renderer/Managers/DepthStencilStateManager.h"
#include "../../Renderer/Managers/VertexBufferManager.h"
#include "../../Renderer/Containers/Material.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RenderShape : public RenderNode
		{
		public:
			RenderShape() {};
			~RenderShape() {};
			virtual void Draw() {};
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
				Material* _Material) {
				return false;
			};
		};


	}
}