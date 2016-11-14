#include "RenderMesh.h"
#include "RenderTexture.h"
#include "../Managers/InputLayoutManager.h"
#include "../../Utils/FileExporter.h"
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
		//context switching
		//vertex buffer
		//index buffer
		//shaders
		m_pRenderTextures->Draw();
	}

	bool RenderMesh::Load(std::string _VertexFileName)
	{
		m_sVertexFileName = _VertexFileName;
		std::string tempfilename(&m_sVertexFileName[m_sVertexFileName.length() - 3]);
		if (tempfilename == ".obj" || tempfilename == ".OBJ")
			return MEExporter::FileExporter::LoadOBJ(m_sVertexFileName, m_vVerticies, m_uiNumVerticies, m_vIndicies, m_uiNumIndicies);
		else if (tempfilename == ".fbx" || tempfilename == ".FBX")
			return MEExporter::FileExporter::LoadFBX(m_sVertexFileName, m_vVerticies, m_uiNumVerticies, m_vIndicies, m_uiNumIndicies);
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
			if (temp->GetTextureFileName() == _TextureFileName)
				return true;
			temp = (RenderTexture*)temp->GetNext();
		}
		return false;
	}

	bool RenderMesh::LoadTexture(std::string _TextureFileName, RenderTexture*& _Texture)
	{
		_Texture = new RenderTexture;
		return _Texture->Load(_TextureFileName);
	}

	const VERTEX* RenderMesh::GetVerticies()
	{
		return m_vVerticies;
	}

	const unsigned int* RenderMesh::GetIndicies()
	{
		return m_vIndicies;
	}

	const unsigned int RenderMesh::RenderMesh::GetNumVerticies()
	{
		return m_uiNumVerticies;
	}

	const unsigned int RenderMesh::GetNumIndicies()
	{
		return m_uiNumIndicies;
	}

	const unsigned int RenderMesh::GetStartIndexLocation()
	{
		return m_uiStartIndexLocation;
	}

	const int RenderMesh::GetBaseVertexLocation()
	{
		return m_iBaseVertexLocation;
	}
}