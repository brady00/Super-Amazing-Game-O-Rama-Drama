#include "RenderTexture.h"



namespace MERenderer
{
	RenderTexture::RenderTexture()
	{
	}


	RenderTexture::~RenderTexture()
	{
	}


	ID3D11ShaderResourceView* RenderTexture::GetDiffuseTexture()
	{
		return m_d3DiffuseTexture;
	}
}