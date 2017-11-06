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
			//in: void			
			//out: VertexBufferManager*		
			//	The only instance of the VertexBufferManager
			//desc: returns the only instance of the VertexBufferManager
			static VertexBufferManager* GetInstance();
			//in: void			
			//out: VertexBuffer<VERTEX_POS>	
			//	The VERTEX_POS VertexBuffer
			//desc: returns the VERTEX_POS VertexBuffer
			VertexBuffer<VERTEX_POS> &GetPositionBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSCOLOR>								
			//	The VERTEX_POSCOLOR VertexBuffer
			//desc: returns the VERTEX_POSCOLOR VertexBuffer
			VertexBuffer<VERTEX_POSCOLOR> &GetPositionColorBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSTEX>								
			//	The VERTEX_POSTEX VertexBuffer
			//desc: returns the VERTEX_POSTEX VertexBuffer
			VertexBuffer<VERTEX_POSTEX> &GetPositionTexBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSTEXCOLOR>								
			//	The VERTEX_POSTEXCOLOR VertexBuffer
			//desc: returns the VERTEX_POSTEXCOLOR VertexBuffer
			VertexBuffer<VERTEX_POSTEXCOLOR> &GetPositionTexColorBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSNORMTEX>								
			//	The VERTEX_POSNORMTEX VertexBuffer
			//desc: returns the VERTEX_POSNORMTEX VertexBuffer
			VertexBuffer<VERTEX_POSNORMTEX> &GetPosNormTexBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSTEXCOLOR>								
			//	The VERTEX_POSTEXCOLOR VertexBuffer
			//desc: returns the VERTEX_POSTEXCOLOR VertexBuffer
			VertexBuffer<VERTEX_POSNORMTEXCOLOR> &GetPosNormTexColorBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSNORMTANTEX>								
			//	The VERTEX_POSNORMTANTEX VertexBuffer
			//desc: returns the VERTEX_POSNORMTANTEX VertexBuffer
			VertexBuffer<VERTEX_POSNORMTANTEX> &GetPosNormTanTexBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSNORMTANTEXCOLOR>								
			//	The VERTEX_POSNORMTANTEXCOLOR VertexBuffer
			//desc: returns the VERTEX_POSNORMTANTEXCOLOR VertexBuffer
			VertexBuffer<VERTEX_POSNORMTANTEXCOLOR> &GetPosNormTanTexColorBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSBONEWEIGHT>								
			//	The VERTEX_POSBONEWEIGHT VertexBuffer
			//desc: returns the VERTEX_POSBONEWEIGHT VertexBuffer
			VertexBuffer<VERTEX_POSBONEWEIGHT> &GetPosBoneWeightBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSBONEWEIGHTCOLOR>								
			//	The VERTEX_POSBONEWEIGHTCOLOR VertexBuffer
			//desc: returns the VERTEX_POSBONEWEIGHTCOLOR VertexBuffer
			VertexBuffer<VERTEX_POSBONEWEIGHTCOLOR> &GetPosBoneWeightColorBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEX>								
			//	The VERTEX_POSBONEWEIGHTNORMTEX VertexBuffer
			//desc: returns the VERTEX_POSBONEWEIGHTNORMTEX VertexBuffer
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEX> &GetPosBoneWeightNormTexBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEXCOLOR>								
			//	The VERTEX_POSBONEWEIGHTNORMTEXCOLOR VertexBuffer
			//desc: returns the VERTEX_POSBONEWEIGHTNORMTEXCOLOR VertexBuffer
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEXCOLOR> &GetPosBoneWeightNormTexColorBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEX>								
			//	The VERTEX_POSBONEWEIGHTNORMTANTEX VertexBuffer
			//desc: returns the VERTEX_POSBONEWEIGHTNORMTANTEX VertexBuffer
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEX> &GetPosBoneWeightNormTanTexBuffer();
			//in: void			
			//out: VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR>								
			//	The VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR VertexBuffer
			//desc: returns the VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR VertexBuffer
			VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR> &GetPosBoneWeightNormTanTexColorBuffer();
		};
	}
}
