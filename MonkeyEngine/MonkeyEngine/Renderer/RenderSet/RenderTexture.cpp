#include "RenderTexture.h"
#include "../../Components/Renderer/CompRenderer.h"
#include "../TextureLoaders/WICTextureLoader.h"
#include "../TextureLoaders/DDSTextureLoader.h"
#include "../Renderer.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		RenderTexture::RenderTexture() : m_pRenderShapes(nullptr)
		{

		}


		RenderTexture::~RenderTexture()
		{
			delete m_pRenderShapes;
			ReleaseCOM(m_Material->m_d3DiffuseTexture);
			ReleaseCOM(m_d3SamplerState);
		}

		void RenderTexture::Draw()
		{

			Renderer::m_d3DeviceContext->PSSetShaderResources(0, 1, &m_Material->m_d3DiffuseTexture);
			Renderer::m_d3DeviceContext->PSSetSamplers(0, 1, &m_d3SamplerState);
			m_pRenderShapes->Draw();
		}

		bool RenderTexture::Load(MEObject::Material* _Material)
		{
			m_Material = new MEObject::Material();
			*m_Material = *_Material;
			std::string extention(&m_Material->mDiffuseMapName[m_Material->mDiffuseMapName.length() - 4]);
			if (extention == ".dds" || extention == ".DDS")
			{
				std::wstring temp(m_Material->mDiffuseMapName.begin(), m_Material->mDiffuseMapName.end());
				DirectX::CreateDDSTextureFromFile(Renderer::m_d3Device, temp.c_str(), nullptr, &m_Material->m_d3DiffuseTexture);
			}
			else
			{
				std::wstring temp(_Material->mDiffuseMapName.begin(), _Material->mDiffuseMapName.end());
				DirectX::CreateWICTextureFromFile(Renderer::m_d3Device, temp.c_str(), nullptr, &m_Material->m_d3DiffuseTexture);
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
			return m_Material->mDiffuseMapName;
		}

		void RenderTexture::AddShape(RenderShape* _Shape)
		{
			if (!m_pRenderShapes)
				m_pRenderShapes = new RenderSet;
			m_pRenderShapes->AddNode(_Shape);
		}
	}
}