#include "../Renderer.h"
namespace MERenderer
{
	template <typename BufferType>
	ConstantBuffer<BufferType>::ConstantBuffer() : m_D3ConstantBuffer(nullptr)
	{
		
	}

	template <typename BufferType>
	ConstantBuffer<BufferType>::~ConstantBuffer()
	{
		ReleaseCOM(m_D3ConstantBuffer);
	}

	template <typename BufferType>
	void ConstantBuffer<BufferType>::Create()
	{
		ReleaseCOM(m_D3ConstantBuffer);
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(BufferType);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Renderer::m_d3Device->CreateBuffer(&bd, nullptr, &m_D3ConstantBuffer);
	}

	template <typename BufferType>
	ID3D11Buffer* const ConstantBuffer<BufferType>::GetConstantBuffer()
	{
		return m_D3ConstantBuffer;
	}

	template <typename BufferType>
	void ConstantBuffer<BufferType>::Update(void* _ConstBuffer, unsigned int _Size)
	{
		D3D11_MAPPED_SUBRESOURCE edit;
		BufferType* temp = (BufferType*)_ConstBuffer;
		Renderer::m_d3DeviceContext->Map(m_D3ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &edit);
		memcpy(edit.pData, temp, _Size);
		Renderer::m_d3DeviceContext->Unmap(m_D3ConstantBuffer, 0);
		Renderer::m_d3DeviceContext->VSSetConstantBuffers(0, 1, &m_D3ConstantBuffer);
	}

	template <typename BufferType>
	BufferType ConstantBuffer<BufferType>::GetBufferValue()
	{
		return m_BufferValue;
	}
}
