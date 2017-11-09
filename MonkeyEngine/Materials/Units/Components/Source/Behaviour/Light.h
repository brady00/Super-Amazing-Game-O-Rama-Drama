#pragma once
#include "Behaviour.h"
#include "Managers/ConstantBufferManager.h"
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
			DirectX::XMFLOAT2 AreaSize;
			float BounceIntensity;
			DirectX::XMFLOAT4 Color;
			float ColorTemperature;
			unsigned int CommandBufferCount;
			//Texture Cookie;
			DirectX::XMFLOAT2 CookieSize;
			int CullingMask;
			//Flare Flare;
			float Intesity;
			bool IsBaked;
			//LightMapBakeType LightMapBakeType;
			float Range;
			//LightRenderMode RenderMode;
			float ShadowBias;
			int ShadowCustomResolution;
			float ShadowNearPlane;
			float ShadowNormalBias;
			//LightShadowResolution ShadowResolution
			//LightShadows Shadows
			float ShadowStrength;
			float SpotAngle;
			LightType Type;
			bool m_DoesCastShadows;
		public:
			DirectionalLightCBuffer DirectionalLight;
			PointLightCBuffer PointLight;
			SpotLightCBuffer SpotLight;
			virtual void Initialize();
			virtual void Update();
			virtual void ShutDown();
			void Load(LightType type, DirectionalLightCBuffer DLight, PointLightCBuffer PLight, SpotLightCBuffer SLight);
			void Draw(ID3D11DeviceContext* d3DeviceContext);
		};
	}
}
