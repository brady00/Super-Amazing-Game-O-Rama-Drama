#pragma warning(disable: 4561)
#include "Skybox.h"
#include "Managers/DepthStencilStateManager.h"
#include "Managers/RasterizerStateManager.h"
#include "Managers/BlendStateManager.h"
#include "RenderStructures.h"
#include "Transform\Transform.h"
namespace MonkeyEngine
{
	namespace MEObject
	{
		REGISTER_CLASS("Skybox", Skybox)
			Skybox::Skybox()
		{
			m_ObjectConstantBuffer = nullptr;
			m_VertexBuffer = nullptr;
			m_IndexBuffer = nullptr;
			m_VertexShaderColor = nullptr;
			m_VertexShaderTexture = nullptr;
			m_PixelShaderColor = nullptr;
			m_PixelShaderTexture = nullptr;
			m_Layout = nullptr;
			XMStoreFloat4x4(&m_cbPerObject, XMMatrixIdentity());
		}

		Skybox::~Skybox()
		{
			if (m_ObjectConstantBuffer != nullptr)
				m_ObjectConstantBuffer->Release();
			if (m_VertexBuffer != nullptr)
				m_VertexBuffer->Release();
			if (m_IndexBuffer != nullptr)
				m_IndexBuffer->Release();
			if (m_VertexShaderTexture != nullptr)
				m_VertexShaderTexture->Release();
			if (m_PixelShaderTexture != nullptr)
				m_PixelShaderTexture->Release();
			if (m_VertexShaderColor != nullptr)
				m_VertexShaderColor->Release();
			if (m_PixelShaderColor != nullptr)
				m_PixelShaderColor->Release();
			if (m_Layout != nullptr)
				m_Layout->Release();
		}

		void Skybox::Load(ID3D11Device* _device, ID3D11DeviceContext* d3DeviceContext, wchar_t* _TextureFilePath, Material _Material)
		{
			m_Material = _Material;
			VERTEX_POS data[8];
			data[0].position = { -0.5f, 0.5f, 0.5f };
			data[1].position = { 0.5f, 0.5f, 0.5f };
			data[2].position = { 0.5f, 0.5f, -0.5f };
			data[3].position = { -0.5f, 0.5f, -0.5f };
			data[4].position = { -0.5f, -0.5f, 0.5f };
			data[5].position = { 0.5f, -0.5f, 0.5f };
			data[6].position = { 0.5f, -0.5f, -0.5f };
			data[7].position = { -0.5f, -0.5f, -0.5f };
			VERTEX_POSCOLOR data2[8];
			data2[0].position = data[0].position;
			data2[0].color = m_Material.Color;
			data2[1].position = data[1].position;
			data2[1].color = m_Material.Color;
			data2[2].position = data[2].position;
			data2[2].color = m_Material.Color;
			data2[3].position = data[3].position;
			data2[3].color = m_Material.Color;
			data2[4].position = data[4].position;
			data2[4].color = m_Material.Color;
			data2[5].position = data[5].position;
			data2[5].color = m_Material.Color;
			data2[6].position = data[6].position;
			data2[6].color = m_Material.Color;
			data2[7].position = data[7].position;
			data2[7].color = m_Material.Color;
			m_BaseVertexLocationTexture = VertexBufferManager::GetInstance()->GetPositionBuffer().AddVerts(data, 8, _device, d3DeviceContext);
			m_BaseVertexLocationColor = VertexBufferManager::GetInstance()->GetPositionColorBuffer().AddVerts(data2, 8, _device, d3DeviceContext);

			UINT indicies[36] =
			{
				// top
				0, 2, 1,
				0, 3, 2,

				// bottom
				4, 5, 6,
				4, 6, 7,

				// front
				3, 6, 2,
				3, 7, 6,

				// left
				0, 7, 3,
				0, 4, 7,

				// back
				1, 4, 0,
				1, 5, 4,

				// right
				2, 5, 1,
				2, 6, 5
			};

			m_StartIndexLocation = IndexBuffer::GetInstance()->AddIndicies(indicies, 36, _device, d3DeviceContext);


			m_VertexShaderTexture = ShaderManager::GetInstance()->GetVertexShader(ShaderManager::eShader_VS_SKYBOX);
			m_VertexShaderColor = ShaderManager::GetInstance()->GetVertexShader(ShaderManager::eShader_VS_SKYBOXCOLOR);
			m_PixelShaderTexture = ShaderManager::GetInstance()->GetPixelShader(ShaderManager::eShader_PS_SKYBOX);
			m_PixelShaderColor = ShaderManager::GetInstance()->GetPixelShader(ShaderManager::eShader_PS_SKYBOXCOLOR);
			if(m_Material.mDiffuseMapName.length() != 0)
				CreateDDSTextureFromFile(_device, _TextureFilePath, NULL, &m_Material.m_d3DiffuseTexture);
		}

