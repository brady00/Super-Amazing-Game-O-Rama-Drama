#include "stdafx.h"
#include "DefferedRenderTarget.h"
#include "Managers/DepthStencilStateManager.h"
#include "Managers/VertexBufferManager.h"
#include "Managers/InputLayoutManager.h"
#include "Managers/BlendStateManager.h"
#include "Managers/RasterizerStateManager.h"
#include "Managers/ShaderManager.h"
#include "Managers/ConstantBufferManager.h"
#include "RenderStructures.h"
#include "Float3/Float3.h"
namespace MonkeyEngine
{
	using namespace MEMath;
	namespace MERenderer
	{

		DefferedRenderTarget::DefferedRenderTarget()
		{
		}


		DefferedRenderTarget::~DefferedRenderTarget()
		{
		}

		void DefferedRenderTarget::Initialize(ID3D11Device* _Device, ID3D11DeviceContext* d3DeviceContext,  UINT _ScreenHeight, UINT _ScreenWidth)
		{
			D3D11_TEXTURE2D_DESC textureDesc;
			ZeroMemory(&textureDesc, sizeof(textureDesc));
			textureDesc.Width = _ScreenWidth;
			textureDesc.Height = _ScreenHeight;
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;
			for (unsigned int i = 0; i < m_uiBufferCount; i++)
				_Device->CreateTexture2D(&textureDesc, NULL, &m_d3GbufferTarget[i]);
			D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
			renderTargetViewDesc.Format = textureDesc.Format;
			renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetViewDesc.Texture2D.MipSlice = 0;
			for (unsigned int i = 0; i < m_uiBufferCount; i++)
				_Device->CreateRenderTargetView(m_d3GbufferTarget[i], &renderTargetViewDesc, &m_d3GBufferTargetView[i]);
			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
			shaderResourceViewDesc.Format = textureDesc.Format;
			shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
			shaderResourceViewDesc.Texture2D.MipLevels = 1;
			for (unsigned int i = 0; i < m_uiBufferCount; i++)
				_Device->CreateShaderResourceView(m_d3GbufferTarget[i], &shaderResourceViewDesc, &m_d3GBufferShaderView[i]);
			float left, right, top, bottom;
			VERTEX_POSTEX* vertices = new VERTEX_POSTEX[6];

			left = (float)((_ScreenHeight / 2.0f) * -1);
			right = left + (float)_ScreenWidth;
			top = (float)(_ScreenHeight / 2.0f);
			bottom = top - (float)_ScreenHeight;

			vertices[0].position = Float3(-1, -1, 0.0f);
			vertices[0].texcoord = DirectX::XMFLOAT2(0.0f, 1.0f);
			vertices[1].position = Float3(-1, 1, 0.0f);
			vertices[1].texcoord = DirectX::XMFLOAT2(0.0f, 0.0f);
			vertices[2].position = Float3(1, -1, 0.0f);
			vertices[2].texcoord = DirectX::XMFLOAT2(1.0f, 1.0f);
			vertices[3].position = Float3(1, -1, 0.0f);
			vertices[3].texcoord = DirectX::XMFLOAT2(1.0f, 1.0f);
			vertices[4].position = Float3(-1, 1, 0.0f);
			vertices[4].texcoord = DirectX::XMFLOAT2(0.0f, 0.0f);
			vertices[5].position = Float3(1, 1, 0.0f);
			vertices[5].texcoord = DirectX::XMFLOAT2(1.0f, 0.0f);

			m_uiStartVert = VertexBufferManager::GetInstance()->GetPositionTexBuffer().AddVerts(vertices, 6, _Device, d3DeviceContext);

			delete[] vertices;
			vertices = 0;

			D3D11_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
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
			_Device->CreateSamplerState(&samplerDesc, &m_d3SamplerState);

		}

