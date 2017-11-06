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
			size_t m_szTestSize;
		public:
			~VertexBuffer();
			//in: const VertexFormat*
			//	The Verticies to add to the VertexBuffer
			//in: UINT
			//	The Amount of Verticies to add to the VertexBuffer
			//in: ID3D11Device*
			//	The current Renderer's Device
			//in: ID3D11DeviceContext*
			//	The current Renderer's DeviceContext
			//out: UINT
			//	The BaseVertexLocation used for drawing
			//desc: Adds Verticies to the Vertex Buffer
			UINT AddVerts(const VertexFormat* verts, UINT _numVerts, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext);
			//in: void
			//out: ID3D11Buffer*
			//	D3D Vertex Buffer used for drawing
			//desc: Gets the D3D Vertex Buffer used for drawing
			ID3D11Buffer* const GetVertexBuffer();
		};
	}
}
#include "VertexBuffer.hpp"