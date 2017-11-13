#pragma once
#include "RenderToolsDLL.h"
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		template <typename BufferType>
		class __declspec(dllexport) ConstantBuffer
		{
			friend class ConstantBufferManager;
		private:
			ID3D11Buffer* m_D3ConstantBuffer;
			BufferType m_BufferValue;
			ConstantBuffer();
			ConstantBuffer(const ConstantBuffer&) {}
			ConstantBuffer &operator=(const ConstantBuffer&) { return *this; }
		public:
			~ConstantBuffer();
			//in: void
			//out: ID3D11Device*
			//	The current Renderer's Device
			//desc: Creates the D3D ConstantBuffer
			void Create(ID3D11Device* d3Device);
			//in: void
			//out: ID3D11Buffer*
			//	The D3D Constant Buffer
			//desc: Creates the D3D ConstantBuffer
			ID3D11Buffer* const GetConstantBuffer();
			//in: void
			//out: ID3D11Buffer*
			//	The D3D Constant Buffer
			//desc: Creates the D3D ConstantBuffer
			BufferType GetBufferValue();
			void Update(void* _ConstBuffer, unsigned int _Size, ID3D11DeviceContext* d3DeviceContext);
		};
	}
}
#include "ConstantBuffer.hpp"
