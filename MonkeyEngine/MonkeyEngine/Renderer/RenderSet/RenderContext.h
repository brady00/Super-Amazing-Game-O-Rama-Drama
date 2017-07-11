#pragma once
#include "RenderNode.h"
#include <string>
#include "../Managers/InputLayoutManager.h"
#include "../Managers/BlendStateManager.h"
#include "../Managers/RasterizerStateManager.h"
#include "../Managers/DepthStencilStateManager.h"
namespace MEFileIO
{
	class FileIO;
}
namespace MERenderer
{
	class RenderSet;
	class RenderMesh;
	class RenderContext : public RenderNode
	{
		friend class MEFileIO::FileIO;
		friend class Renderer;
	private:
		RenderSet* m_pRenderMeshes;
		VertexFormat m_VertexFormat;
		BlendStateManager::BStates m_BlendState;
		RasterizerStateManager::RasterStates m_RasterState;
		DepthStencilStateManager::DSStates m_DSState;
	public:
		RenderContext();
		~RenderContext();
		void Draw();
		RenderMesh* AddMesh(std::string VertexFileName);
		RenderMesh* MeshExists(std::string VertexFileName);
		bool LoadMesh(std::string _VertexFileName, RenderMesh*& _Mesh);
		bool Load(VertexFormat _VertexFormat, BlendStateManager::BStates _BlendState, RasterizerStateManager::RasterStates _RasterState, DepthStencilStateManager::DSStates _DSState);
	};
}

