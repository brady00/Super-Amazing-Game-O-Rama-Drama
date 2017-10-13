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
			m_VertexShader = nullptr;
			m_PixelShader = nullptr;
			m_Layout = nullptr;
			XMStoreFloat4x4(&m_cbPerObject.world, XMMatrixIdentity());
		}

		Skybox::~Skybox()
		{
			if (m_ObjectConstantBuffer != nullptr)
				m_ObjectConstantBuffer->Release();
			if (m_VertexBuffer != nullptr)
				m_VertexBuffer->Release();
			if (m_IndexBuffer != nullptr)
				m_IndexBuffer->Release();
			if (m_VertexShader != nullptr)
				m_VertexShader->Release();
			if (m_PixelShader != nullptr)
				m_PixelShader->Release();
			if (m_Layout != nullptr)
				m_Layout->Release();
		}

		void Skybox::Load(ID3D11Device* _device, ID3D11DeviceContext* d3DeviceContext, wchar_t* _TextureFilePath)
		{
			VERTEX_POS data[8];
			data[0].position = { -0.5f, 0.5f, 0.5f };
			data[1].position = { 0.5f, 0.5f, 0.5f };
			data[2].position = { 0.5f, 0.5f, -0.5f };
			data[3].position = { -0.5f, 0.5f, -0.5f };
			data[4].position = { -0.5f, -0.5f, 0.5f };
			data[5].position = { 0.5f, -0.5f, 0.5f };
			data[6].position = { 0.5f, -0.5f, -0.5f };
			data[7].position = { -0.5f, -0.5f, -0.5f };

			m_BaseVertexLocation = VertexBufferManager::GetInstance()->GetPositionBuffer().AddVerts(data, 8, _device, d3DeviceContext);

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

			m_VertexShader = ShaderManager::GetInstance()->GetVertexShader(ShaderManager::eShader_VS_SKYBOX);
			m_PixelShader = ShaderManager::GetInstance()->GetPixelShader(ShaderManager::eShader_PS_SKYBOX);

			m_Material.mName = "Skybox";
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
			RasterizerStateManager::GetInstance()->ApplyState(RasterizerStateManager::RS_Default, d3DeviceContext);
			BlendStateManager::GetInstance()->ApplyState(BlendStateManager::BS_Default, d3DeviceContext);
			d3DeviceContext->IASetInputLayout(InputLayoutManager::GetInstance()->GetInputLayout(eVERTEX_POS));
			m_VertexBuffer = VertexBufferManager::GetInstance()->GetPositionBuffer().GetVertexBuffer();
			UINT stride = sizeof(VERTEX_POS);
			UINT offset = 0;
			d3DeviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
			m_IndexBuffer = IndexBuffer::GetInstance()->GetIndicies();
			d3DeviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
			m_cbPerObject.world._41 = GetTransform()->GetPosition().x;
			m_cbPerObject.world._42 = GetTransform()->GetPosition().y;
			m_cbPerObject.world._43 = GetTransform()->GetPosition().z;
			ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().Update(&m_cbPerObject, sizeof(cbPerObject), d3DeviceContext);
			m_ObjectConstantBuffer = ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().GetConstantBuffer();
			d3DeviceContext->VSSetConstantBuffers(0, 1, &m_ObjectConstantBuffer);
			d3DeviceContext->VSSetShader(m_VertexShader, NULL, 0);
			d3DeviceContext->PSSetShader(m_PixelShader, NULL, 0);
			d3DeviceContext->PSSetShaderResources(0, 1, &m_Material.m_d3DiffuseTexture);
			d3DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			d3DeviceContext->DrawIndexed(36, m_StartIndexLocation, m_BaseVertexLocation); // m_StartIndexLocation and m_BaseVertexLocation gotten from AddVerts() and AddIndicies()
		}
	}
}