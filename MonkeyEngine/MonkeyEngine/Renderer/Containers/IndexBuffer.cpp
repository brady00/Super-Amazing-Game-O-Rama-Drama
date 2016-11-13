#include "IndexBuffer.h"
#include "../Renderer.h"
namespace MERenderer
{
	IndexBuffer *IndexBuffer::m_pInstance = 0;

	IndexBuffer::IndexBuffer(void)
	{
		m_pInstance = 0;
	}

	IndexBuffer::~IndexBuffer(void)
	{
		//ReleaseCOM(m_d3IndexBuffer);
	}

	IndexBuffer* IndexBuffer::GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new IndexBuffer;
		}
		return m_pInstance;
	}

	void IndexBuffer::DeleteInstance()
	{
		delete m_pInstance;
	}

	UINT IndexBuffer::AddIndicies(const UINT *_indices, UINT _numIndices)
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
			Renderer::m_d3Device->CreateBuffer(&ibd, &iinitData, &newIndexBufferPtr);
			Renderer::m_d3DeviceContext->CopySubresourceRegion(newIndexBufferPtr, 0, 0, 0, 0, m_d3IndexBuffer, 0, 0);
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
			Renderer::m_d3Device->CreateBuffer(&ibd, &iinitData, &m_d3IndexBuffer);
		}
		return ret;
	}
}
