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
			RenderMesh* MeshExists(std::string VertexFileName);
			bool LoadMesh(std::string _VertexFileName, RenderMesh*& _Mesh, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext);
		public:
			RenderContext();
			~RenderContext();
			//in: ID3D11DeviceContext*			
			//	The Current Renderer's Device Context								
			//out: void								
			//desc: Updates the InputLayout, BlendStae, Rasterizerstate, and DepthStencilState on the rendering pipeline			
			void Draw(ID3D11DeviceContext* d3DeviceContext);
			//in: string
			//	The File Name for the Mesh to Add
			//in: ID3D11Device*
			//	The current Renderer's Device
			//in: ID3D11DeviceContext*
			//	The current Renderer's DeviceContext
			//out: RenderMesh*
			//	The RenderMesh Added, or found
			//desc: Looks for a RenderMesh that is the same as the one being added
			//	If found will return that RenderMesh otherwise will create a new one
			RenderMesh* AddMesh(std::string VertexFileName, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext);
			//in: VertexFormat
			//	The VertexFormat for the InputLayout
			//out: BStates
			//	The BlendState for the BlendState
			//in: RasterStates
			//	The RasterizerState for the RasterizerState
			//in: DSStates
			//	The DepthStencilState for the DepthStencilState
			//out: bool
			//	whether it was successfully loaded or not
			//desc: Used during Scene Loading to set up the InputLayout, BlendStae, Rasterizerstate, and DepthStencilState
			bool Load(VertexFormat _VertexFormat, BlendStateManager::BStates _BlendState, RasterizerStateManager::RasterStates _RasterState, DepthStencilStateManager::DSStates _DSState);
		};
	}
}
