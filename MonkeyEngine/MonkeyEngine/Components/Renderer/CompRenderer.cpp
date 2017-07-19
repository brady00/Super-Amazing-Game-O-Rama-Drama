#include "CompRenderer.h"
#include "../../Renderer/Managers/ConstantBufferManager.h"
#include "../Transform/Transform.h"
namespace MonkeyEngine
{
	using namespace MERenderer;
	namespace MEObject
	{
		CompRenderer::CompRenderer() :
			m_BlendState(nullptr),
			m_RasterState(nullptr),
			m_DSState(nullptr),
			m_vVerticies(nullptr),
			m_uiNumVerticies(nullptr),
			m_vIndicies(nullptr),
			m_uiNumIndicies(nullptr),
			m_uiStartIndexLocation(nullptr),
			m_iBaseVertexLocation(nullptr),
			m_sVertexFileName(nullptr),
			m_eVertexFormat(nullptr)
		{

		}

		CompRenderer::~CompRenderer()
		{

		}

		MERenderer::BlendStateManager::BStates& CompRenderer::GetBlendState()
		{
			return *m_BlendState;
		}
		MERenderer::RasterizerStateManager::RasterStates& CompRenderer::GetRasterState()
		{
			return *m_RasterState;
		}
		MERenderer::DepthStencilStateManager::DSStates& CompRenderer::GetDepthStencilState()
		{
			return *m_DSState;
		}
		MERenderer::VERTEX*& CompRenderer::GetVerticies()
		{
			return m_vVerticies;
		}
		unsigned int& CompRenderer::GetNumVerticies()
		{
			return *m_uiNumVerticies;
		}
		unsigned int*& CompRenderer::GetIndicies()
		{
			return m_vIndicies;
		}
		unsigned int& CompRenderer::GetiNumIndicies()
		{
			return *m_uiNumIndicies;
		}
		unsigned int& CompRenderer::GetStartIndexLocation()
		{
			return *m_uiStartIndexLocation;
		}
		int& CompRenderer::GetBaseVertexLocation()
		{
			return *m_iBaseVertexLocation;
		}
		std::string& CompRenderer::GetVertexFileName()
		{
			return *m_sVertexFileName;
		}
		MERenderer::VertexFormat& CompRenderer::GetVertexFormat()
		{
			return *m_eVertexFormat;
		}
		Material& CompRenderer::GetMaterial()
		{
			return *m_Material;
		}
		void CompRenderer::SetBlendState(MERenderer::BlendStateManager::BStates* _bState)
		{
			m_BlendState = _bState;
		}
		void CompRenderer::SetRasterState(MERenderer::RasterizerStateManager::RasterStates* _rState)
		{
			m_RasterState = _rState;
		}
		void CompRenderer::SetDepthStencilState(MERenderer::DepthStencilStateManager::DSStates* _DSState)
		{
			m_DSState = _DSState;
		}
		void CompRenderer::SetVerticies(MERenderer::VERTEX* _Verts)
		{
			m_vVerticies = _Verts;
		}
		void CompRenderer::SetNumVerticies(unsigned int& _numVerts)
		{
			m_uiNumVerticies = &_numVerts;
		}
		void CompRenderer::SetIndicies(unsigned int* _Indicies)
		{
			m_vIndicies = _Indicies;
		}
		void CompRenderer::SetiNumIndicies(unsigned int& _numIndicies)
		{
			m_uiNumIndicies = &_numIndicies;
		}
		void CompRenderer::SetStartIndexLocation(unsigned int& _startIndex)
		{
			m_uiStartIndexLocation = &_startIndex;
		}
		void CompRenderer::SetBaseVertexLocation(int& _baseVertex)
		{
			m_iBaseVertexLocation = &_baseVertex;
		}
		void CompRenderer::SetVertexFileName(std::string& _vertFile)
		{
			m_sVertexFileName = &_vertFile;
		}
		void CompRenderer::SetVertexFormat(MERenderer::VertexFormat& _vertFormat)
		{
			m_eVertexFormat = &_vertFormat;
		}
		void CompRenderer::SetMaterial(Material& mat)
		{
			*m_Material = mat;
		}

		void CompRenderer::Draw()
		{
			cbPerObject temp = ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().GetBufferValue();
			temp.world = GetTransform()->GetMatrix();
			ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().Update(&temp, sizeof(temp));
			ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().GetConstantBuffer();
			Renderer::m_d3DeviceContext->VSSetConstantBuffers(temp.REGISTER_SLOT, 1, &buf);
			if (!m_vIndicies)
			{
				Renderer::m_d3DeviceContext->Draw(*m_uiNumVerticies, *m_iBaseVertexLocation);
			}
			else
			{
				Renderer::m_d3DeviceContext->DrawIndexed(*m_uiNumIndicies, *m_uiStartIndexLocation, *m_iBaseVertexLocation);
			}
		}

		bool CompRenderer::Load(MERenderer::BlendStateManager::BStates* _BlendState,
			MERenderer::RasterizerStateManager::RasterStates* _RasterState,
			MERenderer::DepthStencilStateManager::DSStates* _DSState,
			MERenderer::VERTEX* _vVerticies,
			unsigned int* _uiNumVerticies,
			unsigned int* _vIndicies,
			unsigned int* _uiNumIndicies,
			unsigned int* _uiStartIndexLocation,
			int* _iBaseVertexLocation,
			std::string* _sVertexFileName,
			MERenderer::VertexFormat* _eVertexFormat,
			Material* _Material)
		{
			m_BlendState = _BlendState;
			m_RasterState = _RasterState;
			m_DSState = _DSState;
			m_vVerticies = _vVerticies;
			m_uiNumVerticies = _uiNumVerticies;
			m_vIndicies = _vIndicies;
			m_uiNumIndicies = _uiNumIndicies;
			m_uiStartIndexLocation = _uiStartIndexLocation;
			m_iBaseVertexLocation = _iBaseVertexLocation;
			m_sVertexFileName = _sVertexFileName;
			m_eVertexFormat = _eVertexFormat;
			m_Material = _Material;
			return true;
		}
	}
}