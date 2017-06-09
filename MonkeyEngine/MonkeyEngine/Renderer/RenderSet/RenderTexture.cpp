#include "RenderTexture.h"
#include "RenderShape.h"
#include "../TextureLoaders/WICTextureLoader.h"
#include "../TextureLoaders/DDSTextureLoader.h"
#include "../Renderer.h"

namespace MERenderer
{
	RenderTexture::RenderTexture() : m_d3DiffuseTexture(nullptr), m_pRenderShapes(nullptr)
	{

	}


	RenderTexture::~RenderTexture()
	{
		delete m_pRenderShapes;
		ReleaseCOM(m_d3DiffuseTexture);
		ReleaseCOM(m_d3SamplerState);
	}

	void RenderTexture::Draw()
	{
		
		Renderer::m_d3DeviceContext->PSSetShaderResources(0, 1, &m_d3DiffuseTexture);
		Renderer::m_d3DeviceContext->PSSetSamplers(0,1,&m_d3SamplerState);
		m_pRenderShapes->Draw();
	}

	bool RenderTexture::Load(std::string _TextureFileName)
	{
		std::string extention(&_TextureFileName[_TextureFileName.length() - 4]);
		if (extention == ".dds" || extention == ".DDS")
		{
			std::wstring temp(_TextureFileName.begin(), _TextureFileName.end());
			DirectX::CreateDDSTextureFromFile(Renderer::m_d3Device, temp.c_str(), nullptr, &m_d3DiffuseTexture);
		}
		else
		{
			std::wstring temp(_TextureFileName.begin(), _TextureFileName.end());
			DirectX::CreateWICTextureFromFile(Renderer::m_d3Device, temp.c_str(), nullptr, &m_d3DiffuseTexture);
		}
		D3D11_SAMPLER_DESC samplerDesc;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		// Create the texture sampler state.
		Renderer::m_d3Device->CreateSamplerState(&samplerDesc, &m_d3SamplerState);
		return true;
	}

	const std::string& RenderTexture::GetTextureFileName()
	{
		return m_TextureFileName;
	}

	bool RenderTexture::AddShape(MEObject::CompRenderer* _RenderComp, MEObject::Animator* _AnimationComp)
	{
		if (!ShapeExsits(_RenderComp, _AnimationComp))
		{
			RenderShape* _Shape;
			if (!LoadShape(_RenderComp, _AnimationComp, _Shape))
			{
				delete _Shape;
				return false;
			}
			m_pRenderShapes->AddNode(_Shape);
		}
		else
		{
			RenderShape* temp = (RenderShape*)m_pRenderShapes->getHead();
			while (temp)
			{
				if (temp->GetRenderComp() == _RenderComp || temp->GetAnimationComp() == _AnimationComp)
					if (!LoadShape(_RenderComp, _AnimationComp, temp))
						return false;
				temp = (RenderShape*)temp->GetNext();
			}
		}
		return true;
	}

	bool RenderTexture::ShapeExsits(MEObject::CompRenderer* _RenderComp, MEObject::Animator* _AnimationComp)
	{
		if (m_pRenderShapes == nullptr)
		{
			m_pRenderShapes = new RenderSet;
			return nullptr;
		}
		RenderShape* temp = (RenderShape*)m_pRenderShapes->getHead();
		while (temp)
		{
			if (temp->GetRenderComp() == _RenderComp || temp->GetAnimationComp() == _AnimationComp)
				return true;
			temp = (RenderShape*)temp->GetNext();
		}
		return false;
	}

	bool RenderTexture::LoadShape(MEObject::CompRenderer* _RenderComp, MEObject::Animator* _AnimationComp, RenderShape*& _Shape)
	{
		_Shape = new RenderShape;
		return _Shape->Load(_RenderComp, _AnimationComp);
	}

	ID3D11ShaderResourceView* RenderTexture::GetDiffuseTexture()
	{
		return m_d3DiffuseTexture;
	}

	void RenderTexture::SetDiffuseTexture(ID3D11ShaderResourceView* _Diffuse)
	{
		m_d3DiffuseTexture = _Diffuse;
	}
}