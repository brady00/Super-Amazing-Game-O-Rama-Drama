#include "Skybox.h"

namespace MonkeyEngine
{
	namespace MERenderer
	{
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

		void Skybox::Initialize(ID3D11Device* _device, wchar_t* _TextureFilePath)
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

			m_StartIndexLocation = VertexBufferManager::GetInstance()->GetPositionBuffer().AddVerts(data, 8);

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

			m_BaseVertexLocation = IndexBuffer::GetInstance()->AddIndicies(indicies, 36);

			m_VertexShader = ShaderManager::GetInstance()->GetVertexShader(ShaderManager::eShader_SKYBOX);
			m_PixelShader = ShaderManager::GetInstance()->GetPixelShader(ShaderManager::eShader_SKYBOX);

			m_Material.mName = "Skybox";
			CreateDDSTextureFromFile(_device, _TextureFilePath, NULL, &m_Material.m_d3DiffuseTexture);
		}

		void Skybox::Update()
		{
		}

		void Skybox::Draw(float _cameraPosX, float _cameraPosY, float _cameraPosZ)
		{
			m_VertexBuffer = VertexBufferManager::GetInstance()->GetPositionBuffer().GetVertexBuffer();
			Renderer::m_d3DeviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, (UINT*)sizeof(VERTEX_POS), 0);

			m_IndexBuffer = IndexBuffer::GetInstance()->GetIndicies();
			Renderer::m_d3DeviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			m_cbPerObject.world._41 = _cameraPosX;
			m_cbPerObject.world._42 = _cameraPosY;
			m_cbPerObject.world._43 = _cameraPosZ;
			ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().Update(&m_cbPerObject, sizeof(cbPerObject));
			m_ObjectConstantBuffer = ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().GetConstantBuffer();
			Renderer::m_d3DeviceContext->VSSetConstantBuffers(0, 1, &m_ObjectConstantBuffer);

			Renderer::m_d3DeviceContext->VSSetShader(m_VertexShader, NULL, 0);

			Renderer::m_d3DeviceContext->PSSetShader(m_PixelShader, NULL, 0);

			Renderer::m_d3DeviceContext->PSSetShaderResources(0, 1, &m_Material.m_d3DiffuseTexture);

			Renderer::m_d3DeviceContext->IASetInputLayout(InputLayoutManager::GetInstance()->GetInputLayout(eVERTEX_POS));

			Renderer::m_d3DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			Renderer::m_d3DeviceContext->DrawIndexed(36, m_StartIndexLocation, m_BaseVertexLocation); // m_StartIndexLocation and m_BaseVertexLocation gotten from AddVerts() and AddIndicies()

			Renderer::m_d3DeviceContext->ClearDepthStencilView(Renderer::m_d3DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		}
	}
}