#include "Light.h"
#include "Managers\ConstantBufferManager.h"
#include "Transform\Transform.h"
namespace MonkeyEngine
{
	using namespace MERenderer;
	namespace MEObject
	{
		void Light::Initialize()
		{

		}

		void Light::Update()
		{

		}

		void Light::ShutDown()
		{

		}

		void Light::Load(LightType type, DirectionalLightCBuffer DLight, PointLightCBuffer PLight, SpotLightCBuffer SLight)
		{
			Type = type;
			switch (Type)
			{
			case MonkeyEngine::MEObject::ePointLight:
				DLight = DirectionalLight;
				break;
			case MonkeyEngine::MEObject::eDirectionalLight:
				PLight = PointLight;
				break;
			case MonkeyEngine::MEObject::eSpotLight:
				SLight = SpotLight;
				break;
			default:
				break;
			}
		}

		void Light::Draw(ID3D11DeviceContext* d3DeviceContext)
		{
			//update Constant Buffers
			switch (Type)
			{
			case MonkeyEngine::MEObject::ePointLight:
			{
				cbPointLight temp;
				temp.pointLight = PointLight;
				ConstantBufferManager::GetInstance()->GetPointLightCBuffer().Update(&temp, sizeof(temp), d3DeviceContext);
				ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetPointLightCBuffer().GetConstantBuffer();
				d3DeviceContext->VSSetConstantBuffers(temp.POINT_LIGHT_REGISTER_SLOT, 1, &buf);
				break;
			}
			case MonkeyEngine::MEObject::eDirectionalLight:
			{
				cbDirectionalLight temp;
				temp.DirLight = DirectionalLight;
				ConstantBufferManager::GetInstance()->GetDirectionalLightCBuffer().Update(&temp, sizeof(temp), d3DeviceContext);
				ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetDirectionalLightCBuffer().GetConstantBuffer();
				d3DeviceContext->VSSetConstantBuffers(temp.DIRECTIONAL_LIGHT_SHADOW_REGISTER_SLOT, 1, &buf);
				break;
			}
			case MonkeyEngine::MEObject::eSpotLight:
			{
				cbSpotLight temp;
				temp.spotLight = SpotLight;
				ConstantBufferManager::GetInstance()->GetSpotLightCBuffer().Update(&temp, sizeof(temp), d3DeviceContext);
				ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetSpotLightCBuffer().GetConstantBuffer();
				d3DeviceContext->VSSetConstantBuffers(temp.SPOT_LIGHT_REGISTER_SLOT, 1, &buf);
				break;
			}
			default:
				break;
			}
		}
	}
}