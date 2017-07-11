#include "../Renderer.h"
namespace MERenderer
{
	template <typename VertexFormat>
	VertexBuffer<VertexFormat>::VertexBuffer()
	{
		m_D3VertexBuffer = 0;
	}

	template <typename VertexFormat>
	VertexBuffer<VertexFormat>::~VertexBuffer()
	{
		ReleaseCOM(m_D3VertexBuffer);
	}

	template <typename VertexFormat>
	UINT VertexBuffer<VertexFormat>::AddVerts(const VertexFormat *verts, UINT _numVerts)
	{
		size_t ret;
		if (!m_D3VertexBuffer)
		{
			ret = 0;
			D3D11_BUFFER_DESC vbd;
			vbd.Usage = D3D11_USAGE_DEFAULT;
			vbd.ByteWidth = sizeof(VertexFormat) * _numVerts;
			vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vbd.CPUAccessFlags = 0;
			vbd.MiscFlags = 0;
			vbd.StructureByteStride = 0;
			D3D11_SUBRESOURCE_DATA vinitData;
			vinitData.pSysMem = verts;
			Renderer::m_d3Device->CreateBuffer(&vbd, &vinitData, &m_D3VertexBuffer);
		}
		else
		{
			D3D11_BUFFER_DESC ibd;
			m_D3VertexBuffer->GetDesc(&ibd);
			D3D11_SUBRESOURCE_DATA iinitData;
			UINT oldBuffeSize = ibd.ByteWidth / sizeof(VertexFormat);
			UINT newBuffeSize = oldBuffeSize + _numVerts;
			iinitData.pSysMem = new VertexFormat[newBuffeSize];
			memcpy((char *)(iinitData.pSysMem) + ibd.ByteWidth, verts, sizeof(VertexFormat) * _numVerts);
			ibd.ByteWidth += sizeof(VertexFormat) * _numVerts;
			ID3D11Buffer *newVertexBufferPtr;
			Renderer::m_d3Device->CreateBuffer(&ibd, &iinitData, &newVertexBufferPtr);
			Renderer::m_DeviceContextMutex.lock();
			Renderer::m_d3DeviceContext->CopySubresourceRegion(newVertexBufferPtr, 0, 0, 0, 0, m_D3VertexBuffer, 0, 0);
			Renderer::m_DeviceContextMutex.unlock();
			//ReleaseCOM(vertexBufferPtr);
			m_D3VertexBuffer = newVertexBufferPtr;
			delete[] iinitData.pSysMem;
			ret = oldBuffeSize;
		}
		return (UINT)ret;
	}

	template <typename VertexFormat>
	ID3D11Buffer* const VertexBuffer<VertexFormat>::GetVertexBuffer()
	{
		return m_D3VertexBuffer;
	}
}