#pragma once
#include <d3d11.h>
namespace MonkeyEngine
{
	namespace MERenderer
	{
		template <typename BufferType>
		class ConstantBuffer
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
			void Create();
			ID3D11Buffer* const GetConstantBuffer();
			BufferType GetBufferValue();
			void Update(void* _ConstBuffer, unsigned int _Size);
		};
	}
}
#include "ConstantBuffer.hpp"
