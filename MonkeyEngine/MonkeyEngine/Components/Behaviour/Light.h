#pragma once
#include "Behaviour.h"
#include "../../Renderer/Managers/ConstantBufferManager.h"
namespace MonkeyEngine
{
	namespace MEObject
	{
		enum LightType
		{
			ePointLight = 0,
			eDirectionalLight,
			eSpotLight
		};
		class Light : public Behaviour
		{
		private:
			bool m_DoesCastShadows;
		public:
			DirectionalLightCBuffer m_cbDirectionalLight;
			PointLightCBuffer		m_cbPointLight;
			SpotLightCBuffer		m_cbSpotLight;
			PointLightShadowDataCBuffer	m_cbPointLightWithShadows;
			SpotLightShadowDataCBuffer	m_cbSpotLightWithShadows;
		};
	}
}
