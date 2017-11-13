#include "stdafx.h"
#include "IndexBuffer.h"
#include "CriticalRegion.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{

		IndexBuffer::IndexBuffer(void)
		{

		}

		IndexBuffer::~IndexBuffer(void)
		{
			if (m_d3IndexBuffer)
			{
				m_d3IndexBuffer->Release();
				m_d3IndexBuffer = 0;
			}
		}

		IndexBuffer* IndexBuffer::GetInstance()
		{
			static IndexBuffer m_pInstance;
			return &m_pInstance;
		}

		UINT IndexBuffer::AddIndicies(const UINT *_indices, UINT _numIndices, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext)
		{
			UINT ret = 0;
			if (m_d3IndexBuffer)
			{
				D3D11_BUFFER_DESC ibd;
				m_d3IndexBuffer->GetDesc(&ibd);
				D3D11_SUBRESOURCE_DATA iinitData;
				UINT oldBuffeSize = ibd.ByteWidth / sizeof(UINT);
				UINT newBuffeSize = oldBuffeSize + _numIndices;
				ret = oldBuffeSize;
				iinitData.pSysMem = new UINT[newBuffeSize];
				memcpy((char *)(iinitData.pSysMem) + ibd.ByteWidth, _indices, sizeof(UINT) * _numIndices);
				ibd.ByteWidth += sizeof(UINT) * _numIndices;
				ID3D11Buffer *newIndexBufferPtr;
				d3Device->CreateBuffer(&ibd, &iinitData, &newIndexBufferPtr);
				CriticalRegion::Enter(d3DeviceContext);
				d3DeviceContext->CopySubresourceRegion(newIndexBufferPtr, 0, 0, 0, 0, m_d3IndexBuffer, 0, 0);
				CriticalRegion::Exit(d3DeviceContext);
				//ReleaseCOM(indexBufferPtr);
				m_d3IndexBuffer = newIndexBufferPtr;
				delete[] iinitData.pSysMem;
			}
			else
			{
				D3D11_BUFFER_DESC ibd;
				ibd.Usage = D3D11_USAGE_DEFAULT;
				ibd.ByteWidth = sizeof(UINT) * _numIndices;
				ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
				ibd.CPUAccessFlags = 0;
				ibd.MiscFlags = 0;
				ibd.StructureByteStride = 0;
				D3D11_SUBRESOURCE_DATA iinitData;
				iinitData.pSysMem = _indices;
				d3Device->CreateBuffer(&ibd, &iinitData, &m_d3IndexBuffer);
			}
			return ret;
		}

		ID3D11Buffer* const IndexBuffer::GetIndicies()
		{
			return m_d3IndexBuffer;
		}
	}
}
