#pragma once
#include "../Base/Component.h"
#include "../../Renderer/Managers/InputLayoutManager.h"
#include "../../Renderer/Managers/BlendStateManager.h"
#include "../../Renderer/Managers/RasterizerStateManager.h"
#include "../../Renderer/Managers/DepthStencilStateManager.h"
#include "../../Renderer/Managers/VertexBufferManager.h"
namespace MEObject
{
	class CompRenderer : public Component
	{
	private:
		MERenderer::VertexFormat* m_VertexFormat;
		MERenderer::BlendStateManager::BStates* m_BlendState;
		MERenderer::RasterizerStateManager::RasterStates* m_RasterState;
		MERenderer::DepthStencilStateManager::DSStates* m_DSState;
		MERenderer::VERTEX* m_vVerticies;
		unsigned int m_uiNumVerticies;
		unsigned int* m_vIndicies;
		unsigned int m_uiNumIndicies;
		unsigned int m_uiStartIndexLocation;
		int m_iBaseVertexLocation;
		std::string m_sVertexFileName;
		MERenderer::VertexFormat m_eVertexFormat;
		std::string m_TextureFileName; 
	public:
		CompRenderer();
		~CompRenderer();
	private:
		void Initialize();
	};
}

