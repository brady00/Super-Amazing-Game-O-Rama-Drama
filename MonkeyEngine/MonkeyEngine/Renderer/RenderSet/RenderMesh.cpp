#include "RenderMesh.h"
#include "RenderTexture.h"
#include "../Managers/InputLayoutManager.h"
#include "../../Utils/FileExporter.h"
#include "../Containers/IndexBuffer.h"
#include "../Managers/ShaderManager.h"
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
		switch (m_eVertexFormat)
		{
		case MERenderer::eVERTEX_POS:
			UINT Stride = sizeof(VERTEX_POS);
			UINT Offset = 0;
			ID3D11Buffer* vertbuff = VertexBufferManager::GetInstance()->GetPositionBuffer().GetVertexBuffer();
			Renderer::m_d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
			break;
		case MERenderer::eVERTEX_POSCOLOR:
			UINT Stride = sizeof(VERTEX_POSCOLOR);
			UINT Offset = 0;
			ID3D11Buffer* vertbuff = VertexBufferManager::GetInstance()->GetPositionColorBuffer().GetVertexBuffer();
			Renderer::m_d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
			break;
		case MERenderer::eVERTEX_POSTEX:
			UINT Stride = sizeof(VERTEX_POSTEX);
			UINT Offset = 0;
			ID3D11Buffer* vertbuff = VertexBufferManager::GetInstance()->GetPositionTexBuffer().GetVertexBuffer();
			Renderer::m_d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
			break;
		case MERenderer::eVERTEX_POSNORMTEX:
			UINT Stride = sizeof(VERTEX_POSNORMTEX);
			UINT Offset = 0;
			ID3D11Buffer* vertbuff = VertexBufferManager::GetInstance()->GetPosNormTexBuffer().GetVertexBuffer();
			Renderer::m_d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
			break;
		case MERenderer::eVERTEX_POSNORMTANTEX:
			UINT Stride = sizeof(VERTEX_POSNORMTANTEX);
			UINT Offset = 0;
			ID3D11Buffer* vertbuff = VertexBufferManager::GetInstance()->GetPosNormTanTexBuffer().GetVertexBuffer();
			Renderer::m_d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
			break;
		case MERenderer::eVERTEX_POSBONEWEIGHT:
			UINT Stride = sizeof(VERTEX_POSBONEWEIGHT);
			UINT Offset = 0;
			ID3D11Buffer* vertbuff = VertexBufferManager::GetInstance()->GetPosBoneWeightBuffer().GetVertexBuffer();
			Renderer::m_d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
			break;
		case MERenderer::eVERTEX_POSBONEWEIGHTNORMTEX:
			UINT Stride = sizeof(VERTEX_POSBONEWEIGHTNORMTEX);
			UINT Offset = 0;
			ID3D11Buffer* vertbuff = VertexBufferManager::GetInstance()->GetPosBoneWeightNormTexBuffer().GetVertexBuffer();
			Renderer::m_d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
			break;
		case MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEX:
			UINT Stride = sizeof(VERTEX_POSBONEWEIGHTNORMTANTEX);
			UINT Offset = 0;
			ID3D11Buffer* vertbuff = VertexBufferManager::GetInstance()->GetPosBoneWeightNormTanTexBuffer().GetVertexBuffer();
			Renderer::m_d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
			break;
		default:
			break;
		}
		//index buffer
		ID3D11Buffer* indexbuff = IndexBuffer::GetInstance()->GetIndicies();
		Renderer::m_d3DeviceContext->IASetIndexBuffer(indexbuff, DXGI_FORMAT_R32_UINT, 0);

		//primitive topology
		Renderer::m_d3DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_pRenderTextures->Draw();
	}

	bool RenderMesh::Load(std::string _VertexFileName, VertexFormat _VertexFormat)
	{
		m_sVertexFileName = _VertexFileName;
		std::string tempfilename(&m_sVertexFileName[m_sVertexFileName.length() - 3]);
		if (tempfilename == ".obj" || tempfilename == ".OBJ")
		{
			if (!MEExporter::FileExporter::LoadOBJ(m_sVertexFileName, m_eVertexFormat, m_vVerticies, m_uiNumVerticies, m_vIndicies, m_uiNumIndicies))
				return false;
		}
		else if (tempfilename == ".fbx" || tempfilename == ".FBX")
		{
			if (!MEExporter::FileExporter::LoadFBX(m_sVertexFileName, m_eVertexFormat, m_vVerticies, m_uiNumVerticies, m_vIndicies, m_uiNumIndicies))
				return false;
		}
		switch (m_eVertexFormat)
		{
		case MERenderer::eVERTEX_POS:
			m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPositionBuffer().AddVerts((VERTEX_POS*)m_vVerticies, m_uiNumVerticies);
			break;
		case MERenderer::eVERTEX_POSCOLOR:
			m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPositionColorBuffer().AddVerts((VERTEX_POSCOLOR*)m_vVerticies, m_uiNumVerticies);
			break;
		case MERenderer::eVERTEX_POSTEX:
			m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPositionTexBuffer().AddVerts((VERTEX_POSTEX*)m_vVerticies, m_uiNumVerticies);
			break;
		case MERenderer::eVERTEX_POSNORMTEX:
			m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosNormTexBuffer().AddVerts((VERTEX_POSNORMTEX*)m_vVerticies, m_uiNumVerticies);
			break;
		case MERenderer::eVERTEX_POSNORMTANTEX:
			m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosNormTanTexBuffer().AddVerts((VERTEX_POSNORMTANTEX*)m_vVerticies, m_uiNumVerticies);
			break;
		case MERenderer::eVERTEX_POSBONEWEIGHT:
			m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightBuffer().AddVerts((VERTEX_POSBONEWEIGHT*)m_vVerticies, m_uiNumVerticies);
			break;
		case MERenderer::eVERTEX_POSBONEWEIGHTNORMTEX:
			m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightNormTexBuffer().AddVerts((VERTEX_POSBONEWEIGHTNORMTEX*)m_vVerticies, m_uiNumVerticies);
			break;
		case MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEX:
			m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightNormTanTexBuffer().AddVerts((VERTEX_POSBONEWEIGHTNORMTANTEX*)m_vVerticies, m_uiNumVerticies);
			break;
		default:
			break;
		}
		IndexBuffer::GetInstance()->AddIndicies(m_vIndicies, m_uiNumIndicies);
	}

	const std::string& RenderMesh::GetVertexFileName()
	{
		return m_sVertexFileName;
	}

	RenderTexture* RenderMesh::AddTexture(std::string _TextureFileName)
	{
		RenderTexture* _Texture = TextureExsits(_TextureFileName);
		if (_Texture == nullptr)
		{
			LoadTexture(_TextureFileName, _Texture);
			m_pRenderTextures->AddNode(_Texture);
		}
		return _Texture;
	}

	RenderTexture* RenderMesh::TextureExsits(std::string _TextureFileName)
	{
		RenderTexture* temp = (RenderTexture*)m_pRenderTextures->getHead();
		while (temp)
		{
			if (temp->GetTextureFileName() == _TextureFileName)
				return temp;
			temp = (RenderTexture*)temp->GetNext();
		}
		return nullptr;
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

	const VertexFormat RenderMesh::GetVertexFormat()
	{
		return m_eVertexFormat;
	}
}