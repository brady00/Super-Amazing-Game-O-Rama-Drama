#include "stdafx.h"
#include "ConstantBufferManager.h"

namespace MonkeyEngine
{
	namespace MERenderer
	{

		ConstantBufferManager::ConstantBufferManager()
		{

		}

		ConstantBufferManager::~ConstantBufferManager()
		{

		}

		ConstantBufferManager* ConstantBufferManager::GetInstance()
		{
			static ConstantBufferManager m_pInstance;
			return&m_pInstance;
		}

		void ConstantBufferManager::DeleteInstance()
		{

		}

		void ConstantBufferManager::CreateBuffers(ID3D11Device* d3Device)
		{
			m_PerObjectCBuffer.Create(d3Device);
			m_PerCameraCBuffer.Create(d3Device);
			m_MiscCBuffer.Create(d3Device);
			m_DebugCBuffer.Create(d3Device);
			m_PostProcessCBuffer.Create(d3Device);
			m_PerSkinnedObjectCBuffer.Create(d3Device);
			m_PerTileFrameCBuffer.Create(d3Device);
			m_TerrainCBuffer.Create(d3Device);
			m_DirectionalLightCBuffer.Create(d3Device);
			m_PointLightWithShadowCBuffer.Create(d3Device);
			m_PointLightCBuffer.Create(d3Device);
			m_SpotLightWithShadowCBuffer.Create(d3Device);
			m_SpotLightCBuffer.Create(d3Device);
			m_ForwardLightsCBuffer.Create(d3Device);
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