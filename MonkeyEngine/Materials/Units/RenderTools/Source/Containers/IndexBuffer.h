#pragma once
#include "RenderToolsDLL.h"
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RENDERTOOLS_EXPORT IndexBuffer
		{
		private:
			IndexBuffer();
			IndexBuffer(const IndexBuffer &) {}
			IndexBuffer &operator=(const IndexBuffer &) { return *this; }
			ID3D11Buffer* m_d3IndexBuffer;
			~IndexBuffer();
		public:
			//in: void			
			//out: IndexBuffer*								
			//	The only instance of the IndexBuffer
			//desc: returns the only instance of the IndexBuffer
			static IndexBuffer* GetInstance();
			//in: const UINT*
			//	The Indicies to add to the IndexBuffer
			//in: UINT
			//	The Amount of Indicies to add to the IndexBuffer
			//in: ID3D11Device*
			//	The current Renderer's Device
			//in: ID3D11DeviceContext*
			//	The current Renderer's DeviceContext
			//out: UINT
			//	The StartIndexLocation used for drawing
			//desc: Adds Indicies to the Index Buffer
			UINT AddIndicies(const UINT* _indicies, UINT numIndicies, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext);
			//in: void
			//out: ID3D11Buffer*
			//	D3D Index Buffer used for drawing
			//desc: Gets the D3D Index Buffer used for drawing
			ID3D11Buffer* const GetIndicies();
		};
	}
}
