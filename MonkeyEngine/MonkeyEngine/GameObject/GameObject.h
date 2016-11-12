#pragma once
#include "../Object/Object.h"
#include <vector>
class Scene;
class Transform;
namespace MEObject
{
	enum COMPONENT_ID { BASECLASS = -1,  };
	class GameObject : public Object
	{
	private:
		bool m_bActiveInHeirarchy;
		bool m_bActiveSelf;
		bool m_bIsStatic;
		unsigned int m_uiLayer;
		Scene* m_pSCene;
		std::string m_sTag;
		Object* m_pTransform;
		std::vector<Object*> m_vComponents[1];
	public:
		GameObject();
		~GameObject();
	protected:
		void Initialize();
		MEReturnValues::RETURNVALUE Update();
		void ShutDown();
	};
}
