#pragma once
#include "RenderToolsDLL.h"
#include "../Containers/VertexBuffer.h"

namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RENDERTOOLS_EXPORT VertexBufferManager
		{
		private:
			VertexBufferManager();
			VertexBufferManager(const VertexBufferManager &) {}
			VertexBufferManager(const VertexBufferManager &&) {}
			VertexBufferManager &operator=(const VertexBufferManager &) { return *this; }
			VertexBufferManager &operator=(const VertexBufferManager &&) { return *this; }
			VertexBuffer<VERTEX_POS> m_PositionBuffer;
			VertexBuffer<VERTEX_POSCOLOR> m_PositionColorBuffer;
			VertexBuffer<VERTEX_POSTEX> m_PositionTexBuffer;
			VertexBuffer<VERTEX_POSNORMTEX> m_PosNormTexBuffer;
			VertexBuffer<VERTEX_POSNORMTANTEX> m_PosNormTanTexBuffer;
			VertexBuffer<VERTEX_POSBONEWEIGHT> m_PosBoneWeightBuffer;
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEX> m_PosNormBoneWeightTexBuffer;
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEX> m_PosNormBoneWeightTanTexBuffer;
		public:
			~VertexBufferManager(void);
			static VertexBufferManager* GetInstance();
			VertexBuffer<VERTEX_POS> &GetPositionBuffer();
			VertexBuffer<VERTEX_POSCOLOR> &GetPositionColorBuffer();
			VertexBuffer<VERTEX_POSTEX> &GetPositionTexBuffer();
			VertexBuffer<VERTEX_POSNORMTEX> &GetPosNormTexBuffer();
			VertexBuffer<VERTEX_POSNORMTANTEX> &GetPosNormTanTexBuffer();
			VertexBuffer<VERTEX_POSBONEWEIGHT> &GetPosBoneWeightBuffer();
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEX> &GetPosBoneWeightNormTexBuffer();
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEX> &GetPosBoneWeightNormTanTexBuffer();
			template <typename VertexFormat>
			VertexBuffer<VertexFormat> &GetVertexBuffer();
		};
	}
}