		void Skybox::Initialize(ID3D11Device* _device, ID3D11DeviceContext* d3DeviceContext, wchar_t* _TextureFilePath)
		{
		}

		void Skybox::Update()
		{
		}

		void Skybox::Draw(ID3D11DeviceContext* d3DeviceContext)
		{
			DepthStencilStateManager::GetInstance()->ApplyState(DepthStencilStateManager::DSS_Default, d3DeviceContext);
			RasterizerStateManager::GetInstance()->ApplyState(RasterizerStateManager::RS_NOCULL, d3DeviceContext);
			BlendStateManager::GetInstance()->ApplyState(BlendStateManager::BS_Default, d3DeviceContext);
			UINT stride;
			if (m_Material.m_d3DiffuseTexture)
			{
				d3DeviceContext->IASetInputLayout(InputLayoutManager::GetInstance()->GetInputLayout(eVERTEX_POS));
				m_VertexBuffer = VertexBufferManager::GetInstance()->GetPositionBuffer().GetVertexBuffer();
				stride = sizeof(VERTEX_POS);
			}
			else
			{
				d3DeviceContext->IASetInputLayout(InputLayoutManager::GetInstance()->GetInputLayout(eVERTEX_POSCOLOR));
				m_VertexBuffer = VertexBufferManager::GetInstance()->GetPositionColorBuffer().GetVertexBuffer();
				stride = sizeof(VERTEX_POSCOLOR);
			}
			UINT offset = 0;
			d3DeviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
			m_IndexBuffer = IndexBuffer::GetInstance()->GetIndicies();
			d3DeviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
			m_cbPerObject._41 = GetTransform()->GetPosition().x;
			m_cbPerObject._42 = GetTransform()->GetPosition().y;
			m_cbPerObject._43 = GetTransform()->GetPosition().z;
			cbPerObject temp;
			temp.world = m_cbPerObject;
			ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().Update(&temp, sizeof(cbPerObject), d3DeviceContext);
			m_ObjectConstantBuffer = ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().GetConstantBuffer();
			d3DeviceContext->VSSetConstantBuffers(0, 1, &m_ObjectConstantBuffer);
			if (m_Material.m_d3DiffuseTexture)
			{
				d3DeviceContext->VSSetShader(m_VertexShaderTexture, NULL, 0);
				d3DeviceContext->PSSetShader(m_PixelShaderTexture, NULL, 0);
			}
			else
			{
				d3DeviceContext->VSSetShader(m_VertexShaderColor, NULL, 0);
				d3DeviceContext->PSSetShader(m_PixelShaderColor, NULL, 0);
			}
			d3DeviceContext->PSSetShaderResources(0, 1, &m_Material.m_d3DiffuseTexture);
			d3DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			if (m_Material.m_d3DiffuseTexture)
				d3DeviceContext->DrawIndexed(36, m_StartIndexLocation, m_BaseVertexLocationTexture);
			else
				d3DeviceContext->DrawIndexed(36, m_StartIndexLocation, m_BaseVertexLocationColor);
		}
	}
}