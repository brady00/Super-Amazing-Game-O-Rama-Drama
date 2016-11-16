#include "RenderContext.h"
#include "RenderMesh.h"
#include "RenderSet.h"
#include "../Managers/InputLayoutManager.h"
#include "../Managers/BlendStateManager.h"
#include "../Managers/RasterizerStateManager.h"
#include "../Managers/DepthStencilStateManager.h"


namespace MERenderer
{
	RenderContext::RenderContext() :m_pRenderMeshes(nullptr)
	{

	}

	RenderContext::~RenderContext()
	{

	}

	void RenderContext::Draw()
	{
		//context switching
		//input layout
		InputLayoutManager::GetInstance()->GetInputLayout(eVERTEX_POSNORMTEX);
		//blend state
		BlendStateManager::GetInstance()->ApplyState(BlendStateManager::BS_Default);
		//rasterizer
		RasterizerStateManager::GetInstance()->ApplyState(RasterizerStateManager::RS_Default);
		//depthbuffer
		DepthStencilStateManager::GetInstance()->ApplyState(DepthStencilStateManager::DSS_Default);
		m_pRenderMeshes->Draw();
	}

	RenderMesh* RenderContext::AddMesh(std::string VertexFileName, VertexFormat _VertexFormat)
	{
		RenderMesh* _Mesh = MeshExists(VertexFileName);
		if (_Mesh == nullptr)
		{
			LoadMesh(VertexFileName, _Mesh, _VertexFormat);
			m_pRenderMeshes->AddNode(_Mesh);
		}
		return _Mesh;
	}

	RenderMesh* RenderContext::MeshExists(std::string _VertexFileName)
	{
		RenderMesh* temp = (RenderMesh*)m_pRenderMeshes->getHead();
		while (temp)
		{
			if (temp->GetVertexFileName() == _VertexFileName)
				return temp;
			temp = (RenderMesh*)temp->GetNext();
		}
		return nullptr;
	}

	bool RenderContext::LoadMesh(std::string _VertexFileName, RenderMesh*& _Mesh, VertexFormat _VertexFormat)
	{
		_Mesh = new RenderMesh;
		return _Mesh->Load(_VertexFileName, _VertexFormat);
	}
}