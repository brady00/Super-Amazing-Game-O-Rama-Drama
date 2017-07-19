#include "ConstantBufferManager.h"

namespace MonkeyEngine
{
	namespace MERenderer
	{
		ConstantBufferManager ConstantBufferManager::m_pInstance;

		ConstantBufferManager::ConstantBufferManager()
		{

		}

		ConstantBufferManager::~ConstantBufferManager()
		{

		}

		ConstantBufferManager* ConstantBufferManager::GetInstance()
		{
			return&m_pInstance;
		}

		void ConstantBufferManager::DeleteInstance()
		{

		}

		void ConstantBufferManager::CreateBuffers()
		{
			m_PerObjectCBuffer.Create();
			m_PerCameraCBuffer.Create();
			m_MiscCBuffer.Create();
			m_DebugCBuffer.Create();
			m_PostProcessCBuffer.Create();
			m_PerSkinnedObjectCBuffer.Create();
			m_PerTileFrameCBuffer.Create();
			m_TerrainCBuffer.Create();
			m_DirectionalLightCBuffer.Create();
			m_PointLightWithShadowCBuffer.Create();
			m_PointLightCBuffer.Create();
			m_SpotLightWithShadowCBuffer.Create();
			m_SpotLightCBuffer.Create();
			m_ForwardLightsCBuffer.Create();
		}

		ConstantBuffer<cbPerObject>	&ConstantBufferManager::GetPerObjectCBuffer()
		{
			return m_PerObjectCBuffer;
		}

		ConstantBuffer<cbPerCamera>	&ConstantBufferManager::GetPerCameraCBuffer()
		{
			return m_PerCameraCBuffer;
		}

		ConstantBuffer<cbMisc> &ConstantBufferManager::GetMiscCBuffer()
		{
			return m_MiscCBuffer;
		}

		ConstantBuffer<cbDebug>	&ConstantBufferManager::GetDebugCBuffer()
		{
			return m_DebugCBuffer;
		}

		ConstantBuffer<cbPostProcess> &ConstantBufferManager::GetPostProcessCBuffer()
		{
			return m_PostProcessCBuffer;
		}

		ConstantBuffer<cbPerSkinnedObject> &ConstantBufferManager::GetPerSkinnedObjectCBuffer()
		{
			return m_PerSkinnedObjectCBuffer;
		}

		ConstantBuffer<cbPerTileFrame> &ConstantBufferManager::GetPerTileFrameCBuffer()
		{
			return m_PerTileFrameCBuffer;
		}

		ConstantBuffer<cbTerrain> &ConstantBufferManager::GetTerrainCBuffer()
		{
			return m_TerrainCBuffer;
		}

		ConstantBuffer<cbDirectionalLight> &ConstantBufferManager::GetDirectionalLightCBuffer()
		{
			return m_DirectionalLightCBuffer;
		}

		ConstantBuffer<cbPointLightShadowData> &ConstantBufferManager::GetPointLightWithShadowCBuffer()
		{
			return m_PointLightWithShadowCBuffer;
		}

		ConstantBuffer<cbPointLight> &ConstantBufferManager::GetPointLightCBuffer()
		{
			return m_PointLightCBuffer;
		}

		ConstantBuffer<cbSpotLightShadowData> &ConstantBufferManager::GetSpotLightWithShadowCBuffer()
		{
			return m_SpotLightWithShadowCBuffer;
		}

		ConstantBuffer<cbSpotLight> &ConstantBufferManager::GetSpotLightCBuffer()
		{
			return m_SpotLightCBuffer;
		}

		ConstantBuffer<cbForwardLights>	&ConstantBufferManager::GetForwardLightsCBuffer()
		{
			return m_ForwardLightsCBuffer;
		}

		template <>
		ConstantBuffer<cbPerObject>	&ConstantBufferManager::GetConstantBuffer()
		{
			return m_PerObjectCBuffer;
		}

		template <>
		ConstantBuffer<cbPerCamera>	&ConstantBufferManager::GetConstantBuffer()
		{
			return m_PerCameraCBuffer;
		}

		template <>
		ConstantBuffer<cbMisc> &ConstantBufferManager::GetConstantBuffer()
		{
			return m_MiscCBuffer;
		}

		template <>
		ConstantBuffer<cbDebug>	&ConstantBufferManager::GetConstantBuffer()
		{
			return m_DebugCBuffer;
		}

		template <>
		ConstantBuffer<cbPostProcess> &ConstantBufferManager::GetConstantBuffer()
		{
			return m_PostProcessCBuffer;
		}

		template <>
		ConstantBuffer<cbPerSkinnedObject> &ConstantBufferManager::GetConstantBuffer()
		{
			return m_PerSkinnedObjectCBuffer;
		}

		template <>
		ConstantBuffer<cbPerTileFrame> &ConstantBufferManager::GetConstantBuffer()
		{
			return m_PerTileFrameCBuffer;
		}

		template <>
		ConstantBuffer<cbTerrain> &ConstantBufferManager::GetConstantBuffer()
		{
			return m_TerrainCBuffer;
		}

		template <>
		ConstantBuffer<cbDirectionalLight> &ConstantBufferManager::GetConstantBuffer()
		{
			return m_DirectionalLightCBuffer;
		}

		template <>
		ConstantBuffer<cbPointLightShadowData> &ConstantBufferManager::GetConstantBuffer()
		{
			return m_PointLightWithShadowCBuffer;
		}

		template <>
		ConstantBuffer<cbPointLight> &ConstantBufferManager::GetConstantBuffer()
		{
			return m_PointLightCBuffer;
		}

		template <>
		ConstantBuffer<cbSpotLightShadowData> &ConstantBufferManager::GetConstantBuffer()
		{
			return m_SpotLightWithShadowCBuffer;
		}

		template <>
		ConstantBuffer<cbSpotLight> &ConstantBufferManager::GetConstantBuffer()
		{
			return m_SpotLightCBuffer;
		}

		template <>
		ConstantBuffer<cbForwardLights>	&ConstantBufferManager::GetConstantBuffer()
		{
			return m_ForwardLightsCBuffer;
		}
	}
}