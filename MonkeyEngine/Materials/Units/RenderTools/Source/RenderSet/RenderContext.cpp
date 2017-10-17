#include "RenderContext.h"
#include "RenderMesh.h"
#include "RenderSet.h"


namespace MonkeyEngine
{
	namespace MERenderer
	{
		RenderContext::RenderContext() : m_pRenderMeshes(nullptr), m_VertexFormat(eVERTEX_MAX), m_BlendState(BlendStateManager::BS_Default), m_RasterState(RasterizerStateManager::RS_Default), m_DSState(DepthStencilStateManager::DSS_Default)
		{

		}

		RenderContext::~RenderContext()
		{
			delete m_pRenderMeshes;
		}

		void RenderContext::Draw(ID3D11DeviceContext* d3DeviceContext, unsigned int State)
		{
			//context switching
			//input layout
			d3DeviceContext->IASetInputLayout(InputLayoutManager::GetInstance()->GetInputLayout(m_VertexFormat));
			//blend state
			BlendStateManager::GetInstance()->ApplyState(m_BlendState, d3DeviceContext);
			//rasterizer
			RasterizerStateManager::GetInstance()->ApplyState(m_RasterState, d3DeviceContext);
			//depthbuffer
			DepthStencilStateManager::GetInstance()->ApplyState(m_DSState, d3DeviceContext);
			m_pRenderMeshes->Draw(d3DeviceContext, State);
		}

		RenderMesh* RenderContext::AddMesh(std::string VertexFileName, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext)
		{
			RenderMesh* _Mesh = MeshExists(VertexFileName);
			if (_Mesh == nullptr)
			{
				LoadMesh(VertexFileName, _Mesh, d3Device, d3DeviceContext);
				m_pRenderMeshes->AddNode(_Mesh);
			}
			return _Mesh;
		}

		RenderMesh* RenderContext::MeshExists(std::string _VertexFileName)
		{
			if (!m_pRenderMeshes)
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

		bool RenderContext::LoadMesh(std::string _VertexFileName, RenderMesh*& _Mesh, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext)
		{
			_Mesh = new RenderMesh;
			return _Mesh->Load(_VertexFileName, m_VertexFormat, d3Device, d3DeviceContext);
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
}