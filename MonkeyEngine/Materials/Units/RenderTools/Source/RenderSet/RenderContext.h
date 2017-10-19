#pragma once
#include "RenderToolsDLL.h"
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
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RenderSet;
		class RenderMesh;
		class RENDERTOOLS_EXPORT RenderContext : public RenderNode
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
			void Draw(ID3D11DeviceContext* d3DeviceContext);
			RenderMesh* AddMesh(std::string VertexFileName, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext);
			RenderMesh* MeshExists(std::string VertexFileName);
			bool LoadMesh(std::string _VertexFileName, RenderMesh*& _Mesh, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext);
			bool Load(VertexFormat _VertexFormat, BlendStateManager::BStates _BlendState, RasterizerStateManager::RasterStates _RasterState, DepthStencilStateManager::DSStates _DSState);
		};
	}
}
