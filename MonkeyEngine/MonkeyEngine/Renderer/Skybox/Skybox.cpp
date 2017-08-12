#include "Skybox.h"

namespace MonkeyEngine
{
	namespace MERenderer
	{
		Skybox::Skybox()
		{
			m_ObjectConstantBuffer = nullptr;
			m_CameraConstantBuffer = nullptr;
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
			if (m_CameraConstantBuffer != nullptr)
				m_CameraConstantBuffer->Release();
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

			unsigned int indicies[36] =
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

			D3D11_BUFFER_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
			bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufferDesc.CPUAccessFlags = NULL;
			bufferDesc.ByteWidth = sizeof(data);

			D3D11_SUBRESOURCE_DATA subResource;
			subResource.pSysMem = data;
			subResource.SysMemPitch = 0;
			subResource.SysMemSlicePitch = 0;

			_device->CreateBuffer(&bufferDesc, &subResource, &m_VertexBuffer);

			D3D11_BUFFER_DESC indexBufferDesc;
			ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
			indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexBufferDesc.CPUAccessFlags = NULL;
			indexBufferDesc.ByteWidth = sizeof(indicies);

			D3D11_SUBRESOURCE_DATA indexSubResource;
			indexSubResource.pSysMem = indicies;
			indexSubResource.SysMemPitch = 0;
			indexSubResource.SysMemSlicePitch = 0;

			_device->CreateBuffer(&indexBufferDesc, &indexSubResource, &m_IndexBuffer);

			m_VertexShader = ShaderManager::GetInstance()->GetVertexShader(ShaderManager::eShader_SKYBOX);
			m_PixelShader = ShaderManager::GetInstance()->GetPixelShader(ShaderManager::eShader_SKYBOX);

			D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			_device->CreateInputLayout(layoutDesc, 1, m_VertexShader, sizeof(m_VertexShader), &m_Layout);

			m_Material.mName = "Skybox";
			CreateDDSTextureFromFile(_device, _TextureFilePath, NULL, &m_Material.m_d3DiffuseTexture);
		}

		void Skybox::Update()
		{
		}

		void Skybox::Draw()
		{
			Renderer::m_d3DeviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, (UINT*)sizeof(VERTEX_POS), 0);

			Renderer::m_d3DeviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			m_ObjectConstantBuffer = ConstantBufferManager::GetInstance()->GetPerObjectCBuffer().GetConstantBuffer();
			m_CameraConstantBuffer = ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().GetConstantBuffer();

			D3D11_MAPPED_SUBRESOURCE mapSubresource;

			Renderer::m_d3DeviceContext->Map(m_CameraConstantBuffer, NULL, D3D11_MAP_READ, NULL, &mapSubresource);
			memcpy_s(&m_cbPerCamera, sizeof(cbPerCamera), mapSubresource.pData, sizeof(cbPerCamera));
			Renderer::m_d3DeviceContext->Unmap(m_CameraConstantBuffer, NULL);

			m_cbPerObject.world._41 = m_cbPerCamera.CameraPos.x;
			m_cbPerObject.world._42 = m_cbPerCamera.CameraPos.y;
			m_cbPerObject.world._43 = m_cbPerCamera.CameraPos.z;

			Renderer::m_d3DeviceContext->Map(m_ObjectConstantBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mapSubresource);
			memcpy_s(mapSubresource.pData, sizeof(cbPerObject), &m_cbPerObject, sizeof(cbPerObject));
			Renderer::m_d3DeviceContext->Unmap(m_ObjectConstantBuffer, NULL);
			Renderer::m_d3DeviceContext->VSSetConstantBuffers(0, 1, &m_ObjectConstantBuffer);

			Renderer::m_d3DeviceContext->VSSetShader(m_VertexShader, NULL, 0);

			Renderer::m_d3DeviceContext->PSSetShader(m_PixelShader, NULL, 0);

			Renderer::m_d3DeviceContext->PSSetShaderResources(0, 1, &m_Material.m_d3DiffuseTexture);

			Renderer::m_d3DeviceContext->IASetInputLayout(m_Layout);

			Renderer::m_d3DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			Renderer::m_d3DeviceContext->DrawIndexed(36, 0, 0);

			Renderer::m_d3DeviceContext->ClearDepthStencilView(Renderer::m_d3DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		}
	}
}