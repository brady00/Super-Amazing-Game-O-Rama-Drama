#include "RenderMesh.h"
#include "RenderTexture.h"
#include "../Managers/InputLayoutManager.h"
#include "../../../DirectXTK/Inc/WICTextureLoader.h"
#include "../../../DirectXTK/Inc/DDSTextureLoader.h"
#include "../Renderer.h"
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
		return true;
	}

	const std::string& RenderMesh::GetVertexFileName()
	{
		return m_sVertexFileName;
	}

	bool RenderMesh::AddTexture(std::string _TextureFileName)
	{
		if (!TextureExsits(_TextureFileName))
		{
			RenderTexture* _Texture;
			if (!LoadTexture(_TextureFileName, _Texture))
				return false;
			m_pRenderTextures->AddNode(_Texture);
		}
		return true;
	}

	bool RenderMesh::TextureExsits(std::string _TextureFileName)
	{
		RenderTexture* temp = (RenderTexture*)m_pRenderTextures->getHead();
		while (temp)
		{
			if (temp->GetVertexFileName() == _TextureFileName)
				return true;
			temp = (RenderTexture*)temp->GetNext();
		}
		return false;
	}

	bool RenderMesh::LoadTexture(std::string _TextureFileName, RenderTexture*& _Texture)
	{
		_Texture = new RenderTexture;
		DirectX::CreateWICTextureFromFile(Renderer::m_d3Device, _TextureFileName, nullptr, _Texture->GetDiffuseTexture());
	}
}