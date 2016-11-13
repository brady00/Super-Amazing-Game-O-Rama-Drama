#include "RenderContext.h"
#include "RenderMesh.h"
#include "RenderSet.h"


namespace MERenderer
{
	RenderContext::RenderContext() :m_pRenderMeshes(nullptr)
	{

	}

	RenderContext::RenderContext() : m_pRenderMeshes(nullptr)
	{

	}


	RenderContext::~RenderContext()
	{

	}

	void RenderContext::Draw()
	{
		//context switching
		//input layout
		//blend state
		//rasterizer
		//depthbuffer
		m_pRenderMeshes->Draw();
	}

	bool RenderContext::AddMesh(std::string VertexFileName)
	{
		if (!MeshExists(VertexFileName))
		{
			RenderMesh* _Mesh;
			if (!LoadMesh(VertexFileName, _Mesh))
				return false;
			m_pRenderMeshes->AddNode(_Mesh);
		}
		return true;
	}

	bool RenderContext::MeshExists(std::string _VertexFileName)
	{
		RenderMesh* temp = (RenderMesh*)m_pRenderMeshes->getHead();
		while (temp)
		{
			if (temp->GetVertexFileName() == _VertexFileName)
				return true;
			temp = (RenderMesh*)temp->GetNext();
		}
		return false;
	}

	bool RenderContext::LoadMesh(std::string _VertexFileName, RenderMesh*& _Mesh)
	{
		_Mesh = new RenderMesh;
		_Mesh->Load(_VertexFileName);
	}
}