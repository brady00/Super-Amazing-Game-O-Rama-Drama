#pragma once
#include "RenderToolsDLL.h"
#include "Containers/ConstantBuffer.h"
#include "ShaderBuffers/ConstantBuffers.h"
#include "ShaderBuffers/LightBuffers.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class RENDERTOOLS_EXPORT ConstantBufferManager
		{
		private:
			ConstantBufferManager();
			ConstantBufferManager(const ConstantBufferManager &) {}
			ConstantBufferManager(const ConstantBufferManager &&) {}
			ConstantBufferManager &operator=(const ConstantBufferManager &) { return *this; }
			ConstantBufferManager &operator=(const ConstantBufferManager &&) { return *this; }
			ConstantBuffer<cbPerObject>				m_PerObjectCBuffer;
			ConstantBuffer<cbPerCamera>				m_PerCameraCBuffer;
			ConstantBuffer<cbMisc>					m_MiscCBuffer;
			ConstantBuffer<cbDebug>					m_DebugCBuffer;
			ConstantBuffer<cbPostProcess>			m_PostProcessCBuffer;
			ConstantBuffer<cbPerSkinnedObject>		m_PerSkinnedObjectCBuffer;
			ConstantBuffer<cbPerTileFrame>			m_PerTileFrameCBuffer;
			ConstantBuffer<cbTerrain>				m_TerrainCBuffer;
			ConstantBuffer<cbDirectionalLight>		m_DirectionalLightCBuffer;
			ConstantBuffer<cbPointLightShadowData>	m_PointLightWithShadowCBuffer;
			ConstantBuffer<cbPointLight>			m_PointLightCBuffer;
			ConstantBuffer<cbSpotLightShadowData>	m_SpotLightWithShadowCBuffer;
			ConstantBuffer<cbSpotLight>				m_SpotLightCBuffer;
			ConstantBuffer<cbForwardLights>			m_ForwardLightsCBuffer;
		public:
			~ConstantBufferManager(void);
			static ConstantBufferManager* GetInstance();
			static void DeleteInstance();
			void CreateBuffers(ID3D11Device* d3Device);
			ConstantBuffer<cbPerObject>				&GetPerObjectCBuffer();
			ConstantBuffer<cbPerCamera>				&GetPerCameraCBuffer();
			ConstantBuffer<cbMisc>					&GetMiscCBuffer();
			ConstantBuffer<cbDebug>					&GetDebugCBuffer();
			ConstantBuffer<cbPostProcess>			&GetPostProcessCBuffer();
			ConstantBuffer<cbPerSkinnedObject>		&GetPerSkinnedObjectCBuffer();
			ConstantBuffer<cbPerTileFrame>			&GetPerTileFrameCBuffer();
			ConstantBuffer<cbTerrain>				&GetTerrainCBuffer();
			ConstantBuffer<cbDirectionalLight>		&GetDirectionalLightCBuffer();
			ConstantBuffer<cbPointLightShadowData>	&GetPointLightWithShadowCBuffer();
			ConstantBuffer<cbPointLight>			&GetPointLightCBuffer();
			ConstantBuffer<cbSpotLightShadowData>	&GetSpotLightWithShadowCBuffer();
			ConstantBuffer<cbSpotLight>				&GetSpotLightCBuffer();
			ConstantBuffer<cbForwardLights>			&GetForwardLightsCBuffer();
			template <typename BufferType>
			ConstantBuffer<BufferType>& GetConstantBuffer();
		};

	}
}