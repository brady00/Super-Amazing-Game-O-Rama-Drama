#include "RenderTexture.h"
#include "../TextureLoaders/WICTextureLoader.h"
#include "../TextureLoaders/DDSTextureLoader.h"
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
			if (m_Material->m_d3DiffuseTexture)
			{

				m_Material->m_d3DiffuseTexture->Release();
				m_Material->m_d3DiffuseTexture = 0;
			}
			if (m_d3SamplerState)
			{
				m_d3SamplerState->Release();
				m_d3SamplerState = 0;
			}
		}

		void RenderTexture::Draw(ID3D11DeviceContext* d3DeviceContext, unsigned int State)
		{

			d3DeviceContext->PSSetShaderResources(0, 1, &m_Material->m_d3DiffuseTexture);
			d3DeviceContext->PSSetSamplers(0, 1, &m_d3SamplerState);
			m_pRenderShapes->Draw(d3DeviceContext, State);
		}
		
		bool RenderTexture::Load(Material* _Material, ID3D11Device* d3Device)
		{
			m_Material = new Material();
			*m_Material = *_Material;
			std::string extention(&m_Material->mDiffuseMapName[m_Material->mDiffuseMapName.length() - 4]);
			if (extention == ".dds" || extention == ".DDS")
			{
				std::wstring temp(m_Material->mDiffuseMapName.begin(), m_Material->mDiffuseMapName.end());
				DirectX::CreateDDSTextureFromFile(d3Device, temp.c_str(), nullptr, &m_Material->m_d3DiffuseTexture);
			}
			else
			{
				std::wstring temp(_Material->mDiffuseMapName.begin(), _Material->mDiffuseMapName.end());
				DirectX::CreateWICTextureFromFile(d3Device, temp.c_str(), nullptr, &m_Material->m_d3DiffuseTexture);
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
			d3Device->CreateSamplerState(&samplerDesc, &m_d3SamplerState);
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
			m_pRenderShapes->AddNode((RenderNode*)_Shape);
		}
	}
}