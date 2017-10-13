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

		Skybox* Camera::GetSkybox()
		{
			return m_Skybox;
		}
	}
}