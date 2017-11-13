#ifndef EDITOR
#include "CriticalRegion.h"
#endif
namespace MonkeyEngine
{
	namespace MERenderer
	{
		template <typename BufferType>
		ConstantBuffer<BufferType>::ConstantBuffer() : m_D3ConstantBuffer(nullptr)
		{

		}

		template <typename BufferType>
		ConstantBuffer<BufferType>::~ConstantBuffer()
		{
			if (m_D3ConstantBuffer)
			{
				m_D3ConstantBuffer->Release();
				m_D3ConstantBuffer = 0;
			}
		}

		template <typename BufferType>
		void ConstantBuffer<BufferType>::Create(ID3D11Device* d3Device)
		{
			if (m_D3ConstantBuffer)
			{
				m_D3ConstantBuffer->Release();
				m_D3ConstantBuffer = 0;
			}
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(BufferType);
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			d3Device->CreateBuffer(&bd, nullptr, &m_D3ConstantBuffer);
		}

		template <typename BufferType>
		ID3D11Buffer* const ConstantBuffer<BufferType>::GetConstantBuffer()
		{
			return m_D3ConstantBuffer;
		}

		template <typename BufferType>
		void ConstantBuffer<BufferType>::Update(void* _ConstBuffer, unsigned int _Size, ID3D11DeviceContext* d3DeviceContext)
		{
			D3D11_MAPPED_SUBRESOURCE edit;
			BufferType* temp = (BufferType*)_ConstBuffer;
			CriticalRegion::Enter(d3DeviceContext);
			d3DeviceContext->Map(m_D3ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &edit);
			memcpy(edit.pData, temp, _Size);
			d3DeviceContext->Unmap(m_D3ConstantBuffer, 0);
			CriticalRegion::Exit(d3DeviceContext);
		}

		template <typename BufferType>
		BufferType ConstantBuffer<BufferType>::GetBufferValue()
		{
			return m_BufferValue;
		}
	}
}