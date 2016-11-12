#include "RenderMesh.h"
#include "../Managers/InputLayoutManager.h"
namespace MERenderer
{
	RenderMesh::RenderMesh()
	{

	}

	RenderMesh::~RenderMesh()
	{

	}

	void RenderMesh::Draw()
	{

	}

	bool RenderMesh::Load(std::string _VertexFileName)
	{
		m_sVertexFileName = _VertexFileName;
	}

	const std::string& RenderMesh::GetVertexFileName()
	{
		return m_sVertexFileName;
	}
}