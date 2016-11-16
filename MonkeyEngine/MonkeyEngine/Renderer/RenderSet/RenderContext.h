#pragma once
#include "RenderNode.h"
#include <string>
#include "../Managers/InputLayoutManager.h"
namespace MERenderer
{
	class RenderSet;
	class RenderMesh;
	class RenderContext : public RenderNode
	{
	private:
		RenderSet* m_pRenderMeshes;
	public:
		RenderContext();
		~RenderContext();
		void Draw();
		RenderMesh* AddMesh(std::string VertexFileName, VertexFormat _VertexFormat);
		RenderMesh* MeshExists(std::string VertexFileName);
		bool LoadMesh(std::string _VertexFileName, RenderMesh*& _Mesh, VertexFormat _VertexFormat);
	};
}

