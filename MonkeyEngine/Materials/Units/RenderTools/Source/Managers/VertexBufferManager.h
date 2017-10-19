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
			VertexBuffer<VERTEX_POSTEXCOLOR> m_PositionTexColorBuffer;
			VertexBuffer<VERTEX_POSNORMTEX> m_PosNormTexBuffer;
			VertexBuffer<VERTEX_POSNORMTEXCOLOR> m_PosNormTexColorBuffer;
			VertexBuffer<VERTEX_POSNORMTANTEX> m_PosNormTanTexBuffer;
			VertexBuffer<VERTEX_POSNORMTANTEXCOLOR> m_PosNormTanTexColorBuffer;
			VertexBuffer<VERTEX_POSBONEWEIGHT> m_PosBoneWeightBuffer;
			VertexBuffer<VERTEX_POSBONEWEIGHTCOLOR> m_PosBoneWeightColorBuffer;
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEX> m_PosNormBoneWeightTexBuffer;
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEXCOLOR> m_PosNormBoneWeightTexColorBuffer;
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEX> m_PosNormBoneWeightTanTexBuffer;
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR> m_PosNormBoneWeightTanTexColorBuffer;
		public:
			~VertexBufferManager(void);
			static VertexBufferManager* GetInstance();
			VertexBuffer<VERTEX_POS> &GetPositionBuffer();
			VertexBuffer<VERTEX_POSCOLOR> &GetPositionColorBuffer();
			VertexBuffer<VERTEX_POSTEX> &GetPositionTexBuffer();
			VertexBuffer<VERTEX_POSTEXCOLOR> &GetPositionTexColorBuffer();
			VertexBuffer<VERTEX_POSNORMTEX> &GetPosNormTexBuffer();
			VertexBuffer<VERTEX_POSNORMTEXCOLOR> &GetPosNormTexColorBuffer();
			VertexBuffer<VERTEX_POSNORMTANTEX> &GetPosNormTanTexBuffer();
			VertexBuffer<VERTEX_POSNORMTANTEXCOLOR> &GetPosNormTanTexColorBuffer();
			VertexBuffer<VERTEX_POSBONEWEIGHT> &GetPosBoneWeightBuffer();
			VertexBuffer<VERTEX_POSBONEWEIGHTCOLOR> &GetPosBoneWeightColorBuffer();
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEX> &GetPosBoneWeightNormTexBuffer();
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEXCOLOR> &GetPosBoneWeightNormTexColorBuffer();
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEX> &GetPosBoneWeightNormTanTexBuffer();
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR> &GetPosBoneWeightNormTanTexColorBuffer();
		};
	}
}
