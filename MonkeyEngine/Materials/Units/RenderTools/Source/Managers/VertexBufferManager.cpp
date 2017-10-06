#include "VertexBufferManager.h"


namespace MonkeyEngine
{
	namespace MERenderer
	{
		VertexBufferManager *VertexBufferManager::m_pInstance = 0;

		VertexBufferManager::VertexBufferManager(void)
		{

		}


		VertexBufferManager::~VertexBufferManager(void)
		{

		}

		VertexBufferManager* VertexBufferManager::GetInstance()
		{
			if (0 == m_pInstance)
			{
				m_pInstance = new VertexBufferManager;
			}
			return m_pInstance;
		}

		void VertexBufferManager::DeleteInstance()
		{
			delete m_pInstance;
			m_pInstance = 0;
		}

		template <>
		VertexBuffer<VERTEX_POS> &VertexBufferManager::GetVertexBuffer()
		{
			return GetPositionBuffer();
		}

		template <>
		VertexBuffer<VERTEX_POSCOLOR> &VertexBufferManager::GetVertexBuffer()
		{
			return GetPositionColorBuffer();
		}

		template <>
		VertexBuffer<VERTEX_POSTEX> &VertexBufferManager::GetVertexBuffer()
		{
			return GetPositionTexBuffer();
		}

		template <>
		VertexBuffer<VERTEX_POSNORMTEX> &VertexBufferManager::GetVertexBuffer()
		{
			return GetPosNormTexBuffer();
		}

		template <>
		VertexBuffer<VERTEX_POSNORMTANTEX> &VertexBufferManager::GetVertexBuffer()
		{
			return GetPosNormTanTexBuffer();
		}

		template <>
		VertexBuffer<VERTEX_POSBONEWEIGHT> &VertexBufferManager::GetVertexBuffer()
		{
			return GetPosBoneWeightBuffer();
		}

		template <>
		VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEX> &VertexBufferManager::GetVertexBuffer()
		{
			return GetPosBoneWeightNormTexBuffer();
		}

		template<>
		VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEX> &VertexBufferManager::GetVertexBuffer()
		{
			return GetPosBoneWeightNormTanTexBuffer();
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

		VertexBuffer<VERTEX_POSNORMTEX>& VertexBufferManager::GetPosNormTexBuffer()
		{
			return m_PosNormTexBuffer;
		}

		VertexBuffer<VERTEX_POSNORMTANTEX>&	VertexBufferManager::GetPosNormTanTexBuffer()
		{
			return m_PosNormTanTexBuffer;
		}

		VertexBuffer<VERTEX_POSBONEWEIGHT>&	VertexBufferManager::GetPosBoneWeightBuffer()
		{
			return m_PosBoneWeightBuffer;
		}

		VertexBuffer<VERTEX_POSBONEWEIGHTNORMTEX>&VertexBufferManager::GetPosBoneWeightNormTexBuffer()
		{
			return m_PosNormBoneWeightTexBuffer;
		}

		VertexBuffer<VERTEX_POSBONEWEIGHTNORMTANTEX>& VertexBufferManager::GetPosBoneWeightNormTanTexBuffer()
		{
			return m_PosNormBoneWeightTanTexBuffer;
		}
	}
}