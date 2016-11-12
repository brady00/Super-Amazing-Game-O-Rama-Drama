#include "RenderContext.h"
#include "../Containers/Mesh.h"
#include "RenderSet.h"
#include "RenderTexture.h"


namespace MERenderer
{
	RenderContext::RenderContext() : m_pMesh(nullptr), m_pRenderTextures(nullptr)
	{

	}

	RenderContext::RenderContext(Mesh* _Mesh) : m_pMesh(_Mesh), m_pRenderTextures(nullptr)
	{

	}


	RenderContext::~RenderContext()
	{

	}

	Mesh* RenderContext::GetMesh()
	{
		return m_pMesh;
	}

	void RenderContext::SetMesh(Mesh* _Mesh)
	{
		m_pMesh = _Mesh;
	}

	void RenderContext::Draw()
	{
		//context switching
		m_pRenderTextures->Draw();
	}

	bool RenderContext::AddTexture(std::string _Texture)
	{
		return true;
	}

	bool RenderContext::TextureExists(std::string _Texture)
	{
		return false;
	}

	bool RenderContext::LoadMesh(std::string _VertexFileName, std::string _TextureFileName)
	{
		return true;
	}

	ID3D11ShaderResourceView* RenderContext::LoadTexture(std::string _FileName)
	{
		return nullptr;
	}
}