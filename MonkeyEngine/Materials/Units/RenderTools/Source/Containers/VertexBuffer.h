#pragma once
#include "RenderToolsDLL.h"
#include "../Managers/InputLayoutManager.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		template <typename VertexFormat>
		class __declspec(dllexport) VertexBuffer
		{
			friend class VertexBufferManager;
		private:
			ID3D11Buffer* m_D3VertexBuffer;
			VertexBuffer();
			VertexBuffer(const VertexBuffer&) {}
			VertexBuffer &operator=(const VertexBuffer&) { return *this; }
		public:
			size_t m_szTestSize;
			~VertexBuffer();
			UINT AddVerts(const VertexFormat* verts, UINT _numVerts, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext);
			ID3D11Buffer* const GetVertexBuffer();
		};
	}
}
#include "VertexBuffer.hpp"