		void DefferedRenderTarget::ResizeBuffers(ID3D11Device* _Device, UINT _ScreenHeight, UINT _ScreenWidth)
		{
			D3D11_TEXTURE2D_DESC textureDesc;
			ZeroMemory(&textureDesc, sizeof(textureDesc));
			textureDesc.Width = _ScreenWidth;
			textureDesc.Height = _ScreenHeight;
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;
			for (unsigned int i = 0; i < m_uiBufferCount; i++)
			{
				if (m_d3GbufferTarget[i])
				{
					m_d3GbufferTarget[i]->Release();
					m_d3GbufferTarget[i] = nullptr;
				}
				_Device->CreateTexture2D(&textureDesc, NULL, &m_d3GbufferTarget[i]);
			}
			D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
			renderTargetViewDesc.Format = textureDesc.Format;
			renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetViewDesc.Texture2D.MipSlice = 0;
			for (unsigned int i = 0; i < m_uiBufferCount; i++)
			{
				if (m_d3GBufferTargetView[i])
				{
					m_d3GBufferTargetView[i]->Release();
					m_d3GBufferTargetView[i] = nullptr;
				}
				_Device->CreateRenderTargetView(m_d3GbufferTarget[i], &renderTargetViewDesc, &m_d3GBufferTargetView[i]);
			}
			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
			shaderResourceViewDesc.Format = textureDesc.Format;
			shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
			shaderResourceViewDesc.Texture2D.MipLevels = 1;
			for (unsigned int i = 0; i < m_uiBufferCount; i++)
			{
				if (m_d3GBufferShaderView[i])
				{
					m_d3GBufferShaderView[i]->Release();
					m_d3GBufferShaderView[i] = nullptr;
				}
				_Device->CreateShaderResourceView(m_d3GbufferTarget[i], &shaderResourceViewDesc, &m_d3GBufferShaderView[i]);
			}
		}

		void DefferedRenderTarget::Update(ID3D11DeviceContext* d3DeviceContext)
		{
			d3DeviceContext->IASetInputLayout(InputLayoutManager::GetInstance()->GetInputLayout(VertexFormat::eVERTEX_POSTEX));
			BlendStateManager::GetInstance()->ApplyState(BlendStateManager::BS_Default, d3DeviceContext);
			RasterizerStateManager::GetInstance()->ApplyState(RasterizerStateManager::RS_NOCULL, d3DeviceContext);
			DepthStencilStateManager::GetInstance()->ApplyState(DepthStencilStateManager::DSS_NoDepth, d3DeviceContext);
			UINT Stride = sizeof(VERTEX_POSTEX);
			UINT Offset = 0;
			ID3D11Buffer* vertbuff = VertexBufferManager::GetInstance()->GetPositionTexBuffer().GetVertexBuffer();
			d3DeviceContext->IASetVertexBuffers(0, 1, &vertbuff, &Stride, &Offset);
			d3DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			d3DeviceContext->VSSetShader(ShaderManager::GetInstance()->GetVertexShader((ShaderManager::VertexShaderType)VertexFormat::eVERTEX_POSTEX), 0, 0);
			d3DeviceContext->PSSetShader(ShaderManager::GetInstance()->GetPixelShader(ShaderManager::PixelShaderType::eShader_PS_GBUFFER), 0, 0);
			d3DeviceContext->PSSetShaderResources(0, 2, m_d3GBufferShaderView);
			d3DeviceContext->PSSetSamplers(0, 1, &m_d3SamplerState);
			d3DeviceContext->Draw(6, m_uiStartVert);
		}

		void DefferedRenderTarget::Shutdown()
		{
			for (unsigned int i = 0; i < m_uiBufferCount; i++)
				ReleaseCOM(m_d3GBufferTargetView[i]);
			for (unsigned int i = 0; i < m_uiBufferCount; i++)
				ReleaseCOM(m_d3GBufferShaderView[i]);
			for (unsigned int i = 0; i < m_uiBufferCount; i++)
				ReleaseCOM(m_d3GbufferTarget[i]);
			ReleaseCOM(m_d3SamplerState);
		}

		void DefferedRenderTarget::SetAsRenderTarget(ID3D11DepthStencilView* _StencilView, ID3D11DeviceContext* _DeviceContext)
		{
			float color[] = { 0,0,1,1 };
			_DeviceContext->OMSetRenderTargets(m_uiBufferCount, m_d3GBufferTargetView, _StencilView);
			for (unsigned int i = 0; i < m_uiBufferCount; i++)
				_DeviceContext->ClearRenderTargetView(m_d3GBufferTargetView[i], color);
		}
	}
}