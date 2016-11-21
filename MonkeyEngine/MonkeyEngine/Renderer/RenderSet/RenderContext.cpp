#include "RenderContext.h"
#include "RenderMesh.h"
#include "RenderSet.h"



namespace MERenderer
{
	RenderContext::RenderContext() : m_pRenderMeshes(nullptr), m_VertexFormat(eVERTEX_MAX), m_BlendState(BlendStateManager::BS_Default), m_RasterState(RasterizerStateManager::RS_Default), m_DSState(DepthStencilStateManager::DSS_Default)
	{

	}

	RenderContext::~RenderContext()
	{

	}

	void RenderContext::Draw()
	{
		//context switching
		//input layout
		Renderer::m_d3DeviceContext->IASetInputLayout(InputLayoutManager::GetInstance()->GetInputLayout(m_VertexFormat));
		//blend state
		BlendStateManager::GetInstance()->ApplyState(m_BlendState);
		//rasterizer
		RasterizerStateManager::GetInstance()->ApplyState(m_RasterState);
		//depthbuffer
		DepthStencilStateManager::GetInstance()->ApplyState(m_DSState);
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
		if (m_pRenderMeshes == nullptr)
		{
			m_pRenderMeshes = new RenderSet;
			return nullptr;
		}
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

	bool RenderContext::Load(VertexFormat _VertexFormat, BlendStateManager::BStates _BlendState, RasterizerStateManager::RasterStates _RasterState, DepthStencilStateManager::DSStates _DSState)
	{
		m_VertexFormat = _VertexFormat;
		m_BlendState = _BlendState;
		m_RasterState = _RasterState;
		m_DSState = _DSState;
		return true;
	}
}