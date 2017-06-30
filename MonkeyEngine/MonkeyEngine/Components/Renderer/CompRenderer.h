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
		MERenderer::BlendStateManager::BStates* m_BlendState;
		MERenderer::RasterizerStateManager::RasterStates* m_RasterState;
		MERenderer::DepthStencilStateManager::DSStates* m_DSState;
		MERenderer::VERTEX* m_vVerticies;
		unsigned int* m_uiNumVerticies;
		unsigned int* m_vIndicies;
		unsigned int* m_uiNumIndicies;
		unsigned int* m_uiStartIndexLocation;
		int* m_iBaseVertexLocation;
		std::string* m_sVertexFileName;
		MERenderer::VertexFormat* m_eVertexFormat;
		std::string* m_TextureFileName; 

	public:
		CompRenderer();
		~CompRenderer();

		MERenderer::BlendStateManager::BStates* GetBlendState();
		MERenderer::RasterizerStateManager::RasterStates* GetRasterState();
		MERenderer::DepthStencilStateManager::DSStates* GetDepthStencilState();
		MERenderer::VERTEX* GetVerticies();
		unsigned int GetNumVerticies();
		unsigned int* GetIndicies();
		unsigned int GetiNumIndicies();
		unsigned int GetStartIndexLocation();
		int GetBaseVertexLocation();
		std::string GetVertexFileName();
		MERenderer::VertexFormat& GetVertexFormat();
		std::string GetTextureFileName();

		void SetBlendState(MERenderer::BlendStateManager::BStates*);
		void SetRasterState(MERenderer::RasterizerStateManager::RasterStates*);
		void SetDepthStencilState(MERenderer::DepthStencilStateManager::DSStates*);
		void SetVerticies(MERenderer::VERTEX*);
		void SetNumVerticies(unsigned int&);
		void SetIndicies(unsigned int*);
		void SetiNumIndicies(unsigned int&);
		void SetStartIndexLocation(unsigned int&);
		void SetBaseVertexLocation(int&);
		void SetVertexFileName(std::string&);
		void SetVertexFormat(MERenderer::VertexFormat&);
		void SetTextureFileName(std::string&);

	private:
		void Initialize();
	};
}

