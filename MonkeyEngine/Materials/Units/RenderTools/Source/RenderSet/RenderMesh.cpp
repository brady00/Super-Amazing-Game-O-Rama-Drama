#include "stdafx.h"
#include "RenderMesh.h"
#include "RenderTexture.h"
#include "../Managers/InputLayoutManager.h"
#include "../Containers/IndexBuffer.h"
#include "../Managers/ShaderManager.h"
#include "CriticalRegion.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		RenderMesh::RenderMesh() : m_vVerticies(nullptr), m_uiNumVerticies(0), m_vIndicies(nullptr), m_uiNumIndicies(0), m_uiStartIndexLocation(0), m_iBaseVertexLocationEditor(0), m_iBaseVertexLocationGame(0), m_pRenderTextures(nullptr), m_eVertexFormat(eVERTEX_MAX)
		{

		}

		RenderMesh::~RenderMesh()
		{
			if (m_vVerticies)
			{
				switch (m_eVertexFormat)
				{
				case MonkeyEngine::MERenderer::eVERTEX_POS:
					delete[] ((VERTEX_POS*)m_vVerticies);
					break; 
				case MonkeyEngine::MERenderer::eVERTEX_POSCOLOR:
					delete[]((VERTEX_POSCOLOR*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSTEX:
					delete[]((VERTEX_POSTEX*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSTEXCOLOR:
					delete[]((VERTEX_POSTEXCOLOR*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSNORMTEX:
					delete[]((VERTEX_POSNORMTEX*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSNORMTEXCOLOR:
					delete[]((VERTEX_POSNORMTEXCOLOR*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSNORMTANTEX:
					delete[]((VERTEX_POSNORMTANTEX*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSNORMTANTEXCOLOR:
					delete[]((VERTEX_POSNORMTANTEXCOLOR*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSBONEWEIGHT:
					delete[]((VERTEX_POSBONEWEIGHT*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSBONEWEIGHTCOLOR:
					delete[]((VERTEX_POSBONEWEIGHTCOLOR*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSBONEWEIGHTNORMTEX:
					delete[]((VERTEX_POSBONEWEIGHTNORMTEX*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSBONEWEIGHTNORMTEXCOLOR:
					delete[]((VERTEX_POSBONEWEIGHTNORMTEXCOLOR*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEX:
					delete[]((VERTEX_POSBONEWEIGHTNORMTANTEX*)m_vVerticies);
					break;
				case MonkeyEngine::MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEXCOLOR:
					delete[]((VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR*)m_vVerticies);
					break;
				default:
					break;
				}
				
				m_vVerticies = nullptr;
			}
			if (m_vIndicies)
			{
				delete[] m_vIndicies;
				m_vIndicies = nullptr;
			}
			if (m_pRenderTextures)
			{
				delete m_pRenderTextures;
				m_pRenderTextures = nullptr;
			}
		}

		void RenderMesh::Draw(ID3D11DeviceContext* d3DeviceContext)
		{
			//context switching
			//vertex buffer
			switch (m_eVertexFormat)
			{
			case MERenderer::eVERTEX_POS:
			{
				UINT Stride = sizeof(VERTEX_POS);
				UINT Offset = 0;
				ID3D11Buffer* vertbuff;
				if(RenderState::GetRenderState() == RenderState::EDITOR_RENDERING)
					vertbuff = VertexBufferManager::GetInstance()->GetPositionColorBuffer().GetVertexBuffer();
				else
					vertbuff = VertexBufferManager::GetInstance()->GetPositionBuffer().GetVertexBuffer();
				CriticalRegion::Enter(d3DeviceContext);
				d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
				CriticalRegion::Exit(d3DeviceContext);
				break;
			}
			case MERenderer::eVERTEX_POSTEX:
			{
				UINT Stride = sizeof(VERTEX_POSTEX);
				UINT Offset = 0;
				ID3D11Buffer* vertbuff;
				if (RenderState::GetRenderState() == RenderState::EDITOR_RENDERING)
					vertbuff = VertexBufferManager::GetInstance()->GetPositionTexColorBuffer().GetVertexBuffer();
				else
					vertbuff = VertexBufferManager::GetInstance()->GetPositionTexBuffer().GetVertexBuffer();
				CriticalRegion::Enter(d3DeviceContext);
				d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
				CriticalRegion::Exit(d3DeviceContext);
				break;
			}
			case MERenderer::eVERTEX_POSNORMTEX:
			{
				UINT Stride = sizeof(VERTEX_POSNORMTEX);
				UINT Offset = 0;
				ID3D11Buffer* vertbuff;
				if (RenderState::GetRenderState() == RenderState::EDITOR_RENDERING)
					vertbuff = VertexBufferManager::GetInstance()->GetPosNormTexColorBuffer().GetVertexBuffer();
				else
					vertbuff = VertexBufferManager::GetInstance()->GetPosNormTexBuffer().GetVertexBuffer();	
				CriticalRegion::Enter(d3DeviceContext);
				d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
				CriticalRegion::Exit(d3DeviceContext);
				break;
			}
			case MERenderer::eVERTEX_POSNORMTANTEX:
			{
				UINT Stride = sizeof(VERTEX_POSNORMTANTEX);
				UINT Offset = 0;
				ID3D11Buffer* vertbuff;
				if (RenderState::GetRenderState() == RenderState::EDITOR_RENDERING)
					vertbuff = VertexBufferManager::GetInstance()->GetPosNormTanTexColorBuffer().GetVertexBuffer();
				else
					vertbuff = VertexBufferManager::GetInstance()->GetPosNormTanTexBuffer().GetVertexBuffer();
				CriticalRegion::Enter(d3DeviceContext);
				d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
				CriticalRegion::Exit(d3DeviceContext);
				break;
			}
			case MERenderer::eVERTEX_POSBONEWEIGHT:
			{
				UINT Stride = sizeof(VERTEX_POSBONEWEIGHT);
				UINT Offset = 0;
				ID3D11Buffer* vertbuff;
				if (RenderState::GetRenderState() == RenderState::EDITOR_RENDERING)
					vertbuff = VertexBufferManager::GetInstance()->GetPosBoneWeightColorBuffer().GetVertexBuffer();
				else
					vertbuff = VertexBufferManager::GetInstance()->GetPosBoneWeightBuffer().GetVertexBuffer();
				CriticalRegion::Enter(d3DeviceContext);
				d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
				CriticalRegion::Exit(d3DeviceContext);
				break;
			}
			case MERenderer::eVERTEX_POSBONEWEIGHTNORMTEX:
			{
				UINT Stride = sizeof(VERTEX_POSBONEWEIGHTNORMTEX);
				UINT Offset = 0;
				ID3D11Buffer* vertbuff;
				if (RenderState::GetRenderState() == RenderState::EDITOR_RENDERING)
					vertbuff = VertexBufferManager::GetInstance()->GetPosBoneWeightNormTexColorBuffer().GetVertexBuffer();
				else
					vertbuff = VertexBufferManager::GetInstance()->GetPosBoneWeightNormTexBuffer().GetVertexBuffer();
				CriticalRegion::Enter(d3DeviceContext);
				d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
				CriticalRegion::Exit(d3DeviceContext);
				break;
			}
			case MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEX:
			{
				UINT Stride;
				UINT Offset = 0;
				ID3D11Buffer* vertbuff;
				if (RenderState::GetRenderState() == RenderState::EDITOR_RENDERING)
				{
					Stride = sizeof(VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR);
					vertbuff = VertexBufferManager::GetInstance()->GetPosBoneWeightNormTanTexColorBuffer().GetVertexBuffer();
				}
				else
				{
					Stride = sizeof(VERTEX_POSBONEWEIGHTNORMTANTEX);
					vertbuff = VertexBufferManager::GetInstance()->GetPosBoneWeightNormTanTexBuffer().GetVertexBuffer();
				}
				CriticalRegion::Enter(d3DeviceContext);
				d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
				CriticalRegion::Exit(d3DeviceContext);
				break;
			}
			default:
				break;
			}
			//index buffer
			ID3D11Buffer* indexbuff = IndexBuffer::GetInstance()->GetIndicies();
			CriticalRegion::Enter(d3DeviceContext);
			d3DeviceContext->IASetIndexBuffer(indexbuff, DXGI_FORMAT_R32_UINT, 0);
			//primitive topology
			d3DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			//shaders
			d3DeviceContext->VSSetShader(ShaderManager::GetInstance()->GetVertexShader((ShaderManager::VertexShaderType)m_eVertexFormat), 0, 0);
			d3DeviceContext->PSSetShader(ShaderManager::GetInstance()->GetPixelShader(ShaderManager::PixelShaderType::eShader_PS_TEXTURE_GBUFFER_BUMP), 0, 0);
			CriticalRegion::Exit(d3DeviceContext);
			//d3DeviceContext->GSSetShader(ShaderManager::GetInstance()->GetGeometryShader((ShaderManager::ShaderType)m_eVertexFormat), 0, 0);
			//d3DeviceContext->DSSetShader(ShaderManager::GetInstance()->GetDomainShader((ShaderManager::ShaderType)m_eVertexFormat), 0, 0);
			//d3DeviceContext->HSSetShader(ShaderManager::GetInstance()->GetHullShader((ShaderManager::ShaderType)m_eVertexFormat), 0, 0);
			m_pRenderTextures->Draw(d3DeviceContext);
		}

		bool RenderMesh::Load(std::string _VertexFileName, VertexFormat& _VertexFormat, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext)
		{
			m_sVertexFileName = _VertexFileName;
			std::string tempfilename(&m_sVertexFileName[m_sVertexFileName.length() - 4]);
			if (tempfilename == ".obj" || tempfilename == ".OBJ")
				m_eVertexFormat = _VertexFormat = MERenderer::eVERTEX_POSNORMTEX;
			else if (tempfilename == ".fbx" || tempfilename == ".FBX")
				m_eVertexFormat = _VertexFormat = MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEX;
			return true;
		}

		const std::string& RenderMesh::GetVertexFileName()
		{
			return m_sVertexFileName;
		}

		RenderTexture* RenderMesh::AddTexture(std::string _TextureFileName, ID3D11Device* d3Device)
		{
			RenderTexture* _Texture = TextureExsits(_TextureFileName);
			if (_Texture == nullptr)
			{
				LoadTexture(_TextureFileName, _Texture, d3Device);
				m_pRenderTextures->AddNode(_Texture);
			}
			return _Texture;
		}

		RenderTexture* RenderMesh::TextureExsits(std::string _TextureFileName)
		{
			if (m_pRenderTextures == nullptr)
			{
				m_pRenderTextures = new RenderSet;
				return nullptr;
			}
			RenderTexture* temp = (RenderTexture*)m_pRenderTextures->getHead();
			while (temp)
			{
				if (temp->GetTextureFileName() == _TextureFileName)
					return temp;
				temp = (RenderTexture*)temp->GetNext();
			}
			return nullptr;
		}

		bool RenderMesh::LoadTexture(std::string _TextureFileName, RenderTexture*& _Texture, ID3D11Device* d3Device)
		{
			_Texture = new RenderTexture;
			if (!temp_Material)
			{
				temp_Material = new Material();
				temp_Material->mDiffuseMapName = _TextureFileName;
			}
			return _Texture->Load(temp_Material, d3Device);
		}
	}
}