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
			static IndexBuffer* m_pInstance;
			ID3D11Buffer* m_d3IndexBuffer;
		public:
			~IndexBuffer();
			static IndexBuffer* GetInstance();
			static void DeleteInstance();
			UINT AddIndicies(const UINT* _indicies, UINT numIndicies, ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext);
			ID3D11Buffer* const GetIndicies();
		};
	}
}
