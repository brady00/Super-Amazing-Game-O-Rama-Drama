#pragma once
#include "RenderNode.h"
#include <string>
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
		bool AddMesh(std::string VertexFileName);
		bool MeshExists(std::string VertexFileName);
		bool LoadMesh(std::string _VertexFileName, RenderMesh*& _Mesh);
	};
}

