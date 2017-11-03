#include "CompRenderer.h"
#include "Managers/ConstantBufferManager.h"
#include "Transform/Transform.h"

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

		std::string& CompRenderer::GetVertexFileName()
		{
			return *m_sVertexFileName;
		}
		Material& CompRenderer::GetMaterial()
		{
			return *m_Material;
		}
		void CompRenderer::SetVertexFileName(std::string& _vertFile)
		{
			m_sVertexFileName = &_vertFile;
		}
		void CompRenderer::SetMaterial(Material& mat)
		{
			*m_Material = mat;
		}

		bool CompRenderer::GetEnabled()
		{
			return m_Enabled;
		}

		void CompRenderer::SetEnabled(bool enable)
		{
			m_Enabled = enable;
		}

		void CompRenderer::Draw(ID3D11DeviceContext* d3DeviceContext)
		{

		}

		bool CompRenderer::Load(MERenderer::BlendStateManager::BStates* _BlendState,
			MERenderer::RasterizerStateManager::RasterStates* _RasterState,
			MERenderer::DepthStencilStateManager::DSStates* _DSState,
			void* _vVerticies,
			unsigned int* _uiNumVerticies,
			unsigned int* _vIndicies,
			unsigned int* _uiNumIndicies,
			unsigned int* _uiStartIndexLocation,
			int* _iBaseVertexLocation,
			std::string* _sVertexFileName,
			MERenderer::VertexFormat* _eVertexFormat,
			Material* _Material,
			Skeleton _Skeleton)
		{
			return true;
		}
	}
}