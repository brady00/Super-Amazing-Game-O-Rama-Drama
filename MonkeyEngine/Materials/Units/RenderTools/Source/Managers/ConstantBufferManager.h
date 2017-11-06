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
			~ConstantBufferManager(void);
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
			//in: void			
			//out: ConstantBufferManager*		
			//	The only instance of the ConstantBufferManager
			//desc: returns the only instance of the ConstantBufferManager
			static ConstantBufferManager* GetInstance();
			//in: ID3D11Device*
			//	The current Renderer's Device
			//out: void								
			//desc: Creates all of the ConstantBuffers used by the Engine
			void CreateBuffers(ID3D11Device* d3Device);
			//in: void			
			//out: ConstantBuffer<cbPerObject>	
			//	The cbPerObject ConstantBuffer
			//desc: returns the cbPerObject ConstantBuffer
			ConstantBuffer<cbPerObject>				&GetPerObjectCBuffer();
			//in: void			
			//out: ConstantBuffer<cbPerCamera>	
			//	The cbPerCamera ConstantBuffer
			//desc: returns the cbPerCamera ConstantBuffer
			ConstantBuffer<cbPerCamera>				&GetPerCameraCBuffer();
			//in: void			
			//out: ConstantBuffer<cbMisc>	
			//	The cbMisc ConstantBuffer
			//desc: returns the cbMisc ConstantBuffer
			ConstantBuffer<cbMisc>					&GetMiscCBuffer();
			//in: void			
			//out: ConstantBuffer<cbDebug>	
			//	The cbDebug ConstantBuffer
			//desc: returns the cbDebug ConstantBuffer
			ConstantBuffer<cbDebug>					&GetDebugCBuffer();
			//in: void			
			//out: ConstantBuffer<cbPostProcess>	
			//	The cbPostProcess ConstantBuffer
			//desc: returns the cbPostProcess ConstantBuffer
			ConstantBuffer<cbPostProcess>			&GetPostProcessCBuffer();
			//in: void			
			//out: ConstantBuffer<cbPerSkinnedObject>	
			//	The cbPerSkinnedObject ConstantBuffer
			//desc: returns the cbPerSkinnedObject ConstantBuffer
			ConstantBuffer<cbPerSkinnedObject>		&GetPerSkinnedObjectCBuffer();
			//in: void			
			//out: ConstantBuffer<cbPerTileFrame>	
			//	The cbPerTileFrame ConstantBuffer
			//desc: returns the cbPerTileFrame ConstantBuffer
			ConstantBuffer<cbPerTileFrame>			&GetPerTileFrameCBuffer();
			//in: void			
			//out: ConstantBuffer<cbTerrain>	
			//	The cbTerrain ConstantBuffer
			//desc: returns the cbTerrain ConstantBuffer
			ConstantBuffer<cbTerrain>				&GetTerrainCBuffer();
			//in: void			
			//out: ConstantBuffer<cbDirectionalLight>	
			//	The cbDirectionalLight ConstantBuffer
			//desc: returns the cbDirectionalLight ConstantBuffer
			ConstantBuffer<cbDirectionalLight>		&GetDirectionalLightCBuffer();
			//in: void			
			//out: ConstantBuffer<cbPointLightShadowData>	
			//	The cbPointLightShadowData ConstantBuffer
			//desc: returns the cbPointLightShadowData ConstantBuffer
			ConstantBuffer<cbPointLightShadowData>	&GetPointLightWithShadowCBuffer();
			//in: void			
			//out: ConstantBuffer<cbPointLight>	
			//	The cbPointLight ConstantBuffer
			//desc: returns the cbPointLight ConstantBuffer
			ConstantBuffer<cbPointLight>			&GetPointLightCBuffer();
			//in: void			
			//out: ConstantBuffer<cbSpotLightShadowData>	
			//	The cbSpotLightShadowData ConstantBuffer
			//desc: returns the cbSpotLightShadowData ConstantBuffer
			ConstantBuffer<cbSpotLightShadowData>	&GetSpotLightWithShadowCBuffer();
			//in: void			
			//out: ConstantBuffer<cbSpotLight>	
			//	The cbSpotLight ConstantBuffer
			//desc: returns the cbSpotLight ConstantBuffer
			ConstantBuffer<cbSpotLight>				&GetSpotLightCBuffer();
			//in: void			
			//out: ConstantBuffer<cbForwardLights>	
			//	The cbForwardLights ConstantBuffer
			//desc: returns the cbForwardLights ConstantBuffer
			ConstantBuffer<cbForwardLights>			&GetForwardLightsCBuffer();
			//in: void			
			//out: ConstantBuffer<BufferType>	
			//	The BufferType ConstantBuffer
			//desc: returns the BufferType ConstantBuffer
			template <typename BufferType>
			ConstantBuffer<BufferType>& GetConstantBuffer();
		};

	}
}