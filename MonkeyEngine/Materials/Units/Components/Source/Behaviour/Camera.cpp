#include "Camera.h"


namespace MonkeyEngine
{
	namespace MEObject
	{
		REGISTER_CLASS("Camera", Camera)

		Camera::Camera()
		{
			m_Skybox = (MEObject::Skybox*)ComponentObjectFactory::GetInstance()->Create("Skybox");
		}
		void Camera::Initialize()
		{
			GetGameObject()->AddComponent(m_Skybox, GameObject::COMPONENT_ID::eSkybox);
		}

		void Camera::Update()
		{

		}

		Skybox* Camera::GetSkybox()
		{
			return m_Skybox;
		}
	}
}