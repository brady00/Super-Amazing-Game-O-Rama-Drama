#include "CompRenderer.h"

namespace MEObject
{
	CompRenderer::CompRenderer()
	{

	}

	CompRenderer::~CompRenderer()
	{

	}

	MERenderer::BlendStateManager::BStates* CompRenderer::GetBlendState()
	{
		return m_BlendState;
	}
	MERenderer::RasterizerStateManager::RasterStates* CompRenderer::GetRasterState()
	{
		return m_RasterState;
	}
	MERenderer::DepthStencilStateManager::DSStates* CompRenderer::GetDepthStencilState()
	{
		return m_DSState;
	}
	MERenderer::VERTEX* CompRenderer::GetVerticies()
	{
		return m_vVerticies;
	}
	unsigned int CompRenderer::GetNumVerticies()
	{
		return *m_uiNumVerticies;
	}
	unsigned int* CompRenderer::GetIndicies()
	{
		return m_vIndicies;
	}
	unsigned int CompRenderer::GetiNumIndicies()
	{
		return *m_uiNumIndicies;
	}
	unsigned int CompRenderer::GetStartIndexLocation()
	{
		return *m_uiStartIndexLocation;
	}
	int CompRenderer::GetBaseVertexLocation()
	{
		return *m_iBaseVertexLocation;
	}
	std::string CompRenderer::GetVertexFileName()
	{
		return *m_sVertexFileName;
	}
	MERenderer::VertexFormat& CompRenderer::GetVertexFormat()
	{
		return *m_eVertexFormat;
	}
	std::string CompRenderer::GetTextureFileName()
	{
		return *m_TextureFileName;
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
	void CompRenderer::SetTextureFileName(std::string& _texFile)
	{
		m_TextureFileName = &_texFile;
	}

	void CompRenderer::Initialize()
	{

	}


}