#include "stdafx.h"
#include "VertexBufferManager.h"


namespace MonkeyEngine
{
	namespace MERenderer
	{

		VertexBufferManager::VertexBufferManager(void)
		{

		}


		VertexBufferManager::~VertexBufferManager(void)
		{

		}

		VertexBufferManager* VertexBufferManager::GetInstance()
		{
			static VertexBufferManager m_pInstance;
			return &m_pInstance;
		}


		VertexBuffer<VERTEX_POS>& VertexBufferManager::GetPositionBuffer()
		{
			return m_PositionBuffer;
		}

		VertexBuffer<VERTEX_POSCOLOR>& VertexBufferManager::GetPositionColorBuffer()
		{
			return m_PositionColorBuffer;
		}

		VertexBuffer<VERTEX_POSTEX>& VertexBufferManager::GetPositionTexBuffer()
		{
			return m_PositionTexBuffer;
		}

		VertexBuffer<VERTEX_POSTEXCOLOR> &VertexBufferManager::GetPositionTexColorBuffer()
		{
			return m_PositionTexColorBuffer;
		}

		VertexBuffer<VERTEX_POSNORMTEX>& VertexBufferManager::GetPosNormTexBuffer()
		{
			return m_PosNormTexBuffer;
		}

		VertexBuffer<VERTEX_POSNORMTEXCOLOR> &VertexBufferManager::GetPosNormTexColorBuffer()
		{
			return m_PosNormTexColorBuffer;

		}

		VertexBuffer<VERTEX_POSNORMTANTEX>&	VertexBufferManager::GetPosNormTanTexBuffer()
		{
			return m_PosNormTanTexBuffer;
		}

		VertexBuffer<VERTEX_POSNORMTANTEXCOLOR> &VertexBufferManager::GetPosNormTanTexColorBuffer()
		{
			return m_PosNormTanTexColorBuffer;
		}

		VertexBuffer<VERTEX_POSBONEWEIGHT>&	VertexBufferManager::GetPosBoneWeightBuffer()
		{
			return m_PosBoneWeightBuffer;
		}

		VertexBuffer<VERTEX_POSBONEWEIGHTCOLOR> &VertexBufferManager::GetPosBoneWeightColorBuffer()
		{
			return m_PosBoneWeightColorBuffer;
		}

		VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEX>&VertexBufferManager::GetPosBoneWeightNormTexBuffer()
		{
			return m_PosNormBoneWeightTexBuffer;
		}

		VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEXCOLOR> &VertexBufferManager::GetPosBoneWeightNormTexColorBuffer()
		{
			return m_PosNormBoneWeightTexColorBuffer;
		}

		VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEX>& VertexBufferManager::GetPosBoneWeightNormTanTexBuffer()
		{
			return m_PosNormBoneWeightTanTexBuffer;
		}

		VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR> &VertexBufferManager::GetPosBoneWeightNormTanTexColorBuffer()
		{
			return m_PosNormBoneWeightTanTexColorBuffer;
		}
	}
}